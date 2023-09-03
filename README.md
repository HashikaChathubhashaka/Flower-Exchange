# Flower Exchange Project

![Project Logo](https://github.com/HashikaChathubhashaka/Flower-Exchange/blob/main/Images/cover.jpg)

## Overview

The Flower Exchange Project is an application for managing and executing flower orders. It provides a platform for clients to submit buy and sell orders for different types of flowers. This README provides an overview of the project, its features, how to get started, and more.

## Table of Contents

- [How It Works](#how-it-works)
- [Features](#features)
- [Getting Started](#getting-started)
- [Contributors](#contributors)

## How It Works

The Flower Exchange Project is designed to efficiently manage and execute flower orders. Here's how it works:

1. **Input Data:** The application takes an `orders.csv` file as input. This CSV file contains a list of flower orders submitted by clients. Each order specifies details such as the client's order ID, the flower type (instrument), whether it's a buy or sell order, the quantity, and the price.

2. **Order Validation:** Before processing the orders, the application performs thorough validation to ensure the orders meet specific criteria. Orders are rejected if they don't contain required fields, have an invalid instrument, an invalid side, a non-positive price, a quantity that's not a multiple of 10, or a quantity outside the range (min = 10, max = 1000).

3. **Order Book:** Once validated, the orders are added to separate order books for each flower type. Order books have two sides: Buy and Sell. Buy orders are sorted in ascending order of price, while Sell orders are sorted in descending order of price. Orders with the same price are ordered by time priority.

4. **Order Execution:** The application continuously matches buy and sell orders from the order books. When a match is found, an execution report is generated with details such as the client order ID, order ID, instrument, side, price, quantity, status (executed or rejected), reason for rejection (if applicable), and transaction time.

5. **Output Data:** The execution reports are recorded in an `exec_reports.csv` file. This file provides a comprehensive overview of all executed and rejected orders, making it easy to track the status of each order.

By following these steps, the Flower Exchange Project provides a robust platform for clients to trade flower orders efficiently, ensuring that valid orders are executed promptly while rejecting those that do not meet the specified criteria.


## Features

- Separate order books for different flower types.
- Buy and sell orders are sorted based on price.
- Orders with the same price are ordered by time priority.
- Checks for order validity based on several criteria.
- Generates detailed execution reports.

## Getting Started

1. Open the application.cpp file in your preferred text editor or IDE.

2. Create an orders.csv file containing the flower orders you want to process.

3. In the application.cpp code, replace the placeholder "path/to/orders.csv" with the actual path to your orders.csv file.

4. Compile the application.cpp using your C++ compiler.

--------------------Note --------------------

-***Example `orders.csv` file and `exec_reports.csv` files are provided.***
**You can simply remove the `exec_reports.csv` file and edit the `orders.csv` as you want.**
**Then by running `Application.cpp` You can get new `exec_reports.csv` file.**

## Contributors

- [Sandeepa Dilshan](https://github.com/sandeepa0105)
- [Hashika Chathubhashaka](https://github.com/HashikaChathubhashaka)
