// диалог индейцев в поселениях
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Не о чем говорить!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// ==> индейцы в поселении
		case "IndianMan":
			NextDiag.TempNode = "IndianMan";
			dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("Бледнолицый","Белая скво") +" хочет говорить?", 
				"Снова ты, "+ GetSexPhrase("бледнолицый","белая скво") +".", 
				""+ GetSexPhrase("Бледнолицый любит говорить. Он похож на скво.","Белая скво любит говорить.") +"",
                "Духи привели ко мне бледнолиц"+ GetSexPhrase("его брата","ую сестру") +".", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Да.", 
				"Да, снова я.",
                "Очень поэтично.", 
				"Я тоже рад"+ GetSexPhrase("","а") +" тебя видеть.", npchar, Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
			/*if (CheckAttribute(pchar, "questTemp.Memento_Dominica"))
			{
				link.l7 = "Диалог 25";
				link.l7.go = "Memento_Dominika_Man_1";
			}*/
		break;
		
		case "IndPearlMan_1":
			dialog.text = "Говори, зачем приш"+ GetSexPhrase("ёл","ла") +".";
			link.l1 = "Да ничего особенного, послушать тебя хотел"+ GetSexPhrase("","а") +"...";
			link.l1.go = "exit";
		break;
		
		case "IndianWoman":
			NextDiag.TempNode = "IndianWoman";
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Белый человек","Белая скво")+" хочет говорить?", 
				"Снова ты, яланауи?", 
				"Бледнолиц"+GetSexPhrase("ый","ая")+" любит говорить.",
                "Духи привели ко мне "+GetSexPhrase("бледнолицего брата","белую скво")+"...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Да.", 
				"Да, снова я.",
                "Очень поэтично.", 
				"Я тоже рад"+GetSexPhrase("","а")+" тебя видеть.", npchar, Dialog.CurrentNode);
			link.l1.go = "IndianWoman_1";
			/*if (CheckAttribute(pchar, "questTemp.Memento_Dominica"))
			{
				link.l7 = "Диалог 26";
				link.l7.go = "Memento_Dominika_Woman_1";
			}*/
		break;
		
		case "IndianWoman_1":
			dialog.text = LinkRandPhrase(""+npchar.name+" слушать тебя, "+GetSexPhrase("сын","дочь")+" моря.","Что ты хотеть от "+npchar.name+", бледнолиц"+GetSexPhrase("ый","ая")+"?","Мои уши открыты для твоих слов, "+GetSexPhrase("чужеземец","чужеземка")+".");
			if (CheckIndianGift() && !CheckAttribute(npchar, "quest.gift"))
			{
				link.l1 = LinkRandPhrase("У меня есть кое-что для тебя. Хочешь посмотреть?","Хочешь, покажу тебе кое-что интересное? Тебе понравится...","У меня есть кое-что, что порадует тебя, дитя джунглей... Хочешь глянуть?");
				link.l1.go = "gift";
			}
			link.l9 = "Да ничего особенного, просто послушать тебя хотел"+GetSexPhrase("","а")+"...";
			link.l9.go = "exit";
		break;
		
		case "gift":
			iTemp = 2;
			dialog.text = RandPhraseSimple(""+npchar.name+" хотеть посмотреть. Показывать.", ""+npchar.name+" интересно. Показать мне.");
			if (CheckCharacterItem(pchar, "mineral6"))
			{
				link.l1 = "Подарить зеркальце.";
				link.l1.go = "gift_1";
			}
			for (i=50; i>=47; i--)
			{
				if (CheckCharacterItem(pchar, "jewelry"+i))
				{
					sTemp = "l"+iTemp;
					link.(sTemp) = "Подарить "+XI_ConvertString("jewelry"+i)+".";
					link.(sTemp).go = "gift_"+i;
					iTemp++;				
				}
			}
		break;
		
		case "gift_1":
			RemoveItems(pchar, "mineral6", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Ах! Теперь "+npchar.name+" суметь смотреть на себя не только в речной вода! Спасибо, "+GetSexPhrase("добрый чужеземец","добрая чужеземка")+"!";
			link.l1 = "Да пожалуйста, рассматривай своё личико вдоволь...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_47":
			RemoveItems(pchar, "jewelry47", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Ах! Какой красота! Этот браслет для "+npchar.name+"? Спасибо, "+GetSexPhrase("добрый чужеземец","добрая чужеземка")+"!";
			link.l1 = "Надень на свою смуглую ручку, красотка, тебе это пойдёт...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_48":
			RemoveItems(pchar, "jewelry48", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Ах! Какой красивый узорчатый колечко! Это для "+npchar.name+", да? Спасибо, "+GetSexPhrase("добрый чужеземец","добрая чужеземка")+"!";
			link.l1 = "Надень его на свой пальчик, пусть подружки обзавидуются...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_49":
			RemoveItems(pchar, "jewelry49", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Ах! Этот изумительный зелёный бусы - для "+npchar.name+"? Какой красота! Спасибо, "+GetSexPhrase("добрый чужеземец","добрая чужеземка")+"!";
			link.l1 = "Укрась ими свою грудь, дочь сельвы, пусть все восхищаются...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_50":
			RemoveItems(pchar, "jewelry50", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Ах! Какой замечательный зелёный кольцо! Это подарок для "+npchar.name+"? Спасибо, "+GetSexPhrase("добрый чужеземец","добрая чужеземка")+"!";
			link.l1 = "На твоей ручке оно будет смотреться просто прелестно, малышка...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_exit":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) // Addon 2016-1 Jason Пиратская линейка
			{
				dialog.text = "Ты хотеть что-то спросить у "+npchar.name+", "+GetSexPhrase("сын","дочь")+" моря?";
				link.l1 = "Да, красавица. Я и мои отважные воины собираемся в сельву, к поселению испанцев среди гор и ищем проводника. Я щедро одарю того, кто пойдёт со мной: как самого храброго воина, так и его жену. У меня много богатств: красивые пистолеты, магические увеличивающие трубы, зеркальца, ожерелья, браслеты, кольца. Может, твой муж покажет нам дорогу?";
				link.l1.go = "hayamee";
			}
			else
			{
				DialogExit();
			}
			ChangeIndianRelation(1.00);
			npchar.quest.gift = true;
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		// Кумвана, вождь деревни араваков
		case "cumvana":
			dialog.text = "Приветствовать тебя, "+GetSexPhrase("сын","дочь")+" моря. Я - Кумвана, вождь рода Черепаха племени локоно. Какой дело привело тебя в наша деревня?";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0 || CheckCharacterItem(pchar, "compass1") || GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l1 = "Я принес тебе подарок, вождь. Взгляни, тебе понравится.";
				link.l1.go = "cumvana_2";
			}
			else 
			{
				link.l1 = "Вождь, я пришёл просить тебя о помощи. Мне нужно пройти в поселение испанцев под названием Мерида - оно находится в вашей сельве среди гор, но я не знаю дороги...";
				link.l1.go = "cumvana_no";
			}
			DelLandQuestMark(npchar);
		break;
		
		case "cumvana_no":
			dialog.text = "И это очень хорошо для тебя, "+GetSexPhrase("сын","дочь")+" моря, что ты не знать дороги туда. Путь лежать через лес, земля индейцев свирепый племя капонг. Это настоящий ягуары, о-ей! Я никогда не ходить к тот испанский поселение. Мой народ - мирный народ, и мы не лезть на земля племени капонг. Кумвана не может дать совет тебе.";
			link.l1 = "Но испанцы же как-то прошли туда! Да и я не боюсь этих капонгов...";
			link.l1.go = "cumvana_no_1";
		break;
		
		case "cumvana_no_1":
			dialog.text = "А надо их бояться. Это жестокий коварный народ, они убивать моих людей в лесу. Кумвана все сказал.";
			link.l1 = "Вот незадача...";
			link.l1.go = "cumvana_no_2";
		break;
		
		case "cumvana_no_2":
			DialogExit();
			AddQuestRecord("Roger_5", "5");
			npchar.dialog.currentnode = "cumvana_1";
		break;
		
		case "cumvana_1":
			dialog.text = "О-ей! Это снова ты, "+GetSexPhrase("сын","дочь")+" моря. Что ты хотеть сказать Кумвана?";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0 || CheckCharacterItem(pchar, "compass1") || GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l1 = "Я принес тебе подарок, вождь. Взгляни, тебе понравится.";
				link.l1.go = "cumvana_2";
			}
			else 
			{
				link.l1 = "Надежда найти Мериду не оставляет меня...";
				link.l1.go = "cumvana_1_1";
			}
		break;
		
		case "cumvana_1_1":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_1";
		break;
		
		case "cumvana_2":
			dialog.text = "Локоно всегда рады добрым друзьям.";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0)
			{
				link.l1 = "Подарить дуэльный пистоль."; // 5
				link.l1.go = "cumvana_2_1";
			}
			if (CheckCharacterItem(pchar, "compass1")) // 3
			{
				link.l2 = "Подарить компас.";
				link.l2.go = "cumvana_2_2";
			}
			if (GetCharacterFreeItem(pchar, "spyglass1") > 0)
			{
				link.l3 = "Подарить дешевую подзорную трубу.";
				link.l3.go = "cumvana_2_3";
			}
			if (GetCharacterFreeItem(pchar, "spyglass2") > 0)
			{
				link.l4 = "Подарить обычную подзорную трубу."; // 2
				link.l4.go = "cumvana_2_4";
			}
			if (GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l5 = "Подарить хорошую подзорную трубу."; // 4
				link.l5.go = "cumvana_2_5";
			}
		break;
		
		case "cumvana_2_1":
			Log_Info("Вы отдали дуэльный пистоль");
			//Log_Info("Вы получили амулеты");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "pistol5", 1);
			GiveItem2Character(pchar, "obereg_9");
			GiveItem2Character(pchar, "indian_7");
			GiveItem2Character(pchar, "obereg_3");
			dialog.text = "О-ей! Какой красивый оружие бледнолицых! Кумвана принять твой подарок. И ты, "+GetSexPhrase("сын","дочь")+" моря, прими подарок от Кумвана и племя локоно.";
			link.l1 = "Спасибо, вождь!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_2":
			Log_Info("Вы отдали компас");
			//Log_Info("Вы получили амулеты");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "compass1", 1);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "indian_6");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "О-ей! Зачарованный амулет бледнолицых! Кумвана принять твой подарок. И ты, "+GetSexPhrase("сын","дочь")+" моря, прими подарок от Кумвана и племя локоно.";
			link.l1 = "Спасибо, вождь!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_3":
			Log_Info("Вы отдали дешевую подзорную трубу");
			//Log_Info("Вы получили амулеты");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass1", 1);
			GiveItem2Character(pchar, "obereg_2");
			GiveItem2Character(pchar, "indian_5");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "О-ей! Колдовской труба бледнолицых! Кумвана принять твой подарок. И ты, "+GetSexPhrase("сын","дочь")+" моря, прими подарок от Кумвана и племя локоно.";
			link.l1 = "Спасибо, вождь!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_4":
			Log_Info("Вы отдали обычную подзорную трубу");
			//Log_Info("Вы получили амулеты");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass2", 1);
			GiveItem2Character(pchar, "obereg_6");
			GiveItem2Character(pchar, "indian_6");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "О-ей! Колдовской труба бледнолицых! Кумвана принять твой подарок. И ты, "+GetSexPhrase("сын","дочь")+" моря, прими подарок от Кумвана и племя локоно.";
			link.l1 = "Спасибо, вождь!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_5":
			Log_Info("Вы отдали хорошую подзорную трубу");
			//Log_Info("Вы получили амулеты");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass3", 1);
			GiveItem2Character(pchar, "obereg_9");
			GiveItem2Character(pchar, "indian_7");
			GiveItem2Character(pchar, "obereg_5");
			dialog.text = "О-ей! Колдовской труба бледнолицых! Кумвана принять твой подарок. И ты, "+GetSexPhrase("сын","дочь")+" моря, прими подарок от Кумвана и племя локоно.";
			link.l1 = "Спасибо, вождь!..";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_3":
			dialog.text = "Какой дело привело тебя в нашу деревню, "+GetSexPhrase("сын","дочь")+" моря?";
			link.l1 = "Вождь, я пришёл просить тебя о помощи. Мне нужно пройти в поселение испанцев под названием Мерида - оно находится в вашей сельве среди гор, но я не знаю дороги. Мог ли бы ты найти отважного воина среди своего племени, который взялся бы провести меня туда?";
			link.l1.go = "cumvana_4";
		break;
		
		case "cumvana_4":
			dialog.text = "О-ей! Дорога туда полна опасность. Путь лежать через лес, земля индейцев свирепый племя капонг. Это настоящий ягуары! Мой народ - мирный народ, и мы избегать земля племя капонг.";
			link.l1 = "Мне очень надо попасть в Мериду. Кумвана, спроси своих людей - согласится ли кто присоединиться к моему отряду? Мои люди опытные, хорошо вооружены и мы никого не боимся. Проводник будет под надёжной защитой, а за помощь получит хорошую награду.";
			link.l1.go = "cumvana_5";
		break;
		
		case "cumvana_5":
			dialog.text = "Хорошо, "+GetSexPhrase("сын","дочь")+" моря. Я соберу совет воинов и передам им твоя просьба. Приходи завтра после восход солнца, я дать ответ.";
			link.l1 = "Спасибо, вождь!";
			link.l1.go = "cumvana_6";
		break;
		
		case "cumvana_6":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetStayType(pchar);
			npchar.dialog.currentnode = "cumvana_7";
			//AddQuestRecord("Roger_5", "6");
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			SetLaunchFrameFormParam("На следующий день...", "Mtraxx_MeridaVozhdDialog", 0, 4.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 1, 0, 0);
			RecalculateJumpTable();
		break;
		
		case "cumvana_7":
			dialog.text = "О-ей! Это снова ты, "+GetSexPhrase("сын","дочь")+" моря. Что ты хотеть сказать Кумвана?";
			link.l1 = "Пока ничего, вождь...";
			link.l1.go = "cumvana_7x";
			if(CheckAttribute(pchar,"questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "merida_hayamee")
			{
				link.l2 = "Послушай, Кумвана. Мне и моим людям очень нужно перебраться за реку и попасть к этому несчастному городку. И сейчас я объясню тебе, насколько мне это нужно.";
				link.l2.go = "cumvana_hard";
			}
		break;
		
		case "cumvana_hard":
			dialog.text = "Моя уже сказать тебе, что мои охотники...";
			link.l1 = "Нет нужды повторяться дважды, Кумвана. Но выгляни наружу - и оцени ситуацию... трезво. В твоей деревне рассредоточены мои бравые ребята, которые явились сюда за испанскими камешками. И их терпение на исходе. А что будет, когда оно иссякнет окончательно, тебе лучше не знать - ты уж мне поверь.";
			link.l1.go = "cumvana_medium_1";
			link.l2 = "Заткнись и слушай, краснокожая обезьяна. Мои люди могут быть куда страшнее, чем твои капонги. Не обманывайся тем, что сейчас мы такие добрые. Я даю тебе выбор: или ты в течение суток находишь мне проводника, или мы свяжем всех вас и пустим через сельву впереди отряда. Заведёте нас не туда - сами сгинете в болотах или отправитесь связанными на бой с капонгами. Ты меня понял?";
			link.l2.go = "cumvana_hard_1";
			link.l3 = "Кумвана, мне нужен этот проводник. Мы проделали немалый путь, и мне очень не хочется говорить своим парням, что это было зря.";
			link.l3.go = "cumvana_good_1";
			pchar.questTemp.Mtraxx_MeridaZapugivanieIndeets = true;
		break;
		
		case "cumvana_good_1":
			dialog.text = "Кумвана уже говорить, никто из локоно не хотеть идти с бледнолицый.";
			link.l1 = "И ты не сможешь ничего с этим сделать? Попроси кого-нибудь лично. Прикажи, в конце концов. Ты же вождь.";
			link.l1.go = "cumvana_good_2";
		break;
		
		case "cumvana_good_2":
			dialog.text = "Вождь не заставлять индеец. Вождь править и хотеть для его людей мир. Индейцы знать - капонг увидеть, локоно привести бледнолицый. Их голова захватить Канаима. Они приходить мстить локоно. Капонг - убивать. Захватывать локоно, делать раб.";
			link.l1 = "А кто захватил ваши головы? Какой дух или демон делает индейцев такими малодушными ничтожествами? Что ж, возможно, мне действительно придётся отказаться от похода на Мериду. Но знай, вождь. Когда у меня будут спрашивать, что я знаю о локоно, я неизменно буду отвечать - что это племя никчёмных трусов. Ведомых таким же, как они, трусливым, не дальновидным правителем, лицо которого искажает гримаса ужаса от одного только воспоминания о капонгах. Не снискать тебе ни славы среди индейцев, ни уважения среди нас, бледнолицых.";
			link.l1.go = "cumvana_good_3";
		break;
		
		case "cumvana_good_3":
			dialog.text = "Бледнолицый не знать обычай индейцев...";
			link.l1 = "Я достаточно знаю, чтобы понимать, кого индейцы называют трусом, а кого храбрым воином. Прощай, Кумвана. И помни мои слова. Ты - трусливый и не дальновидный правитель.";
			link.l1.go = "cumvana_good_4";
		break;
		
		case "cumvana_good_4":
			DialogExit();
			ChangeIndianRelation(5.00);
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			pchar.questTemp.Mtraxx = "fail";
			
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.win_condition.l1 = "location";
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.win_condition.l1.location = "Locono_village";
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.function = "Mtraxx_MeridaHayameeGoodDialog";
		break;
		
		case "cumvana_medium_1":
			dialog.text = "Зачем ты так угрожать индеец? Мы думать, ты хороший...";
			link.l1 = "Я хороший, пока ты будешь слушаться, понял? Даю тебе ровно сутки. И лучше поверь мне на слово: мои люди могут сделать с вами всё, что я прикажу. Мы сильнее. И мы на взводе. А если ты сомневаешься... Я видел твою жену. И твоих дочерей. Я понятно изъясняюсь, приятель?";
			link.l1.go = "cumvana_hard_2";
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		case "cumvana_hard_1":
			dialog.text = "Зачем ты так угрожать индеец? Мы думать, ты хороший...";
			link.l1 = "Я хороший, пока ты будешь слушаться, понял? Даю тебе ровно сутки. И лучше поверь мне на слово: мои люди могут сделать с вами всё, что я прикажу. Мы сильнее. И мы на взводе. А если ты сомневаешься... Я видел твою жену. И твоих дочерей. Я понятно изъясняюсь, приятель?";
			link.l1.go = "cumvana_hard_2";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		
		case "cumvana_hard_2":
			dialog.text = "Кумвана понять, бледнолицый. В деревня есть охотник, звать Тагофа. Может быть он смочь провести вас до поселение...";
			link.l1 = "Я вернусь через двадцать четыре часа. И надеюсь, мне не придётся превращать твою чудесную деревушку в пепелище.";
			link.l1.go = "cumvana_hard_3";
		break;
		
		case "cumvana_hard_3":
			DialogExit();
			ref Hayam = characterFromId("Hayamee");
			ChangeCharacterAddressGroup(Hayam, "none", "", "");
			Hayam.lifeday = 0;
			pchar.questTemp.Mtraxx = "merida_hayamee_hard";
			npchar.dialog.currentnode = "cumvana_7";
			SetFunctionTimerCondition("Mtraxx_MeridaHayameeHardTagofaWait", 0, 0, 1, false);
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			ChangeCharacterComplexReputation(pchar, "nobility", -80);
			ChangeOfficersLoyality("bad", 5);
			ChangeIndianRelation(-50.0);
			//log_Info("Отношение индейцев снизилось");
			AddQuestRecord("Roger_5", "8a");
			pchar.GenQuest.CannotWait = true; //запретить отдыхать
			
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.win_condition.l1 = "location";
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.win_condition.l1.location = "Locono_village";
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.function = "Mtraxx_MeridaHayameeHardLepriconDialog";
		break;
		
		case "cumvana_7x":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_7";
		break;
		
		case "cumvana_8":
			dialog.text = "Вот и ты, "+GetSexPhrase("сын","дочь")+" моря. Кумвана говорил с воины локоно.";
			link.l1 = "И каков результат? Есть доброволец?";
			link.l1.go = "cumvana_9";
		break;
		
		case "cumvana_9":
			dialog.text = "В наш племя есть несколько охотники, которые ходить туда. Но они бояться капонг - ягуары выйти на тропа войны. Идти не хотят - сказать, капонг перебить ваш отряд. Капонг не боятся белых.";
			link.l1 = "Мои воины сильнее любых капонгов! Часть моего отряда всю жизнь провела в джунглях - мы не зелёные юнцы!";
			link.l1.go = "cumvana_10";
		break;
		
		case "cumvana_10":
			dialog.text = "Мне жаль, "+GetSexPhrase("сын","дочь")+" моря. Мои охотники боятся. Капонг опасный, очень опасный воин. Никто не захотел рисковать своя жизнь.";
			link.l1 = "Хорошо, тогда может они расскажут дорогу? Подробно?";
			link.l1.go = "cumvana_11";
		break;
		
		case "cumvana_11":
			dialog.text = "Чтобы попасть туда, надо сначала плыть по река, потом высадиться в определённый место. Выйти не там - угодить в болото и погибнуть. Наша сельва полна опасность. Ты сам не найти, "+GetSexPhrase("сын","дочь")+" моря.";
			link.l1 = RandSwear()+"Что же мне делать? Как мне уговорить твоих охотников?";
			link.l1.go = "cumvana_12";
		break;
		
		case "cumvana_12":
			dialog.text = "Кумвана больше нечего сказать, "+GetSexPhrase("сын","дочь")+" моря.";
			link.l1 = "Ладно...";
			link.l1.go = "cumvana_13";
		break;
		
		case "cumvana_13":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			npchar.dialog.currentnode = "cumvana_7";
			AddQuestRecord("Roger_5", "7");
			pchar.questTemp.Mtraxx = "merida_advice";
			LAi_SetHuberType(npchar);
			AddLandQuestMark(characterFromId("Lepricon"), "questmarkmain");
		break;
		
		// Хайами
		case "hayamee":
			if (npchar.id == "Hayamee")
			{
				dialog.text = "Мой муж Тагофа лучший охотник племя. О-ей! "+npchar.name+" гордиться свой муж. "+npchar.name+" часто ходить в сельва вместе с Тагофа. Далеко ходить.";
				if (IsCharacterPerkOn(pchar, "Trustworthy") && stf(pchar.questTemp.Indian.relation) >= 40.0)
				{
					link.l1 = "А известна ли Тагофе дорога к испанскому городу, который бледнолицые называют Меридой?";
					link.l1.go = "hayamee_1";
				}
				else
				{
					link.l1 = "Так-так... А Тагофа знает, как добраться до испанского города?";
					link.l1.go = "hayamee_bad_1";
				}
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("Мой муж не ходить в сельва, "+GetSexPhrase("сын","дочь")+" моря. Он ловить и бить рыба. Хороший рыбак, о-ей!","Мой муж хороший охотник, о-ей, но он не ходить так глубоко в джунгли."), RandPhraseSimple("Ягуар ранить мой муж на охота. Теперь он сидеть деревня и делать стрелы, копья и лук, о-ей!","Шесть лун назад на мой муж в сельва напасть три воина капонг. Теперь он не ходить на охота далеко от селение, никогда! О-ей!"));
				link.l1 = LinkRandPhrase("Очень жаль...","Вот незадача...","Какая досада..."));
				link.l1.go = "exit";
			}
		break;
		
		case "hayamee_bad_1":
			dialog.text = "Тагофа вырасти в этот сельва. Он знать каждое дерево и каждый камень вокруг!";
			link.l1 = "Я дам много подарков тебе и Тагофе, если он проведёт нас туда. Украшения, оружие, что угодно. Всё, что пожелаешь. В разумных пределах, конечно, хе-хе. Как поговорить с твоим мужем?";
			link.l1.go = "hayamee_bad_2";
		break;
		
		case "hayamee_bad_2":
			dialog.text = "Тагофа не пойти с бледнолицый. Тагофа оставаться в селение. Ходить на охота. Не воевать с капонг.";
			link.l1 = "Ему и не придётся воевать с капонгами. Как только он увидит их, он может спрятаться. Драться будут только мои люди.";
			link.l1.go = "hayamee_bad_3";
		break;
		
		case "hayamee_bad_3":
			dialog.text = "Нет, яланауи. Бледнолицый никогда не держать своё слово. Бледнолицый говорить - и слово сразу улетать в пустота. Капонги убить Тагофа и потом прийти в наше селение, убивать локоно.";
			link.l1 = "Ты думаешь, эти капонги - это всё, чего вам  стоит опасаться? Ты сильно ошибаешься...";
			link.l1.go = "hayamee_bad_4";
			if (stf(pchar.questTemp.Indian.relation) < 40.0) notification("Индейцы вас не уважают "+stf(pchar.questTemp.Indian.relation)+"/40", "None");
			if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("Не открыта способность", "Trustworthy");
		break;
		
		case "hayamee_bad_4":
			dialog.text = "Яхаху вселяться в бледнолицый! Хайами больше не говорить с яланауи.";
			link.l1 = "Ну-ну...";
			link.l1.go = "hayamee_bad_5";
		break;
		
		case "hayamee_bad_5":
			DialogExit();
			pchar.questTemp.Mtraxx = "merida_hayamee";
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "hayamee_1":
			dialog.text = "Тагофа достойный сын сельва. Он знать любой путь. Тагофа знать, как идти в город бледнолицых.";
			link.l1 = "Хайами, я дам много подарков тебе и Тагофе, если он проведёт нас туда. Как поговорить с твоим мужем?";
			link.l1.go = "hayamee_1_1";
		break;
		
		case "hayamee_1_1":
			dialog.text = "Локоно не верить яланауи. Яланауи обманывать индеец, делать индеец раб. Но локоно слышать твой имя, бледнолицый. Моя доверять твоя. Приходить завтра после закат, сын моря. Я быть вместе с Тагофа в той хижина. Я спросить его, пойти он с вами или нет.";
			link.l1 = "Передай Тагофе, что я дам ему мой самый красивый пистолет. А тебе много украшений.";
			link.l1.go = "hayamee_2";
			notification("Индейцы вас уважают "+stf(pchar.questTemp.Indian.relation)+"/40", "None");
			notification("Вызывающий доверие", "Trustworthy");
		break;
		
		case "hayamee_2":
			dialog.text = "О-ей!";
			link.l1 = "...";
			link.l1.go = "hayamee_3";
		break;
		
		case "hayamee_3":
			DialogExit();
			AddQuestRecord("Roger_5", "9");
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.hour  = 22.0;
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.function = "Mtraxx_MeridaHayameeTimer";
		break;
		
		case "hayamee_4":
			pchar.quest.Mtraxx_MeridaPotionLate.over = "yes";
			dialog.text = ""+npchar.name+" рада видеть сына моря. Тагофа вернуться. Но он выпить слишком много кашири и крепко уснуть. Не будить его, Тагофа отдыхать. Я буду говорить.";
			link.l1 = "Хорошо, "+npchar.name+". Твой муж проведёт нас к Мериде?";
			link.l1.go = "hayamee_5";
		break;
		
		case "hayamee_5":
			dialog.text = "Тагофа согласиться провести твой воины через сельва к испанский деревня. Но есть несколько условия...";
			link.l1 = "Какие?";
			link.l1.go = "hayamee_6";
		break;
		
		case "hayamee_6":
			dialog.text = "Ты защищать Тагофа от воин-капонг. Тагофа не вступать в драки ни с капонг, ни с испанцы. Если ему грозить опасность, он просто скрыться в джунгли, и его никто не найти - он лучший охотник локоно.";
			link.l1 = "Понимаю. Ты беспокоишься о своём муже, это справедливо. Обещаю, со всеми вашими капонгами мы разберемся сами.";
			link.l1.go = "hayamee_7";
		break;
		
		case "hayamee_7":
			dialog.text = "О-ей! Тагофа хотеть получить от "+GetSexPhrase("сын","дочь")+" моря два пистоль: один красивый, стрелять пули, второй большой, стрелять мелкие камешки, и заряд, столько, сколько пальцы на две рука три раза, к каждый пистоль.";
			link.l1 = "Ого! Да твой муж разбирается в оружии, я смотрю... Хорошо. Что ещё?";
			link.l1.go = "hayamee_8";
		break;
		
		case "hayamee_8":
			dialog.text = "Тагофа хотеть волшебный глаз белых.";
			link.l1 = "Подзорную трубу? Ладно. Это всё?";
			link.l1.go = "hayamee_9";
		break;
		
		case "hayamee_9":
			dialog.text = "Для Тагофа всё. А "+npchar.name+" хотеть красивый вещи. Жёлтое кольцо с большой красный камень и бусы из много-много зелёный блестящий камень. "+npchar.name+" видеть такое у белой Мери в Маракайбо.";
			link.l1 = "Золотое кольцо с рубином и нефритовые бусы?";
			link.l1.go = "hayamee_10";
		break;
		
		case "hayamee_10":
			dialog.text = "Этот камень звать не нефрит. Он блестящий, и белый люди его ценить.";
			link.l1 = "Изумруд? Изумрудное ожерелье?";
			link.l1.go = "hayamee_11";
		break;
		
		case "hayamee_11":
			dialog.text = "О-ей!";
			link.l1 = "Хех, "+npchar.name+" знает толк в украшениях! Хорошо, будет тебе и кольцо рубиновое, и бусы изумрудные.";
			link.l1.go = "hayamee_12";
		break;
		
		case "hayamee_12":
			dialog.text = "Принести сразу все вещи "+npchar.name+", "+GetSexPhrase("сын","дочь")+" моря. И тогда Тагофа повести тебя и твои воины. Но не терять время - через половину луны мы с Тагофа хотеть пойти в соседний деревня на праздник. А сейчас идти, "+npchar.name+" хотеть спать.";
			link.l1 = "Я не заставлю тебя ждать долго. До встречи.";
			link.l1.go = "hayamee_13";
		break;
		
		case "hayamee_13":
			DialogExit();
			AddQuestRecord("Roger_5", "10");
			LAi_CharacterDisableDialog(npchar);
			SetFunctionTimerCondition("Mtraxx_MeridaHayameeLate", 0, 0, 15, false); // таймер
			// Тагофу в сидячее положение
			pchar.quest.mtraxx_merida_wait2.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.hour  = 9.0;
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.function = "Mtraxx_MeridaTagofaHide";
		break;
		
		case "hayamee_14":
			bOk = GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0;
			dialog.text = "Ты принести то, что просить "+npchar.name+" и Тагофа?";
			if (bOk && GetCharacterFreeItem(pchar, "pistol3") > 0 && GetCharacterFreeItem(pchar, "pistol5") > 0 && GetCharacterItem(pchar, "bullet") >= 30 && GetCharacterItem(pchar, "grapeshot") >= 30 && GetCharacterItem(pchar, "gunpowder") >= 60 && CheckCharacterItem(pchar, "jewelry41") && CheckCharacterItem(pchar, "jewelry42"))
			{
				link.l1 = "Да. Всё, как вы заказывали.";
				link.l1.go = "hayamee_15";
			}
			else
			{
				link.l1 = "Нет, я ещё работаю над этим.";
				link.l1.go = "hayamee_14x";
			}
		break;
		
		case "hayamee_14x":
			DialogExit();
			npchar.dialog.currentnode = "hayamee_14";
		break;
		
		case "hayamee_15":
			pchar.quest.Mtraxx_MeridaHayameeLate.over = "yes";
			Mtraxx_MeridaRemoveGifts();
			dialog.text = ""+npchar.name+" рада, "+GetSexPhrase("сын","дочь")+" моря. Сейчас я позвать мужа. Он пойти с тобой в поход. Но помнить, что ты обещать "+npchar.name+"!";
			link.l1 = "Да-да, я ничего не забываю.";
			link.l1.go = "hayamee_16";
		break;
		
		case "hayamee_16":
			DialogExit();
			pchar.questTemp.Mtraxx = "merida_hayamee_peace";
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 7.0);
			DoQuestFunctionDelay("Mtraxx_MeridaTagofaEnter", 20.0);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
			
		case "CitizenNotBlade":
			dialog.text = "Убирать оружие, яланауи, пока мы не заставить тебя это сделать!";
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Не переживай, уже убираю...");
			link.l1.go = "exit";
		break;  
		
		// Мементо, Доминика
		/*case "Memento_Dominika_Man_1":
			dialog.text = "Заглушка 1";
			link.l1 = "Заглушка 1";
			link.l1.go = "exit";
		break;
		
		case "Memento_Dominika_Woman_1":
			dialog.text = "Заглушка 2";
			link.l1 = "Заглушка 2";
			link.l1.go = "Memento_Dominika_Woman_2";
		break;
		
		case "Memento_Dominika_Woman_2":
			dialog.text = "Заглушка 3";
			if (stf(pchar.questTemp.Indian.relation) >= 60.0)
			{
				link.l1 = "Заглушка 4";
				link.l1.go = "Memento_Dominika_Woman_3";
				notification("Индейцы вас уважают "+stf(pchar.questTemp.Indian.relation)+"/60", "None");
			}
			else
			{
				link.l1 = "Заглушка 5";
				link.l1.go = "Memento_Dominika_Woman_4";
				notification("Индейцы вас не уважают "+stf(pchar.questTemp.Indian.relation)+"/60", "None");
			}
		break;
		
		case "Memento_Dominika_Woman_3":
			dialog.text = "В воде, в одной из бухт Доминики рандомно спавнится Череп-оберег";
			link.l1 = "Понял";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dominica_SpawnObereg");
		break;
		
		case "Memento_Dominika_Woman_4":
			dialog.text = "Заглушка 6";
			link.l1 = "Заглушка 6";
			link.l1.go = "exit";
		break;*/
		
		

	}
}
