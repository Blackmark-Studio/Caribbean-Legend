// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
    switch (Dialog.CurrentNode)
	{
		case "quests":
			//регата
			if (CheckAttribute(pchar, "questTemp.Regata.Go") && !CheckAttribute(npchar, "quest.regatatalk"))
			{
				dialog.text = "Что вам угодно? А-а, вы участник регаты! Так?";
				link.l1 = "Да, именно так, мистер. Мне нужно отметиться у вас согласно правил.";
				link.l1.go = "Regata_check";
				break;
			}
			//регата
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), "Совсем недавно вы пытались задать мне вопрос " + GetAddress_Form(NPChar) + "...", "В течение этого дня вы уже третий раз говорите о каком-то вопросе...",
                          "Послушайте, если вы не по делам порта, то не стоит меня вопросами донимать.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал"+ GetSexPhrase("","а") +"...", "Сейчас мне не о чем говорить."), "Хм, что-то с памятью моей стало...",
                      "Да уж, действительно в третий раз...", "Извините, но портовые дела меня сейчас не интересуют.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Грани справедливости
			if (CheckAttribute(pchar, "questTemp.GS_Portman"))
			{
				link.l1 = "До меня дошли слухи, что на вас было совершено покушение, и вы пытаетесь найти нападавшего?";
				link.l1.go = "GS_Portman_1";
			}
			if (CheckAttribute(pchar, "questTemp.GS_NaemnikMertv"))
			{
				link.l1 = "Человек, покусившийся на вашу жизнь, пал, господин "+npchar.lastname+". Вам больше ничего не угрожает.";
				link.l1.go = "GS_Portman_6";
			}
			//<-- Грани справедливости
		break;

		//регата
		case "Regata_check":
		iTest = FindColony(npchar.city); 
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			bool bRegLugger = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Сaнта-Kатepина")
			{
			dialog.text = "Хм... Вы нарушили правила регаты и я вынужден вас дисквалифицировать. Увы! В дальнейшем заплыве вы не участвуете. Я уже подготовил депешу в Порт-Рояль.";
			link.l1 = "Эх... жаль! Ладно, ничего не поделаешь - вы оказались бдительны. До свидания!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Regata");
			pchar.quest.Regata_PU.over = "yes"; // mitrokosta снимаем прерывание
			AddQuestRecord("Regata", "45");
			CloseQuestHeader("Regata");
			}
			else
			{
			pchar.questTemp.Regata.FirstTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());//истратил ГГ в часах на 1 переход
			dialog.text = "Так, отмечаем: капитан "+ GetFullName(pchar) +", корабль - "+pchar.Ship.Name+"... Затрачено времени от старта регаты в часах - "+sti(pchar.questTemp.Regata.FirstTransitionTime)+". Всё, ваш результат зафиксирован, можете продолжать путь.";
			link.l1 = "Скажите, а на каком я сейчас месте?";
			link.l1.go = "Regata_info";
			}
		}
		else
		{
			dialog.text = "Вы сами прибыли - а корабль ваш где? Что-то я его не вижу.";
			link.l1 = "Прошу прощения, сэр. Я немедленно приведу свой корабль в порт.";
			link.l1.go = "exit";
		}
		break;
		
		case "Regata_info":
			int n=1;
			string sTemp, sName, sShip;
			for (int i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				if (pchar.questTemp.Regata.AdversaryFirstTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FirstTransitionTime))
				{
					n++;
					sName = pchar.questTemp.Regata.AdversaryName.(sTemp);//имя ближайшего противника
					sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp);//его корабль
				}
			}
			if (n==1)
			{
			dialog.text = "Вы на первом месте. Поздравляю! Так держать!";
			link.l1 = "Спасибо!";
			link.l1.go = "exit";
			AddQuestRecord("Regata", "4");
			}
			else
			{
				if (n==6)
				{
				dialog.text = "Вы на последнем месте. Вам следует поторопиться!";
				link.l1 = "Уже бегу!";
				link.l1.go = "exit";
				AddQuestRecord("Regata", "9");
				}
				else
				{
					if (n==2)
					{
					dialog.text = "Вы на втором месте. Перед вами только "+sName+" на корабле "+sShip+". Думаю, вы вполне сможете его обогнать.";
					link.l1 = "Спасибо! Буду стараться!";
					link.l1.go = "exit";
					AddQuestRecord("Regata", "5");
					}
					else
					{
					dialog.text = "Вы на "+n+" месте. Ваш ближайший соперник впереди - "+sName+" на корабле "+sShip+".";
					link.l1 = "Спасибо!";
					link.l1.go = "exit";
					if (n==3) AddQuestRecord("Regata", "6");
					if (n==4) AddQuestRecord("Regata", "7");
					if (n==5) AddQuestRecord("Regata", "8");
					}
				}
			}
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			npchar.quest.regatatalk = "true";
			pchar.questTemp.Regata.Beliz = "true";//отметка Белиза
			pchar.quest.Regata_Check1.win_condition.l1 = "location";
			pchar.quest.Regata_Check1.win_condition.l1.location = "Cuba1";
			pchar.quest.Regata_Check1.function = "RegataCheck";//проверка 1
			pchar.quest.Regata_Check2.win_condition.l1 = "location";
			pchar.quest.Regata_Check2.win_condition.l1.location = "Cuba2";
			pchar.quest.Regata_Check2.function = "RegataCheck";//проверка 2
			pchar.quest.Regata_Check.win_condition.l1 = "location";
			pchar.quest.Regata_Check.win_condition.l1.location = "Hispaniola2";
			pchar.quest.Regata_Check.function = "RegataCheck";//проверка 3
			pchar.questTemp.Regata.AttackIsland = "Cuba1";
			pchar.questTemp.Regata.AttackNation = SPAIN;
			pchar.quest.Regata_Attack.win_condition.l1 = "location";
			pchar.quest.Regata_Attack.win_condition.l1.location = "Cuba1";
			pchar.quest.Regata_Attack.function = "RegataAttack_Lugger";//первая засада у Сантьяго
			pchar.quest.Regata_Hunter.win_condition.l1 = "location";
			pchar.quest.Regata_Hunter.win_condition.l1.location = "Cuba2";
			pchar.quest.Regata_Hunter.function = "RegataAttack_Hunter";//ДУ у Гаваны
			pchar.questTemp.Regata.Town = "Portpax";
			pchar.quest.Regata_PU.win_condition.l1 = "locator";
			pchar.quest.Regata_PU.win_condition.l1.location = "Portpax_town";
			pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
			pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back";
			pchar.quest.Regata_PU.win_condition.l2 = "Night";
			pchar.quest.Regata_PU.function = "RegataPU_Open";//вход в ПУ ночью
		break;
		//регата
		
		//--> Грани справедливости
		case "GS_Portman_1":
			dialog.text = "Покушение действительно было, это правда. А вот по поводу розысков... всё немного иначе. Мне не нужен беглый преступник - мне нужна его голова. Только в этом случае я смогу вновь обрести спокойствие.";
			Link.l1 = "У вас есть предположения, кто на вас напал и почему?";
			Link.l1.go = "GS_Portman_2";
			DelLandQuestMark(npchar);
		break;
		
		case "GS_Portman_2":
			dialog.text = "Я... я не знаю, кто он! Не знаю, откуда он взялся и зачем напал на меня. Но одно мне ясно - он желал моей смерти. А теперь... теперь я желаю его гибели с такой же яростью! Вы понимаете меня?\nТак что оставьте свои бесполезные вопросы. Ваше любопытство мне ни к чему, мне могут помочь только действия. Двести дублонов за его голову - вот моя цена. Беритесь за поиски или не тратьте моё время на пустую болтовню.";
			Link.l1 = "Я понимаю, что страх и злость застилают вам разум, и даже прощу этот тон. Но возьмите себя в руки. Не вижу очереди из желающих решать ваши проблемы, так что умерьте пыл. Двести дублонов меня устроят, но прежде чем я возьмусь за дело, мне нужно знать всё.";
			Link.l1.go = "GS_Portman_3";
			Link.l2 = "Ваши слова - лишь пустая болтовня, а зацепок - никаких. Искать неизвестно кого в сельве - всё равно что искать иголку в стоге сена. Я не стану зря тратить своё время на бесполезные поиски. Желаю вам удачи. Она вам точно пригодится.";
			Link.l2.go = "GS_Portman_End";
		break;
		
		case "GS_Portman_End":
			DialogExit();
			CloseQuestHeader("GS");
			DeleteAttribute(pchar, "questTemp.GS_Portman");
		break;
		
		case "GS_Portman_3":
			dialog.text = "Ахгрк... Прошу простить, "+GetAddress_Form(NPChar)+", я весь на нервах... Что конкретно вы хотите знать?";
			Link.l1 = "Вы запомнили какие-нибудь приметы, которые помогут мне его опознать? Он был один, или за ним стоит какой-то более влиятельный недруг? Чем больше вы расскажете, тем быстрее сможете спать спокойно.";
			Link.l1.go = "GS_Portman_4";
		break;
		
		case "GS_Portman_4":
			dialog.text = "Какой недруг?! Нет у меня врагов! И никогда не было! Я не занимаюсь ничем таким, чтобы заслужить смерть вот так, посреди улицы, средь бела дня\nЭтот негодяй... он просто озлобленный безумец, каких полно в этих колониальных поселениях\nЧто касается того, где его искать... я думаю, он прячется в сельве. В этих проклятых джунглях легко потеряться, но я уверен - он направится к гротам или бухтам, там проще укрыться\nЧто до внешности, его лицо закрыто платком, на голове шляпа, а оружия при нём - больше, чем у охранника его величества. Разглядеть больше не было времени.";
			Link.l1 = "Что ж, информации немного, но этого хватит, чтобы начать поиски. Отправляюсь немедленно. Не прячьте золото далеко - скоро вернусь.";
			Link.l1.go = "GS_Portman_5";
		break;
		
		case "GS_Portman_5":
			DialogExit();
			AddQuestRecord("GS", "2");
			DeleteAttribute(pchar, "questTemp.GS_Portman");
			
			PChar.quest.GS_Peshera.win_condition.l1 = "location";
			PChar.quest.GS_Peshera.win_condition.l1.location = "Beliz_Cave";
			PChar.quest.GS_Peshera.function = "GS_Peshera";
			locations[FindLocation("Beliz_Cave")].DisableEncounters = true;
			
			PChar.quest.GS_Peshera_pusto.win_condition.l1 = "location";
			PChar.quest.GS_Peshera_pusto.win_condition.l1.location = "Beliz_Cave_2";
			PChar.quest.GS_Peshera_pusto.function = "GS_Peshera_pusto";
		break;
		
		case "GS_Portman_6":
			dialog.text = "Превосходно, "+GetFullName(pchar)+"! Это просто превосходно! Вы доказали, что ваше мастерство не знает равных. Вот ваша награда - двести дублонов. Извольте получить!";
			Link.l1 = "Благодарю! Но скажите, нет ли у вас оснований полагать, что убийцу нанял кто-то из ваших бывших клиентов?";
			Link.l1.go = "GS_Portman_7";
			AddItems(pchar, "gold_dublon", 200);
			DelLandQuestMark(npchar);
		break;
		
		case "GS_Portman_7":
			dialog.text = "Бывших клиентов?.. Что за вздор!.. Я - честный человек, и мои дела всегда были чисты! Но раз уж вы мне помогли, я расскажу. Не так давно ко мне приходили пираты\nОни предлагали мне продавать наводки на торговые корабли за деньги. Я отказал, и они обрушили на меня угрозы и проклятия, а потом ушли. Думаю, этот убийца - их работа. Они не терпят отказов.";
			Link.l1 = "В таком случае, берегите себя. Кто знает, сколько ещё наёмных убийц пошлют эти, как вы выразились, 'пираты'. За сим вынужден"+GetSexPhrase("","а")+" откланяться - дела ждут.";
			Link.l1.go = "GS_Portman_8";
		break;
		
		case "GS_Portman_8":
			dialog.text = "Постойте, капитан. Я хочу ещё раз поблагодарить вас. Помимо денег, вы заслужили и моё расположение. Пока я здесь начальник порта, вы можете оставлять любой свой корабль здесь на любое время со скидкой в пятьдесят процентов. Как вам такое предложение?";
			Link.l1 = "Весьма щедро с вашей стороны! Ещё раз спасибо!";
			Link.l1.go = "GS_Portman_9";
		break;
		
		case "GS_Portman_9":
			dialog.text = "А я ещё раз благодарю вас за проделанную работу. Уверен, если ненужные мысли не будут отвлекать вас от главного, ваши дела и впредь будут столь же успешными, как сегодня. До свидания, капитан.";
			Link.l1 = "До свидания.";
			Link.l1.go = "GS_Portman_10";
		break;
		
		case "GS_Portman_10":
			DialogExit();
			AddQuestRecord("GS", "4");
			CloseQuestHeader("GS");
			AddQuestRecordInfo("Useful_Acquaintances", "3");
			DeleteAttribute(pchar, "questTemp.GS_NaemnikMertv");
			pchar.questTemp.GS_BelizSkidka = true;
		break;
		//<-- Грани справедливости
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}


