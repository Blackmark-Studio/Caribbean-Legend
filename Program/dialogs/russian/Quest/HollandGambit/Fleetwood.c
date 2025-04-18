// Ричард Флитвуд - английский капитан
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "Start_main")
				{
					dialog.text = "Здравствуйте, капитан. Не обращайте внимания на мой внешний вид - я в порядке, правда, почти ничего не вижу. Позвольте представиться - капитан Ричард Флитвуд.";
					link.l1 = "Добрый день. А я - капитан " + GetFullName(pchar) + ".";
					link.l1.go = "First_Task";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "GotoPortoffice")
				{
					if (sti(Pchar.Ship.Type) != SHIP_NOTUSED)
					{
						dialog.text = "Я попросил вас сдать свой корабль на хранение. Чем вы слушаете?";
						link.l1 = "Да-да, я понял, уже иду.";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Итак, вот вы снова здесь. Принимайте командование 'Валькирией' - моя команда уже предупреждена обо всём - и отправляйтесь в Бриджтаун. Обойдите всех значимых в этом городе лиц и распустите слухи, о которых мы с вами говорили. Потом будьте готовы к атаке этого негодяя. Не меняйте судно и не создавайте эскадру - иначе он заподозрит ловушку и попросту не появится\nЕго корабль вы должны обязательно взять абордажем и привести в Сент-Джонс, а также найти судовой журнал пирата - только тогда мы сможем получить доказательства причастности к этому Лукаса Роденбурга. Я уверен - вы справитесь. Удачи, капитан.";
						link.l1 = "Спасибо! Буду действовать согласно нашего плана.";
						link.l1.go = "First_Task_3";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
					}
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "MirageTake")//а вот теперь начинается перебор кораблей
				{
					pchar.quest.ToAntiguaMirageOver.over = "yes"; //снять таймер
					int iMir = 0;
					int iVal = 0;
					for(i = 0; i < COMPANION_MAX; i++)
					{
						iTemp = GetCompanionIndex(PChar, i);
						if(iTemp > 0)
						{
							sld = GetCharacter(iTemp);
							pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
							if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE)
							{
							iMir = 1;
							RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 1;//чистый корпус
							SetShipSailsFromFile(sld, "ships/parus_silk.tga");
							SetSailsColor(sld, 0);//белый хлопковый парус
							DeleteAttribute(sld, "ship.sails");//починить паруса
							DeleteAttribute(sld, "ship.masts");//вернуть мачты
							}
							if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA) iVal = 1;
						}
					}//установили признак наличия кораблей в эскадре.
					if (iMir == 1 && iVal == 0)//потеряли Валькирию
					{
						dialog.text = "Вот вы и вернулись, капитан... Я уже всё знаю о вашем путешествии.";
						link.l1 = "Вот как? Тогда вам наверное известно, что...";
						link.l1.go = "Fleetwood_lostVal";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
					if (iMir == 0 && iVal == 1)//потеряли Мираж
					{
						dialog.text = "Вот вы и вернулись, капитан... Я уже всё знаю о вашем путешествии.";
						link.l1 = "Вот как? Тогда вам наверное известно, что...";
						link.l1.go = "Fleetwood_lostMir";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
					if (iMir == 0 && iVal == 0)//а это вообще плохо
					{
						dialog.text = "Вот вы и вернулись, капитан... Я уже всё знаю о вашем путешествии.";
						link.l1 = "Вот как? Тогда вам наверное известно, что...";
						link.l1.go = "Fleetwood_lostFull";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
					dialog.text = "Вот вы и вернулись, капитан... Я уже всё знаю о вашем путешествии.";
					link.l1 = "Вот как? Тогда вам наверное известно, что...";
					link.l1.go = "Fleetwood_complete";
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "toAntigua")
				{
					dialog.text = "Здравствуйте, мой друг! Рад вас видеть! Абигайль у вас на корабле?";
					link.l1 = "К сожалению, нет, Ричард. Она отказалась отправиться со мной, объяснив это тем, что её отъезд будет тяжким ударом для её отца, потерявшего все сбережения. Я взялся решить эту проблему - разыскать деньги Соломона - и отправился на поиски острова...";
					link.l1.go = "Fleetwood_LastTask";
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					break;
				}
				dialog.text = "У вас ещё какие-то вопросы, капитан?";
				link.l1 = "Нет. Я уже ухожу.";
				link.l1.go = "exit";		
				NextDiag.TempNode = "First time";
			}
			dialog.text = "У вас ещё какие-то вопросы, капитан?";
			link.l1 = "Нет. Я уже ухожу.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Fleetwood_abordage":
			PlaySound("VOICE\Russian\hambit\Richard Flitwood-03.wav");
			dialog.text = "Проклятый пират! Ты одержал победу в абордажной схватке, но я всё равно выполню свой долг. Я устроил пожар в крюйт-камере, и осталось очень немного до того момента, как моё судно взлетит на воздух, прихватив с собой и твой 'призрак'. Тебе больше не удастся топить английские корабли. Я умру с честью!";
			link.l1 = "На самом деле ты ошибаешься, Флитвуд. Пиратов на корабле уже нет - я позаботился об этом раньше тебя. А нужен мне ты, и корабль этот послужил отличной приманкой. Но довольно слов - надо ещё успеть добить тебя и отойти от твоей пылающей лоханки!";
			link.l1.go = "Fleetwood_abordage_1";
		break;
		
		case "Fleetwood_abordage_1":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.HWIC.Holl = "FleetwoodCapture";
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
		case "First_Task":
			dialog.text = "Чарли мне о вас рассказал. О вас и ваших успехах в перехвате вражеского торгового каравана. Я рад встрече с вами - такие отважные капитаны нужны Англии. Теперь я бы хотел поговорить с вами об одном очень важном деле, которое я хочу поручить именно вам.";
			link.l1 = "Слушаю вас внимательно, мистер Флитвуд.";
			link.l1.go = "First_Task_1";			
		break;
		
		case "First_Task_1":
			dialog.text = "На архипелаге бесчинствует пират. Он выдаёт себя за легендарный корабль-призрак, 'Летучий Голландец', но я уверен, что он хоть и голландец, но вовсе не летучий. Я имею все основания полагать, что это наймит вице-директора Голландской Вест-Индской компании Лукаса Роденбурга\nРоденбург развязал против Англии негласную торговую войну - этот 'корабль-призрак' уничтожает только купеческие корабли, идущие под английским флагом, и никакие более. Компании важно ослабить наше влияние на архипелаге, но без развязывания открытой войны, поэтому и применяются такие коварные методы\nЯ давно веду охоту на этот корабль-призрак, но ему всё время удавалось ускользнуть - проклятый пират весьма опытный моряк, а его судно быстроходное и увёртливое. Он не раз уже уходил прочь, едва завидев паруса моей 'Валькирии', и я не мог догнать его\nНо раз невозможно взять шакала в открытом противостоянии, нужно это сделать хитростью, и недавнее покушение на меня окажет неоценимую услугу. Вас ещё не напугали мои слова, капитан?";
			link.l1 = "Ни капли. Я готов помочь вам в розысках и уничтожении этого мерзавца. Ведь вы это собираетесь мне предложить?";
			link.l1.go = "First_Task_2";	
		break;
		
		case "First_Task_2":
			dialog.text = "Вы совершенно правы. Теперь перейдём к подробностям дела. Мои люди распустили слухи, что я при смерти, а свой корабль, 'Валькирию', продал. Дальше мы продолжим разыгрывать этот спектакль. Вы будете якобы купец, который и приобрёл у меня бриг, снял с него большую часть орудий и приспособил под торговое судно\nТаким образом, прикинувшись торговцем, вы должны прибыть на Барбадос, в Бриджтаун, и распустить о себе слухи: в трюмах у вас полно товара, а в карманах - денег, и что вы отбываете со дня на день. В общем, сыграть роль жадного и недалёкого, но богатого негоцианта\nИнформация о наших торговых кораблях проклятому пирату поступает именно из Бриджтауна, это я уже выяснил, но вот от кого... Под подозрением находятся все - начиная от местного купца и заканчивая губернатором, хотя в последнее мне очень не хочется верить. Для выполнения задания вы примете командование 'Валькирией', с моей отлично обученной командой и снаряжением\nНо прежде вы должны сдать все свои корабли на стоянку в портовое управление. Я договорился с начальником порта - стоянка для вашего флагмана будет стоить всего 10 000 песо\nКак только сдадите - возвращайтесь ко мне, я отдам необходимые распоряжения и 'Валькирия' перейдёт под ваше начало. Да, капитан, не забудьте взять свою долю за захват серебряного каравана и десять тысяч на стоянку - деньги лежат в комоде.";
			link.l1 = "Я вас понял, мистер Флитвуд. Отправляюсь в портовое управление.";
			link.l1.go = "exit";	
			pchar.questTemp.HWIC.Eng = "GotoPortoffice";
			bDisableFastReload = false;//откроем быстрый переход
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//иные варианты более невозможны
			AddLandQuestMark(characterFromId("SentJons_PortMan"), "questmarkmain");
		break;
		
		case "First_Task_3":
			DialogExit();
			pchar.questTemp.HWIC.TakeQuestShip = "true";//все ПУ недоступны для стоянки до поры, также корабль нельзя продать
			pchar.questTemp.HWIC.EngEquip = "true"; //форма солдат
			pchar.questTemp.HWIC.Eng = "GotoBridgetown";
			GetValckiriaToCharacter(pchar);
			pchar.quest.Knippel_Officer.win_condition.l1 = "location";
			pchar.quest.Knippel_Officer.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Knippel_Officer.function = "KnippelToOfficer";
			pchar.questTemp.HWIC.Eng.BridgeCounter = 0;//счетчик посещений неписей Бриджтауна по квесту
			AddQuestRecord("Holl_Gambit", "2-5");
			AddMapQuestMarkCity("Bridgetown", false);
			AddLandQuestMark(characterFromId("Bridgetown_trader"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_shipyarder"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_Mayor"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_usurer"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_PortMan"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_Hostess"), "questmarkmain");
		break;
		
		//изымаем корабль
		case "Fleetwood_lostMir":
			dialog.text = "Да, мне известно, что вы провалили дело, не сумев захватить пиратское судно. Весь мой план пошёл прахом. 'Валькирию' я у вас забираю. А теперь можете идти. Более ваши услуги мне не нужны.";
			link.l1 = "Мне очень жаль, что так получилось. Всего доброго, мистер Флитвуд.";
			link.l1.go = "Fleetwood_RemoveShip";
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_VALCIRIA;
		break;
		
		case "Fleetwood_lostVal":
			dialog.text = "Да, мне известно, что вы потеряли 'Валькирию'. Это было совершенно недопустимо... Я изымаю у вас захваченный пиратский корабль. А теперь можете идти. Более ваши услуги мне не нужны.";
			link.l1 = "Мне очень жаль, что так получилось. Всего доброго, мистер Флитвуд.";
			link.l1.go = "Fleetwood_RemoveShip";
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_MIRAGE;
		break;
		
		case "Fleetwood_lostFull":
			dialog.text = "Да, мне известно, что вы редкостный растяпа и неумеха. Вы не привели в порт пиратское судно, да ещё и 'Валькирию' потеряли. Я в вас глубоко разочарован. Убирайтесь прочь с глаз моих!";
			link.l1 = "Мне очень жаль, что так получилось. Прощайте, мистер Флитвуд.";
			link.l1.go = "exit";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("Knippel");
			AddDialogExitQuestFunction("LandEnc_OfficerFired");//Книппеля из офицеров
			sld = characterFromId("Knippel");
			ChangeCharacterAddressGroup(sld, "SentJons_houseH1", "goto", "goto1");//Книппеля домой
			pchar.questTemp.HWIC.Eng = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			pchar.questTemp.HWIC.Detector = "eng_fail";
			AddSimpleRumourCity("Говорят, что вы провалили некое секретное поручение Ричарда Флитвуда. Ну, теперь на Антигуа вам точно делать нечего...", "SentJons", 20, 3, "");
		break;
		
		case "Fleetwood_RemoveShip":
			DialogExit();
			AddDialogExitQuestFunction("Fleetwood_RemoveShip");
			pchar.questTemp.HWIC.Eng = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			pchar.questTemp.HWIC.Detector = "eng_fail";
			AddSimpleRumourCity("Говорят, что вы провалили некое секретное поручение Ричарда Флитвуда. Ну, теперь на Антигуа вам точно делать нечего...", "SentJons", 20, 3, "");
		break;
		
		case "Fleetwood_complete":
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_VALCIRIA;
			AddDialogExitQuestFunction("Fleetwood_RemoveShip");	
			if (CheckCharacterItem(pchar, "JacobJournal"))//проверяем журнал
			{
				dialog.text = "Да, мне известно, что вы великолепно выполнили задуманный нами план. Вы обезвредили дерзкого пирата и захватили его судно. Как, кстати, оно называется?";
				link.l1 = "'Мираж'.";
				link.l1.go = "Abigile";
			}
			else//нет журнала - нет продолжения квеста
			{
				dialog.text = "Да, мне известно, что вы великолепно выполнили задуманный нами план. Вы обезвредили дерзкого пирата и захватили его судно. 'Валькирию' я у вас забираю, а пиратский корабль оставьте себе в качестве приза... и в каком-то роде компенсации - во время вашего отсутствия в доках произошёл пожар, и ваше судно сгорело дотла. Я сожалею, " + pchar.name + "... Надеюсь, что 'корабль-призрак' послужит достойной заменой\nЯ уже распорядился, чтобы на нашей верфи привели в порядок корпус вашего нового судна - почистили от водорослей и прочей маскарадной дряни. Также вам поставят комплект лучших хлопковых парусов вместо этой рванины\nКроме того, примите денежное вознаграждение - 100 000 песо и вот этот навигационный прибор. Я давно решил, что подарю его достойному моряку... Вы сделали благое дело, и я горжусь знакомством с вами! Ну, а теперь мы должны проститься - мои дела на Карибах окончены, я со дня на день отбываю в Европу. Всего вам доброго, капитан!";
				link.l1 = "И вам всех благ, Ричард!";
				link.l1.go = "exit";
				LocatorReloadEnterDisable("SentJons_houseSP3", "reload2", true);//закроем Флитвуда в комнате и пусть там сидит
				pchar.questTemp.HWIC.Eng = "end";
				pchar.questTemp.HWIC.Detector = "eng_win_half";
				CloseQuestHeader("Holl_Gambit");
			}
			AddMoneyToCharacter(pchar, 100000);
			GiveItem2Character(pchar, "bussol");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			AddSimpleRumourCity("Говорят, что вы с Ричардом Флитвудом провернули военную операцию, в результате которой вы лично уничтожили неуловимого пирата, грабившего наши торговые суда. Вы настоящий герой, капитан!", "SentJons", 20, 3, "");
		break;
		
		case "Abigile":
			dialog.text = "'Мираж'? Весьма подходящее имя, хочу отметить... 'Валькирию' я у вас забираю, а 'Мираж' оставьте себе в качестве приза... и в каком-то роде компенсации - во время вашего отсутствия в доках произошёл пожар, и ваше судно сгорело дотла. Я сожалею, " + pchar.name + "... Надеюсь, что 'корабль-призрак' послужит достойной заменой\nЯ уже распорядился, чтобы на нашей верфи привели в порядок корпус вашего нового судна - почистили от водорослей и прочей маскарадной дряни. Также вам поставят комплект лучших хлопковых парусов вместо этой рванины\nКроме того, примите денежное вознаграждение - 100 000 песо, и вот этот навигационный прибор. Я давно решил, что подарю его достойному моряку. Вы сделали благое дело, и я горжусь знакомством с вами! Судовой журнал этого негодяя у вас?";
			link.l1 = "Да, конечно. Вот он, возьмите. И хотел вот что спросить: нет ли в подручных Лукаса Роденбурга... азиата?";
			link.l1.go = "Abigile_1";			
		break;
		
		case "Abigile_1":
			RemoveItems(PChar, "JacobJournal", 1);
			dialog.text = "Есть. Китаец Лонгвэй, капитан его личного судна Мейфенг. Вы прочли об этом в журнале пирата? Давайте и я гляну...(читает) Так-так. Как я и предполагал, за всем этим стоит Лукас Роденбург! Ну, да ладно, это уже не наша забота... Теперь этим двуличным мерзавцем займётся наш генерал-губернатор. Минхеру Роденбургу придётся многое объяснить!";
			link.l1 = "Хм. Интересно, а как генерал-губернатор Англии может 'заняться' голландским подданным?";
			link.l1.go = "Abigile_2";			
		break;
		
		case "Abigile_2":
			dialog.text = "Рычаги политического давления всегда есть, друг мой... Голландии придётся признать, что это именно они развязали торговую войну против Англии. Но это они вряд ли сделают и спишут всё на Роденбурга - дескать, это он сам всё придумал и набивал карманы. Лукас лишится должности, или нет, но во всяком случае, по его карьере будет нанесён тяжёлый удар\nВпрочем, это уже не наше с вами дело, капитан. Вы свою работу выполнили и сделали её хорошо. Поэтому у меня есть к вам ещё одно очень ответственное и деликатное поручение.";
			link.l1 = "Слушаю вас внимательно, Ричард. Какого врага английской короны нужно уничтожить в этот раз?";
			link.l1.go = "Abigile_3";			
		break;
		
		case "Abigile_3":
			dialog.text = "Нет, в этот раз я хочу попросить вас об услуге частного порядка и мирного характера. Позвольте я вам расскажу короткую историю, которая, кстати, касается теперь уже вашего 'Миража'.";
			link.l1 = "Я весь внимание.";
			link.l1.go = "Abigile_4";			
		break;
		
		case "Abigile_4":
			dialog.text = "Примерно за месяц до нашей с вами встречи, я был в очередном рейде по розыску 'корабля-призрака'. Я шёл от Мартиники на юг по долготе 64 гр. 41', когда вахтённый услышал вдали канонаду. Мы поспешили на звуки боя, но ветер в тот день был слишком слаб, и прошло несколько часов, прежде чем мы достигли цели. Английский флейт был атакован кораблём-призраком и потоплен орудиями, у берегов какого-то маленького островка, который даже не обозначен на картах\nЯ пустился в погоню за пиратом, но он не принял бой и скрылся. Увидев, что удача и на этот раз не сопутствует мне, я решил вернуться и произвести высадку на остров - возможно, кто-либо из команды потопленного корабля смог добраться до берега. И не напрасно\nНа острове я обнаружил двух человек, пассажиров того злополучного флейта - еврейских беженцев, отца и дочь. Девушку звали Абигайль. Как она прекрасна! Она просто чудо... Я взял их на борт и подрядился отвезти на Кюрасао, правда, отец Абигайль, Соломон, отнёсся ко мне с большим недоверием\nКак я понял, он принял меня за пирата, потопившего флейт - старик не разбирается в кораблях, а мой бриг издалека и впрямь похож на 'Мираж'. За время путешествия мы с Абигайль подружились и, не побоюсь сказать этого - полюбили друг друга. Вот такая история\nА недавно я узнал, что за моей Абигайль вовсю ухлестывает этот мерзавец Роденбург - подумайте только! Я собирался забрать её на Антигуа, как только решу вопросы с потерянным состоянием её отца - Соломон спрятал на этом острове все свои сбережения - но я так и не смог отыскать этот проклятый остров. Теперь ждать уже нельзя\nПоскольку здоровье мне ещё не позволяет выйти в море, я прошу вас - отправляйтесь в Виллемстад, найдите Абигайль и привезите её в Сент-Джонс. Представитесь ей от меня - она должна будет вам поверить и последовать за вами.";
			link.l1 = "Не вижу никаких сложностей в этом деле. Я могу отчалить хоть прямо сейчас.";
			link.l1.go = "Abigile_5";			
		break;
		
		case "Abigile_5":
			PlaySound("VOICE\Russian\hambit\Richard Flitwood-02.wav");
			dialog.text = "Замечательно! Я рад, что на вас можно положиться, " + pchar.name + ". Ваша работа будет достойно оплачена, можете в этом не сомневаться.";
			link.l1 = "Я не заставлю вас долго ждать. До скорой встречи, Ричард!";
			link.l1.go = "Abigile_6";			
		break;
		
		case "Abigile_6":
			DialogExit();
			npchar.greeting = "fleetwood_2";
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//откроем дом Аби
			LocatorReloadEnterDisable("Villemstad_houseSp2", "reload2", true);//закроем спальню Аби
			AddQuestRecord("Holl_Gambit", "2-16");
			pchar.questTemp.HWIC.Eng = "toAbigile";
			sld = characterFromId("Bridgetown_tavernkeeper");
			sld.model = "barmen_3";
			sld.name = "Гарри";
			sld.lastname = "Флетчер";//перерисуем бармена Бриджтауна
			sld.greeting = "barmen_1";
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_2";
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("Villemstad", false);
		break;
		
		case "Fleetwood_LastTask":
			dialog.text = "" + pchar.name + ", вы и впрямь отправились на поиски острова? Я потрясён вашим благородством. Вам удалось найти его?";
			link.l1 = "Да, удалось. Но, к сожалению, на этом хорошие новости заканчиваются. Я еле ушёл из этого проклятого места живым... как вспомню - до сих пор дрожь в коленях пробирает...";
			link.l1.go = "Fleetwood_LastTask_1";
		break;
		
		case "Fleetwood_LastTask_1":
			dialog.text = "Да что же там такое случилось? Рассказывайте, друг мой, не томите!";
			link.l1 = "Я прибыл на остров и отправился в грот, в котором, судя по всему, и спрятал свой сундук Соломон. Сундук действительно был в гроте. Однако не успел я открыть крышку, как какая-то сила подбросила меня в воздух, затем я услышал звук взрыва и меня швырнуло на землю в десятке футов от сундука...";
			link.l1.go = "Fleetwood_LastTask_2";
		break;
		
		case "Fleetwood_LastTask_2":
			dialog.text = "Невероятно!";
			link.l1 = "Я чудом уцелел, хотя и получил болезненные повреждения. Пока я приходил в себя, сидя на земле, передо мной начал подниматься столб густого дыма, раздались какие-то жуткие звуки, и прямо из земли вылезла кошмарная тварь... о, Господи, вы бы видели это чудовище!";
			link.l1.go = "Fleetwood_LastTask_3";
		break;
		
		case "Fleetwood_LastTask_3":
			dialog.text = "" + pchar.name + "...";
			link.l1 = "Ричард, я не сумасшедший. Так действительно было, хотя я и сам верю в это с трудом. Это был совершенно высохший раскрашенный труп индейца с кучей перьев на голове. Этот монстр что-то заурчал, потом выхватил огромную индейскую палицу и напал на меня!";
			link.l1.go = "Fleetwood_LastTask_4";
		break;
		
		case "Fleetwood_LastTask_4":
			dialog.text = "";
			link.l1 = "Пресвятая Дева... Я по сей момент не могу понять, как мне удалось одолеть эту тварь... Нанесённых ей ударов хватило бы, чтобы отправить на тот свет с десяток человек, а она все стояла на ногах... Отдышавшись после боя, я всё-таки открыл этот злосчастный сундук, но денег там не было. Зато там лежало вот это. Взгляните, презанятная вещица!";
			link.l1.go = "Fleetwood_LastTask_5";
		break;
		
		case "Fleetwood_LastTask_5":
			RemoveItems(PChar, "GastonHead", 1);
			dialog.text = "Б-р-р... Ужас... " + pchar.name + ", постойте... точно! Это голова негодяя, который пытался меня убить, ослепив перцем!";
			link.l1 = "Знаете, кто это? Это Гастон Плешивый, бармен Бриджтауна и по совместительству наводчик ван Берга, капитана корабля-призрака. Я сразу узнал мерзавца. Вот только непонятно, кто его убил, и каким образом его отрезанная голова оказалась в сундуке Соломона на острове, о котором никто не знает!";
			link.l1.go = "Fleetwood_LastTask_6";
		break;
		
		case "Fleetwood_LastTask_6":
			dialog.text = "Действительно, просто какая-то жуткая и непонятная история. Мистика...";
			link.l1 = "Это точно. Ну, а поскольку денег в сундуке не было, то и отправляться к Абигайль с пустыми руками мне не имело смысла. Вот я и вернулся сюда, чтобы поведать вам обо всём произошедшем. Может, вы, Ричард, что-нибудь поймёте в этой кутерьме...";
			link.l1.go = "Fleetwood_LastTask_7";
		break;
		
		case "Fleetwood_LastTask_7":
			dialog.text = "Я? Я понимаю во всём происходящем не больше вас... Но одно могу сказать - всё это мне очень не нравится... " + pchar.name + ", давайте поступим так. Вы сейчас отправитесь в Бриджтаун и убедитесь, что этот... Гастон действительно пропал, чтобы мы не пошли по ложному следу. Потом, не позднее, чем через двадцать дней, считая от сегодняшнего числа, я прошу вас прибыть в лагуну Бланка на Кюрасао. Там вас будет ждать Чарли Книппель. Я соберу деньги для отца Абигайль, в размере потерянного им состояния. Я передам деньги Чарли, а вы отдадите их Соломону, заберёте Абигайль и привезёте её на Антигуа. На этот раз, как вы понимаете, уже никаких препятствий не будет. Отправляйтесь, мой друг!";
			link.l1 = "Хорошо, Ричард. Я немедленно выхожу в море.";
			link.l1.go = "Fleetwood_LastTask_8";
		break;
		
		case "Fleetwood_LastTask_8":
			DialogExit();
			pchar.questTemp.HWIC.Eng = "toBarbados";
			AddQuestRecord("Holl_Gambit", "2-21");
			SetFunctionTimerCondition("HWICEng_toBarbadosOver", 0, 0, 20, false);//чтобы не тянули
			AddSimpleRumourCity("О, капитан, я слышал, как Ричард Флитвуд восхищался вами. Поверьте, его похвала дорогого стоит. Вы, наверное, весьма значительная персона...", "SentJons", 20, 3, "");
			AddMapQuestMarkCity("Bridgetown", false);
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
		break;
		
//---------------------------------------------против всех-----------------------------------------------
		
		case "InTerksShore":
			DelLandQuestMark(npchar);
			pchar.quest.Fleetwood_ShoreOver.over = "yes";//снять таймер
			dialog.text = "Я так полагаю, что вы и есть тот негодяй, похитивший мою Абигайль. Судя по тому, что Чарли так и не вернулся, думаю, к этому тоже приложили руку именно вы.";
			link.l1 = "Вы правы, мистер Флитвуд. Это я. Чарли помог мне войти в доверие к Абигайль, благодаря изъятому у него письму. Но ближе к делу... Вы привезли деньги?";
			link.l1.go = "InTerksShore_1";
		break;
		
		case "InTerksShore_1":
			dialog.text = "Безусловно. Но прежде чем вы их получите, я хочу увидеть Абигайль. Я должен знать, что она жива и с ней всё в порядке, ибо полагаться на слово мерзавца я не намерен.";
			link.l1 = "Вам не кажется, мистер, что вы немного не в том положении, чтобы диктовать мне условия?";
			link.l1.go = "InTerksShore_2";
			// belamour legendary edition -->
			link.l2 = "Нет у меня больше желания играть в эту игру. Аби останется со мной, а ты на этом пляже! Огонь!";
			link.l2.go = "InTerksShore_2a";
		break;

		case "InTerksShore_2a"://массовая драка на необитаемом острове
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)//офицеры Флитвуда
			{
				sld = characterFromId("FlOfficer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=7; i++)//засада Флитвуда
			{
				sld = GetCharacter(NPC_GenerateCharacter("EnemySailor_"+i, "sold_eng_"+i, "man", "man", 18, ENGLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 18, 30, 30, "blade_19", "pistol2", "bullet", 40);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				if (i >= 1 && i < 3) ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto2");
				else ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto9");
			}
			for (i=1; i<=7; i++)//наши - к бою!
			{
				sld = characterFromId("OwrSailor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "FleetwoodDiedInShore");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;

		case "InTerksShore_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			dialog.text = "Я всё понимаю, но я не дурак. Пока я не увижу Абигайль - ни о каких деньгах речи не пойдёт. Ну? Я жду.";
			link.l1 = "Хорошо. Пожалуй, пришло время открыть карты, капитан Флитвуд. Я организовал здесь нашу встречу вовсе не из-за денег. Деньги, конечно, мне тоже не помешают, но в первую очередь мне нужны вы.";
			link.l1.go = "InTerksShore_3";
		break;
		
		case "InTerksShore_3":
			dialog.text = "Я? Становится интересно... Кажется, я начинаю понимать, что здесь происходит. Скажите мне - Абигайль жива? Она жива, или вы убили её, мерзавец?";
			link.l1 = "Пожалуй, я оставлю вас в неведении по поводу её судьбы. Скажу одно - её здесь нет. Свою роль она сыграла - вы здесь, в моих руках. Любовь - такая штука, она творит чудеса... Иначе как бы я смог выманить лису из норы на открытое место? Ха-ха-ха!";
			link.l1.go = "InTerksShore_4";
		break;
		
		case "InTerksShore_4":
			dialog.text = "Рано радуетесь, каналья. Я позаботился об организации тёплой встречи для вас на этом острове, и ещё неизвестно, кто у кого в руках! Так что готовьтесь - вам ещё предстоит многое рассказать мне - о судьбе Абигайль, и о судьбе Чарли... и ответить за всё!";
			link.l1 = "Я уже весь дрожу! Пришло время закончить наш разговор, мистер. Приготовьтесь к путешествию в ад, ибо в раю вам делать нечего.";
			link.l1.go = "InTerksShore_5";
		break;
		
		case "InTerksShore_5"://массовая драка на необитаемом острове
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)//офицеры Флитвуда
			{
				sld = characterFromId("FlOfficer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=7; i++)//засада Флитвуда
			{
				sld = GetCharacter(NPC_GenerateCharacter("EnemySailor_"+i, "sold_eng_"+i, "man", "man", 18, ENGLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 18, 30, 30, "blade_19", "pistol2", "bullet", 40);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				if (i >= 1 && i < 3) ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto2");
				else ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto9");
			}
			for (i=1; i<=7; i++)//наши - к бою!
			{
				sld = characterFromId("OwrSailor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "FleetwoodDiedInShore");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
	}
}