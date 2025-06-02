int questShips[50];
int questShipsNum = 0;

extern void InitGunExt(string id,			
				string sAttr,       
				string sBullet,     
				string sGunPowder,  
				float  DmgMin_NC,   
				float  DmgMax_NC,   
				float  DmgMin_C,    
				float  DmgMax_C,    
				float  EnergyP_NC,  
				float  EnergyP_C,   
				bool   Stun_NC,     
				bool   Stun_C,      
				bool   MultiDamage, 
				int    MisFire,     
				bool   SelfDamage,  
				bool   Explosion,   
				float  Accuracy,    
				int    ChargeSpeed, 
				bool   isDefault );

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp, attr, companion;
	ref chref;
	int iTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	string node = Dialog.CurrentNode;
	if(HasSubStr(node, "joruba_p3_ship_")) {
		iTemp = findsubstr(node, "joruba_p3_ship_", 0);
	 	companion = strcut(node, iTemp + strlen("joruba_p3_ship_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_p3";
	}
	
	if(HasSubStr(node, "joruba_p4_off_")) {
		iTemp = findsubstr(node, "joruba_p4_off_", 0);
	 	pchar.questTemp.ChickenGod.Sacrifice = strcut(node, iTemp + strlen("joruba_p4_off_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_p4_off";
	}

	if(HasSubStr(node, "joruba_o6_off_")) {
		iTemp = findsubstr(node, "joruba_o6_off_", 0);
	 	pchar.questTemp.ChickenGod.Sacrifice = strcut(node, iTemp + strlen("joruba_o6_off_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_o6_off";
	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "Этого вы видеть не должны.";
			link.l1 = "Пойду составлять багрепорт.";
			link.l1.go = "exit";
		break;
		
        case "native":
			dialog.text = "О-ей! Ta'kahi, " + GetSexPhrase("молодой человек","девушка") + "! Не сочтите за грубость, но... как вы сюда попали? Я настоятельно рекомендовал мадам закрыть заведение на время моего пребывания.";
			link.l1 = "Индеец? Здесь?! Тебя-то как пустили, и почему этот бордель ещё не сожгли разгневанные богобоязненные люди?";
			link.l1.go = "native_1";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Panama");
		break;
		
        case "native_1":
			dialog.text = "А зачем им это делать? Моя много тратить денег - меня белый люди любить, ха-ха! Этот 'Свет', может быть, и 'Новый', но порядки в нём старые. Или " + GetSexPhrase("достопочтенный сеньор","достопочтенная сеньорита") + " этого ещё не понял" + GetSexPhrase("","а") + "?";
			link.l1 = "Не надо со мной так разговаривать, красная рожа! Я тут недавно, это правда, хоть и не знаю, как ты это пронюхал. Я могу пристрелить тебя прямо тут, " + GetSexPhrase("и стребовать любую девку на ночь в качестве компенсации за доставленные мне хлопоты!","и дело с концом!") + "";
			link.l1.go = "native_var1";
			link.l2 = "Ха! Для аборигена ты демонстрируешь недюжую наблюдательность и витиевато изъясняешься!";
			link.l2.go = "native_var2";
		break;
		
        case "native_var1":
			dialog.text = "Не хочу расстраивать, капитан, но эта бравада меня не страшит. Я здесь в полной безопасности... пока что. Впрочем, раз уж мы перешли 'на ты', то давай попробуем начать наше знакомство сначала. Выпьем?";
			link.l1 = "Это можно, ты меня заинтересовал.";
			link.l1.go = "native_play";
		break;
		
        case "native_var2":
			dialog.text = "Браво! Всего полминуты, а мы уже 'на ты' и обменялись колкостями. А теперь предлагаю, согласно вашим обычаям, выпить и поговорить о деле.";
			link.l1 = "Это можно, ты меня заинтересовал.";
			link.l1.go = "native_play";
		break;
		
        case "native_play":
			dialog.text = "Учитывая назначение этого заведения, твой комментарий, капитан, меня несколько тревожит! Смотри, в чём дело: я уже почти месяц торчу тут безвылазно, местные девки уже ничем не способны меня удивить, а от скуки и бессмысленности происходящего я готов уже лезть на стену.";
			link.l1 = "Ну, дверь не заперта - бери да уходи. Можешь посетить церковь, ну так, для разнообразия... В которую, правда, тебя даже с деньгами вряд ли пустят.";
			link.l1.go = "native_play_1";
		break;
		
        case "native_play_1":
			dialog.text = "Не так всё просто... Я обязан провести в этом... заведении ещё сутки, согласно моему... pactum.";
			link.l1 = "Звучит ужасно конечно, но сочувствия от меня не дождёшься. Весь бордель со всеми его девками в одном твоём распоряжении на целый месяц - это же мечта!";
			link.l1.go = "native_play_2";
		break;
		
        case "native_play_2":
			dialog.text = "Бойся своих желаний, капитан! Впервые, оставшись наедине со всеми этими скво, я думал точно так же. Но женщины, в любом количестве, последовательности и позах надоели уже через неделю. Одна радость у меня осталась - вино, но сегодня тошнить стало уже и от него.";
			link.l1 = "И что ты хочешь от меня? Разделить с тобой этот тяжкий груз " + GetSexPhrase("вина и девок","") + "?";
			link.l1.go = "native_play_3";
		break;
		
        case "native_play_3":
			dialog.text = "Возможно и хочу. Но сначала предлагаю сыграть! Давай 1000 серебра за карту, а? Заодно и познакомимся! Меня, кстати, Агуэбана зовут.";
			link.l1 = "А меня " + GetFullName(pchar) + ". Давай сыграем.";
			link.l1.go = "native_accept";
			link.l2 = "А меня " + GetFullName(pchar) + ". Тысяча песо? Недурно. Я подумаю, но ничего не обещаю.";
			link.l2.go = "native_decline";
		break;
		
        case "native_play_again":
			dialog.text = "Передумал" + GetSexPhrase("","а") + ", капитан? Играем?";
			link.l1 = "Давай сыграем, это точно будет нескучно.";
			link.l1.go = "native_accept";
			link.l2 = "Нет пока.";
			link.l2.go = "native_decline";
		break;
		
        case "native_decline":
			DialogExit();
			
			NextDiag.CurrentNode = "native_play_again";
		break;
		
        case "native_accept":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1");
		break;
		
        case "native_cards_loss":
			dialog.text = "Спасибо за игру, капитан! Думал, что победа хоть как-то облегчит мою измученную душу, но... Эх. Давай, что ли, прощаться уже. Тебе всё же не следует здесь находиться, а я ... а я возьму графин вина, закроюсь здесь и протяну ещё один, последний день. О боги, если бы я только знал, во что всё это выльется!";
			link.l1 = "И это всё? Ни интересной истории, ничего? Признаться, моё разочарование сильнее горечи утраты целой кучи денег!";
			link.l1.go = "native_cards_loss_1";
		break;
		
        case "native_cards_loss_1":
			dialog.text = "Повторяю, капитан - тебя вообще не должно было тут быть. Но если тебе так интересно, поищи один древний храм на большой земле. И притащи туда с собой побольше tuunich kaane'. Вот, на, держи один!";
			link.l1 = "Камень с дыркой? Как мило, да и место для подарка подходящее. Спасибо, Агуэбана!";
			link.l1.go = "native_cards_loss_2";
		break;
		
        case "native_cards_loss_2":
			dialog.text = "Прощай, капитан.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Game1LossGoAway");
		break;
		
        case "native_cards_win":
			dialog.text = "О-ей! Спасибо, капитан! Жалко денег, но... снова оценить вкус жизни стоит дороже!";
			link.l1 = "Н-да, впервые вижу, как радуются такому разгрому. Кстати, а откуда у тебя столько серебра?";
			link.l1.go = "native_cards_win_1";
		break;
		
        case "native_cards_win_1":
			dialog.text = "Хех! Пусть я всего лишь странный индеец в борделе белых людей, но это всё равно не делает твой вопрос уместным! Что же до игры... у меня ещё остались деньги, дай отыграться, а? Обещаю, дальше будет интереснее!";
			link.l1 = "Чёрт с тобой, давай ещё по одной.";
			link.l1.go = "native_cards_win_2";
		break;
		
        case "native_cards_win_2":
			dialog.text = "Предлагаю поднять риски: играем в кости, 1000 монет за кубик. И вот ещё, давай переместимся наверх: у меня к тебе будет разговор, а здесь слишком много прелестных ушек. Сходи к мадам и оплати комнату, а? Мой кредит, к сожалению, на тебя не распространяется.";
			link.l1 = "Снять комнату? На двоих? Иди-ка ты своей дорогой, Агуэбана. Я в этом больше не участвую!";
			link.l1.go = "native_cards_rematch_decline";
			link.l2 = "А-ать, чем чёрт не шутит! Мне уже даже интересно, как закончится весь этот сюр! Но оружие останется со мной, так что без глупостей, ха-ха! Жди, сейчас все организую!";
			link.l2.go = "native_cards_rematch_accept";
		break;
		
        case "native_cards_rematch_decline":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1WinNoRematch");
		break;
		
        case "native_cards_rematch_accept":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1WinRematch");
		break;
		
        case "native_dice":
			dialog.text = "Ну?";
			link.l1 = "Очень надеюсь, что это всё действительно ради игры в кости! Иначе...";
			link.l1.go = "native_dice_1";
		break;
		
        case "native_dice_1":
			dialog.text = "Не бойся, капитан, меня такие глупости не интересуют! Хотя, если бы ты явил" + GetSexPhrase("ся","ась") + " сюда в первый день... ха-ха! Начнём?";
			link.l1 = "Fortes fortuna adiuvat!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Game2");
		break;
		
        case "native_dice_win":
			dialog.text = "Ой-ей! Хорошо-то как! Поздравляю с победой, капитан.";
			link.l1 = "Может хоть сейчас меня просветишь, что тут происходит?";
			link.l1.go = "native_dice_story";
			link.l2 = "Странный ты, Агуэбана. Знаешь, если я не покину это место прямо сейчас, то моей репутации " + GetSexPhrase("дворянина и просто мужчины","") + " будет нанесён непоправимый ущерб. Давай моё серебро и попрощаемся.";
			link.l2.go = "native_dice_win_not_story";
		break;
		
        case "native_dice_loss":
			dialog.text = "Как же жаль, я рассчитывал закончить день на другой ноте...";
			link.l1 = "Впервые вижу, чтобы победа в этой плебейской игре настолько расстраивала человека. Может, хоть сейчас ты меня просветишь, что тут происходит?";
			link.l1.go = "native_dice_story";
			link.l2 = "А-ать! Иди к чёрту, Агуэбана! С меня хватит!";
			link.l2.go = "native_dice_loss_not_story";
		break;
		
        case "native_dice_story":
			dialog.text = "Насколько смогу. Это не по правилам, но всё же, ты несколько скрасил" + GetSexPhrase("","а") + " мои последние дни... В этом борделе, я хотел сказать.";
			link.l1 = "К чему была эта ремарка?";
			link.l1.go = "native_dice_story_1";
		break;
		
        case "native_dice_story_1":
			dialog.text = "Не важно... Слушай сюда, "+GetSexPhrase("белый человек","белая женщина")+"! Я - великий вождь народа Таино, Агуэбана. Иногда мне снится, что я родился на сто лет раньше и изгнал захватчиков-испанцев со своих островов! И что мне поклоняются как богу-заступнику! Но вместо этого я продал три тысячи своих соплеменников на рудники по десять дублонов за голову.";
			link.l1 = "Достойная биография, вождь! Мне что-то резко захотелось пристрелить тебя, Агуэбана, и оставить гнить в этом, пропахшем кислым вином, гадюшнике.";
			link.l1.go = "native_dice_story_2";
		break;
		
        case "native_dice_story_2":
			dialog.text = "Оставь это, капитан. Я всегда хотел только одного - быть как вы.";
			link.l1 = "Как мы?";
			link.l1.go = "native_dice_story_3";
		break;
		
        case "native_dice_story_3":
			dialog.text = "Я видел ваши корабли, эти чудеса человеческого гения, и хотел себе такой же. Видел ваших женщин в тесных корсетах и мечтал о том, как снимаю такой же со своей. Наблюдал, как даже самый вшивый ваш комендант обладает властью, которая даже и не снилась ни одному нашему вождю! Слышал рассказы о Европе и об огромных каменных домах, в которых люди живут вместо того, чтобы выживать. И у меня всё это было! Более того, я даже в Европе побывал - и все за последний год!";
			link.l1 = "Ты перебрал вина, вождь. В Европе ты мог бы побывать только на правах экзотической зверушки для потехи публики. Свой корабль! Женщина в корсете! Не слишком ли ты нафантазировал себе возможности, недоступные тебе в мире белых людей?";
			link.l1.go = "native_dice_story_4";
		break;
		
        case "native_dice_story_4":
			dialog.text = "В вашем мире, капитан, как раз возможно всё! Мне уже это объяснили: стоит лишь захотеть и, пожалуйста, всё будет! И не важно, индеец ты или белый человек.";
			link.l1 = "И кто же был тот умник, что тебе это объяснил? Тебя, судя по всему, пускают не только в бордели, но и в дома для умалишенных!";
			link.l1.go = "native_dice_story_5";
		break;
		
        case "native_dice_story_5":
			dialog.text = "А вот мы и подошли к сути моего рассказа. Знаешь же, как тут устроены дела? За наших трудоспособных мужчин и женщин испанцы с англичанами платят ружьями, инструментами и порохом. Я же брал плату за своих соплеменников в ваших деньгах. Как ты думаешь, почему?";
			link.l1 = "Чувствую, что ты вот-вот меня просветишь.";
			link.l1.go = "native_dice_story_6";
		break;
		
        case "native_dice_story_6":
			dialog.text = "Если ты не можешь жить той жизнью, которой хочешь, то проси богов изменить твою судьбу. В отличие от вашего бога, перед которым нужно извиняться за свои постыдные желания, наши боги могут помочь в их воплощении. Но вот беда: почти все они уже мертвы, да и золото их никогда и не интересовало. Однако, свято место пусто не бывает, и в одной из старых пирамид завелся новый божок. Ему не важно кто ты: местный или европеец, злодей или герой - только плати и всё будет! Все наши племена о нём знают и даже более того, о нём слышали и некоторые ваши люди! Я заплатил и пожил как один из вас. Завтра будет уже ровно год как.";
			link.l1 = "Какой ещё божок? Он что, наколдовал тебе путешествие в Европу и обратно на год, вершиной которого стал месяц в здешнем борделе? Знаешь, всё это звучит как пьяная байка и, пожалуй, я так к ней и отнесусь. Наливай и продолжай свой рассказ.";
			link.l1.go = "native_dice_story_7";
		break;
		
        case "native_dice_story_7":
			dialog.text = "Всё, что я тебе сказал - это истинная правда. А рассказывать мне больше нечего.";
			link.l1 = "Мало ты пожил в нашем мире, Агуэбана. В конце каждой побасенки должна быть мораль, особенно у той, что была рассказана на пьяную голову в борделе. Мы обязательно должны пофилософствовать перед тем, как достойно закончить наш салон.";
			link.l1.go = "native_dice_story_8";
		break;
		
        case "native_dice_story_8":
			dialog.text = "А чем он обычно заканчивается?";
			link.l1 = "Зависит от пола собеседников. С мужчинами обычно дерутся, женщин - ведут в альков. А бывает и, кхм, наоборот. Так в чём мораль твоей побасенки? Что деньги не приносят счастья? Банально!";
			link.l1.go = "native_dice_story_9";
		break;
		
        case "native_dice_story_9":
			dialog.text = "Это не мораль моей, как ты выразил" + GetSexPhrase("ся","ась") + ", басни. Но коль уж начал" + GetSexPhrase("","а") + " говорить про деньги, то я не согласен с твоей сентенцией. Напротив, я верю, что деньги приносят счастье и делают людей лучше.";
			link.l1 = "Да брось! Ты же тогда сам себе и противоречишь - ты нажил огромное состояние, продавая свой народ в рабство. Сколько там вышло? Почти тридцать тысяч золотом?! Ну и погляди на себя теперь, чучело. На счастливчика ты совсем не тянешь.";
			link.l1.go = "native_dice_story_10";
		break;
		
        case "native_dice_story_10":
			dialog.text = "Хорошо, поправляюсь: деньги делают жизнь и людей лучше.";
			link.l1 = "Вот это ближе к истине, но с чего ты решил, что людей-то они делают лучше? Это ты то у нас образец добродетели? А что с теми, у кого мало денег? Мы их запишем в людей нехороших?";
			link.l1.go = "native_dice_story_11";
		break;
		
        case "native_dice_story_11":
			dialog.text = "Мне нравится этот разговор! Хорошо, ещё раз поправляюсь: деньги делают и жизнь, и людей лучше, но только тех, в ком уже сидит зерно добродетели.";
			link.l1 = "Ого, да ты ещё и философ. А в тебе добродетель, получается, не сидела?";
			link.l1.go = "native_dice_story_12";
		break;
		
        case "native_dice_story_12":
			dialog.text = "Ну, я-то был вождем, а власть людей безусловно портит. И вот знаешь, гляжу я на тебя, капитан, и понимаю, что тебя ждёт именно это.";
			link.l1 = "Твой божок наделил тебя ещё и даром провидения? Так тебе надо в Сантьяго, я слышал"+GetSexPhrase("","а")+" там с особенным интересом относятся ко всякого рода медиумам и предсказателям.";
			link.l1.go = "native_dice_story_13";
		break;
		
        case "native_dice_story_13":
			dialog.text = "Так! Давай закончим этот наш, гм, салон без драк и без алькова, пожалуйста! С моралью как-то не очень выходит, так что вместо этого предлагаю тост!";
			link.l1 = "Совсем ты запутался, вождь. Но в одном ты прав. Давай лучше выпьем!";
			link.l1.go = "native_dice_story_14";
		break;
		
        case "native_dice_story_14":
			dialog.text = "За то, чтобы то, что мы хотим - всегда совпадало с тем, что нам нужно! Спасибо, капитан, мне не хватало с кем-то вот так поговорить. Если ты, однажды, захочешь проверить истинность моей истории, то отправляйся на большую землю и найди там древний храм. И собери с собой сто тринадцать tuunich kaane'. У меня осталось девяносто девять - вот, держи их и прощай!";
			link.l1 = "Куча камней с дыркой? Как мило, да и место для подарка подходящее. Спасибо за игру, историю и выпивку, Агуэбана! Может, свидимся ещё!";
			link.l1.go = "native_dice_story_15";
		break;
		
        case "native_dice_story_15":
			dialog.text = "Не свидимся. Попутного ветра тебе, капитан!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_BuyAmulets");
		break;
		
        case "native_dice_win_not_story":
			dialog.text = "Понимаю, капитан. Иди, но сначала послушай! В благодарность или в проклятие, но я дам тебе наводку на сокровище. Всё же, скрасил" + GetSexPhrase("","а") + " мои последние дни... В этом борделе, я хотел сказать. Поищи древний храм на большой земле. И притащи с собой сто тринадцать tuunich kaane'. Вот, держи один.";
			link.l1 = "Камень с дыркой? Как мило, и место для подарка подходящее. Прощай, Агуэбана!";
			link.l1.go = "native_dice_not_story";
		break;
		
        case "native_dice_loss_not_story":
			dialog.text = "Понимаю, ты расстроен" + GetSexPhrase("","а") + ". Но, прежде чем ты уйдёшь, я хочу тебе кое-что сказать. В благодарность или в проклятие, но я дам тебе наводку на сокровище. Всё же, ты несколько скрасил" + GetSexPhrase("","а") + " мои последние дни... В этом борделе, я хотел сказать. Ищи древний храм на большой земле и притащи с собой побольше tuunich kaane'. Вот, держи один.";
			link.l1 = "Камень с дыркой? Как мило, да и место для подарка подходящее. Хватит с меня твоих издевательств!";
			link.l1.go = "native_dice_not_story";
		break;
		
        case "native_dice_not_story":
			dialog.text = "Прощай, капитан.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_NotBuyAmulets");
		break;
		
		case "joruba":
			dialog.text = "Ещё од" + GetSexPhrase("ин","на") + "?! Господи, как вы все мне надоели-то, а!";
			link.l1 = "А-а-а! Сдохни!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_1";
			AddDialogExitQuestFunction("ChickenGod_ShootJoruba");
		break;
		
		case "joruba_1":
			dialog.text = "Ай! Пади ниц, смертн" + GetSexPhrase("ый","ая") + "! Узри же мощь моей пирамиды!";
			link.l1 = "(истошный вопль)";
			link.l1.go = "joruba_2";
			link.l2 = "(убить чудовище)";
			link.l2.go = "joruba_3";
		break;
		
		case "joruba_2":
			dialog.text = "Проняло, а?! То-то же! Добро пожаловать в мою скромную факторию, капитан! Барабанной дроби не будет, не обессудь.";
			link.l1 = "Ч-что ты такое?!";
			link.l1.go = "joruba_4";
		break;
		
		case "joruba_3":
			DialogExit();
			
			NextDiag.CurrentNode = "joruba_3_next";
			AddDialogExitQuestFunction("ChickenGod_ShootJoruba");
		break;
		
		case "joruba_3_next":
			dialog.text = "Хвалю за упорство! Хочешь попробовать ещё разок? 'Третий раз волшебный' - слышал" + GetSexPhrase("","а") + ", так говорят? Но я предлагаю не тратить зазря время, которое, как известно, деньги, и перейти к взаимовыгодной сделке.";
			link.l1 = "Ч-что ты такое?";
			link.l1.go = "joruba_4";
		break;
		
		case "joruba_4":
			dialog.text = "Что я такое не имеет значения, важна функция, которую я выполняю. Конкретно сейчас я провожу торговые сделки с обитателями этой дыры к обоюдной выгоде.";
			link.l1 = "Дыра - это место, где ты сидишь, уж без обид!";
			link.l1.go = "joruba_6";
			
			AddDialogExitQuestFunction("ChickenGod_JorubaToNormal");
		break;
		
		case "joruba_6":
			dialog.text = "Первое и последнее предупреждение, капитан! Но эта пирамида и впрямь тесновата, очевидно я перерос её.";
			link.l1 = "Кхм... ладно, извини, не 'дыра'! А что за сделки, с обоюдной выгодой, о которых ты вначале сказал?";
			if (CheckAttribute(pchar, "questTemp.ChickenGod.SawJoruba")) {
				link.l1.go = "joruba_7A";
			} else {
				link.l1.go = "joruba_7";
			}
		break;
		
		case "joruba_7":
			dialog.text = "О! А это я тебе сейчас очень доходчиво объясню: я даю то, что людям нужно больше всего.";
			link.l1 = "В смысле? Желания, что ли, исполняешь, словно какой-то сказочный джинн?";
			link.l1.go = "joruba_7_1";
		break;
		
		case "joruba_7_1":
			dialog.text = "А ты что, видишь у меня под ногами золотую лампу? Глупости! Я лишь способствую тому, чтобы человек поскорее и максимально приятным способом получил то, за чем он пришёл на этот свет.";
			link.l1 = "Так ты, получается, кто-то вроде ... шамана?";
			link.l1.go = "joruba_8";
		break;
		
		case "joruba_7A":
			dialog.text = "Ты же видел" + GetSexPhrase("","а") + " Агуэбану? Ну так вот.";
			link.l1 = "Этот несчастный, загубленный и пьяный в хлам индеец - твоих рук дело?! И это ты называешь взаимной выгодой?!";
			link.l1.go = "joruba_7A_1";
		break;
		
		case "joruba_7A_1":
			dialog.text = "Не я продал его племя за пару тысяч фунтов золота, не я заливал ему в глотку пойло бочками, и, уж тем более, не я заставил его подцепить все известные и неизвестные в вашем времени болезни от сотен куртизанок. Стать белым аристократом - такова была его просьба. Я лишь только поспособствовал его предназначению.";
			link.l1 = "Че-е-е-го?! В смысле, ты 'поспособствовал'? Ты что... умеешь исполнять желания? Господи, что тут происходит?!";
			link.l1.go = "joruba_7A_2";
		break;
		
		case "joruba_7A_2":
			dialog.text = "Глупости! Я тебе что, джинн из сказок, чтобы исполнять желания? Ты видишь у меня под ногами лампу, а сам я весь синий? Не неси чушь. Я лишь способствую тому, чтобы человек поскорее и максимально приятным способом получил то, за чем он пришёл на этот свет. Вот наш общий знакомый, Агуэбана, должен был спасти свой народ от рудников, а вместо этого, насмотревшись на стянутые корсетом груди дочки коменданта, решил свой народ заложить\nС тех пор в его жизни остался только один смысл - осознать всю глубину своей ошибки, а осознав её - поскорее начать сначала. Год в Европе, цирроз печени и разговор с тобой должны были этому поспособствовать. Однако признаю, отдохнул он на все деньги, ха-ха!";
			link.l1 = "Чего-чего печени? Так, подожди, ты тогда, получается, кто-то вроде... шамана?";
			link.l1.go = "joruba_8";
		break;
		
		case "joruba_8":
			dialog.text = "Не задавай глупых вопросов, капитан. Тебе моё предложение понравится. Более того, в этот раз я буду искренне рад помочь.";
			link.l1 = "Предложение, значит? А давай-ка ты сразу свою цену назовёшь, м?";
			link.l1.go = "joruba_9A";
			link.l2 = "С чего бы это вдруг такая честь?";
			link.l2.go = "joruba_9B";
		break;
		
		case "joruba_9A":
			dialog.text = "Недурно, капитан. Или ты очень ум" + GetSexPhrase("ён","на") + ", или глуп" + GetSexPhrase("","а") + " как пробка, но твои шансы только что сильно выросли. О цене договоримся.";
			link.l1 = "Тебе убить надо кого-то? Я таким не занимаюсь.";
			link.l1.go = "joruba_10";
		break;
		
		case "joruba_9B":
			dialog.text = "Потому что твоё предназначение - наделать дырок в одном моём хорошем знакомом, ха-ха!";
			link.l1 = "Тебе убить надо кого-то? Я таким не занимаюсь.";
			link.l1.go = "joruba_10";
		break;
		
		case "joruba_10":
			dialog.text = "Во-первых, не ври - занимаешься. Во-вторых, разговор у нас пойдёт так: мы проведём с тобой четыре крупных сделки и ещё четыре - поменьше. Каждая успешная сделка сделает тебя значительно сильнее и повысит твои шансы оказаться на верху пищевой цепочки. Если проведём всё, то гарантирую, что однажды ты сможешь выйти на равных биться с богами, а про обычных смертных я вообще умолчу.";
			link.l1 = "Звучит заманчиво! Рассказывай.";
			link.l1.go = "joruba_11";
		break;
		
		case "joruba_11":
			dialog.text = "Я же говорил, что тебе понравится предложение! А вообще ты не робкого десятка, хвалю! К этому моменту, как правило, менее стойкие падают в обморок и приходится уносить их в Блювельд с подозрением на инфаркт, ха-ха! Предложение я тебе уже рассказал, а теперь вот список заданий: небольшие услуги бартерного характера, которые, как я ожидаю, ты сделаешь. В сроках, хе-хе, ты не ограничен" + GetSexPhrase("","а") + ".";
			link.l1 = "Любопытно! Но изучу попозже. Что-то ещё?";
			link.l1.go = "joruba_12";
		break;
		
		case "joruba_12":
			dialog.text = "Сущая мелочь! Осталось провести только первую транзакцию. С тебя, капитан, две тысячи дублонов.";
			link.l1 = "Кхм, мелочь! Ну, допустим... Но это же целая куча золота! Куда тебе столько? Песо не подойдёт?";
			link.l1.go = "joruba_13";
			link.l2 = "Мелочь?! Совсем сдурел? Я на эти деньги могу фрегат купить!";
			link.l2.go = "joruba_insult";
		break;
		
		case "joruba_13":
			dialog.text = "Объясняю. Пирамида нуждается в ремонте, чтобы всякие тут её не называли 'дырой'. Кладка иногда падает на головы посетителей, а сие плохо для коммерции. Мои хоть и латают её каждый день, но срочно нужны вливания извне. Песо я не принимаю - курс скачет постоянно.";
			link.l1 = "Зря ты так про честные песо... Погоди, а что, ты тут не один?";
			link.l1.go = "joruba_14";
		break;
		
		case "joruba_14":
			dialog.text = "Не один. Я так - фасад серьёзной организации. Ну что, соглас" + GetSexPhrase("ен","на") + "?";
			link.l1 = "Я подумаю ещё, но хотелось бы конечно знать, ЧТО я получу за эти немалые деньги!";
			link.l1.go = "joruba_15";
		break;
		
		case "joruba_15":
			dialog.text = "Зачем же портить сюрприз? И потом, относись к этим деньгам, как к налогу. Самое ценное твоё приобретение будет в том, что тебе откроются другие сделки, а награды там... ух, самому жалко отдавать! Да и найти тебе таких наград больше негде, даже не рассчитывай.";
			link.l1 = "Хорошо. А зовут то тебя-то как вообще?";
			link.l1.go = "joruba_16";
		break;
		
		case "joruba_16":
			dialog.text = "Аруба Великолепный. И последнее, " + pchar.name + ", вход в пирамиду - только раз в день. Не задерживай других клиентов и не беспокой меня по пустякам.";
			link.l1 = "Что-то не вижу очереди... До встречи, Ваше Великолепие.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_wait";
			AddDialogExitQuestFunction("ChickenGod_GiveFirstTask");
		break;
		
		case "joruba_wait":
			dialog.text = "Ахой, капитан. С чем приш" + GetSexPhrase("ёл","ла") + "?";
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p1") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p1.Completed") && PCharDublonsTotal() >= 2000) {
				link.p1 = "Вот твои дублоны. А-ать, как же тяжело таскать это проклятый металл... но ещё тяжелее его отдавать!";
				link.p1.go = "joruba_p1";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p2") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p2.Completed") && GetCharacterItem(pchar, "cannabis7") >= 15) {
				link.p2 = "Я выполнил" + GetSexPhrase("","а") + " свою часть сделки. Вот твоя трава, Аруба.";
				link.p2.go = "joruba_p2";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p3") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p3.Completed") && ChickenGod_FindQuestShips()) {
				for (i = 0; i < questShipsNum; i++) {
					sTemp = "p3_" + (i + 1);
				
					chref = GetCharacter(questShips[i]);
					sld = GetRealShip(sti(chref.ship.type));
					link.(sTemp) = "Ахой, Аруба! Забирай, " + GetStrSmallRegister(XI_ConvertString(sld.BaseName)) + " '" + chref.Ship.Name + "'.";
					link.(sTemp).go = "joruba_p3_ship_" + questShips[i];
					if (FindCompanionShips(SHIP_PINK) && sti(pchar.questTemp.ChickenGod.Tasks.Schyot) <= 1 && startHeroType != 4)
					{
						link.(sTemp) = "Ахой, Аруба! Забирай, пинк '" + chref.Ship.Name + "'.";
						link.(sTemp).go = "joruba_p3_PinkOtkaz";
					}
					/*if (FindCompanionShips(SHIP_GALEON_SM))
					{
						link.(sTemp) = "Ахой, Аруба! Забирай, галеон '" + chref.Ship.Name + "'.";
						link.(sTemp).go = "joruba_p3_HolyMercy";
					}*/
				}
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4.Completed")) {
				link.p3 = "Я готов" + GetSexPhrase("","а") + " принести жертву.";
				link.p3.go = "joruba_p4";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Lady") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Completed")) {
				link.o2 = "Я прив" + GetSexPhrase("ёз","езла") + " тебе невесту и проблемы с испанскими властями. Дама прогуливается снаружи, под охраной, и я не отдам её тебе, пока ты не убедишь меня в благородности своих намерений.";
				link.o2.go = "joruba_o2";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o3") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o3.Completed") && GetCharacterFreeItem(pchar, "cirass4") >= 1) {
				link.o3 = "Держи свой доспех, Аруба. Надеюсь, награда того стоит.";
				link.o3.go = "joruba_o3";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o4") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o4.Completed") && GetPrisonerQty() >= 30) {
				link.o4 = "Твои тридцать пленников у меня.";
				link.o4.go = "joruba_o4";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o5") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o5.Completed") && GetCharacterItem(pchar, "talisman11") >= 113) {
				link.p2 = "Я прив" + GetSexPhrase("ёз","езла") + " тебе твой хлам. Вот, сто тринадцать камней, как и просил.";
				link.p2.go = "joruba_o5";
			}
			
			bOk = (PCharDublonsTotal() >= 25000) || (ChickenGod_HaveOfficers());
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.Completed") && bOk) {
				link.p3 = "Я готов" + GetSexPhrase("","а") + " принести тебе жертву, Аруба.";
				link.p3.go = "joruba_o6";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4.Completed")) {
				link.respec = "(Перераспределить характеристики персонажа)";
				link.respec.go = "joruba_respec";
			}
			
			link.exit = "Просто так.";
			link.exit.go = "joruba_wait_1";
			
			NextDiag.TempNode = "joruba_wait";
		break;
		
		case "joruba_wait_1":
			dialog.text = "Тогда в другой раз.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "joruba_p1":
			dialog.text = "Недурно, пойдёт в общее дело. На, вот: эта вещичка одного очень-очень добродетельного вождя Таино тебе пригодится в таскании тяжестей. Ему, хе-хе, пригодилось...";
			link.l1 = "Спасибо. Надеюсь, я об этом не пожалею. Помнится, в прошлый раз ты упоминал о каких-то более выгодных сделках?";
			link.l1.go = "joruba_p1_1";
			link.l2 = "Так, подожди! Я отдал" + GetSexPhrase("","а") + " тебе кучу золота, а взамен получил"+GetSexPhrase("","а")+" этот кусок глины?! Да на рынке и то сделки честнее! Возвращай мне золото, я отказываюсь!";
			link.l2.go = "joruba_insult";
			
			RemoveDublonsFromPCharTotal(2000);
			pchar.questTemp.ChickenGod.Gold = 2000;
			
			pchar.questTemp.ChickenGod.Tasks.p1.Completed = true;
			GiveItem2Character(pchar, "talisman13");
			//Log_info("Вы получили Оберег 'Фигурка Таино'");
			PlaySound("interface\important_item.wav");
		break;
		
		case "joruba_p1_1":
			dialog.text = "А, да. Денег мне теперь, на первое время, хватит. Но зачем эта куча золота, если моё здоровье не позволит нам проводить наши взаимовыгодные операции, смекаешь?";
			link.l1 = "Ты чего, болен?";
			link.l1.go = "joruba_p1_2";
		break;
		
		case "joruba_p1_2":
			dialog.text = "Исключительно душой! Священники сюда более не ходят после того инцидента с инквизицией, так что приходится обращаться к традиционным методам. Мне... то есть, фактории, требуется пятнадцать стеблей мангаросы.";
			if (!ChickenGod_TalkedToAmelia()) {
				link.l1 = "Это трава такая?";
			} else {
				link.l1 = "Мангаросы? А, ну ещё бы, не настойкой на кактусе же лечить душевные раны, хе-хе.";
			}
			link.l1.go = "joruba_p1_3";
		break;
		
		case "joruba_p1_3":
			dialog.text = "Буду честным, трава это редкая и ценности великой. Хорошенько подумай, надо ли оно тебе - годами собирать её по всему архипелагу?";
			link.l1 = "Ничего не обещаю. Жди, не болей, и лучше бы награда в этот раз того стоила.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveSecondTask");
		break;
		
		case "joruba_p2":
			dialog.text = "Отлично, давай её сюда поскорее - у меня выходной на носу. За такую сделку не жалко отдать настоящие сокровища. Вот, узри!\nЭто мачете однажды чуть не раздробило голову имбецилу Канеку, так что оно дорого мне как память. Оружие старое, но верное. Береги его!";
			link.l1 = "Канек? А кто это?";
			link.l1.go = "joruba_p2_1";
			
			TakeNItems(pchar, "cannabis7", -15);
			pchar.questTemp.ChickenGod.Tasks.p2.Completed = true;
			if (pchar.rank >= 21)
			{
				sld = ItemsFromID("machete2");
                sld.Attack = 80.0;
			}
			else
			{
				sld = ItemsFromID("machete2");
                sld.Attack = 60.0;
			}
			GiveItem2Character(pchar, "machete2");
			//Log_info("Вы получили Мачете конкистадора");
			PlaySound("interface\important_item.wav");
			SetAlchemyRecipeKnown("bullet_double");
			SetAlchemyRecipeKnown("grapeshot_double");
			ChickenGod_InitAmmo();
		break;
		
		case "joruba_p2_1":
			dialog.text = "Думаю, ещё познакомитесь. И, надеюсь, ты не из этих напомаженных говнюков, которые брезгуют ручным трудом? Если да, то тебе не повезло, потому что вторая часть награды - это схемы по созданию усиленных зарядов! Здорово, а?";
			if (pchar.HeroParam.HeroType == "HeroType_4") {
				link.l1 = "О, я такое люблю! Но в чём их особенность? Двойной заряд пороха - давно не новость, и я делаю вывод, что ты явно не покидал свою пирамиду со времён вот этого музейного мачете.";
			} else {
				link.l1 = "Вроде же эти рецепты можно выгодно продать, я правильно понял" + GetSexPhrase("","а") + "?";
			}
			link.l1.go = "joruba_p2_2";
		break;
		
		case "joruba_p2_2":
			dialog.text = "Ты не умничай, а дослушай! Забить в ствол две горки пороха и рисковать потерей глаз, ожогами лица и сломанным носом - может любой идиот. Я же предлагаю тебе немного магии: тщательно проверь качество пороха, сделай помол нужной консистенции, положи пулю или картечь, и зашлифуй рубленым дублоном. Бабахнет так, что кираса не спасёт!";
			link.l1 = "Ну, знаешь, для того, кому я притащил" + GetSexPhrase("","а") + " кучу золота, стрелять деньгами - очень в его духе!";
			link.l1.go = "joruba_p2_3";
		break;
		
		case "joruba_p2_3":
			dialog.text = "Как же с вами сложно! Держи ещё эту ручную мортирку, да десяток гранат. Инструкцию по созданию сам" + GetSexPhrase("","а") + " ищи, раз так" + GetSexPhrase("ой","ая") + " умн" + GetSexPhrase("ый","ая") + "!";
			link.l1 = "Спасибо, Ваше Великолепие! А какой следующий контракт?";
			link.l1.go = "joruba_p2_4";
			
			//Log_info("Вы получили Ручную мортирку");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "mortairgun");
			TakeNItems(pchar, "grenade", 10);
		break;
		
		case "joruba_p2_4":
			dialog.text = "Тебе не понравится, он слишком кощунский для моряка. Мне нужен корабль, да не простой корабль, а корабль уникальный, с историей!";
			link.l1 = "С историей, говоришь? Такой же древней, как эта пирамида или мачете?";
			link.l1.go = "joruba_p2_5";
		break;
		
		case "joruba_p2_5":
			dialog.text = "Пошути мне ещё тут! Лучше думай о своей награде - за такое я могу стребовать отмыть эту пирамиду сверху донизу, да ещё и долж"+GetSexPhrase("ен","на")+" окажешься!";
			link.l1 = "Слушай, давай что-то более реалистичное? Ты вообще в курсе, что кораблю нужна пристань или бухта для стоянки? Как, по-твоему, я долж" + GetSexPhrase("ен","на") + " дотащить корабль в пирамиду?!";
			link.l1.go = "joruba_p2_6";
		break;
		
		case "joruba_p2_6":
			dialog.text = "Озеро за пирамидой видел" + GetSexPhrase("","а") + "? То-то. Просто держи нужный корабль в эскадре, а остальное сделают мои люди. Всё, проваливай, очередь задерживаешь.";
			link.l1 = "Ну разумеется. Прощай!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveThirdTask");
		break;
		
		case "joruba_p3":
			sld = GetCharacter(sti(companion));
			pchar.questTemp.ChickenGod.Tasks.p3.ship = sld.ship.type;
			RemoveCharacterCompanion(pchar, sld);
			AddPassenger(pchar, sld, false);
					
			npchar.ship.type = pchar.questTemp.ChickenGod.Tasks.p3.ship;
			SetCharacterShipLocation(npchar, "Temple");
					
			sld = GetRealShip(sti(pchar.questTemp.ChickenGod.Tasks.p3.ship));
					
			dialog.text = "Отлично! Забираю!";
			link.l1 = "Не умничай и гони награду!";
			link.l1.go = "joruba_p3_1";
			switch (sti(sld.BaseType)) {
				case SHIP_MAYFANG:
					dialog.text = "А что с остальными двумя? Не смог" + GetSexPhrase("","ла") + " приберечь для себя? Хе-хе.";
				break;
				
				case SHIP_MIRAGE:
					dialog.text = "А что с остальными двумя? Не смог" + GetSexPhrase("","ла") + " приберечь для себя? Хе-хе.";
				break;
				
				case SHIP_VALCIRIA:
					dialog.text = "А что с остальными двумя? Не смог" + GetSexPhrase("","ла") + " приберечь для себя? Хе-хе.";
				break;
				
				case SHIP_FRIGATE_L:
					dialog.text = "Я впечатлён, что ты не решил" + GetSexPhrase("","а") + " оставить её себе. Вот это я понимаю - корабль с историей. Эх, Вилли... Я правда желал тебе вернуться домой и основать великий банк, как ты и хотел.";
				break;
				
				case SHIP_CORVETTE_QUEST:
					sTemp = "приватир";
					if (isMainCharacterPatented()) {
						sTemp = GetStrSmallRegister(GetAddress_FormTitle(sti(Items[sti(pchar.EquipedPatentId)].Nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur)));
					}
					
					dialog.text = "Вы только посмотрите на него! Вы опозорили свой патент, " + sTemp + "! Забираю.";
				break;
				
				case SHIP_POLACRE_QUEST:
					dialog.text = "Чарли Принц решил избавиться от инкриминирующих его улик в старой пирамиде? Одобряю!";
				break;
				
				case SHIP_ECLIATON:
					dialog.text = "Удачи объяснить начальству потерю флагмана, адмирал. Ой, простите, генерал-губернатор.";
				break;
				
				case SHIP_CURSED_FDM:
					dialog.text = "Ты " + GetSexPhrase("суеверный дурак","суеверная дура") + " или просто дура" + GetSexPhrase("к","") + "? Этому же кораблю цены нет! Не уверен, что такую сделку можно будет назвать честной, ну да ладно.";
				break;
				
				case SHIP_FDM:
					dialog.text = "Ты " + GetSexPhrase("суеверный дурак","суеверная дура") + " или просто дура" + GetSexPhrase("к","") + "? Этому же кораблю цены нет! Не уверен, что такую сделку можно будет назвать честной, ну да ладно.";
				break;
				
				case SHIP_RENOVATED_FDM:
					dialog.text = "Ты " + GetSexPhrase("суеверный дурак","суеверная дура") + " или просто дура" + GetSexPhrase("к","") + "? Этому же кораблю цены нет! Не уверен, что такую сделку можно будет назвать честной, ну да ладно.";
				break;
				
				case SHIP_ELCASADOR:
					dialog.text = "А вот это очень кстати! Люблю кастильцев, знаешь ли. Попользуюсь и верну им.";
				break;
				
				case SHIP_HIMERA:
					dialog.text = "У тебя нет сердца, капитан. От этого корабля воняет предательством. Забираю.";
				break;
				
				case SHIP_PINK:
					if (startHeroType == 4)
					{
						dialog.text = "Корабль этот хоть и правда с историей, но как-то слишком просто... Но твой случай особый, дорогая. Забираю. Хоть молодость вспомню.";
						Achievment_Set("ach_CL_127");
					}
					else 
					{
						dialog.text = "Корабль этот хоть и правда с историей, но как-то слишком просто... Ладно, кэп, ты здорово поработал с теми заказами из моего списка. Забираю. Хоть молодость вспомню.";
					}
				break;
				
				case SHIP_GALEON_SM:
					dialog.text = "А попа ты видел"+GetSexPhrase("","а")+"? Ну, ещё познакомитесь. И лучше бы тебе заготовить побольше двойных зарядов к пистолю. Если не поможет - попробуй осиновый кол.";
				break;
				
				case SHIP_LADYBETH:
					dialog.text = "А попа ты видел"+GetSexPhrase("","а")+"? Ну, ещё познакомитесь. И лучше бы тебе заготовить побольше двойных зарядов к пистолю. Если не поможет - попробуй осиновый кол.";
				break;
			}
		break;
		
		/*case "joruba_p3_HolyMercy":
			dialog.text = "А попа ты видел"+GetSexPhrase("","а")+"?";
			link.l1 = "Какого попа?";
			link.l1.go = "joruba_p3_HolyMercy_2";
		break;
		
		case "joruba_p3_HolyMercy_2":
			dialog.text = "Ну, ещё познакомитесь. И лучше бы тебе заготовить побольше двойных зарядов к пистолю. Если не поможет - попробуй осиновый кол.";
			link.l1 = "...";
			link.l1.go = "joruba_p3_1";
		break;*/
		
		case "joruba_p3_PinkOtkaz":
			dialog.text = "Корабль этот хоть и правда с историей, но как-то слишком просто... Нет уж! У тебя еще целая куча несделанной работы по списку. Как сделаешь - обсудим еще раз.";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "joruba_p3_1":
			dialog.text = "Благословляю тебя, " + GetFullName(pchar) + ". Пусть море будет к тебе благосклонно. А теперь, давай обсудим следующую сделку...";
			link.l1 = "В смысле обсудим следующую сделку? А награда?! Я тебе отдал" + GetSexPhrase("","а") + " полноценный боевой корабль, а взамен ты только покрутил рукой и чёт пробурчал? Я что, похож"+GetSexPhrase("","а")+" на "+GetSexPhrase("впечатлительного дурачка","впечатлительную дурочку")+", котор"+GetSexPhrase("ый","ая")+" на это поведётся?!";
			link.l1.go = "joruba_insult";
			link.l2 = "Погоди со сделкой! Лучше сначала скажи, что скрывается за этим твоим благословением?";
			link.l2.go = "joruba_p3_2";
			
			pchar.questTemp.ChickenGod.Tasks.p3.Completed = true;
		break;
		
		case "joruba_p3_2":
			dialog.text = "Любой твой корабль теперь будет крепче, а корабли твоих врагов - не очень. Ну и бонусом: время в море для тебя будет длиться чуть медленней. Если тебе и этого не хватит, чтобы поставить на колени всю эту дыру, то лучше отправляйся к папаше и требуй возврат!";
			link.l1 = "Ладно, конечно, но если я не замечу этих изменений, то, клянусь, я вернусь сюда ночью и спалю твою пирамиду к чертям! А теперь давай, рассказывай про следующую сделку!";
			link.l1.go = "joruba_p3_3";
			notification("+10% к защите корпуса", "None");
			notification("+10% урон корпуса врагу", "None");
			notification("+5% скорость на глобальной карте", "None");
			PlaySound("Interface\new_level.wav");
		break;
		
		case "joruba_p3_3":
			dialog.text = "Ха-ха, вош" + GetSexPhrase("ёл","ла") + " во вкус?! К несчастью для тебя - я тоже! Как ты думаешь, почему я выбрал местом для своей конторы эту пирамиду?";
			link.l1 = "Думается, потому, что в любом приличном месте тебя бы сожгли?";
			link.l1.go = "joruba_p3_4";
		break;
		
		case "joruba_p3_4":
			dialog.text = "Хе-хе, а вот и нет! Всё просто - лучшие сделки требуют крови. Эта пирамида требует крови. Я требую от тебя крови. Так было заведено, так оно и будет!";
			link.l1 = "Даже не думай, чудовище! Я не стану доставлять тебе жертв для твоих кровожадных ритуалов!";
			link.l1.go = "joruba_p3_5";
		break;
		
		case "joruba_p3_5":
			dialog.text = "Ох, какие мы щепетильные! А, знаешь, скольких убил" + GetSexPhrase("","а") + " ЛИЧНО ты, а? Я тебе даже точно скажу: " + (Statistic_AddValue(pchar, "Solder_s", 0) + Statistic_AddValue(pchar, "Citizen_s", 0) + Statistic_AddValue(pchar, "Warrior_s", 0) + Statistic_AddValue(pchar, "Solder_g", 0) + Statistic_AddValue(pchar, "Citizen_g", 0) + Statistic_AddValue(pchar, "Warrior_g", 0)) + " человек! Безо всяких ритуалов положил" + GetSexPhrase("","а") + " гору народа ради своего честолюбия и жажды богатства! ";
			if (HasSubStr(pchar.model, "Sharle")) {
				dialog.text = dialog.text + "Тот миллион за твоего братца - из-за него уже угроблено людей как на средненькой европейской войнушке! ";
			}
			dialog.text = dialog.text + "Поэтому, даже не заводи со мной морализаторские речи! Но ты только не подумай, будто я тебя сейчас осуждаю, ха-ха! Успех одних всегда будет оплачен трагедиями других, а боги, ха, особенно боги - они будут наблюдать и забирать свою долю!";
			link.l1 = "Я не могу дать тебе ответ прямо сейчас... Мне нужно уйти отсюда и поскорее.";
			link.l1.go = "joruba_p3_6";
		break;
		
		case "joruba_p3_6":
			dialog.text = "Освежить голову? Хорошо, но сначала дослушай. Я дам тебе могущество и полную власть над своим телом и разумом, только приведи мне человека большой ценности. Не статиста, не безликую серую мышь с улиц городов или крысу из вонючих трюмов. Приведи мне человека, который следует за тобой и играет важную роль в твоей трагикомедии.";
			link.l1 = "Моего офицера? Ниже падать некуда, Аруба! Если про это узнают...";
			link.l1.go = "joruba_p3_7";
		break;
		
		case "joruba_p3_7":
			dialog.text = "Этот нюанс я возьму на себя. И не трясись так, наши сделки полностью конфиденциальны! Но погоди возражать, ведь я ещё не рассказал про одну хитрую лазейку!";
			link.l1 = "Что же, мне не обязательно тащить на заклание своих людей?";
			link.l1.go = "joruba_p3_8";
		break;
		
		case "joruba_p3_8":
			dialog.text = "Не-а, но альтернатива тебе не понравится: не хочешь платить кровью - заплатишь золотом. Три тысячи дублонов и чистая совесть. Деньги и не такое могут.";
			link.l1 = "Прощай, Аруба. Я больше не хочу с тобой разговаривать!";
			link.l1.go = "joruba_p3_9";
		break;
		
		case "joruba_p3_9":
			dialog.text = "Ты знаешь, где меня найти.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveFourthTask");
		break;
		
		case "joruba_p4":
			dialog.text = "Давай поскорее, пока испанская инквизиция не явилась. Sangre u oro?";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Золото. Вот твои три тысячи, хотя я не очень понимаю, зачем они тебе нужны.";
				link.l1.go = "joruba_p4_1";
			}
			if (ChickenGod_HaveOfficers()) 
			{
				link.l2 = "Кровь.";
				link.l2.go = "joruba_p4_other";
			}
			link.l3 = "Я передумал"+GetSexPhrase("","а")+".";
			link.l3.go = "exit";
		break;
		
		case "joruba_p4_1":
			dialog.text = "...";
			link.l1 = "Всё? Давай поговорим о моей награде.";
			link.l1.go = "joruba_p4_reward_1";
			RemoveDublonsFromPCharTotal(3000);
			pchar.questTemp.ChickenGod.Gold = sti(pchar.questTemp.ChickenGod.Gold) + 3000;
		break;
		
		case "joruba_p4_other":
			dialog.text = "Да будет так. Назови имя?";
			
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Duran");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Baker");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Folke");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Avendel");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Tonzag");
			if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Longway");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Knippel");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Tichingitu");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Irons");
		break;
		
		case "joruba_p4_off":
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba"))
			{
				dialog.text = "Клод Дюран не офицер, а безжалостный наёмник, так что выбери другую жертву.";
				link.l1 = "";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba") && CheckAttribute(pchar, "questTemp.SKD_DevushkaUbita"))
			{
				Achievment_Set("ach_CL_116");
			}
		
			dialog.text = "Принимаю, сейчас всё организуем. Ты можешь отвернуться.";
			link.l1 = "Нет уж. Я вернусь через час за своей наградой.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_p4_reward";
			ChangeCharacterComplexReputation(pchar, "nobility", -50);
			
			AddDialogExitQuestFunction("ChickenGod_KillOfficer");
		break;
		
		case "joruba_o6_money":
			dialog.text = "Прекрасный выбор. Алтарь отмывать хоть не придётся. Держи зелье - комплимент от моего хорошего друга.";
			link.l1 = "На вкус недурно...";
			link.l1.go = "exit";
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			RemoveDublonsFromPCharTotal(25000);
			pchar.questTemp.ChickenGod.Gold = sti(pchar.questTemp.ChickenGod.Gold) + 25000;
			
			if (sti(pchar.questTemp.ChickenGod.Gold) >= 30000) {
				Achievment_Set("ach_CL_87");
			}
			
			notification("+3 очка P.I.R.A.T.E.S.", "None");
			PlaySound("Interface\new_level.wav");
			pchar.skill.FreeSPECIAL = 3;
			pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices = sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) + 5;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) >= 5) {
				pchar.questTemp.ChickenGod.Tasks.o6.Completed = true;
			}
			
			AddDialogExitQuestFunction("ChickenGod_Respec");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_p4_reward":
			dialog.text = "";
			link.l1 = "Всё? Давай поговорим о моей награде.";
			link.l1.go = "joruba_p4_reward_1";
		break;
		
		case "joruba_p4_reward_1":
			dialog.text = "Обращайся ко мне в любое время, когда захочешь изменить свою судьбу... " + XI_ConvertString(pchar.HeroParam.HeroType) + ".";
			link.l1 = "Но что мне это даст?";
			link.l1.go = "joruba_p4_reward_2";
		break;
		
		case "joruba_p4_reward_2":
			dialog.text = "Власть над собой. Попробуй как-нибудь - тебе понравится. А пока, давай расскажу о следующем контракте. Самом важном!";
			link.l1 = "Не уверен"+GetSexPhrase("","а")+", что оно того стоит!";
			link.l1.go = "joruba_p4_reward_3";
			link.l2 = "Давай уже, не томи!";
			link.l2.go = "joruba_p4_reward_3";
		break;
		
		case "joruba_p4_reward_3":
			dialog.text = "Тебе доступна возможность уже не просто изменить свою судьбу, а встать рядом с гениями и богами нашего времени. Да, сейчас ты можешь сколь угодно менять свое тело и разум, но выше головы ты не прыгнешь никогда, ведь обычный человек не может быть хорош во всём. Я же предлагаю тебе сломать эти рамки.";
			link.l1 = "И во что же мне это обойдётся? Больше крови? Золота?";
			link.l1.go = "joruba_p4_reward_4";
		break;
		
		case "joruba_p4_reward_4":
			dialog.text = "Все верно. Либо ты приносишь мне двадцать пять тысяч золотых монет, либо одного из своих спутников. И на этом больше контрактов не будет.";
			link.l1 = "Я подумаю.";
			link.l1.go = "joruba_p4_reward_5";
		break;
		
		case "joruba_p4_reward_5":
			dialog.text = "Ты знаешь, где меня найти. И обращайся, когда захочешь изменить свою судьбу.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_wait";
			
			pchar.questTemp.ChickenGod.Tasks.p4.Completed = true;
			AddDialogExitQuestFunction("ChickenGod_GiveFifthTask");
		break;
		
		case "joruba_respec":
			dialog.text = "Как пожелаешь.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ChickenGod_Respec");
		break;
		
		case "joruba_o2":
			dialog.text = "Во-первых, ты прив"+GetSexPhrase("ёз","ела")+" мне мою жену. Во-вторых, проблемы с кастильцами у тебя, а не у меня. И в третьих, я её уже забрал. А что касается благородных намерений... посмотри на меня, разве я не образец достойного джентльмена? Тласолтеотль, благослови "+GetSexPhrase("его","её")+", чтобы тоже однажды "+GetSexPhrase("познал настоящую женщину","познала настоящего мужчину")+". Ну, или "+GetSexPhrase("мужчину","женщину")+".";
			link.l1 = "Сгинь и до свидания, Аруба.";
			link.l1.go = "exit";
			
			notification("+ 10 ОЗ, + 10 ОЭ!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(10.0);
			pchar.questTemp.ChickenGod.Tasks.o2.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			sld = CharacterFromID(pchar.questTemp.ChickenGod.Tasks.o2.Lady);
			RemovePassenger(pchar, sld);
			ChangeCharacterAddressGroup(sld, "Temple", "goto", "goto1");
			LAi_SetCitizenTypeNoGroup(sld);
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o3":
			dialog.text = "Недурно, спасибо. Откровенно говоря, он не очень-то мне и нужен, но возможно пару раз да поношу ещё в приличном обществе. Именем Иштар благословляю тебя, иди и греши.";
			link.l1 = "Какое странное чувство...";
			link.l1.go = "exit";
			
			notification("+ 15 ОЗ, + 15 ОЭ!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o3.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			TakeItemFromCharacter(pchar, "cirass4");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o4":
			dialog.text = "Забираю. Чего смотришь? Не думал"+GetSexPhrase("","а")+", что мне тоже нужно набирать смертников себе в экипаж? Не могу же я зайти в таверну и сказать: 'Айда со мной, в заброшенную пирамиду!'. Так что приходится выкручиваться. Баст, благослови "+GetSexPhrase("нашего героя","нашу героиню")+" на дальнейшие подвиги!";
			link.l1 = "Какое странное чувство...";
			link.l1.go = "exit";
			
			notification("+ 15 ОЗ, + 15 ОЭ!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o4.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
			
			AddDialogExitQuestFunction("ChickenGod_RemovePrisoners");
		break;
		
		case "joruba_o5":
			dialog.text = "Ага, спасибо! Надо будет раскидать обратно, а то людишки теряют их постоянно, а клиенты нужны. Фрейя, защити " + GetSexPhrase("этого великого собирателя","эту великую собирательницу") + " камней с дыркой!";
			link.l1 = "Какое странное чувство...";
			link.l1.go = "exit";
			
			TakeNItems(pchar, "talisman11", -113);
			
			notification("+ 15 ОЗ, + 15 ОЭ!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o5.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o6":
			dialog.text = "Давай поскорее, пока испанская инквизиция не явилась. Sangre u oro?";
			
			if (PCharDublonsTotal() >= 25000)
			{
				link.money = "Держи свои желтяки, жадная сволочь.";
				link.money.go = "joruba_o6_money";
			}
			
			if (ChickenGod_HaveOfficers())
			{
				link.blood = "Кровь.";
				link.blood.go = "joruba_o6_blood";
			}
			link.l3 = "Я передумал"+GetSexPhrase("","а")+".";
			link.l3.go = "exit";
		break;
		
		case "joruba_o6_blood":
			dialog.text = "Назови имя?";
			
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Duran");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Baker");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Folke");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Avendel");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Tonzag");
			if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Longway");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Knippel");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Tichingitu");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Irons");
			
			if (!CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.gf")) {
				ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Helena");
				ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Mary");
			}
		break;
		
		case "joruba_o6_off":
			if (pchar.questTemp.ChickenGod.Sacrifice == "Mary" || pchar.questTemp.ChickenGod.Sacrifice == "Helena") {
				pchar.questTemp.ChickenGod.Tasks.o6.gf = true;
				sTemp = "будущей жене";
				sld = CharacterFromID(pchar.questTemp.ChickenGod.Sacrifice);
				if (sld.lastname == pchar.lastname) {
					sTemp = "жене";
				}
				
				dialog.text = "Соблазнительно, конечно, но я сделаю для тебя исключение и не приму твою жертву в этот раз. Я даже не буду говорить об этом твоей " + sTemp + ", хотя стоило бы. Если захочет - сама поймёт, какой же ты гадёныш. А ты запомни - без неё ты никто! Ноль! Пустота! Проваливай и до завтра меня не беспокой.";
				link.l1 = "";
				link.l1.go = "exit";
				
				AddDialogExitQuestFunction("ChickenGod_KickedFromTemple");
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba"))
			{
				dialog.text = "Клод Дюран не офицер, а безжалостный наёмник, так что выбери другую жертву.";
				link.l1 = "";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba") && CheckAttribute(pchar, "questTemp.SKD_DevushkaUbita"))
			{
				Achievment_Set("ach_CL_116");
			}
			
			dialog.text = "Принимаю, сейчас всё организуем. Держи зелье - комплимент от моего хорошего друга.";
			link.l1 = "На вкус недурно...";
			link.l1.go = "joruba_o6_reward";
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			
			ChangeCharacterComplexReputation(pchar, "nobility", -50);
			notification("+3 очка P.I.R.A.T.E.S.", "None");
			PlaySound("Interface\new_level.wav");
			pchar.skill.FreeSPECIAL = 3;
			pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices = sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) + 5;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) >= 5) {
				pchar.questTemp.ChickenGod.Tasks.o6.Completed = true;
			}
			
			AddDialogExitQuestFunction("ChickenGod_KillOfficer");
			AddDialogExitQuestFunction("ChickenGod_Respec");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o6_reward":
			dialog.text = "До следующего раза, капитан.";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.questTemp.ChickenGod.OnExitKick = true;
		break;
		
		case "joruba_final":
			dialog.text = "Ахой-ахой! Боги, наконец-то всё!";
			link.l1 = "А?";
			link.l1.go = "joruba_final_1";
		break;
		
		case "joruba_final_1":
			dialog.text = "Мы здесь закончили, капитан. Сделки закрыты, стороны удовлетворены, возврат не принимается, жалобы можешь писать на имя ближайших губернаторств. Наша контора закрывается и переезжает.";
			link.l1 = "Погоди, Аруба. Я отдал"+GetSexPhrase("","а")+" тебе кучу золота, платил"+GetSexPhrase("","а")+" кровью, приводил"+GetSexPhrase("","а")+" в это гнездо женщин и пленников. Я был"+GetSexPhrase("","а")+" готов к тому, что на Карибах творится чертовщина, которую дома считают пустыми суевериями или, в лучшем случае, колдовством. Но наши с тобой 'контракты' выходят за любые рамки разумного! Объяснись!";
			link.l1.go = "joruba_final_2";
		break;
		
		case "joruba_final_2":
			dialog.text = "А знаешь что? Я расскажу\nМне осточертел этот ваш мир, вот серьёзно. И я хочу отсюда выбраться. Каждый день одно и то же: чёртова пирамида с осыпающимся потолком, ненавистные одинаковые пальмы и бесконечный поток Их Величеств капитанов - каждый со своим, гениальным, желанием! Одно охренительней другого! Хочу! Дай! Сделай! Да, я даю людям, то что им нужно. Suum cuique! Это моё призвание и я им горжусь, но, боги, как же я вас всех уже ненавижу!";
			link.l1 = "А тебя здесь кто-то держит? Выход - он вот там, умник!";
			link.l1.go = "joruba_final_3";
		break;
		
		case "joruba_final_3":
			dialog.text = "Верно, никто не держит. Больше никто. И это благодаря тебе, " + GetSexPhrase("дружище","подруга") + "!";
			link.l1 = "Какая резкая смена настроения. Я ожидал" + GetSexPhrase("","а") + " услышать историю, но пока слышу только бессмысленные разглагольствования какого-то мерзкого божка в затхлой пирамиде!";
			link.l1.go = "joruba_final_4";
		break;
		
		case "joruba_final_4":
			dialog.text = "Ну, позволено же мне выпустить пар иногда, а? Я правда рад, что ты приш" + GetSexPhrase("ёл","ла") + " сюда, ведь благодаря тебе я могу наконец-то покинуть этот мир. Золото, экипаж, снаряжение и корабль, " + GetSexPhrase("дружище","подруга") + ". Помнишь? Знакомо? Это всё, что было мне нужно, и ты мне всё это дал" + GetSexPhrase("","а") + "! А что до остального... наверняка в этом мире найдутся ещё божки и все желающие могут пойти к ним и расшибить свой лоб в надежде на какие-то блага взамен. Но, видишь ли, капитан, из всех нас результат даю только я, ха-ха!";
			link.l1 = "И всё же, это не объясняет твою чудную манеру речи и почти божественные способности. Если ты настолько всемогущ, то мог давно сам себе наколдовать и корабль, и команду, и золото!";
			link.l1.go = "joruba_final_5";
		break;
		
		case "joruba_final_5":
			dialog.text = "А я и наколдовал, как видишь. У всех свои методы.";
			link.l1 = "Но как, чёрт побери?! Кто ты такой?!";
			link.l1.go = "joruba_final_6";
		break;
		
		case "joruba_final_6":
			dialog.text = "Как-как... я просто могу. До встречи в новом мире, " + GetPersonaName() + ". Надеюсь, в этот раз он будет по-настоящему новым! Спасибо тебе и прощай!";
			link.l1 = "Лучше не надо, не хочу более иметь с тобой никаких дел. Прощай, Аруба.";
			link.l1.go = "exit";
			link.l2 = "Ну, тогда до встречи... Надеюсь, будет интересно!";
			link.l2.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_FinalGood");
		break;
		
		case "joruba_insult":
			dialog.text = "Вижу, коммерция у нас не клеится, жаль. Пора тебе покинуть нас, капитан.";
			link.l1 = "Кого это 'нас'? Иди ты на...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Insult");
		break;
		
		case "ChickenGod_TheInquisition_1":
			dialog.text = "Именем испанской инквизиции, назовитесь!";
			link.l1 = "Капитан "+GetFullName(pchar)+". И вправду говорят, никто не ждёт испанскую инквизицию...";
			link.l1.go = "ChickenGod_TheInquisition_2";
		break;
		
		case "ChickenGod_TheInquisition_2":
			dialog.text = "... эта шутка всегда к месту, хоть и привела немало невинных христиан на костёр.";
			link.l1 = "...";
			link.l1.go = "ChickenGod_TheInquisition_3";
		break;
		
		case "ChickenGod_TheInquisition_3":
			dialog.text = "Шучу, капитан. Вы пошутили, и я пошутил. Меня зовут падре Эмилио Боканегра, а эти воины Христа - моя вооружённая охрана.";
			link.l1 = "Чем могу помочь, падре?";
			link.l1.go = "ChickenGod_TheInquisition_4";
		break;
		
		case "ChickenGod_TheInquisition_4":
			dialog.text = "Вам знаком некий сеньор Аруба?";
			link.l1 = "Да, он до недавнего времени жил в этой старой пирамиде.";
			link.l1.go = "ChickenGod_TheInquisition_5";
		break;
		
		case "ChickenGod_TheInquisition_5":
			dialog.text = "Что значит жил? Разве там можно жить? И почему 'до недавнего времени'?";
			link.l1 = "Этот сеньор буквально пару минут назад покинул нас на корабле.";
			link.l1.go = "ChickenGod_TheInquisition_6";
		break;
		
		case "ChickenGod_TheInquisition_6":
			dialog.text = "Откуда вы это знаете? Ближайшая бухта в нескольких днях пути отсюда!";
			link.l1 = "Это озеро, видимо, больше чем кажется. Иных объяснений у меня для вас нет, падре.";
			link.l1.go = "ChickenGod_TheInquisition_7";
		break;
		
		case "ChickenGod_TheInquisition_7":
			dialog.text = "Н-да, удивительные дела творятся на землях Вице-Королевства...";
			link.l1 = "Это земли англичан, падре.";
			link.l1.go = "ChickenGod_TheInquisition_8";
		break;
		
		case "ChickenGod_TheInquisition_8":
			dialog.text = "Пусть еретики и дальше так думают. Мы своё обязательно вернём. Простите меня, " + GetSexPhrase("сын мой","дочь моя") + ", за неуёмные вопросы: Сантьяго поручил мне провести официальное дознание по поводу этой пирамиды... и её бывшего обитателя.";
			link.l1 = "А что, собственно, случилось, падре?";
			link.l1.go = "ChickenGod_TheInquisition_9";
		break;
		
		case "ChickenGod_TheInquisition_9":
			dialog.text = "Поскольку дело, видимо, будет закрыто, я смогу вас развлечь небольшим рассказом\nВидите ли, слухи об этом месте давно расползались по всему Мэйну. Мы получали достоверные донесения о том, что лица, оставившие значительный след в истории этого региона, ранее совершали регулярные визиты сюда\nТем не менее, по-настоящему серьёзное внимание Сантьяго начал уделять этим слухам после инцидента в Панаме\nНекий индеец знатно покуролесил в этом славном городе и даже провёл несколько проповедей философского содержания. К сожалению, жители Панамы сделали из них достаточно поверхностные выводы и убедили сами себя, что в этой пирамиде заключены несметные сокровища и исполняются любые желания\nЕресь чистой воды, конечно же... так что мы вынуждены были открыть делопроизводство в отношении некоторых жителей Панамы и этого индейца Агуэбаны.";
			link.l1 = "Почему власти Панамы не пресекли это?";
			link.l1.go = "ChickenGod_TheInquisition_10";
		break;
		
		case "ChickenGod_TheInquisition_10":
			dialog.text = "Как и всегда в таких случаях, заявляют, что были околдованы. Эту юридическую лазейку можно было бы и прикрыть, допроси мы Агуэбану, но тот успел скоропостижно скончаться.";
			link.l1 = "Как он умер?";
			link.l1.go = "ChickenGod_TheInquisition_11";
		break;
		
		case "ChickenGod_TheInquisition_11":
			dialog.text = "Его погубило пьянство. Впрочем, проблем наших его смерть не решила, поскольку ересь успела пустить свои корни по всему архипелагу, и тысячи людей устремились на своеобразное паломничество к этому древнему храму.";
			link.l1 = "Никогда не видел" + GetSexPhrase("","а") + " здесь толп народа... И что же, вы собирались захватить Арубу и судить его?";
			link.l1.go = "ChickenGod_TheInquisition_12";
		break;
		
		case "ChickenGod_TheInquisition_12":
			dialog.text = "Конечно же нет, " + GetSexPhrase("сын мой","дочь моя") + ". Суд инквизиции суров, но справедлив. Нужно иметь веские основания для судилища. Нет, я собирался только лишь собрать показания сеньора Арубы и передать их в Сантьяго.";
			link.l1 = "Ну, тут вам не повезло.";
			link.l1.go = "ChickenGod_TheInquisition_13";
		break;
		
		case "ChickenGod_TheInquisition_13":
			dialog.text = "Как знать, " + GetSexPhrase("сын мой","дочь моя") + ". На всё воля Божья.";
			link.l1 = "Прощайте, падре.";
			link.l1.go = "ChickenGod_TheInquisition_14";
		break;
		
		case "ChickenGod_TheInquisition_14":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Temple", "reload2", false);
			LAi_SetActorType(npchar);
			//LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "ChickenGod_TheInquisitionLeave", -1);
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition.l1.location = PChar.location;
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition = "ChickenGod_TheInquisitionLeave";
		break;
		
	}
} 

