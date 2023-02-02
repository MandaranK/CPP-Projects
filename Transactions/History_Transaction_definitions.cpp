#include <cassert>
#include <iomanip>
#include <iostream>

#include "project4.hpp"
#include "History.hpp"
#include "Transaction.hpp"

////////////////////////////////////////////////////////////////////////////////
// Definitions for Transaction class
////////////////////////////////////////////////////////////////////////////////
//
//

// Constructor
// TASK 1
//
Transaction::Transaction( std::string ticker_symbol, unsigned int day_date, unsigned int month_date,
unsigned year_date, bool buy_sell_trans, unsigned int number_shares, double trans_amount) 
{
  symbol = ticker_symbol;
  day = day_date;
  month = month_date;
  year = year_date;
  
  if (buy_sell_trans == true) {
    trans_type = "Buy";
  } else if (buy_sell_trans == false) {
    trans_type = "Sell";
  }

  shares = number_shares;
  amount = trans_amount;
  
  acb = 0;
  acb_per_share = 0;
  share_balance = 0;
  cgl = 0;
  
  trans_id = assigned_trans_id;
  assigned_trans_id++;

}

 


// Destructor
// TASK 1
//
Transaction::~Transaction() {}

// Overloaded < operator.
// TASK 2
//
bool Transaction::operator<( Transaction const &other ) 
{
  if(this->year < other.year) {
    return true;
  } else if (this->year > other.year) {
    return false;
  } else if (this->year == other.year) {
    if (this->month < other.month) {
      return true;
    } else if (this->month > other.month) {
      return false;
    } else if (this->month == other.month) {
      if (this->day < other.day) {
        return true;
      } else if (this->day > other.day) {
        return false;
      } else if (this->day == other.day) {
        if (this->trans_id > other.trans_id) {
          return true;
        } else {
          return false;
        }
      }
    }
  }
}


// GIVEN
// Member functions to get values.
//
std::string Transaction::get_symbol() const { return symbol; }
unsigned int Transaction::get_day() const { return day; }
unsigned int Transaction::get_month() const { return month; }
unsigned int Transaction::get_year() const { return year; }
unsigned int Transaction::get_shares() const { return shares; }
double Transaction::get_amount() const { return amount; }
double Transaction::get_acb() const { return acb; }
double Transaction::get_acb_per_share() const { return acb_per_share; }
unsigned int Transaction::get_share_balance() const { return share_balance; }
double Transaction::get_cgl() const { return cgl; }
bool Transaction::get_trans_type() const { return (trans_type == "Buy") ? true: false ; }
unsigned int Transaction::get_trans_id() const { return trans_id; }
Transaction *Transaction::get_next() { return p_next; }

// GIVEN
// Member functions to set values.
//
void Transaction::set_acb( double acb_value ) { acb = acb_value; }
void Transaction::set_acb_per_share( double acb_share_value ) { acb_per_share = acb_share_value; }
void Transaction::set_share_balance( unsigned int bal ) { share_balance = bal ; }
void Transaction::set_cgl( double value ) { cgl = value; }
void Transaction::set_next( Transaction *p_new_next ) { p_next = p_new_next; }

// GIVEN
// Print the transaction.
//
void Transaction::print() {
  std::cout << std::fixed << std::setprecision(2);
  std::cout << std::setw(4) << get_trans_id() << " "
    << std::setw(4) << get_symbol() << " "
    << std::setw(4) << get_day() << " "
    << std::setw(4) << get_month() << " "
    << std::setw(4) << get_year() << " ";


  if ( get_trans_type() ) {
    std::cout << "  Buy  ";
  } else { std::cout << "  Sell "; }

  std::cout << std::setw(4) << get_shares() << " "
    << std::setw(10) << get_amount() << " "
    << std::setw(10) << get_acb() << " " << std::setw(4) << get_share_balance() << " "
    << std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
    << std::setw(10) << std::setprecision(3) << get_cgl()
    << std::endl;
}


////////////////////////////////////////////////////////////////////////////////
// Definitions for the History class
////////////////////////////////////////////////////////////////////////////////
//
//


// Constructor
// TASK 3
//
History::History(){
  p_head = NULL;
}

// Destructor
// TASK 3
//
History::~History(){
  Transaction *p_temp{};
  while (p_head != nullptr) {
    p_temp = p_head; 
    p_head = p_head->get_next();
    delete p_temp;
  }
}


// read_history(...): Read the transaction history from file.
// TASK 4
//
void History::read_history(){
  ece150::open_file();

  while (ece150::next_trans_entry()) {
    Transaction *read = new Transaction(ece150::get_trans_symbol(), ece150::get_trans_day(), ece150::get_trans_month(), ece150::get_trans_year(), ece150::get_trans_type(), ece150::get_trans_shares(), ece150::get_trans_amount());
    History::insert(read);
  }

  ece150::close_file();
}

