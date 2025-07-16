// диалог прочих НПС по квесту Саги
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
		case "First time":
			dialog.text = "Вы что-то хотели?";
			link.l1 = "Да нет, пожалуй, ничего.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
//---------------------------------------------Джимми в доме в Марун-Тауне------------------------------------
		case "Jimmy":
			dialog.text = "Чего тебе надо? Не видишь - горе у меня! Проваливай, пока я не спустил тебя с лестницы! ";
			link.l1 = "Сначала купи себе дом больше, чем в один этаж, а потом уже с лестницы спускай, герой выискался...";
			link.l1.go = "Jimmy_1_1";
			link.l2 = "Кто тебя так расстроил, Джимми? Не пить мне больше рому, если в этом не замешана какая-нибудь красотка! Только они могут заставить такого морского волка, как ты, бросаться на старых друзей, толком не разглядев...";
			link.l2.go = "Jimmy_1_2";
		break;
		
		case "Jimmy_1_1":
			dialog.text = "Ненавижу чистоплюев вроде тебя! Вечно вам достаются лучшие куски. Мне не дали прикончить одного выскочку, но на тебе я отыграюсь сполна!";
			link.l1 = "...";
			link.l1.go = "Jimmy_fight";
		break;
		
		case "Jimmy_fight":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_KillJimmy");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Jimmy_1_2":
			dialog.text = "Да?! Мы знакомы? Убей, не помню...";
			link.l1 = "Да это же я, "+pchar.name+"! Славно мы посидели с тобой в Блювельде после того, как ты чуть было не вспорол брюхо этому наглецу в мундире. Как его звали, кстати? Вылетело из головы... Попадётся он мне в море, не посмотрю на пушки его корвета!";
			link.l1.go = "Jimmy_2";
		break;
		
		case "Jimmy_2":
			dialog.text = "Его звали Артур! Артур Донован, капитан корвета 'Арбутус'! Гнусный мерзавец! Так ты говоришь, что я его чуть не отправил к дьяволу?";
			link.l1 = "Так и было! Ты набросился на него как кашалот на креветку. У него не было шансов, если бы не вмешались твои ребята. Прости их, им просто не хотелось, чтобы тебя повесили за убийство морского офицера.";
			link.l1.go = "Jimmy_3";
		break;
		
		case "Jimmy_3":
			dialog.text = "Аргх! Если бы у меня был корабль! Этого мерзавца легко найти около Антигуа... Ха! Если ты отправишь его на дно - я твой должник!";
			link.l1 = "По рукам, ха-ха! А что, Румба действительно стоит твоих страданий?";
			link.l1.go = "Jimmy_4";
		break;
		
		case "Jimmy_4":
			dialog.text = "Что ты! Лучше неё я не встречал до сих пор. Но она только смеётся надо мной. За этой русалкой кто только не охотится. Тут мне по большому секрету сказали, что наш Якоб разыскивает девушку, по всем приметам похожую на мою Румбу. И этот туда же! Как я теперь могу выполнять его приказы?";
			link.l1 = "Тише, приятель! У стен могут быть уши... А с чего ты взял, что Джекман ищет именно Румбу?";
			link.l1.go = "Jimmy_5";
		break;
		
		case "Jimmy_5":
			dialog.text = "Ну как же! Он ищет какого-то Генри Висельника, Глэдис Чандлер и девушку со светлыми волосами и голубыми глазами, примерно двадцати лет от роду. Её опекуншей должна быть некая Глэдис Чандлер родом из Белиза. Всё сходится.";
			link.l1 = "Постой! У Глэдис же другая фамилия.";
			link.l1.go = "Jimmy_6";
		break;
		
		case "Jimmy_6":
			dialog.text = "Джимми хитрый! Его на мякине не проведёшь! Я под Румбу давно клинья подбиваю и втихаря выяснил, что Глэдис вышла замуж за Шона МакАртура как раз двадцать лет назад. А до этого она жила в Белизе. А её первого мужа звали Пит Чандлер\nБеднягу Пита кто-то зашиб по пьяни. Поговаривают, что сам МакАртур и приложил к этому руку, поскольку запал на толстушку Глэдис. Она стала вдовой с младенцем на руках. Так вот ребёнок этот ненамного пережил своего папашу и помер от лихоманки\nА вскоре Глэдис с Шоном появились в Блювельде с живой девчушкой на руках, которую записали как дочку МакАртура. Когда она успела родить второго? Сечёшь?";
			link.l1 = "Ты кому-нибудь уже рассказал про это?";
			link.l1.go = "Jimmy_7";
		break;
		
		case "Jimmy_7":
			dialog.text = "Пока нет. Смотри, держи язык за зубами, а не то... ты меня знаешь!";
			link.l1 = "Ага, знаю. Это поганый язык, который готов разболтать любые тайны первому встречному. Правильно Румба послала тебя куда подальше, трепло...";
			link.l1.go = "Jimmy_8_1";
			link.l2 = "О чём речь! Я буду нем, как могила! А сейчас мне пора. Прощай, Джимми.";
			link.l2.go = "Jimmy_8_2";
		break;
		
		case "Jimmy_8_1":
			dialog.text = "Что... Что ты сказал?!";
			link.l1 = "Больше ты это никому не расскажешь...";
			link.l1.go = "Jimmy_fight";
			pchar.questTemp.Saga.Jimmysecret = "true";
		break;
		
		case "Jimmy_8_2":
			DialogExit();
			pchar.questTemp.Saga = "jackman";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "4_1");
		break;
// <-- Джимми 
		
//-------------------------------------------корвет Донована, абордаж-----------------------------------------
		//Донован
		case "Donovan_abordage":
			PlaySound("VOICE\Russian\saga\Artur Donovan.wav");
			dialog.text = "Аргх, гнусный мерзавец!";
			link.l1 = "Это кто ещё из нас мерзавец, сударь! Где Румба?";
			link.l1.go = "Donovan_abordage_1";
		break;
		
		case "Donovan_abordage_1":
			dialog.text = "Какой ещё Румба? У меня нет на корабле негодяев, отзывающихся на клички. Это английское военное судно!";
			link.l1 = "Не дури, Донован. Ты прекрасно понимаешь, о ком я говорю. Где девушка? Где Элен, я тебя спрашиваю?";
			link.l1.go = "Donovan_abordage_2";
		break;
		
		case "Donovan_abordage_2":
			dialog.text = "Элен? На моём судне нет портовых шлюх, гнусное отродье!";
			link.l1 = "Нет? А вот я так не считаю, потому что одна из них стоит сейчас прямо передо мной... И, как я вижу, дальнейший разговор не имеет смысла. Сдохни, тварь!";
			link.l1.go = "Donovan_abordage_3";
		break;
		
		case "Donovan_abordage_3":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Saga_AfterDonovanBoarding");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Takehelen = "true";//признак, что абордировали судно
		break;
		
		//наш матрос
		case "Tempsailor":
			dialog.text = "Капитан, мы обыскали каюты и трюм, как вы и говорили. В трюме нашли девушку, закованную в кандалы...";
			link.l1 = "Вот мерзавец! Я так и думал... Девушку освободили?";
			link.l1.go = "Tempsailor_1";
		break;
		
		case "Tempsailor_1":
			dialog.text = "Конечно, капитан. Она уже на нашем корабле, в безопасности.";
			link.l1 = "Молодцы! Отведите её ко мне в каюту, я хочу немедленно побеседовать с ней.";
			link.l1.go = "Tempsailor_2";
		break;
		
		case "Tempsailor_2":
			dialog.text = "Есть, капитан!";
			link.l1 = "...";
			link.l1.go = "Tempsailor_3";
		break;
		
		case "Tempsailor_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
		break;
		//<-- абордаж корвета Донована
		