void ChickenGod_InitAmmo() {
	if(LoadSegment("items\initItems.c")) {
		InitGunExt(		 "pistol1", "t3", 	 "bullet_double",               "", 100.0, 300.0,  60.0, 260.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 40, 20, 0);
		InitGunExt( 	 "pistol2", "t2", "grapeshot_double",               "",  60.0, 160.0,  20.0, 100.0,  0.0,  0.0, 0, 1, 1, 0, 1, 1, 40, 20, 0);
		InitGunExt(		 "pistol3", "t2", "grapeshot_double",               "",  80.0, 180.0,  30.0, 110.0,  0.0,  0.0, 0, 1, 1, 2, 1, 1, 40, 20, 0);
		InitGunExt(		 "pistol4", "t3",    "bullet_double",               "",  70.0, 270.0,  30.0, 230.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 35, 30, 0);
		InitGunExt(		 "pistol5", "t3", 	 "bullet_double",               "", 130.0, 330.0,  90.0, 290.0,  0.0,  0.0, 1, 0, 0, 2, 0, 0, 70, 30, 0);
		InitGunExt(		 "pistol6", "t3",    "bullet_double",               "", 100.0, 300.0,  60.0, 260.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 50, 20, 0);
		InitGunExt(		 "pistol8", "t4", "grapeshot_double",               "",  50.0, 100.0,  30.0,  60.0,  5.0,  5.0, 1, 1, 1, 0, 1, 1, 20, 20, 0);
		InitGunExt(		 "pistol9", "t3", 	 "bullet_double",               "", 100.0, 320.0,  80.0, 280.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 40, 30, 0);
		InitGunExt(		 "pistol10", "t3",   "bullet_double",               "", 140.0, 280.0, 100.0, 240.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 45, 30, 0);
		InitGunExt(		 "pistol11", "t3",   "bullet_double",               "",  10.0, 700.0,  10.0, 620.0, 40.0, 30.0, 1, 1, 0, 0, 0, 0, 45,100, 0);
		InitGunExt(		 "pistol12", "t3",   "bullet_double",               "",  80.0, 290.0,  60.0, 240.0,  0.0,  0.0, 1, 0, 0, 0, 0, 0, 45, 20, 0);
		InitGunExt(		 "pistol13", "t3",   "bullet_double",               "", 130.0, 300.0,  90.0, 260.0, 15.0,  0.0, 1, 1, 0, 0, 0, 0, 60, 30, 0);
		InitGunExt(		 "howdah",  "t3", "grapeshot_double",	            "",  50.0, 140.0,  30.0,  70.0,  5.0,  5.0, 1, 1, 1, 0, 0, 1, 50, 30, 0);
		InitGunExt(		 "pistol14", "t3",   "bullet_double",               "", 130.0, 330.0,  90.0, 290.0,  0.0,  0.0, 1, 0, 0, 4, 0, 0, 70, 34, 0); // Дуэльный двухзарядный пистоль cle 1.3
		
		UnloadSegment("items\initItems.c");
	}
	
	CGInitGrapeGunExt(	"pistol2",	"t2",		3,		50,		4.25,	5.0,	3);		// трёхствольный дробовик, двойной заряд
	CGInitGrapeGunExt(	"pistol3",	"t2",		4,		40,		6.0,	5.0,	4);		// тромбон, двойной заряд
	CGInitGrapeGunExt(	"pistol8",	"t4",		4,		110,	5.0,	3.0,	2);		// бландербуз, двойной заряд
	CGInitGrapeGunExt(	"howdah",	"t3",		3,		85,		3.0,	5.5,	2);		// гауда, двойной заряд
	CGInitGrapeGunExt(	"mushket3",	"t2",		3,		60,		6.0,	3.0,	3);		// аркебуза, картечь
	CGInitGrapeGunExt(	"mushket6",	"t3",		3,		90,		4.0,	3.5,	2);		// башенный мушкетон, картечь
}

