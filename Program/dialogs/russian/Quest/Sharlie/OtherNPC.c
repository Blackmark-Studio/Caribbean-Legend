// диалог прочих и малозначимых НПС
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp;
	string attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Вы что-то хотели?";
			link.l1 = "Да нет, ничего.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// --> матрос на корабле, прибытие в Сен-Пьер
		case "Startsailor":
			dialog.text = "Эх, первым делом, как сойду на берег - напьюсь!.. Просыпайтесь, месье... как вас там... Прибыли!";
			link.l1 = "А-ах! Что, уже? Чёртова жара...";
			link.l1.go = "Startsailor_1";
			link.l2 = "Шарль де Мор! Дворянин, знаете ли. Как вы вообще можете выпивать в такую жару? Я бы лучше воды выпил, ей-Богу.";
			link.l2.go = "Startsailor_1a";
		break;
		
		case "Startsailor_1":
			dialog.text = "Привыкайте, месье, тут другой погоды и не бывает... Разве что хуже.";
			link.l1 = "Куда уж хуже! Под одной полотняной рубашкой пот катится градом!";
			link.l1.go = "Startsailor_2";			
		break;
		
		case "Startsailor_2":
			dialog.text = "Не забудьте свои вещи... Поторопитесь, месье, шлюпка ждать не станет. Вы же не хотите добираться до берега вплавь?";
			link.l1 = "Да, я уже готов... Где моя шпага? Ах, вот...";
			link.l1.go = "Startsailor_3";			
		break;
		
		case "Startsailor_3":
			dialog.text = "Да, тут вам не Европа... Будьте осторожны, месье. Здесь в последнее время не любят тех, кто задаёт слишком много вопросов. Времена нынче, знаете ли, неспокойные. Говорят, что остров продали каким-то фанатикам веры. Я до сих пор не замечал каких-то перемен в привычном укладе жителей Мартиники. Но за время моего отсутствия многое могло измениться.";
			link.l1 = "Фанатики веры? Что за вздор!";
			link.l1.go = "Startsailor_4";			
		break;
		
		case "Startsailor_4":
			dialog.text = "Вздор, или не вздор, а слухи ходят. Да и без этого напастей хватает. Людоеды в джунглях, лихорадка, пираты в море, бандиты в переулках...";
			link.l1 = "Ну, началось... Страсти-то какие. Пока единственные напасти, которые я встретил - это жара и москиты... Ладно, я готов. Идём?";
			link.l1.go = "Startsailor_5";			
		break;
		
		case "Startsailor_5":
			dialog.text = "Поднимайтесь наверх и ступайте в шлюпку, месье. Добро пожаловать на Карибы!";
			link.l1 = "";
			link.l1.go = "Startsailor_6";			
		break;
		
		case "Startsailor_1a":
			dialog.text = "Другой погоды тут и не бывает, ваше благородие. Разве что ещё хуже.";
			link.l1 = "Погода просто отвратительна, как и моя компания за эти месяцы. Надеюсь, на Архипелаге найдутся люди достойные.";
			link.l1.go = "Startsailor_2a";
			AddCharacterExpToSkill(pchar, "Leadership", 10);
		break;
		
		case "Startsailor_2a":
			dialog.text = "Тогда, думаю, мы все будем рады тому, что вы наконец-то нас покинете, месье. Шлюпка ждёт. Из панталон от радости не выпрыгните. Вещи не оставляйте - корабль отправится дальше, и тогда вы можете смело о них забыть.";
			link.l1 = "Как же, оставлю я вам их на радость. Песо, шпага - вроде не обворовали.";
			link.l1.go = "Startsailor_3a";			
		break;
		
		case "Startsailor_3a":
			dialog.text = "Мы, конечно, ребята честные, но верно мыслите - всегда следите за вещами, а то и карманы обчистить могут. Впрочем, как и в старушке Европе. Да и везде вообще. Но здесь вам не как дома. Неспокойно у нас сейчас. Какие-то фанатики основали здесь базу. Но люди говорят, что на самом деле они тайно купили весь остров. Так что смотрите в оба и не привлекайте внимания.";
			link.l1 = "Фанатики да целый остров? Какая чушь!";
			link.l1.go = "Startsailor_4a";			
		break;
		
		case "Startsailor_4a":
			dialog.text = "Слухи такие ходят. Скажите спасибо, что поделился и обеспокоился вашим пребыванием здесь. А то того и гляди, завянет нежная гасконская роза под нашим палящим солнцем. Чушь или нет, а глядите в оба - и без фанатиков у нас хватает всякого. Бандиты в подворотнях и сельве, пираты в море, людоеды краснокожие...";
			link.l1 = "Но-но! Привыкну. Мне, может, пока что и жарковато, но я закалён солнцем дома, в отличие от, например, нормандских. А если с чем-то можно справиться клинком - за мной не заржавеет. Но вот москиты - просто мука! Ну что же, все мои вещи точно на месте. Шлюпка уже ждёт, говорите?";
			link.l1.go = "Startsailor_5a";			
		break;
		
		case "Startsailor_5a":
			dialog.text = "Ждёт не дождётся. Надеюсь, сами дойдёте, месье? Вам наверх, а дальше не заблудитесь, надеюсь. А, и добро пожаловать на Архипелаг, хе-хе.";
			link.l1 = "Да уж, спасибо. Радует только, что я здесь ненадолго.";
			link.l1.go = "Startsailor_6";			
		break;
		
		case "Startsailor_6":
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_StartGameInMartinique");
		break;
		// <-- матрос на корабле, прибытие в Сен-Пьер
		
		// горожанин знает Мишеля
		case "Benuatalker":
			DelLandQuestMark(npchar);
			dialog.text = LinkRandPhrase("Приветствую, капитан! Что вам угодно?","Здравствуйте, судар"+GetSexPhrase("ь","ыня")+". Чем могу быть вам полезен?","Доброго дня, уважаем"+GetSexPhrase("ый","ая")+". Вы что-то хотели?");
			link.l1 = "Извините, "+GetAddress_FormToNPC(NPChar)+" вы не знаете, где я могу найти человека - Мишеля де Монпе? Он должен быть где-то у вас в городе.";
            link.l1.go = "Benuatalker_1";
		break;
		
		case "Benuatalker_1":
			dialog.text = "Хм... Вижу, вы в нашем городе приезжий, раз совершенно без опаски ведёте подобные расспросы... Я советую вам их прекратить, не то накличете беду на свою голову. А насчёт вашего вопроса... поговорите с аббатом Бенуа. Вы сможете найти его в церкви.";
			link.l1 = "Спасибо!";
            link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddDialogExitQuest("Sharlie_SetBenua");
			QuestPointerToLoc("FortFrance_town", "reload", "reload7_back");
		break;
		
		// --> арест в резиденции
		case "Sharlie_arest":
			dialog.text = "Немедленно сдайте оружие, месье, и следуйте за нами!";
			link.l1 = "Вот так влип...";
			link.l1.go = "Sharlie_arest_1";
			if (CheckCharacterItem(PChar, "knife_03")) pchar.Sharlie.KnifeMonpe = true;
		break;
		
		case "Sharlie_arest_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("FortFrance_prison", "goto", "goto9", "Puancie_InJail");
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			RecalculateJumpTable();
			RemoveAllCharacterItems(PChar, true);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "Puancie_Jail"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "FortFrance_prison", "goto", "goto13");
		break;
		// арест в резиденции
		
		// --> офицер базы
		case "Maltie_officer":
			ref location = &Locations[FindLocation(pchar.location)];
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "begin")
			{
				dialog.text = "Рад вас видеть, месье де Мор. По какому вопросу пожаловали?";
				link.l1 = TimeGreeting()+", офицер. Я хочу поговорить о моём брате, Мишеле де Монпе. Причём неофициально. Мне хотелось бы немного больше узнать о его службе здесь.";
				link.l1.go = "spanish";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "think")
			{
				dialog.text = "Ну, как прошёл допрос? Много нового узнали?";
				link.l1 = "Настолько много, что я забираю этого испанца к себе на корабль. Это важный свидетель, и он должен быть доставлен на Сент-Кристофер для дальнейших разбирательств.";
				link.l1.go = "spanish_10";
				break;
			}
			if (!CheckAttribute(location, "first_meeting"))
			{
				DelLandQuestMark(npchar);
				dialog.text = "Месье, как вы попали сюда? По какому делу вы здесь?";
				link.l1 = "Я пришёл, чтобы увидеть своего брата, Мишеля де Монпе.";
				link.l1.go = "Maltie_officer_1";
				location.first_meeting = true;
			}
			else
			{
				dialog.text = "Месье, я прошу вас не забывать, что вы находитесь на военном объекте. Так что ведите себя соответствующим образом.";
				link.l1 = "Да, конечно, офицер.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Maltie_officer";
			}
			
			if (SandBoxMode)
			{
				dialog.text = ""+GetSexPhrase("Месье","Мадмуазель")+", я прошу вас не забывать, что вы находитесь на военном объекте. Так что ведите себя соответствующим образом.";
				link.l1 = "Да, конечно, офицер.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Maltie_officer";
			}
		break;
		
		case "Maltie_officer_1":
			dialog.text = "Мишель де Монпе находится под стражей в одной из камер, заключён по личному приказу шевалье Филиппа де Пуанси. Спуститесь на нижний ярус, там отыщете казематы. Думаю, не заблудитесь.";
			link.l1 = "Спасибо!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Maltie_officer";
			QuestPointerToLoc("FortFrance_Dungeon", "quest", "quest1");
		break;
		// офицер базы
		
		// --> солдаты базы
		case "Maltie_soldier":
			dialog.text = "Здравствуйте, "+GetAddress_Form(NPChar)+". Я чем-нибудь могу помочь вам?";
			link.l1 = "Благодарю, солдат. Увы, помочь вы мне ничем не можете...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Maltie_soldier";
		break;
		// --> солдаты базы
		
		// --> мальтиец-проводник
		case "Sharlie_maltie":
			dialog.text = "Я здесь, месье. Так это вы ищете Мишеля де Монпе? И вы - его брат?";
			link.l1 = "Да, это так. Я его брат Шарль. Мне нужно срочно увидеть Мишеля! Он попал в неприятности, да?";
			link.l1.go = "Sharlie_maltie_1";			
		break;
		
		case "Sharlie_maltie_1":
			dialog.text = "К сожалению, да, месье. Мишель арестован и находится в нашей тюрьме. Приказ о его помещении под стражу выдан и подписан самим шевалье де Пуанси, генерал-губернатором французских колоний архипелага. Мы все были буквально ошарашены этим\nВаш брат - образец мужественности, решительности и отваги, гордость нашего Ордена, и тут - такое! Угнетает также то, что мы, его друзья, вынуждены теперь запирать за ним решётку каземата и смотреть, как за преступником! Мы делаем всё, чтобы облегчить его участь, но... тюрьма есть тюрьма.";
			link.l1 = "Так в чём же его обвиняют? Он совершил преступление?";
			link.l1.go = "Sharlie_maltie_1_1";			
		break;
		
		case "Sharlie_maltie_1_1":
			dialog.text = "Вздор! Чистой воды вздор! Они обвинили Мишеля в растрате и присвоении государственных денег. Это полная чушь! Мы все уверены в том, что это какие-то грязные политические игры. Мишель участвовал в секретных операциях, проводимых Орденом, и, видимо, узнал больше, чем положено было знать\nИли что-то ещё. Но украсть деньги! В это никто не верит. Это предлог, а не причина, причём грубый и нелепый предлог! Но довольно слов. Ваш брат очень ждал вас, и, думаю, он сам вам всё расскажет.";
			link.l1 = "Хорошо. Где находится тюрьма?";
			link.l1.go = "Sharlie_maltie_1_2";
		break;
		
		case "Sharlie_maltie_1_2":
			dialog.text = "Это на нашей подземной базе, тут, в городе. Следуйте за мной, я вас проведу!";
			link.l1 = "...";
			link.l1.go = "Sharlie_maltie_2";
		break;
		
		case "Sharlie_maltie_2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "FortFrance_town", "officers", "reload7_1", "Maltie_GoTown", -1);
		break;
		
		case "Sharlie_maltie_3":
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Maltie_officer"), "questmarkmain");
			dialog.text = "Вот мы и пришли. Это наша база - Ордена Мальтийских рыцарей. Казематы находятся внизу. Пройдите мимо столовой и комнаты для молитв и спуститесь по лестнице вниз. Там вы найдёте коридор с зарешёченными камерами. В одной из них и содержится ваш несчастный брат\nСтупайте, Шарль, и помогите нашему Мишелю! Он ни в чём не виноват, здесь все готовы подтвердить это под присягой...";
			link.l1 = "Я затем и прибыл в эту глушь, чтобы помочь брату. Надеюсь, мне удастся хоть что-то сделать.";
			link.l1.go = "Sharlie_maltie_4";
		break;
		
		case "Sharlie_maltie_4":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "none", -1);
		break;
		
		//belamour cle -->
		case "Sharlie_maltieA":
			dialog.text = "Так это вы ищете Мишеля де Монпе? И вы - его брат?";
			link.l1 = "Да, это так. Я его брат Шарль. Мне нужно срочно увидеть Мишеля! Он попал в неприятности, да?";
			link.l1.go = "Sharlie_maltie_1a";			
		break;
		
		case "Sharlie_maltie_1a":
			dialog.text = "К сожалению, да, месье. Мишель арестован и находится в нашей тюрьме. Приказ о его помещении под стражу выдан и подписан самим шевалье де Пуанси, генерал-губернатором французских колоний архипелага. Мы все были буквально ошарашены этим\nВаш брат - образец мужественности, решительности и отваги, гордость нашего Ордена, и тут - такое! Угнетает также то, что мы, его друзья, вынуждены теперь запирать за ним решётку каземата и смотреть, как за преступником! Мы делаем всё, чтобы облегчить его участь, но... тюрьма есть тюрьма.";
			link.l1 = "Так в чём же его обвиняют? Он совершил преступление?";
			link.l1.go = "Sharlie_maltie_1_1a";			
		break;
		
		case "Sharlie_maltie_1_1a":
			dialog.text = "Вздор! Чистой воды вздор! Они обвинили Мишеля в растрате и присвоении государственных денег. Это полная чушь! Мы все уверены в том, что это какие-то грязные политические игры. Мишель участвовал в секретных операциях, проводимых Орденом, и, видимо, узнал больше, чем положено было знать\nИли что-то ещё. Но украсть деньги! В это никто не верит. Это предлог, а не причина, причём грубый и нелепый предлог! Но довольно слов. Ваш брат очень ждал вас, и, думаю, он сам вам всё расскажет.";
			link.l1 = "Хорошо. Где находится тюрьма?";
			link.l1.go = "Sharlie_maltie_1_2a";
		break;
		
		case "Sharlie_maltie_1_2a":
			dialog.text = "Это на нашей подземной базе, тут, в городе. Следуйте за мной, я вас проведу!";
			link.l1 = "...";
			link.l1.go = "Sharlie_maltie_2a";
		break;
		
		case "Sharlie_maltie_2a":
			DialogExit();
			//LAi_ActorGoToLocation(npchar, "reload", "reloadPr1", "FortFrance_Dungeon", "reload", "reload1", "", -1);
			Pchar.quest.Sharlie_Maltie.win_condition.l1 = "location";
			Pchar.quest.Sharlie_Maltie.win_condition.l1.location = "FortFrance_town";
			Pchar.quest.Sharlie_Maltie.win_condition = "Maltie_GoBasement";
			QuestPointerDelLoc("FortFrance_prison", "reload", "reload1");
		break;
		//<-- cle
		// мальтиец-проводник
		
		// --> найм матросов
		case "Sharlie_sailor":
			DelLandQuestMark(npchar);
			dialog.text = "А потом он свесился за борт... и выдал столько, что Карибскому Морю тоже поплохело! Ха-ха-ха!";
			link.l1 = "Алонсо?";
			link.l1.go = "Sharlie_sailor_1";
		break;
		
		case "Sharlie_sailor_1":
			dialog.text = "О! Шарль, а я как раз рассказываю парням про наши приключения!";
			link.l1 = "Я заметил. Слушай, Алонсо. Я тут капитаном заделался...";
			link.l1.go = "Sharlie_sailor_2";
		break;
		
		case "Sharlie_sailor_2":
			dialog.text = "Уже? Я думал, вам потребуется где-то с месяц, ха-ха!";
			link.l1 = "Я серьёзно с тобой разговариваю!";
			link.l1.go = "Sharlie_sailor_3";
		break;
		
		case "Sharlie_sailor_3":
			dialog.text = "Если бы дело касалось только меня лично, то я бы к вам пошёл сразу, без всякой задней мысли. Но со мной - ещё сорок душ с 'Улисса'. Парни доверили мне своё будущее, и я должен быть уверен, что вы их не подведёте\n"+
			"Что у вас за корабль?";
			link.l1 = "Корабль как корабль, "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype), "Name")))+". А это так важно?";
			link.l1.go = "Sharlie_sailor_4";
		break;
		
		case "Sharlie_sailor_4":
			dialog.text = "Ну знаете, после 'Улисса' не хотелось бы служить на каком-то баркасе или тартане. Ваш корабль мы уже видели и парням он понравился\n"+
			"Теперь денежный вопрос. Мы возьмём 4800 песо авансом. Ну а после - как везде. Лишнего не попросим, за это не беспокойтесь. Потянете?";
			if (sti(Pchar.money) >= 4800)
			{
				link.l1 = "Ну что же, тогда - по рукам! Вот ваши монеты.";
				link.l1.go = "Sharlie_sailor_5";
			}
			link.l2 = "К сожалению, у меня нет пока такой суммы.";
			link.l2.go = "Sharlie_sailor_nomoney";
		break;
		
		case "Sharlie_sailor_5":
			if (GetSquadronGoods(pchar, GOOD_FOOD) < 20 || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < 30)
			{
				dialog.text = "А запасы продовольствия у вас есть в трюме, капитан? И лекарства? Нет? Ну, тогда сначала закупите хотя бы какой-то минимум - тогда и возвращайтесь.";
				link.l1 = "Хм. Ты прав. Хорошо, я так и сделаю.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_sailor_again";
				NewGameTip("Быстрый переход до магазина можно сделать через меню действий (ENTER). Экономит время!");
			}
			else
			{
				AddMoneyToCharacter(pchar, -4800);
				dialog.text = "Ба! Поздравляю... капитан! Я немедленно собираю ребят и мы сейчас же отправимся на ваш корабль.";
				link.l1 = "Рад продолжить наше приключение, Алонсо. Готовьте судно к выходу в море!";
				link.l1.go = "Sharlie_sailor_6";
			}
		break;
		
		case "Sharlie_sailor_6":
			DialogExit();
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, "Fortfrance_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
			SetCrewQuantityOverMax(PChar, 40);
			pchar.Ship.Crew.Morale = 50;
			pchar.Ship.Crew.Exp.Sailors = 50;
			pchar.Ship.Crew.Exp.Cannoners = 50;
			pchar.Ship.Crew.Exp.Soldiers = 50;
			AddQuestRecord("Sharlie", "7");
			pchar.questTemp.Sharlie = "skiper";
			DeleteAttribute(pchar, "GenQuest.CannotWait");//снимаем запрет, если не был снят раньше
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
		break;
		
		case "Sharlie_sailor_nomoney":
			dialog.text = "Ну, тогда как соберёте - возвращайтесь. Думаю, вы сможете найти меня здесь, в таверне - пока никаких кораблей на рейде нет, службы не предвидится. Будем и дальше пропивать свои монеты, ха-ха!";
			link.l1 = "Хорошо. Я постараюсь вернуться как можно скорее.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Sharlie_sailor_again";
		break;
		
		case "Sharlie_sailor_again":
			dialog.text = "Ну что, капитан, вы готовы нанять меня и моих товарищей на своё судно? Нам не терпится снова выйти в море! Да и в карманах уже начинает ветер гулять...";
			if (sti(Pchar.money) < 4800)
			{
				link.l1 = "Нет пока, я ещё подготавливаюсь.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_sailor_again";
			}
			else
			{
				link.l1 = "Да. Получите ваш аванс. Теперь вы у меня на службе.";
				link.l1.go = "Sharlie_sailor_5";
			}
		break;
		// найм матросов
		
		// наводчик на штурмана
		case "skipertalker":
			DelLandQuestMark(npchar);
			dialog.text = LinkRandPhrase("Приветствую, капитан! Что вам угодно?","Здравствуйте, "+GetSexPhrase("сударь","сударыня")+". Чем могу быть вам полезен?","Доброго дня, уважаем"+GetSexPhrase("ый","ая")+". Вы что-то хотели?");
			link.l1 = RandPhraseSimple("У меня есть вопрос к тебе.", "Мне нужна информация о делах в этой колонии.");
			link.l1.go = "skipertalker_1";
			link.l2 = "Просто решил"+GetSexPhrase("","а")+" поздороваться. Бывай!";
			link.l2.go = "exit";
			NextDiag.TempNode = "skipertalker";
		break;
		
		case "skipertalker_1":
			dialog.text = RandPhraseSimple("Какие вопросы?", "Что вам угодно?");
			link.l1 = "Послушайте, "+GetAddress_FormToNPC(NPChar)+", тут такое дело... Я ищу штурмана на свой корабль - может, знаете подходящего человека в вашем городе?";
			link.l1.go = "skipertalker_2";
		break;
		
		case "skipertalker_2":
			dialog.text = "Штурман? Хм... Есть тут такой... вот только незадача - в тюрьме он сейчас. За долги его посадили, наверное, уже месяц в каземате, бедолага.";
			link.l1 = "За долги? Хм... Как его зовут, не подскажете?";
			link.l1.go = "skipertalker_3";
		break;
		
		case "skipertalker_3":
			dialog.text = "Фульк Делюк его зовут. Спросите у коменданта в тюрьме. Но только не думаю, что его отпустят так просто, разве что вы заплатите за него долг, ха-ха!";
			link.l1 = "Возможно, и заплачу. Благодарю за информацию, вы мне очень помогли!";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			pchar.questTemp.Sharlie = "jailskiper";
			AddQuestRecord("Sharlie", "8");
			LocatorReloadEnterDisable("Fortfrance_town", "reload_jail", false);
			SetFunctionLocationCondition("FortfranceJailOff_AddQuestMark", "fortfrance_prison", false);
		break;
		
		// --> штурман
		case "Folke":
			dialog.text = "Чем обязан такому вниманию, месье?";
			link.l1 = "Приветствую, Фульк. Всё очень просто - у меня есть корабль, но нет штурмана, а он мне очень нужен. Поэтому я и выкупил тебя из долговой ямы...";
			link.l1.go = "Folke_1";
		break;
		
		case "Folke_1":
			dialog.text = "Вы хотите сказать, что вытащили меня отсюда, чтобы взять к себе на службу?";
			link.l1 = "Именно так. Думаю, ты быстро отработаешь затраченные на тебя деньги. А затем... впрочем, там и посмотрим.";
			link.l1.go = "Folke_2";
		break;
		
		case "Folke_2":
			dialog.text = "Благодарю вас, месье. Мне чертовски опостылели эти казематы. Я с удовольствием вновь поднимусь на палубу корабля. Эх, море, море...";
			link.l1 = "Я рад, что мы поняли друг друга, Фульк. Да, ещё: у тебя есть какие-либо познания в морском деле, кроме управления кораблём?";
			link.l1.go = "Folke_3";
		break;
		
		case "Folke_3":
			dialog.text = "Всего понемногу, кэп. Когда я служил наёмником в голландском флоте, я научился наводить орудия и грамотно перезаряжать их. Так что в бою могу занять место на орудийной палубе. А вот торговаться c купцами или забрасывать абордажные крючья - это совсем не моё.";
			link.l1 = "Понятно. Теперь следуй за мной на корабль, посмотришь опытным глазом, что да как. А потом я хочу как можно скорее отправиться на Гваделупу.";
			link.l1.go = "Folke_4";
		break;
		
		case "Folke_4":
			dialog.text = "Слушаюсь, кэп! И вот ещё, небольшой презент за то, что вытаскиваете меня из этой безнадёги.";
			link.l1 = "Спасибо, Фульк. Увидимся на корабле.";
			link.l1.go = "Folke_5";
			Log_Info("Получен амулет 'Чётки торговца'");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "obereg_8");
			if(CheckAttribute(pchar,"systeminfo.tutorial.Amulet"))
			{
				DoQuestFunctionDelay("Tutorial_Amulet", 0.1);
			}
		break;
		
		case "Folke_5":
			DialogExit();
			EndQuestMovie();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			AddQuestRecord("Sharlie", "10");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Sharlie_skiper.win_condition.l1 = "location";
			pchar.quest.Sharlie_skiper.win_condition.l1.location = "My_Cabin_Small";
			pchar.quest.Sharlie_skiper.function = "Sharlie_SkiperTalk";
			//прерывание на засаду пиратов - принудительный квест
			pchar.quest.Sharlie_seabattle.win_condition.l1 = "location";
			pchar.quest.Sharlie_seabattle.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_seabattle.function = "SharlieSeabattle_agent";
			
			pchar.quest.NewGameTip2.win_condition.l1 = "location";
			pchar.quest.NewGameTip2.win_condition.l1.location = "Martinique";
			pchar.quest.NewGameTip2.function = "ShowNewGameTip";
			pchar.quest.NewGameTip2.text = "Ваш будущий штурман ждёт вас в вашей каюте, Используйте меню действий (ENTER) для перехода в каюту.";
		break;
		
		case "Folke_6":
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин 250912
			dialog.text = "Отличный люггер, капитан! Весьма и весьма достойный корабль. На таком можно без опаски не то что на Гваделупу отправляться, но хоть через всё Карибское море.";
			link.l1 = "Очень хорошо. По крайней мере, деньги не пропали даром... Какие-нибудь советы перед тем как отправиться в путь будут, Фульк?";
			link.l1.go = "Folke_8";
		break;
		
		case "Folke_7":
			dialog.text = "Да уж, этот шлюп основательно повреждён, капитан. Для перехода до Гваделупы он с большего годен, но по прибытии в Бас-Тер нужно сразу поставить его на ремонт.";
			link.l1 = "У меня не было выбора - на верфи предложили только эту посудину. Да ещё и содрали приличную сумму, а чинить её, понимаешь ли, времени у них нет... Какие-нибудь советы перед тем как отправиться в путь будут, Фульк?";
			link.l1.go = "Folke_8";
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_BALLS) >= 80) && (GetSquadronGoods(pchar, GOOD_GRAPES) >= 80) && (GetSquadronGoods(pchar, GOOD_KNIPPELS) >= 80) && (GetSquadronGoods(pchar, GOOD_BOMBS) >= 80) && (GetSquadronGoods(pchar, GOOD_POWDER) >= 180);
		case "Folke_8":
			if (bOk)
			{
				dialog.text = "Ну, боеприпасами вы запаслись достаточно, капитан. Этого арсенала нам хватит вполне, только не забывайте своевременно пополнять его.";
				link.l1 = "Конечно, это же само собой разумеется. Ещё какие-то замечания?";
				link.l1.go = "Folke_10";
				if (CheckCharacterItem(PChar, "BoxOfBalls"))
				{
					link.l2 = "О! Спасибо, что напомнил. У меня как раз с собой целый ящик ядер!";
					link.l2.go = "Folke_8_1";
				}
			}
			else
			{
				dialog.text = "Я осмотрел трюм, капитан. У нас недостаточно боеприпасов. Нужно как минимум по сто штук ядер, книппелей и бомб, а также сто порций картечи и пороха на двести выстрелов. Закупите необходимый арсенал, капитан - всё это не будет стоить дорого, зато спасёт наши жизни в случае нападения пиратов или испанцев.";
				link.l1 = "Хорошо. Я последую твоему совету. Отправляюсь на берег.";
				link.l1.go = "Folke_9";
			}
		break;
		
		case "Folke_8_1":
			dialog.text = "...И давно вы таскаете его с собой?";
			link.l1 = "Почти две недели.";
			link.l1.go = "Folke_8_2";
			TakeItemFromCharacter(pchar, "BoxOfBalls");
			//AddCharacterGoodsSimple(sld, GOOD_BALLS, 10);
		break;
		
		case "Folke_8_2":
			dialog.text = "Но зачем, кэп?!";
			link.l1 = "Люблю собирать всякую всячину. Никогда не знаешь, что пригодится.";
			link.l1.go = "Folke_8_3";
		break;
		
		case "Folke_8_3":
			dialog.text = "Ну, тут вы дали маху, конечно. К нашим хлопушкам их применить в любом случае не получится. Никогда не видел таких крупных ядер. 'Аделине' хватит и одного такого, чтобы ко дну пойти.";
			link.l1 = "...";
			link.l1.go = "Folke_10";
		break;
		
		case "Folke_9":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_1";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "12");
		break;
		
		case "Folke_goods_1":
			dialog.text = "Вы закончили закупку амуниции, капитан?";
			if (bOk)
			{
				link.l1 = "Да, закончил. Ещё какие-то замечания?";
				link.l1.go = "Folke_10";
				if (CheckCharacterItem(PChar, "BoxOfBalls"))
				{
					link.l2 = "О! Спасибо, что напомнил. У меня как раз с собой целый ящик ядер!";
					link.l2.go = "Folke_8_1";
				}
			}
			else
			{
				link.l1 = "Нет, я ещё этим занимаюсь.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_1";
			}
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_WEAPON) >= 50);
		case "Folke_10":
			if (bOk)
			{
				dialog.text = "Оружия для команды вы закупили достаточно, и правильно сделали - не дай Бог рукопашная - не голыми же руками драться. Не забывайте проверять его количество, потому что безоружный матрос - это мёртвый матрос\nИ лучше держать оружие с запасом, ибо проклятые крысы любят грызть рукояти сабель и пистолей, приводя их в негодность.";
				link.l1 = "Понятно. Вижу, ты ещё что-то хочешь сказать?";
				link.l1.go = "Folke_11";
			}
			else
			{
				dialog.text = "У нас нехватка оружия для матросов. Не дай Бог рукопашная - что им, голыми руками драться? Безоружный матрос - это мёртвый матрос. Как я понял, у вас сорок человек экипажа\nНужно купить оружие каждому, и лучше с запасом, комплектов пятьдесят, ибо проклятые крысы любят грызть рукояти сабель и пистолей, приводя их в негодность.";
				link.l1 = "Так и поступим. Скоро вернусь.";
				link.l1.go = "Folke_10_1";
			}
		break;
		
		case "Folke_10_1":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_2";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "13");
		break;
		
		case "Folke_goods_2":
			dialog.text = "Вы закончили закупку оружия, капитан?";
			if (bOk)
			{
				link.l1 = "Оружие в трюме. Вижу, ты ещё что-то хочешь сказать?";
				link.l1.go = "Folke_11";
			}
			else
			{
				link.l1 = "Нет, я ещё этим занимаюсь.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_2";
			}
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_FOOD) >= 100) && (GetSquadronGoods(pchar, GOOD_RUM) >= 10);
		case "Folke_11":
			if (bOk)
			{
				dialog.text = "Наверное, больше ничего. Провизии у нас достаточно, о роме для команды вы тоже позаботились - очень хорошо, так как нет лучшего лекарства от всех хворей, как добрая кружка рому после вахты. Матросы любят и уважают капитанов, выдающих ежедневные порции рома...";
				link.l1 = "Ну, как я понял, мы можем смело отправляться в путь?";
				link.l1.go = "Folke_12";
			}
			else
			{
				dialog.text = "Да. Это касается провианта и рома. Если на корабле мало провианта - это плохо. Никогда не знаешь, на сколько затянется рейс - штиль или шторм могут нарушить все планы. А если закончится еда - быть беде: голодный бунт обеспечен\nКасательно рома всё не так серьёзно, конечно, но рекомандую держать его на корабле постоянно - нет лучшего лекарства от всех хворей, как добрая кружка рому после вахты. Матросы любят и уважают капитанов, выдающих ежедневные порции рома\nТак что докупите необходимое количество, хотя бы сто пачек провианта и десять бочонков рому.";
				link.l1 = "Пожалуй, ты прав. Пойду снова к купцу.";
				link.l1.go = "Folke_11_1";
			}
		break;
		
		case "Folke_11_1":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_3";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "14");
		break;
		
		case "Folke_goods_3":
			dialog.text = "Вы закончили закупку провизии и рома, капитан?";
			if (bOk)
			{
				link.l1 = "Да. Теперь мы можем смело отправляться в путь?";
				link.l1.go = "Folke_12";
			}
			else
			{
				link.l1 = "Нет, я ещё этим занимаюсь.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_3";
			}
		break;
		
		case "Folke_12":
			dialog.text = "Да, кэп. Можно поднимать якоря и брать курс на север, к Гваделупе, как вы и хотели.";
			// belamour legendary edition -->
			link.l1 = "Отличная работа, Фульк. Без тебя бы я не справился.";
			link.l1.go = "Folke_13";
			link.l2 = "Так и сделаем. Всё, за работу, посмотрим, стоишь ли ты своих денег.";
			link.l2.go = "Folke_13a";
		break;
		
		case "Folke_13a":
			Npchar.loyality = makeint(Npchar.loyality) - 5;
			ChangeCharacterComplexReputation(pchar,"authority", 5);
			dialog.text = "Тогда поставьте меня на должность штурмана и я отправлюсь на своё место на палубе.";
			link.l1 = "...";
			link.l1.go = "Folke_14";
		break;
		
		case "Folke_13":
			Npchar.loyality = makeint(Npchar.loyality) + 5;
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			// <-- legendary edition
			dialog.text = "Тогда поставьте меня на должность штурмана и я отправлюсь на своё место на палубе.";
			link.l1 = "...";
			link.l1.go = "Folke_14";
		break;
		
		case "Folke_14":
			DialogExit();
			LAi_SetStayType(npchar);
			LAi_SetImmortal(npchar, false);
			AddQuestRecord("Sharlie", "15");
			pchar.questTemp.Sharlie = "seabattle";//в Ле Франсуа
			DeleteAttribute(pchar, "NoNavyPenalty"); // штрафуем за нехватку навигации
			
			npchar.quest.OfficerPrice = 20;
			npchar.loyality = 30;
			
			// --> копипаста LandEnc_OfficerHired
			AddPassenger(pchar, npchar, false);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			// <--
			
			pchar.questTemp.HelenDrinking.TakeFolke = true;
			
			DoQuestFunctionDelay("Tutorial_Navigator2", 1.0);
			//DoQuestFunctionDelay("Ngt_FolkeRus", 3.0);
			//NewGameTip("У вас новый офицер! Назначьте его своим штурманом в окне персонажа (F4).");
			pchar.questTemp.Sharlie.FolkeWait = true;
			LocatorReloadEnterDisable("My_Cabin_Small", "reload1", true);
			NextDiag.CurrentNode = "Folke_wait";
		break;
		
		case "Folke_wait":
			dialog.text = "Приказывайте отчаливать, капитан!";
			link.l1 = "...";
			
			if (!CheckAttribute(npchar, "navigator")) {
				dialog.text = "Капитан, поставьте меня на должность штурмана, а то ведь на мель сядем.";
				link.l1 = "Понял, сейчас сделаю.";
			}
			
			link.l1.go = "exit";
			NextDiag.TempNode = "Folke_wait";
		break;
		
		// штурман
		
		// --> пират-обманщик
		case "Seabattle_pirate":
			dialog.text = "Прошу прощения, ведь это вы - "+GetFullName(pchar)+"?";
			link.l1 = "Именно так. Чем обязан вашему вниманию, сударь?";
			link.l1.go = "Seabattle_pirate_1";
		break;
		
		case "Seabattle_pirate_1":
			dialog.text = "Позвольте представиться - "+GetFullName(npchar)+". Меня послал к вам Чезаре Крейг. Вы, должны его знать - это хозяин таверны в Ле Франсуа. Насколько ему известно, вы собираетесь на Гваделупу, и он хочет предложить вам неплохо подзаработать.";
			link.l1 = "Хм... Забавно! Интересно, и откуда же Чезаре Крейг так осведомлён о моих планах?";
			link.l1.go = "Seabattle_pirate_2";
		break;
		
		case "Seabattle_pirate_2":
			dialog.text = "Капитан, это же просто. Ваш корабль в порту Сен-Пьера сейчас - единственный, так что про вас уже всем практически всё известно: и кто вы, и куда идёте. В наших краях слухи разносятся молниеносно. Так вам интересно послушать моё предложение?";
			link.l1 = "Конечно. Я никогда не прочь заработать.";
			link.l1.go = "Seabattle_pirate_3";
		break;
		
		case "Seabattle_pirate_3":
			dialog.text = "Вот это разговор! Сразу видно деловую хватку. Так вот, Чезаре нужно срочно перевезти на Гваделупу тамошнему купцу груз нашего местного вина, двести бочонков. Трюм вашего корабля без труда их вместит\nЗа эту несложную работу вы получите целых десять тысяч песо - Чезаре очень спешит, а других кораблей, кроме вашего, сейчас у наших берегов нет. Соглашайтесь - такие выгодные предложения не каждый день поступают.";
			link.l1 = "Десять тысяч песо? Ну конечно же я согласен! Где нужно произвести погрузку?";
			link.l1.go = "Seabattle_pirate_4";
		break;
		
		case "Seabattle_pirate_4":
			dialog.text = "Отправляйтесь на корабле в порт Ле Франсуа и поговорите с Чезаре. Он сам всё организует - вам нужно будет только поставить корабль у берега. Не подведите, кэп: Крейг пообещал мне тысячу песо, если мне удастся уговорить вас...";
			link.l1 = "Не волнуйтесь, сударь. Считайте, что вы меня уговорили. Как только я буду готов к выходу в море - сразу отправлюсь в Ле Франсуа.";
			link.l1.go = "Seabattle_pirate_5";
		break;
		
		case "Seabattle_pirate_5":
			dialog.text = "Вот и славно! Тогда я пойду за своей тысячей. Спасибо, кэп!";
			link.l1 = "Да не за что...";
			link.l1.go = "Seabattle_pirate_6";
		break;
		
		case "Seabattle_pirate_6":
			DialogExit();
			AddLandQuestMark(characterFromId("LeFransua_tavernkeeper"), "questmarkmain");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "", "", "", "", -1);
			AddQuestRecord("Sharlie", "11");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.location = "None";
		break;
		// пират-обманщик
		
		// офицер Гриффондора
		case "griffondor_officer":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		// командир абордажной роты по защите Сен-Пьера
		case "rosetti":
			PlaySound("VOICE\Russian\EvilPirates01.wav");
			dialog.text = "Капитан, абордажная рота построена и в полной боевой готовности! Ждём ваших приказаний!";
			link.l1 = "";
			link.l1.go = "rosetti_1";
		break;
		
		case "rosetti_1":
			DialogExit();
			bDisableCharacterMenu = true;//лоченые интерфейсы
			ChangeShowIntarface();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("DefendSP_soldier_0"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Blaze");
			sld.dialog.filename = "MainHero_dialog.c";
			sld.dialog.currentnode = "SP_defend";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rosetti_2":
			PlaySound("interface\abordage_wining.wav");
			dialog.text = "Есть, капитан! Рота, готовьсь! Выступаем! Ура, ура, ура! Вперёд, за капитаном!";
			link.l1 = "";
			link.l1.go = "rosetti_3";
		break;
		
		case "rosetti_3":
			DialogExit();
			PlaySound("interface\abordage_wining.wav");
			bDisableCharacterMenu = false;//лоченые интерфейсы
			ChangeShowIntarface();
			for (i=0; i<=12; i++)
			{
				sld = CharacterFromID("DefendSP_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// прерывание на джунгли перед выходом из города
			pchar.quest.DefendSP_jungle1.win_condition.l1 = "location";
			pchar.quest.DefendSP_jungle1.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.DefendSP_jungle1.function = "DefendSP_SpainPatrol";
		break;
		
		case "spain_patrol":
			dialog.text = "Французы! К бою! Лоренцо, бегом в лагерь! Поднять тревогу!";
			link.l1 = "...";
			link.l1.go = "spain_patrol_1";
		break;
		
		case "spain_patrol_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("DefendSP_spapatrol_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "DefendSP_SpaPatrolDie");
				AddDialogExitQuest("MainHeroFightModeOn");
			}
			sld = CharacterFromID("DefendSP_spapatrol_5");
			LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "DefendSP_GateAlarm", -1);
		break;
		
		// страж истины
		case "spanish":
			dialog.text = "Вы понимаете, что я не могу разглашать подобную информацию?";
			link.l1 = "А вы понимаете, что только благодаря моей своевременной помощи Сен-Пьер не был разобран испанцами по кирпичику? Мой брат скрылся, оставив службу Ордену. Это неспроста. Я, как представитель интересов Филиппа де Пуанси, обязан разобраться в этом!";
			link.l1.go = "spanish_1";
		break;
		
		case "spanish_1":
			dialog.text = "Хорошо-хорошо, месье де Мор. Я отвечу на все ваши вопросы. Только не горячитесь. Спрашивайте.";
			link.l1 = "Что предшествовало заключению Мишеля под стражу?";
			link.l1.go = "spanish_2";
		break;
		
		case "spanish_2":
			dialog.text = "Мишель де Монпе вёл переговоры среди влиятельных пиратских баронов, чтобы вызвать политическую перестановку на Тортуге.";
			link.l1 = "Это мне уже известно. Что ещё?";
			link.l1.go = "spanish_3";
		break;
		
		case "spanish_3":
			dialog.text = "Также он готовил военную операцию против испанцев, а именно - захват испанского корабля с очень ценным грузом. Ваш брат должен был каким-то образом вывести испанский транспорт в нужное место прямо под пушки малого фрегата 'Гриффондор'. Мишель отбыл в длительную экспедицию, и некоторое время о нём не было ни слуху, ни духу\nОднако что-то у него пошло не так, поскольку испанского транспорта 'Гриффондор' не дождался, а сам Мишель был обнаружен рыбаками, выброшенный волнами на берег в бухте Ле Марен, контуженный и едва живой. Видимо, операция провалилась\nКазалось бы - на войне, как на войне, хорошо, что вообще жив остался, однако шевалье де Пуанси совершенно неожиданно ополчился против Мишеля, обвинил в растрате и присвоении денежных средств Ордена и заключил под стражу\nКонечно, мы не поверили этим обвинениям: Мишель - честнейший парень, так что одному Богу известно, какая чёрная кошка пробежала между ним и шевалье. Быть может, сам месье де Пуанси поведает вам об этом?";
			link.l1 = "Возможно. Это всё, что вам известно?";
			link.l1.go = "spanish_4";
		break;
		
		case "spanish_4":
			dialog.text = "К сожалению, добавить к сказанному мне нечего. Подробности всех операций, проводимых вашим братом, были известны только ему самому и шевалье де Пуанси. Мы, офицеры и солдаты Ордена, просто выполняли приказы.";
			link.l1 = "Раз шевалье так доверял Мишелю, значит, не все его операции были провальными? Были и успехи?";
			link.l1.go = "spanish_5";
		break;
		
		case "spanish_5":
			dialog.text = "Конечно. Последняя неудача Мишеля де Монпе была также и его первой неудачей, поэтому мы буквально были поражены реакцией шевалье. Ещё незадолго до этого при помощи тщательно спланированной операции Мишеля 'Гриффондором' был захвачен испанский галеон, доверху гружёный серебром. Одно это могло компенсировать десяток неудач в будущем. И всё же ваш брат был арестован.";
			link.l1 = "Ясно. У вас есть какие-то предположения, почему Мишель так спешно скрылся из Сен-Пьера?";
			link.l1.go = "spanish_6";
		break;
		
		case "spanish_6":
			dialog.text = "Я подозреваю, что причины его ареста - в межличностном конфликте с Филиппом де Пуанси. Ваш брат, очевидно, опасался, что преследования со стороны шевалье продолжатся и после освобождения, поэтому принял превентивные меры. И знаете что, месье де Мор - здесь никто не осуждает его решение!\nЧеловек мужественно и доблестно работал на благо Ордена, а его при первой же неудаче, которую он бы компенсировал в дальнейшем сторицей, раненого и больного, бросают в камеру, обвиняя в какой-то совершенной нелепице!\nДа, если что: разговор наш неофициальный, и под присягой повторять свои слова я не буду. Мы поняли друг друга, месье де Мор?";
			link.l1 = "Безусловно, офицер. Мы договорились об этом с самого начала. Скажите, а нападение испанцев на Сен-Пьер не могло быть спровоцировано военными операциями Ордена против испанских кораблей? Ну, тот же галеон с серебром, о котором вы упомянули? Уж больно рьяно кастильцы орудовали на вашей базе...";
			link.l1.go = "spanish_7";
		break;
		
		case "spanish_7":
			dialog.text = "Навряд ли. О нашей базе на Мартинике вообще мало кому известно, да и все наши действия против испанцев были точечными и аккуратно спланированными. Но вы можете сами спросить об этом у пленного испанского офицера, который в данный момент содержится в наших казематах. Мы уже допросили его\nАтака Сен-Пьера - обычный грабительский налёт, организованный испанским грандом, бароном Рамоном де-Мендосой-и-Риба, с целью личной наживы и устрашения гражданского населения французских колоний, а также чтобы выслужиться перед Эскориалом.";
			link.l1 = "Я побеседую с вашим пленным. Где мне его найти?";
			link.l1.go = "spanish_8";
		break;
		
		case "spanish_8":
			dialog.text = "Внизу, в камере, где содержался ваш брат.";
			link.l1 = "Хорошо. Я вернусь, после того как допрошу испанца. Возможно, у меня появятся ещё вопросы.";
			link.l1.go = "spanish_9";
		break;
		
		case "spanish_9":
			DialogExit();
			NextDiag.CurrentNode = "Maltie_officer";
			AddQuestRecord("Guardoftruth", "2");
			pchar.questTemp.Guardoftruth = "prisoner";
			sld = characterFromId("spa_baseprisoner");
			LAi_CharacterEnableDialog(sld);
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "spanish_10":
			dialog.text = "Вот это новость! Но я не могу отпустить пленника, он участвовал в набеге на Сен-Пьер...";
			link.l1 = "Офицер, это важный свидетель. Нападение на Сен-Пьер было совершено не для грабежа. Дону Рамону Мендосе нужно было другое. Мы должны разобраться с этим окончательно. Так вы выдадите мне этого испанца, или мне затребовать разрешение у де Пуанси?";
			link.l1.go = "spanish_11";
		break;
		
		case "spanish_11":
			dialog.text = "Ладно, забирайте его, раз уж он так важен вам. Всё равно я собирался казнить мерзавца публично на площади Сен-Пьера... Но строго под вашу личную ответственность!";
			link.l1 = "Безусловно. Перед шевалье де Пуанси за этого испанца буду отвечать я. Распорядитесь надеть на пленника кандалы и доставить в порт к моей шлюпке.";
			link.l1.go = "spanish_12";
		break;
		
		case "spanish_12":
			dialog.text = "Будет сделано, капитан.";
			link.l1 = "И ещё, офицер: имя 'Мигель Дичозо' о чём-нибудь говорит вам?";
			link.l1.go = "spanish_13";
		break;
		
		case "spanish_13":
			dialog.text = "Нет. Впервые слышу. А что?";
			link.l1 = "Точно нет? То есть ни на вашей базе, ни в губернаторском дворце, ни вообще в Сен-Пьере вы не встречали человека с таким именем?";
			link.l1.go = "spanish_14";
		break;
		
		case "spanish_14":
			dialog.text = "Нет, не встречал. У нас, знаете ли, не жалуют испанцев.";
			link.l1 = "Ясно. Впрочем, этого и следовало ожидать. Было бы слишком просто... Ладно, я ещё раз поговорю с пленным испанцем, а вы тем временем подготовьте его к доставке. И: спасибо, офицер! Вы мне очень помогли.";
			link.l1.go = "spanish_15";
		break;
		
		case "spanish_15":
			dialog.text = "Да не за что... Как вы думаете, месье де Мор: где же сейчас ваш брат?";
			link.l1 = "Я бы и сам хотел знать ответ на этот вопрос. И узнаю... рано или поздно. Удачи!";
			link.l1.go = "spanish_16";
		break;
		
		case "spanish_16":
			DialogExit();
			NextDiag.CurrentNode = "Maltie_officer";
			AddQuestRecord("Guardoftruth", "3");
			pchar.questTemp.Guardoftruth = "toship";
			sld = characterFromId("spa_baseprisoner");
			sld.dialog.currentnode = "spa_prisoner_28";
			LAi_CharacterEnableDialog(sld);
		break;
		
		// монах-посланник от Винсенто
		case "monk_vinsento":
			dialog.text = TimeGreeting()+"! Вы и есть капитан "+GetFullName(pchar)+"?";
			link.l1 = "Да, это я. Что вам угодно?";
			link.l1.go = "monk_vinsento_1";
		break;
		
		case "monk_vinsento_1":
			dialog.text = "Я к вам от отца Винсенто. У меня для вас...";
			link.l1 = "От отца Винсенто? Боюсь, с Его Преосвященством у меня дела окончены. После того, как он натравил на меня дружка Диего де Монтойи, Алонсо де Мальдонадо. Однако он просчитался, так ему и передайте.";
			link.l1.go = "monk_vinsento_2";
		break;
		
		case "monk_vinsento_2":
			dialog.text = "Постойте, капитан. Отец Винсенто ожидал от вас такой реакции, и предупредил меня об этом. Уверяю, Его Преосвященство не желает вам зла. Пожалуйста, прочтите его письмо. Это очень, очень важно.";
			link.l1 = "Не желает мне зла? Хм. Может, он также ничего не рассказывал про меня и дону де Мальдонадо? Не верится мне что-то.";
			link.l1.go = "monk_vinsento_3";
		break;
		
		case "monk_vinsento_3":
			dialog.text = "Возьмите письмо, капитан. Прочтите его, и решайте сами. Только помните, что судьба всего христианского мира сейчас в ваших руках, и отнеситесь к этому со всей серьёзностью. Да просветит вас Господь, и да направит он ваши стопы на путь истинный!";
			link.l1 = "Ладно, давайте сюда письмо.";
			link.l1.go = "monk_vinsento_4";
		break;
		
		case "monk_vinsento_4":
			GiveItem2Character(pchar, "specialletter"); 
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_vinsento");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento_last";
			dialog.text = "Держите. Надеюсь, вы примете правильное решение.";
			link.l1 = "...";
			link.l1.go = "monk_vinsento_5";
		break;
		
		case "monk_vinsento_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 30.0);
			ReOpenQuestHeader("Sharlie"); // patch-8
			AddQuestRecord("Sharlie", "40");
			CloseQuestHeader("Ksochitam");
		break;
		
		// падре Адриан
		case "adrian":
			dialog.text = "Приветствую, "+GetSexPhrase("сын мой","дочь моя")+". Да благословит Господь дела твои...";
			link.l1 = "Здравствуйте, отец Адриан. Его Преосвященство сказал мне, что вы можете снабдить меня оберегами и лекарствами...";
			link.l1.go = "adrian_1";
		break;
		
		case "adrian_1":
			dialog.text = "Да, конечно. Вот то, что я привёз из Сантьяго специально для тебя. Здесь освящённые обереги и целебные отвары. И даже редкая, уникальная тинктура Ометочтли, улучшающая боевые качества. Это всё тебе, "+GetSexPhrase("сын мой","дочь моя")+".";
			link.l1 = "Спасибо!";
			link.l1.go = "adrian_2";
		break;
		
		case "adrian_2":
			for(i=2; i<=10; i++)
			{
				if (i == 4 || i == 5 || i == 8 || i == 9) continue;
				TakeNItems(pchar, "amulet_"+i, 2);
			}
			TakeNItems(pchar, "potion2", 20);
			TakeNItems(pchar, "potion4", 10);
			TakeNItems(pchar, "potion7", 3);
			TakeNItems(pchar, "berserker_potion", 3);
			dialog.text = "Если тебе ещё понадобятся целебные зелья - ты можешь приобрести их у меня, по одному пузырьку каждого вида в день. Я буду их готовить по мере надобности.";
			link.l1 = "Хорошо, отец Адриан. Я учту это.";
			link.l1.go = "exit";
			link.l2 = "Отлично. Я прямо сейчас хочу приобрести некоторые из них.";
			link.l2.go = "potion";
			NextDiag.TempNode = "adrian_3";
		break;
		
		case "adrian_3":
			dialog.text = "Да благословит тебя Господь, "+GetSexPhrase("сын мой","дочь моя")+". Что ты хотел?";
			link.l1 = "Я хочу купить несколько лечебных эликсиров.";
			link.l1.go = "potion";
			link.l2 = "Пока ничего, готовлюсь к походу. Просто заглянул проведать.";
			link.l2.go = "exit";
			NextDiag.TempNode = "adrian_3";
		break;
		
		case "potion":
			dialog.text = "Конечно, "+GetSexPhrase("сын мой","дочь моя")+". Какое лекарство ты желаешь приобрести?";
			if (!CheckAttribute(npchar, "potion1_date") || GetNpcQuestPastDayParam(npchar, "potion1_date") >= 1)
			{
				link.l1 = "Простую лечебную эссенцию.";
				link.l1.go = "potion1";
			}
			if (!CheckAttribute(npchar, "potion2_date") || GetNpcQuestPastDayParam(npchar, "potion2_date") >= 1)
			{
				link.l2 = "Целебный эликсир.";
				link.l2.go = "potion2";
			}
			if (!CheckAttribute(npchar, "potion3_date") || GetNpcQuestPastDayParam(npchar, "potion3_date") >= 1)
			{
				link.l3 = "Противоядие.";
				link.l3.go = "potion3";
			}
			if (!CheckAttribute(npchar, "potion4_date") || GetNpcQuestPastDayParam(npchar, "potion4_date") >= 1)
			{
				link.l4 = "Травяную микстуру.";
				link.l4.go = "potion4";
			}
			link.l5 = "Извините, отец Адриан, я передумал"+GetSexPhrase("","а")+".";
			link.l5.go = "exit";
		break;
		
		case "potion1":
			npchar.quest.price = 90;
			npchar.quest.type = 1;
			dialog.text = "Лечебную эссенцию? С тебя 90 песо, "+GetSexPhrase("сын мой","дочь моя")+".";
			if (sti(Pchar.money) >= 90)
			{
				link.l1 = "Пожалуйста, отец Адриан. Вот деньги.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "К сожалению, у меня недостаточно средств... Я вернусь позже.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion2":
			npchar.quest.price = 500;
			npchar.quest.type = 2;
			dialog.text = "Целебный эликсир? С тебя 500 песо, "+GetSexPhrase("сын мой","дочь моя")+".";
			if (sti(Pchar.money) >= 500)
			{
				link.l1 = "Пожалуйста, отец Адриан. Вот деньги.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "К сожалению, у меня недостаточно средств... Я вернусь позже.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion3":
			npchar.quest.price = 200;
			npchar.quest.type = 3;
			dialog.text = "Противоядие? С тебя 200 песо, "+GetSexPhrase("сын мой","дочь моя")+".";
			if (sti(Pchar.money) >= 200)
			{
				link.l1 = "Пожалуйста, отец Адриан. Вот деньги.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "К сожалению, у меня недостаточно средств... Я вернусь позже.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion4":
			npchar.quest.price = 900;
			npchar.quest.type = 4;
			dialog.text = "Микстуру? С тебя 900 песо, "+GetSexPhrase("сын мой","дочь моя")+".";
			if (sti(Pchar.money) >= 900)
			{
				link.l1 = "Пожалуйста, отец Адриан. Вот деньги.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "К сожалению, у меня недостаточно средств... Я вернусь позже.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion_pay":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
			iTemp = sti(npchar.quest.type);
			GiveItem2Character(pchar, "potion"+iTemp);
			PlaySound("interface\important_item.wav");
			dialog.text = "Пожалуйста. Держи своё лекарство. Да хранит тебя Господь!";
			link.l1 = "Спасибо, отец Адриан.";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "potion"+iTemp+"_date");
			NextDiag.TempNode = "adrian_3";
		break;
		
		// посланец Дичозо
		case "Dichoso_agent":
			dialog.text = "Капитан "+GetFullName(pchar)+"?";
			link.l1 = "Да, это я. Чем обязан?";
			link.l1.go = "Dichoso_agent_1";
		break;
		
		case "Dichoso_agent_1":
			dialog.text = "У меня к вам сообщение от капитана Мигеля Дичозо. Он сказал, что вы знаете его.";
			link.l1 = "Чести знать лично не удостоился, а слышать о нём - не спорю, доводилось.";
			link.l1.go = "Dichoso_agent_2";
		break;
		
		case "Dichoso_agent_2":
			dialog.text = "Капитан Дичозо хочет с вами встретиться. У него предложение к вам лично касательно похода вглубь Мэйна к индейскому городу Тайясаль. Как он сказал - ваш опыт, помноженный на его знания, дадут отличный результат.";
			link.l1 = "Прямо так и сказал?";
			link.l1.go = "Dichoso_agent_3";
		break;
		
		case "Dichoso_agent_3":
			dialog.text = "Именно! Капитан Дичозо будет ждать вас на острове Сент-Кристофер. Дабы избежать ненужных глаз и ушей, Мигель предлагает провести встречу в большой крипте кладбища Капстервиля.";
			link.l1 = "Хм...";
			link.l1.go = "Dichoso_agent_4";
		break;
		
		case "Dichoso_agent_4":
			dialog.text = "Дичозо предупредил, что вы будете колебаться и уполномочил меня заверить, что гарантирует мирный исход переговоров независимо ни от чего. А также попросил передать, что то, что вы нашли на одном острове, лишь малая толика того, что есть в Тайясале.";
			link.l1 = "Даже так! Тогда это очень интересно. Но почему же капитан Дичозо не явился ко мне сам, а прислал третье лицо?";
			link.l1.go = "Dichoso_agent_5";
		break;
		
		case "Dichoso_agent_5":
			dialog.text = "Дон Дичозо разыскивал вас на Исла-Тесоро, потом здесь, а теперь отбыл на Сент-Кристофер, в надежде найти вас там. Ведь вы же офицер самого Филиппа де Пуанси, я не прав? А я должен был ожидать тут, на случай, если вы прибудете в Блювельд.";
			link.l1 = "Тогда всё ясно. Ну что же, не буду терять времени и отправляюсь в Капстервиль.";
			link.l1.go = "Dichoso_agent_6";
		break;
		
		case "Dichoso_agent_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "Tieyasal_PrepareDichosoTrap", -1);
		break;
		
		// агент Дичозо
		case "Dichoso_crypt_agent":
			dialog.text = "Ну, наконец мы с тобой встретились, капитан "+GetFullName(pchar)+"...";
			if (CheckAttribute(pchar, "questTemp.Tieyasal.MigelKnow")) 
			{
				link.l1 = "Где Мигель Дичозо? И не пытайся юлить. Я прекрасно знаю, кто он есть на самом деле. Думаю, что и ты тоже.";
				link.l1.go = "Dichoso_crypt_agent_2";
			}
			else
			{
				link.l1 = "Полагаю, передо мной Мигель Дичозо собственной персоной?";
				link.l1.go = "Dichoso_crypt_agent_1";
			}
		break;
		
		case "Dichoso_crypt_agent_1":
			dialog.text = "Правильно полагаешь, капитан. Мы уже давно ходим по следу друг друга, разве не так?";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) // прочел журнал Санта-Квитерии
			{
				link.l1 = "Вот смотрю я на тебя, приятель, и понимаю, что ты лжёшь. Никакой ты не Дичозо. Я читал записи в судовом журнале капитана 'Санта-Квитерии', а также расспрашивал о его внешности. Что-то не похож ты на него. Даже сабельного шрама на лице нет.";
				link.l1.go = "Dichoso_crypt_agent_2";
			}
			else
			{
				link.l1 = "Именно так. Как я понимаю, речь пойдёт о Тайясале?";
				link.l1.go = "Dichoso_crypt_agent_7";
			}
		break;
		
		case "Dichoso_crypt_agent_2":
			dialog.text = "Хм. Ну что же, не вижу смысла играть в прятки. Мигель предупреждал, что ты чертовски сообразительный каналья...";
			link.l1 = "Где Дичозо?";
			link.l1.go = "Dichoso_crypt_agent_3";
		break;
		
		case "Dichoso_crypt_agent_3":
			dialog.text = "Его тут нет. Я уполномочен встретить тебя и побеседовать от его имени.";
			link.l1 = "У меня нет желания разговаривать с пешкой. Мне нужен ферзь. Так где он?";
			link.l1.go = "Dichoso_crypt_agent_4";
		break;
		
		case "Dichoso_crypt_agent_4":
			dialog.text = "Мы не будем долго с тобой разговаривать, капитан. В общем-то, тебя пригласили сюда не для разглагольствований.";
			link.l1 = "Понимаю. Примитивная ловушка-засада. Я угадал?";
			link.l1.go = "Dichoso_crypt_agent_5";
		break;
		
		case "Dichoso_crypt_agent_5":
			dialog.text = "В точку, приятель. За вот той маленькой дверью есть подвал, а в нём мои люди. Кроме того, в каждый гроб я спрятал по отменному стрелку. Выход назад тебе отрезан. Так что ловушка хоть и примитивная, но ты в неё залез. Желание увидеть Тайясаль перевесило осторожность, да?";
			link.l1 = "А вообще удачное ты выбрал место для засады, дружок. Сразу тут тебя и твоих бандитов по гробам и упакуем.";
			link.l1.go = "Dichoso_crypt_agent_6";
		break;
		
		case "Dichoso_crypt_agent_6":
			dialog.text = "Мне нравится твоё чувство юмора. В этом ты похож на Мигеля. Что ни говори - родная кровь... Я сделаю, как он просил: отправлю тебя на тот свет максимально быстро и безболезненно. Ребята, к бою!";
			link.l1 = "Многие пытались это сделать, да руки коротки...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_StartCryptBattle");
		break;
		
		case "Dichoso_crypt_agent_7":
			dialog.text = "Очень хочется туда попасть? Понимаю. Но не думаю, что это хорошая идея.";
			link.l1 = "Тогда о чём ты собрался со мной беседовать?";
			link.l1.go = "Dichoso_crypt_agent_8";
		break;
		
		case "Dichoso_crypt_agent_8":
			dialog.text = "А я и не собираюсь с тобой разводить долгие разговоры. Ты здесь, и этого мне достаточно.";
			link.l1 = "Понимаю. Примитивная ловушка-засада. Я угадал?";
			link.l1.go = "Dichoso_crypt_agent_5";
		break;
		
		// командир абордажников
		case "newcastle_officer":
			dialog.text = "Ждём ваших приказаний, капитан!";
			link.l1 = "Выдвигаемся через джунгли в сторону кладбища Сент-Кристофера. На само кладбище не заходите, занимаете позицию в джунглях у тропы и следите за происходящим. В случае опасности - атакуйте.";
			link.l1.go = "newcastle_officer_1";
		break;
		
		case "newcastle_officer_0":
			dialog.text = "Ждём ваших приказаний, капитан!";
			link.l1 = "Выдвигаемся через джунгли в сторону кладбища Сент-Кристофера. На само кладбище не заходите, занимаете позиции в джунглях по обе стороны тропы - окружаете территорию и следите за происходящим. Враг наверняка готовит засаду. Как только увидите неприятеля - немедленно атакуйте.";
			link.l1.go = "newcastle_officer_1";
		break;
		
		case "newcastle_officer_1":
			dialog.text = "Есть, капитан!";
			link.l1 = "Хорошо. Вперёд!";
			link.l1.go = "newcastle_officer_2";
		break;
		
		case "newcastle_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Charles_exittown")].DisableEncounters = true; //энкаутеры закрыть
			locations[FindLocation("Charles_CaveEntrance")].DisableEncounters = true; //энкаутеры закрыть
			for(i=2; i<=4; i++)
			{
				locations[FindLocation("Charles_Jungle_0"+i)].DisableEncounters = true; //энкаутеры закрыть
			}
			LocatorReloadEnterDisable("Shore42", "boat", true);
			for(i=1; i<=iTotalTemp; i++)
			{
				sld = characterFromID("Tieyasal_Oursoldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// на локацию перед кладбищем
			pchar.quest.Tieyasal_newcastle.win_condition.l1 = "location";
			pchar.quest.Tieyasal_newcastle.win_condition.l1.location = "Charles_exittown";
			pchar.quest.Tieyasal_newcastle.function = "Tieyasal_NewcastleGoJungle";
			// на крипту
			pchar.quest.Tieyasal_graveyard.win_condition.l1 = "location";
			pchar.quest.Tieyasal_graveyard.win_condition.l1.location = "Charles_CryptBig2";
			pchar.quest.Tieyasal_graveyard.function = "Tieyasal_InGraveyardCrypt";
		break;
		
		case "Europe":
			PlaySound("VOICE\Russian\military01.wav");
			dialog.text = "Капитан Гобарт! По сведениям лазутчиков, в этом имении укрываются беглые мятежники. В вашем распоряжении пять драгун - обыщите дом и схватите всех, кто там находится! Можете не церемониться, вы действуете от имени короля!";
			link.l1 = "Есть, сэр!";
			link.l1.go = "Europe_1";
		break;
		
		case "Europe_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Europe_SharlieFinal_1", 5);
		break;
		
		//Индеец по квесту "Знакомство с индейцами"
		case "ZsI_ListKakao":
			dialog.text = "Тск! Сын моря!";
			link.l1 = "Кхм... Это ты ко мне обращаешься?";
			link.l1.go = "ZsI_ListKakao_1";
			sld = characterFromId("Tichingitu");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "ZsI_ListKakao_1":
			dialog.text = "Так. Моя звать Лист Какао. У меня дело, Сын Моря.";
			link.l1 = "Э-э... Понятия не имею, как выглядит какао, и почему ты его лист. Имена вы себе подбираете, конечно... Ладно, говори, что у тебя, да побыстрее.";
			link.l1.go = "ZsI_ListKakao_2";
		break;
		
		case "ZsI_ListKakao_2":
			dialog.text = "Тск! Твоя ходить в город. Купить два пистоль. И два по десять порох с пулей. И передать моя. Награда есть. Сын Моря будет доволен.";
			link.l1 = "Два пистоля и заряд к ним на двадцать выстрелов? Всего-то? А чего сам не сходишь и не купишь, Лист Какао?";
			link.l1.go = "ZsI_ListKakao_3";
		break;
		
		case "ZsI_ListKakao_3":
			dialog.text = "Бледнолицый не понимать? Да кто же продать я огненный оружие?!";
			if (CheckAttribute(pchar, "questTemp.ZsI_Cannibals"))		//Sinistra Только если проходил квест "Каннибалы"
			{
				link.l1 = "А знаешь, я ведь уже встречался с вашим братом на Мартинике... Они были каннибалами. Они похитили девушку и двух мужчин, и одного успели убить, зажарить и съесть. И если бы хоть у одного из них имелся пистоль, то, полагаю, мы с тобой тут сейчас не беседовали бы...";
				link.l1.go = "ZsI_ListKakao_3_1";
			}
			else
			{
				link.l1 = "И зачем же тебе огнестрельное оружие, Лист Какао? Убить кого-то хочешь?";
				link.l1.go = "ZsI_ListKakao_3_2";
			}
		break;
		
		case "ZsI_ListKakao_3_1":
			dialog.text = "Гу-у! Лист Какао не разбойник, моя сражаться только воины твой племя. Бледнолицый пришли наша земля, делать нас раб. Лист Какао сам воевать. Брать раб. Не плохо, не хорошо. Так есть. Индеец, белый - нет разница. Но бледнолицый победить лишь помощь огненный оружие.";
			link.l1 = "И зачем же тебе огнестрельное оружие, Лист Какао? Убить кого-то хочешь?";
			link.l1.go = "ZsI_ListKakao_3_2";
		break;
		
		case "ZsI_ListKakao_3_2":
			dialog.text = "Воевать. Но на равных. Бледнолицый есть огненный оружие, индеец нет. Так не есть справедливо. И быть пистоль у индеец - бледнолицый не обижать нас просто так, не унижать, не оскорблять ради свой веселье.";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_4";
		break;
		
		case "ZsI_ListKakao_4":
			StartInstantDialog("Tichingitu", "ZsI_ListKakao_5", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_ListKakao_5":
			dialog.text = "Так, капитан. Бледнолицые нас презирать.";
			link.l1 = "Это я уже заметил. Эх, а в Европе доводилось слышать, что движимые искренней заботой святые отцы и простые колонисты успешно наставляют индейцев в истинной вере, а аборигены становятся добрыми христианами...";
			link.l1.go = "ZsI_ListKakao_6";
		break;
		
		case "ZsI_ListKakao_6":
			dialog.text = "Что это значить?";
			link.l1 = "Видимо, это должно означать, что конфликта между белыми и индейцами якобы уже больше нет, и мы все вместе трудимся в мире на... На этих, как их?.. Плантациях.";
			link.l1.go = "ZsI_ListKakao_7";
		break;
		
		case "ZsI_ListKakao_7":
			dialog.text = "Тичингиту не понимать капитан, но понимать Лист Какао. Он желать месть.";
			link.l1 = "Похоже, что так... А тебе не хочется отомстить? Тем же тюремщикам?";
			link.l1.go = "ZsI_ListKakao_8";
		break;
		
		case "ZsI_ListKakao_8":
			dialog.text = "Может, и хотеть. Но Тичингиту так не делать. Тичингиту теперь с капитан. И Тичингиту думать свой голова. Быть много кровь. Кровь белый. Кровь индеец. Много счёт. Плохо. Не то, не так.";
			link.l1 = "Да это уже есть, да и счёт этот только вырастет, если я куплю оружие и отдам его Листу Какао... С другой стороны, по-своему он прав... А мне ещё команде скоро платить...";
			link.l1.go = "ZsI_ListKakao_9";
		break;
		
		case "ZsI_ListKakao_9":
			dialog.text = "Думать свой голова, капитан.";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_10";
		break;
		
		case "ZsI_ListKakao_10":
			StartInstantDialog("ListKakao", "ZsI_ListKakao_11", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_ListKakao_11":
			dialog.text = "Сын Моря любить говорить. Похож на усатый скво.";
			link.l1 = "На кого? Ты вот что лучше мне объясни, Лист Какао. Я ведь тоже бледнолицый. Ты просишь оружие у бледнолицего для борьбы с бледнолицыми. И считаешь, что я могу тебе его дать. Ничего не смущает? Почему ты обратился ко мне?";
			link.l1.go = "ZsI_ListKakao_12";
		break;
		
		case "ZsI_ListKakao_12":
			dialog.text = "Я слышать ваш разговор с этот чужой индеец в диковинный наряд. Ты не такой, как другой бледнолицый. Ты понимать этот Тичингиту. И ты понимать Лист Какао, я быть уверен.";
			link.l1 = "Ох... Что дашь за оружие, Лист Какао?";
			link.l1.go = "ZsI_ListKakao_13";
		break;
		
		case "ZsI_ListKakao_13":
			dialog.text = "Слёзы богов. Вы называть их жемчуг. Много жемчуг.";
			link.l1 = "Я принял решение, Лист Какао. Жди меня здесь, я иду к городскому торговцу оружием. Куплю необходимое, и сразу назад.";
			link.l1.go = "ZsI_ListKakao_Soglasen_5";
			if (sti(pchar.items.pistol1) >= 2 && sti(pchar.items.GunPowder) >= 20 && sti(pchar.items.bullet) >= 20)
			{
				link.l2 = "Я принял решение, Лист Какао. Так получилось, что у меня уже есть то, что тебе нужно. Держи.";
				link.l2.go = "ZsI_ListKakao_Soglasen_2";
			}
			link.l3 = "Я принял решение, Лист Какао. Мне не нужны лишние проблемы, которые неизбежно появятся, исполни я твою просьбу. Огнестрельное оружие ты от меня не получишь. Иди своей дорогой.";
			link.l3.go = "ZsI_ListKakao_Otkaz";
			npchar.LifeDay = 1;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		
		case "ZsI_ListKakao_Otkaz":
			dialog.text = "Тск!";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_Otkaz_2";
		break;
		
		case "ZsI_ListKakao_Otkaz_2":
			DialogExit();
			
			ChangeIndianRelation(-3.0);
			ChangeCharacterComplexReputation(pchar, "authority", -1);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "ZsI_Mir", -1);
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 1.0, 1.0);
			npchar.lifeday = 0;
			PChar.quest.ZsI_Draka.win_condition.l1 = "NPC_Death";
			PChar.quest.ZsI_Draka.win_condition.l1.character = "ListKakao";
			PChar.quest.ZsI_Draka.win_condition = "ZsI_Draka";
			PChar.quest.ZsI_Mir.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ZsI_Mir.win_condition.l1.location = PChar.location;
			PChar.quest.ZsI_Mir.win_condition = "ZsI_Mir";
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			sld = characterFromId("Tichingitu");
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			sld.Dialog.CurrentNode = "Tichingitu_officer";
			LaunchTutorial("Fighter", 1);
		break;
		
		case "ZsI_ListKakao_Soglasen_2":
			dialog.text = "Ой-ей! А у Сын Моря есть мушкет? За мушкет давать вкусный цена!";
			link.l1 = "Только орудие с корабля могу предложить. Иди своей дорогой, Лист Какао, пока нас тут не увидели и не арестовали.";
			link.l1.go = "ZsI_ListKakao_Soglasen_3";
			AddCharacterExpToSkill(pchar, "Commerce", 50);
			ChangeIndianRelation(3.0);
			AddItems(pchar, "jewelry53", 180);
			//Log_info("Вы получили 180 маленьких жемчужин");
			PlaySound("Interface\important_item.wav");
			DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
			if (sti(pchar.items.pistol1) >= 2 && sti(pchar.items.GunPowder) >= 20 && sti(pchar.items.bullet) >= 20)
			{
				RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
				RemoveItems(PChar, "pistol1", 2);
				RemoveItems(PChar, "GunPowder", 20);
				RemoveItems(PChar, "bullet", 20);
			}
		break;
		
		case "ZsI_ListKakao_Soglasen_3":
			dialog.text = "Хороший сделка! Сын Моря, если ходить в сельва, брать огненный оружие. Встретить индеец - выгодный сделка!";
			link.l1 = "Учту на будущее. Прощай, Лист Какао.";
			link.l1.go = "ZsI_ListKakao_Soglasen_4";
		break;
		
		case "ZsI_ListKakao_Soglasen_4":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			Return_TichingituOfficer();
			LaunchTutorial("Fighter", 1);
		break;
		
		case "ZsI_ListKakao_Soglasen_5":
			dialog.text = "Лист Какао недолго ждать.";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_Soglasen_6";
		break;
		
		case "ZsI_ListKakao_Soglasen_6":
			DoQuestReloadToLocation("BasTer_town", "reload", "gate_back", "ZsI_TPvGorod");
		break;

		case "ZsI_officer":
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				dialog.text = "Ба, да у нас тут целое собрание коренного населения!\n(обращаясь к Тичингиту) Обратно в тюрьму захотел, собака?\nА вы что здесь забыли, месье?";
			}
			else
			{
				dialog.text = "Стоять! Вы что здесь забыли, месье?";
			}
			link.l1 = "";
			link.l1.go = "ZsI_officer_2";
			sld = CharacterFromID("ListKakao");
			LAi_CharacterEnableDialog(sld);
			EndBattleLandInterface();
		break;
		
		case "ZsI_officer_2":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ListKakao"));
			dialog.text = "Эй, шваль, ты тут этого капитана караулишь?";
			link.l1 = "";
			link.l1.go = "ZsI_officer_3";
		break;
		
		case "ZsI_officer_3":
			DialogExit();
			StartInstantDialog("ListKakao", "ZsI_officer_4", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_officer_4":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ZsI_Patrul_off"));
			dialog.text = "Бледнолицый для меня один лицо. Но этого не помнить. Ты, воин, делай со мной, что собираться. Надоесть уже. Лист Какао готов встречать духи леса.";
			link.l1 = "";
			link.l1.go = "ZsI_officer_5";
		break;
		
		case "ZsI_officer_5":
			DialogExit();
			StartInstantDialog("ZsI_Patrul_off", "ZsI_officer_6", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_officer_6":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ListKakao"));
			dialog.text = "Ад тебя ждёт, образина, а не духи леса.";
			link.l1 = "";
			link.l1.go = "ZsI_officer_7";
		break;
		
		case "ZsI_officer_7":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			dialog.text = "Капитан, вы свободны. Не мешайте. Охрана города - серьёзная задача.";
			link.l1 = "Вижу... Но что с этим индейцем?";
			link.l1.go = "ZsI_officer_8";
		break;
		
		case "ZsI_officer_8":
			dialog.text = "Что за интерес к индейцам, месье?.. Хотя... Ну да, как же, вы же недавно из Европы\nКак там в Париже? Городских крыс всё так же давят на месте, или начали уже к причастию приглашать? А у нас тут вместо крыс вот эти. Водятся с буканьерами, нападают на лесорубов, жрут людей, чёрт побери!\nА недавно один умник продал аборигенам мушкет с боеприпасом! И эти паскуды всех солдат патруля перебили! А патрулём этим, кстати, командовал мой друг и товарищ. Предателя-колониста мы выявили и вздёрнули сушиться на солнышке, чтоб другим неповадно было! Давать индейцам огнестрел! Это же измена! Измена Франции!.. А эту раскрашенную обезьяну мы давно выслеживаем, успел примелькаться по разным случаям\nНу да теперь будет ему скорый и заслуженный конец. А вы идите, капитан, нечего вам тут торчать и лезть в дела, которые прямо вас не касаются. Вы к этой войне отношения не имеете... Пока не имеете... Или, всё-таки, имеете?!";
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				notification("Вызывающий доверие", "Trustworthy");
				link.l1 = "(Вызывающий доверие) Видите ли, офицер... Я - капитан Шарль де Мор, гость Фадея Московита. И у нас есть интерес к этому индейцу... Давайте не будем мешать друг другу делать свою работу. По рукам, лейтенант?";
				link.l1.go = "ZsI_officer_Mir";
			}
			else
			{
				notification("Не открыта способность", "Trustworthy");
			}
			link.l2 = "Хм... Белый человек разный, индеец тоже разный... Отношение к пришлым, отношение к коренным... Колонист, абориген... Сейчас сравнение не в вашу пользу, офицер... К бою!";
			link.l2.go = "ZsI_officer_Draka";
			link.l3 = "Вы правы, лейтенант, не имею. Прощайте.";
			link.l3.go = "ZsI_officerKIll";
			StartBattleLandInterface();
		break;
		
		case "ZsI_officer_Mir":
			dialog.text = "Кхм! Я понял вас, капитан. Передайте, пожалуйста, мои самые добрые пожелания месье Фадею. Отряд, продолжаем патрулирование!";
			link.l1 = "";
			link.l1.go = "ZsI_officer_Mir_2";
		break;
		
		case "ZsI_officer_Mir_2":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			LAi_SetImmortal(sld, true);
			LAi_ActorGoToLocation(sld, "reload", "reload4", "none", "", "", "", -1);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("ZsI_Patrul_"+i);
				LAi_SetActorType(sld);
				sld.lifeday = 0;
				LAi_SetImmortal(sld, true);
				LAi_ActorGoToLocation(sld, "reload", "reload4", "none", "", "", "", -1);
			}
			sld = CharacterFromID("ListKakao");
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "ZsI_MirFinal";
			LAi_SetActorType(sld);
			LAi_SetActorType(pchar);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
			
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Fortune", 30);
		break;
		
		case "ZsI_MirFinal":
			dialog.text = "Ой-ей!";
			link.l1 = "Да уж, я и сам потрясён тем фактом, что моя уловка сработала. Держи свой товар, Лист Какао.";
			link.l1.go = "ZsI_MirFinal_2";
		break;
		
		case "ZsI_MirFinal_2":
			dialog.text = "Сын Моря хорошо говорить. Спасать индеец - большой дело! Большой награда!";
			link.l1 = "Ого! Сколько же тут всего... И камень с дыркой, и амулет какой-то...";
			link.l1.go = "ZsI_MirFinal_3";
			AddItems(pchar, "jewelry53", 180);
			AddItems(pchar, "cannabis1", 3);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "talisman11");
			//Log_info("Вы получили 180 маленьких жемчужин");
			//Log_info("Вы получили амулет Каскавелла");
			//Log_info("Вы получили оберег Куриный Бог");
			//Log_info("Вы получили 3 травы Дьявола");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_MirFinal_3":
			dialog.text = "А у Сын Моря есть мушкет? За мушкет давать высокий цена!";
			link.l1 = "Только орудие с корабля могу предложить. Иди своей дорогой, Лист Какао, пока нас всех снова не заприметили.";
			link.l1.go = "ZsI_MirFinal_4";
		break;
		
		case "ZsI_MirFinal_4":
			dialog.text = "Хороший сделка! Сын Моря, если ходить в сельва, брать огненный оружие. Встретить индеец - выгодный сделка!";
			link.l1 = "Учту на будущее. Прощай, Лист Какао.";
			link.l1.go = "ZsI_MirFinal_5";
		break;
		
		case "ZsI_MirFinal_5":
			DialogExit();
			
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_ExitTown")], false);
			LAi_SetPlayerType(pchar);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "ZsI_officer_Draka":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_ExitTown")], false);
			LAi_SetFightMode(pchar, true);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeCharacterComplexReputation(pchar, "authority", -2);	
			ChangeIndianRelation(5.0);
			ChangeCharacterNationReputation(pchar, FRANCE, -10);
			sld = CharacterFromID("ListKakao");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetImmortal(sld, false);
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("ZsI_Patrul_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "ZsI_officer_Draka_3");
		break;
		
		case "ZsI_Final":
			ChangeIndianRelation(5.0);
			dialog.text = "Ой-ей! Плохой решение, Сын Моря. Зачем так делать?";
			link.l1 = "Уф... Пять минут назад это казалось правильным... А теперь я уже не уверен... Всё же французов убил. И как мне теперь быть? А если узнают? Чёрт! Чёрт!";
			link.l1.go = "ZsI_Final_2";
		break;
		
		case "ZsI_Final_2":
			dialog.text = "Теперь быть облава. Солдаты всех убивать. Два патруль не простить. Лист Какао осторожно воевать, думать голова. А ты, Сын Моря... Плохой решение. Лист Какао всё равно умирать. Духи так хотеть.";
			link.l1 = "Ох... А сделка-то наша ещё в силе?";
			link.l1.go = "ZsI_Final_3";
		break;
		
		case "ZsI_Final_3":
			dialog.text = "Плохой решение, Сын Моря. Но благодарить. Большой награда.";
			link.l1 = "Не такая уж и большая, учитывая все обстоятельства...";
			link.l1.go = "ZsI_Final_4";
			AddItems(pchar, "jewelry53", 180);
			AddItems(pchar, "cannabis1", 3);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "talisman11");
			//Log_info("Вы получили 180 маленьких жемчужин");
			//Log_info("Вы получили амулет Каскавелла");
			//Log_info("Вы получили оберег Куриный Бог");
			//Log_info("Вы получили 3 травы Дьявола");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_Final_4":
			dialog.text = "Сын Моря, если ты выживать и потом ходить в сельва, брать огненный оружие. Встретить индеец - быть сделка.";
			link.l1 = "Учту на будущее. Прощай, Лист Какао.";
			link.l1.go = "ZsI_Final_5";
		break;
		
		case "ZsI_Final_5":
			DialogExit();
			
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			LAi_SetImmortal(npchar, true);
			npchar.lifeday = 0;
		break;
		
		case "ZsI_officerKIll":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("ListKakao"));
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("ZsI_officerKIll_1", 0.1);
			DoQuestCheckDelay("ZsI_officerKIll_2", 1.3);
			AddItems(pchar, "pistol1", 2);
			AddItems(pchar, "GunPowder", 20);
			AddItems(pchar, "bullet", 20);
		break;
		
		//Торговец Барбье по квесту "Деньги на деревьях"
		case "MOT_Barbie":
			dialog.text = "Здравствуйте, капитан Шарль де Мор. Меня зовут Шарль Барбье. Могу я занять немного вашего времени?";
			link.l1 = "Капитан Шарль де Мор... Звучит, однако! Слушаю вас, месье.";
			link.l1.go = "MOT_Barbie_2";
		break;
		
		case "MOT_Barbie_2":
			dialog.text = "Всегда рад встретить коллегу, да к тому же ещё и тёзку! У меня есть для вас работа, капитан. Видите-ли, мне нужен эскорт до Сен-Пьера и...";
			link.l1 = "Но это же всего в двух днях пути! И потом, защитник из меня пока никакой - кораблём я командую без году неделя.";
			link.l1.go = "MOT_Barbie_3";
		break;
		
		case "MOT_Barbie_3":
			dialog.text = "Ха! Ценю честность и прямоту! Шарль, уж простите меня за фривольность в обращении, но вы как раз тот человек, который мне и нужен.";
			link.l1 = "Хм... Я что-то такое уже слышал совсем недавно. И в результате попал в засаду, устроенную мне пиратами у Ле-Франсуа.";
			link.l1.go = "MOT_Barbie_4";
		break;
		
		case "MOT_Barbie_4":
			dialog.text = "Я слышал об этой истории и именно поэтому решил обратиться к вам\nВо-первых, я везу достаточно ценный груз, и на него всегда могут объявиться охотники, но ваша недавняя победа над пиратской шайкой заставит отребье из Ле-Франсуа дважды подумать, прежде чем снова что-то выкинуть\nВо-вторых, вы вхожи к самому Фадею Московиту, а это сильная рекомендация и гарантия, что с вами можно вести дела.";
			link.l1 = "Убедительная речь, месье. И во сколько вы оцените подобную услугу?";
			link.l1.go = "MOT_Barbie_5";
		break;
		
		case "MOT_Barbie_5":
			dialog.text = "Это не услуга, а совместное предприятие, капитан! Я заплачу вам сорок золотых монет, если вы сопроводите меня до Сен-Пьера в разумные сроки.";
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				notification("Вызывающий доверие", "Trustworthy");
				link.l1 = "(Вызывающий доверие) Мне совсем в другую сторону, месье. Поэтому, я попрошу оплату вперёд.";
				link.l1.go = "MOT_Barbie_Torg";
			}
			else
			{
				notification("Не открыта способность", "Trustworthy");
			}
			link.l2 = "Недурно - мне всё равно в ту же сторону. По рукам!";
			link.l2.go = "MOT_Barbie_Soglasen";
			link.l3 = "Ценный груз, говорите? Простите, месье, но с меня пока хватит приключений.";
			link.l3.go = "MOT_Barbie_Otkaz";
		break;
		
		case "MOT_Barbie_Torg":
			dialog.text = "Сложно отказать такому серьёзному молодому человеку, капитан. Прошу - ваши сорок полновесных дублонов. Надеюсь, мы можем отправляться без промедлений? Время - деньги.";
			link.l1 = "Мы надолго не задержимся месье. Скоро выходим в море.";
			link.l1.go = "MOT_Barbie_Escadra";
			
			AddItems(pchar, "gold_dublon", 40);
			Log_info("Получено 40 дублонов");
			PlaySound("Interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddCharacterExpToSkill(pchar, "Commerce", 20);
		break;
		
		case "MOT_Barbie_Soglasen":
			dialog.text = "Вот и славно! Отправляюсь готовиться к отплытию!";
			link.l3 = "";
			link.l3.go = "MOT_Barbie_Escadra";
		break;
		
		case "MOT_Barbie_Otkaz":
			dialog.text = "Жаль, но навязываться не буду. Хорошего дня, капитан.";
			link.l3 = "";
			link.l3.go = "MOT_Barbie_Otkaz_2";
		break;
		
		case "MOT_Barbie_Otkaz_2":
			DialogExit();
			
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload6_back", "none", "", "", "", -1);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "MOT_Barbie_Escadra":
			DialogExit();
			
			SetQuestHeader("MoneyOnTrees");
			AddQuestRecord("MoneyOnTrees", "1");
			
			FantomMakeCoolSailor(npchar, SHIP_BARKENTINE, "Шарль", CANNON_TYPE_CANNON_LBS3, 40, 33, 20);
			npchar.Ship.Mode = "trade";
			SetCharacterRemovable(npchar, false);
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.CompanionEnemyEnable = true;
			SetCrewQuantity(npchar, 35);
			SetCharacterGoods(npchar, GOOD_ROPES, 30);
			LAi_SetImmortal(npchar, false);
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			SetTimerCondition("MOT_ZadanieProvaleno", 0, 0, 14, false);
			PChar.quest.MOT_Zahvatili.win_condition.l1 = "NPC_Death";
			PChar.quest.MOT_Zahvatili.win_condition.l1.character = "SharlieBarbie";
			PChar.quest.MOT_Zahvatili.win_condition = "MOT_Zahvatili";
			PChar.quest.MOT_Dostavili.win_condition.l1 = "location";
			PChar.quest.MOT_Dostavili.win_condition.l1.location = "FortFrance_town";
			PChar.quest.MOT_Dostavili.win_condition = "MOT_Dostavili";
		break;
		
		case "MOT_Barbie_101":
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				dialog.text = "Благодарю вас за образцовое сопровождение, капитан. Хорошо, что обошлось без приключений.";
				link.l1 = "Приятно было иметь с вами дело, месье. А теперь, извините, но у меня много дел.";
			}
			else
			{	
				dialog.text = "Благодарю вас за образцовое сопровождение, капитан. Хорошо, что обошлось без приключений. Вот ваша оплата - сорок полновесных дублонов.";
				link.l1 = "Приятно было иметь с вами дело, месье. А теперь, извините, но у меня много дел.";
				AddItems(pchar, "gold_dublon", 40);
				Log_info("Получено 40 дублонов");
				PlaySound("Interface\important_item.wav");
			}
			link.l1.go = "MOT_Barbie_102";
		break;
		
		case "MOT_Barbie_102":
			dialog.text = "Шарль...";
			link.l1 = "Я вас слушаю, Шарль. Вы выглядите встревоженным. Что-то случилось?";
			link.l1.go = "MOT_Barbie_103";
			RemoveCharacterCompanion(pchar, npchar);
			npchar.lifeday = 0;
		break;
		
		case "MOT_Barbie_103":
			dialog.text = "Эх, ладно. Поскольку вы парень надёжный, да и Фадея знаете\nСлушайте, торговля - дело рискованное, так?";
			link.l1 = "Вам виднее.";
			link.l1.go = "MOT_Barbie_104";
		break;
		
		case "MOT_Barbie_104":
			dialog.text = "Мне удалось очень дёшево закупить несколько бухт канатов на Гваделупе у... ну вы поняли. Я планировал быстро реализовать их в Сен-Пьере и на вырученные деньги закупить кофе для дальнейшей перепродажи в Виллемстаде. Хороший маршрут получился бы.";
			link.l1 = "Не совсем понимаю, у кого вы купили товар, но в чём проблема? Канаты погрызли крысы?";
			link.l1.go = "MOT_Barbie_105";
		break;
		
		case "MOT_Barbie_105":
			dialog.text = "Нет, что вы! Я постоянно держу достаточно мышьяка на корабле для защиты товара. Беда в том, что, как только мы прибыли сюда, мне достаточно доходчиво дали понять, что канаты у меня не примут. А это значит, что я в убытке.";
			link.l1 = "Постойте-ка, месье. Я ни в коем случае не хочу вас оскорбить, однако всё это звучит весьма сомнительно. Вы говорите о вашем грузе так, как будто он соткан из золота. А между тем, у меня весь корабль просто завешен этими канатами - кому они вообще могут понадобится?";
			link.l1.go = "MOT_Barbie_106";
		break;
		
		case "MOT_Barbie_106":
			dialog.text = "Вы же здесь совсем недавно... А держитесь уже так уверенно, что я и забыл об этой детали. Шарль, канаты эти - высшего качества, сделаны из превосходной пеньки и сотканы на мануфактурах московского царя. Товар этот назначения стратегического и используется при оснастке военных кораблей. Англичане держат торговые пути с Московией под своим контролем, свободное обращение этих канатов под запретом. Да и другие нации стремятся весь доступный им оборот полностью прибрать для своих верфей в Европе.";
			link.l1 = "Так это контрабанда?";
			link.l1.go = "MOT_Barbie_107";
		break;
		
		case "MOT_Barbie_107":
			dialog.text = "Да. К сожалению, год назад, у меня вышло некоторое недопонимание с контрабандистами Сантьяго. Я давно забыл об этой истории, но эти люди поддерживают тесные контакты друг с другом и всё помнят. Вот вам совет: не вздумайте их злить и срывать сделки, потом не расхлебаете.";
			link.l1 = "Спасибо, но контрабанда меня не интересует.";
			link.l1.go = "MOT_Barbie_108";
		break;
		
		case "MOT_Barbie_108":
			dialog.text = "Зря! Хорошие деньги можно заработать и честным путём, но вот большие деньги - уже не получится. В любом случае, я не просто так завёл с вами этот достаточно рискованный для меня разговор. Я предлагаю вам выкупить у меня груз канатов. Местные дельцы обретаются в таверне и они вам точно не откажут. Заработаете солидные деньги, даже не выходя в открытое море!";
			link.l1 = "Хм... Сколько вы просите за груз?";
			link.l1.go = "MOT_Barbie_109";
		break;
		
		case "MOT_Barbie_109":
			dialog.text = "Десять тысяч песо. Это совсем небольшая сумма, а перепродажа канатов контрабандистам принесёт вам солидную прибыль.";
			if (sti(pchar.Money) >= 10000)
			{
				link.l1 = "Никогда не прощу себе, если откажусь от такой возможности. Держите ваше серебро и проследите, чтобы товар был немедленно доставлен ко мне на корабль.";
				link.l1.go = "MOT_Barbie_ContraSoglasen";
			}
			if (sti(pchar.Money) >= 7000)
			{
				link.l2 = "Это рискованное дело, коллега. Давайте пойдём друг другу навстречу? Я приму ваши канаты за семь тысяч.";
				link.l2.go = "MOT_Barbie_ContraTorg";
			}
			link.l3 = "Это огромная сумма, месье. Я сочувствую вашему положению, но такой риск на себя не возьму.";
			link.l3.go = "MOT_Barbie_ContraOtkaz";
		break;
		
		case "MOT_Barbie_ContraSoglasen":
			dialog.text = "Ох, спасибо вам, Шарль! Вы спасли меня от долговой ямы! Товар будет доставлен немедленно - со всеми мерами предосторожности\nИ позвольте дать вам один совет, как коллеге-негоцианту: найдите себе хорошего казначея, закупитесь кофе в Сен-Пьере и продайте его с выгодой в Виллемстаде. Местные столицы платят хорошую цену за товары колониального производства и вывозят их в Европу, где продают, получая уже баснословные барыши. Успехов в торговле, друг!";
			link.l1 = "Прощайте, месье.";
			link.l1.go = "MOT_Barbie_ContraSoglasen_2";
			AddCharacterGoodsSimple(pchar, GOOD_ROPES, 30);
			AddMoneyToCharacter(pchar, -10000);
			Log_info("Получено 30 канатов");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "MOT_Barbie_ContraSoglasen_2":
			DialogExit();
			
			AddQuestRecord("MoneyOnTrees", "5");
			CloseQuestHeader("MoneyOnTrees");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			
			sld = CharacterFromID("SharlieBarbie");
			sld.lifeday = 0;
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "MOT_Barbie_ContraTorg":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) > 30)
			{
				notification("Проверка пройдена", SKILL_COMMERCE);
				dialog.text = "Ох, спасибо вам, Шарль! Вы спасли меня от долговой ямы! Товар будет доставлен немедленно - со всеми мерами предосторожности\nИ позвольте дать вам один совет, как коллеге-негоцианту: закупитесь кофе в Сен-Пьере и продайте его с выгодой в Виллемстаде. Местные столицы платят хорошую цену за товары колониального производства и вывозят их в Европу, где продают, получая уже баснословные барыши. Успехов в торговле, друг!";
				link.l1 = "Прощайте, месье.";
				link.l1.go = "MOT_Barbie_ContraSoglasen_2";
				AddCharacterGoodsSimple(pchar, GOOD_ROPES, 30);
				AddMoneyToCharacter(pchar, -7000);
				Log_info("Получено 30 канатов");
				PlaySound("Interface\important_item.wav");
			}
			else
			{
				notification("Недостаточно развит навык (31)", SKILL_COMMERCE); 
				dialog.text = "Нет, капитан. Товар у нас серьёзный и требует самого серьёзного отношения. Большинство вольных капитанов даже мечтать не могут о реализации товаров стратегического назначения. Боюсь, торг здесь неуместен.";
				if (sti(pchar.Money) >= 10000)
				{
					link.l1 = "Держите ваше серебро и проследите, чтобы товар был немедленно доставлен ко мне на корабль.";
					link.l1.go = "MOT_Barbie_ContraSoglasen";
				}
				link.l2 = "Это огромная сумма, месье. Я сочувствую вашему положению, но такой риск на себя не возьму.";
				link.l2.go = "MOT_Barbie_ContraOtkaz";
			}
		break;
		
		case "MOT_Barbie_ContraOtkaz":
			dialog.text = "Жаль! Прощайте, капитан.";
			link.l1 = "";
			link.l1.go = "MOT_Barbie_ContraOtkaz_2";
		break;
		
		case "MOT_Barbie_ContraOtkaz_2":
			DialogExit();
			
			AddQuestRecord("MoneyOnTrees", "4");
			CloseQuestHeader("MoneyOnTrees");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			
			sld = CharacterFromID("SharlieBarbie");
			sld.lifeday = 0;
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		//Миниквест "Делюк"
		//Матрос Алонсо
		case "Del_Alonso":
			dialog.text = "Беда, кэп.";
			link.l1 = "Ну?";
			link.l1.go = "Del_Alonso_2";
		break;
		
		case "Del_Alonso_2":
			dialog.text = "Штурмана нашего арестовали и упекли в местную тюрьму. Говорят, за долги.";
			link.l1 = "Опять?!";
			link.l1.go = "Del_Alonso_3";
		break;
		
		case "Del_Alonso_3":
			dialog.text = "Такой уж бедовый он человек, кэп.";
			link.l1 = "Как не вовремя! Без штурмана я тут застряну. Придётся снова выкупать его из долговой ямы! Пойду беседовать с комендантом...";
			link.l1.go = "Del_Alonso_4";
		break;
		
		case "Del_Alonso_4":
			dialog.text = "Разрешите обратиться, кэп?";
			link.l1 = "Да?";
			link.l1.go = "Del_Alonso_5";
		break;
		
		case "Del_Alonso_5":
			dialog.text = "Зачем вам эти траты и хлопоты? Такой человек и гальюн превратит в крюйт-камеру.";
			link.l1 = "А у меня есть выбор? Штурманы на дороге не валяются, так что придётся пока обходиться тем, кто есть.";
			link.l1.go = "Del_Alonso_6";
		break;
		
		case "Del_Alonso_6":
			dialog.text = "Отличный штурман, ясное дело, зверь редкий. Но вам отличный пока и не нужен, сойдёт и просто хороший. Раньше ведь как было? Человек вы новый, кораблём ранее не командовали, люди вас не знали. Вот и пришлось по тюрьмам искать себе специалиста. Но то прошлое, а сейчас народ уже шепчется, как вы пирата того разделали, и к каким важным людям вхожи. Да и команда теперь за вас, кэп, - полюбились вы нам.";
			link.l1 = "Приятно слышать, Алонсо. Ради такой оценки стоило рвать жилы. И какое мнение у команды по поводу всей этой истории с Фульком?";
			link.l1.go = "Del_Alonso_7";
		break;
		
		case "Del_Alonso_7":
			dialog.text = "Вы быстро учитесь, кэп. Команда считает, что хоть офицер в целом он и толковый, и с нашим братом ведёт себя по-людски, но хлопот таких не стоит. Недавно офицеров с большого торговца распустили, - может, загляните в таверну? Наверняка там будет нужный вам человек. А про Делюка забудьте. Такое вот у людей нарисовалось мнение.";
			link.l1 = "Спасибо за совет, Алонсо. Я знал, что всегда могу на тебя положиться. Отправляйся на корабль и принимай вахту, пока я буду разбираться с возникшей проблемой.";
			link.l1.go = "Del_Alonso_8";
		break;
		
		case "Del_Alonso_8":
			dialog.text = "Так точно!";
			link.l1 = "...";
			link.l1.go = "Del_Alonso_9";
		break;
		
		case "Del_Alonso_9":
			DialogExit();
			SetQuestHeader("FolkeDeluc");
			AddQuestRecord("FolkeDeluc", "1");
			
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			SetFunctionLocationCondition("FortfranceJailOff_AddQuestMark", "fortfrance_prison", false);
			QuestCloseSeaExit();
			sld = CharacterFromID("Folke");
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Del_Folke_1";
			RemovePassenger(pchar, sld);
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "FortFrance_prison", "goto", "goto9");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			pchar.questTemp.Del_Deluck = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("Del_shturman", "mercen_4", "man", "man", 5, FRANCE, 3, false, "quest"));
			GiveItem2Character(sld, "blade_03");
			EquipCharacterByItem(sld, "blade_03");
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Del_shturman";
			LAi_SetSitType(sld);
			sld.greeting = "officer_hire";
			SetSelfSkill(sld, 21, 23, 18, 33, 25);
			SetShipSkill(sld, 25, 10, 8, 6, 35, 11, 13, 25, 14);
			SetSPECIAL(sld, 7, 10, 6, 8, 7, 8, 4);
			sld.rank = 5;
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "BasicDefense");
			//sld.quest.officertype = "navigator";
			FreeSitLocator("FortFrance_tavern", "sit4");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "sit", "sit4");
			AddLandQuestMark(characterFromId("Del_shturman"), "questmarkmain");
		break;
		
		//Делюк
		case "Del_Folke_1":
			DelLandQuestMark(npchar);
			dialog.text = "Кэп...";
			link.l1 = "У меня много вопросов, но задам всего один: как?! Каким образом ты умудрился влезть в новые долги за столь короткий срок? Всё это время ты был со мной, обучал меня основам морского дела!";
			link.l1.go = "Del_Folke_2";
		break;
		
		case "Del_Folke_2":
			dialog.text = "Стыдно признаться, кэп, но займов-то я успел набрать у разных ростовщиков ещё задолго до нашего с вами знакомства. Планировал не высовываться и торчать на корабле, пока не заработаю у вас на службе достаточно денег, чтобы покрыть долги. Так бы и расплатился, да промашка вышла: потянул меня чёрт к одной хорошей бабе тут, в Сен-Пьере... Ну и прямо из-под неё меня солдаты и забрали под белы рученьки. Как так вышло - не знаю, но клянусь, на Мартинике я новых долгов не делал!";
			link.l1 = "Ты безнадёжный дурак, Делюк, и мне жаль потраченных на тебя денег, сил и времени. Из-за тебя я стал посмешищем в Сен-Пьере!";
			link.l1.go = "Del_Folke_3a";
			link.l2 = "Впечатляет, Фульк. Спасибо за анекдот.";
			link.l2.go = "Del_Folke_3b";
		break;
		
		case "Del_Folke_3a":
			AddComplexSelfExpToScill(10, 10, 10, 10);
			dialog.text = "Что будете делать, кэп? Может, всё-таки выручите ещё раз? Нового штурмана найти - задача непростая.";
			link.l1 = "Сиди пока тут. Я приму решение. Может, к ростовщику ещё раз загляну.";
			link.l1.go = "Del_Folke_4";
		break;
		
		case "Del_Folke_3b":
			AddCharacterExpToSkill(pchar, "Sailing", 10);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 10);//торговля
			dialog.text = "Что будете делать, кэп? Может, всё-таки выручите ещё раз? Нового штурмана найти - задача непростая.";
			link.l1 = "Сиди пока тут. Я приму решение. Может, к ростовщику ещё раз загляну.";
			link.l1.go = "Del_Folke_4";
		break;
		
		case "Del_Folke_4":
			dialog.text = "Куда я денусь, кэп.";
			link.l1 = "...";
			link.l1.go = "Del_Folke_5";
		break;
		
		case "Del_Folke_5":
			DialogExit();
			
			pchar.questTemp.Del_Rostovshik = true;
			LAi_CharacterDisableDialog(npchar);
			AddLandQuestMark(characterFromId("FortFrance_usurer"), "questmarkmain");
		break;
		
		case "Del_Folke_10":
			dialog.text = "Кэп, спасибо вам. Вы оплатили мои долги, но теперь я в пожизненном долгу перед вами. И я чертовски рад этому! Клянусь, вернее человека вам будет не сыскать!";
			link.l1 = "Некоторые долги, видимо, можно погасить, только задолжав другим. Займись делом, Фульк. У нас впереди целое море работы.";
			link.l1.go = "Del_Folke_11a";
			link.l2 = "Никогда не забывай об этом, Делюк. В третий раз я тебя уже просто пристрелю.";
			link.l2.go = "Del_Folke_11b";
			
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			QuestOpenSeaExit()
			sld = CharacterFromID("Del_shturman");
			sld.lifeday = 0;
			
			sld = CharacterFromID("Del_Ohranik");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", -1);
		break;
		
		case "Del_Folke_11a":
			AddCharacterExpToSkill(pchar, "Sailing", 10);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 10);//торговля
			dialog.text = "Так точно, кэп!";
			link.l1 = "...";
			link.l1.go = "Del_Folke_12";
		break;
		
		case "Del_Folke_11b":
			AddComplexSelfExpToScill(10, 10, 10, 10);
			dialog.text = "Так точно, кэп!";
			link.l1 = "...";
			link.l1.go = "Del_Folke_12";
		break;
		
		case "Del_Folke_12":
			DialogExit();
			EndQuestMovie();
			AddQuestRecord("FolkeDeluc", "3");
			CloseQuestHeader("FolkeDeluc");
			
			ChangeCharacterComplexReputation(pchar, "authority", -2);
			AddCrewMorale(Pchar, -30);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.quest.meeting = true;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			npchar.location = "None";
			npchar.Dialog.CurrentNode = "hired";
			npchar.Payment = true;
			SetCharacterPerk(npchar, "ByWorker");
			DeleteAttribute(npchar, "CompanionDisable");
		break;
		
		//Штурман из таверны. Стандартный диалог, но с некоторыми изменениями (обучение найма для новичков)
		case "Del_shturman":
			dialog.text = "Офицер не нужен, капитан?";
    		Link.l1 = "Офицер? А на что ты годен?";
    		Link.l1.go = "Del_Node_2";
			Link.l2 = "Нет, у меня полный комплект.";
			Link.l2.go = "Exit";
			NextDiag.TempNode = "Del_OnceAgain";
		break;		
		case "Del_Node_2":
			dialog.text = "Я лучший штурман в этих водах. Ещё поверхностно медицину знаю. Готов оказать вам услугу, пойдя на службу.";
			Link.l1 = "Сколько ты хочешь?";
			Link.l1.go = "Del_price";
			Link.l2 = "А что ты из себя представляешь как специалист?";
			Link.l2.go = "Del_ShowParam_exit";
			Link.l3 = "Увы, у меня уже есть штурман.";
			Link.l3.go = "Exit";
		break;		
		case "Del_price":
			dialog.text = "Думаю, мы с вами сойдёмся на 4000 песо.";
			Link.l1 = "Не слишком ли ты много хочешь?";
			Link.l1.go = "Del_trade";
			Link.l2 = "Я "+ GetSexPhrase("согласен","согласна") +". Считай себя зачисленным в команду.";
			Link.l2.go = "Del_hire";
			Link.l3 = "Ты не стоишь этих денег. Прощай.";
			Link.l3.go = "exit";
		break;	
		case "Del_ShowParam_exit":
			NextDiag.TempNode = "Del_OnceAgain";
			NPChar.quest.meeting = true;
			DialogExit();
			
			PChar.SystemInfo.OnlyShowCharacter = true;
            LaunchCharacter(NPChar);
		break;		
		case "Del_OnceAgain":
			NextDiag.TempNode = "Del_OnceAgain";
			dialog.text = "Неужели передумали, капитан? Решили, что новый штурман вам не помешает?";
			// boal -->
			if (FindFreeRandomOfficer() > 0)
			{
                Link.l1 = "Пожалуй, так. Сколько ты хочешь?";
                Link.l1.go = "Del_price";
			}
			Link.l2 = "Каков ты будешь в деле?";
			Link.l2.go = "Del_ShowParam_exit";
			// boal <--
			Link.l3 = "У меня полный комплект. Счастливо оставаться.";
			Link.l3.go = "exit";
		break;		
		case "Del_trade":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) > 25)
			{
				dialog.text = "Хорошо... Пожалуй, я готов согласиться даже на 2500 песо. Ну как?";
				Link.l1 = "Вот это уже лучше. Ты принят.";
				Link.l1.go = "Del_hire";
				pchar.questTemp.Del_SniziliTsenu = true;
			}
			else
			{
				dialog.text = "Увы, капитан, я стою именно столько, сколько запросил. Если это слишком дорого для вас - поищите кого-нибудь другого.";
				Link.l1 = "Ну ладно, я "+ GetSexPhrase("согласен","согласна") +". Я беру тебя.";
				Link.l1.go = "Del_hire";				
				Link.l2 = "Так я и поступлю. Всего хорошего.";
				Link.l2.go = "exit";
			}
		break;		
		case "Del_hire":
			if (CheckAttribute(pchar, "questTemp.Del_SniziliTsenu"))
			{
				if (sti(pchar.Money) >= 2500)
				{
					AddMoneyToCharacter(pchar, -2500);
					NextDiag.TempNode = "OnboardSoon";
					dialog.text = "Благодарю вас, капитан. Вы не пожалеете, что отдали мне эти деньги.";
					Link.l1 = "Хочется в это верить.";
					Link.l1.go = "Del_Exit_hire";
					DeleteAttribute(pchar, "questTemp.Del_SniziliTsenu");
				}
				else
				{
					dialog.text = "Эй, похоже, у вас проблемы с наличностью! Извините, капитан, но я не работаю в кредит.";
					Link.l1 = "Ах ты, чёрт!";
					Link.l1.go = "Exit";								
				}
			}
			else
			{
				if (sti(pchar.Money) >= 4000)
				{
					AddMoneyToCharacter(pchar, -4000);
					NextDiag.TempNode = "Del_OnboardSoon";
					dialog.text = "Благодарю вас, капитан. Вы не пожалеете, что отдали мне эти деньги.";
					Link.l1 = "Хочется в это верить.";
					Link.l1.go = "Del_Exit_hire";
				}
				else
				{
					dialog.text = "Эй, похоже, у вас проблемы с наличностью! Извините, капитан, но я не работаю в кредит.";
					Link.l1 = "Ах ты, чёрт!";
					Link.l1.go = "Exit";								
				}
			}
		break;
		case "Del_OnboardSoon":			
			NextDiag.TempNode = "Del_OnboardSoon";
			dialog.text = "Сейчас я допью, капитан, и отправлюсь на борт. Не извольте беспокоиться - я успею до отплытия.";
			Link.l1 = "Хорошо. Опоздаешь - заставлю драить палубу!";
			Link.l1.go = "Exit";											
		break;
		case "Del_exit_hire":
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.Dialog.CurrentNode = "hired";
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NPChar.quest.meeting = true;
			npchar.loyality = 18;
			
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			AddCrewMorale(Pchar, 30);
			QuestOpenSeaExit();
			DelLandQuestMark(npchar);
			pchar.quest.FortfranceJailOff_AddQuestMark.over = "yes";
			if (GetCharacterIndex("FortFranceJailOff") != -1)
			{
				DelLandQuestMark(characterFromId("FortFranceJailOff"));
			}
			sld = CharacterFromID("Folke");
			LAi_CharacterDisableDialog(sld);
			DeleteAttribute(pchar, "questTemp.Del_Deluck");
			DeleteAttribute(pchar, "questTemp.Del_DeluckSvoboda");
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik");
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik_repeat");
			pchar.questTemp.Del_DeluckSiditTurma = true;
			AddQuestRecord("FolkeDeluc", "4");
			CloseQuestHeader("FolkeDeluc");
			DialogExit();
		break;
		
		//Квест "Травля крысы"
		//Капитан корабля Хейтер
		case "TK_Kapitan":
			dialog.text = "А-ать! Сдаюсь! Я сдаюсь, чёрт побери!";
			link.l1 = "Теперь вы мой пленник, милейший. Но вас уже ожидают в Сен-Пьере, знаете ли, виселица по вам плачет.";
			link.l1.go = "TK_Kapitan_1";
			PChar.quest.TK_Potopil.over = "yes";
		break;
		
		case "TK_Kapitan_1":
			dialog.text = "Значит, вот как карта мне легла. А как узнал, где меня ловить?";
			link.l1 = "Губернатор лично сообщил мне все детали!";
			link.l1.go = "TK_Kapitan_2";
		break;
		
		case "TK_Kapitan_2":
			dialog.text = "Вот скотина! Видать, пронюхал про мои планы и решил мне парус приспустить!";
			link.l1 = "Ещё одно оскорбление в адрес его светлости, и ваше путешествие до Сен-Пьера будет коротким, но запоминающимся!";
			link.l1.go = "TK_Kapitan_3";
		break;
		
		case "TK_Kapitan_3":
			dialog.text = "Что? Да я не об этой твоей светлости, приятель. Я говорю про Жака Добряка\nДьявол, правдивы слухи оказались! Понял Барбазон, что птица я вольная, на подъёме, и, чтобы я ему не мешал, сдал меня твоему губернатору. Иначе бы ты меня просто не нашёл.";
			link.l1 = "Вы бредите. Губернатор Мартиники не может опуститься до контактов с пиратским вожаком!";
			link.l1.go = "TK_Kapitan_4";
		break;
		
		case "TK_Kapitan_4":
			dialog.text = "Ага, как же. Не сам, конечно, через посредников, но переговорил с Добряком как миленький, ведь ему сплошное удобство: опасный пират-еретик на виселице, торговля в безопасности, а расходы на проведённую военную операцию задокументированы и обоснованы, ха! Я сам служил, думаешь, не знаю, как дела делаются? А ты в гарнизоне служишь, приятель?";
			link.l1 = "Я служу своей стране, и на этом наше знакомство предлагаю закончить. Прошу пожаловать в трюм.";
			link.l1.go = "TK_Kapitan_5";
		break;
		
		case "TK_Kapitan_5":
			dialog.text = "Погоди, ну так и я не кастилец какой-нибудь, и в море сегодня вышел не для того, чтобы наших торгашей щипать. Давай договоримся?";
			link.l1 = "Для пленника вы слишком словоохотливы, и поощрять я это не собираюсь. В трюм. Живо.";
			link.l1.go = "TK_Kapitan_7_1";
			link.l2 = "Надеетесь избежать петли?";
			link.l2.go = "TK_Kapitan_6";
		break;
		
		case "TK_Kapitan_6":
			dialog.text = "Я охочусь на одного жирного кота, но с радостью уступлю его тебе, если отпустишь. Приятель, за моё бренное тело выплатят всего-то пару тысяч серебром, я же предлагаю тебе заработать гораздо больше - и без налогов.";
			if (CheckAttribute(pchar, "questTemp.MOT_SharlyBad"))
			{
				link.l1 = "Соблазнительное предложение... Пиратство для меня уже не впервой, хотя особой радости оно мне не доставляет.";
				link.l1.go = "TK_Kapitan_7";
			}
			else
			{
				link.l1 = "Я не пират!";
				link.l1.go = "TK_Kapitan_7";
			}
		break;
		
		case "TK_Kapitan_7":
			dialog.text = "Сам решай, кем быть: джентльменом удачи или нищим капитаном с принципами. Если нужны реальные деньги и свобода, которые они дают, то придётся тебе побывать и пиратом, и торгашом - всем понемногу. Лови момент, кэп.";
			link.l1 = "Выражаешься ты, конечно, весьма складно...";
			link.l1.go = "TK_Kapitan_8";
			link.l2 = "Кхм... Пожалуй, я доставлю тебя в Сен-Пьер, это будет самым правильным решением.";
			link.l2.go = "TK_Kapitan_7_1";
		break;
		
		case "TK_Kapitan_7_1":
			dialog.text = "Ну и чёрт с тобой!";
			link.l1 = "...";
			link.l1.go = "TK_Kapitan_Plen";
		break;
		
		case "TK_Kapitan_8":
			dialog.text = "Значит, уговор?";
			link.l1 = "Да. Говори, что за жирный кот, и проваливай на все четыре стороны.";
			link.l1.go = "TK_Kapitan_9";
		break;
		
		case "TK_Kapitan_9":
			dialog.text = "Один хитрозадый англичанин на барке 'Генрих' собирается в ближайшее время завершить свой вояж по контрабандистам и задорого сбыть в Виллемстаде товары с французских плантаций. На днях он выходит с Мартиники и сразу же отправляется на Кюрасао. Дело плёвое - охраны никакой, а сам барк почти полностью забит товаром в ущерб своей боеспособности. Рисковый парень, и делает всё правильно, но слишком затянул: слухи уже успели разойтись. Вот тебе мой совет, кэп: не брезгуй общаться с народом в таверне. Поставишь пьяницам пару кружек, так они тебе и не такое расскажут!";
			link.l1 = "Почему барк идёт без охраны?";
			link.l1.go = "TK_Kapitan_10";
		break;
		
		case "TK_Kapitan_10":
			dialog.text = "А как англичанину ещё свои дела на Кюрасао по-тихому проворачивать? На архипелаге между Англией и Нидерландами, считай, открытая война, а на торговую лицензию тратиться - удел терпеливых и не жадных, а к таким наш парень не относится.";
			link.l1 = "Но между Францией и Англией война-то не идёт. Каковы будут последствия, если я нападу на корабль нейтральной державы?";
			link.l1.go = "TK_Kapitan_11";
		break;
		
		case "TK_Kapitan_11":
			dialog.text = "Никаких, если наглеть не будешь. Команда, конечно, проболтается о твоём геройстве в первом же порту, но, пока ты не устраиваешь регулярную охоту на корабли англичан или голландцев, можешь спать спокойно. Приближайся к 'Генриху' под флагом враждебной Англии державы, или уж сразу под Весёлым Роджером. Заряди пушки картечью, подойди к барку на пистолетный выстрел, дай пару залпов и вперёд! Плёвое дело, кэп.";
			link.l1 = "Посмотрим. Я слово своё держу и отпускаю тебя на все четыре стороны. Надеюсь, ты не дашь мне повода об этом пожалеть.";
			link.l1.go = "TK_Kapitan_12";
		break;
		
		case "TK_Kapitan_12":
			dialog.text = "Не дам. Прощай, брат.";
			link.l1 = "...";
			link.l1.go = "TK_Kapitan_Otpustil";
		break;
		
		case "TK_Kapitan_Plen":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			sld.DontRansackCaptain = true;
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = GetCharacter(NPC_GenerateCharacter("TK_Heiter2", "mercen_8", "man", "man", sti(PChar.rank), PIRATE, -1, false, "pirate"));
			sld.name = "Даниэль";
			sld.lastname = "Монбар";
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto7");
			LAi_SetGroundSitType(sld);
			LAi_CharacterDisableDialog(sld);
			DoQuestCheckDelay("TK_KapitanSidit_1", 0.8);
		break;
		
		case "TK_Kapitan_Otpustil":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			sld.ShipEnemyDisable  = true;
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetCitizenType(sld);
			sld.lifeday = 0;
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			pchar.questTemp.TK_Otpustil = true;
			AddQuestRecord("TravlyaKrys", "4");
			
			SetTimerCondition("TK_GenrihSpawn", 0, 0, 1, false);	
		break;
		
		//Диего и Гийом за столиком по квесту "Встреча с Диего"
		case "VsD_DiegoAndErnat":
			dialog.text = "(обращаясь к французскому лейтенанту) А твои карточные дела я возьму на себя. Эй! Caramba! Ты мужчина или кто? Возьми себя в руки и не трясись, иначе я сам тебя в чувство приведу.";
			link.l1 = "";
			link.l1.go = "VsD_DiegoAndErnat_2";
			sld = CharacterFromID("GiumDyubua");
			LAi_CharacterEnableDialog(sld);
		break;
		
		case "VsD_DiegoAndErnat_2":
			DialogExit();
			StartInstantDialogNoType("GiumDyubua", "VsD_DiegoAndErnat_3", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "VsD_DiegoAndErnat_3":
			dialog.text = "(обращаясь к вам) Месье, прошу прощения, но вы нам немного мешаете.";
			link.l1 = "Да, разумеется. Приятного вам дня, господа.";
			link.l1.go = "VsD_DiegoAndErnat_4";
		break;
		
		case "VsD_DiegoAndErnat_4":
			DialogExit();
			sld = CharacterFromID("Diego");
			LAi_CharacterDisableDialog(sld);
			sld = CharacterFromID("GiumDyubua");
			LAi_CharacterDisableDialog(sld);
		break;
		
		//Гийом Дюбуа по квесту "Встреча с Диего"
		case "VsD_GiumDyubua":
			dialog.text = "Капитан де Мор! Постойте!";
			link.l1 = "Слушаю вас, лейтенант.";
			link.l1.go = "VsD_GiumDyubua_2";
			DelLandQuestMark(npchar);
		break;
		
		case "VsD_GiumDyubua_2":
			dialog.text = "Еле вас догнал. Возникла... небольшая накладка, капитан. Вечно у нас бардак!";
			link.l1 = "Отдышитесь и успокойтесь, пожалуйста.";
			link.l1.go = "VsD_GiumDyubua_3";
		break;
		
		case "VsD_GiumDyubua_3":
			dialog.text = "Да-да. Послушайте, у вас ведь ещё место в трюме остаётся после погрузки пушек?";
			link.l1 = "Я пока не сильно в таких нюансах разбираюсь, но, полагаю, что должно остаться.";
			link.l1.go = "VsD_GiumDyubua_4";
		break;
		
		case "VsD_GiumDyubua_4":
			dialog.text = "Замечательно! Командование хочет помочь операции у Порто Белло, чем может, и распорядилось доставить на фрегат 'Воинственный' ещё двести мер пороха. Это немного, но даже два дополнительных полновесных залпа способны переломить ход сражения!";
			link.l1 = "Хорошо, лейтенант, грузите этот порох - думаю, проблем не возникнет.";
			link.l1.go = "VsD_GiumDyubua_5";
		break;
		
		case "VsD_GiumDyubua_5":
			dialog.text = "Благодарю вас, капитан. Я сейчас же сообщу нашей погрузочной команде, благо они ещё не закончили с '" + PChar.Ship.Name + "'. Удачи вам на задании!";
			link.l1 = "Спасибо, а то и правда, бардак. До свидания, лейтенант.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("VsD_GoToCity");
		break;
		
		//Фульк или Алонсо по квесту "Встреча с Диего"
		case "VsD_FolkeAlonso":
			dialog.text = "Господи, капитан! Слава Богу, вас не задело!";
			link.l1 = "Какого чёрта?! Что с моим кораблём?!";
			link.l1.go = "VsD_FolkeAlonso_2";
		break;
		
		case "VsD_FolkeAlonso_2":
			dialog.text = "Не могу знать, капитан! Я тут с женщиной прощался... Дьявол! Эжени!";
			link.l1 = "Она погибла, "+npchar.name+". Мне очень жаль, но сейчас нам надо взять себя в руки и поскорее выяснить, не пострадали ли наши матросы.";
			link.l1.go = "VsD_FolkeAlonso_3";
		break;
		
		case "VsD_FolkeAlonso_3":
			dialog.text = "Только познакомились... А-ать! Докладываю: команда в момент взрыва, к счастью, почти вся ещё оставалась на берегу - парни решили как следует отдохнуть перед дальним рейсом... Но вот вахта, кэп... Не думаю, что кто-то выжил. Посмотрите вокруг! Даже на берегу людей зашибло, нас с вами чудом не контузило!";
			link.l1 = "А корабль? Корабль цел?!";
			link.l1.go = "VsD_FolkeAlonso_4";
		break;
		
		case "VsD_FolkeAlonso_4":
			dialog.text = "Цел?! Простите, капитан. Точно сказать пока ничего нельзя, но, судя по всему, взрыв произошёл прямо на верхней палубе, а не внутри. Активного пожара я не наблюдаю, и думаю, что мы ещё легко отделались, и корабль не потеряем.";
			link.l1 = "...";
			link.l1.go = "VsD_FolkeAlonso_5";
			sld = GetCharacter(CreateCharacterClone(CharacterFromID("PortPaxAmmoOff"), 0));
			sld.id = "PortPaxAmmoOff_clone";
			LAi_LoginInCaptureTown(sld, true);
			ChangeCharacterAddressGroup(sld, "PortPax_town", "quest", "quest1");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "VsD_FolkeAlonso_5":
			DialogExit();
			LAi_SetStayType(pchar);
			sld = CharacterFromID("PortPaxAmmoOff_clone");
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "VsD_Komendant";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 3, 0);
		break;
		
		case "VsD_Komendant":
			dialog.text = "Капитан, какого чёрта?!";
			link.l1 = "У меня тот же вопрос, полковник!";
			link.l1.go = "VsD_Komendant_1";
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				LAi_SetActorType(sld);
				LAi_ActorGoToLocator(sld, "reload", "reload1", "", -1);
			}
		break;
		
		case "VsD_Komendant_1":
			dialog.text = "Не смейте мне дерзить, де Мор! Вы согласились нам помочь, вы приняли на борт тяжёлые пушки - собственность Короны, и стратегической важности! Под строгую ответственность! Вы хоть понимаете, что эти орудия значат для всей операции?! Из-за вашей безалаберности она теперь под угрозой срыва! Под суд пойдёте!";
			link.l1 = "Успокойтесь, полковник! Произошло чудо: похоже, мой корабль уцелел, а ваш драгоценный груз в целости... почти.";
			link.l1.go = "VsD_Komendant_2";
		break;
		
		case "VsD_Komendant_2":
			dialog.text = "Что значит почти?!";
			link.l1 = "Я не могу ручаться, что те двести мер пороха, которые один из ваших лейтенантов попросил погрузить в последний момент, не пострадали. Скорее всего, именно они и взорвались - их совершенно точно должны были грузить последними.";
			link.l1.go = "VsD_Komendant_3";
		break;
		
		case "VsD_Komendant_3":
			dialog.text = "Что вы несёте, Шарль? Какой лейтенант? Какой порох? Такого распоряжения я не давал!";
			link.l1 = "Этот лейтенант совершенно точно был из вашего гарнизона. Имени его я не спросил, но он был в курсе операции.";
			link.l1.go = "VsD_Komendant_4";
		break;
		
		case "VsD_Komendant_4":
			dialog.text = "Вот значит как... Похоже, кастильцы тоже решили поиграть грубо. Я разберусь с этой досадной историей, капитан. А у вас - своя забота: вы уверены, что ваш корабль на плаву?";
			link.l1 = "На плаву - да, но ему совершенно точно не помешает серьёзный ремонт.";
			link.l1.go = "VsD_Komendant_5";
			SetMusic("classic_fra_music_day");
		break;
		
		case "VsD_Komendant_5":
			dialog.text = "Нет времени, капитан. Выходите в море немедленно и выполняйте задание. Слишком высоки ставки, так что придётся рискнуть.";
			link.l1 = "Хотя бы дайте нам один день, чёрт возьми! Местная верфь ведь может обеспечить необходимый ремонт! И что с моими людьми?! Наверняка есть убитые и раненые!";
			link.l1.go = "VsD_Komendant_6";
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				sld.Dialog.CurrentNode = "Tichingitu_officer";
			}
			if (GetCharacterIndex("Folke") != -1 && CheckPassengerInCharacter(pchar, "Folke"))
			{
				sld = CharacterFromID("Folke");
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.Dialog.Filename = "Enc_Officer_dialog.c";
				sld.Dialog.CurrentNode = "hired";
			}
			else
			{
				sld = CharacterFromID("Alonso");
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
		break;
		
		case "VsD_Komendant_6":
			dialog.text = "Если вы не заметили, то верфь горит. И нам ещё только предстоит выяснить, подожгли ли её специально, или это побочный результат взрыва. Ваши раненые получат лечение и уход, не переживайте за них, капитан. А убитых мы похороним за счёт Короны.";
			link.l1 = "Вы серьёзно? И это всё, что вы можете сделать?";
			link.l1.go = "VsD_Komendant_7";
			sld = CharacterFromID("VsD_Tsyganka");
			ChangeCharacterAddressGroup(sld, "PortPax_town", "reload", "reload5_back");
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "VsD_Komendant_7":
			dialog.text = "Капитан, я всё понимаю, но Франции сейчас нужна ваша помощь. Я выделю вам доски, и, если вы грамотно всё сделаете, то к Ямайке ваш корабль придёт уже почти полностью отремонтированным.";
			link.l1 = "Простите, но какие к чёрту доски? И причём тут Ямайка?";
			link.l1.go = "VsD_Komendant_8";
			pchar.ship.HP = sti(pchar.ship.HP) / 2;
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) - sti(pchar.ship.Crew.Quantity) / 7;
			AddCharacterGoodsSimple(pchar, GOOD_PLANKS, 100);
		break;
		
		case "VsD_Komendant_8":
			dialog.text = "Ваши матросы, без сомнения, смогут произвести экстренный ремонт прямо в море. И вообще, имейте в виду на будущее: на разные непредвиденные случаи всегда полезно иметь в команде профессионального плотника, а в трюме - небольшой запас досок и парусины. Что касается Ямайки - она вам почти по пути. Если не будете терять время, то там вы успеете осуществить уже полный ремонт корабля и доукомплектовать команду.";
			link.l1 = "Хорошо, так уж и быть. Немедленно выхожу в море, полковник.";
			link.l1.go = "VsD_Komendant_9";
			
			sld = CharacterFromID("PortRoyal_shipyarder");
			sld.TrialDelQuestMark = true;
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("PortRoyal", false);
		break;
		
		case "VsD_Komendant_9":
			DialogExit();
			LAi_SetStayType(pchar);
			
			sld = CharacterFromID("VsD_Tsyganka");
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "VsD_Tsyganka";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 3, 0);
			
			sld = CharacterFromID("PortPaxAmmoOff_clone");
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "gate_back", "none", "", "", "", -1);
		break;
		
		case "VsD_Tsyganka":
			dialog.text = "Куда торопишься, "+GetSexPhrase("соколик","голубушка")+"?";
			link.l1 = "Голубушка, не до тебя сейчас. Не видишь, что вокруг творится?";
			link.l1.go = "VsD_Tsyganka_1";
		break;
		
		case "VsD_Tsyganka_1":
			dialog.text = "Ох, горе страшное, но по руке твоей вижу, что беды только начинаются.";
			link.l1 = "Это понятно любому здравомыслящему человеку даже без взгляда на мою руку, которая, замечу, в перчатке. Ладно, я подыграю: какая нынче цена за то, чтобы отвести беду?";
			link.l1.go = "VsD_Tsyganka_2";
		break;
		
		case "VsD_Tsyganka_2":
			dialog.text = "Нет у меня такой власти, красавец. А если бы была - не расплатился бы. Но кое-чем помочь могу, ведь кораблик-то твой совсем плох.";
			link.l1 = "Никогда не замечал у вашей сестры плотницких амбиций.";
			link.l1.go = "VsD_Tsyganka_3";
			
			for (i=3; i<=8; i++)
			{				
				sld = CharacterFromID("VsD_MirnyeMan_"+i);
				LAi_SetCitizenType(sld);
			}
			for (i=3; i<=6; i++)
			{				
				sld = CharacterFromID("VsD_MirnyeWoman_"+i);
				LAi_SetCitizenType(sld);
			}
			for (i=1; i<=6; i++)
			{				
				sld = CharacterFromID("VsD_Sold_"+i);
				LAi_SetCitizenType(sld);
			}
			//Возвращаем всё обратно
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			bDisableCharacterMenu = false;
			SetLocationCapturedState("PortPax_town", false);
			Locations[FindLocation("PortPax_town")].locators_radius.quest.quest1 = 1.0;
			Locations[FindLocation("PortPax_town")].locators_radius.patrol.patrol14 = 0.5;
			LocatorReloadEnterDisable("PortPax_ExitTown", "reload2_back", false);
			LocatorReloadEnterDisable("PortPax_ExitTown", "reload1_back", false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_town")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_Fort")], false);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("VsD_Guard_"+i);
				sld.lifeday = 0;
			}
			//Диего исчезает
			sld = CharacterFromID("Diego");
			LAi_CharacterEnableDialog(sld);
			sld.location = "None";
			//Верфь закрывается
			LocatorReloadEnterDisable("PortPax_Town", "reload5_back", true);
			SetTimerCondition("VsD_VerfOtkryt", 0, 0, 7, false);
			//Труп предателя в джунглях
			PChar.quest.VsD_TrupPredatelya.win_condition.l1 = "location";
			PChar.quest.VsD_TrupPredatelya.win_condition.l1.location = "PortPax_ExitTown";
			PChar.quest.VsD_TrupPredatelya.win_condition = "VsD_TrupPredatelya";
			SetTimerCondition("VsD_TrupPredatelya_3", 0, 0, 60, false);
		break;
		
		case "VsD_Tsyganka_3":
			dialog.text = "У тебя, "+GetSexPhrase("соколик","голубушка")+", тоже таких стремлений нет. Думаешь, доски твои сами кораблик починят? Плотницкого дела мастер тебе нужен.";
			link.l1 = "Плотника у меня сейчас нет. Есть ещё какие варианты?";
			link.l1.go = "VsD_Tsyganka_4";
		break;
		
		case "VsD_Tsyganka_4":
			dialog.text = "Есть амулет хороший, местным народцем почитаем. Дерево его слушается, да и дела столярные с ним спорятся даже у тех, кто молотка-то в руках никогда не держал. Всего тысяча песо, "+GetSexPhrase("соколик","голубушка")+".";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "Ладно, давай сюда амулет. Мне сейчас любая помощь пригодится.";
				link.l1.go = "VsD_Tsyganka_Da";
			}
			link.l2 = "Нет у меня времени на твои глупости. Иди с миром, дорогая, и не мешай.";
			link.l2.go = "VsD_Tsyganka_Net";
			npchar.lifeday = 0;
		break;
		
		case "VsD_Tsyganka_Net":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Trial", "7_1");
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "VsD_Tsyganka_Da":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Trial", "7_1");
			AddCharacterExpToSkill(pchar, "Repair", 20);
			AddMoneyToCharacter(pchar, -1000);
			GiveItem2Character(PChar, "obereg_1");
			Log_info("Вы получили амулет 'Тередо'");
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнажённым клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнажённым клинком.");
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (npchar.id == "GigoloMan") NextDiag.TempNode = "GigoloMan";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}