//----------------------------------------поиск Энрике Гонсалеса, Картахена----------------------------------
		//фальшивый Гонсалес №1, дом
		case "GonsalesA":
			dialog.text = "Что вам угодно, сeньор?";
			link.l1 = "Ну здравствуй, Висельник! Привет тебе от капитана Бучера.";
			link.l1.go = "GonsalesA_1_1";
			link.l2 = "Меня зовут Шарль де Мор. Я разыскиваю сына сeньоры Гонзалес Энрике по просьбе её старого друга. Мне кажется, что это вы...";
			link.l2.go = "GonsalesA_2_1";
		break;
		
		case "GonsalesA_1_1":
			dialog.text = "Какого чёрта! Я не знаю никакого Бучера!";
			link.l1 = "Брось кривляться, Генри. Расскажи мне, зачем тебя ищут пираты Джекмана, и я не сделаю тебе больно.";
			link.l1.go = "GonsalesA_1_2";
		break;
		
		case "GonsalesA_1_2":
			dialog.text = "Караул! Пираты! Убивают!";
			link.l1 = "Тише, придурок! На твои вопли сбежится полгорода. Ах, вот ты так?!";
			link.l1.go = "GonsalesA_1_fight";
		break;
		
		case "GonsalesA_1_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesA");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		
		case "GonsalesA_2_1":
			dialog.text = "Хм... Любезный, вы, вероятно, ошиблись. Я воспитывался в чужой семье и свою мать не помню. Я взял фамилию своего опекуна. Фамилия моей матери мне не известна. Но вряд ли она тоже была Гонзалес. Вы можете навести обо мне справки в мэрии, да и любой старожил города подтвердит мои слова. Мой названый отец был человек известный, и этот дом перешёл ко мне от него по наследству, так как своих детей у него не было, а...";
			link.l1 = "Извините. Видимо, я действительно ошибся. Всего хорошего.";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) link.l1.go = "GonsalesA_3_1";
			else link.l1.go = "GonsalesA_2_2";
		break;
		
		case "GonsalesA_2_2":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Saga", "17");
		break;
		
		// belamour участвовал в событиях Картахены -->
		case "GonsalesA_3_1":
			dialog.text = "Я так не думаю.";
			link.l1 = "Простите?";
			link.l1.go = "GonsalesA_3_2";
		break;
		
		case "GonsalesA_3_2":
			dialog.text = "Знаете, недавно на нашу колонию был совершён дерзкий налёт пиратов. Думаю, вы слышали об этом? В результате этого налёта пострадало бесчисленное множество людей. Я остался цел, но вот мой бизнес, оставшийся мне в наследство, теперь переживает не лучшие времена. А виной всему предводитель этих пиратов, поганец по имени Чарли Принц.";
			link.l1 = "Очень сожалею, но причём тут я?";
			link.l1.go = "GonsalesA_3_3";
		break;
		
		case "GonsalesA_3_3":
			dialog.text = "Ха-ха, вы только посмотрите на этого невинного агнеца! Я предлагаю вам покрыть мои издержки, виновником которых вы являетесь. Сумма в размере пятнадцати тысяч песо меня устроит. И тогда я, так уж и быть, сделаю вид, что вас не было в моём доме.";
			if (sti(pchar.money) >= 15000)
			{
				link.l1 = "Какие все злопамятные... Держи свои деньги. И помни, что если кто-то узнает о том, что я был в этом городе, я вернусь к тебе.";
				link.l1.go = "GonsalesA_3_4";
			}
			link.l2 = "Пятнадцать тысяч? Хм... Я твою жизнь так дорого не ценю. Так что, пожалуй, дешевле будет просто прирезать тебя здесь, чтобы лишнего не болтал.";
			link.l2.go = "GonsalesA_3_5";
		break;
		
		case "GonsalesA_3_4":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Saga", "171");
		break;
		
		case "GonsalesA_3_5":
			dialog.text = "Караул! Пираты! Убивают!";
			link.l1 = "Ах, вот ты так?!";
			link.l1.go = "GonsalesA_3_6";
		break;
		
		case "GonsalesA_3_6":
			DialogExit();
			iTemp = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE - 2;
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("SpSold"+i, "sold_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", iTemp, SPAIN, 0, true, "soldier"));
				SetFantomParamFromRank(sld, iTemp, true);         
				LAi_SetWarriorType(sld); 
				LAi_warrior_DialogEnable(sld, false);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			}
			sld = GetCharacter(NPC_GenerateCharacter("SpOfficer", "off_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", iTemp, SPAIN, 0, true, "quest"));
			FantomMakeCoolFighter(sld, 25, 100, 100, "blade_13", "pistol6", "bullet", 150);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesAK");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		// <-- участвовал в событиях Картахены
		
		// фальшивый Гонсалес №2, улицы
		case "GonsalesB":
			PlaySound("VOICE\Russian\citizen\Pirati v Gorode-08.wav");
			dialog.text = "Я гляжу, тебе тесак мой приглянулся. Хочешь, продам? Возьму недорого, а то трубы горят, а в кармане только вошь на аркане.";
			link.l1 = "На кой ляд он мне сдался? Меня просил передать тебе привет Лесной дьявол.";
			link.l1.go = "GonsalesB_1_1";
			if (sti(pchar.money) >= 1000)
			{
				link.l2 = "Да уж. Тесак у тебя знатный. Сколько хочешь за него?";
				link.l2.go = "GonsalesB_2_1";
			}
		break;
		
		case "GonsalesB_1_1":
			dialog.text = "Лучше бы он передал для меня сотню песо! ";
			link.l1 = "Так ты знаешь Свенсона?";
			link.l1.go = "GonsalesB_1_2";
		break;
		
		case "GonsalesB_1_2":
			dialog.text = "Да пошёл ты со своим Свенсоном к дьяволу! Хошь к лесному, хошь к морскому. Не желаешь помочь больному человеку и купить тесак, так я его тебе даром в корму запихаю!";
			link.l1 = "Да? Ну давай, посмотрим, как ты это сделаешь, синяя рожа!";
			link.l1.go = "GonsalesB_1_fight";
		break;
		
		case "GonsalesB_1_fight":
			chrDisableReloadToLocation = true;
			DialogExit();
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesB");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		
		case "GonsalesB_2_1":
			dialog.text = "Сразу видно бывалого человека! Тысяча песо - и он твой.";
			link.l1 = "Замётано!";
			link.l1.go = "GonsalesB_2_2";
		break;
		
		case "GonsalesB_2_2":
			AddMoneyToCharacter(pchar, -1000);
			GiveItem2Character(pchar, "blade_10");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			dialog.text = "Таких висельников во всей Картахене всего два - у меня и старика Альвареса на маяке. Но тот свой хангер ни за что не продаст. Хоть он и корчит из себя святошу, но я бывшего пирата за милю узнаю. Этот клинок для него навроде талисмана\nВидно есть, что вспомнить бродяге. Недаром он каждый месяц в церковь бегает - не иначе грехи спокойно спать не дают.";
			link.l1 = "А ты, я смотрю, тоже хлебнул вольной жизни. Не про тебя ли мне Свенсон все уши прожужжал? Говорит, как встретишь в Картахене Генри, передавай ему от меня привет и зови в гости.";
			link.l1.go = "GonsalesB_2_3";
		break;
		
		case "GonsalesB_2_3":
			dialog.text = "Свенсон? Не знаю такого. Меня зовут Энрике Гальярдо. Но если у твоего Свенсона найдётся для меня бутылка рома, то я согласен побыть для него Генри. Меня хоть клистиром назови, только в гузно не суй. Ну что, рванули?";
			link.l1 = "Не сегодня. Свенсон далеко, а трактир рядом. Ты теперь при деньгах, так что бывай, Энрике.";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) link.l1.go = "GonsalesB_3_1";
			else link.l1.go = "GonsalesB_2_4";
		break;
		
		case "GonsalesB_2_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "19");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega();
		break;
		
		// belamour участвовал в событиях Картахены -->
		case "GonsalesB_3_1":
			dialog.text = "При деньгах, но не совсем. Хочу больше. И ты мне заплатишь.";
			link.l1 = "Не понял... Тебе жизнь не мила? Решил меня ограбить посреди города? И это после того, как ты сам же продал мне своё оружие?";
			link.l1.go = "GonsalesB_3_2";
		break;
		
		case "GonsalesB_3_2":
			dialog.text = "Нет, ты мне сам заплатишь. А знаешь, почему?";
			link.l1 = "Даже интересно послушать.";
			link.l1.go = "GonsalesB_3_3";
		break;
		
		case "GonsalesB_3_3":
			dialog.text = "Я узнал тебя. Я сидел в казематах за пьяную драку в таверне, когда твои ребята ворвались в тюрьму и перерезали всю стражу. Я смог дотянуться до трупа охранника с ключами и вышел на улицу. Город пылал, всюду трупы, кровь и пороховой дым... Прямо как во время абордажа! И сквозь этот дым я увидел тебя, выходящего из резиденции губернатора. Поэтично, да? Йо-хо-хо, здравствуй, Чарли Принц!";
			link.l1 = "А ну не ори так! Учитывая сказанное тобой, тебе тем более не следует пытаться вытрясти из меня деньги. Ты хоть представляешь, что я с тобой могу сделать?";
			link.l1.go = "GonsalesB_3_4";
		break;
		
		case "GonsalesB_3_4":
			dialog.text = "Посреди города, который ты когда-то ограбил? Ничего ты не сделаешь. Короче... Давай так: ты мне даёшь сейчас... Скажем, десять тысяч песо. Думаю, на месяц мне хватит. И идёшь себе дальше! Хоть к своему любимому Генри, хоть к Свенсону, хоть к любому дьяволу на выбор... А нет - так стоит мне крикнуть, и тебя тут же загребут в специально подготовленную персональную камеру с полным комплектом орудий пыток.";
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "Чёрт с тобой, держи свои десять тысяч и проваливай с глаз моих! И не приведи Господь я тебя ещё хоть раз увижу.";
				link.l1.go = "GonsalesB_3_5";
			}
			link.l2 = "Всё, мне это надоело. Оружие твоё у меня, так что шансов у тебя нет, падаль.";
			link.l2.go = "GonsalesB_3_7";
			link.l3 = "Хах, а ты хорош! Знаешь, что? Любому другому я уже проделал бы дырку от паха до горла. Но такие люди, как ты, мне нужны. Давай я дам тебе десять тысяч песо, верну тебе твой 'Висельник' и ещё каждый месяц буду выплачивать по три тысячи. На выпивку хватать будет. А ты пойдёшь ко мне абордажником.";
			link.l3.go = "GonsalesB_3_9";
		break;
		
		case "GonsalesB_3_5":
			dialog.text = "Всё-всё, меня уже нет! Удачи тебе в твоих поисках, Чарли Принц!";
			link.l1 = "...";
			link.l1.go = "GonsalesB_3_6";
		break;
		
		case "GonsalesB_3_6":
			AddMoneyToCharacter(pchar, -10000);
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "191");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega();
		break;
		
		case "GonsalesB_3_7":
			dialog.text = "Стража! Стража!!! Это Чарли Принц!!!";
			link.l1 = "Ах ты мразь!";
			link.l1.go = "GonsalesB_3_8";
		break;
		
		case "GonsalesB_3_8":
			DialogExit();
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			LAi_group_AttackGroup("Spain_citizens", LAI_GROUP_PLAYER);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "192");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega(); 
		break;
		
		case "GonsalesB_3_9":
			dialog.text = "Ты что, предлагаешь мне пойти к тебе на службу?";
			link.l1 = "Предлагаю, да. Но только один раз. Ну, что скажешь? Соглашайся, не то ведь потроха выпущу. Ты же не думаешь, что можешь вот так вот запросто шантажировать Чарли Принца?";
			link.l1.go = "GonsalesB_3_10";
		break;
		
		case "GonsalesB_3_10":
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34 && makeint(pchar.reputation.nobility) < 48)
			{
				notification("Проверка чести пройдена", "None");
				notification("Проверка пройдена", SKILL_LEADERSHIP);
				dialog.text = "Дьявол! Сам Чарли Принц предлагает мне пойти к нему абордажником! Чёрт тебя подери, я согласен! Давай обратно мой клинок и десять тысяч песо впридачу. Вот уж не думал, что всё так обернётся!";
				link.l1 = "Держи. И прикуси язык: никто в этом городе не должен знать, кто я такой, понял?";
				link.l1.go = "GonsalesB_3_11";
				break;
			}
			if(makeint(pchar.reputation.nobility) > 47)
			{
				notification("Слишком низкий уровень чести! ("+XI_ConvertString(GetReputationName(48))+")", "None");
				dialog.text = "Ну нет. Может быть капитан ты и нормальный, да только, думается мне, чистоплюй тот ещё. Да, когда-то ты держал испанцев в страхе, совершил дерзкий налёт на Картахену - но всё это только при помощи Маркуса Тиракса. А самому заниматься честным разбоем у тебя кишка тонка. Так что гони деньги!";
			}
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35)
			{
				notification("Недостаточно развит навык (35)", SKILL_LEADERSHIP);
				dialog.text = "Ну нет. Ты, конечно, злостный пират, но капитан, думается мне, аховый. Это ты только с помощью Маркуса Тиракса смог ограбить колонию - сам бы и дряхлую шхуну на абордаж не взял. Так что гони деньги!";
			}
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "Чёрт с тобой, держи свои десять тысяч и проваливай с глаз моих! И не приведи Господь я тебя ещё хоть раз увижу.";
				link.l1.go = "GonsalesB_3_5";
			}
			link.l2 = "Всё, мне это надоело. Оружие твоё у меня, так что шансов у тебя нет, падаль.";
			link.l2.go = "GonsalesB_3_7";
		break;
		
		case "GonsalesB_3_11":
			dialog.text = "Понял, не дурак.";
			link.l1 = "Вот и славно.";
			link.l1.go = "GonsalesB_3_12";
		break;
		
		case "GonsalesB_3_12":
			DialogExit();
			AddMoneyToCharacter(pchar, -10000);
			LAi_RemoveLoginTime(npchar);
			npchar.quest.OfficerPrice = 3000;
			npchar.reputation.nobility = 30;
			npchar.dialog.FileName = "Enc_Officer_dialog.c";
			npchar.loyality = MAX_LOYALITY;
			GiveItem2Character(npchar, "blade_10");
			EquipCharacterByItem(npchar, "blade_10");
			TakeItemFromCharacter(pchar, "blade_10");
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			AddQuestRecord("Saga", "193");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega(); 
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
		break;
		// <-- участвовал в событиях Картахены
		
		//настоящий Гонсалес - Ортега, маяк
		case "Ortega":
			dialog.text = "Я не жду гостей сегодня, как, впрочем, и в любой другой день. Что тебе нужно?";
			link.l1 = "Ну здравствуй, Висельник. Меня послал к тебе Лесной дьявол. Хорошо, что я успел найти тебя раньше Джекмана. Его люди ищут тебя по всем Карибам. На твоё счастье, Генри, только Свенсон знает, откуда ты родом. Он попросил предупредить тебя.";
			link.l1.go = "Ortega_1";
		break;
		
		case "Ortega_1":
			dialog.text = "Так вот оно что... Стало быть, Свенсон до сих пор жив и не забыл старого друга. Сколько крови утекло с тех пор, когда я впервые увидел его салагой с потрёпанного брига... Как быстро пролетела жизнь, и мне уже совсем немного осталось\nХотелось умереть своей смертью на этом пустыре подальше от людей, и поближе к морю. Но если Джекман снова появился на Карибах, то в покое он меня не оставит. Задолжал я его хозяину не по своей воле. Но кто мне теперь поверит\nСмерти я не боюсь, я боюсь боли. А Джекман большой мастак по этой части. При одной мысли об этом у меня в глазах темнеет и сердце останавливается.";
			link.l1 = "Если ты про Бучера, то его повесили двадцать лет назад. Так что долг тебе возвращать некому. А если боишься Джекмана, можешь передать свой долг мне. Думаю, моя встреча с ним неизбежна, и рассказать о ней сможет лишь один из нас.";
			link.l1.go = "Ortega_2";
		break;
		
		case "Ortega_2":
			dialog.text = "Таких, как капитан Бучер, мало повесить один раз. Бывший палач Сент-Джонса мог бы рассказать много интересного о мертвецах, которые возвращаются с того света. Впрочем, Якоб многому научился у капитана и я даже не знаю, с кем из них я бы предпочёл не встречаться подольше.";
			link.l1 = "Зачем ты понадобился Джекману?";
			link.l1.go = "Ortega_3";
		break;
		
		case "Ortega_3":
			dialog.text = "Я должен был передать золото одной вдове на содержание дочери Бучера. А что ты так удивился? Да, у капитана незадолго до гибели 'Нептуна' родилась дочь. Он не смог за ней вернуться вовремя и послал меня, чтобы я позаботился о малышке и её кормилице.";
			link.l1 = "Кормилицу звали Глэдис Чандлер?";
			link.l1.go = "Ortega_4";
		break;
		
		case "Ortega_4":
			dialog.text = "Не прикидывайся простаком. Если Джекман ищет меня, значит, ему нужна дочь Бучера, а не мой старый хангер. И ты наверняка знаешь, что помимо Висельника он ищет женщину по имени Глэдис родом из Белиза и её воспитанницу. Будь честным со мной, и может быть я тебе поверю.";
			link.l1 = "Что ты должен был сказать Глэдис?";
			link.l1.go = "Ortega_5";
		break;
		
		case "Ortega_5":
			dialog.text = "Ничего. Я должен был показать ей перстень Бучера. По нему она признала бы меня, как гонца от капитана. А ещё я должен был передать ей сундук с золотыми дублонами на содержание крошки. Чтобы забрать этот перстень у одного негодяя, мне пришлось его убить. Из-за этого я задержался на Антигуа на целый месяц\nА когда наконец добрался до Белиза Глэдис и след простыл, а город лежал в руинах после набега испанцев. Она успела продать свой дом и укатила куда-то вместе с новым хахалем, прихватив малютку Элен с собой. Надеюсь, она позаботилась о ней, а не продала цыганам или в бордель на забаву.";
			link.l1 = "Дочь Бучера звали Элен?";
			link.l1.go = "Ortega_6";
		break;
		
		case "Ortega_6":
			dialog.text = "Именно так. В честь матери Бучера. Если ты не боишься живых мертвецов и пиратов с мёртвыми глазами, как у моего приятеля Якоба, я могу отдать тебе перстень и золото. Я не тронул его. С голоду подыхал, но не тронул.  Отдай эту посылку, кому сочтёшь нужным. А взамен я попрошу те...";
			link.l1 = "Что с тобой, Генри?!";
			link.l1.go = "Ortega_7";
		break;
		
		case "Ortega_7":
			dialog.text = "Те... бя... Попро... ах!";
			link.l1 = "Нет!";
			link.l1.go = "Ortega_8";
		break;
		
		case "Ortega_8":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			AddQuestRecord("Saga", "20");
			pchar.questTemp.Saga = "svenson1";
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "bucher_ring"); //перстень Бучера
			//таймер на возврат смотрителя
			SetFunctionTimerCondition("Saga_LightmanReturn", 0, 0, 10, false);
			//ставим прерывания, если ГГ наследил в городе
			if (CheckAttribute(pchar, "questTemp.Saga.Trap"))
			{
				pchar.quest.Saga_Trap.win_condition.l1 = "location";
				pchar.quest.Saga_Trap.win_condition.l1.location = "Mayak11";
				pchar.quest.Saga_Trap.function = "Saga_CreateTrapBandos";
				TraderHunterOnMap(true);
			}
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			
			DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs");
			//pchar.questTemp.HelenDrinking = "end_henry";
		break;
		
		//бандиты в поисках Гонсалеса, маяк
		case "saga_trap":
			dialog.text = "А-а, вот и наш любопытный дружок! Успел таки добраться до Гонсалеса? Молодец, что вывел нас на него... более ты нам не нужен. Ребята, валим этого пижона!";
			link.l1 = "Ну, держитесь, крабьи потроха!";
			link.l1.go = "saga_trap_1";
		break;
		
		case "saga_trap_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			int n = makeint(MOD_SKILL_ENEMY_RATE/3);
			for (i=1; i<=3+n; i++)
			{	
				sld = characterFromId("sagatrap_sold_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		//<-- поиск Гонсалеса, Картахена
		
//--------------------------------------------НПС по квесту Возвращение барона---------------------------------
		
		// доминиканский вождь
		case "DominicaHead":
			dialog.text = "Ахой! Ахой! Великий Кукулькан требовать новый жертва! О-ей! Дух великого воина прошлого прийти наш деревня, дабы быть принесённым великий Кукулькан! О-ёй! Все склониться перед духом великий воин!";
			link.l1 = "(глухо) Чёрт возьми, куда я попал?";
			link.l1.go = "DominicaHead_1";
			NextDiag.TempNode = "DominicaHead";
			if (CheckCharacterItem(pchar, "Ultimate_potion"))
			{
				pchar.systeminfo.NoNotifications = true;
				RemoveItems(pchar, "Ultimate_potion", 1);
				DeleteAttribute(pchar,"systeminfo.NoNotifications");
				notification("Использовано зелье команчей", "None");
				LAi_SetCurHPMax(PChar);
				AddCharacterHealth(pchar, 50);
				DeleteAttribute(pchar, "chr_ai.poison");
				notification("Вы чувствуете себя полностью излеченным!", "None");
				//Log_Info("Использовано зелье команчей");
				//Log_Info("Вы чувствуете себя полностью излеченным!");
				//PlaySound("Ambient\Tavern\glotok_001.wav");
				PlaySound("Ambient\Horror\Fear_breath_01.wav");
			}
		break;
		
		case "DominicaHead_1":
			dialog.text = "О-ёй! Великий воин желать быть пожран великий Кукулькан! Солнце становиться выше, тени короче! Великий Кукулькан скоро оживать! Мы отвести тебя к нему, о великий воин, и ты продолжить свой путь по стране предков!";
			link.l1 = "(глухо) Ну и вздор... Опять Кукулькан? Эй, вождь, я прибыл с миром! Я пришёл...";
			link.l1.go = "DominicaHead_2";
		break;
		
		case "DominicaHead_2":
			dialog.text = "О-ёй! Великий воин сказать мне, что желать быть принесенным в жертву Кукулькан немедля. О, великий воин! Мы отправиться к Кукулькан сейчас и ждать, когда его дух посетит нас! Воины! Нам выпасть огромный честь - провести дух предка к Кукулькан!";
			link.l1 = "(глухо) Вот дубина... Ладно, придётся идти с ними. Хорошо, хоть не напали всем скопом - в этой штуковине я бы от них не отбился...";
			link.l1.go = "DominicaHead_3";
		break;
		
		case "DominicaHead_3":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload1_back", "Saga_DominicaDollyReload", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
			for (i=2; i<=10; i++)
			{
				sld = characterFromId("Dominica_ind_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
			}
		break;
		
		case "DominicaHead_4":
			dialog.text = "Мы прийти к Кукулькан, великий дух предка. Скоро солнце идти вниз, тени расти, и Кукулькан явиться к нам. Жди, великий воин...";
			link.l1 = "(глухо) Всё с тобой понятно, индейский военачальник...";
			link.l1.go = "DominicaHead_5";
		break;
		
		case "DominicaHead_5":
			DialogExit();
			bDisableCharacterMenu = true;//лочим Ф2
			AddQuestRecord("BaronReturn", "7");
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_DominicaDollyWait", 5.0);
			pchar.questTemp.Saga.BaronReturn = "third_teleport";
		break;
		
		case "DominicaHead_6":
			dialog.text = "Кукулькан ожить! Кукулькан с нами! Великий воин может быть принесён жертва Кукулькан! Воины, склонить головы перед великий дух предка!";
			link.l1 = "(глухо) Не мешай, вождь. Я сам принесу себя в жертву Кукулькану. Не в первый раз...";
			link.l1.go = "DominicaHead_7";
		break;
		
		case "DominicaHead_7":
			DialogExit();
			bDisableCharacterMenu = false;//разлочим Ф2
			AddQuestRecord("BaronReturn", "8");
			for (i=2; i<=10; i++)
			{
				sld = characterFromId("Dominica_ind_"+i);
				LAi_SetActorType(sld);
			}
		break;
		
//----------------------------------------НПС по квесту Искушение Барбазона----------------------------------
		// капитан рыболовного баркаса, стыривший шелк, море
		case "BarbCapBarkas":
			dialog.text = "Чем обязан вашему визиту, минхер?";
			link.l1 = "Так-так... Ну, рассказывай, дружище, что это ты тут делаешь?";
			link.l1.go = "BarbCapBarkas_1";
		break;
		
		case "BarbCapBarkas_1":
			dialog.text = "Что делаю? Я рыбак, и занимаюсь ловлей рыбы. А какого чёрта вы мне тут устраиваете допрос, да ещё в таком тоне?";
			link.l1 = "Не лги мне, приятель. Может, ты и рыбак, да только сейчас ты ловил совсем не рыбу. Здесь, на этом месте, из одного корабля был выброшен ценный парусный шёлк. И твоё присутствие тут кажется мне весьма подозрительным.";
			link.l1.go = "BarbCapBarkas_2";
		break;
		
		case "BarbCapBarkas_2":
			dialog.text = "Что за вздор? Какой ещё шёлк?";
			link.l1 = "Какой шёлк? Который из Китая привозят... Не строй из себя дурака! Значит, так: или ты немедленно достаёшь из трюма своей скорлупы выловленный шёлк и передаёшь его мне, или я сам его заберу. Правда перед этим тебя и твоих матросов моя абордажная рота уложит физиономиями в палубу. Ну? Мне звать своих ребят?";
			link.l1.go = "BarbCapBarkas_3";
		break;
		
		case "BarbCapBarkas_3":
			dialog.text = "Нет! Сударь, откуда же я мог знать... Плавают себе и плавают тюки, вот я и решил...";
			link.l1 = "Живо переноси шёлк на мой корабль!";
			link.l1.go = "BarbCapBarkas_4";
		break;
		
		case "BarbCapBarkas_4":
			dialog.text = "Да, да, конечно. Сейчас мы всё сделаем, только не трогайте мою лодку!";
			link.l1 = "Давай пошевеливайся! У меня мало времени...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Saga_BarbBarkasSilk");
		break;
		
		case "BarbCapBarkas_5":
			dialog.text = "Вот, мы перенесли всё, что выловили в море, все девять тюков. Больше не было, я клянусь...";
			link.l1 = "Ладно. Рыбачь себе дальше и впредь не зарься на чужое!";
			link.l1.go = "BarbCapBarkas_6";
		break;
		
		case "BarbCapBarkas_6":
			DialogExit();
			npchar.DontDeskTalk = true;
			npchar.lifeday = 0;
			LAi_SetStayType(npchar);
			pchar.quest.BarbBarkas_Sink.over = "yes"; //снять прерывание
			pchar.quest.BarbBarkas_Abordage.over = "yes"; //снять прерывание
			NextDiag.CurrentNode = "BarbCapBarkas_7";
			AddQuestRecord("BarbTemptation", "6");
			pchar.questTemp.Saga.BarbTemptation = "give_silk";
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
		break;
		
		case "BarbCapBarkas_7":
			dialog.text = "Вы уже получили, что хотели. У меня больше ничего нет! Что вам ещё от меня надо?";
			link.l1 = "Не переживай, приятель. Я уже ухожу.";
			link.l1.go = "exit";
			NextDiag.TempNode = "BarbCapBarkas_7";
		break;
		
		// Моррель, капитан потопленного судна, тюрьма
		case "Morelle":
			dialog.text = "Если ты от Барбазона, то передай ему, что по своей воле я из тюрьмы не выйду. Я лучше дождусь суда. Даже голландская пенька на шее лучше его ласк.";
			link.l1 = "Не порть воздух раньше времени. Жак со слов твоего штурмана считает тебя покойником. Он послал меня разыскивать свой шёлк, который ты якобы выкинул за борт. Сколько его было на борту твоей бригантины?";
			link.l1.go = "Morelle_1";
		break;
		
		case "Morelle_1":
			dialog.text = "Я сам во всём виноват, бес попутал. Связной передал для Барабазона девять тюков шёлка. Я приказал выследить его. Он поднял шум и его пришлось прикончить. В его тайнике нашлось ещё три тюка, которые я забрал для себя и перепрятал в укромном месте. Вероятно, шум привлёк внимание\nНас быстро вычислили, и в море 'Соленого Пса' ждал голландский патруль, уйти от которого нам так и не удалось. Не говори Барбазону про меня, и можешь забрать лишний шёлк себе. Тайник находится на пляже Гранд Кейс, между камней в тупике. Мне-то он теперь вряд ли понадобится.";
			link.l1 = "Хорошо. Я не скажу Барбазону, что ты ещё жив. Если то, что о нём болтают правда, то тебе и впрямь лучше быть повешенным голландцами. А может ещё и каторгой отделаешься.";
			link.l1.go = "Morelle_2";
		break;
		
		case "Morelle_2":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			// тайник - модель
			//int m = Findlocation("Shore40");
			//locations[m].models.always.Roll = "Roll_of_rolls";
			//Locations[m].models.always.Roll.locator.group = "quest";
			//Locations[m].models.always.Roll.locator.name = "quest1";
			pchar.quest.Saga_MorelGoods.win_condition.l1 = "locator";
			pchar.quest.Saga_MorelGoods.win_condition.l1.location = "Shore40";
			pchar.quest.Saga_MorelGoods.win_condition.l1.locator_group = "quest";
			pchar.quest.Saga_MorelGoods.win_condition.l1.locator = "quest1";
			pchar.quest.Saga_MorelGoods.function = "Saga_SetMorelGoods";
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 200);//скрытность
		break;
		
		// Валет, брат Джекмана в Капстервиле
		case "valet":
			dialog.text = "Я жду человека, который знает, когда начнётся охота на белую акулу.";
			link.l1 = "Охота уже началась.";
			link.l1.go = "valet_1";
		break;
		
		case "valet_1":
			dialog.text = "Наконец-то! Теперь слушай меня внимательно: тебе нужно отправиться в гости к Маркусу Тираксу в Ла Вегу и сообщить ему, что бригантина 'Разлучница' была атакована у острова Теркс и укрылась в южной бухте. Её капитан тяжело ранен, а команда ждёт помощи. Сам ты узнал об этом случайно, подобрав в море матроса с 'Разлучницы'. Матрос умер. Больше ты ничего не знаешь. Запомнил?";
			link.l1 = "А зачем для такого пустяка нужен именно я? Стоило ждать столько времени...";
			link.l1.go = "valet_2";
		break;
		
		case "valet_2":
			dialog.text = "Тебе платят за то, чтобы ты работал, а не вопросы задавал. Впрочем, ты прав. Это ещё не всё. Должен тебя предупредить, что Тиракс вряд ли тебя отпустит, пока не убедится, что ты говоришь правду. Ну, а когда убедится, вознаградит тебя по заслугам. Если успеет...";
			link.l1 = "Что-то ты темнишь, сударь... А почему бы тебе самому не воспользоваться его благодарностью?";
			link.l1.go = "valet_3";
		break;
		
		case "valet_3":
			dialog.text = "Карамба! Кто бы ты ни был, но твоё любопытство мне не нравится! Твоя болтовня однажды сведёт тебя в могилу.";
			link.l1 = "Да, временами я бываю просто несносен. Особенно, когда вижу, что меня собираются подставить. Нет, дружок, играть мы будем по моим правилам. Кто твой хозяин, чёрт бы тебя побрал? Отвечай, или я вытащу из тебя эти сведения!";
			link.l1.go = "valet_4";
		break;
		
		case "valet_4":
			dialog.text = "Ах ты... мерзавец! Ну, Барбазону это аукнется, а тебе недолго жить осталось, наглец!";
			link.l1 = "Ха! Другой реакции я и не ожидал. Держись, прохвост!";
			link.l1.go = "valet_5";
		break;
		
		case "valet_5":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_ValetDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "vensan":
			// Addon 2016-1 Jason пиратская линейка патч 17/1
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
			{
				dialog.text = "Чарли Принц? Что ты здесь делаешь? А-аргх, три тысячи чертей, я понял! Это ты всё затеял!";
				link.l1 = "Уймись, Берни. Я на твоей стороне. Засада на берегу уничтожена, так что твоему судну и тебе ничего не угрожает, если, конечно, не раскуривать трубку на палубе.";
				link.l1.go = "vensan_8";
			}
			else
			{
				dialog.text = "Чёрт возьми, вы кто? Как вы сюда попали? Уходите быстрее - мой корабль заминирован, и негодяи, засевшие на берегу, могут взорвать его одним выстрелом.";
				link.l1 = "Не беспокойтесь, сударь. Засада на берегу уничтожена. Вашему судну ничего не угрожает, если, конечно, не раскуривать трубку на палубе. Ваше имя?";
				link.l1.go = "vensan_1";
			}
		break;
		
		case "vensan_1":
			dialog.text = "Венсан. Бернар Венсан. А вы?";
			link.l1 = "Капитан "+GetFullName(pchar)+". Сейчас я разрежу веревки и освобожу вас...";
			link.l1.go = "vensan_2";
		break;
		
		case "vensan_2":
			LAi_SetStayType(npchar);
			dialog.text = "Ох... Спасибо. Как мне отблагодарить вас?";
			link.l1 = "Ещё не всё закончилось, сударь. У вас остались живые люди на корабле?";
			link.l1.go = "vensan_3";
		break;
		
		case "vensan_3":
			dialog.text = "Три десятка матросов заперты в трюме...";
			link.l1 = "Выпускайте их и немедленно убирайтесь отсюда.";
			link.l1.go = "vensan_4";
		break;
		
		case "vensan_4":
			dialog.text = "Но...";
			link.l1 = "Не теряйте времени, Бернар. Благодарности выскажете потом, в Ла Веге, у... Тиракса.";
			link.l1.go = "vensan_5";
		break;
		
		case "vensan_5":
			dialog.text = "Так вы здесь не случайно? Вы знали?";
			link.l1 = "Да, не случайно. Мне удалось раскрыть махинацию Джекмана, с помощью которой этот мерзавец рассчитывал уничтожить Маркуса. Да, и попроси Тиракса ничего не предпринимать, пока я не нанесу ему визит - своим вмешательством он может спугнуть Джекмана.";
			link.l1.go = "vensan_6";
		break;
		
		case "vensan_6":
			dialog.text = "Обязательно передам! Вы уже уходите?";
			link.l1 = "Да. И вы поторапливайтесь.";
			link.l1.go = "vensan_7";
		break;
		
		case "vensan_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto2", "none", "", "", "", 5.0);
			Ship_SetTaskRunaway(SECONDARY_TASK, GetCharacterIndex("Cap_Vensan"), GetMainCharacterIndex());
			pchar.questTemp.Saga.BarbTemptation.Vensan_free = "true";
			if (!CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.vensan_attack"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = characterFromId("Mary");
				else sld = characterFromId("Helena");
				sld.dialog.currentnode = "sea_bomb"; 
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto6");
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			sld = characterFromId("Cap_Vensan");
			sld.lifeday = 1;
			sld.DontDeskTalk = true;
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "vensan_8":
			dialog.text = "Это правда? Прости, брат, просто я...";
			link.l1 = "Всё, забудь. Сейчас я разрежу верёвки и освобожу тебя.";
			link.l1.go = "vensan_9";
		break;
		
		case "vensan_9":
			LAi_SetStayType(npchar);
			dialog.text = "Ох... Руки затекли...";
			link.l1 = "Берни, у тебя ещё остались живые люди на корабле?";
			link.l1.go = "vensan_10";
		break;
		
		case "vensan_10":
			dialog.text = "Три десятка матросов заперты в трюме...";
			link.l1 = "Выпускай их и немедленно убирайся отсюда.";
			link.l1.go = "vensan_11";
		break;
		
		case "vensan_11":
			dialog.text = "Но...";
			link.l1 = "Ты будешь мне только мешать, если останешься. Живо поднимай паруса, лети в Ла Вегу и расскажи обо всём Тираксу.";
			link.l1.go = "vensan_12";
		break;
		
		case "vensan_12":
			dialog.text = "Тебя послал Маркус?";
			link.l1 = "Нет. Просто мне удалось раскрыть махинацию одного мерзавца, с помощью которой тот рассчитывал уничтожить Маркуса. Да, и попроси Тиракса ничего не предпринимать, пока я сам не навещу его - своим вмешательством он может спугнуть птичку... Скажи - Принц знает, что делает. И ещё передай ему, чтобы он перестал на меня дуться. Всё, Берни, не теряй времени!";
			link.l1.go = "vensan_7";
		break;
		
 //--------------------------------------НПС по Завещанию Шарпа--------------------------------------------------
		// Устрица, Поль Моллиган
		case "molligan":
			dialog.text = "Что вам нужно на моём судне, сударь?";
			link.l1 = "Здравствуй, Поль. Ведь это ты - Поль Моллиган?";
			link.l1.go = "molligan_0";
		break;
		
		case "molligan_0":
			dialog.text = "Да, это я. Чем обязан?";
			link.l1 = "Я - "+GetFullName(pchar)+", и меня послал за тобой Ян Свенсон.";
			link.l1.go = "molligan_1";
		break;
		
		case "molligan_1":
			dialog.text = "Ян? А-а, припоминаю я тебя. Точно! Ты в последнее время постоянно ошиваешься в его доме. Так что же Яну нужно от меня?";
			link.l1 = "Ты поторопился уйти из Блювельда. Ян хотел погрузить тебе ещё двести центнеров красного дерева, чтобы ты передал его лорду Уиллогби в Бриджтауне. Готовь судно под погрузку - мои люди перенесут тебе в трюмы древесину с моего судна.";
			link.l1.go = "molligan_2";
		break;
		
		case "molligan_2":
			dialog.text = "Красное дерево? Это Ян так сказал? Хм. А почему ты сам не можешь отвезти его на Барбадос? Зачем для этого понадобился я?";
			link.l1 = "Потому что ты идёшь в Бриджтаун, а я - нет. У меня срочное задание от Свенсона, и мне некогда задерживаться. К тому же Ян не доверяет мне переговоров с лордом Уиллогби и возложил это на тебя, уж не обессудь. Давай грузиться, мне уже пора.";
			link.l1.go = "molligan_3";
		break;
		
		case "molligan_3":
			dialog.text = "Послушай, но у меня нет места в трюмах. Я не смогу выполнить просьбу Яна, как бы мне того ни хотелось...";
			link.l1 = "Нет места? Странно... А мне Ян сказал, что у тебя трюмы заполнены не доверху.";
			link.l1.go = "molligan_4";
		break;
		
		case "molligan_4":
			dialog.text = "Это так, но Ян не знал, что я поставил на 'Устрицу' новые, более тяжёлые орудия. Я не могу погрузить груза больше, чем у меня уже есть. Отвези древесину на Барбадос сам, а, дружище? Скажешь Яну, что я не смог. А с Уиллогби уметь разговаривать не надо: пришёл, сдал груз, получил расписку и ушёл. Ничего сложного.";
			link.l1 = "Гм. Это совсем не входило в мои планы... Может, спустимся в трюмы, глянем? Мой квартирмейстер просто мастер упаковки - так уложит товар, что ещё и место останется...";
			link.l1.go = "molligan_5";
		break;
		
		case "molligan_5":
			dialog.text = "Приятель, но я действительно не могу взять лишний груз. Или ты хочешь, чтобы я выбросил для этого за борт орудия и оставил 'Устрицу' беззащитной?";
			link.l1 = "Ладно. Ну, раз ты так категоричен... Но Яну это не понравится, учти!";
			link.l1.go = "molligan_6";
		break;
		
		case "molligan_6":
			dialog.text = "Я объясню Свенсону, не переживай. В конце концов, Лесной Дьявол сам дал промашку, не поинтересовавшись заранее, будет ли у меня место.";
			link.l1 = "Эх, тащи теперь эти брёвна до Барбадоса, чтоб они в труху рассыпались... Пока, приятель.";
			link.l1.go = "molligan_7";
		break;
		
		case "molligan_7":
			DialogExit();
			// ставим проверку скрытности
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > (10+hrand(50)))
			{
				pchar.questTemp.Saga.Molligan.friend = "true"; // будет шанс критического залпа картечью
				sTemp = "Негодяй, похоже, ничего не заподозрил. Подойду к нему поближе и сделаю залп картечью: неожиданное нападение - залог успеха в любой схватке. ";
				log_Testinfo("Друзья");
				AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
				AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			}
			else
			{
				pchar.questTemp.Saga.Molligan.enemy = "true"; // нападет
				sTemp = "";
				log_Testinfo("Враги");
				AddCharacterExpToSkill(pchar, "Sneak", 150);//скрытность
			}
			AddQuestRecord("Testament", "7");
			AddQuestUserData("Saga", "sText", sTemp);
			NextDiag.CurrentNode = "molligan_8";
			npchar.DontDeskTalk = true; // patch-5
		break;
		
		case "molligan_8":
			dialog.text = "Мы всё обсудили, дружище, разве нет?";
			link.l1 = "Да, да. Я уже отправляюсь на свой корабль.";
			link.l1.go = "exit";
			NextDiag.TempNode = "molligan_8";
		break;
		
	//-----------------------------------------НПС по Теням прошлого--------------------------------------------
		// Джим Бенсон, плешивая мэгги
		case "benson":
			dialog.text = "Зачем я вам понадобился? Я не люблю сплетни и азартные игры. А ром предпочитаю глушить в одиночестве. К тому же у меня после этого рейса особенно паршивое настроение.";
			link.l1 = "А что такого особенного произошло в этом рейсе?";
			link.l1.go = "benson_1";
		break;
		
		case "benson_1":
			dialog.text = "Человек мне один хороший доверился, а я пошёл на поводу у команды и выкинул его за борт. Ну не то, чтобы выкинул, всё же старый баркас и запас продовольствия оставляют ему шансы, но, признаться, небольшие.";
			link.l1 = "Чем же он провинился, этот бедолага?";
			link.l1.go = "benson_2";
		break;
		
		case "benson_2":
			dialog.text = "Я тут недавно и мало с кем знаком. Ну и нанял этого добродушного толстяка корабельным врачом, ничего не зная о его прошлом. Когда мы возвращались обратно, от самого Барбадоса у нас на хвосте повисли пираты. Зачем им вдруг понадобилась моя лоханка?\nЕле-еле оторвались благодаря шторму. Ну выпили на радостях по такому случаю. Так вот этот дурень  ничего лучше не придумал, как заявить при всех, что гнались скорее всего за ним, так как он бывший палач и чего-то там знает лишнего\nНу, ясное дело, матросы взвились. Как это так?! Палач на борту да ещё в качестве врача! Да и с пиратами дел никто иметь не хочет... Ну и пришлось мне высадить его, бедолагу. Сам виноват, болтать нужно меньше. Но на душе всё равно тошно. Жалко этого увальня, да и врач он от Бога. Мне вот похмелье как рукой снял.";
			link.l1 = "Чёрт побери! Его звали Раймонд Бейкер, этого вашего врача?";
			link.l1.go = "benson_3";
		break;
		
		case "benson_3":
			dialog.text = "Да. Именно так. А вы откуда знаете? Уж не вы ли гнались за мной?";
			link.l1 = "Нет, не я. Мне просто очень нужен этот человек - второго такого лекаря днём с огнём не сыскать. Где вы его высадили?";
			link.l1.go = "benson_4";
		break;
		
		case "benson_4":
			dialog.text = "Я высадил его в районе 15 гр. 28' северной широты и 63 гр. 28' западной долготы. Поторопитесь, сударь! Он должен быть ещё жив, и если вы его спасёте - вы снимете грех с моей души!";
			link.l1 = "Уже поднимаю якоря!";
			link.l1.go = "benson_5";
		break;
		
		case "benson_5":
			DialogExit();
			NextDiag.CurrentNode = "benson_6";
			AddQuestRecord("Shadows", "3");
			npchar.lifeday = 0;
			bQuestDisableMapEnter = false;
			pchar.quest.Saga_Shadows_Baker.win_condition.l1 = "location";
			pchar.quest.Saga_Shadows_Baker.win_condition.l1.location = "Dominica";
			pchar.quest.Saga_Shadows_Baker.function = "Saga_SetBakerBoat";
			DeleteAttribute(pchar, "Cheats.SeaTeleport");
		break;
		
		case "benson_6":
			dialog.text = "Капитан, поспешите! Он должен быть ещё жив!";
			link.l1 = "Да-да, бегу...";
			link.l1.go = "exit";
			NextDiag.TempNode = "benson_6";
		break;
		
	//---------------------------------------бандиты у джекмановского рудника-------------------------------
		case "mine_bandit":
			locCameraFromToPos(6.21, 2.31, 8.46, true, -2.26, -1.10, 4.99);
			if (CheckAttribute(pchar, "questTemp.Saga.MineAttack"))
			{
				dialog.text = "Эй! А ну стой, где стоишь! Ни шагу дальше! Эта территория - под охраной!";
				link.l1 = "Не будь столь суров, старина! Свои! Мы от Джекмана. Нам нужно пройти на рудник. Приказ хозяина...";
				link.l1.go = "mine_attack";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Эй! А ну стой, где стоишь! Ни шагу дальше! Эта территория - под охраной!";
				link.l1 = "Хм. Но я хочу пройти... С какой стати ты мне это запрещаешь?";
				link.l1.go = "mine_bandit_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "А-а, это опять ты?! Вижу, по-хорошему до тебя не доходит... Ребята, пли!!";
				link.l1 = "...";
				link.l1.go = "mine_bandit_fire";
			}
		break;
		
		case "mine_bandit_0":
			dialog.text = "Давай, проходи, нечего тут стоять!";
			link.l1 = "Хорошо...";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_bandit_0";
		break;
		
		case "mine_bandit_1":
			dialog.text = "А с такой, что рудник за моей спиной - частная собственность, и я здесь стою для того, чтобы не пускать туда всяких проходимцев, вроде тебя. Лучше разворачивайся и уходи с миром, незнакомец. Наши пушки заряжены картечью - так шарахнем, что от тебя только мокрое место останется.";
			link.l1 = "Хех, понятно. Серьёзная у вашего рудника охрана. Хорошо, я ухожу.";
			link.l1.go = "mine_bandit_exit";
			link.l2 = "Ах ты, мерзавец! Ну это мы сейчас посмотрим, от кого что останется!";
			link.l2.go = "mine_bandit_2";
		break;
		
		case "mine_bandit_exit":
			DialogExit();
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "PIRATE_CITIZENS");
			chrDisableReloadToLocation = false;//открыть локацию
			DoQuestReloadToLocation("Mine_02", "reload", "reload3", "");
		break;
		
		case "mine_bandit_2":
			dialog.text = "Ну, ты сам напросился... Ребята, пли!!";
			link.l1 = "...";
			link.l1.go = "mine_bandit_fire";
		break;
		
		case "mine_bandit_fire":
			DialogExit();
			DoQuestCheckDelay("Saga_MineBanditsFire", 1.5);
		break;
		
		case "mine_banditx":
			locCameraFromToPos(6.21, 2.31, 8.46, true, -2.26, -1.10, 4.99);
			if (CheckAttribute(pchar, "questTemp.Saga.MineAttack"))
			{
				dialog.text = "Эй! А ну поворачивай назад! Эта территория - под охраной!";
				link.l1 = "Хей, полегче, приятель! Мы от Джекмана. Нам нужно пройти на рудник. Приказ хозяина...";
				link.l1.go = "mine_attackx";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Эй! А ну поворачивай назад! Эта территория - под охраной!";
				link.l1 = "Хм. А что там такое?";
				link.l1.go = "mine_banditx_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "А-а, это опять ты?! Вижу, по-хорошему до тебя не доходит... Мушкеты на изготовку! Пли!!";
				link.l1 = "...";
				link.l1.go = "mine_banditx_fire";
			}
		break;
		
		case "mine_banditx_1":
			dialog.text = "Не твоё дело. Убирайся, или мы положим тебя на месте, клянусь!";
			link.l1 = "Ладно, не кипятись. Я уже ухожу.";
			link.l1.go = "mine_banditx_exit";
			link.l2 = "Ах ты, мерзавец! Ну это мы сейчас посмотрим, кто кого положит!";
			link.l2.go = "mine_banditx_2";
		break;
		
		case "mine_banditx_exit":
			DialogExit();
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "PIRATE_CITIZENS");
			DoQuestReloadToLocation("Mine_04", "reload", "reload3", "");
		break;
		
		case "mine_banditx_2":
			dialog.text = "Ну, ты сам напросился... Мушкеты на изготовку! Пли!!";
			link.l1 = "...";
			link.l1.go = "mine_banditx_fire";
		break;
		
		case "mine_banditx_fire":
			DialogExit();
			DoQuestCheckDelay("Saga_MineBanditsxFire", 0.6);
		break;
		
		case "mine_attackx":
			dialog.text = "Вот как? Ну тогда тебе должен быть известен пароль для входа. Говори его, а если ты солгал - даже пожалеть об этом не успеешь...";
			link.l1.edit = 5;
			link.l1 = "";
			link.l1.go = "mine_attackx_1";
		break;
		
		case "mine_attackx_1":
			sTemp = GetStrSmallRegister(dialogEditStrings[5]);
			if (sTemp == "нептун")
			{
				dialog.text = "Всё верно. Но ты, приятель, пришёл не с той стороны. Разве тебя не предупредили? Топай назад по тропе, потом пройдёшь мимо сухого колодца, возьмёшь левее, на тропинку вокруг холма - она тебя приведёт к центральному входу.";
				link.l1 = "А здесь пройти никак нельзя?";
				link.l1.go = "mine_attackx_2";
			}
			else
			{
				dialog.text = "Ребята, у нас тут шпик! Мушкеты на изготовку! Пли!!";
				link.l1 = "...";
				link.l1.go = "mine_banditx_fire";
			}
		break;
		
		case "mine_attackx_2":
			dialog.text = "Нет. Только через центральный вход.";
			link.l1 = "Хорошо, дружище... Эй! Смотри! Что это за дрянь наверху частокола?";
			link.l1.go = "mine_attackx_3";
		break;
		
		case "mine_attackx_3":
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Mine_banditx_"+i);
				LAi_RemoveCheckMinHP(sld);
			}
			sld = characterFromId("Svensons_sold_12");
			LAi_SetActorType(sld);
			LAi_ActorTurnToLocator(sld, "soldiers", "soldier1");
			LAi_ActorAnimation(sld, "shot", "Saga_MineBanditxDie", 1.0);
		break;
		
		case "mine_attack":
			dialog.text = "Да неужели? Ну тогда тебе должен быть известен пароль. Говори его, и говори чётко, чтобы я хорошо расслышал. Ну, а если ты сейчас попытался схитрить - то это была последняя неудачная шутка в твоей жизни.";
			link.l1.edit = 5;
			link.l1 = "";
			link.l1.go = "mine_attack_1";
		break;
		
		case "mine_attack_1":
			sTemp = GetStrSmallRegister(dialogEditStrings[5]);
			if (sTemp == "нептун")
			{
				dialog.text = "Верно. Можете проходить. Старший по лагерю находится в доме слева от входа в шахту. Топайте сразу к нему.";
				link.l1 = "Хорошо, приятель...";
				link.l1.go = "mine_attack_2";
			}
			else
			{
				dialog.text = "Ребята, у нас тут шпик! Орудия, пли!!";
				link.l1 = "...";
				link.l1.go = "mine_bandit_fire";
			}
		break;
		
		case "mine_attack_2":
			DialogExit();
			NextDiag.CurrentNode = "mine_attack_3";
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "ActorDialog_Any2Pchar", -1);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetActorDialogAny2Pchar(npchar.id, "", 0.0, 0.0);
		break;
		
		case "mine_attack_3":
			dialog.text = "Чего тебе ещё? Забыл что-то?";
			link.l1 = "Да. Меня просили передать тебе привет.";
			link.l1.go = "mine_attack_4";
		break;
		
		case "mine_attack_4":
			dialog.text = "Мне? Ха-ха! И от кого же?";
			link.l1 = "От Яна Свенсона, мразь!";
			link.l1.go = "mine_attack_5";
		break;
		
		case "mine_attack_5":
			DialogExit();
			LAi_SetPlayerType(pchar);
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("Mine_bandit_"+i);
				LAi_RemoveCheckMinHP(sld);
			}
			if (pchar.questTemp.Saga.MineAttack == "soldiers")
			{
				sld = characterFromId("Svensons_sold_12");
				LAi_SetActorType(sld);
				LAi_ActorTurnToLocator(sld, "soldiers", "soldier1");
				LAi_ActorAnimation(sld, "shot", "Saga_MineBanditDie", 1.0);
			}
			else
			{
				for (i=1; i<=6; i++)
				{
					sld = characterFromId("Mine_bandit_"+i);
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, "EnemyFight");
				}
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "Saga_BanditsDestroyed");
				AddDialogExitQuest("MainHeroFightModeOn");	
			}
			pchar.quest.Saga_MineAttack_07.win_condition.l1 = "NPC_Death";
			pchar.quest.Saga_MineAttack_07.win_condition.l1.character = "Mine_bandit_1";
			pchar.quest.Saga_MineAttack_07.win_condition.l2 = "NPC_Death";
			pchar.quest.Saga_MineAttack_07.win_condition.l2.character = "Mine_bandit_2";
			pchar.quest.Saga_MineAttack_07.function = "Saga_SvensonMineexitAttack";
		break;
		
	// ----------------------------- диалоги НПС при штурме бандитского рудника -------------------------------
		case "Svensons_off":
			dialog.text = LinkRandPhrase("Мы порвём этих грязных подонков, как старую тряпку!","Мне не терпится врезать как следует по шее этим мерзавцам!","Шестёркам Джекмана не место на Западном Мэйне! Мы выбьем отсюда эту погань!");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Svensons_off";
		break;
		
		case "Svensons_sold":
			dialog.text = LinkRandPhrase("Мы готовы к бою!","Покажем этим ублюдкам!","Они ещё не знают, с кем связались!");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Svensons_sold";
		break;
		
		case "gunner":
			PlaySound("Voice\russian\evilpirates01.wav");
			dialog.text = "Командир, орудие к бою готово. Заряжено бомбой, как вы приказали.";
			link.l1 = "Смотрю, никто не ждёт нас тут в гости... Надо заявить о себе. Ян сказал, что лагерь бандитов за этим холмом. Попадёшь туда, как думаешь?";
			link.l1.go = "gunner_0_1";
		break;
		
		case "gunner_0_1":
			dialog.text = "Запросто, командир. Поднимем ствол повыше, и - в самый раз... Вот так\nГотовьсь!.. Огонь!!";
			link.l1 = "...";
			link.l1.go = "gunner_0_2";
			npchar.quest.canonada = "1";
		break;
		
		case "gunner_0_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_Gunfire", 3.0);
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_1":
			dialog.text = "";
			link.l1 = "Хм. Как думаешь, Рандольф, мы хоть куда-то попали?";
			link.l1.go = "gunner_1_1";
		break;
		
		case "gunner_1_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "Командир, куда-то мы точно попали, но вот куда... За этим проклятым холмом ни черта не видно. Сейчас попробую немного изменить угол\nГотовьсь! Огонь!";
			link.l1 = "...";
			link.l1.go = "gunner_0_2";
			npchar.quest.canonada = "2";
		break;
		
		case "gunner_2":
			PlaySound("interface\abordage_wining.wav");
			PlaySound("types\warrior03.wav");
			dialog.text = "Ха! Смотрите, командир! Посмотрите наверх - это дым! Раздери меня селёдка, если мы не угодили бомбой в какой-то бандитский сарай! Ура-а!";
			link.l1 = "Точно - дым... Перезаряжаем орудие и наводим на тропу - клянусь честью, сейчас к нам пожалуют гости! Встретим их как следует!";
			link.l1.go = "gunner_2_1";
		break;
		
		case "gunner_2_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "Есть, командир! Зарядить бомбой! Приготовиться к выстрелу! Фитиль! Огонь по моей команде!";
			link.l1 = "...";
			link.l1.go = "gunner_2_2";
			npchar.quest.canonada = "3";
		break;
		
		case "gunner_2_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_LoginBandos_01", 6.0);
			LAi_ActorTurnToLocator(pchar, "goto", "goto14");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_3":
			PlaySound("interface\abordage_wining.wav");
			PlaySound("types\warrior03.wav");
			PlaySound("Voice\russian\evilpirates05.wav");
			dialog.text = "Ха-ха, получили, куриные потроха!";
			link.l1 = "Не расслабляться! Зарядить орудие! Не думаю, что это их остановило - сейчас пожалуют ещё!";
			link.l1.go = "gunner_3_1";
		break;
		
		case "gunner_3_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");//
			dialog.text = "Есть, командир! Зарядить бомбой! Готовьсь! Огонь по моей команде!";
			link.l1 = "...";
			link.l1.go = "gunner_3_2";
			npchar.quest.canonada = "4";
		break;
		
		case "gunner_3_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_LoginBandos_02", 5.0);
			LAi_ActorTurnToLocator(pchar, "goto", "goto14");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_5":
			PlaySound("types\warrior04.wav");
			PlaySound("Voice\russian\evilpirates06.wav");
			dialog.text = "Ха-ха-ха, мерзавцы показали спины! Собачье мясо! Картечь с близкого расстояния - убойная штука! Похоже, желание атаковать у них поостыло!";
			link.l1 = "Теперь пора нам пойти в контратаку. Рандольф, ты остаёшься возле орудия. Дай пару выстрелов бомбами в направлении тропы за холмом, потом целься на дым - преврати их логово в дымящиеся развалины! Только нас не подстрели.";
			link.l1.go = "gunner_5_1";
		break;
		
		case "gunner_5_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "Есть, командир! Орудие к бою! Зарядить бомбой!";
			link.l1 = "Отря-яд! К оружию! За мной, в атаку! Ура-а!!";
			link.l1.go = "attack";
		break;
		
		case "attack":
			DialogExit();
			n = Findlocation("mine");
			Locations[n].hidden_fire = true;
			PlaySound("interface\abordage_wining.wav");
			PlaySound("interface\abordage_wining.wav");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			if (GetCharacterIndex("Svensons_sold_12") != -1 && pchar.questTemp.Saga.MineAttack == "soldiers")
			{
				sld = characterFromId("Svensons_sold_12");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=8; i++)
			{
				if (GetCharacterIndex("Ourmine_sold_"+i) != -1)
				{
					sld = characterFromId("Ourmine_sold_"+i);
					if (i == 1) sld.MusketerDistance = 10; 
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			LAi_group_SetRelation("EnemyFight", "TMP_FRIEND", LAI_GROUP_NEITRAL);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_MineBandos_05Die");
			AddDialogExitQuest("MainHeroFightModeOn");	
			DoQuestCheckDelay("Saga_MineSetMusic", 0.3);
			// запускаем автобабахалку на 10 выстрелов
			iTotalTemp = 0;
			DoQuestCheckDelay("Saga_GunAutoFire", 7.0);
			bDisableCharacterMenu = false;//разлочим интерфейсы
			InterfaceStates.Buttons.Save.enable = true;//разрешим сохраняться
		break;
		
		case "convict":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = LinkRandPhrase("Не трогайте меня, я не из них! Убейте бандитов!","Освободи нас, дружище! Перебей мерзавцев!","Режь их, приятель, режь! Чтоб они все сдохли, подонки!");
				link.l1 = "Ха! Не переживай - именно это мы и делаем!";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Неужели рабство закончится? Вы освободите нас?","Хех, неужели я дожил до этого дня?","Мерзавцы выпили из нас всю кровь...");
				link.l1 = "Думаю, приятель, ты скоро сможешь наслаждаться свободой...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "convict";
		break;
		
		// жена Яна Свенсона
		case "js_girl":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Лучше бы вам убраться отсюда, сударь. Мы не укрываем преступников и не конфликтуем с властями колонии.";
				link.l1 = "Хорошо, я уже ухожу...";
				link.l1.go = "exit";
				NextDiag.TempNode = "js_girl";
				break;
			}
			if(NPChar.quest.meeting == "0")
			{
				// Первый диалог с Элен
				if(startHeroType == 4)
				{
					dialog.text = "А, Элен. Могла бы и поприличнее принарядиться перед тем, как заходить к Яну в таком виде и показывать, какая ты на самом деле. Жаль, что он мне не верит.";
					link.l1 = "И какая же? Он помогал матери растить меня с самого детства и знает меня, как никто другой. У меня нет от него секретов. Жарко мне с самого детства, вот и всё.";
					link.l1.go = "js_helen_ft";
					NextDiag.TempNode = "js_girl";
					NPChar.quest.meeting = "1";
					break;
				}
				dialog.text = TimeGreeting()+", сэр. Вы, как я полагаю, к Яну?";
				link.l1 = "Здравствуйте. Приятно познакомиться, мисс?..";
				link.l1.go = "js_girl_1";
			}
			else
			{
				// заглушка элен
				if(startHeroType == 4)
				{
					dialog.text = "Ян у себя. Проходи, не на что здесь смотреть и действовать мне на нервы.";
					link.l1 = "Да не очень-то и хотелось.";
					link.l1.go = "exit";
					NextDiag.TempNode = "js_girl";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Joan")) {
					dialog.text = "Фыр!";
					link.l1 = "И вам не хворать, миссис Свенсон.";
					link.l1.go = "exit";
					break;
				}
				
				if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
				{
					dialog.text = TimeGreeting()+", капитан "+GetFullName(pchar)+". Если вы к Яну, то я вынуждена вас огорчить - его нет дома. Он отбыл по срочным делам.";
					link.l1 = "Чёрт побери! И это именно тогда, когда он мне больше всего нужен! Скажите, миссис Свенсон, а когда ваш муж вернётся - он не сказал?";
					link.l1.go = "js_girl_3";
					break;
				}
				dialog.text = "А-а, это опять вы, капитан "+GetFullName(pchar)+"... Проходите, Ян как обычно - у себя на втором этаже.";
				link.l1 = "Спасибо, миссис Свенсон...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "js_girl";
		break;
		
		case "js_girl_1":
			dialog.text = "Миссис. Миссис Джоанна Свенсон.";
			link.l1 = "Капитан "+GetFullName(pchar)+".";
			link.l1.go = "js_girl_2";
		break;
		
		case "js_girl_2":
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
			{
				dialog.text = "Даже капитан? Ну что же, рада приветствовать вас в моём доме. Но если вы пришли к Яну - то я вынуждена вас огорчить - его нет дома. Он отбыл по срочным делам.";
				link.l1 = "Чёрт побери! И это именно тогда, когда он мне больше всего нужен! Скажите, миссис Свенсон, а когда ваш муж вернётся - он не сказал?";
				link.l1.go = "js_girl_3";
				break;
			}
			dialog.text = "Даже капитан? Ну что же, рада приветствовать вас в моём доме. Муж на втором этаже в своём кабинете. Поднимайтесь вверх по лестнице.";
			link.l1 = "Я понял, миссис Свенсон...";
			link.l1.go = "exit";
			NPChar.quest.meeting = "1";
			NextDiag.TempNode = "js_girl";
		break;
		
		case "js_girl_3":
			dialog.text = "Нет. Точной даты возвращения он не сказал даже мне, поскольку и сам не знает, сколько продлятся поиски.";
			link.l1 = "Простите, что вмешиваюсь не в своё дело, но мне и правда очень нужен Ян... Какими поисками он занят, не скажете?";
			link.l1.go = "js_girl_4";
		break;
		
		case "js_girl_4":
			dialog.text = "Скажу, конечно. Пропала его любимица Элен по прозвищу Румба, дочь старого приятеля по лихим годам Шона МакАртура, упокой Господи его душу. Ян относится к этой чертовке, словно к своей дочери. Сильно она по характеру похожа на его старинную любовь, такая же безбашенная, видимо, в этом и кроется его привязанность\nИ вот неделю назад эта девка пропала вместе со своей шхуной 'Радугой' и всей командой. Шон МакАртур выучил Элен морскому делу, а 'Радуга' досталась ей в наследство. Вот теперь она и играет в капитана...";
			link.l1 = "Что могло с ней случиться?";
			link.l1.go = "js_girl_5";
		break;
		
		case "js_girl_5":
			dialog.text = "Кто же знает... Неделя - срок небольшой, но вдова МакАртура Глэдис уверена, что с её дочерью случилось что-то скверное, и смогла убедить в этом Яна. Тот поднял на ноги своих людей и сам отправился на поиски, но пока безрезультатно. Хотя лично моё мнение - ничего с Элен страшного не произошло, и Ян только напрасно себе душу истерзал\nНаслушался бредней старой толстухи Глэдис и забил тревогу. А девка, скорее всего, сейчас кувыркается с каким-нибудь очередным ухажёром подальше от людских глаз, и всех дел. Нагуляется - приплывёт назад.";
			link.l1 = "Джоанна, где мне найти эту Глэдис? Я хочу поговорить с ней...";
			link.l1.go = "js_girl_6";
		break;
		
		case "js_girl_6":
			dialog.text = "Её дом рядом с пристанью, налево от причала. Но там её скорее всего нет. Она целыми днями торчит на стенах форта, всё высматривает свою ненаглядную дочку.";
			link.l1 = "Ясно. Спасибо огромное за информацию!";
			link.l1.go = "js_girl_7";
		break;
		
		case "js_girl_7":
			DialogExit();
			NextDiag.CurrentNode = "js_girl_8";
			sld = characterFromId("Gladis"); //устанавливаем Глэдис на форт
			ChangeCharacterAddressGroup(sld, "SantaCatalina_fort", "goto", "goto53");
			LAi_SetStayType(sld);
			sld.dialog.currentnode = "FindHelena";
			pchar.questTemp.Saga = "gladis";
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("SantaCatalina_tavernkeeper"));
			DelMapQuestMarkCity("SantaCatalina");
		break;
		
		case "js_girl_8":
			dialog.text = "Ян пока ещё не вернулся из поисков, капитан, так что заходите позже.";
			link.l1 = "Понятно...";
			link.l1.go = "exit";
			NextDiag.TempNode = "js_girl_8";
		break;
		
		case "js_helen_ft":
			dialog.text = "Сказала бы я, от чего тебе жарко. Сходила бы ты в церковь, а то почти ни разу тебя там не видела.";
			link.l1 = "Потому что моя совесть чиста - мне не из-за чего вымаливать прощение. До сих пор злишься, что он помог мне снарядить корабль, а не купил очередное платье для тебя, Джоанна?";
			link.l1.go = "js_helen_ft_1";
		break;
		
		case "js_helen_ft_1":
			dialog.text = "Я? Злюсь? Не стоишь ты того. Просто больно легко тебе всё даётся, не заслуживаешь ты этого.";
			link.l1 = "Зато как только я получила корабль, начала зарабатывать сама. А ты с тех пор, как тебя подобрали, как кошку, ни дня не проработала. И кто из нас сидит на его шее?";
			link.l1.go = "js_helen_ft_2";
		break;
		
		case "js_helen_ft_2":
			dialog.text = "Договоришься ты однажды. Ему и Глэдис явно стоило поучить тебя приличиям. Ладно, проходи, зачем пришла - не мозоль мне глаза, Элен. Он у себя.";
			link.l1 = "*про себя* Тупая курица. *Вслух* Угу, непременно.";
			link.l1.go = "exit";
		break;
		
		// хронометр Алекса
		case "Alexs_bandos":
			dialog.text = "Эй! Ты чего здесь выискиваешь, а?";
			link.l1 = "Это я тебя хотел спросить - что ты со своими дружками забыл в моём подземелье?!";
			link.l1.go = "Alexs_bandos_1";
		break;
		
		case "Alexs_bandos_1":
			dialog.text = "Ха! Твоё подземелье? Когда же оно стало твоим, пижон?";
			link.l1 = "Тогда, когда твой папаша совершал ошибку, греша с твоей маманей.";
			link.l1.go = "Alexs_bandos_2";
		break;
		
		case "Alexs_bandos_2":
			dialog.text = "Нарываешься, да?";
			link.l1 = "Слушай, дружок: даю тебе шанс свалить отсюда подобру-поздорову. Это моё подземелье, и я не позволю по нему расхаживать не пойми кому, ясно? Стоит мне свистнуть - и здесь через минуту будет половина пиратов Исла Тесоро.";
			link.l1.go = "Alexs_bandos_3";
		break;
		
		case "Alexs_bandos_3":
			dialog.text = "Ну что же, тогда мы постараемся заткнуть тебе рот побыстрее, чтобы ты не свистел!";
			link.l1 = "Ха-ха! Ты жалок, оборванец!";
			link.l1.go = "Alexs_bandos_4";
		break;
		
		case "Alexs_bandos_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Bermudes_Dungeon")], false);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Alexs_bandos_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
			int iScl = 25+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("Alexs_bandos_5", "mush_ctz_8", "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "cartridge", iScl*2+50);
			ChangeCharacterAddressGroup(sld, "Bermudes_Dungeon", "monsters", "monster8");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "AlexClock_BandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "helendrinking_gypsy":
			dialog.text = "Погоди, соколик!";
			link.l1 = "Не вовремя ты, голубушка.";
			link.l1.go = "helendrinking_gypsy_1";
		break;
		
		case "helendrinking_gypsy_1":
			dialog.text = "Ох, не прав ты, красавец. Нравишься ты девочке этой, да и мы её любим.";
			link.l1 = "Не самая лучшая рекомендация... Давай выкладывай, что у тебя. Ручку позолотить?";
			link.l1.go = "helendrinking_gypsy_2";
		break;
		
		case "helendrinking_gypsy_2":
			dialog.text = "Подспорье тебе хочу предложить в деле твоём нелёгком. Гляди! Кружка заговорённая, да мазь запретная. Кружка в деле питейном выручит, а мазь - в любовном. Что выберешь? Всего две тысячи!";
			link.l1 = "Ничего не надо - и так вашей сестре кучу серебра уже отвалил.";
			link.l1.go = "helendrinking_gypsy_refuse";
			if (sti(pchar.money) >= 2000) {
				link.l2 = "Запретная мазь, говоришь? Есть грех, признаю. Давай сюда.";
				link.l2.go = "helendrinking_gypsy_fuck";
				link.l3 = "Кружка? Я разве похож на пьяницу? Ну да, кого я обманываю - беру!";
				link.l3.go = "helendrinking_gypsy_drink";
			}
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_refuse":
			dialog.text = "Красивый, да глупый. Лети дальше, соколик.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_drink":
			dialog.text = "Да не прячь ты её в карманы свои бездонные! Лети дальше, соколик, и не греши!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddMoneyToCharacter(pchar, -2000);
			GiveItem2Character(pchar, "totem_01");
			Log_Info("Получен талисман 'Лужёная глотка'!");
			PlaySound("interface\important_item.wav");
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_fuck":
			dialog.text = "Да не прячь ты её в карманы свои бездонные! Лети дальше, соколик, и не греши!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddMoneyToCharacter(pchar, -2000);
			GiveItem2Character(pchar, "totem_03");
			Log_Info("Получен талисман 'Бальзам Купидона'!");
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			notification("Элен не одобряет", "Helena");
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_joan":
			dialog.text = "Ах! Вон отсюда, мерзавка! Я тебе сколько раз говорила, не смей залезать в мой дом! А это кто ещё такой?!";
			link.l1 = "Мэм, мы же с вами уже знакомы.";
			link.l1.go = "helendrinking_joan_1";
		break;
		
		case "helendrinking_joan_1":
			dialog.text = "Месье де Мор? Хорошенькие дела! Это вы так с моим мужем дела ведёте?! Дождались! А я предупреждала Яна: однажды эта шлёндра начнёт мужиков своих водить! И что это вы в руках держите?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog1");
		break;
		
		case "helendrinking_joan_2":
			dialog.text = "Что-о-о?! Да как ты смеешь, дрянь?! Никуда вы не уйдёте, сейчас придёт мой муж и враз научит тебя, как со старшими разговаривать!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog3");
		break;
		
		case "helendrinking_fort_officer":
			dialog.text = "Что здесь происходит? Мисс МакАртур! Я очень уважал вашего отца, да и мистер Свенсон - нам друг... Но разве вы не помните, чем всё закончилось в прошлый раз?!\nОбидно, слово офицера, обидно! Могли бы и пригласить!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog");
		break;
		
		case "helendrinking_fort_officer_1":
			dialog.text = "Почту за честь, мисс МакАртур. Позвольте заметить, что мы все очень рады вашему возвращению. То, что случилось, - великая тайна, но... неудивительно, что город о ней знает. Однако болтать никто не будет. Приношу свои искренние извинения за недавнее поведение одного из наших капитанов. И отдельно хочу поблагодарить вас, месье де Мор.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog3");
		break;
		
		case "helendrinking_fort_officer_2":
			dialog.text = "Всё будет хорошо, мисс. Месье, буду откровенен: несмотря на то, что Донован поступил как настоящий мерзавец и бандит, флот, безусловно, никогда открыто не осудит его - скорее даже поддержит. Ваш небольшой поход попал в сводки и значительно осложнил отношения между нашими странами. Тем не менее, принимая во внимание влияние мистера Свенсона, а также удивительную готовность к уступкам, на которые ради вас пошёл Капстервиль, вам опасаться нечего.";
			link.l1 = "Вот и славно. Предлагаю за это и выпить!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog1");
		break;
		
		case "helendrinking_poorman":
			dialog.text = "Уважаемые, извините великодушно, ну так что там с работой?";
			link.l1 = "А-ать! Ты всё ещё здесь?!";
			link.l1.go = "helendrinking_poorman_1";
		break;
		
		case "helendrinking_poorman_1":
			dialog.text = "Мил человек, да куда ж я денусь? Только вот отлить отходил, да расчувствовался от вашей беседы, и разморило немного. Душевно-то как!";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.BoughtRainbow")) {
				link.l1 = "Господи, ну раз дал я тебе слово, то делать теперь нечего. Иди, принимай командование.";
				link.l1.go = "helendrinking_poorman_bought";
			} else {
				link.l1 = "Нет у меня для тебя работы, уважаемый.";
				link.l1.go = "helendrinking_poorman_notbought";
			}
		break;
		
		case "helendrinking_poorman_bought":
			dialog.text = "Так точно, капитан!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AddRainbow");
			AddDialogExitQuestFunction("HelenDrinking_LightsOut1NoArg");
		break;
		
		case "helendrinking_poorman_notbought":
			dialog.text = "Жалко-то как! В любом случае, благодарю за угощение, капитан!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AddRainbow");
			AddDialogExitQuestFunction("HelenDrinking_LightsOut1NoArg");
		break;
		
		case "helensleep_amelia_mary":
			dialog.text = "In nomine Patris et Filii et Spiritus Sancti... проходи, "+GetSexPhrase("сын мой","дочь моя")+".";
			if (HelenSleep_TalkedToAmelia()) {
				link.l1 = "Привет, мать Амелия. Тоже будешь орать на меня?";
				link.l1.go = "helensleep_amelia_mary_know";
			} else {
				link.l1 = "(крестится) Сгинь! Это какой-то кошмар. Что вообще происходит? Я сплю?";
				link.l1.go = "helensleep_amelia_mary_notknow";
			}
		break;
		
		case "helensleep_amelia_mary_know":
			dialog.text = "Нет, соколик. И прости ты дурня Яна - переволновался человек. Но поругать тебя я хочу, конечно. Зачем в церковь пришёл? В грехах покаяться? Или за рыжей?";
			link.l1 = "Сам не знаю...";
			link.l1.go = "helensleep_amelia";
			link.l2 = "Тоже её видела? Приглянулась она мне.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_mary_notknow":
			dialog.text = "Сам ты сгинь. Должны были уже познакомится, да ты тянешь всё. Зачем в церковь пришёл? В грехах покаяться? Или за рыжей?";
			link.l1 = "Сам не знаю...";
			link.l1.go = "helensleep_amelia";
			link.l2 = "Тоже её видела? Приглянулась она мне.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_helen":
			dialog.text = "Доброе утро, соколик. Приём ещё не начался, подожди в очереди, пожалуйста.";
			if (HelenSleep_TalkedToAmelia()) {
				link.l1 = "Привет, твоё превосходительство. Тоже начнёшь орать на меня?";
				link.l1.go = "helensleep_amelia_helen_know";
			} else {
				link.l1 = "Это какой-то кошмар. Что вообще происходит? Я сплю?";
				link.l1.go = "helensleep_amelia_helen_notknow";
			}
		break;
		
		case "helensleep_amelia_helen_know":
			dialog.text = "Нет, соколик. И прости ты дурня Яна - переволновался человек. Ругать тебя незачем, всё правильно сделал - не пошёл за рыжей в церковь. Умничка!";
			link.l1 = "Приятно, когда хвалят. Особенно - если понятно, за что.";
			link.l1.go = "helensleep_amelia";
			link.l2 = "Тоже её видела? Приглянулась она мне.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_helen_notknow":
			dialog.text = "Сейчас тот редкий момент, когда ты бодрствуешь, соколик. Мы с тобой должны были уже познакомится, да ты всё тянешь. Иди сюда, хвалить тебя буду - не пошёл за рыжей в церковь. Умничка!";
			link.l1 = "Приятно, когда хвалят. Особенно - если понятно, за что.";
			link.l1.go = "helensleep_amelia";
			link.l2 = "Тоже её видела? Приглянулась она мне.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia":
			dialog.text = "Не буду тебе голову забивать, дурню, а скажу вот что: быть тебе великим человеком. Много зла принесёшь, но добра всё же больше. А вот счастья тебе не обещано. Счастье, соколик, даётся только тем, кто по своей тропе идёт, да не сворачивает. И поможет тебе не свернуть только женщина верная.\nДве их у тебя будет, и обе счастье принесут, но выбрать тебе надо светленькую.";
			link.l1 = "С чего бы это вдруг? Сам буду решать!";
			link.l1.go = "helensleep_amelia_1";
		break;
		
		case "helensleep_amelia_1":
			dialog.text = "Выбирай-то, конечно, сам, но светленькая - лучше. Мы так порешили.";
			link.l1 = "Кто это - мы?";
			link.l1.go = "helensleep_amelia_2";
		break;
		
		case "helensleep_amelia_2":
			dialog.text = "Несчастная даже имени своего истинного не знает. Назови его, и быть ей твоею. Я так сказала.";
			link.l1 = "Я уже ничего не понимаю.";
			link.l1.go = "helensleep_amelia_3";
		break;
		
		case "helensleep_amelia_3":
			dialog.text = "Слышишь, стучат? Открывай и не ошибись.";
			link.l1 = "И правда, стучат... Входите!";
			link.l1.go = "exit";
			
			PlaySound("interface\knock.wav");
			
			AddDialogExitQuestFunction("HelenSleep_WakeUp");
		break;
		
		case "helendrinking_notifier":
			dialog.text = "Месье, мистер Свенсон просил вас зайти к нему и уделить немного времени.";
			link.l1 = "Чёрт, это не к добру. Ничего не обещаю, но постараюсь.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_End");
		break;
		
		case "islatesoro_pirate1":
			dialog.text = "Удачный день, ребята! Я вам говорил, что она сюда обязательно припрётся? Голубушка, оружие сдаём и идём с нами.";
			link.l1 = "Вы ошиблись, парни. Она со мной.";
			link.l1.go = "islatesoro_pirate1_1";
		break;
		
		case "islatesoro_pirate1_1":
			dialog.text = "Не лезь, а то пристрелю как собаку. За девчонку назначены солидные деньги, а мы парни голодные, без принципов.";
			link.l1 = "Продолжишь разговаривать со мной в таком тоне - станете вы, парни, мёртвые.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroSpawnSecond");
		break;
		
		case "islatesoro_pirate1_2":
			dialog.text = "Совсем озверел уже, Счастливчик? Мы первые её нашли! Обоснуй сначала, прежде чем хайло на меня раскрывать!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog1");
		break;
		
		case "islatesoro_pirate1_3":
			dialog.text = "Сам ты крыса! Да мы испанца того так распотрошили, что год можем на жопе ровно сидеть!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog3");
		break;
		
		case "islatesoro_pirate2":
			dialog.text = "Ба! А вот и наша девочка. Так, все - вон, а вы, мадам, - с нами.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog");
		break;
		
		case "islatesoro_pirate2_1":
			dialog.text = "Нас больше и мы круче, Датчанин. Какое обоснование тебе ещё нужно, крыса ты трюмная? Полгода уже голяк у тебя в море, всё у Вуазье со стола слизываешь!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog2");
		break;
		
		case "islatesoro_pirate2_2":
			dialog.text = "";
			link.l1 = "Похоже, мирного решения не будет.";
			link.l1.go = "islatesoro_pirate_a";
			if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedB")) {
				link.l2 = "Как-как ты сказал? Счастливчик? Я слышал байку, что он с Вуазье сговорились вам наводки хилые давать. Это объясняет вашу полосу неудач в море.";
				link.l2.go = "islatesoro_pirate_b";
			}
			bOk = (!CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice")) || (pchar.questTemp.Mtraxx.Retribution.Choice == "bad");
			if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedC") && CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold") && bOk) {
				link.l3 = "Мне надоел этот фарс. Исла-Тесоро, слушай меня! Кто был со мной в Картахене?! Кто жёг со мной Мериду?! На Чарли Принца бочку катят! Наваляем им, парни!";
				link.l3.go = "islatesoro_pirate_c";
			}
		break;
		
		case "islatesoro_pirate_a":
			dialog.text = "Ты ещё здесь, чучело? Парни, давайте так: кэпа - на ремни, а с девкой потом решим, лады?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog4");
		break;
		
		case "islatesoro_pirate_a_1":
			dialog.text = "Ну давай, хе-хе. Кровь погоняем хоть.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroA");
		break;
		
		case "islatesoro_pirate_b":
			pchar.questTemp.HelenDrinking.IslaTesoroAmbush.TriedB = true;
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 60) {
				dialog.text = "Что?! Дьявол, я знал, что ты мухлюешь с этим очкастым подонком! Режьте их всех, парни, а девку потом подберём!";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("HelenDrinking_IslaTesoroB");
			} else {
				dialog.text = "Ты-то чего лаешь, кэп? Проваливай, пока уважаемые люди про тебя не вспомнили.";
				link.l1 = "";
				link.l1.go = "islatesoro_pirate2_2";
			}
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "islatesoro_pirate_c":
			pchar.questTemp.HelenDrinking.IslaTesoroAmbush.TriedC = true;
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 50) {
				DialogExit();
				AddDialogExitQuestFunction("HelenDrinking_IslaTesoroC");
			} else {
				dialog.text = "Ты-то чего лаешь, кэп? Чарли Принца я видал, и на него ты не тянешь. Проваливай, пока уважаемые люди про тебя не вспомнили.";
				link.l1 = "";
				link.l1.go = "islatesoro_pirate2_2";
			}
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "francois":
			dialog.text = "Шарль де Мор? Сын Анри де Монпе?";
			link.l1 = "Всё так, месье. А кто вы?";
			link.l1.go = "francois_1";
		break;
		
		case "francois_1":
			dialog.text = "Полковник Франсуа де Таванн. Считайте, что вы получили мою пощечину и перчатку в лицо, месье! Не хочу даже марать о вас руки, но клинком, клянусь, достану!";
			link.l1 = "Вызов на дуэль? В таком случае вам придётся постараться получше, полковник. Пока вас можно принять разве что за бандита, а с ними в этих краях разговор короткий! Объяснитесь!";
			link.l1.go = "francois_2";
		break;
		
		case "francois_2":
			dialog.text = "Вы соблазнили мою жену, месье!  Пока я проливал кровь за короля и Отчизну, вы... вы развлекались с моей женой!..";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog");
		break;
		
		case "francois_3":
			dialog.text = "Молчите, мадам. Своим дерзким нарядом вы позорите честь любой женщины, хотя смотритесь вполне уместно рядом с этим недостойным дворянского звания обольстителем!";
			link.l1 = "Все ещё недостаточно оснований для дуэли, полковник. И позволю себе заметить, что пока здесь ведёте себя недостойно вы.";
			link.l1.go = "francois_4";
		break;
		
		case "francois_4":
			dialog.text = "Вам мало? Я навёл справки - на моём месте сейчас могло быть с десяток благородных мужей, месье. Но если вам нужны подробности, то к своему стыду признаюсь, что одной из ваших пассий была Лулу де Таванн, прекраснейшая и честнейшая из женщин!";
			link.l1 = "Лулу значит... И как она?";
			link.l1.go = "francois_5";
		break;
		
		case "francois_5":
			dialog.text = "Молчать! Моя жена, не выдержав мук, которые вы ей нанесли, недавно скончалась! Я потратил почти год и целое состояние, чтобы найти вас, мерзавец! Хватит слов! Или вы примете вызов, или я убью вас как собаку. Ричард! Будьте моим секундантом!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog2");
		break;
		
		case "francois_6":
			dialog.text = "Молчать, месье! Примите вызов или потеряете любые остатки чести, если они у вас ещё имеются!!";
			if (pchar.HeroParam.HeroType == "HeroType_1") {
				link.l1 = "Дуэль так дуэль. Не скрою, люблю я это дело. Капитан, передайте полковнику, что ему пора заказать для себя подходящий гроб.";
			} else {
				link.l1 = "Хотите драки? Будет вам драка! Капитан, передайте полковнику, что ему пора заказать для себя подходящий гроб.";
			}
			link.l1.go = "francois_duel";
			link.l2 = "Здесь не Европа, полковник. Честь на Карибах сложнее обрести, но и не так просто потерять. Я отказываю вам в дуэли, потому что просто не хочу.";
			link.l2.go = "francois_refuse";
		break;
		
		case "francois_7":
			dialog.text = "Твой отец и так на ладан дышит уже, мерзавец! А я уж позабочусь, чтобы он узнал о твоей трусости, подонок!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog7");
		break;
		
		case "richard":
			dialog.text = "Полковник, я подтверждаю ваше право на дуэль, но просто бандитского убийства не допущу! Господин де Мор, я - капитан Ричард Смолл. Вы согласны дать сатисфакцию полковнику де Таванну?";
			link.l1 = "Один момент, капитан. Я хорошо знал Лулу... и она... была склонна часто менять поклонников, да и здоровье у неё было лучше моего... Как она умерла, полковник? До или после вашего возвращения домой?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog3");
		break;
		
		case "richard_1":
			dialog.text = "Прошу вас, Франсуа, позвольте мне. Месье де Мор, вам бросили вызов. Офицерское общество Блювельда признало, что требование полковником де Таванном сатисфакции оправдано. Принимайте вызов, или потеряете честь.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog5");
		break;
		
		case "richard_2":
			dialog.text = "Шарль, прошу вас как дворянин дворянина. Это же просто некрасиво. Полковник де Таванн гнался за вами через полмира! Скандалом уже пахнет!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog8");
		break;
		
		case "richard_3":
			dialog.text = "Д-да, конечно, мисс. Но я буду...";
			link.l1 = "";
			link.l1.go = "exit";
			CharacterTurnToLoc(npchar, "quest", "helen");
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath1");
		break;
		
		case "richard_4":
			dialog.text = "Капитан де Мор, день - ваш! Не самый достойный бой, но честь свою вы сегодня отстояли.";
			link.l1 = "Вы что-то сказали, капитан? Ещё одну дуэль я, пожалуй, могу сегодня осилить.";
			link.l1.go = "richard_5";
		break;
		
		case "richard_5":
			dialog.text = "Прошу прощения, капитан. Это я от нервов!";
			link.l1 = "Думаю, ваше присутствие здесь более необязательно.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_DuelVictory");
		break;
		
		case "richard_duel":
			dialog.text = "Достойное решение! Пусть и высказанное не самым достойным образом... Господа! Начинаем!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SetupDuel");
		break;
		
		case "alonso":
			dialog.text = "Кэп, я не понимаю половину слов, что эти высочества говорят, но вот у нас ведь как - коли кого назвали трусом, то принято обидчику спуску не давать. Прибейте гадёныша, капитан, а то команда уже волнуется. Люди не оценят, кэп.";
			link.l1 = "Крови так хотите? Жизнь слишком скучна, а подвиги не предвидятся? Будет вам кровь, животные!";
			link.l1.go = "francois_duel";
			link.l2 = "Боюсь, очень боюсь. Всё, господа? У меня очень много дел.";
			link.l2.go = "alonso_refuse";
		break;
		
		case "alonso_1":
			dialog.text = "Кэп, команда ропщет! Дело-то серьёзное: как узнают, что наш кэп хвост поджал, когда его при людях на бой вызывали... Беда будет! А на нас как смотреть будут? Режьте дворяшку уже, мы-то знаем, какой вы мастак саблей махать!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog9");
		break;
		
		case "alonso_refuse":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog6");
		break;
		
		case "francois_refuse":
			dialog.text = "Трус! Бабник, тряпка! Боишься, мерзавец? Вы все это видели?! Ричард, я убью его и так!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog4");
		break;
		
		case "francois_duel":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_SetupDuelDialog");
		break;
		
		case "francois_sit":
			dialog.text = "М-мерзавец! Ничего, к ранениям мне не привыкать - я оклемаюсь и...";
			link.l1 = "Звучит как угроза, полковник. А с угрозами у меня разговор короткий.";
			link.l1.go = "francois_sit_kill";
			link.l2 = "Как оклемаешься - не забудь похвастаться обстоятельствами своего ранения перед офицерским сообществом.";
			link.l2.go = "francois_sit_taunt";
		break;
		
		case "francois_sit_kill":
			DialogExit();
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			notification("Элен не одобряет", "Helena");
			
			AddDialogExitQuestFunction("HelenDrinking_FinishFrancois");
		break;
		
		case "francois_sit_taunt":
			DialogExit();
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
			notification("Элен одобряет", "Helena");
			AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 300);
			AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 300);
			
			AddDialogExitQuestFunction("HelenDrinking_SpareFrancois");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

bool HelenSleep_TalkedToAmelia() {
	if (GetCharacterIndex("Amelia") < 0) {
		return false;
	}
	
	sld = CharacterFromID("Amelia");
	if (sld.dialog.currentnode == "amelia") {
		return false;
	}
	
	return true;
}