void CGInitGrapeGunExt(string id, string sAttr, int basedmg, int shards, float width, float height, int dispersion)
{
	ref gun = ItemsFromID(id);
	gun.type.(sAttr).basedmg = basedmg;
	gun.type.(sAttr).shards = shards;
	string sArea = "grapes_area_"+dispersion;
	gun.type.(sAttr).area = XI_ConvertString(sArea);
	gun.type.(sAttr).width = width;
	gun.type.(sAttr).height = height;
}

bool ChickenGod_FindQuestShips() {
	questShipsNum = 0;
	
	for(int i = 1; i < COMPANION_MAX; i++) {
		int index = GetCompanionIndex(pchar, i);
		if (index < 0) {
			continue;
		}
		
		sld = GetCharacter(index);
		int shipIndex = sti(sld.ship.type);
		if (shipIndex == SHIP_NOTUSED) {
			continue;
		}
		
		ref realShip = GetRealShip(shipIndex);
		if (!CheckAttribute(realShip, "QuestShip")) {
			continue;
		}
		
		if (!GetRemovable(sld) || !GetShipRemovable(sld)) {
			continue;
		}
		
		if (CheckAttribute(pchar, "questTemp.HWIC.TakeQuestShip")) {
			if (sti(realShip.BaseType) == SHIP_MAYFANG || sti(realShip.BaseType) == SHIP_MIRAGE || sti(realShip.BaseType) == SHIP_VALCIRIA) {
				continue;
			}
		}
		
		questShips[questShipsNum] = sti(sld.index);
		questShipsNum++;
	}
	
	return (questShipsNum > 0);
}

