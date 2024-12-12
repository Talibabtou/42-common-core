/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdumas <gdumas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 07:45:05 by jmougel           #+#    #+#             */
/*   Updated: 2024/11/30 16:39:14 by gdumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "header.hpp"

ClapTrap::ClapTrap(): _name("none"), _hit_point(10), _energy_point(10), _attack_damage(0)
{
	std::cout << "Default ClapTrap constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& copy)
{
	std::cout << "ClapTrap copy constructor called" << std::endl;
	if (this != &copy)
		*this = copy;
}

ClapTrap&	ClapTrap::operator=(const ClapTrap& copy)
{
	std::cout << "ClapTrap affectation operator called" << std::endl;
	if (this != &copy)
	{
		this->_name = copy._name;
		this->_hit_point = copy._hit_point;
		this->_energy_point = copy._energy_point;
		this->_attack_damage = copy._attack_damage;
	}
	return (*this);
}

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap destructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name): _name(name), _hit_point(10), _energy_point(10), _attack_damage(0)
{
	std::cout << "ClapTrap constructor with parameter <std::string> called" << std::endl;
}

void	ClapTrap::attack(const std::string& target)
{
	if (this->_energy_point > 0 && this->_hit_point > 0)
	{
		this->_energy_point -= 1;
		std::cout << BOLD << "ClapTrap " << this->_name << " attacks " << target << ", causing " << END;
		std::cout << BOLD << _attack_damage << " points of damage!" << END << std::endl;
	}
	else if (this->_energy_point <= 0)
		std::cout << BOLD << RED << "ClapTrap " << this->_name << " has no more energy." << END << std::endl;
	else if (this->_hit_point <= 0)
		std::cout << BOLD << RED << "ClapTrap " << this->_name << " has not enought life." << END << std::endl;
	if (this->_energy_point < 0)
		this->_energy_point = 0;
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	if (this->_hit_point > 0)
	{
		this->_hit_point -= amount;
		std::cout << BOLD << "ClapTrap " << this->_name << " take " << amount << " point of damage." << END << std::endl;
		if (this->_hit_point < 0)
			this->_hit_point = 0;
		std::cout << RED << "	ClapTrap " << this->_name << " now has " << this->_hit_point << " life points." << END << std::endl;
	}
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (this->_energy_point > 0 && this->_hit_point > 0)
	{
		this->_energy_point -= 1;
		this->_hit_point += amount;
		std::cout << BOLD << "ClapTrap " << this->_name << " recovers " << amount << " life points." END << std::endl;
		std::cout << RED << "	ClapTrap " << this->_name << " now has " << this->_hit_point << " life points." << END << std::endl;
	}
	else if (this->_energy_point <= 0)
		std::cout << BOLD << RED << "ClapTrap " << this->_name << " has no more energy." << END << std::endl;
	else if (this->_hit_point <= 0)
		std::cout << BOLD << RED << "ClapTrap " << this->_name << " has not enought life." << END << std::endl;
	if (this->_energy_point < 0)
		this->_energy_point = 0;
}

std::string	ClapTrap::getName()
{
	return (this->_name);
}