// insert(...): Insert transaction into linked list.
// TASK 5
//
void History::insert(Transaction *p_new_trans){
  
  if (p_head == nullptr) {
    p_head = p_new_trans;
  }
  else {
    Transaction *new_trans{p_head};
    while ( new_trans->get_next() != nullptr ) {
      new_trans = new_trans->get_next();
    }
    new_trans->set_next(p_new_trans);
  }
}

// sort_by_date(): Sort the linked list by trade date.
// TASK 6
//
void History::sort_by_date(){}

// update_acb_cgl(): Updates the ACB and CGL values.
// TASK 7
//
void History::update_acb_cgl(){
  Transaction *p_node;
  double new_acb = 0;
  double new_share_balance = 0;
  double new_acb_per_share = 0;
  double new_cgl = 0;
  
    for(p_node = p_head; p_node != nullptr; p_node = p_node->get_next()){
      if (p_node->get_trans_type()) {
        new_acb += p_node->get_amount();
        p_node->set_acb(new_acb);
        new_share_balance += p_node->get_shares();
        p_node->set_share_balance(new_share_balance);
        new_acb_per_share += p_node->get_acb() / p_node->get_share_balance();
        p_node->set_acb_per_share(new_acb_per_share);
      } else {
        new_acb -=(p_node->get_shares())*new_acb_per_share;
        p_node->set_acb(new_acb);
        new_share_balance -= p_node->get_shares();
        p_node->set_share_balance(new_share_balance);
        new_acb_per_share += p_node->get_acb() / p_node->get_share_balance();
        p_node->set_acb_per_share(new_acb_per_share);
        new_cgl = p_node->get_amount() - new_acb_per_share * p_node->get_shares();
        p_node->set_cgl(new_cgl);
      }
    }
}


// compute_cgl(): )Compute the ACB, and CGL.
// TASK 8
double History::compute_cgl(unsigned int year){
  Transaction *p_node;
  double new_acb = 0;
  double new_share_balance = 0;
  double new_acb_per_share = 0;
  double new_cgl = 0;
  double cgl_total = 0;
  
  for(p_node = p_head; p_node != nullptr; p_node = p_node->get_next()){
    if (p_node->get_trans_type()) {
      new_acb += p_node->get_amount();
      p_node->set_acb(new_acb);
      new_share_balance += p_node->get_shares();
      p_node->set_share_balance(new_share_balance);
      new_acb_per_share += p_node->get_acb() / p_node->get_share_balance();
      p_node->set_acb_per_share(new_acb_per_share);
    } else {
      new_acb -= (p_node->get_shares())*new_acb_per_share;
      p_node->set_acb(new_acb);
      new_share_balance -= p_node->get_shares();
      p_node->set_share_balance(new_share_balance);
      new_cgl = p_node->get_amount() - new_acb_per_share * p_node->get_shares();
      p_node->set_cgl(new_cgl);
      cgl_total += new_cgl; 
      new_acb_per_share += p_node->get_acb() / p_node->get_share_balance();
      p_node->set_acb_per_share(new_acb_per_share);
    }
  }
  return cgl_total;
}

// unsigned int Transaction::get_shares() const { return shares; }
// double Transaction::get_amount() const { return amount; }
// double Transaction::get_acb() const { return acb; }
// double Transaction::get_acb_per_share() const { return acb_per_share; }
// unsigned int Transaction::get_share_balance() const { return share_balance; }
// double Transaction::get_cgl() const { return cgl; }
// bool Transaction::get_trans_type() const { return (trans_type == "Buy") ? true: false ; }

// void Transaction::set_acb( double acb_value ) { acb = acb_value; }
// void Transaction::set_acb_per_share( double acb_share_value ) { acb_per_share = acb_share_value; }
// void Transaction::set_share_balance( unsigned int bal ) { share_balance = bal ; }
// void Transaction::set_cgl( double value ) { cgl = value; }
// void Transaction::set_next( Transaction *p_new_next ) { p_next = p_new_next; }



// print() Print the transaction history.
//TASK 9
//
void History::print(){
  std::cout << "========== BEGIN TRANSACTION HISTORY ============" << std::endl;
  Transaction *p_temp = p_head;
  while (p_temp != nullptr) {
    p_temp->print();
    p_temp = p_temp->get_next();
  }
  std::cout << "========== END TRANSACTION HISTORY ============" << std::endl;
}


// GIVEN
// get_p_head(): Full access to the linked list.
//
Transaction *History::get_p_head() { return p_head; }
