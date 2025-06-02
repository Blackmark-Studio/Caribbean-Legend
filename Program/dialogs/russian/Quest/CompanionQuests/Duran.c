void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Что вам надо?";
			link.l1 = "Ничего.";
			link.l1.go = "exit";
		break;
		
		case "SKD_DomAnri":
			dialog.text = "Приветствую вас в моём доме, господа. Чем могу помочь?";
			link.l1 = "Левассер передаёт вам привет, месье.";
			link.l1.go = "SKD_DomAnri_2";
			StartQuestMovie(true, false, true);
		break;
		
		case "SKD_DomAnri_2":
			dialog.text = "Вот значит как... Алисия! Оставь нас, пожалуйста. У этих господ ко мне есть дело.";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_2_1";
			CharacterTurnToLoc(npchar, "goto", "goto1");
		break;
		case "SKD_DomAnri_2_1":
			StartInstantDialog("SKD_Alisia", "SKD_DomAnri_3", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_3":
			dialog.text = "Но...";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_3_1";
			CharacterTurnToLoc(npchar, "barmen", "stay");
		break;
		case "SKD_DomAnri_3_1":
			StartInstantDialog("SKD_Anri", "SKD_DomAnri_4", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_4":
			dialog.text = "Я люблю тебя, дорогая. Иди же!";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_5";
			CharacterTurnToLoc(npchar, "goto", "goto1");
		break;
		
		case "SKD_DomAnri_5":
			DialogExit();
			locCameraFromToPos(3.47, 2.41, 0.10, false, -1.05, 0.20, -0.07);
			
			sld = CharacterFromID("SKD_Anri");
			CharacterTurnByLoc(sld, "barmen", "stay");
			
			sld = CharacterFromID("SKD_Alisia");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "", "", "", "", -1);
			sld.location = "None";
			sld.lifeday = 0;
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("SKD_DomAnri_2", 4.0);
		break;
		
		case "SKD_DomAnri_6":
			dialog.text = "Чудны дела твои, Господи! Стоило потерять всё, чтобы найти любовь всей жизни на краю света! Господа, я весь ваш. Полагаю, договориться у нас не получится?";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_6_1";
		break;
		case "SKD_DomAnri_6_1":
			StartInstantDialog("Duran", "SKD_DomAnri_7", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_7":
			dialog.text = "Нет, и просить пощады тоже не пытайтесь.";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_7_1";
			CharacterTurnToLoc(npchar, "barmen", "stay");
			locCameraFromToPos(-0.52, 1.47, 0.76, false, -2.52, 0.20, 0.99);
		break;
		case "SKD_DomAnri_7_1":
			StartInstantDialog("SKD_Anri", "SKD_DomAnri_8", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_8":
			dialog.text = "Рыцарю Ордена просить пощады не к лицу.";
			link.l1 = "Бывшему рыцарю, однако.";
			link.l1.go = "SKD_DomAnri_9";
		break;
		
		case "SKD_DomAnri_9":
			dialog.text = "Бюрократам не хватило бы всех чернил мира, чтобы отнять у меня это звание.";
			link.l1 = "В таком случае, докажите это. Но сначала удовлетворите моё любопытство: вы - изменник Короны? Иначе я не понимаю, зачем Левассеру так была нужна ваша жизнь?";
			link.l1.go = "SKD_DomAnri_10";
		break;
		
		case "SKD_DomAnri_10":
			dialog.text = "Я верен своей присяге, месье, так что уж не обессудьте. Скажу только, что один изменник Короны отправил меня устранить другого изменника. И он будет делать это снова и снова, пока у кого-нибудь из более способных, чем я, братьев не получится. Хватит пустословить. Господа, к бою!";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_11";
		break;
		
		case "SKD_DomAnri_11":
			DialogExit();
			EndQuestMovie();
			
			sld = CharacterFromID("Duran");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "SKD_DomAnri_6");
		break;
		
		case "SKD_DomAnri_12":
			dialog.text = "А-ать! Ох, спасибо вам, кэп. Крепкий же парень был! Сам бы я ни за что не одолел его.";
			link.l1 = "Почему-то радости от этой победы у меня немного. Полагаю, мы здесь закончили?";
			link.l1.go = "SKD_DomAnri_13";
		break;
		
		case "SKD_DomAnri_13":
			dialog.text = "Не совсем, сначала надо прибраться и устранить девушку, которая так резво убежала на второй этаж.";
			link.l1 = "Что-о?! Отставить! Совсем разум потерял, Клод? Я не мясник!";
			link.l1.go = "SKD_DomAnri_14";
		break;
		
		case "SKD_DomAnri_14":
			dialog.text = "Да вам и делать-то ничего не придётся, кэп. И потом, это всё из-за вас: зря вы упомянули Левассера при ней.";
			link.l1 = "Это полная чушь и ты сам это знаешь. А если ещё раз посмеешь мне ставить невнятные упрёки, то с рук это тебе не сойдёт.";
			link.l1.go = "SKD_DomAnri_15";
		break;
		
		case "SKD_DomAnri_15":
			dialog.text = "Хе! Виноват, капитан. И правда, Левассер достаточно ясно сказал убрать не только рыцаришку, но и всех его спутников. Всех, понимаете? С такими людьми не шутят и к их требованиям надо относиться серьёзно. Не мешайте мне делать мою работу, кэп. Последнее грязное дело, и дальше я с вами до конца, клянусь!";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				notification("Проверка чести пройдена", "None");
				notification("Вызывающий доверие", "Trustworthy");
				link.l1 = "(Вызывающий доверие) (Честь) Ты как-то сказал, что суждено мне летать высоко, и ты был рад поспособствовать этому.";
				link.l1.go = "SKD_DomAnri_VD";
			}
			else
			{
				notification("Слишком низкий уровень чести! ("+XI_ConvertString(GetReputationName(71))+")", "None");
				notification("Не открыта способность", "Trustworthy");
			}
			link.l2 = "Чёрт с тобой! Делай свое грязное дело. Клятву твою я принимаю - и лучше бы тебе к ней отнестись смертельно серьёзно. Мы поняли друг друга?";
			link.l2.go = "SKD_DomAnri_DuranDruzhba";
			link.l3 = "Не такой ценой, Клод. Я не позволю тебе убить эту девушку.";
			link.l3.go = "SKD_DomAnri_DuranDraka";
		break;
		
		case "SKD_DomAnri_DuranDraka":
			dialog.text = "Хе! Сколько верёвочке не виться... Видать, судьбой было суждено нам укокошить друг друга, да, кэп?";
			link.l1 = "Видимо, так. Продолжим на чём остановились?";
			link.l1.go = "SKD_DomAnri_DuranDraka_2";
		break;
		
		case "SKD_DomAnri_DuranDraka_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			
			RemovePassenger(pchar, npchar);
			npchar.SaveItemsForDead = true;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "SKD_DomAnri_DuranDraka");
		break;
		
		case "SKD_DomAnri_DuranDruzhba":
			dialog.text = "Так точно, капитан!";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_2";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_2":
			DialogExit();
			
			LocatorReloadEnterDisable("PortRoyal_houseSp1", "reload2", true);
			sld = CharacterFromID("Duran");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("PortRoyal_town", true);
			
			PChar.quest.SKD_DomAnri_DuranDruzhba.win_condition.l1 = "location";
			PChar.quest.SKD_DomAnri_DuranDruzhba.win_condition.l1.location = "PortRoyal_town";
			PChar.quest.SKD_DomAnri_DuranDruzhba.win_condition = "SKD_DomAnri_DuranDruzhba";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_3":
			dialog.text = "Дело сделано, кэп. Удивила она меня, конечно...";
			link.l1 = "Слушать об этом не хочу. Я слово своё сдержал. Теперь твоя очередь.";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_4";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_4":
			dialog.text = "Золото - это одно, но подставить свою шкуру под удар ради простого наёмника - это дорогого стоит. Я с вами до конца, капитан.";
			link.l1 = "В таком случае, здесь мы закончили.";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_5";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_5":
			dialog.text = "Так точно!";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_6";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_6":
			DialogExit();
			
			EndQuestMovie();
			locCameraTarget(PChar);
			locCameraFollow();
			LAi_LocationDisableOfficersGen("PortRoyal_town", false);
			chrDisableReloadToLocation = false;
			AddQuestRecord("TheFormerKnight", "3");
			CloseQuestHeader("TheFormerKnight");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			
			sld = CharacterFromID("Duran");	//Клод Дюран становится постоянным офицером
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.Dialog.CurrentNode = "hired";
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			
			pchar.questTemp.SKD_DuranDruzhba = true;
			pchar.questTemp.SKD_DevushkaUbita = true;
			sld.reputation = sti(sld.reputation) - 15;
			OfficersFollow();
		break;
		
		case "SKD_DomAnri_VD":
			dialog.text = "Было дело. К чему вы это, кэп?";
			link.l1 = "Докажи мне, что эти слова были не пустым звоном. Я - человек чести. Хочешь заслужить место в моей команде? Иметь долю в будущей добыче? Выполняй мои приказы. Не трогай девушку. Почему? Потому что иначе ты навсегда останешься обыкновенным мясником, а у меня для таких людей места нет.";
			link.l1.go = "SKD_DomAnri_VD_2";
		break;
		
		case "SKD_DomAnri_VD_2":
			dialog.text = "Второй раз мы с вами готовимся схватиться насмерть, кэп\nИ снова вы побеждаете благодаря своему дару чесать языком! Ха-ха! Ну вы и сказанули! Ладно, чёрт с ней с девчонкой. Я же не зверь в самом деле. Берёте в команду?";
			link.l1 = "Добро пожаловать, Клод. Теперь уже - по-настоящему.";
			link.l1.go = "SKD_DomAnri_VD_3";
		break;
		
		case "SKD_DomAnri_VD_3":
			dialog.text = "Так точно, капитан!";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_VD_4";
		break;
		
		case "SKD_DomAnri_VD_4":
			DialogExit();
			AddQuestRecord("TheFormerKnight", "2");
			CloseQuestHeader("TheFormerKnight");
			chrDisableReloadToLocation = false;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			
			sld = CharacterFromID("Duran");	//Клод Дюран становится постоянным офицером
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.Dialog.CurrentNode = "hired";
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			
			pchar.questTemp.SKD_DuranDruzhba = true;
			sld.reputation = 60;
			OfficersFollow();
		break;
		
		case "SKD_KlodDuran":
			dialog.text = "Есть дело, кэп.";
			Link.l1 = "Дай догадаюсь: опять будешь угрожать отставкой и требовать прибавки?";
			Link.l1.go = "SKD_KlodDuran_1";
		break;
		
		case "SKD_KlodDuran_1":
			dialog.text = "Хе! Не в этот раз... Ого, как напряглись! Не переживайте, капитан, пока вы платите - я весь ваш... в разумных пределах, конечно. Нашему брату наёмнику иначе и не выжить. А платят даже лучшим из нас гроши.";
			link.l1 = "Чем прибедняться, лучше давай сразу к делу.";
			link.l1.go = "SKD_KlodDuran_2";
		break;
		
		case "SKD_KlodDuran_2":
			dialog.text = "Помните ту стерву с Тортуги?";
			link.l1 = "Марселину? Жену губернатора? Такую не забудешь.";
			link.l1.go = "SKD_KlodDuran_3";
		break;
		
		case "SKD_KlodDuran_3":
			dialog.text = "Я ведь не случайно попал в дом Левассера. У меня были дела с этим мерзавцем и еретиком...";
			link.l1 = "Довольно странно с твоей стороны так пренебрежительно высказываться о сильных мира сего, Клод.";
			link.l1.go = "SKD_KlodDuran_4";
		break;
		
		case "SKD_KlodDuran_4":
			dialog.text = "А? Хе! Левассер - это сущий дьявол! Он намного хуже даже кормящихся с его рук пиратов!";
			link.l1 = "Ты сам только что сказал, что вёл с ним дела. Не слишком ли это лицемерно с твоей стороны?";
			link.l1.go = "SKD_KlodDuran_5";
		break;
		
		case "SKD_KlodDuran_5":
			dialog.text = "Я не ангел, кэп, и зарабатываю на жизнь, убивая тех, на кого укажут пальцем. За это вы меня и цените, разве нет? Но даже у таких людей, как я, кровь стынет в жилах от слухов о том, что творят с женщинами на Тортуге в многочисленных логовах Левассера!";
			link.l1 = "Слухи меня не интересуют. Этот человек - дворянин и слуга Короля, и заслуживает уважения.";
			link.l1.go = "SKD_KlodDuran_6";
		break;
		
		case "SKD_KlodDuran_6":
			dialog.text = "И поэтому вы ограбили этого слугу Короля и развлеклись с его жёнушкой? Хе! Как угодно, кэп. Значит, ближе к делу. Его превосходительство заказал мне найти и убить одного человека. Достаточно обыденное задание, пусть и нечасто оно поступает от настолько высокого лица, да ещё и лично.";
			link.l1 = "И что ты хочешь? Отпустить тебя, чтобы ты сдержал своё слово и убил этого человека?";
			link.l1.go = "SKD_KlodDuran_7";
		break;
		
		case "SKD_KlodDuran_7":
			dialog.text = "Я хочу, чтобы вы помогли мне это сделать, кэп. Когда дело на Тортуге для меня обернулось худо, я согласился пойти к вам на службу, но не видать мне покоя, пока я не выполню эту работу. Левассер меня просто убьёт, если узнает. Да и непрофессионально это.";
			link.l1 = "А крутить шашни с женой заказчика - это профессионально? Очень странно слышать от тебя подобную просьбу, особенно если вспомнить начало нашего разговора, где ты достаточно точно описал суть наших взаимоотношений. Кровь за золото, так оно было?";
			link.l1.go = "SKD_KlodDuran_8";
		break;
		
		case "SKD_KlodDuran_8":
			dialog.text = "Если выручите, то получите не просто мою саблю, а ещё и мою верность. Я-то сразу вижу, что суждено летать вам высоко, кэп. Буду рад поспособствовать этому.";
			link.l1 = "Не скрою, я бы предпочёл, чтобы человек твоих способностей и дальше продолжал прикрывать мне спину. Где найти этого несчастного?";
			link.l1.go = "SKD_KlodDuran_10";
			link.l2 = "Твоей сабли мне пока хватит. Я не наёмный убийца. Вольно, офицер!";
			link.l2.go = "SKD_KlodDuran_9";
		break;
		
		case "SKD_KlodDuran_9":
			dialog.text = "Так точно, кэп. Спросить всё равно стоило.";
			link.l1 = "...";
			link.l1.go = "SKD_KlodDuran_9_1";
		break;
		
		case "SKD_KlodDuran_9_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.loyality = makeint(npchar.loyality) + 10;
			Return_DurandOfficer();
		break;
		
		case "SKD_KlodDuran_10":
			dialog.text = "Хе! В этом-то и проблема, кэп. Я знаю только то, что он бывший рыцарь Мальтийского Ордена и сейчас в бегах где-то на территории англичан. Человек знатного происхождения, так что в лачуге жить не будет.";
			link.l1 = "Рыцарь Ордена?";
			link.l1.go = "SKD_KlodDuran_11";
		break;
		
		case "SKD_KlodDuran_11":
			dialog.text = "Бывший. Да уж, и я уже тысячу раз успел пожалеть, что взял эту работу. Рыцари - парни крепкие, так что серьёзную драку я вам гарантирую.";
			link.l1 = "Не нравится мне это, но давай попробуем. Значит: не бедный человек, дворянин и прячется у англичан? Левассер не сказал, почему его надо убрать?";
			link.l1.go = "SKD_KlodDuran_12";
		break;
		
		case "SKD_KlodDuran_12":
			dialog.text = "Как же, скажет он! Но дело явно политическое, иначе послал бы солдат.";
			link.l1 = "Попробую, но ничего не обещаю.";
			link.l1.go = "SKD_KlodDuran_13";
		break;
		
		case "SKD_KlodDuran_13":
			dialog.text = "Спасибо, кэп.";
			link.l1 = "...";
			link.l1.go = "SKD_KlodDuran_14";
		break;
		
		case "SKD_KlodDuran_14":
			DialogExit();
			SetQuestHeader("TheFormerKnight");
			AddQuestRecord("TheFormerKnight", "1");
			chrDisableReloadToLocation = false;
			npchar.loyality = makeint(npchar.loyality) + 15;
			Return_DurandOfficer();
			PChar.quest.SKD_DomAnri.win_condition.l1 = "location";
			PChar.quest.SKD_DomAnri.win_condition.l1.location = "PortRoyal_houseSp1";
			PChar.quest.SKD_DomAnri.win_condition = "SKD_DomAnri";
			pchar.GenQuestBox.PortRoyal_houseSp1.box1.items.chest = 1;
		break;
		
	}
} 
