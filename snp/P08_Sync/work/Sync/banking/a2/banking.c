//******************************************************************************
// Course:  BSy
// File:    banking.c (copied from a1, with additional branchLock protection)
// Author:  M. Thaler, ZHAW
// Purpose: locking mechanisms
// Version: v.fs20
//******************************************************************************

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#include "banking.h"

//******************************************************************************

typedef struct account_struct_ {
    long int balance;
    pthread_mutex_t acntLock;
} Account;

typedef struct branch_struct {
    Account *accounts;
    pthread_mutex_t branchLock; 
} Branch;

//******************************************************************************

static Branch *Bank;
static int nBranches, nAccounts;

//******************************************************************************
// banking functions

void makeBank(int num_branches, int num_accounts) {
    nBranches = num_branches;
    nAccounts = num_accounts;
    Bank = (Branch *)malloc(nBranches * sizeof(Branch));

    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);

    for (int  i = 0; i < nBranches; i++) {
        Bank[i].accounts = (Account *)malloc(nAccounts * sizeof(Account));
        pthread_mutex_init(&(Bank[i].branchLock), &attr);
        for (int j = 0; j < nAccounts; j++) {
            Bank[i].accounts[j].balance = 0;
            pthread_mutex_init((&(Bank[i].accounts[j].acntLock)), &attr);
        }
    }
}

void deleteBank(void) {
    for (int i = 0; i < nBranches; i++)
        free(Bank[i].accounts);
    free(Bank);
    nBranches = nAccounts = 0;
}

long int withdraw(int branchNr, int accountNr, long int value) {
    long int rv = 0;
    // lock branch and account to ensure atomicity
    pthread_mutex_lock(&Bank[branchNr].branchLock);
    pthread_mutex_lock(&Bank[branchNr].accounts[accountNr].acntLock);
    long int tmp = Bank[branchNr].accounts[accountNr].balance - value;
    if (tmp >= 0) {
        Bank[branchNr].accounts[accountNr].balance = tmp;
        rv = value;
    }
    pthread_mutex_unlock(&Bank[branchNr].accounts[accountNr].acntLock);
    pthread_mutex_unlock(&Bank[branchNr].branchLock);
    return rv;
}

void deposit(int branchNr, int accountNr, long int value) {
    // lock branch and account to ensure atomicity
    pthread_mutex_lock(&Bank[branchNr].branchLock);
    pthread_mutex_lock(&Bank[branchNr].accounts[accountNr].acntLock);
    Bank[branchNr].accounts[accountNr].balance += value;
    pthread_mutex_unlock(&Bank[branchNr].accounts[accountNr].acntLock);
    pthread_mutex_unlock(&Bank[branchNr].branchLock);
}

void transfer(int fromB, int toB, int accountNr, long int value) {
    int money = withdraw(fromB, accountNr, value);
    if (money >= 0)
        deposit(toB, accountNr, money);
}

void checkAssets(void) {
    static long assets = 0;
    long sum = 0;
    for (int i = 0; i < nBranches; i++) {
        for (int j = 0; j < nAccounts; j++) {
            sum += (long)Bank[i].accounts[j].balance;
        }
    }
    if (assets == 0) {
        assets = sum;
        printf("Balance of accounts is: %ld\n", sum);
    }
    else {
        if (sum != assets)
            printf("Balance of accounts is: %ld ... not correct\n", sum);
        else
            printf("Balance of accounts is: %ld ... correct\n", assets);
    }
}

//******************************************************************************
