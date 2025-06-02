// Диалог начала игры (туториал) 03.10.06 boal
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref sld;
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Finish_2":
			SetAchievement("Test_Ach");
			dialog.text = "Кэп, последний вопрос. Что мне передать команде?";
			link.l1     = "В каком это смысле?";
			link.l1.go  = "Finish_2_0";
		break;
		
		case "Finish_2_0":
			dialog.text = "Ну, люди хотят понимать, что им ожидать. Я так вижу, что вы ещё не определились, чем заниматься будете.";
			link.l1     = "Какие у меня есть варианты?";
			link.l1.go  = "Finish_2_0_1";
		break;
		
		case "Finish_2_0_1":
			dialog.text = "О, Карибы это совершенно уникальное место, кэп. Торгуйте, грабьте, ввязываетесь в сомнительные истории, ищите клады - есть много способов стать карибской легендой. Мы с парнями посовещались и готовы принять любое ваше решение.";
			link.l1     = "Обязательно выбирать что-то одно?";
			link.l1.go  = "Finish_2_0_2";
		break;
		
		case "Finish_2_0_2":
			dialog.text = "Нет, конечно, но хорошо бы наметить наши первые приоритеты.";
			link.l1     = "Как и любой нормальный человек, я хочу миллион!";
			link.l1.go  = "Finish_2_1";
			link.l2     = "Хочу, чтобы ко мне относились с уважением. Уважением, которым пользовался л'Олонэ после того, как разграбил Маракайбо.";
			link.l2.go  = "Finish_2_2";
			link.l3     = "Приключения! Хочу побывать в странных местах и познакомится с разными людьми.";
			link.l3.go  = "Finish_2_3";
			link.l4     = "Всегда мечтал"+GetSexPhrase("","а")+" о славе охотника за кладами. Романтика!";
			link.l4.go  = "Finish_2_4";
			link.l5     = "Оставь свои советы, Сандро. Зачем себя ограничивать? Я знаю, что делать и хочу всё и сразу!";
			link.l5.go  = "Finish_2_5";
		break;
		
		case "Finish_2_1":
			pchar.questTemp.SanBoxTarget = 1;
			dialog.text = "Вполне себе цель, кэп. Самый быстрый способ это грабеж торговых судов и контрабанда. Можете, конечно, торговать и честно, но времени уйдёт несколько больше. Впрочем, ограничивать себя не надо - берите любую работу, да ввязываетесь во все неприятности, какие найдёте. Так и зарабатываются большие деньги. Я передам команде, кэп. Храни нас всех Бог!";
			link.l1     = "Начать игру";
			link.l1.go  = "Finish_3";
		break;
		
		case "Finish_2_2":
			pchar.questTemp.SanBoxTarget = 2;
			dialog.text = "А вы знаете-то, как л'Олонэ карьеру закончил? Ну, не мне вас судить, капитан. Кровь невинных действительно оплачивается хорошо, но готовьтесь к последствиям. Вам потребуется крупный корабль, или даже целая эскадра, чтобы подавить форт и высадить десант. Можете конечно, взять город и с суши - человек четыреста вам хватит, но будьте уверены, что не подавленный гарнизон обязательно вас выбьет обратно в джунгли и очень быстро. Я передам команде, кэп. Храни нас всех Бог!";
			link.l1     = "Начать игру";
			link.l1.go  = "Finish_3";
		break;
		
		case "Finish_2_3":
			pchar.questTemp.SanBoxTarget = 3;
			dialog.text = "И того, и другого у нас избыток, кэп! Посещайте города, общайтесь с людьми и приключения сами вас найдут. Учитывайте только, что серьёзные люди обратятся к вам за помощью только после того, как вы покажете, чего стоите и сделаете себе какое-никакое, но имя. Команде это понравится. Храни нас всех Бог!";
			link.l1     = "Начать игру";
			link.l1.go  = "Finish_3";
		break;
		
		case "Finish_2_4":
			pchar.questTemp.SanBoxTarget = 4;
			dialog.text = "Романтики там мало, кэп. Дело долгое, но достаточно прибыльное, особенно если удача вас не обделила. Ищите карты сокровищ у продавцов в тавернах, да поглядывайте через плечо - охотников поживится за ваш счёт на этом пути вы встретите немало. Да, и вот ещё: cамые ценные клады можно найти, собрав половинки карт из кладов попроще, так что дерзайте! Храни нас всех Бог!";
			link.l1     = "Начать игру";
			link.l1.go  = "Finish_3";
		break;
		
		case "Finish_2_5":
			pchar.questTemp.SanBoxTarget = 5;
			dialog.text = "Тогда вы знаете чего вам будет стоить звание карибской легенды, капитан. Команда верит в вас и ждёт ваших призов. Храни нас всех Бог!";
			link.l1     = "Начать игру";
			link.l1.go  = "Finish_3";
		break;
		
		case "Finish_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_RemoveCheckMinHP(Pchar); // снимем проверки
			LAi_SetImmortal(pchar, false);
			LAi_SetPlayerType(pchar);
			InterfaceStates.Buttons.Save.enable = true;
			DoReloadCharacterToLocation(Pchar.HeroParam.Location, Pchar.HeroParam.Group, Pchar.HeroParam.Locator);
			SetFunctionTimerCondition("SanBoxStatusCityRemove", 0, 0, 30, false);
			bGameMenuStart = false;
			//AddQuestRecordInfo("Guide_AtSea", "1");
			//AddQuestRecordInfo("Guide_OnLand", "1");
			DoQuestFunctionDelay("Tutorial_CameraControlFP", 2.5);
			//DoQuestFunctionDelay("Tutorial_Rest", 2.5);
		break;
		
		case "ChangePIRATES":
            LAi_SetCitizenTypeNoGroup(NPChar);
            LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = "Node_5";
			DialogExit();
			pchar.SystemInfo.ChangePIRATES = true;
			LaunchCharacter(pchar);
		break;
		
		case "ChangePIRATES_Jess":
            LAi_SetCitizenTypeNoGroup(NPChar);
            LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = "Node_5_Jess";
			DialogExit();
			pchar.SystemInfo.ChangePIRATES = true;
			LaunchCharacter(pchar);
		break;
		
		case "Teach_battle_1":
		    LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = "Teach_6";
			AddDialogExitQuestFunction("Tut_TeachBattle");
			DialogExit();
		break;
		
		case "First time":
			NextDiag.TempNode = "First time";
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			LAi_LockFightMode(Pchar, false);
			LAi_SetActorTypeNoGroup(Pchar);
			LAi_ActorTurnToCharacter(Pchar, NPChar);
			if (pchar.name == "Джессика")
			{
				dialog.text = "Наконец-то вы снова на ногах, капитан. Хвала Всевышнему, а то мы уж и не знали, что думать.";
				if (bBettaTestMode)
				{
					link.l0 = "BetaTest - пропустить и начать игру";
					link.l0.go = "Finish_2";
				}
				link.l1 = "Сандро? Чёрт возьми, что произошло? И почему так адски болит голова?..";
				link.l1.go = "Node_1_Jess";
			}
			else
			{
				dialog.text = "Вот, капитан, теперь вы хоть на себя стали похожи. Как себя чувствуете?";
				//link.l2 = "BetaTest - Начать тест квеста Лонгвея";
				//link.l2.go = "PZ_Test_Start_1";
				//link.l3 = "BetaTest - Начать тест квеста Леди Бет";
				//link.l3.go = "LadyBeth_Test_Start_1";
				if (bBettaTestMode)
				{
					link.l0 = "BetaTest - пропустить и начать игру";
					link.l0.go = "Finish_2";
				}
				link.l1 = "Хм... а раньше на кого был"+ GetSexPhrase("","а") +" похож"+ GetSexPhrase("","а") +"?";
				link.l1.go = "Node_1";
			}
			locCameraFromToPos(-2.04, 4.95, 13.26, true, -0.82, 2.52, 7.87);
		break;
		
		case "LadyBeth_Test_Start_1":
			dialog.text = "Откуда начнём?";
			link.l1     = "Сразу в битву. Обычный отряд.";
			link.l1.go  = "LadyBeth_Test_Start_CaimanBitvaLite";
			link.l2     = "Сразу в битву. Усиленный отряд";
			link.l2.go  = "LadyBeth_Test_Start_CaimanBitvaStrong";
			link.l3     = "Можно подготовиться перед Кайманом. Блеквуд будет ждать там сколько нужно.";
			link.l3.go  = "LadyBeth_Test_Start_Caiman";
		break;
		
		case "LadyBeth_Test_Start_CaimanBitvaLite":
			DialogExit();
			LAi_SetPlayerType(pchar);
			InterfaceStates.Buttons.Save.enable = true;
			bGameMenuStart = false;
			RemoveAllCharacterItems(pchar, true);
			AddMoneyToCharacter(pchar, 10000000);
			pchar.rank = 8;
			AddCharacterExpToSkill(pchar, "Sailing", 50000);
			pchar.skill.FreeSPECIAL = sti(pchar.skill.FreeSPECIAL) + 25;
			pchar.Skill.FreeSkill = sti(pchar.Skill.FreeSkill) + 1000;
			pchar.perks.FreePoints_self = sti(pchar.perks.FreePoints_self) + 30;
			pchar.perks.FreePoints_ship = sti(pchar.perks.FreePoints_ship) + 30;
			GiveItem2Character(PChar, "blade_16");
			GiveItem2Character(PChar, "blade_13");
			EquipCharacterByItem(Pchar, "blade_13");
			GiveItem2Character(PChar, "pistol5");
			EquipCharacterByItem(Pchar, "pistol5");
			GiveItem2Character(PChar, "cirass8");
			GiveItem2Character(PChar, "cirass1");
			EquipCharacterByItem(Pchar, "cirass1");
			GiveItem2Character(PChar, "spyglass4");
			EquipCharacterByItem(Pchar, "spyglass4");
			GiveItem2Character(PChar, "talisman2");
			GiveItem2Character(PChar, "talisman13");
			EquipCharacterByItem(Pchar, "talisman13");
			GiveItem2Character(PChar, "mushket3");
			GiveItem2Character(PChar, "mushket5");
			GiveItem2Character(PChar, "mushket8");
			AddItems(Pchar, "cartridge", 50);
			AddItems(Pchar, "grapeshot", 50);
			AddItems(Pchar, "GunPowder", 50);
			AddItems(Pchar, "potion4", 20);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "cartridge");
			AddItems(pchar, "gold_dublon", 500);
			// Мой корабль
			pchar.Ship.Type = GenerateShipExt(SHIP_PINK, true, pchar);
			pchar.Ship.name = "Принципио";
			SetSailsColor(pchar, 0); //белый хлопковый парус
			SetBaseShipData(pchar);
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS6;
			SetCrewQuantityFull(pchar);
			pchar.Ship.Crew.Morale = 100;
			pchar.Ship.Crew.Exp.Sailors = 100;
			pchar.Ship.Crew.Exp.Cannoners = 100;
			pchar.Ship.Crew.Exp.Soldiers = 100;
			UpgradeShipParameter(pchar, "SpeedRate"); //апгрейдить скорость
			UpgradeShipParameter(pchar, "TurnRate");  //маневренность
			UpgradeShipParameter(pchar, "HP");        //корпус
			ChangeCrewExp(pchar, "Sailors", 100);
			ChangeCrewExp(pchar, "Cannoners", 100);
			ChangeCrewExp(pchar, "Soldiers", 100);
			SetCharacterGoods(pchar, GOOD_BALLS, 400);
			SetCharacterGoods(pchar, GOOD_GRAPES, 400);
			SetCharacterGoods(pchar, GOOD_KNIPPELS, 400);
			SetCharacterGoods(pchar, GOOD_BOMBS, 500);
			SetCharacterGoods(pchar, GOOD_FOOD, 3000);
			SetCharacterGoods(pchar, GOOD_POWDER, 2000);
			SetCharacterGoods(pchar, GOOD_WEAPON, 500);
			SetCharacterGoods(pchar, GOOD_MEDICAMENT, 500);
			SetCharacterGoods(pchar, GOOD_RUM, 500);
			setCharacterShipLocation(pchar, "Shore35");
			setWDMPointXZ("Shore35");
			// Томми
			sld = GetCharacter(NPC_GenerateCharacter("Irons", "Irons", "man", "Irons", 12, ENGLAND, -1, false, "quest"));
			sld.name = StringFromKey("BlackMark_5");
			sld.lastname = StringFromKey("BlackMark_6");
			sld.rank = 12;
			sld.CanTakeMushket = true;
			sld.PriorityMode = 2;
			sld.MusketerDistance = 10;
			SetSPECIAL(sld, 6, 9, 6, 3, 7, 6, 9);
			SetSelfSkill(sld, 15, 15, 50, 60, 20);
			SetShipSkill(sld, 5, 1, 4, 6, 1, 1, 7, 1, 10);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "Jager"); //Егерь
			SetCharacterPerk(sld, "Sniper"); //Снайпер
			GiveItem2Character(sld, "cirass10");
			EquipCharacterByItem(sld, "cirass10");
			GiveItem2Character(sld, "blade_42");
			EquipCharacterByItem(sld, "blade_42");
			GiveItem2Character(sld, "indian_2");
			GiveItem2Character(sld, "mushket1");
			EquipCharacterByItem(sld, "mushket1");
			AddItems(sld, "potionrum", 5);
			AddItems(sld, "GunPowder", 15);
			AddItems(sld, "bullet", 15);
			LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "bullet");
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			sld.quest.OfficerPrice = 15000;
			sld.OfficerWantToGo.DontGo = true;
			sld.CompanionDisable = true;
			sld.loyality = MAX_LOYALITY;
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0; 
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			sld.CanTakeMushket = true;
			LAi_SetOfficerType(sld);
			sld.dialog.filename = "Quest\BlackMark.c";
			sld.Dialog.CurrentNode = "Irons_officer";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(sld, "HiredDate");
			LAi_SetHP(sld, 170.0, 170.0);
			// Тичингиту
			sld = GetCharacter(NPC_GenerateCharacter("Tichingitu", "maskog", "man", "man", 20, FRANCE, -1, false, "quest"));
			sld.name = "Тичингиту";
			sld.lastname = "";
			sld.greeting = "Tichingitu";
			sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			sld.dialog.currentnode = "Tichingitu";
			sld.rank = 20;
			LAi_SetHP(sld, 200.0, 200.0);
			SetSPECIAL(sld, 4, 9, 5, 5, 10, 8, 8);
			SetSelfSkill(sld, 50, 50, 50, 70, 50);
			SetShipSkill(sld, 30, 30, 30, 30, 50, 30, 50, 50, 30);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			AddItems(sld, "mushket1", 1);
			sld.CanTakeMushket = true;
			GiveItem2Character(sld, "blade_10");
			sld.equip.blade = "blade_10";
			GiveItem2Character(sld, "pistol1");
			sld.equip.gun = "pistol1";
			GiveItem2Character(sld, "cirass1");
			EquipCharacterbyItem(sld, "cirass1");
			AddItems(sld, "cartridge", 50);
			sld.quest.OfficerPrice = sti(pchar.rank) * 20;
			sld.OfficerWantToGo.DontGo = true;
			sld.CompanionDisable = true;
			sld.loyality = MAX_LOYALITY;
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			LAi_SetOfficerType(sld);
			sld.dialog.currentnode = "Tichingitu_officer";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(sld, "HiredDate");
			AddItems(sld, "potion2", 10);
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0; 
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			// Дюран
			sld = GetCharacter(NPC_GenerateCharacter("Duran", "Claude_Durand", "man", "man", 15, FRANCE, -1, false, "soldier"));
			sld.name = StringFromKey("FMQ_49");
			sld.lastname = StringFromKey("FMQ_50");
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.Dialog.CurrentNode = "hired";
			sld.rank = 15;
			sld.reputation = 25;
			LAi_SetHP(sld, 180, 180);
			SetSelfSkill(sld, 45, 50, 45, 45, 35);
			SetShipSkill(sld, 25, 10, 20, 20, 20, 20, 20, 20, 30);
			SetSPECIAL(sld, 8, 5, 8, 4, 6, 8, 5);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "Tireless");
			sld.SuperShooter = true;
			sld.quest.OfficerPrice = sti(pchar.rank) * 20;
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			EquipCharacterByArtefact(sld, "indian_1");
			EquipCharacterByArtefact(sld, "indian_7");
			EquipCharacterByArtefact(sld, "indian_4");
			GiveItem2Character(sld, "blade_12");
			sld.equip.blade = "blade_12";
			GiveItem2Character(sld, "pistol1");
			EquipCharacterbyItem(sld, "pistol1");
			LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
			TakeNItems(sld, "bullet", 20);
			AddItems(sld, "gunpowder", 20);
			sld.greeting = "Duran_officer";
			LAi_SetOfficerType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0; 
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			
			//Телепорт
			pchar.questTemp.LadyBeth_LiteGroup = true;
			setCharacterShipLocation(pchar, "Shore17");
			DoFunctionReloadToLocation("Shore17", "reload", "sea", "LadyBeth_CaimanBuhta_3");
			//выключить сторонние квесты
			PChar.quest.Red_Chieftain.over = "yes";
			PChar.quest.False_Trace.over = "yes";
			PChar.quest.FalseTrace_Prepare.over = "yes";
			//Остальное
			locations[FindLocation("Caiman_Jungle_01")].DisableEncounters = true;
			locations[FindLocation("Shore16")].DisableEncounters = true;
			locations[FindLocation("Shore17")].DisableEncounters = true;
		break;
		
		case "LadyBeth_Test_Start_CaimanBitvaStrong":
			DialogExit();
			LAi_SetPlayerType(pchar);
			InterfaceStates.Buttons.Save.enable = true;
			bGameMenuStart = false;
			RemoveAllCharacterItems(pchar, true);
			AddMoneyToCharacter(pchar, 10000000);
			pchar.rank = 8;
			AddCharacterExpToSkill(pchar, "Sailing", 50000);
			pchar.skill.FreeSPECIAL = sti(pchar.skill.FreeSPECIAL) + 25;
			pchar.Skill.FreeSkill = sti(pchar.Skill.FreeSkill) + 1000;
			pchar.perks.FreePoints_self = sti(pchar.perks.FreePoints_self) + 30;
			pchar.perks.FreePoints_ship = sti(pchar.perks.FreePoints_ship) + 30;
			GiveItem2Character(PChar, "blade_16");
			GiveItem2Character(PChar, "blade_13");
			EquipCharacterByItem(Pchar, "blade_13");
			GiveItem2Character(PChar, "pistol5");
			EquipCharacterByItem(Pchar, "pistol5");
			GiveItem2Character(PChar, "cirass8");
			GiveItem2Character(PChar, "cirass1");
			EquipCharacterByItem(Pchar, "cirass1");
			GiveItem2Character(PChar, "spyglass4");
			EquipCharacterByItem(Pchar, "spyglass4");
			GiveItem2Character(PChar, "talisman2");
			GiveItem2Character(PChar, "talisman13");
			EquipCharacterByItem(Pchar, "talisman13");
			GiveItem2Character(PChar, "mushket3");
			GiveItem2Character(PChar, "mushket5");
			GiveItem2Character(PChar, "mushket8");
			AddItems(Pchar, "cartridge", 50);
			AddItems(Pchar, "grapeshot", 50);
			AddItems(Pchar, "GunPowder", 50);
			AddItems(Pchar, "potion4", 20);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "cartridge");
			AddItems(pchar, "gold_dublon", 500);
			// Мой корабль
			pchar.Ship.Type = GenerateShipExt(SHIP_PINK, true, pchar);
			pchar.Ship.name = "Принципио";
			SetSailsColor(pchar, 0); //белый хлопковый парус
			SetBaseShipData(pchar);
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS6;
			SetCrewQuantityFull(pchar);
			pchar.Ship.Crew.Morale = 100;
			pchar.Ship.Crew.Exp.Sailors = 100;
			pchar.Ship.Crew.Exp.Cannoners = 100;
			pchar.Ship.Crew.Exp.Soldiers = 100;
			UpgradeShipParameter(pchar, "SpeedRate"); //апгрейдить скорость
			UpgradeShipParameter(pchar, "TurnRate");  //маневренность
			UpgradeShipParameter(pchar, "HP");        //корпус
			ChangeCrewExp(pchar, "Sailors", 100);
			ChangeCrewExp(pchar, "Cannoners", 100);
			ChangeCrewExp(pchar, "Soldiers", 100);
			SetCharacterGoods(pchar, GOOD_BALLS, 400);
			SetCharacterGoods(pchar, GOOD_GRAPES, 400);
			SetCharacterGoods(pchar, GOOD_KNIPPELS, 400);
			SetCharacterGoods(pchar, GOOD_BOMBS, 500);
			SetCharacterGoods(pchar, GOOD_FOOD, 3000);
			SetCharacterGoods(pchar, GOOD_POWDER, 2000);
			SetCharacterGoods(pchar, GOOD_WEAPON, 500);
			SetCharacterGoods(pchar, GOOD_MEDICAMENT, 500);
			SetCharacterGoods(pchar, GOOD_RUM, 500);
			setCharacterShipLocation(pchar, "Shore35");
			setWDMPointXZ("Shore35");
			// Томми
			sld = GetCharacter(NPC_GenerateCharacter("Irons", "Irons", "man", "Irons", 12, ENGLAND, -1, false, "quest"));
			sld.name = StringFromKey("BlackMark_5");
			sld.lastname = StringFromKey("BlackMark_6");
			sld.rank = 12;
			sld.CanTakeMushket = true;
			sld.PriorityMode = 2;
			sld.MusketerDistance = 10;
			SetSPECIAL(sld, 6, 9, 6, 3, 7, 6, 9);
			SetSelfSkill(sld, 15, 15, 50, 60, 20);
			SetShipSkill(sld, 5, 1, 4, 6, 1, 1, 7, 1, 10);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "Jager"); //Егерь
			SetCharacterPerk(sld, "Sniper"); //Снайпер
			GiveItem2Character(sld, "cirass10");
			EquipCharacterByItem(sld, "cirass10");
			GiveItem2Character(sld, "blade_42");
			EquipCharacterByItem(sld, "blade_42");
			GiveItem2Character(sld, "indian_2");
			GiveItem2Character(sld, "mushket1");
			EquipCharacterByItem(sld, "mushket1");
			AddItems(sld, "potionrum", 5);
			AddItems(sld, "GunPowder", 15);
			AddItems(sld, "bullet", 15);
			LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "bullet");
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			sld.quest.OfficerPrice = 15000;
			sld.OfficerWantToGo.DontGo = true;
			sld.CompanionDisable = true;
			sld.loyality = MAX_LOYALITY;
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0; 
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			sld.CanTakeMushket = true;
			LAi_SetOfficerType(sld);
			sld.dialog.filename = "Quest\BlackMark.c";
			sld.Dialog.CurrentNode = "Irons_officer";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(sld, "HiredDate");
			LAi_SetHP(sld, 170.0, 170.0);
			// Тичингиту
			sld = GetCharacter(NPC_GenerateCharacter("Tichingitu", "maskog", "man", "man", 20, FRANCE, -1, false, "quest"));
			sld.name = "Тичингиту";
			sld.lastname = "";
			sld.greeting = "Tichingitu";
			sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			sld.dialog.currentnode = "Tichingitu";
			sld.rank = 20;
			LAi_SetHP(sld, 200.0, 200.0);
			SetSPECIAL(sld, 4, 9, 5, 5, 10, 8, 8);
			SetSelfSkill(sld, 50, 50, 50, 70, 50);
			SetShipSkill(sld, 30, 30, 30, 30, 50, 30, 50, 50, 30);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			AddItems(sld, "mushket1", 1);
			sld.CanTakeMushket = true;
			GiveItem2Character(sld, "blade_10");
			sld.equip.blade = "blade_10";
			GiveItem2Character(sld, "pistol1");
			sld.equip.gun = "pistol1";
			GiveItem2Character(sld, "cirass1");
			EquipCharacterbyItem(sld, "cirass1");
			AddItems(sld, "cartridge", 50);
			sld.quest.OfficerPrice = sti(pchar.rank) * 20;
			sld.OfficerWantToGo.DontGo = true;
			sld.CompanionDisable = true;
			sld.loyality = MAX_LOYALITY;
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			LAi_SetOfficerType(sld);
			sld.dialog.currentnode = "Tichingitu_officer";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(sld, "HiredDate");
			AddItems(sld, "potion2", 10);
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0; 
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			// Дюран
			sld = GetCharacter(NPC_GenerateCharacter("Duran", "Claude_Durand", "man", "man", 15, FRANCE, -1, false, "soldier"));
			sld.name = StringFromKey("FMQ_49");
			sld.lastname = StringFromKey("FMQ_50");
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.Dialog.CurrentNode = "hired";
			sld.rank = 15;
			sld.reputation = 25;
			LAi_SetHP(sld, 180, 180);
			SetSelfSkill(sld, 45, 50, 45, 45, 35);
			SetShipSkill(sld, 25, 10, 20, 20, 20, 20, 20, 20, 30);
			SetSPECIAL(sld, 8, 5, 8, 4, 6, 8, 5);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "Tireless");
			sld.SuperShooter = true;
			sld.quest.OfficerPrice = sti(pchar.rank) * 20;
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			EquipCharacterByArtefact(sld, "indian_1");
			EquipCharacterByArtefact(sld, "indian_7");
			EquipCharacterByArtefact(sld, "indian_4");
			GiveItem2Character(sld, "blade_12");
			sld.equip.blade = "blade_12";
			GiveItem2Character(sld, "pistol1");
			EquipCharacterbyItem(sld, "pistol1");
			LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
			TakeNItems(sld, "bullet", 20);
			AddItems(sld, "gunpowder", 20);
			sld.greeting = "Duran_officer";
			LAi_SetOfficerType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0; 
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			
			//Телепорт
			pchar.questTemp.LadyBeth_StrongGroup = true;
			setCharacterShipLocation(pchar, "Shore17");
			DoFunctionReloadToLocation("Shore17", "reload", "sea", "LadyBeth_CaimanBuhta_3");
			//выключить сторонние квесты
			PChar.quest.Red_Chieftain.over = "yes";
			PChar.quest.False_Trace.over = "yes";
			PChar.quest.FalseTrace_Prepare.over = "yes";
			//Остальное
			locations[FindLocation("Caiman_Jungle_01")].DisableEncounters = true;
			locations[FindLocation("Shore16")].DisableEncounters = true;
			locations[FindLocation("Shore17")].DisableEncounters = true;
		break;
		
		case "LadyBeth_Test_Start_Caiman":
			DialogExit();
			LAi_SetPlayerType(pchar);
			InterfaceStates.Buttons.Save.enable = true;
			bGameMenuStart = false;
			RemoveAllCharacterItems(pchar, true);
			AddMoneyToCharacter(pchar, 10000000);
			pchar.rank = 8;
			AddCharacterExpToSkill(pchar, "Sailing", 50000);
			pchar.skill.FreeSPECIAL = sti(pchar.skill.FreeSPECIAL) + 25;
			pchar.Skill.FreeSkill = sti(pchar.Skill.FreeSkill) + 1000;
			pchar.perks.FreePoints_self = sti(pchar.perks.FreePoints_self) + 30;
			pchar.perks.FreePoints_ship = sti(pchar.perks.FreePoints_ship) + 30;
			GiveItem2Character(PChar, "blade_16");
			GiveItem2Character(PChar, "blade_13");
			EquipCharacterByItem(Pchar, "blade_13");
			GiveItem2Character(PChar, "pistol5");
			EquipCharacterByItem(Pchar, "pistol5");
			GiveItem2Character(PChar, "cirass8");
			GiveItem2Character(PChar, "cirass1");
			EquipCharacterByItem(Pchar, "cirass1");
			GiveItem2Character(PChar, "spyglass4");
			EquipCharacterByItem(Pchar, "spyglass4");
			GiveItem2Character(PChar, "talisman2");
			GiveItem2Character(PChar, "talisman13");
			EquipCharacterByItem(Pchar, "talisman13");
			GiveItem2Character(PChar, "mushket3");
			GiveItem2Character(PChar, "mushket5");
			GiveItem2Character(PChar, "mushket8");
			AddItems(Pchar, "cartridge", 50);
			AddItems(Pchar, "grapeshot", 50);
			AddItems(Pchar, "GunPowder", 50);
			AddItems(Pchar, "potion4", 20);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "cartridge");
			AddItems(pchar, "gold_dublon", 500);
			// Мой корабль
			pchar.Ship.Type = GenerateShipExt(SHIP_PINK, true, pchar);
			pchar.Ship.name = "Принципио";
			SetSailsColor(pchar, 0); //белый хлопковый парус
			SetBaseShipData(pchar);
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS6;
			SetCrewQuantityFull(pchar);
			pchar.Ship.Crew.Morale = 100;
			pchar.Ship.Crew.Exp.Sailors = 100;
			pchar.Ship.Crew.Exp.Cannoners = 100;
			pchar.Ship.Crew.Exp.Soldiers = 100;
			UpgradeShipParameter(pchar, "SpeedRate"); //апгрейдить скорость
			UpgradeShipParameter(pchar, "TurnRate");  //маневренность
			UpgradeShipParameter(pchar, "HP");        //корпус
			ChangeCrewExp(pchar, "Sailors", 100);
			ChangeCrewExp(pchar, "Cannoners", 100);
			ChangeCrewExp(pchar, "Soldiers", 100);
			SetCharacterGoods(pchar, GOOD_BALLS, 400);
			SetCharacterGoods(pchar, GOOD_GRAPES, 400);
			SetCharacterGoods(pchar, GOOD_KNIPPELS, 400);
			SetCharacterGoods(pchar, GOOD_BOMBS, 500);
			SetCharacterGoods(pchar, GOOD_FOOD, 3000);
			SetCharacterGoods(pchar, GOOD_POWDER, 2000);
			SetCharacterGoods(pchar, GOOD_WEAPON, 500);
			SetCharacterGoods(pchar, GOOD_MEDICAMENT, 500);
			SetCharacterGoods(pchar, GOOD_RUM, 500);
			setCharacterShipLocation(pchar, "Shore35");
			setWDMPointXZ("Shore35");
			// Томми
			sld = GetCharacter(NPC_GenerateCharacter("Irons", "Irons", "man", "Irons", 12, ENGLAND, -1, false, "quest"));
			sld.name = StringFromKey("BlackMark_5");
			sld.lastname = StringFromKey("BlackMark_6");
			sld.rank = 12;
			sld.CanTakeMushket = true;
			sld.PriorityMode = 2;
			sld.MusketerDistance = 10;
			SetSPECIAL(sld, 6, 9, 6, 3, 7, 6, 9);
			SetSelfSkill(sld, 15, 15, 50, 60, 20);
			SetShipSkill(sld, 5, 1, 4, 6, 1, 1, 7, 1, 10);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "Jager"); //Егерь
			SetCharacterPerk(sld, "Sniper"); //Снайпер
			GiveItem2Character(sld, "cirass10");
			EquipCharacterByItem(sld, "cirass10");
			GiveItem2Character(sld, "blade_42");
			EquipCharacterByItem(sld, "blade_42");
			GiveItem2Character(sld, "indian_2");
			GiveItem2Character(sld, "mushket1");
			EquipCharacterByItem(sld, "mushket1");
			AddItems(sld, "potionrum", 5);
			AddItems(sld, "GunPowder", 15);
			AddItems(sld, "bullet", 15);
			LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "bullet");
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			sld.quest.OfficerPrice = 15000;
			sld.OfficerWantToGo.DontGo = true;
			sld.CompanionDisable = true;
			sld.loyality = MAX_LOYALITY;
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0; 
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			sld.CanTakeMushket = true;
			LAi_SetOfficerType(sld);
			sld.dialog.filename = "Quest\BlackMark.c";
			sld.Dialog.CurrentNode = "Irons_officer";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(sld, "HiredDate");
			LAi_SetHP(sld, 170.0, 170.0);
			// Тичингиту
			sld = GetCharacter(NPC_GenerateCharacter("Tichingitu", "maskog", "man", "man", 20, FRANCE, -1, false, "quest"));
			sld.name = "Тичингиту";
			sld.lastname = "";
			sld.greeting = "Tichingitu";
			sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			sld.dialog.currentnode = "Tichingitu";
			sld.rank = 20;
			LAi_SetHP(sld, 200.0, 200.0);
			SetSPECIAL(sld, 4, 9, 5, 5, 10, 8, 8);
			SetSelfSkill(sld, 50, 50, 50, 70, 50);
			SetShipSkill(sld, 30, 30, 30, 30, 50, 30, 50, 50, 30);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			AddItems(sld, "mushket1", 1);
			sld.CanTakeMushket = true;
			GiveItem2Character(sld, "blade_10");
			sld.equip.blade = "blade_10";
			GiveItem2Character(sld, "pistol1");
			sld.equip.gun = "pistol1";
			GiveItem2Character(sld, "cirass1");
			EquipCharacterbyItem(sld, "cirass1");
			AddItems(sld, "cartridge", 50);
			sld.quest.OfficerPrice = sti(pchar.rank) * 20;
			sld.OfficerWantToGo.DontGo = true;
			sld.CompanionDisable = true;
			sld.loyality = MAX_LOYALITY;
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			LAi_SetOfficerType(sld);
			sld.dialog.currentnode = "Tichingitu_officer";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(sld, "HiredDate");
			AddItems(sld, "potion2", 10);
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0; 
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			// Дюран
			sld = GetCharacter(NPC_GenerateCharacter("Duran", "Claude_Durand", "man", "man", 15, FRANCE, -1, false, "soldier"));
			sld.name = StringFromKey("FMQ_49");
			sld.lastname = StringFromKey("FMQ_50");
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.Dialog.CurrentNode = "hired";
			sld.rank = 15;
			sld.reputation = 25;
			LAi_SetHP(sld, 180, 180);
			SetSelfSkill(sld, 45, 50, 45, 45, 35);
			SetShipSkill(sld, 25, 10, 20, 20, 20, 20, 20, 20, 30);
			SetSPECIAL(sld, 8, 5, 8, 4, 6, 8, 5);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "Tireless");
			sld.SuperShooter = true;
			sld.quest.OfficerPrice = sti(pchar.rank) * 20;
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			EquipCharacterByArtefact(sld, "indian_1");
			EquipCharacterByArtefact(sld, "indian_7");
			EquipCharacterByArtefact(sld, "indian_4");
			GiveItem2Character(sld, "blade_12");
			sld.equip.blade = "blade_12";
			GiveItem2Character(sld, "pistol1");
			EquipCharacterbyItem(sld, "pistol1");
			LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
			TakeNItems(sld, "bullet", 20);
			AddItems(sld, "gunpowder", 20);
			sld.greeting = "Duran_officer";
			LAi_SetOfficerType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0; 
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			
			//Телепорт
			DoQuestReloadToLocation("Shore35", "reload", "reload1", "");
			//выключить сторонние квесты
			PChar.quest.Red_Chieftain.over = "yes";
			PChar.quest.False_Trace.over = "yes";
			PChar.quest.FalseTrace_Prepare.over = "yes";
			//Остальное
			SetFunctionLocationCondition("LadyBeth_CaimanSea", "Caiman", false);
		break;
		
		
		case "PZ_Test_Start_1":
			dialog.text = "Откуда начнём?";
			link.l0     = "Эпизод 0. ПРОЛОГ. (c самого начала)";
			link.l0.go  = "PZ_Test_Start_S_samogo_nachala";
			link.l1     = "Эпизод 1. ВЕРНЫЙ КЛЯТВЕ.";
			link.l1.go  = "PZ_Test_Start_BasTer";
			link.l2     = "Эпизод 2-3. СТРАНИЦЫ ИСТОРИИ.";
			link.l2.go  = "PZ_Test_Start_Formosa";
			link.l4     = "Эпизод 4. ОБМАНЧИВАЯ ЗВЕЗДА.";
			link.l4.go  = "PZ_Test_Start_Etap4";
			link.l51     = "Эпизод 5-6. ПАДАЮЩАЯ ЗВЕЗДА. (С Элен)";
			link.l51.go  = "PZ_Test_Start_Etap5_Helena";
			link.l52     = "Эпизод 5-6. ПАДАЮЩАЯ ЗВЕЗДА. (С Мэри)";
			link.l52.go  = "PZ_Test_Start_Etap5_Mary";
			/*link.l61     = "Эпизод 6. ПОГАСШАЯ ЗВЕЗДА. (С Элен)";
			link.l61.go  = "PZ_Test_Start_Etap6_Helena";
			link.l62     = "Эпизод 6. ПОГАСШАЯ ЗВЕЗДА. (С Мэри)";
			link.l62.go  = "PZ_Test_Start_Etap6_Mary";*/
		break;
		
		case "PZ_Test_Start_Etap5_Helena":
			DialogExit();
			LAi_SetPlayerType(pchar);
			InterfaceStates.Buttons.Save.enable = true;
			bGameMenuStart = false;
			RemoveAllCharacterItems(pchar, true);
			AddMoneyToCharacter(pchar, 10000000);
			pchar.rank = 35;
			LAi_SetHP(pchar, 400.0, 400.0);
			SetSPECIAL(PChar, 10, 10, 10, 10, 10, 10, 10);
			SetSelfSkill(PChar, 50, 50, 50, 50, 50);
			SetShipSkill(PChar, 50, 75, 50, 50, 100, 50, 50, 50, 75);
			LAi_SetHP(pchar, 400.0, 400.0);
			SetCharacterPerk(pchar, "BasicDefense");
			SetCharacterPerk(pchar, "AdvancedDefense");
			SetCharacterPerk(pchar, "Ciras");
			SetCharacterPerk(pchar, "SwordplayProfessional");
			SetCharacterPerk(pchar, "CriticalHit");
			SetCharacterPerk(pchar, "AgileMan");
			SetCharacterPerk(pchar, "BladeDancer");
			SetCharacterPerk(pchar, "Sliding");
			SetCharacterPerk(pchar, "HardHitter");
			SetCharacterPerk(pchar, "EnergyPlus");
			SetCharacterPerk(pchar, "Medic");
			SetCharacterPerk(pchar, "Gunman");
			SetCharacterPerk(pchar, "GunProfessional");
			SetCharacterPerk(pchar, "Tireless");
			SetCharacterPerk(pchar, "IronWill");
			SetCharacterPerk(pchar, "CrewDamageUp");
			SetCharacterPerk(pchar, "CriticalShoot");
			SetCharacterPerk(pchar, "LongRangeShoot");
			SetCharacterPerk(pchar, "CannonProfessional");
			SetCharacterPerk(pchar, "LongRangeGrappling");
			SetCharacterPerk(pchar, "MusketsShoot");
			SetCharacterPerk(pchar, "GrapplingProfessional");
			SetCharacterPerk(pchar, "ShipDefenseProfessional");
			SetCharacterPerk(pchar, "ShipSpeedUp");
			SetCharacterPerk(pchar, "ShipTurnRateUp");
			SetCharacterPerk(pchar, "BasicBattleState");
			SetCharacterPerk(pchar, "AdvancedBattleState");
			SetCharacterPerk(pchar, "ShipDefenseProfessional");
			SetCharacterPerk(pchar, "StormProfessional");
			SetCharacterPerk(pchar, "SailingProfessional");
			SetCharacterPerk(pchar, "SailsMan");
			SetCharacterPerk(pchar, "WindCatcher");
			SetCharacterPerk(pchar, "SeaDogProfessional");
			SetCharacterPerk(pchar, "Trustworthy");
			GiveItem2Character(PChar, "blade_16");
			GiveItem2Character(PChar, "blade_13");
			EquipCharacterByItem(Pchar, "blade_13");
			GiveItem2Character(PChar, "pistol5");
			EquipCharacterByItem(Pchar, "pistol5");
			GiveItem2Character(PChar, "cirass8");
			EquipCharacterByItem(Pchar, "cirass8");
			GiveItem2Character(PChar, "spyglass4");
			EquipCharacterByItem(Pchar, "spyglass4");
			GiveItem2Character(PChar, "talisman2");
			EquipCharacterByItem(Pchar, "talisman2");
			GiveItem2Character(PChar, "talisman13");
			AddItems(Pchar, "cartridge", 50);
			AddItems(Pchar, "potion4", 20);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "cartridge");
			AddItems(pchar, "gold_dublon", 500);
			// Мой корабль
			pchar.Ship.Type = GenerateShipExt(SHIP_LINESHIP, true, pchar);
			pchar.Ship.name = "Авентура";
			SetSailsColor(pchar, 0); //белый хлопковый парус
			SetBaseShipData(pchar);
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS24;
			SetCrewQuantityFull(pchar);
			pchar.Ship.Crew.Morale = 100;
			pchar.Ship.Crew.Exp.Sailors = 100;
			pchar.Ship.Crew.Exp.Cannoners = 100;
			pchar.Ship.Crew.Exp.Soldiers = 100;
			UpgradeShipParameter(pchar, "SpeedRate"); //апгрейдить скорость
			UpgradeShipParameter(pchar, "TurnRate");  //маневренность
			UpgradeShipParameter(pchar, "HP");        //корпус
			ChangeCrewExp(pchar, "Sailors", 100);
			ChangeCrewExp(pchar, "Cannoners", 100);
			ChangeCrewExp(pchar, "Soldiers", 100);
			SetCharacterGoods(pchar, GOOD_BALLS, 2000);
			SetCharacterGoods(pchar, GOOD_GRAPES, 700);
			SetCharacterGoods(pchar, GOOD_KNIPPELS, 600);
			SetCharacterGoods(pchar, GOOD_BOMBS, 2000);
			SetCharacterGoods(pchar, GOOD_FOOD, 2000);
			SetCharacterGoods(pchar, GOOD_POWDER, 5000);
			SetCharacterGoods(pchar, GOOD_WEAPON, 750);
			SetCharacterGoods(pchar, GOOD_MEDICAMENT, 900);
			SetCharacterGoods(pchar, GOOD_RUM, 800);
			setCharacterShipLocation(pchar, "Pirates_town");
			setWDMPointXZ("Pirates_town");
			//Лонгвэй
			sld = GetCharacter(NPC_GenerateCharacter("Longway", "Longway", "man", "Longway", 20, HOLLAND, -1, false, "quest"));
			sld.name = "Лонгвэй";
			sld.lastname = "";
			sld.greeting = "Longway";
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.dialog.currentnode = "Longway_officer";
			sld.CompanionDisable = true;
			sld.rank = 20;
			sld.money = 5000;
			SetSelfSkill(sld, 45, 45, 45, 40, 50);
			SetShipSkill(sld, 50, 20, 25, 25, 65, 20, 20, 50, 15);
			SetSPECIAL(sld, 8, 9, 6, 5, 10, 7, 5);
			LAi_SetHP(sld, 250, 250);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "StormProfessional");
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "SailingProfessional");
			GiveItem2Character(sld, "blade_08");
			sld.equip.blade = "blade_08";
			GiveItem2Character(sld, "pistol3");
			EquipCharacterbyItem(sld, "pistol3");
			LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "grapeshot");
			TakeNItems(sld, "grapeshot", 50);
			AddItems(sld, "gunpowder", 50);
			TakeNItems(sld, "potion2", 1);
			//
			sld.quest.OfficerPrice = sti(pchar.rank)*200;
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0; 
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			LAi_SetOfficerType(sld);
			sld.greeting = "Longway";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			// Тичингиту
			sld = GetCharacter(NPC_GenerateCharacter("Tichingitu", "maskog", "man", "man", 5, FRANCE, -1, false, "quest"));
			sld.name = "Тичингиту";
			sld.lastname = "";
			sld.greeting = "Tichingitu";
			sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			sld.dialog.currentnode = "Tichingitu";
			sld.rank = 20;
			LAi_SetHP(sld, 200.0, 200.0);
			SetSPECIAL(sld, 4, 9, 5, 5, 10, 8, 8);
			SetSelfSkill(sld, 50, 50, 50, 70, 50);
			SetShipSkill(sld, 30, 30, 30, 30, 50, 30, 50, 50, 30);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			AddItems(sld, "mushket1", 1);
			sld.CanTakeMushket = true;
			GiveItem2Character(sld, "blade_10");
			sld.equip.blade = "blade_10";
			GiveItem2Character(sld, "pistol1");
			sld.equip.gun = "pistol1";
			GiveItem2Character(sld, "cirass1");
			EquipCharacterbyItem(sld, "cirass1");
			AddItems(sld, "cartridge", 50);
			sld.quest.OfficerPrice = sti(pchar.rank) * 20;
			sld.OfficerWantToGo.DontGo = true;
			sld.CompanionDisable = true;
			sld.loyality = MAX_LOYALITY;
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			LAi_SetOfficerType(sld);
			sld.dialog.currentnode = "Tichingitu_officer";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(sld, "HiredDate");
			AddItems(sld, "potion2", 10);
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0; 
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			// Элен:
			pchar.questTemp.Saga.Helena_officer = "true";
			sld = characterFromId("Helena");
			sld.greeting = "helena_hire";
			sld.quest.OfficerPrice = sti(pchar.rank) * 500;
			sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
			sld.loyality = MAX_LOYALITY;
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			sld.DontClearDead = true;
			sld.dialog.currentnode = "Helena_officer";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(sld, "HiredDate");
			sld.rank = 35;
			LAi_SetHP(sld, 500.0, 500.0);
			SetSelfSkill(sld, 100, 90, 100, 100, 90);
			SetShipSkill(sld, 100, 40, 40, 40, 40, 40, 40, 40, 40);
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "ByWorker");
			SetCharacterPerk(sld, "ByWorker2");
			SetCharacterPerk(sld, "Grus");
			GiveItem2Character(sld, "pirate_cutlass");
			sld.equip.blade = "pirate_cutlass";
			GiveItem2Character(sld, "pistol4");
			sld.equip.gun = "pistol4";
			GiveItem2Character(sld, "cirass4");
			EquipCharacterbyItem(sld, "cirass4");
			AddItems(sld, "cartridge", 50);
			LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "cartridge");
			AddItems(sld, "potion2", 10);
			AddItems(sld, "potion4", 5);
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			LAi_SetImmortal(sld, false);
			// Бейкер
			sld = GetCharacter(NPC_GenerateCharacter("Baker", "Baker", "man", "man_B", 1, ENGLAND, -1, false, "quest"));
			sld.name = "Раймонд";
			sld.lastname = "Бейкер";
			sld.greeting = "baker";
			sld.Dialog.Filename = "Quest\Saga\Baker.c";
			sld.dialog.currentnode = "Baker_officer";
			sld.rank = 28;
			LAi_SetHP(sld, 150, 150); 
			SetSelfSkill(sld, 20, 20, 70, 20, 40);
			SetShipSkill(sld, 20, 40, 10, 10, 15, 5, 8, 95, 50);
			SetSPECIAL(sld, 6, 6, 7, 6, 9, 6, 5);
			SetCharacterPerk(sld, "Doctor1");
			SetCharacterPerk(sld, "Doctor2");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "BasicCommerce");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Gunman");
			GiveItem2Character(sld, "blade_11");
			sld.equip.blade = "blade_11";
			GiveItem2Character(sld, "pistol1");
			EquipCharacterbyItem(sld, "pistol1");
			LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
			TakeNItems(sld, "bullet", 20);
			AddItems(sld, "gunpowder", 20);
			sld.quest.OfficerPrice = sti(pchar.rank)*500;
			sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
			sld.CompanionDisable = true; //нельзя в компаньоны
			sld.loyality = MAX_LOYALITY;
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			sld.DontClearDead = true;
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(sld, "HiredDate");
			
			//Телепорт
			DoQuestReloadToLocation("Pirates_town", "reload", "reload1", "PZ_Etap5_Start");
			//выключить сторонние квесты
			PChar.quest.Red_Chieftain.over = "yes";
			PChar.quest.False_Trace.over = "yes";
			PChar.quest.FalseTrace_Prepare.over = "yes";
			//Остальное
			sld = characterFromID("Charles_Priest");
			sld.name = "Жорж";
			sld.lastname = "Гравель";
		break;
		
		case "PZ_Test_Start_Etap5_Mary":
			DialogExit();
			LAi_SetPlayerType(pchar);
			InterfaceStates.Buttons.Save.enable = true;
			bGameMenuStart = false;
			RemoveAllCharacterItems(pchar, true);
			AddMoneyToCharacter(pchar, 10000000);
			pchar.rank = 35;
			LAi_SetHP(pchar, 400.0, 400.0);
			SetSPECIAL(PChar, 10, 10, 10, 10, 10, 10, 10);
			SetSelfSkill(PChar, 50, 50, 50, 50, 50);
			SetShipSkill(PChar, 50, 75, 50, 50, 100, 50, 50, 50, 75);
			LAi_SetHP(pchar, 400.0, 400.0);
			SetCharacterPerk(pchar, "BasicDefense");
			SetCharacterPerk(pchar, "AdvancedDefense");
			SetCharacterPerk(pchar, "Ciras");
			SetCharacterPerk(pchar, "SwordplayProfessional");
			SetCharacterPerk(pchar, "CriticalHit");
			SetCharacterPerk(pchar, "AgileMan");
			SetCharacterPerk(pchar, "BladeDancer");
			SetCharacterPerk(pchar, "Sliding");
			SetCharacterPerk(pchar, "HardHitter");
			SetCharacterPerk(pchar, "EnergyPlus");
			SetCharacterPerk(pchar, "Medic");
			SetCharacterPerk(pchar, "Gunman");
			SetCharacterPerk(pchar, "GunProfessional");
			SetCharacterPerk(pchar, "Tireless");
			SetCharacterPerk(pchar, "IronWill");
			SetCharacterPerk(pchar, "CrewDamageUp");
			SetCharacterPerk(pchar, "CriticalShoot");
			SetCharacterPerk(pchar, "LongRangeShoot");
			SetCharacterPerk(pchar, "CannonProfessional");
			SetCharacterPerk(pchar, "LongRangeGrappling");
			SetCharacterPerk(pchar, "MusketsShoot");
			SetCharacterPerk(pchar, "GrapplingProfessional");
			SetCharacterPerk(pchar, "ShipDefenseProfessional");
			SetCharacterPerk(pchar, "ShipSpeedUp");
			SetCharacterPerk(pchar, "ShipTurnRateUp");
			SetCharacterPerk(pchar, "BasicBattleState");
			SetCharacterPerk(pchar, "AdvancedBattleState");
			SetCharacterPerk(pchar, "ShipDefenseProfessional");
			SetCharacterPerk(pchar, "StormProfessional");
			SetCharacterPerk(pchar, "SailingProfessional");
			SetCharacterPerk(pchar, "SailsMan");
			SetCharacterPerk(pchar, "WindCatcher");
			SetCharacterPerk(pchar, "SeaDogProfessional");
			SetCharacterPerk(pchar, "Trustworthy");
			GiveItem2Character(PChar, "blade_16");
			GiveItem2Character(PChar, "blade_13");
			EquipCharacterByItem(Pchar, "blade_13");
			GiveItem2Character(PChar, "pistol5");
			EquipCharacterByItem(Pchar, "pistol5");
			GiveItem2Character(PChar, "cirass8");
			EquipCharacterByItem(Pchar, "cirass8");
			GiveItem2Character(PChar, "spyglass4");
			EquipCharacterByItem(Pchar, "spyglass4");
			GiveItem2Character(PChar, "talisman2");
			EquipCharacterByItem(Pchar, "talisman2");
			GiveItem2Character(PChar, "talisman13");
			AddItems(Pchar, "cartridge", 50);
			AddItems(Pchar, "potion4", 20);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "cartridge");
			AddItems(pchar, "gold_dublon", 500);
			// Мой корабль
			pchar.Ship.Type = GenerateShipExt(SHIP_LINESHIP, true, pchar);
			pchar.Ship.name = "Авентура";
			SetSailsColor(pchar, 0); //белый хлопковый парус
			SetBaseShipData(pchar);
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS24;
			SetCrewQuantityFull(pchar);
			pchar.Ship.Crew.Morale = 100;
			pchar.Ship.Crew.Exp.Sailors = 100;
			pchar.Ship.Crew.Exp.Cannoners = 100;
			pchar.Ship.Crew.Exp.Soldiers = 100;
			UpgradeShipParameter(pchar, "SpeedRate"); //апгрейдить скорость
			UpgradeShipParameter(pchar, "TurnRate");  //маневренность
			UpgradeShipParameter(pchar, "HP");        //корпус
			ChangeCrewExp(pchar, "Sailors", 100);
			ChangeCrewExp(pchar, "Cannoners", 100);
			ChangeCrewExp(pchar, "Soldiers", 100);
			SetCharacterGoods(pchar, GOOD_BALLS, 2000);
			SetCharacterGoods(pchar, GOOD_GRAPES, 700);
			SetCharacterGoods(pchar, GOOD_KNIPPELS, 600);
			SetCharacterGoods(pchar, GOOD_BOMBS, 2000);
			SetCharacterGoods(pchar, GOOD_FOOD, 2000);
			SetCharacterGoods(pchar, GOOD_POWDER, 5000);
			SetCharacterGoods(pchar, GOOD_WEAPON, 750);
			SetCharacterGoods(pchar, GOOD_MEDICAMENT, 900);
			SetCharacterGoods(pchar, GOOD_RUM, 800);
			setCharacterShipLocation(pchar, "Pirates_town");
			setWDMPointXZ("Pirates_town");
			//Лонгвэй
			sld = GetCharacter(NPC_GenerateCharacter("Longway", "Longway", "man", "Longway", 20, HOLLAND, -1, false, "quest"));
			sld.name = "Лонгвэй";
			sld.lastname = "";
			sld.greeting = "Longway";
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.dialog.currentnode = "Longway_officer";
			sld.CompanionDisable = true;
			sld.rank = 20;
			sld.money = 5000;
			SetSelfSkill(sld, 45, 45, 45, 40, 50);
			SetShipSkill(sld, 50, 20, 25, 25, 65, 20, 20, 50, 15);
			SetSPECIAL(sld, 8, 9, 6, 5, 10, 7, 5);
			LAi_SetHP(sld, 250, 250);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "StormProfessional");
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "SailingProfessional");
			GiveItem2Character(sld, "blade_08");
			sld.equip.blade = "blade_08";
			GiveItem2Character(sld, "pistol3");
			EquipCharacterbyItem(sld, "pistol3");
			LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "grapeshot");
			TakeNItems(sld, "grapeshot", 50);
			AddItems(sld, "gunpowder", 50);
			TakeNItems(sld, "potion2", 1);
			//
			sld.quest.OfficerPrice = sti(pchar.rank)*200;
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0; 
			sld.Health.maxHP    = 60.0;
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			LAi_SetOfficerType(sld);
			sld.greeting = "Longway";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			// Тичингиту
			sld = GetCharacter(NPC_GenerateCharacter("Tichingitu", "maskog", "man", "man", 5, FRANCE, -1, false, "quest"));
			sld.name = "Тичингиту";
			sld.lastname = "";
			sld.greeting = "Tichingitu";
			sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			sld.dialog.currentnode = "Tichingitu";
			sld.rank = 20;
			LAi_SetHP(sld, 200.0, 200.0);
			SetSPECIAL(sld, 4, 9, 5, 5, 10, 8, 8);
			SetSelfSkill(sld, 50, 50, 50, 70, 50);
			SetShipSkill(sld, 30, 30, 30, 30, 50, 30, 50, 50, 30);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			AddItems(sld, "mushket1", 1);
			sld.CanTakeMushket = true;
			GiveItem2Character(sld, "blade_10");
			sld.equip.blade = "blade_10";
			GiveItem2Character(sld, "pistol1");
			sld.equip.gun = "pistol1";
			GiveItem2Character(sld, "cirass1");
			EquipCharacterbyItem(sld, "cirass1");
			AddItems(sld, "cartridge", 50);
			sld.quest.OfficerPrice = sti(pchar.rank) * 20;
			sld.OfficerWantToGo.DontGo = true;
			sld.CompanionDisable = true;
			sld.loyality = MAX_LOYALITY;
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			LAi_SetOfficerType(sld);
			sld.dialog.currentnode = "Tichingitu_officer";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(sld, "HiredDate");
			AddItems(sld, "potion2", 10);
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0; 
			sld.Health.maxHP    = 60.0;
			// Мэри:
			pchar.questTemp.LSC.Mary_officer = "true";
			sld = characterFromId("Mary");
			sld.quest.OfficerPrice = sti(pchar.rank) * 500;
			sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
			sld.CompanionDisable = true;       //нельзя в компаньоны
			sld.loyality = MAX_LOYALITY;
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			sld.DontClearDead = true;
			sld.dialog.currentnode = "Mary_officer";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(sld, "HiredDate");
			sld.rank = 35;
			LAi_SetHP(sld, 500.0, 500.0);
			SetSelfSkill(sld, 100, 90, 100, 100, 90);
			SetShipSkill(sld, 100, 40, 40, 40, 40, 40, 40, 40, 40);
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "ByWorker");
			SetCharacterPerk(sld, "ByWorker2");
			SetCharacterPerk(sld, "Grus");
			GiveItem2Character(sld, "blade_31");
			sld.equip.blade = "blade_31";
			GiveItem2Character(sld, "pistol4");
			sld.equip.gun = "pistol4";
			GiveItem2Character(sld, "cirass4");
			EquipCharacterbyItem(sld, "cirass4");
			AddItems(sld, "cartridge", 50);
			LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "cartridge");
			AddItems(sld, "potion2", 10);
			AddItems(sld, "potion4", 5);
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			// Бейкер
			sld = GetCharacter(NPC_GenerateCharacter("Baker", "Baker", "man", "man_B", 1, ENGLAND, -1, false, "quest"));
			sld.name = "Раймонд";
			sld.lastname = "Бейкер";
			sld.greeting = "baker";
			sld.Dialog.Filename = "Quest\Saga\Baker.c";
			sld.dialog.currentnode = "Baker_officer";
			sld.rank = 28;
			LAi_SetHP(sld, 150, 150); 
			SetSelfSkill(sld, 20, 20, 70, 20, 40);
			SetShipSkill(sld, 20, 40, 10, 10, 15, 5, 8, 95, 50);
			SetSPECIAL(sld, 6, 6, 7, 6, 9, 6, 5);
			SetCharacterPerk(sld, "Doctor1");
			SetCharacterPerk(sld, "Doctor2");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "BasicCommerce");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Gunman");
			GiveItem2Character(sld, "blade_11");
			sld.equip.blade = "blade_11";
			GiveItem2Character(sld, "pistol1");
			EquipCharacterbyItem(sld, "pistol1");
			LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
			TakeNItems(sld, "bullet", 20);
			AddItems(sld, "gunpowder", 20);
			sld.quest.OfficerPrice = sti(pchar.rank)*500;
			sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
			sld.CompanionDisable = true; //нельзя в компаньоны
			sld.loyality = MAX_LOYALITY;
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			sld.DontClearDead = true;
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(sld, "HiredDate");
			
			//Телепорт
			DoQuestReloadToLocation("Pirates_town", "reload", "reload1", "PZ_Etap5_Start");
			//выключить сторонние квесты
			PChar.quest.Red_Chieftain.over = "yes";
			PChar.quest.False_Trace.over = "yes";
			PChar.quest.FalseTrace_Prepare.over = "yes";
			//Остальное
			sld = characterFromID("Charles_Priest");
			sld.name = "Жорж";
			sld.lastname = "Гравель";
		break;
		
		case "PZ_Test_Start_Etap4":
			DialogExit();
			LAi_SetPlayerType(pchar);
			InterfaceStates.Buttons.Save.enable = true;
			bGameMenuStart = false;
			locations[FindLocation("Shore9")].DisableEncounters = true;
			RemoveAllCharacterItems(pchar, true);
			AddMoneyToCharacter(pchar, 10000000);
			pchar.rank = 25;
			SetSPECIAL(PChar, 10, 10, 10, 10, 10, 10, 10);
			SetSelfSkill(PChar, 50, 50, 50, 50, 50);
			SetShipSkill(PChar, 50, 75, 50, 50, 100, 50, 50, 50, 75);
			SetCharacterPerk(pchar, "BasicDefense");
			SetCharacterPerk(pchar, "AdvancedDefense");
			SetCharacterPerk(pchar, "Ciras");
			SetCharacterPerk(pchar, "SwordplayProfessional");
			SetCharacterPerk(pchar, "CriticalHit");
			SetCharacterPerk(pchar, "AgileMan");
			SetCharacterPerk(pchar, "BladeDancer");
			SetCharacterPerk(pchar, "Sliding");
			SetCharacterPerk(pchar, "HardHitter");
			SetCharacterPerk(pchar, "EnergyPlus");
			SetCharacterPerk(pchar, "Medic");
			SetCharacterPerk(pchar, "Gunman");
			SetCharacterPerk(pchar, "GunProfessional");
			SetCharacterPerk(pchar, "Tireless");
			SetCharacterPerk(pchar, "IronWill");
			SetCharacterPerk(pchar, "CrewDamageUp");
			SetCharacterPerk(pchar, "CriticalShoot");
			SetCharacterPerk(pchar, "LongRangeShoot");
			SetCharacterPerk(pchar, "CannonProfessional");
			SetCharacterPerk(pchar, "LongRangeGrappling");
			SetCharacterPerk(pchar, "MusketsShoot");
			SetCharacterPerk(pchar, "GrapplingProfessional");
			SetCharacterPerk(pchar, "ShipDefenseProfessional");
			SetCharacterPerk(pchar, "ShipSpeedUp");
			SetCharacterPerk(pchar, "ShipTurnRateUp");
			SetCharacterPerk(pchar, "BasicBattleState");
			SetCharacterPerk(pchar, "AdvancedBattleState");
			SetCharacterPerk(pchar, "ShipDefenseProfessional");
			SetCharacterPerk(pchar, "StormProfessional");
			SetCharacterPerk(pchar, "SailingProfessional");
			SetCharacterPerk(pchar, "SailsMan");
			SetCharacterPerk(pchar, "WindCatcher");
			SetCharacterPerk(pchar, "SeaDogProfessional");
			SetCharacterPerk(pchar, "Trustworthy");
			GiveItem2Character(PChar, "blade_16");
			GiveItem2Character(PChar, "blade_13");
			EquipCharacterByItem(Pchar, "blade_13");
			GiveItem2Character(PChar, "pistol5");
			EquipCharacterByItem(Pchar, "pistol5");
			GiveItem2Character(PChar, "cirass8");
			EquipCharacterByItem(Pchar, "cirass8");
			GiveItem2Character(PChar, "spyglass4");
			EquipCharacterByItem(Pchar, "spyglass4");
			GiveItem2Character(PChar, "talisman2");
			EquipCharacterByItem(Pchar, "talisman2");
			GiveItem2Character(PChar, "talisman13");
			AddItems(Pchar, "cartridge", 50);
			AddItems(Pchar, "potion4", 20);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "cartridge");
			AddItems(pchar, "gold_dublon", 500);
			// Мой корабль
			pchar.Ship.Type = GenerateShipExt(SHIP_MAYFANG, true, pchar);
			pchar.Ship.name="Мейфенг";
			SetBaseShipData(pchar);
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS20;
			SetCrewQuantity(pchar, 170);
			pchar.ship.Crew.Morale = 100;
			ChangeCrewExp(pchar, "Sailors", 100);
			ChangeCrewExp(pchar, "Cannoners", 100);
			ChangeCrewExp(pchar, "Soldiers", 100);
			SetCharacterGoods(pchar, GOOD_BALLS, 300);
			SetCharacterGoods(pchar, GOOD_GRAPES, 800);
			SetCharacterGoods(pchar, GOOD_KNIPPELS, 800);
			SetCharacterGoods(pchar, GOOD_BOMBS, 300);
			SetCharacterGoods(pchar, GOOD_POWDER, 1500);
			SetCharacterGoods(pchar, GOOD_FOOD, 3000);
			SetCharacterGoods(pchar, GOOD_MEDICAMENT, 500);
			SetCharacterGoods(pchar, GOOD_WEAPON, 500);
			SetCharacterGoods(pchar, GOOD_RUM, 500);
			setCharacterShipLocation(pchar, "Shore9");
			setWDMPointXZ("Shore9");
			//Лонгвэй
			sld = GetCharacter(NPC_GenerateCharacter("Longway", "Longway", "man", "Longway", 20, HOLLAND, -1, false, "quest"));
			sld.name = "Лонгвэй";
			sld.lastname = "";
			sld.greeting = "Longway";
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.dialog.currentnode = "Longway_officer";
			sld.CompanionDisable = true;
			sld.rank = 20;
			sld.money = 5000;
			SetSelfSkill(sld, 45, 45, 45, 40, 50);
			SetShipSkill(sld, 50, 20, 25, 25, 65, 20, 20, 50, 15);
			SetSPECIAL(sld, 8, 9, 6, 5, 10, 7, 5);
			LAi_SetHP(sld, 250, 250);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "StormProfessional");
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "SailingProfessional");
			GiveItem2Character(sld, "blade_08");
			sld.equip.blade = "blade_08";
			GiveItem2Character(sld, "pistol3");
			EquipCharacterbyItem(sld, "pistol3");
			LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "grapeshot");
			TakeNItems(sld, "grapeshot", 50);
			AddItems(sld, "gunpowder", 50);
			TakeNItems(sld, "potion2", 1);
			//
			sld.quest.OfficerPrice = sti(pchar.rank)*200;
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0; 
			sld.Health.maxHP    = 60.0;
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			LAi_SetOfficerType(sld);
			sld.greeting = "Longway";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			// Тичингиту
			sld = GetCharacter(NPC_GenerateCharacter("Tichingitu", "maskog", "man", "man", 5, FRANCE, -1, false, "quest"));
			sld.name = "Тичингиту";
			sld.lastname = "";
			sld.greeting = "Tichingitu";
			sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			sld.dialog.currentnode = "Tichingitu";
			sld.rank = 20;
			LAi_SetHP(sld, 200.0, 200.0);
			SetSPECIAL(sld, 4, 9, 5, 5, 10, 8, 8);
			SetSelfSkill(sld, 50, 50, 50, 70, 50);
			SetShipSkill(sld, 30, 30, 30, 30, 50, 30, 50, 50, 30);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			AddItems(sld, "mushket1", 1);
			sld.CanTakeMushket = true;
			GiveItem2Character(sld, "blade_10");
			sld.equip.blade = "blade_10";
			GiveItem2Character(sld, "pistol1");
			sld.equip.gun = "pistol1";
			GiveItem2Character(sld, "cirass1");
			EquipCharacterbyItem(sld, "cirass1");
			AddItems(sld, "cartridge", 50);
			sld.quest.OfficerPrice = sti(pchar.rank) * 20;
			sld.OfficerWantToGo.DontGo = true;
			sld.CompanionDisable = true;
			sld.loyality = MAX_LOYALITY;
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			LAi_SetOfficerType(sld);
			sld.dialog.currentnode = "Tichingitu_officer";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(sld, "HiredDate");
			AddItems(sld, "potion2", 10);
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0; 
			sld.Health.maxHP    = 60.0;
			//Элен
			 sld = characterFromId("Helena");
			GiveItem2Character(sld, "pirate_cutlass");
			EquipCharacterbyItem(sld, "pirate_cutlass");
			LAi_SetImmortal(sld, false);
			sld.quest.OfficerPrice = sti(pchar.rank) * 500;
			sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
			DeleteAttribute(sld, "CompanionDisable");
			DeleteAttribute(sld, "HalfImmortal");
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			sld.CompanionDisable = true;       //нельзя в компаньоны - чтобы не утонула
			sld.HalfImmortal = true;           //чтобы не убили в сухопутном бою
			sld.loyality = MAX_LOYALITY;
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			sld.DontClearDead = true;
			sld.dialog.currentnode = "Helena_officer";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(sld, "HiredDate");
			pchar.questTemp.Saga.Helena_friend = "true"; // друг
			
			//Телепорт
			DoQuestReloadToLocation("Shore9", "reload", "reload1", "PZ_Etap4_Start");
			//выключить сторонние квесты
			PChar.quest.Red_Chieftain.over = "yes";
			PChar.quest.False_Trace.over = "yes";
			PChar.quest.FalseTrace_Prepare.over = "yes";
			//Остальное
			sld = characterFromID("Charles_Priest");
			sld.name = "Жорж";
			sld.lastname = "Гравель";
		break;
		
		case "PZ_Test_Start_S_samogo_nachala":
			DialogExit();
			LAi_SetPlayerType(pchar);
			InterfaceStates.Buttons.Save.enable = true;
			bGameMenuStart = false;
			RemoveAllCharacterItems(pchar, true);
			AddMoneyToCharacter(pchar, 10000000);
			pchar.rank = 25;
			SetSPECIAL(PChar, 10, 10, 10, 10, 10, 10, 10);
			SetSelfSkill(PChar, 50, 50, 50, 50, 50);
			SetShipSkill(PChar, 50, 75, 50, 50, 100, 50, 50, 50, 75);
			SetCharacterPerk(pchar, "BasicDefense");
			SetCharacterPerk(pchar, "AdvancedDefense");
			SetCharacterPerk(pchar, "Ciras");
			SetCharacterPerk(pchar, "SwordplayProfessional");
			SetCharacterPerk(pchar, "CriticalHit");
			SetCharacterPerk(pchar, "AgileMan");
			SetCharacterPerk(pchar, "BladeDancer");
			SetCharacterPerk(pchar, "Sliding");
			SetCharacterPerk(pchar, "HardHitter");
			SetCharacterPerk(pchar, "EnergyPlus");
			SetCharacterPerk(pchar, "Medic");
			SetCharacterPerk(pchar, "Gunman");
			SetCharacterPerk(pchar, "GunProfessional");
			SetCharacterPerk(pchar, "Tireless");
			SetCharacterPerk(pchar, "IronWill");
			SetCharacterPerk(pchar, "CrewDamageUp");
			SetCharacterPerk(pchar, "CriticalShoot");
			SetCharacterPerk(pchar, "LongRangeShoot");
			SetCharacterPerk(pchar, "CannonProfessional");
			SetCharacterPerk(pchar, "LongRangeGrappling");
			SetCharacterPerk(pchar, "MusketsShoot");
			SetCharacterPerk(pchar, "GrapplingProfessional");
			SetCharacterPerk(pchar, "ShipDefenseProfessional");
			SetCharacterPerk(pchar, "ShipSpeedUp");
			SetCharacterPerk(pchar, "ShipTurnRateUp");
			SetCharacterPerk(pchar, "BasicBattleState");
			SetCharacterPerk(pchar, "AdvancedBattleState");
			SetCharacterPerk(pchar, "ShipDefenseProfessional");
			SetCharacterPerk(pchar, "StormProfessional");
			SetCharacterPerk(pchar, "SailingProfessional");
			SetCharacterPerk(pchar, "SailsMan");
			SetCharacterPerk(pchar, "WindCatcher");
			SetCharacterPerk(pchar, "SeaDogProfessional");
			SetCharacterPerk(pchar, "Trustworthy");
			GiveItem2Character(PChar, "blade_16");
			GiveItem2Character(PChar, "blade_13");
			EquipCharacterByItem(Pchar, "blade_13");
			GiveItem2Character(PChar, "pistol5");
			EquipCharacterByItem(Pchar, "pistol5");
			GiveItem2Character(PChar, "cirass8");
			EquipCharacterByItem(Pchar, "cirass8");
			GiveItem2Character(PChar, "spyglass4");
			EquipCharacterByItem(Pchar, "spyglass4");
			GiveItem2Character(PChar, "talisman2");
			EquipCharacterByItem(Pchar, "talisman2");
			GiveItem2Character(PChar, "talisman13");
			AddItems(Pchar, "cartridge", 50);
			AddItems(Pchar, "potion4", 20);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "cartridge");
			AddItems(pchar, "gold_dublon", 500);
			// Мой корабль
			pchar.Ship.Type = GenerateShipExt(SHIP_MAYFANG, true, pchar);
			pchar.Ship.name="Мейфенг";
			SetBaseShipData(pchar);
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS20;
			SetCrewQuantity(pchar, 170);
			pchar.ship.Crew.Morale = 100;
			ChangeCrewExp(pchar, "Sailors", 100);
			ChangeCrewExp(pchar, "Cannoners", 100);
			ChangeCrewExp(pchar, "Soldiers", 100);
			SetCharacterGoods(pchar, GOOD_BALLS, 300);
			SetCharacterGoods(pchar, GOOD_GRAPES, 800);
			SetCharacterGoods(pchar, GOOD_KNIPPELS, 800);
			SetCharacterGoods(pchar, GOOD_BOMBS, 300);
			SetCharacterGoods(pchar, GOOD_POWDER, 1500);
			SetCharacterGoods(pchar, GOOD_FOOD, 3000);
			SetCharacterGoods(pchar, GOOD_MEDICAMENT, 500);
			SetCharacterGoods(pchar, GOOD_WEAPON, 500);
			SetCharacterGoods(pchar, GOOD_RUM, 500);
			setCharacterShipLocation(pchar, "SentJons_town");
			setWDMPointXZ("SentJons_town");
			//Лонгвэй
			sld = GetCharacter(NPC_GenerateCharacter("Longway", "Longway", "man", "Longway", 20, HOLLAND, -1, false, "quest"));
			sld.name = "Лонгвэй";
			sld.lastname = "";
			sld.greeting = "Longway";
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.dialog.currentnode = "Longway_officer";
			sld.CompanionDisable = true;
			sld.rank = 20;
			sld.money = 5000;
			SetSelfSkill(sld, 45, 45, 45, 40, 50);
			SetShipSkill(sld, 50, 20, 25, 25, 65, 20, 20, 50, 15);
			SetSPECIAL(sld, 8, 9, 6, 5, 10, 7, 5);
			LAi_SetHP(sld, 250, 250);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "StormProfessional");
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "SailingProfessional");
			GiveItem2Character(sld, "blade_08");
			sld.equip.blade = "blade_08";
			GiveItem2Character(sld, "pistol3");
			EquipCharacterbyItem(sld, "pistol3");
			LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "grapeshot");
			TakeNItems(sld, "grapeshot", 50);
			AddItems(sld, "gunpowder", 50);
			TakeNItems(sld, "potion2", 1);
			//
			sld.quest.OfficerPrice = sti(pchar.rank)*200;
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0; 
			sld.Health.maxHP    = 60.0;
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			LAi_SetOfficerType(sld);
			sld.greeting = "Longway";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			// Тичингиту
			sld = GetCharacter(NPC_GenerateCharacter("Tichingitu", "maskog", "man", "man", 5, FRANCE, -1, false, "quest"));
			sld.name = "Тичингиту";
			sld.lastname = "";
			sld.greeting = "Tichingitu";
			sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			sld.dialog.currentnode = "Tichingitu";
			sld.rank = 20;
			LAi_SetHP(sld, 200.0, 200.0);
			SetSPECIAL(sld, 4, 9, 5, 5, 10, 8, 8);
			SetSelfSkill(sld, 50, 50, 50, 70, 50);
			SetShipSkill(sld, 30, 30, 30, 30, 50, 30, 50, 50, 30);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			AddItems(sld, "mushket1", 1);
			sld.CanTakeMushket = true;
			GiveItem2Character(sld, "blade_10");
			sld.equip.blade = "blade_10";
			GiveItem2Character(sld, "pistol1");
			sld.equip.gun = "pistol1";
			GiveItem2Character(sld, "cirass1");
			EquipCharacterbyItem(sld, "cirass1");
			AddItems(sld, "cartridge", 50);
			sld.quest.OfficerPrice = sti(pchar.rank) * 20;
			sld.OfficerWantToGo.DontGo = true;
			sld.CompanionDisable = true;
			sld.loyality = MAX_LOYALITY;
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			LAi_SetOfficerType(sld);
			sld.dialog.currentnode = "Tichingitu_officer";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(sld, "HiredDate");
			AddItems(sld, "potion2", 10);
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0; 
			sld.Health.maxHP    = 60.0;
			
			//Телепорт
			DoQuestReloadToLocation("SentJons_town", "reload", "reload1", "PZ_BETA_Test_Start_S_samogo_nachala_2");
			//выключить сторонние квесты
			PChar.quest.Red_Chieftain.over = "yes";
			PChar.quest.False_Trace.over = "yes";
			PChar.quest.FalseTrace_Prepare.over = "yes";
			//Остальное
			SetQuestHeader("Holl_Gambit");
			AddQuestRecord("Holl_Gambit", "1-1");
			AddQuestRecord("Holl_Gambit", "1-3");
			AddQuestRecord("Holl_Gambit", "1-6");
		break;
		
		case "PZ_Test_Start_BasTer":
			DialogExit();
			LAi_SetPlayerType(pchar);
			InterfaceStates.Buttons.Save.enable = true;
			bGameMenuStart = false;
			RemoveAllCharacterItems(pchar, true);
			AddMoneyToCharacter(pchar, 10000000);
			pchar.rank = 25;
			SetSPECIAL(PChar, 10, 10, 10, 10, 10, 10, 10);
			SetSelfSkill(PChar, 50, 50, 50, 50, 50);
			SetShipSkill(PChar, 50, 75, 50, 50, 100, 50, 50, 50, 75);
			SetCharacterPerk(pchar, "BasicDefense");
			SetCharacterPerk(pchar, "AdvancedDefense");
			SetCharacterPerk(pchar, "Ciras");
			SetCharacterPerk(pchar, "SwordplayProfessional");
			SetCharacterPerk(pchar, "CriticalHit");
			SetCharacterPerk(pchar, "AgileMan");
			SetCharacterPerk(pchar, "BladeDancer");
			SetCharacterPerk(pchar, "Sliding");
			SetCharacterPerk(pchar, "HardHitter");
			SetCharacterPerk(pchar, "EnergyPlus");
			SetCharacterPerk(pchar, "Medic");
			SetCharacterPerk(pchar, "Gunman");
			SetCharacterPerk(pchar, "GunProfessional");
			SetCharacterPerk(pchar, "Tireless");
			SetCharacterPerk(pchar, "IronWill");
			SetCharacterPerk(pchar, "CrewDamageUp");
			SetCharacterPerk(pchar, "CriticalShoot");
			SetCharacterPerk(pchar, "LongRangeShoot");
			SetCharacterPerk(pchar, "CannonProfessional");
			SetCharacterPerk(pchar, "LongRangeGrappling");
			SetCharacterPerk(pchar, "MusketsShoot");
			SetCharacterPerk(pchar, "GrapplingProfessional");
			SetCharacterPerk(pchar, "ShipDefenseProfessional");
			SetCharacterPerk(pchar, "ShipSpeedUp");
			SetCharacterPerk(pchar, "ShipTurnRateUp");
			SetCharacterPerk(pchar, "BasicBattleState");
			SetCharacterPerk(pchar, "AdvancedBattleState");
			SetCharacterPerk(pchar, "ShipDefenseProfessional");
			SetCharacterPerk(pchar, "StormProfessional");
			SetCharacterPerk(pchar, "SailingProfessional");
			SetCharacterPerk(pchar, "SailsMan");
			SetCharacterPerk(pchar, "WindCatcher");
			SetCharacterPerk(pchar, "SeaDogProfessional");
			SetCharacterPerk(pchar, "Trustworthy");
			GiveItem2Character(PChar, "blade_16");
			GiveItem2Character(PChar, "blade_13");
			EquipCharacterByItem(Pchar, "blade_13");
			GiveItem2Character(PChar, "pistol5");
			EquipCharacterByItem(Pchar, "pistol5");
			GiveItem2Character(PChar, "cirass8");
			EquipCharacterByItem(Pchar, "cirass8");
			GiveItem2Character(PChar, "spyglass4");
			EquipCharacterByItem(Pchar, "spyglass4");
			GiveItem2Character(PChar, "talisman2");
			EquipCharacterByItem(Pchar, "talisman2");
			GiveItem2Character(PChar, "talisman13");
			AddItems(Pchar, "cartridge", 50);
			AddItems(Pchar, "potion4", 20);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "cartridge");
			AddItems(pchar, "gold_dublon", 500);
			// Мой корабль
			pchar.Ship.Type = GenerateShipExt(SHIP_MAYFANG, true, pchar);
			pchar.Ship.name="Мейфенг";
			SetBaseShipData(pchar);
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS20;
			SetCrewQuantity(pchar, 170);
			pchar.ship.Crew.Morale = 100;
			ChangeCrewExp(pchar, "Sailors", 100);
			ChangeCrewExp(pchar, "Cannoners", 100);
			ChangeCrewExp(pchar, "Soldiers", 100);
			SetCharacterGoods(pchar, GOOD_BALLS, 300);
			SetCharacterGoods(pchar, GOOD_GRAPES, 800);
			SetCharacterGoods(pchar, GOOD_KNIPPELS, 800);
			SetCharacterGoods(pchar, GOOD_BOMBS, 300);
			SetCharacterGoods(pchar, GOOD_POWDER, 1500);
			SetCharacterGoods(pchar, GOOD_FOOD, 3000);
			SetCharacterGoods(pchar, GOOD_MEDICAMENT, 500);
			SetCharacterGoods(pchar, GOOD_WEAPON, 500);
			SetCharacterGoods(pchar, GOOD_RUM, 500);
			setCharacterShipLocation(pchar, "Mayak4");
			setWDMPointXZ("Mayak4");
			//Лонгвэй
			sld = GetCharacter(NPC_GenerateCharacter("Longway", "Longway", "man", "Longway", 20, HOLLAND, -1, false, "quest"));
			sld.name = "Лонгвэй";
			sld.lastname = "";
			sld.greeting = "Longway";
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.dialog.currentnode = "Longway_officer";
			sld.CompanionDisable = true;
			sld.rank = 20;
			sld.money = 5000;
			SetSelfSkill(sld, 45, 45, 45, 40, 50);
			SetShipSkill(sld, 50, 20, 25, 25, 65, 20, 20, 50, 15);
			SetSPECIAL(sld, 8, 9, 6, 5, 10, 7, 5);
			LAi_SetHP(sld, 250, 250);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "StormProfessional");
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "SailingProfessional");
			GiveItem2Character(sld, "blade_08");
			sld.equip.blade = "blade_08";
			GiveItem2Character(sld, "pistol3");
			EquipCharacterbyItem(sld, "pistol3");
			LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "grapeshot");
			TakeNItems(sld, "grapeshot", 50);
			AddItems(sld, "gunpowder", 50);
			TakeNItems(sld, "potion2", 1);
			//
			sld.quest.OfficerPrice = sti(pchar.rank)*200;
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0; 
			sld.Health.maxHP    = 60.0;
			//AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			LAi_SetOfficerType(sld);
			sld.greeting = "Longway";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			// Тичингиту
			sld = GetCharacter(NPC_GenerateCharacter("Tichingitu", "maskog", "man", "man", 5, FRANCE, -1, false, "quest"));
			sld.name = "Тичингиту";
			sld.lastname = "";
			sld.greeting = "Tichingitu";
			sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			sld.dialog.currentnode = "Tichingitu";
			sld.rank = 20;
			LAi_SetHP(sld, 200.0, 200.0);
			SetSPECIAL(sld, 4, 9, 5, 5, 10, 8, 8);
			SetSelfSkill(sld, 50, 50, 50, 70, 50);
			SetShipSkill(sld, 30, 30, 30, 30, 50, 30, 50, 50, 30);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			AddItems(sld, "mushket1", 1);
			sld.CanTakeMushket = true;
			GiveItem2Character(sld, "blade_10");
			sld.equip.blade = "blade_10";
			GiveItem2Character(sld, "pistol1");
			sld.equip.gun = "pistol1";
			GiveItem2Character(sld, "cirass1");
			EquipCharacterbyItem(sld, "cirass1");
			AddItems(sld, "cartridge", 50);
			sld.quest.OfficerPrice = sti(pchar.rank) * 20;
			sld.OfficerWantToGo.DontGo = true;
			sld.CompanionDisable = true;
			sld.loyality = MAX_LOYALITY;
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			LAi_SetOfficerType(sld);
			sld.dialog.currentnode = "Tichingitu_officer";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(sld, "HiredDate");
			AddItems(sld, "potion2", 10);
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0; 
			sld.Health.maxHP    = 60.0;
			
			//Телепорт
			DoQuestReloadToLocation("Mayak4", "goto", "goto2", "PZ_BETA_Test_Start_BasTer");
			//выключить сторонние квесты
			PChar.quest.Red_Chieftain.over = "yes";
			PChar.quest.False_Trace.over = "yes";
			PChar.quest.FalseTrace_Prepare.over = "yes";
			//Остальное
		break;
		
		case "PZ_Test_Start_Formosa":
			DialogExit();
			
			SetMainCharacterIndex(GetCharacterIndex("Longway"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			InterfaceStates.Buttons.Save.enable = true;
			bGameMenuStart = false;
			RemoveAllCharacterItems(pchar, true);
			//AddMoneyToCharacter(pchar, 10000000);
			GiveItem2Character(PChar, "blade_11");
			EquipCharacterByItem(Pchar, "blade_11");
			RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
			pchar.rank = 25;
			SetSPECIAL(PChar, 10, 10, 10, 10, 10, 10, 10);
			SetSelfSkill(PChar, 50, 50, 50, 50, 50);
			SetShipSkill(PChar, 50, 75, 50, 50, 100, 50, 50, 50, 75);
			
			//Телепорт
			DoQuestReloadToLocation("Formosa", "patrol", "patrol1", "PZ_Formosa_Start");
			//выключить сторонние квесты
			PChar.quest.Red_Chieftain.over = "yes";
			PChar.quest.False_Trace.over = "yes";
			PChar.quest.FalseTrace_Prepare.over = "yes";
		break;

        case "Node_1":
			bGameMenuStart = false;
			StartBattleLandInterface();
			dialog.text = "Да на безбожников этих краснорожих, даже на их языке говорили.";
			link.l1     = "Дьявол! Сандро, что ты несёшь?!";
			link.l1.go  = "Node_2";
		break;
		
		case "Node_1_Jess":
			dialog.text = "Так вы ничего не помните? Да и немудрено, другой бы от такой контузии давно загнулся, или всю оставшуюся жизнь улыбался и штаны пачкал, а вы оказались крепким орешком. Правда, ослабли очень, еле на ногах держитесь - скоро уж полгода как пытаемся вас выходить.";
			link.l1     = "Расскажи толком, что за контузия - видишь, не помню ничего.";
			link.l1.go  = "Node_2_Jess";
		break;
		
		case "Node_2":
			dialog.text = "Да вы не волнуйтесь, нельзя вам волноваться. Вы воздухом подышите, на море посмотрите, вот голова и прояснится. Доктор так и говорил, - если в себя придёт - ничего помнить не будет, - вот вы и не помните, и незачем вам.";
			link.l1     = "Интересное дело - а, если не придёт?";
			link.l1.go  = "Node_3";
		break;
		
		case "Node_2_Jess":
			dialog.text = "Эх, да что здесь рассказывать... Говорили мы вам - и я, и старпом, - бросайте вы этого Белтропа, доведёт он нас до цугундера. Нет же!.. Вот и доигрались, пока этот тип в маске не послал вам пулю в затылок! Да благодарите Господа и свою пышную шевелюру, что пуля краем прошла. Только кость раздробила, а в черепе не застряла, иначе не жить бы вам\nЧто крови много было, и сознание потеряли - это даже хорошо - Маска решил, что с вами всё кончено. Пока он кинулся, мы уже успели вытащить вас из развалин той старой церкви.";
			link.l1     = "Проклятье! Маска пытался меня убить... Никому нельзя верить... А что с Лоуренсом? Он жив?";
			link.l1.go  = "Node_3_Jess";
		break;
		
		case "Node_3":
			dialog.text = "А, если не придёт, говорит, то всё, везите в приют для душевнобольных и даже не сумлевайтесь. Ибо не он это уже - раздвоение личное... А мы с Хопкинсом думаем - как же не он"+ GetSexPhrase("","а") +", ежели он"+ GetSexPhrase("","а") +"! Только, вроде, с похмелья сильного, и всё браниться норовит, а язык заплетается, и речь на манер туземцев выходит. Почитай, полгода так с вами и пронянькались, в конце уже и понимать приноровились. Только оружие убрали от греха подальше, и доктор рому не велел давать...";
			link.l1     = "Что за чушь ты несёшь - неужели всё это со мной было?";
			link.l1.go  = "Node_4";
		break;
		
		case "Node_3_Jess":
			dialog.text = "Нет, слава Богу. Ой, извините... Вздёрнули его, Маска приказал повесить. А самого Маску, поговаривают, Акула зарезал. А по мне - так туда им обоим и дорога. Оба одним миром мазаны - негодяи. Столько крови вам попортили, мерзавцы!";
			link.l1     = "Нехорошо так о покойных... Да и былого уже не воротишь. Бог им судья... Спасибо вам, братцы, что из могилы вытащили, я этого не забуду.";
			link.l1.go  = "Node_4_Jess";
		break;
		
		case "Node_4":
			dialog.text = "Вот вам крест. Мы и сами испугались - а ну как в себя не придёте, что делать будем? И чем только эти голодранцы краснозадые вас опоили, проклятые! Ну, - слава Богу, - вы уже оклемались. Сейчас-то как себя чувствуете?";
			//link.l1     = "Опоили, говоришь... очень на то похоже - не помню ничегошеньки... Дай-ка я с мыслями соберусь, да в себя приду. (создание своего типа героя).";
			//link.l1.go  = "ChangePIRATES";
			link.l2     = "Да вроде нормально себя чувствую. Только голова чуть кружится, будто с похмелья...";
			link.l2.go  = "Node_5";
		break;
		
		case "Node_4_Jess":
			dialog.text = "Это наш долг, капитан! Мы с Хопкинсом перевезли вас на судно и, как могли, остановили кровь. Потом и доктора доставили - он вас наголо остричь хотел, но мы не позволили. Всё боялся, что мы его пристрелим, если вы Богу душу отдадите\nНо всё обошлось - вот вы уже и на ноги встали. Как себя чувствуете?";
			//link.l1     = "Хм... дай минутку, соберусь с мыслями...(создание своего типа героя).";
			//link.l1.go  = "ChangePIRATES_Jess";
			link.l2     = "Да вроде уже ничего. Спасибо за заботу, Сандро.";
			link.l2.go  = "Node_5_Jess";
		break;
		
		case "Node_5":
			dialog.text = "Ну, спиртного вам нельзя, а то, не ровен час, опять раздвоение начнётся. А вот со шпагой поупражняться не помешало бы. Вы, небось, уже и забыли, с какого конца её держать нужно.";
			link.l1     = "А ты знаешь, чем подцепить. Ну, давай попробуем, а то чувствую себя - "+ GetSexPhrase("медведь медведем","медведицей") +".";
			link.l1.go  = "Teach_1";
			link.l2     = "Не волнуйся, у меня же с головой проблемы были, а не с руками. Схожу-ка я в порт, а то одичал"+ GetSexPhrase("","а") +" совсем.";
			link.l2.go  = "Finish_1";
		break;
		
		case "Node_5_Jess":
			dialog.text = "Ну вот видите, я знал, что всё будет в порядке... Но ранение в голову бесследно не проходит, потребуется время и упорство, чтоб восстановить свои силы и уменья. Не желаете руку размять - в фехтовании поупражняться?";
			link.l1     = "Хорошая идея. Давай-ка посмотрим, не совсем ли я расклеилась.";
			link.l1.go  = "Teach_1_Jess";
			link.l2     = "Нет, не хочу. Я уверена в своих силах.";
			link.l2.go  = "Finish_1";
		break;
		
		case "Finish_1":
			if (pchar.name == "Джессика")
			{
				dialog.text = "Мы сейчас в порту " + XI_ConvertString("Colony" + pchar.HeroParam.ToCityId + "Gen") + ". Нужно как-то начинать новую жизнь без всех этих Масок и Белтропов, будь они неладны... То есть, пусть земля им будет пухом, я хотел сказать... А мы уж вас не подведём, капитан. Ваша команда останется с вами до конца.";
				link.l1     = "Ну что ж, значит - к новой мечте! Я вас не подведу и не разочарую. Всё, я на берег.";
				link.l1.go  = "Finish_2";
				link.l2     = "На смену одним мерзавцам появятся другие - такова жизнь, Сандро. Дашь мне пару советов, перед тем как я сойду на берег?";
				link.l2.go  = "Advice_1";
			}
			else
			{
				dialog.text = "Мы сейчас в порту поселения " + XI_ConvertString("Colony" + pchar.HeroParam.ToCityId + "Gen") + ", осваивайтесь, да возвращайтесь. Мы уж соскучились по настоящему делу - старый корабль продать пришлось, а на этом много не навоюешь. Так, перебивались в ожидании вашего выздоровления. А парни в вас верят, иначе бы разбежались давно...";
				link.l1     = "Замечательно. Всё, я на берег... Да не волнуйся ты так, чай не маленьк"+ GetSexPhrase("ий","ая") +" - не заблужусь.";
				link.l1.go  = "Finish_2";
				link.l2     = "Если считаешь, что я ещё не готов"+ GetSexPhrase("","а") +" - говори. Дельный совет лишним не будет.";
				link.l2.go  = "Advice_1";
			}
		break;
		
		case "Advice_1":
			dialog.text = "Ну что же, кэп... Нужно залатать корабль, пополнить экипаж да запастись припасами. И вперёд, на поиски приключений! Лучше, конечно, получить каперский патент - тогда мы не будем вне закона, если займёмся пиратством, а семьям своим сможем честно сказать, что работа наша - вполне легальна. А вы тогда сможете сделать неплохую карьеру и прославить своё имя.";
			link.l1     = "Что ещё стоит знать?";
			link.l1.go  = "Advice_2";
			link.l2     = "Замечательно. Всё, я на берег.";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_2":
			dialog.text = "Чтобы торговать с выгодой, нужно знать, каковы текущие цены на товары в магазинах архипелага. Узнать их можно, посещая магазины лично, а можно спросить у встречных купцов в море или послушать слухи.";
			link.l1     = "Дальше.";
			link.l1.go  = "Advice_3";
			link.l2     = "Замечательно. Всё, я на берег.";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_3":
			dialog.text = "Орудия на корабле могут выйти из строя, и тогда их придётся заменить. Можно также снять часть орудий и освободить дополнительное место под груз.";
			link.l1     = "Дальше.";
			link.l1.go  = "Advice_4";
			link.l2     = "Замечательно. Всё, я на берег.";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_4":
			dialog.text = "Если мы всё-таки станем каперами, то учтите что корабли, захваченные в море, продаются на верфи по бросовым ценам, тогда как честно купленные можно продать на другой верфи с неплохим барышом.";
			link.l1     = "Дальше.";
			link.l1.go  = "Advice_5";
			link.l2     = "Замечательно. Всё, я на берег.";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_5":
			dialog.text = "Не стоит портить отношения с контрабандистами почём зря - они обеспечивают хороший доход, пусть и с риском для здоровья.";
			link.l1     = "Дальше.";
			link.l1.go  = "Advice_6";
			link.l2     = "Замечательно. Всё, я на берег.";
			link.l2.go  = "Finish_2";
		break;
		
		case "Advice_6":
			dialog.text = "Наймите офицеров, у нас вообще никого нет. Если авторитет ваш невысок, вы не сможете нанять много офицеров. В этом случае нанимайте тех, кто сможет занимать по две-три должности сразу. Трое таких всезнаек закроют нам все должности.";
			link.l1     = "Дальше.";
			link.l1.go  = "Advice_7";
			link.l2     = "Замечательно. Всё, я на берег.";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_7":
			dialog.text = "Воровство - штука неприглядная, но может случиться так, что вам очень нужно будет обчистить сундук в каком-нибудь доме, банке или магазине. Постарайтесь дождаться, когда хозяин отвернётся, и только тогда лезьте в сундук. И помните - если хозяин внезапно обернётся и увидит, что вы в его сундук залезли, то быть беде. Так что здесь нужно быть проворнее!";
			link.l1     = "Дальше.";
			link.l1.go  = "Advice_8";
			link.l2     = "Замечательно. Всё, я на берег.";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_8":
			dialog.text = "Возможно, вам понадобится проникнуть во вражеский город. Запомните хорошенько то, что я вам сейчас скажу - солдат в порту и на воротах, которые проверяют всех входящих в город, ночью нет! Так что заходить во вражеский город лучше ночью, а там уже знай - не попадайся патрулю. Патрульные солдаты, кстати, глаз на затылке не имеют и видят только впереди себя и по бокам. Ночью во вражеском городе пробирайтесь в таверну, переночуйте там до утра, а уже днём делайте свои дела. Но при передвижениях по городу держитесь от солдат подальше.";
			link.l1     = "Дальше.";
			link.l1.go  = "Advice_9";
			link.l2     = "Замечательно. Всё, я на берег.";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_9":
			dialog.text = "Ещё можно поднять на корабле враждебный флаг, если он у вас есть, и уповать на свою удачу и скрытность. Ну, а самый надёжный способ благополучно проникнуть во вражеский город - купить лицензию национальной торговой компании, в этом случае вас никто не задержит. Однако, не забудьте флаг на корабле поднять соответствующий. Сами понимаете, глупо пытаться предъявить испанскую лицензию, если флаг на мачте - английский.";
			link.l1     = "Дальше.";
			link.l1.go  = "Advice_10";
			link.l2     = "Замечательно. Всё, я на берег.";
			link.l2.go  = "Finish_2";
		break;

		case "Advice_10":
			dialog.text = "Знайте, что казематы находятся в фортах, в городах их не ищите.";
			link.l1     = "Спасибо. Мне пора на берег.";
			link.l1.go  = "Finish_2";
		break;
		/////   фехт 
		case "Teach_1":
			dialog.text = "Ну что же, начнём, пожалуй. У вас это всегда здорово получалось, но я напомню. Есть три атакующих удара: обычный удар, выпад и пробивной удар. Защитных действий тоже три: блок, парирование и финт. Есть ещё защитно-атакующий круговой удар. И, конечно же, пистолет, чтобы противника издалека свинцовым талером угостить.";
			link.l1     = "Хорошо-хорошо, давай ближе к делу.";
			link.l1.go  = "Teach_2";
		break;
		
		case "Teach_1_Jess":
			dialog.text = "Ну что же, начнём, пожалуй. У вас это всегда здорово получалось, но я напомню. Есть три атакующих удара: обычный удар, выпад и пробивной удар. Защитных действий тоже три: блок, парирование и финт. Есть ещё защитно-атакующий круговой удар. И, конечно же, пистолет, чтобы противника издалека свинцовым талером угостить.";
			link.l1     = "Это ясно. Что дальше?";
			link.l1.go  = "Teach_2";
		break;
		
		case "Teach_2":
			dialog.text = "Любое атакующее действие требует расхода энергии, на защитные действия энергия не расходуется. Можно также уклоняться от ударов, отскакивая назад и в стороны. Но так можно и пулю получить, если расстояние увеличится, и противник - не дурак.";
			link.l1     = "Дальше.";
			link.l1.go  = "Teach_3";
			link.l2     = "Что такое энергия?";
			link.l2.go  = "Teach_2_1";
		break;
		
		case "Teach_2_1":
			dialog.text = "Энергия - это показатель запаса сил персонажа в рукопашной схватке. Все атакующие действия требуют затрат энергии. Другими словами, в процессе схватки персонаж устаёт, и для восполнения сил ему требуется передышка. "+
						  "Максимальное значение энергии зависит от текущей величины реакции персонажа.";
			link.l1     = "Дальше.";
			link.l1.go  = "Teach_3";
		break;
		
		case "Teach_3":
			dialog.text = "Во время схватки избегайте окружения большим количеством противников, иначе вас быстро порежут на бифштексы. Противостоять двоим ещё можно, а вот троих и более сразу уложить - уже сложно. Когда энергия противников иссякнет, они начнут финты да парирование применять. Смотрите, не попадайтесь - быстро останетесь без головы.";
			link.l1     = "Дальше.";
			link.l1.go  = "Teach_4";
		break;
		
		case "Teach_4":
			dialog.text = "Если соперник попался на ваш финт - он получит заметный урон, поболее, чем от колющего удара. Если же попасться на парирование, то можно и без энергии остаться. Собьют с ритма - и всех дел.";
			link.l1     = "Дальше.";
			link.l1.go  = "Teach_5";
		break;
		
		case "Teach_5":
			dialog.text = "Оружие у всех разное, делится по весу на лёгкое, среднее и тяжёлое. Вес оружия определяет расход энергии. Лёгеньким кинжалом можно без устали орудовать, зато тяжёлым топором можно одним круговым ударом нескольких противников за раз на тот свет отправить.";
			link.l1     = "Дальше.";
			link.l1.go  = "Teach_6";
		break;
		
		case "Teach_6":
			pchar.HeroParam.Teach_battle = 1;
			Tut_RestoreState();
			dialog.text = "Ну что, перейдём к практике? Предлагаю размять косточки. Биться будем по-настоящему, но не до смерти. Жизнь в бою можно эликсирами, зельями или ромом восстановить, но сейчас вы их лучше поберегите - будем тренироваться.";
			link.l1     = "Давай, пощады не жди!";
			link.l1.go  = "Teach_battle_1";
			link.l2     = "Нет, спасибо. Я уже всё понял"+ GetSexPhrase("","а") +".";
			link.l2.go  = "Finish_1";
		break;
		
		case "Teach_battle_lose":
			Tut_RestoreState();
			dialog.text = LinkRandPhrase("Да-а... Что-то совсем вы ослабели. Будьте внимательнее, больше блокируйте и парируйте. От  пробивного удара блок не спасает - используйте финт, парирование или отскок.",
			                             "Не давайте себя ударить, перехватывайте удар противника колющим или парируйте. Но будьте осторожны, если попадётесь на финт - перехватят ваш колющий, да ещё и урон нанесут.",
										 "Если энергия иссякнет - убегайте или отпрыгивайте, а противника доставайте финтом. Учтите, финтом удар так просто не отбить, но можно противника обмануть. И уж если попадётся он на вашу уловку, да попытается на ваш обманный замах ударом ответить - тут вы не только его клинок от себя отведёте, но и сами ему нанесёте урон.") +
										 " Ну что, ещё раз?";
			if (sti(pchar.rank) < 3) // чтоб не качались до упора
			{
				link.l1     = "Ещё раз!";
				link.l1.go  = "Teach_battle_1";
			}
			link.l2     = "Нет, достаточно. Я всё понял"+ GetSexPhrase("","а") +".";
			link.l2.go  = "Finish_1";
		break;
		
		case "Teach_battle_win":
			pchar.HeroParam.Teach_battle = 2;
			Tut_RestoreState();
			dialog.text = "Хорошо. Молодец! Учтите, я дрался честно, но у врагов могут свои эликсиры жизни быть, тогда они будут не так легко даваться. " +
						  "Ну что, усложним задачу. Давайте против двоих противников?";
			link.l1     = "Что же, давай. Эй, Хопкинс! Хватай свой тесак и бегом на палубу!";
			link.l1.go  = "Teach_battle_1";
			link.l2     = "Нет, спасибо. Я достаточно "+ GetSexPhrase("потренировался","потренировалась") +".";
			link.l2.go  = "Finish_1";
		break;
		
		case "Teach_battle_win_2":
			Tut_RestoreState();
			sld = characterFromID("Sailor_2");
			LAi_SetCitizenType(sld);
			if (pchar.name == "Джессика")
			{
				dialog.text = "Прекрасно, капитан! Уроки Белтропа не прошли бесследно, всё же он неплохо вас обучил. И последний совет: чем больше вы фехтуете оружием одного типа, тем больше растёт ваше умение. Хотите восстановить мастерство владения всеми видами - чаще меняйте тип оружия.";
			}
			else
			{
				dialog.text = "Да, с руками у вас всё в порядке - не напрасно мы оружие прятали. И последний совет: чем больше вы фехтуете оружием одного типа, тем больше растёт ваше умение. Хотите быть мастером во всех типах - чаще меняйте вид клинков.";
			}
			link.l1     = "Спасибо!";
			link.l1.go  = "Finish_1";
		break;
		
		case "Teach_battle_win_3":
			Tut_RestoreState();
			sld = characterFromID("Sailor_2");
			LAi_SetCitizenType(sld);
			dialog.text = "Что же, неплохо. Одного противника вы одолели, но двое - не один. Тут сноровка нужна. Враги могут ведь втроём или вчетвером нападать. Повторим?";
   			if (sti(pchar.rank) < 3) // чтоб не качались до упора
			{
				link.l1     = "Ещё раз!";
				link.l1.go  = "Teach_battle_1";
			}
			link.l2     = "Нет, я уже всё понял"+ GetSexPhrase("","а") +".";
			link.l2.go  = "Finish_1";
		break;
	}
}
