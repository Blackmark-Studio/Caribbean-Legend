void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
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
		
		case "Sailor_1":
			dialog.text = "Чего тебе, "+GetSexPhrase("приятель","подруга")+"? Если ты ромом меня угостить хочешь - я не против. Я уж столько кругов по этому богом забытому городку намотал, что ноги скоро в узел завяжутся. Тебя как зовут-то?";
			link.l1 = "Капитан "+GetFullName(pchar)+". А не с 'Орла' ли ты часом?";
			link.l1.go = "Sailor_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Sailor_2":
			if (pchar.sex == "man")
			{
				dialog.text = "А я - "+GetFullName(npchar)+". И да, я с 'Орла'. Приглянулся наш кораблик, а, капитан?";
			}
			else
			{
				dialog.text = "Капитан? Надо же... Кхе-кхе... Ну а я Антонио Велента. И да, я с 'Орла'. Приглянулся наш кораблик, а, госпожа капитан?";
			}
			link.l1 = "Корабль как корабль. Тебе бы на борт поспешить, а не по городу шастать, капитан ваш уже молнии мечет - до того как прилив схлынет, он намерен покинуть порт. И что-то мне подсказывает, что тебя, парень, он ждать не станет.";
			link.l1.go = "Sailor_3";
		break;
		
		case "Sailor_3":
			dialog.text = "Книппель мне в грот... Знаю я, знаю... Только вот дельце у меня в этом городе осталось, незавершённое. Не хочешь пару дублонов заработать, а, кэп?";
			link.l1 = "Дублоны лишними не бывают. Только одно дело - заработать, а другое - вляпаться в неприятности. Что за дельце? Выкладывай.";
			link.l1.go = "Sailor_4";
		break;
		
		case "Sailor_4":
			dialog.text = "Я, понимаешь, пока трюм разгружал, на письмецо одно наткнулся. Не похоже, чтоб его кто специально спрятал, лежало оно как попало, среди старых бочек. Флейт наш не один абордаж пережил, так что и не разберёшь, откуда оно взялось.";
			link.l1 = "Ну нашёл ты письмо, и что с того?";
			link.l1.go = "Sailor_5";
		break;
		
		case "Sailor_5":
			dialog.text = "Адресовано оно некой Марисе Кальдера из Порто Белло. Запечатано сургучом... нутром чую - не пустяковое оно. Может, от капитана, может, от торговца какого... но точно не от простого матроса вроде меня! Только вот разыскать адресата я уже не успею - с нашим кэпом и в самом деле шутки плохи.  Не хочешь выкупить его у меня? Отдам за тысячу песо. Ты же капитан, тебе труда не составит эту сеньориту разыскать. А она, глядишь, отблагодарит золотишком, или ещё чем... смекаешь о чём я?";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "Ну что ж, может, и отыщу твою Марису.  В любом случае, я ничего не теряю. Кроме тысячи песо. Давай письмо.";
				link.l1.go = "Sailor_6";
			}
			else
			{
				notification("Недостаточно денег (1000)", "Money");
			}
			link.l2 = "Извини, приятель, но тебе придётся поискать другого человека. У меня полно дел поважнее, чем доставка писем.";
			link.l2.go = "Sailor_end";
		break;
		
		case "Sailor_end":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Sailor_end");
		break;
		
		case "Sailor_6":
			dialog.text = "Держи. Ну, бывай, "+GetSexPhrase("приятель","подруга")+", мне пора - не хочется, чтоб мои пожитки уплыли вместе с 'Орлом'.";
			link.l1 = "...";
			link.l1.go = "Sailor_accept";
			GiveItem2Character(PChar, "LFD_letter");
			AddMoneyToCharacter(pchar, -1000);
		break;
		
		case "Sailor_accept":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Sailor_accept");
			AddQuestRecord("LFD", "2");
			AddQuestUserData("LFD", "sSex", GetSexPhrase("ся","ась"));
		break;
		
		case "Dolores_1":
			dialog.text = "Кто вы? Что вам нужно?";
			link.l1 = "Меня зовут капитан "+GetFullName(pchar)+". Я ищу Марису Кальдера.";
			link.l1.go = "Dolores_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Dolores_2":
			sld = CharacterFromID("PortoBello_priest");
			dialog.text = "Не знаю я никакой Марисы. Вы ошиблись дверью. Уходите, пока я не позвала стражу - они быстро выставят вас за порог.";
			link.l1 = "Отец "+sld.name+" сказал мне, что вы - её подруга. У меня есть письмо, адресованное ей. Судя по его виду, оно сильно запоздало. Я хочу передать его лично.";
			link.l1.go = "Dolores_3";
		break;
		
		case "Dolores_3":
			dialog.text = "Ах, святой отец... Он слишком добр ко всем, но редко ошибается в людях. Вы можете оставить письмо мне. Я позабочусь о том, чтобы оно попало в её руки.";
			link.l1 = "Простите, сеньорита, но мне хотелось бы передать его лично. У неё могут возникнуть вопросы о том, откуда оно у меня и почему так долго доставлялось.";
			link.l1.go = "Dolores_4";
		break;
		
		case "Dolores_4":
			dialog.text = "И вы полагаете, что я так просто поверю в ваши благие намерения? Я повидала немало мерзавцев с лицом добродетеля. Оставьте письмо или уходите.";
			link.l1 = "Я даю вам слово капитана, что не причиню зла ни вам, ни Марисе. Более того, вы можете пригласить на встречу стражу или кого угодно, кто умеет держать оружие. У меня нет иных целей, кроме как передать письмо лично в руки Марисе.";
			link.l1.go = "Dolores_5";
		break;
		
		case "Dolores_5":
			dialog.text = "Ну хорошо. Приходите завтра после одиннадцати часов вечера. Я не могу обещать, что она согласится на встречу, но передам ей всё, что вы сказали.";
			link.l1 = "Я обязательно приду. До встречи.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Dolores_1");
		break;
		
		case "Marisa_1":
			dialog.text = "Здравствуйте, "+GetAddress_Form(NPChar)+" "+pchar.lastname+". Вы искали меня, и вот я здесь. Долорес сказала, что у вас есть для меня письмо?";
			link.l1 = "Здравствуйте, госпожа Кальдера. Всё верно, вот, возьмите. Увы, похоже, оно добиралось до вас очень долго.";
			link.l1.go = "Marisa_2";
			DelLandQuestMark(npchar);
			TakeItemFromCharacter(pchar, "LFD_letter");
			notification("Отдано: Письмо для Марисы Кальдера", "None");
		break;
		
		case "Marisa_2":
			dialog.text = "Долорес... Это же его почерк... Почерк Рамиро!";
			link.l1 = "...";
			link.l1.go = "Marisa_2_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
			sld = CharacterFromID("LFD_Dolores");
			LAi_CharacterEnableDialog(sld);
		break;
		case "Marisa_2_1":
			StartInstantDialog("LFD_Dolores", "Marisa_3", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_3":
			dialog.text = "Но как такое возможно? Два года ведь прошло!";
			link.l1 = "...";
			link.l1.go = "Marisa_3_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_3_1":
			StartInstantDialog("LFD_Marisa", "Marisa_4", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_4":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+" капитан... Как оно оказалось у вас? Где вы его нашли? Я должна знать всё! Прошу, расскажите мне всё, что вам известно.";
			link.l1 = "Это письмо досталось мне от одного матроса. Он нашёл его в тёмном уголке трюма своего корабля и хотел сам вам его доставить, но вынужден был поспешно вернуться на судно. Тогда он попросил меня разыскать вас и вот, я здесь. Больше мне ничего не известно...";
			link.l1.go = "Marisa_5";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Marisa_5":
			dialog.text = "Спасибо вам, "+GetAddress_Form(NPChar)+"! Спасибо большое! Прошу, не уходите. Я хочу ещё поговорить с вами, но прежде... мне нужно прочесть это письмо.";
			link.l1 = "Конечно, госпожа Кальдера. Я буду здесь.";
			link.l1.go = "Marisa_6";
		break;
		
		case "Marisa_6":
			DialogExit();
			SetLaunchFrameFormParam("Прошло двадцать минут, Мариса прочла письмо...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("LFD_Dolores_3", 0.0);
			LaunchFrameForm();
		break;
		
		case "Marisa_11":
			dialog.text = "Долорес... Он написал это письмо перед своим последним выходом в море. Хотел сообщить мне, что ему представился шанс купить большую партию чёрного дерева у торговца из Белиза, но денег было недостаточно. Тогда он и взял этот займ... Двести дублонов... Из-за которых мне теперь нет покоя.";
			link.l1 = "...";
			link.l1.go = "Marisa_11_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_11_1":
			StartInstantDialog("LFD_Dolores", "Marisa_12", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_12":
			dialog.text = "Это всё проясняет... Но, увы, это не облегчит твою ношу. Держись, Мариса. Тьма не вечна, и этот долг не будет преследовать тебя всегда.";
			link.l1 = "...";
			link.l1.go = "Marisa_12_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_12_1":
			StartInstantDialog("LFD_Marisa", "Marisa_13", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_13":
			dialog.text = "Нет, Долорес, не будет! Рамиро написал, что у него есть тайник... на нашем месте. Если он всё ещё не разграблен, возможно, я смогу покрыть долг и, наконец, вырваться из этого кошмара.";
			link.l1 = "...";
			link.l1.go = "Marisa_13_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_13_1":
			StartInstantDialog("LFD_Dolores", "Marisa_14", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_14":
			dialog.text = "Господь смиловался над тобой! Он услышал наши с тобой молитвы...";
			link.l1 = "...";
			link.l1.go = "Marisa_14_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_14_1":
			StartInstantDialog("LFD_Marisa", "Marisa_15", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_15":
			dialog.text = "Капитан, ещё раз благодарю вас за то, что доставили мне это письмо. Для меня оно бесценно... Но я вынуждена обратиться к вам с ещё одной просьбой. Видите ли, мой муж, Рамиро, был для меня всем, и я никогда не искала защиты у других мужчин. Теперь же, когда его не стало, мне больше некого попросить о помощи, родственников у меня не осталось\nЯ должна добраться до его тайника - он находится за городом. Но одной идти туда мне очень страшно, за мной охотятся кредиторы моего покойного мужа. Вы поступили благородно, разыскав меня, чтобы передать письмо... Прошу, помогите мне ещё раз.";
			link.l1 = "Разумеется, Мариса, я вас провожу. Когда вы хотите отправиться в путь?";
			link.l1.go = "Marisa_16";
			link.l2 = "Прошу прощения, сеньора, но моё пребывание в вашем городе и без того оказалось слишком долгим. Загородные прогулки не входят в мои планы.";
			link.l2.go = "Marisa_end_1";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Marisa_end_1":
			dialog.text = "Понимаю... Вы и так сделали для меня больше, чем можно было надеяться. Спасибо вам, капитан и до свидания.";
			link.l1 = "До свидания.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_end");
		break;
		
		case "Marisa_16":
			dialog.text = "Благодарю вас, капитан. Приходите завтра на рассвете, к семи часам. Я буду готова.";
			link.l1 = "Тогда до встречи, сеньора.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_1");
		break;
		
		case "Marisa_21":
			if (GetHour() >= 7 && GetHour() <= 19)
			{
				if (pchar.sex == "man")
				{
					dialog.text = "Кабальеро, вот и вы... Вы - настоящий человек чести! Давайте отправляться. Наш путь лежит через сельву к гроту, что неподалёку от залива Москитос.";
				}
				else
				{
					dialog.text = "Госпожа капитан, вот и вы... Я не сомневалась, что вы придёте. Знаете, а я ведь впервые встретила девушку - капитана корабля. И уже вижу, что вы не уступаете ни одному из мужчин - ни в чести, ни в благородстве!";
				}
				link.l1 = "Превосходно, сеньора. Тогда не будем терять времени. Держитесь рядом и не отходите ни на шаг.";
				link.l1.go = "Marisa_go_cove";
				if (startHeroType == 4) // если ГГ Элен
				{
					link.l1 = "Благодарю вас, Мариса. Мой отец был капитаном, и человеком чести - и с детства прививал мне те же идеалы.";
					link.l1.go = "Marisa_22";
				}
			}
			else
			{
				dialog.text = "Приходите на рассвете, к семи часам. Я буду готова.";
				link.l1 = "Тогда до встречи, сеньора.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Marisa_21";
			}
		break;
		
		case "Marisa_22":
			dialog.text = "Был? Неужели его настигла такая же судьба как и моего Рамиро?";
			link.l1 = "Сам он, наверняка, предпочёл бы уйти в мир иной с саблей в руке или в схватке со штормом. Но судьба распорядилась иначе - его доконала болезнь, о которой он никогда никому не говорил.";
			link.l1.go = "Marisa_23";
		break;
		
		case "Marisa_23":
			dialog.text = "Сожалею вашей утрате, "+pchar.name+". Господь забирает лучших... И пусть мы не всегда понимаем почему - в этом Его воля. Нам остаётся лишь молиться за упокой их бессмертных душ.";
			link.l1 = "...";
			link.l1.go = "Marisa_24";
		break;
		
		case "Marisa_24":
			dialog.text = "Давайте отправляться. Наш путь лежит через сельву к гроту,  что неподалёку от залива Москитос.";
			link.l1 = "Конечно. Держитесь рядом и не отходите ни на шаг.";
			link.l1.go = "Marisa_go_cove";
		break;
		
		case "Marisa_go_cove":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Marisa_2");
		break;
		
		case "Marisa_31":
			dialog.text = "Вот мы и на месте... Здесь мы с Рамиро когда-то укрылись от дождя - ещё юными, когда он ещё не был моим мужем. Именно тогда он сказал, что покорит моё сердце, чего бы ему это ни стоило.";
			link.l1 = "Мне жаль, что вам пришлось прийти сюда одной, без вашего мужа, сеньора. Такие места хранят много воспоминаний. Давайте осмотримся - возможно, помимо них, мы найдём и то, что Рамиро берёг для самых трудных времён.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_4");
		break;
		
		case "Marisa_32":
			dialog.text = ""+GetSexPhrase("Сеньор "+pchar.lastname+"",""+pchar.name+"")+"... Вы нашли что-то? Это то, что оставил Рамиро? Я даже не знаю, чего боюсь больше - что там пусто или что этого окажется недостаточно для покрытия долга...";
			if (PCharDublonsTotal() >= 400 && GetCharacterItem(pchar, "jewelry2") >= 10 && GetCharacterItem(pchar, "jewelry3") >= 10 && CheckCharacterItem(PChar, "mushket1"))
			{
				link.l1 = "(показывает) Вот, это всё, что было в сундуке. Надеюсь, этого хватит, чтобы изменить вашу судьбу к лучшему.";
				link.l1.go = "Marisa_33";
				DelLandQuestMark(npchar);
			}
			else
			{
				link.l1 = "Я пока ещё осматриваю сундук.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Marisa_32";
			}
		break;
		
		case "Marisa_33":
			dialog.text = "Ах, капитан! Конечно! Этого должно хватить! Но я не могу оставить без награды то, что вы для меня сделали. Возьмите себе сто дублонов. Если бы не вы, я так и не узнала бы об этом тайнике и вынуждена была бы дальше скрываться от людей, посланных кредитором Рамиро...";
			link.l1 = "Вы очень щедры, сеньора, спасибо. В нашем деле золото лишним не бывает.";
			link.l1.go = "Marisa_34";
			link.l2 = "Нет, сеньора. Эти деньги нужны вам гораздо больше, чем мне. Главное, что теперь вы сможете избавиться от бед и жить спокойно. Для меня этого вполне достаточно.";
			link.l2.go = "Marisa_35";
			RemoveDublonsFromPCharTotal(400);
			RemoveItems(pchar, "jewelry2", 10);
			RemoveItems(pchar, "jewelry3", 10);
			TakeItemFromCharacter(pchar, "mushket1");
			TakeItemFromCharacter(pchar, "obereg_7");
			TakeItemFromCharacter(pchar, "amulet_11");
			notification("Отдано: Амулет 'Чимарута'", "None");
			notification("Отдано: Амутет 'Рыбак'", "None");
			notification("Отдано: Фитильный мушкет", "None");
			notification("Отдано: Алмаз (10)", "None");
			notification("Отдано: Рубин (10)", "None");
		break;
		
		case "Marisa_34":
			dialog.text = "Ну а теперь, "+GetSexPhrase("сеньор",""+pchar.name+"")+", нам пора в дорогу. Если меня заметили в городе, за нами могли пойти. Лучше здесь не задерживаться.";
			link.l1 = "Вы правы, Мариса. Идёмте.";
			link.l1.go = "Marisa_naemnik";
			TakeNItems(pchar, "gold_dublon", 100);
		break;
		
		case "Marisa_35":
			dialog.text = "Капитан, прошу вас... мой муж хранил это оружие, чтобы защитить нашу семью, и я уверена - в ваших руках оно послужит правому делу. Рамиро был бы рад знать, что оно досталось человеку, который спас меня, когда надежды уже не оставалось.";
			link.l1 = "Хорошо, Мариса, спасибо вам. Вы - добрая и достойная женщина, и мне искренне жаль, что судьба была к вам так жестока.";
			link.l1.go = "Marisa_36";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Marisa_36":
			dialog.text = "Иногда Господь посылает нам тяжкие дни или даже годы, чтобы испытать нашу веру, но ведь Он никогда не оставляет тех, кто идёт праведным путём. Он ниспослал вас мне на помощь, и теперь, надеюсь, самая большая моя проблема останется позади\nНу а сейчас, нам пора возвращаться. Мы пробыли здесь достаточно долго, и это может быть опасным, ведь меня до сих пор ищут.";
			link.l1 = "Конечно, сеньора, идёмте.";
			link.l1.go = "Marisa_naemnik";
			GiveItem2Character(pchar, "mushket1");
			GiveItem2Character(pchar, "obereg_7");
			GiveItem2Character(pchar, "amulet_11");
		break;
		
		case "Marisa_naemnik":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Marisa_6");
		break;
		
		case "Naemnik_1":
			dialog.text = "Ха! А вот и наша пропажа! Думала, затаишься здесь, в норе, как мышь, и я тебя не найду? Я уж весь город вверх дном перевернул несколько раз, а ты, оказывается, тут"+GetSexPhrase(", да ещё и свидание с каким-то щенком устроила. Где мои денежки, плутовка? Тебе лучше отдать их прямо сейчас, иначе эта пещера станет для тебя могилой.",".")+"";
			link.l1 = "...";
			link.l1.go = "Naemnik_1_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		case "Naemnik_1_1":
			StartInstantDialog("LFD_Marisa", "Naemnik_2", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Naemnik_2":
			dialog.text = "Вы...";
			link.l1 = "...";
			link.l1.go = "Naemnik_2_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		case "Naemnik_2_1":
			StartInstantDialog("LFD_Naemnik", "Naemnik_3", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Naemnik_3":
			dialog.text = "...";
			link.l1 = "Так вот кто зарабатывает на жизнь выбиванием долгов из женщин? Судя по тому, какое ремесло ты выбрал, ум никогда не был твоей сильной стороной. Удивительно, что дорогу сюда ты сам нашёл, а не следовал за кем-то умнее...  за собственным сапогом например.";
			link.l1.go = "Naemnik_4";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Naemnik_4":
			if (pchar.sex == "man")
			{
				dialog.text = "Закрой пасть, герой. Твоё время ещё придёт, но сначала я разберусь с ней. Она должна пятьсот двадцать пять дублонов - таков её долг с процентами. Либо она отдаст их сполна, либо останется здесь навечно - кормить червей. Но раз уж ты у нас такой правильный, можешь заплатить за неё, и я исчезну.";
				if (PCharDublonsTotal() >= 525)
				{
					link.l1 = "Ты думаешь, что можешь просто прийти, нагрубить даме, не считая меня, и уйти отсюда целым, да ещё и с дублонами? Похоже, ты и вправду не очень умён. Но я не собираюсь устраивать побоище на глазах у женщины. Поэтому вот тебе моё предложение: ты извиняешься перед госпожой Кальдера, забираешь дублоны и катишься ко всем чертям. Или же мне всё-таки придётся преподать тебе урок хороших манер.";
					link.l1.go = "Naemnik_5";
					notification("Проверка пройдена (525)", "Dubloon");
				}
				else
				{
					notification("Недостаточно золота (525)", "Dubloon");
				}
			}
			else
			{
				dialog.text = "Закрой свой рот и жди своей очереди. Я займусь тобой позже, когда разберусь с этой паршивкой. Она задолжала пятьсот двадцать пять дублонов - таков её долг с процентами. Раз уж ты у нас такая правильная, можешь заплатить за неё, и я исчезну.";
				if (PCharDublonsTotal() >= 525)
				{
					link.l1 = "Что ж, я готова простить твою неотёсанность и даже грубость в мой адрес. Но если ты хочешь получить дублоны и уйти отсюда целым, тебе придётся извиниться перед госпожой Кальдера. Иначе мы с тобой проверим, кто лучше владеет оружием. И поверь, я ношу его не для красоты.";
					link.l1.go = "Naemnik_5";
				}
				else
				{
					notification("Недостаточно золота (525)", "Dubloon");
				}
			}
			link.l2 = "Видимо, ты и вправду не обременён умом, раз решил, что я стану ждать своей очереди. И уж тем более, что закрою глаза на все беды, которые ты и тебе подобные обрушили на госпожу Кальдера.";
			link.l2.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_5":
			dialog.text = "Ну что ж, будь по-твоему. Если можно получить деньги без лишнего риска, не вижу смысла лезть на рожон. Давай сюда дублоны - и пошёл.";
			link.l1 = "Сначала извинись перед дамой.";
			link.l1.go = "Naemnik_6";
		break;
		
		case "Naemnik_6":
			dialog.text = "Прощения прошу, сеньора. Бес попутал.";
			link.l1 = "...";
			link.l1.go = "Naemnik_7";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		
		case "Naemnik_7":
			dialog.text = "Довол"+GetSexPhrase("ен","ьна")+"? Давай золото, и я пошёл. У меня много дел, некогда с вами тут в любезности играть.";
			link.l1 = "Бери свои дублоны и катись отсюда.";
			link.l1.go = "Naemnik_7_1";
			CharacterTurnByChr(npchar, pchar);
			RemoveDublonsFromPCharTotal(525);
		break;
		
		case "Naemnik_7_1":
			StartInstantDialog("LFD_Marisa", "Marisa_37", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
		break;
		
		case "Marisa_37":
			dialog.text = "Капитан, право, я не понимаю... Что это значит?";
			link.l1 = "Это значит, что больше нет у вас никакого долга. Вы свободны.";
			link.l1.go = "Marisa_38";
			CharacterTurnByChr(npchar, pchar);
			
			sld = CharacterFromID("LFD_Naemnik");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 5);
			sld.lifeday = 0;
		break;
		
		case "Marisa_38":
			dialog.text = "Но... у меня нет всей суммы, чтобы вернуть вам сразу. Если вы сможете немного подождать...";
			link.l1 = "Вы не поняли, Мариса. Вы мне ничего не должны. Вы больше никому ничего не должны. А деньги, которые вы нашли, вам очень пригодятся. Возвращайтесь к прежней жизни - в церкви вас очень ждут.";
			link.l1.go = "Marisa_39";
		break;
		
		case "Marisa_39":
			dialog.text = "Я... Я просто не верю. Так ведь не бывает, "+GetSexPhrase("кабальеро","сеньорита")+"! Вы отдали огромные деньги за меня... просто так? И теперь всё кончено? Никакого долга, никакой погони? Скажите, это правда?";
			link.l1 = "Это правда, сеньора. Всё кончено. Вы больше никому ничего не должны.";
			link.l1.go = "Marisa_40";
		break;
		
		case "Marisa_40":
			dialog.text = "Ах, капитан, вы так благородны! Вы посланы Богом, я это чувствую! Но я даже представить не могу, как вас отблагодарить. Вы ведь... полностью перевернули мою жизнь, а я... что я могу для вас сделать?";
			link.l1 = "Не нужно ничего, Мариса. Просто живите. Без страха, без оков прошлого. Вернитесь к прежней жизни и найдите в ней счастье - это будет лучшей благодарностью. Идёмте, я провожу вас до города.";
			link.l1.go = "Naemnik_mir";
		break;
		
		case "Naemnik_bitva":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Naemnik_bitva");
		break;
		
		case "Naemnik_mir":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Naemnik_mir");
		break;
		
		case "Marisa_41":
			dialog.text = "Что же вы наделали, капитан, вы ведь его убили!";
			link.l1 = "Именно так, сеньора. Мне пришлось защитить вас и вашу честь...";
			link.l1.go = "Marisa_42";
		break;
		
		case "Marisa_42":
			dialog.text = "Ох, капитан, убийство человека, пусть даже такого, - страшный и тяжкий грех! Вам придётся молиться день и ночь, чтобы хоть немного смыть его с вашей бессмертной души. Господь свидетель, я могла бы просто отдать всё, что у меня есть, и он бы ушёл... Но теперь... теперь кровь на ваших руках, и лишь небеса решат, простят ли они вас!";
			link.l1 = "Возможно, такова была воля Господа. Но не будем об этом. Давайте лучше выбираться из этой пещеры.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Naemnik_bitva_3");
		break;
		
		case "Marisa_51":
			dialog.text = "Капитан, позвольте ещё раз выразить вам свою благодарность! Я буду молиться за ваше здоровье и благополучие, "+pchar.name+". Прошу вас, приходите к нам в церковь - пусть Господь дарует вам прощение всех грехов и благословение.";
			link.l1 = "Возможно, как-нибудь загляну. И имейте в виду, Мариса, если я не увижу там ваше счастливое лицо, я очень расстроюсь.";
			link.l1.go = "Marisa_52";
		break;
		
		case "Marisa_52":
			dialog.text = "Ах, "+GetAddress_Form(NPChar)+"... Вы так добры ко мне. Я буду искренне рада снова видеть вас в нашем городе. Ну а сейчас, простите, мне не терпится навести порядок в жизни и поделиться хорошими вестями с Долорес.";
			link.l1 = "Конечно, Мариса. До свидания. Берегите себя.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_In_Church");
		break;
		
		case "Marisa_54":
			dialog.text = "Капитан, позвольте ещё раз выразить вам свою бесконечную благодарность! Вы совершили для меня невозможное! За вашу доброту и благородство, я хочу рассказать вам, как мне удалось избегать встреч с наёмниками эти два года. Возможно, это когда-нибудь пригодится и вам.";
			link.l1 = "Благодарю, сеньора. В таких делах знание не менее ценно, чем золото. Слушаю вас внимательно.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Finish_In_Town_NaemnikAlive_2");
		break;
		
		case "Marisa_55":
			dialog.text = "Вот так я и прожила эти два года. В мире, где сила решает многое, умение оставаться в тени открывает возможности, которые недоступны другим.";
			link.l1 = "Спасибо за рассказ, Мариса. Вы многое пережили, и ваш опыт действительно бесценен.";
			link.l1.go = "Marisa_56";
			AddCharacterExpToSkill(pchar, "Sneak", 500);
		break;
		
		case "Marisa_56":
			dialog.text = "Я буду искренне рада снова видеть вас в нашем городе. Прошу вас, приходите к нам в церковь - пусть Господь дарует вам прощение всех грехов и благословение.";
			link.l1 = "Возможно, как-нибудь загляну. И имейте в виду, Мариса, если я не увижу там ваше счастливое лицо, я очень расстроюсь.";
			link.l1.go = "Marisa_57";
		break;
		
		case "Marisa_57":
			dialog.text = "Ах, капитан... Вы так добры ко мне. Ну а сейчас, простите, мне не терпится навести порядок в жизни и поделиться хорошими вестями с Долорес.";
			link.l1 = "Конечно, Мариса. До свидания. Берегите себя.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_In_Church");
			
			//слухи
			AddSimpleRumourCity(""+GetSexPhrase("Вы слышали? Капитан "+GetFullName(pchar)+" из собственного кармана выплатил долг вдовы Кальдера! Немногие готовы расстаться с таким состоянием ради чужого человека. Не перевелись ещё в Испании настоящие кабальеро!","Сердце радуется, когда видишь: в Испании живут не только достойные кабальеро, но и женщины, чья доблесть и честь не уступают мужской.")+"", "PortoBello", 7, 1, "");
			AddSimpleRumourCity("Говорят, какой-то капитан отдал собственные деньги, чтобы избавить вдову Кальдера от долгов её покойного мужа! Не каждый бы поступил так благородно. Настоящий человек чести, не правда ли?", "PortoBello", 7, 1, "");
		break;
		
		case "Marisa_61":
			if (CheckAttribute(pchar, "questTemp.LFD_NaemnikDead"))
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "Капитан, как же приятно снова вас видеть! Я надеялась, что вы зайдёте. Может, сегодня у вас найдётся время задержаться и помолиться?";
						link.l1 = "Рад"+GetSexPhrase("","а")+" встрече, Мариса. Но, боюсь, сейчас не могу позволить себе долгих остановок. Я помню о долге перед Господом, но молитву придётся отложить.";
						link.l1.go = "Marisa_62";
					break;

					case 1:
						dialog.text = "Капитан, снова вы! Это всегда радует. Кажется, Господь не даёт вам забыть дорогу в храм... Может, вы всё же найдёте минуту на молитву?";
						link.l1 = "Мариса, приятно видеть вас. Но я не могу остаться - мои дела не терпят отлагательств. Верю, что Господь знает мои помыслы даже без молитвы.";
						link.l1.go = "Marisa_63";
					break;
				}
			}
			else
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "Капитан, какое счастье снова вас видеть! Я каждый день благодарю Господа за вашу доброту. Мир стал светлее, когда вы помогли мне.";
						link.l1 = "Рад"+GetSexPhrase("","а")+" видеть вас в добром здравии, Мариса. Надеюсь, жизнь больше не приносит вам неприятных сюрпризов. Вы выглядите гораздо счастливее.";
						link.l1.go = "Marisa_64";
					break;

					case 1:
						dialog.text = "Капитан, как же я рада вас видеть! Каждый раз, когда вы заходите в наш храм, мне становится спокойнее. Вы приносите с собой свет добрых дел.";
						link.l1 = "И я рад"+GetSexPhrase("","а")+" вас видеть, Мариса. Вы уже привыкли к спокойной жизни или иногда всё же оглядываетесь назад?";
						link.l1.go = "Marisa_65";
					break;
				}
			}
			SetTimerFunction("LFD_Marisa_HelloAgain", 0, 0, 1);
		break;
		
		case "Marisa_62":	
			dialog.text = ""+pchar.name+", если бы каждый откладывал молитву, мир давно погрузился бы во тьму. Оставьте суету на время - покаяние даёт силу идти дальше.";
			link.l1 = "Я понимаю, Мариса, но сейчас правда не могу. Верю, что Господь услышит меня и без слов.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_62_1";
		break;
		
		case "Marisa_62_1":	
			dialog.text = ""+pchar.name+", вы передумали? Грехи не стираются сами собой, и чем дольше вы ждёте, тем тяжелее они становятся.";
			link.l1 = "Увы, я должен бежать. Но, другой раз, я обязательно помолюсь.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_62_1";
		break;
		
		case "Marisa_63":	
			dialog.text = "Но ведь вера - это не только знать, но и действовать! Нельзя вечно откладывать путь к искуплению. Разве вы не хотите почувствовать лёгкость, сбросив груз греха?";
			link.l1 = "Быть может, но не сейчас. Пусть Господь услышит меня, даже если молитва подождёт.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_63_1";
		break;
		
		case "Marisa_63_1":	
			dialog.text = "Капитан, вам не кажется, что откладывать покаяние - тоже своего рода грех? Однажды может стать слишком поздно.";
			link.l1 = "Возможно, но, боюсь, сегодня у меня нет времени. Вера со мной, Господь видит моё покаяние даже без молитвы.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_63_1";
		break;
		
		case "Marisa_64":	
			dialog.text = "Да, благодаря вам я могу снова спокойно дышать. Пусть Господь хранит вас и ваш путь. Может, вы помолитесь вместе со мной?";
			link.l1 = "Думаю, ваши молитвы и без того достаточно сильны. Главное, что теперь вас окружает лишь добро.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_64_1";
		break;
		
		case "Marisa_64_1":	
			dialog.text = ""+pchar.name+", вы всё же передумали? Помолимся нашему Создателю?";
			link.l1 = "К сожалению, Мариса, мне уже пора идти, дела.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_64_1";
		break;
		
		case "Marisa_65":	
			dialog.text = "Я стараюсь смотреть только вперёд. Теперь у меня есть будущее, и это всё благодаря вам. Может, вместе поблагодарим за это Господа?";
			link.l1 = "Думаю, вы справитесь лучше меня. Главное, чтобы ваши молитвы приносили вам мир.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_65_1";
		break;
		
		case "Marisa_65_1":	
			dialog.text = ""+pchar.name+", может мне удастся уговорить вас хоть на одну молитву?";
			link.l1 = "Прошу простить, Мариса, но увы, у меня сейчас нет времени. Помолитесь и за меня.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_65_1";
		break;
		
		case "Marisa_Ne_Ta_Peshera":	
			dialog.text = "Капитан, это не то место. Пещера, что нам нужна, у залива Москитос.";
			link.l1 = "...";
			link.l1.go = "Marisa_Ne_Ta_Peshera_1";
		break;
		
		case "Marisa_Ne_Ta_Peshera_1":	
			DialogExit();
			NextDiag.TempNode = "Marisa_31";
			DeleteQuestCondition("LFD_Ne_Ta_Peshera");
			
			sld = CharacterFromID("LFD_Marisa");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
	}
}