void ChickenGod_AddOfficerLink(aref link, string prefix, string id) {
	if (GetCharacterIndex(id) < 0) {
		return;
	}
	
	if (!CheckPassengerInCharacter(pchar, id)) {
		return;
	}
	
	if (id == "Mary" && !CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) {
		return;
	}
	
	if (id == "Helena" && !CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
		return;
	}
	
	sld = CharacterFromID(id);
	
	if (!GetRemovable(sld)) {
		return;
	}
	
	link.(id) = GetFullName(sld) + ".";
	link.(id).go = prefix + id;
}

bool ChickenGod_TalkedToAmelia() {
	if (GetCharacterIndex("Amelia") < 0) {
		return false;
	}
	
	sld = CharacterFromID("Amelia");
	if (sld.dialog.currentnode == "amelia") {
		return false;
	}
	
	return true;
}

bool ChickenGod_HaveOfficers() {
	object fakelink;
	
	ChickenGod_AddOfficerLink(&fakelink, "", "Duran");
	ChickenGod_AddOfficerLink(&fakelink, "", "Baker");
	ChickenGod_AddOfficerLink(&fakelink, "", "Folke");
	ChickenGod_AddOfficerLink(&fakelink, "", "Avendel");
	ChickenGod_AddOfficerLink(&fakelink, "", "Tonzag");
	if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(&fakelink, "", "Longway");
	ChickenGod_AddOfficerLink(&fakelink, "", "Knippel");
	ChickenGod_AddOfficerLink(&fakelink, "", "Tichingitu");
	ChickenGod_AddOfficerLink(&fakelink, "", "Irons");
	
	if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.gf")) {
		ChickenGod_AddOfficerLink(&fakelink, "", "Helena");
		ChickenGod_AddOfficerLink(&fakelink, "", "Mary");
	}
	
	return (GetAttributesNum(&fakelink) > 0);
}
