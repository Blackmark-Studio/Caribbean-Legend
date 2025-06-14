// Тичингиту - индеец-офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Вы что-то хотели?";
			link.l1 = "Да нет, ничего.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Tichingitu":
			DelLandQuestMark(npchar);
			dialog.text = "Что ты хотеть, бледнолицый? У Тичингиту нет для тебя слов.";
			link.l1 = "Тебя зовут Тичингиту? Хм. Послушай, воин, я пришёл не для того, чтобы пялить на тебя глаза, а чтобы спросить: зачем ты полез в дом к этому толстяку?";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "";
			link.l1 = "Молчишь? Глупо. Тебя повесят за воровство, и всех дел. Расскажи, зачем ты совершил этот поступок, - быть может, я смогу тебе помочь.";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			dialog.text = "Тичингиту - индеец-маског, прийти в город бледнолицых через много-много дорог, через большой вода, из страны больших лесов и болот. Тичингиту устать и хотеть есть. Тичингиту умирать от голод. Никто не хотеть помочь Тичингиту, кричать - вон, краснокожий собака. Хозяин таверна выгнать индеец, как шелудивый пёс. Тичингиту хотеть есть. Тичингиту искать монеты, чтобы купить еда.";
			link.l1 = "Чёрт побери, но зачем же ты явился в это поселение из... своего леса?";
			link.l1.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			dialog.text = "Тичингиту изгнать из его родной племя. Тичингиту ссориться шаман племя, шаман сказать вождь, шаман проклинать Тичингиту - Тичингиту уйти племя, прочь-прочь от родной селение. Тичингиту нет дома, нет оружия, нет ничего.";
			link.l1 = "Да, уж, не повезло тебе. Ну и зачем ты поссорился со своими соплеменниками?";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "Шаман наше племя - злой человек. Он завидовать Тичингиту. Он сказать - мой жена вселиться злой дух, жена должен умереть. Но он лгать, дух не вселяться. Я защищать жена, но шаман убить жена. Тичингиту встать против шаман, все встать против Тичингиту, Тичингиту уходить.";
			link.l1 = "Ты пытался спасти жену? Из-за этого тебя изгнали из деревни?";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			dialog.text = "Так, бледнолицый. У Тичингиту не быть выбор - или украсть, или умереть голод...";
			link.l1 = "Вот незадача... Из-за каких-то нескольких жалких монет на кусок еды вешать человека... Тичингиту, я попробую помочь тебе. Я знаю Фадея - того здоровяка, в дом которого ты залез. Может, мне удастся что-то сделать... Я сейчас поговорю с комендантом.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
			pchar.questTemp.Sharlie.Tichingitu = "commandante";
			AddLandQuestMark(characterFromId("BasterJailOff"), "questmarkmain");
			AddQuestRecord("Tichingitu", "2");
		break;
		
		case "Tichingitu_wait":
			dialog.text = "Тичингиту ждать. Индеец не бояться смерти. Шаман проклясть Тичингиту - Тичингиту должен умереть.";
			link.l1 = "Ещё не всё потеряно. Я пытаюсь помочь...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
		break;
		
		case "Tichingitu_6":
			DelLandQuestMark(npchar);
			dialog.text = "Тичингиту ждать. Индеец не бояться смерти. Шаман проклясть Тичингиту - Тичингиту должен умереть.";
			link.l1 = "Не будь таким пессимистом. Твои мытарства окончены. Я добился твоего освобождения.";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			dialog.text = "Бледнолицый шутить? Тичингиту свободен?";
			link.l1 = "Никаких шуток. Сейчас откроют твою камеру и выпустят тебя. Следуй за мной, я выведу тебя из тюрьмы.";
			link.l1.go = "Tichingitu_8";
		break;
		
		case "Tichingitu_8":
			DialogExit();
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			DoQuestReloadToLocation("BasTer_exittown", "rld", "aloc9", "TichingituFree"); // 170712
			pchar.quest.FreeTichingituOver.over = "yes"; //снять таймер
			if (GetHour() > 17.0)
			{
				WaitDate("", 0, 0, 0, 13, 0);
				RecalculateJumpTable();
				RefreshWeather();
				RefreshLandTime();
			}
			if (GetHour() < 8.0)
			{
				WaitDate("", 0, 0, 0, 7, 0);
				RecalculateJumpTable();
				RefreshWeather();
				RefreshLandTime();
			}
		break;
		
		case "Tichingitu_9":
			dialog.text = "";
			link.l1 = "Вот ты и снова на свободе. Иди, Тичингиту, смотри, не воруй и не попадайся больше! Лучше найди какую-нибудь индейскую деревню и живи там - думаю, её жители не откажутся принять тебя.";
			link.l1.go = "Tichingitu_10";
		break;
		
		case "Tichingitu_10":
			dialog.text = "Тичингиту не идти. Белый брат спасти жизнь Тичингиту. Тичингиту оставаться. Жизнь Тичингиту стать неразрывно связана с жизнь белый брат.";
			link.l1 = "Чего? Ты это о чём сейчас? Что это ты придумал - жизни неразрывно связаны? Ты разве не понял - ты свободен! Ступай!";
			link.l1.go = "Tichingitu_11";
		break;
		
		case "Tichingitu_11":
			dialog.text = "Нет, белый брат. Ты спасти Тичингиту, когда он не мочь защищаться, ты отвести позорная смерть от индеец. Тичингиту служить тебе верой и правдой всю жизнь. Тичингиту уметь сражаться. Тичингиту умереть в бою за белый брат, если быть надо. Он оставаться.";
			link.l1 = "Тьфу ты, дьявол... Что это ты такое говоришь, Тичингиту, - служить, сражаться, умереть в бою за меня? Я помог тебе не для того, чтобы затем превратить в какого-то раба-телохранителя!";
			link.l1.go = "Tichingitu_12";
		break;
		
		case "Tichingitu_12":
			dialog.text = "Тичингиту не раб, белый брат. Тичингиту - свободный индеец, он выбирать сам. Тичингиту хотеть служить тебе. Индеец уметь сражаться, любой пёс умереть, прежде чем подойти к белый брат. Тичингиту уметь чистить и заряжать мушкет. Тичингиту уметь стрелять из мушкет.";
			link.l1 = "Кхм... А знаешь, Тичингиту, возможно, это неплохая идея. Мне нужны верные люди, а ты мне кажешься неплохим человеком. И из мушкета, говоришь, стрелять умеешь. Да и что ты будешь делать один? Опять попадёшься на краже, тогда уж точно повесят... Хорошо, оставайся. Но учти - похоже, спокойной жизни со мной не будет. Мне тут пришлось капитаном заделаться...";
			link.l1.go = "Tichingitu_13";
			link.l2 = "Так, довольно. Ступай с миром, краснокожий брат. Да хранят тебя твои боги!";
			link.l2.go = "Tichingitu_exit";
		break;
		
		case "Tichingitu_exit":
			DialogExit();
			AddQuestRecord("Tichingitu", "5");
			CloseQuestHeader("Tichingitu");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.Sharlie.Tichingitu");
			pchar.systeminfo.tutorial.Fighter = true;
		break;
		
		case "Tichingitu_13":
			dialog.text = "Тичингиту не бояться ничего, белый брат. Тичингиту будет рад служить тебе. Тичингиту будет верен капитан до последний вздох.";
			link.l1 = "Хорошо. Добро пожаловать в команду, Тичингиту!";
			link.l1.go = "Tichingitu_hire";
		break;
		
		case "Tichingitu_hire":
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			LAi_SetImmortal(npchar, false);
			npchar.quest.OfficerPrice = sti(pchar.rank)*20;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.CompanionDisable = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			npchar.CanTakeMushket = true;
			LAi_SetOfficerType(npchar);
			NextDiag.CurrentNode = "Tichingitu_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			DeleteAttribute(pchar, "questTemp.Sharlie.Tichingitu");
			pchar.OfficerAttRange = 35.0;
			
			AddQuestRecord("Tichingitu", "4");
			CloseQuestHeader("Tichingitu");
			// Sinistra - Начало квеста "Знакомство с индейцами"
			string sModel = "Miskito_"+(rand(5)+1);
			sld = GetCharacter(NPC_GenerateCharacter("ListKakao", sModel, "man", "man", 1, PIRATE, -1, false, "quest"));
			sld.name = "Лист";
			sld.lastname = "Какао";
			GiveItem2Character(sld, "blade_01");
			EquipCharacterByItem(sld, "blade_01");
			AddItems(sld, "jewelry53", rand(20)+180);
			AddItems(sld, "cannabis1", 3);
			GiveItem2Character(sld, "indian_10");
			GiveItem2Character(sld, "talisman11");
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "ZsI_ListKakao";
			ChangeCharacterAddressGroup(sld, "BasTer_ExitTown", "item", "item3");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			//LaunchTutorial("Fighter", 1);
		break;
		
	//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Tichingitu_officer":
			dialog.text = "Тичингиту слушать вас, капитан "+pchar.name+"!";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Тичингиту, я собираюсь отправиться в старый индейский город Тайясаль. Не буду скрывать: это крайне опасное путешествие, и более того - необычное: через телепортационный истукан. Ты... пойдёшь со мной?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Тичингиту, дай мне полный отчёт о корабле.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Я хочу, чтобы во время стоянки в колонии ты закупал товары.";
				Link.l12.go = "QMASTER_2";
			}

			Link.l1 = "Слушай мой приказ!";
            Link.l1.go = "stay_follow";
			link.l2 = "Пока ничего. Вольно!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Tichingitu_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Отчёт? У Тичингиту нету отчёт, капитан. Только оружие и одежда есть. Никакой отчёт Тичингиту нигде не брать.";
			Link.l1 = "Ладно, проехали.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Капитан, Тичингиту без вас в колония больше нога не ступить. А то зайти Тичингиту в магазин - и снова все подумать, что Тичингиту вор. А дальше тюрьма.";
			link.l1 = "Да, пожалуй, ты прав. Из тюрьмы мне тебя вытаскивать не хочется. Да и не поверит никто, что ты казначей...";
			link.l1.go = "exit";
		break;
		
		case "stay_follow":
            dialog.Text = "Какие быть приказания?";
            Link.l1 = "Стой здесь!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Следуй за мной и не отставай!";
            Link.l2.go = "Boal_Follow";
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Нужно изменить тип боеприпаса для твоего пистолета.";
					Link.l3.go = "SetGunBullets";
				}	
			}
			
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "Нужно изменить тип боеприпаса для твоего мушкета.";
					Link.l4.go = "SetMusketBullets";
				}
					Link.l5 = "Нужно изменить тип твоего приоритетного оружия для боя.";
					Link.l5.go = "SetPriorityMode";
					Link.l6 = "Я хочу, чтобы ты держался на определённом расстоянии от цели.";
					Link.l6.go = "TargetDistance";
			}	
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Выбор типа боеприпаса:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;
		
		case "SetMusketBullets":
			Dialog.Text = "Выбор типа боеприпаса:";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetMusketBullets1_" + i;
			}
		break;
		
		case "SetMusketBullets2":
			i = sti(NPChar.GenQuest.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, "musket", sBullet);
			LAi_GunSetUnload(NPChar, "musket");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(NPChar,"GenQuest.SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "В начале боя я буду доставать:";
			Link.l1 = "Холодное оружие";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Мушкет";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
            SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Есть изменить дислокация!";
            Link.l1 = "Вольно.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Есть изменить дислокация!";
            Link.l1 = "Вольно.";
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = "На какой именно, капитан? Указать Тичингиту в ярдах, но не больше, чем двадцать.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Капитан, простить Тичингиту, но я вас не понимать.";
				link.l1 = "Извини, ошибочка вышла...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Тичингиту быть стоять на месте, никуда не двигаться. Вы это хотеть, капитан?";
				link.l1 = "Да, именно это от тебя и требуется.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Тичингиту не может встать от цель больше двадцать ярдов. Тогда он промахнуться.";
				link.l1 = "Хорошо, тогда держись на расстоянии в двадцать ярдов.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Тичингиту всё понять. Тичингиту занимать позиция на указанный расстояние.";
			link.l1 = "Хорошо.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Жизнь Тичингиту давно стать неразрывно связана с жизнь капитан. Индеец не забывать, что капитан сделать для Тичингиту. Тичингиту идти за ним, куда сказать капитан, без упрёк и колебаний.";
			link.l1 = "Спасибо, друг Тичингиту! Я рад, что не ошибся в тебе.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Когда мы отправляться?";
			link.l1 = "Немного позже. А пока мы подготовимся к походу.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "21");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tonzag_jailed":
			dialog.text = "Мы заплатить белому человеку сто дублонов, выходить и свободно выполнять работа.";
			link.l1 = "А если нас снова поймают?";
			link.l1.go = "tonzag_jailed_1";
			locCameraFromToPos(-16.78, 1.88, -1.70, true, -5.00, -6.10, -20.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "Мы заплатить тысячу дублонов.";
			link.l1 = "Цинично, но очень точно.";
			link.l1.go = "tonzag_jailed_2";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "Гваделупа быть хуже.";
			link.l1 = "Это чем же?";
			link.l1.go = "tonzag_jailed_3";
		break;
		
		case "tonzag_jailed_3":
			dialog.text = "Там вешать одного Тичингиту. Тут вешать не одного. Один вешаться не так страшно.";
			link.l1 = "А вот это уже просто цинично!";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "Картечь, в упор. Капитан, старик силён, можем спасти, если успеем.";
			link.l1 = "...";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Tichingitu_officer";
			AddDialogExitQuestFunction("Tonzag_JailFear");
		break;
		
		case "tonzag_dead":
			dialog.text = "Белый человек не знает жалость. Много моих, капитан. Очень много. Но твоих больше.";
			link.l1 = "Это твоё племя?";
			link.l1.go = "tonzag_dead_1";
		break;
		
		case "tonzag_dead_1":
			dialog.text = "Некоторый... некоторые из моего.";
			link.l1 = "Держись, друг.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Tichingitu_officer";
		break;
		
	// Тичингиту говорит о том, что нужно спасти Делюка
		case "Del_Deluck":
			dialog.text = "Тоже сто дублон?";
			link.l1 = "А? Ты хотел спросить, буду ли я платить за Делюка, выкупать его из тюрьмы?";
			link.l1.go = "Del_Deluck_1";
		break;
		
		case "Del_Deluck_1":
			dialog.text = "Так.";
			link.l1 = "Сам не знаю... А ты как думаешь?";
			link.l1.go = "Del_Deluck_2";
		break;
		
		case "Del_Deluck_2":
			dialog.text = "Своя надо выручать.";
			link.l1 = "Благородно.";
			link.l1.go = "Del_Deluck_3";
		break;
		
		case "Del_Deluck_3":
			dialog.text = "Или надо оставлять тюрьма. Как в сельва ягуар.";
			link.l1 = "Кому?";
			link.l1.go = "Del_Deluck_4";
		break;
		
		case "Del_Deluck_4":
			dialog.text = "Большой кошка.";
			link.l1 = "Тичингиту, я тебя не понимаю. Скажи прямо: что мне делать в этой непростой ситуации?";
			link.l1.go = "Del_Deluck_5";
		break;
		
		case "Del_Deluck_5":
			dialog.text = "Думать свой голова.";
			link.l1 = "Помог так помог!";
			link.l1.go = "Del_Deluck_6";
		break;
		
		case "Del_Deluck_6":
			DialogExit();
			AddQuestRecord("FolkeDeluc", "2");
			Return_TichingituOfficer();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}