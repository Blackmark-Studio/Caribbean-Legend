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
		
		// =================================================================
		// ================== ЭТАП 1. «ЛОЩИНА ВЛЮБЛЁННЫХ» ==================
		// =================================================================
		case "Mary_1":
			dialog.text = ""+pchar.name+", погляди сюда!";
			link.l1 = "Тише, "+npchar.name+", мы можем быть здесь не одни.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_3");
		break;
		
		case "Mary_2":
			dialog.text = ""+pchar.name+"!";
			link.l1 = ""+npchar.name+"? Ты что, шла за мной по пятам?";
			link.l1.go = "Mary_3";
		break;
		
		case "Mary_3":
			dialog.text = "И, похоже, не напрасно, да! Что тут произошло?";
			link.l1 = "Если бы я знал, "+npchar.name+", если бы я знал...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_3");
		break;
		
		case "Mary_4":
			dialog.text = "Бог ты мой...";
			link.l1 = "Да, бедняжке, похоже, тяжко пришлось перед смертью. Никому не пожелаешь такого конца...";
			link.l1.go = "Mary_5";
		break;
		
		case "Mary_5":
			dialog.text = "А это там кто, её муж? Какого чёрта они сунулись в джунгли?! Неужели не слышали о беглых рабах?";
			link.l1 = "Боюсь, на этот вопрос они ответить уже не смогут...";
			link.l1.go = "Mary_6";
		break;
		
		case "Mary_6":
			dialog.text = "Думаешь, тот, кто это сделал, ещё где-то рядом?";
			link.l1 = "Вполне вероятно. Поэтому, нам с тобой стоит вести себя потише - мы должны увидеть их первыми.";
			link.l1.go = "Mary_7";
		break;
		
		case "Mary_7":
			dialog.text = "Поздно, "+pchar.name+". Похоже, нас уже заметили. Посмотри туда.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_6");
		break;
		
		case "Naemnik_1":
			dialog.text = "Так-так, парни, вы только поглядите. Здесь прямо лощина влюблённых, не иначе, хе-хе. Только двое голубков отдали Богу души, как на их место тут же заявились двое других...";
			if (GetOfficersQuantity(pchar) >= 2)
			{
				link.l1 = "Очень остроумно. Но ты, должно быть, не умеешь считать - в отличие от этих несчастных мы тут вовсе не одни.";
				link.l1.go = "Naemnik_2";
			}
			else
			{
				link.l1 = "Ну, с нами будет чуток посложнее, ты уж мне поверь...";
				link.l1.go = "Naemnik_4";
			}
		break;
		
		case "Naemnik_2":
			dialog.text = "Сказал бы я, что вы поумнее их будете - да это будет безбожной ложью. Даже таким числом вы бы тех ублюдков не одолели. А твою красотку постигла бы судьба этой девки у тебя под ногами...";
			link.l1 = "Ты о беглых рабах? Это один из них? Значит, вы люди Бишопа?";
			link.l1.go = "Naemnik_3";
		break;
		
		case "Naemnik_3":
			dialog.text = "На все вопросы - да. Больше двух дней мы вместе с солдатнёй гоняли их по всему острову. Потом поганцы разделились. Часть отступила в сторону пещеры - за ними последовала стража, остальные - дали дёру к бухте. В результате их засады в полумиле к западу отсюда мы потеряли нескольких ребят, и пока приходили в себя и перегруппировывались, они и развлеклись с этой дурёхой...";
			link.l1 = "...";
			link.l1.go = "Naemnik_7";
		break;
		
		case "Naemnik_4":
			dialog.text = "Не трогай ты свою зубочистку, щегол - не нервируй меня моих и ребят. Посмотрел бы я, как она бы тебе помогла, окажись ты в окружении десятка тех уродов, что мы в бухте положили. Вот, только одному повезло - но это ненадолго... Как только этот ублюдок окажется в руках Бишопа...";
			link.l1 = "Так вы его наёмники?";
			link.l1.go = "Naemnik_5";
		break;
		
		case "Naemnik_5":
			dialog.text = "Ну явно уж не служаки гарнизонные. Если бы не эти тюфяки, мы бы изловили негодяев ещё вчера - и этот олух со своей жёнушкой остались бы живы...";
			link.l1 = "Значит, это не ваших рук дело...";
			link.l1.go = "Naemnik_6";
		break;
		
		case "Naemnik_6":
			dialog.text = "Ты за кого это нас принимаешь, а? Мы, конечно, не ангелы, но, если нам приспичит, идём в бордель, а не...";
			link.l1 = "...";
			link.l1.go = "Naemnik_6_add";
		break;
		case "Naemnik_6_add":
			StartInstantDialog("WildRose_Naemnik_Rab", "Naemnik_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_7":
			dialog.text = "Он всё врёт, врёт - подлый мерзавец! Не слушайте его, "+GetAddress_Form(NPChar)+"! Мы и пальцем не тронули этих несчастных!";
			link.l1 = "Вот как? И почему мы должны поверить вам, а не ему?";
			link.l1.go = "Naemnik_8";
			link.l2 = "Да? А может, врёшь на самом деле ты? На святошу ты как-то не тянешь.";
			link.l2.go = "Naemnik_9";
		break;
		
		case "Naemnik_8":
			dialog.text = "Ну, подумайте сами, Бога же ради! Мы бежали от этого зверя Бишопа, два дня бегали по сельве, путали следы - чтобы что? Чтобы сейчас надругаться над бедной леди и позволить этим кровопийцам догнать нас?! Да мои друзья еле ноги выволокли на тот пляж, "+GetAddress_Form(NPChar)+"! У нас не было даже сил вести огонь из наших мушкетов, иначе мы не позволили бы этим канальям сделать их чёрное дело... Это всё они, мы видели!..";
			link.l1 = "...";
			link.l1.go = "Naemnik_9_add";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Naemnik_9":
			dialog.text = "Ну, подумайте вы сами, Бога же ради! Мы бежали от этого зверя Бишопа, два дня бегали по сельве, путали следы - чтобы что? Чтобы сейчас надругаться над бедной леди и позволить этим кровопийцам догнать нас?! Да мои друзья еле ноги выволокли на тот пляж, "+GetAddress_Form(NPChar)+"! У нас не было даже сил вести огонь из наших мушкетов, иначе мы не позволили бы этим канальям сделать их чёрное дело... Это всё они, мы видели!..";
			link.l1 = "...";
			link.l1.go = "Naemnik_9_add";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		case "Naemnik_9_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_10", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_10":
			dialog.text = "Заткнись, Каспер, псина ты вшивая!";
			link.l1 = "...";
			link.l1.go = "Naemnik_10_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_Rab"));
		break;
		case "Naemnik_10_add":
			StartInstantDialog("Mary", "Naemnik_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_11":
			dialog.text = "Что ты сказал?!";
			link.l1 = "...";
			link.l1.go = "Naemnik_11_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
		break;
		case "Naemnik_11_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_12":
			dialog.text = "Ты что, дамочка, плохо слышишь? Я сказал ему захлопнуть пасть. Наш Джерри может часами рассказывать небылицы - он в этом ох какой талант! Бишоп хотел отрезать ему язык и заставить сожрать его, но потом пожалел - а зря, чёрт побери!";
			link.l1 = "...";
			link.l1.go = "Naemnik_12_add";
			CharacterTurnByChr(npchar, CharacterFromID("Mary"));
		break;
		case "Naemnik_12_add":
			StartInstantDialog("Mary", "Naemnik_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_13":
			dialog.text = "Но... Ты назвал его Каспером, да...";
			link.l1 = "...";
			link.l1.go = "Naemnik_13_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
		break;
		case "Naemnik_13_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_14":
			dialog.text = "Послушай, парень, объясни своей подружке, что у людей, даже таких как этот недоносок, помимо имени есть ещё и фамилия. Я не раз слышал, что красивые бабы бывают тупыми, как тюк соломы, но чтоб я сдох...";
			link.l1 = "...";
			link.l1.go = "Naemnik_14_add";
			CharacterTurnByChr(npchar, pchar);
		break;
		case "Naemnik_14_add":
			StartInstantDialog("Mary", "Naemnik_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_15":
			dialog.text = "Именно это я тебе сейчас и устрою, да!";
			link.l1 = "Мэри, стой! Я разберусь с этим сам. Убери оружие в ножны. Сейчас же.";
			link.l1.go = "Naemnik_15_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "normal to fight", "1", 2.5);
			DoQuestFunctionDelay("WildRose_Etap1_EscapeSlaves_6_1", 3.0);
		break;
		case "Naemnik_15_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_16":
			dialog.text = "О, да у нас тут благородный джентльмен. Что ж, твоё поведение и впрямь более достойно, чем визги этого слизняка. Он орал громче, чем его несчастная жёнушка - так, что было слышно даже из-за того холма. Признаться, он нам даже подсобил - именно так мы и выследили этих мерзавцев...";
			link.l1 = "Здесь, на карибах, благородство весьма редкое явление. А теперь давайте все выдохнем - нет ничего благородного в том, чтобы отправиться к праотцам здесь и сейчас.";
			link.l1.go = "Naemnik_17";
			link.l2 = "Мерзавцы тут - только вы. Немедленно принеси Мэри извинения, и, возможно, мы обойдёмся без кровопролития.";
			link.l2.go = "Naemnik_22";
		break;
		
		case "Naemnik_17":
			dialog.text = "Трудно не согласиться. Только сначала угомони свою...";
			link.l1 = "Её зовут Мэри Каспер. Я думаю, это многое прояснит.";
			link.l1.go = "Naemnik_18";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;
		
		case "Naemnik_18":
			dialog.text = "Каспер? Она что, его дочь, ха-ха?";
			link.l1 = "Сильно в этом сомневаюсь. Но, надеюсь, теперь у тебя хватит ума взять свои слова обратно.";
			link.l1.go = "Naemnik_19";
		break;
		
		case "Naemnik_19":
			dialog.text = "Обратно? Иначе что? Вызовешь меня на дуэль? Валяй... Если не боишься оставить свою ненаглядную совсем одну, посреди джунглей, хе-хе. Мы с парнями будем о-о-очень рады такому повороту.";
			link.l1 = "Вот вы и показали своё нутро. Не слишком-то хорошо вы притворялись.";
			link.l1.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_22":
			dialog.text = "Ты, мистер, однако, полон противоречий - такой  миролюбивый, и в то же время - хам. Мне, тем не менее, интересно, ч вымаливать прощение у этой рыжей сумасбродки?";
			link.l1 = "Её зовут Мэри Каспер, и если ты прямо сейчас не...";
			link.l1.go = "Naemnik_23";
		break;
		
		case "Naemnik_23":
			dialog.text = "Каспер? Будь я проклят! Джерри, это случайно не твоя дочурка, а? Ха-ха-ха-ха! Ушам своим не верю! Бывает же такое!";
			link.l1 = "А знаешь, как ещё бывает? Такие, как ты - олухи, которые о чести знают только из слухов - ведут себя с дамами так, будто родились в стойле. Впрочем, чему удивляться - когда вместо мозгов труха, манерам взяться неоткуда.";
			link.l1.go = "Naemnik_24";
		break;
		
		case "Naemnik_24":
			dialog.text = "Ба... Какой дерзкий червяк. Скажи-ка, приятель, хороша твоя девка в гамаке?\nВпрочем, я уверен в обратном - и сам с удовольствием в этом убежусь...";
			link.l1 = "Вот вы и выдали себя. Ненадолго же вас хватило. К бою!";
			link.l1.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_bitva":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_7");
		break;
		
		case "Djerry_1":
			dialog.text = "Лихо же вы их отделали, "+GetAddress_Form(NPChar)+", - этих негодяев. Гореть им в аду! Жаль, я не успел вам помочь. Мушкет, который я заприметил по дороге сюда, лежал слишком далеко. Видимо, кто-то из наших потерял его, когда мы уносили ноги. Хотел бы застрелить этого ублюдка Праймера собственноручно.";
			link.l1 = "Видимо, Праймер здорово тебе досаждал, раз ты решил вернуться.";
			link.l1.go = "Djerry_2";
		break;
		
		case "Djerry_2":
			dialog.text = "Ещё как досаждал. Стараниями этой скотины у меня вся спина исполосована. Но хуже всего то, что он мог запретить нам пить воду, когда ему вздумается.";
			link.l1 = "Жаль, ни один из этих подонков не остался в живых. Его можно было бы передать солдатам - которые, уверен, скоро явятся сюда.";
			link.l1.go = "Djerry_3_1";
		break;
		
		case "Djerry_3_1":
			dialog.text = "Я не совсем понимаю, зачем, э-э, "+GetAddress_Form(NPChar)+"...";
			link.l1 = "Ну как же... Комендант выбил бы из него признание, очистив ваши имена - твоё и твоих павших друзей.";
			link.l1.go = "Djerry_4";
		break;
		
		case "Djerry_4":
			dialog.text = "Ага, обязательно, ха-ха. А потом Вильям Бишоп очистит меня от моей же шкуры - рассказывал мне о таком один черномазый с плантации... Бишоп скор на расправу с беглецами - и чёрный ты или белый, значения не имеет.";
			link.l1 = "Боюсь, тебе так или иначе придётся вернуться на плантацию...";
			link.l1.go = "Djerry_5";
			link.l2 = "Значит, добровольно ты на плантацию не вернёшься?";
			link.l2.go = "Djerry_6";
		break;
		
		case "Djerry_5":
			dialog.text = "А вы славный шутник - вам говорили об этом, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Никаких шуток, "+npchar.name+". Думаешь, я оказался здесь случайно? Я отправился в сельву, чтобы разыскать ваш отряд, вернуть на плантацию - ну и подзаработать золотишка. Но остался один ты. За тебя много не выручишь, так что я, быть может, тебя отпущу. Но скажи мне - что ты вообще себе думал? Остался один. Все остальные мертвы. На что ты надеешься, чёрт тебя побери? Прятаться в горах и кустах, пока не словишь пулю, не сгинешь от лихорадки или не станешь кормом для ягуаров?";
			link.l1.go = "Djerry_8";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Djerry_6":
			dialog.text = "А вы славный шутник - вам говорили об этом, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Никаких шуток, +npchar.name+. Думаешь, я оказался здесь случайно? Я отправился в сельву, чтобы разыскать ваш отряд, вернуть на плантацию - ну и подзаработать золотишка. Но остался один ты. За тебя много не выручишь, так что я, быть может, тебя отпущу. Но скажи мне - что ты вообще себе думал? Остался один. Все остальные мертвы. На что ты надеешься, чёрт тебя побери? Прятаться в горах и кустах, пока не словишь пулю, не сгинешь от лихорадки или не станешь кормом для ягуаров?";
			link.l1.go = "Djerry_8";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Djerry_8":
			dialog.text = "Лучше уж так, ей-Богу, "+GetAddress_Form(NPChar)+" - по мне, так это куда лучше, чем сдохнуть от мук, что уготовил для меня Бишоп. Но на самом деле, всё не так уж и плохо - возле мыса Реггед Пойнт припрятана лодка с парусом.";
			link.l1 = "Ближайшие от Барбадоса земли - это Доминика с аборигенами и Тобаго с испанцами. Даже не знаю, что для тебя... хуже.";
			link.l1.go = "Djerry_9";
		break;
		
		case "Djerry_9":
			dialog.text = "Думаю, я рискну с донами - на Тобаго нередко бросают якорь контрабандисты и пираты. О, вижу, вы осуждаете мой выбор, "+GetAddress_Form(NPChar)+". Я честно служил своей стране - но что мне делать, коль скоро она меня отправила в каменоломни?";
			link.l1 = "Не осуждаю, "+npchar.name+". У каждого свой путь. А теперь возьми побольше пороха и пуль - и ступай. Пока сюда не заявились солдаты.";
			link.l1.go = "Djerry_10";
		break;
		
		case "Djerry_10":
			dialog.text = "Благодарю, "+GetAddress_Form(NPChar)+". И вас, юная леди, э-э, Мэри. (кланяется). Мы с вами, конечно, не родственники, но встретить однофамильца в такой, э-э, ситуации... весьма неожиданно и...";
			link.l1 = "...";
			link.l1.go = "Djerry_10_add";
		break;
		case "Djerry_10_add":
			StartInstantDialog("Mary", "Djerry_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Djerry_11":
			dialog.text = "Пожалуй, что так, да. А теперь прощайте, Джерри.";
			link.l1 = "...";
			link.l1.go = "Djerry_12";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_Rab_mushketer"));
		break;
		
		case "Djerry_12":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_9");
		break;
		
		case "Mary_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", ты чем-то встревожена? Уж больно поспешно ты распрощалась со своим однофамильцем.";
			link.l1.go = "Mary_12";
		break;
		
		case "Mary_12":
			dialog.text = "Просто хотелось поскорее избавиться от общества этого человека... Его история шита белыми нитками, да.";
			link.l1 = "О чём ты, дорогая?";
			link.l1.go = "Mary_13";
		break;
		
		case "Mary_13":
			dialog.text = "После того, что я услышала из уст этого прихвостня Бишопа, у меня нет сомнений, что эти бедняги погибли именно от его рук. Но что до этого... Каспера - ты внимательно слушал, что он говорил?";
			link.l1 = "А что тебя не устроило, милая?";
			link.l1.go = "Mary_14";
		break;
		
		case "Mary_14":
			dialog.text = "Он утверждает, что на пляже припрятана лодка. Но с плантации бежало двадцать с лишним человек. Значит, лодка достаточно большая, верно? Джерри - дезертир с флота, он не может не понимать, что управиться в одиночку с большой посудиной ему будет тяжеловато, да...";
			link.l1 = "Ему нужно будет лишь поставить парус и лечь на курс - остальное сделает ветер. Да, он серьёзно рискует, но, наверное, смерть в море и впрямь лучше, чем от руки палача-плантатора.";
			link.l1.go = "Mary_15";
		break;
		
		case "Mary_15":
			dialog.text = "Пусть так. Но я сейчас поняла, что не вяжется и кое-что ещё... С его слов, они с друзьями издали наблюдали за надругательством наёмников над этой несчастной...";
			link.l1 = "Вместо того, чтобы со всех ног бежать к своей лодке... Да, я понял, к чему ты клонишь, "+npchar.name+". Пожалуй, стоит задать мистеру Касперу ещё парочку вопросов...";
			link.l1.go = "Mary_15_add";
		break;
		case "Mary_15_add":
			StartInstantDialog("WildRose_Naemnik_Rab_mushketer", "Mary_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Mary_16":
			dialog.text = "...";
			link.l1 = " Эй, "+npchar.name+", старина! Погоди-ка минуту...";
			link.l1.go = "Mary_17";
		break;
		
		case "Mary_17":
			dialog.text = "...";
			link.l1 = " Вот чёрт!!! Мэри, берегись!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_11");
		break;
		
		case "Mary_21":
			dialog.text = "Мерзкий негодяй! Мы спасли ему жизнь, а он! Что же это выходит, "+pchar.name+"? Получается...";
			link.l1 = "Да, "+npchar.name+", больше не осталось в живых никого, кто знал правду о случившемся...";
			link.l1.go = "Mary_22";
		break;
		
		case "Mary_22":
			dialog.text = "Надо бы убираться отсюда, "+pchar.name+". Если солдаты обнаружат нас здесь, нам придётся туго, да.";
			link.l1 = "Твоя правда, Мэри. Идём...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_15");
		break;
		
		case "Mary_23":
			dialog.text = "Знаешь, "+pchar.name+", после всего этого мне бы хотелось как следует выпить, да.";
			link.l1 = "Возражать не стану, дорогая. Самому охота промочить горло. Давай заглянем в 'Ирландский рогоносец'.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_2");
		break;
		
		case "Barmen_1":
			dialog.text = "Вы уж простите, что разбудил, капитан...";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "Постучал, и на том спасибо. А теперь выкладывай, что тебе от меня нужно?";
				link.l1.go = "Barmen_2";
			}
			else
			{
				link.l1 = "Хорошо, что ты догадался постучать, приятель. Вломись ты сюда просто так, скатился бы уже по лестнице\nЧто уставился? Выкладывай, зачем ты притащил сюда свою тушку?";
				link.l1.go = "Barmen_2";
			}
		break;
		
		case "Barmen_2":
			dialog.text = "Вас желает видеть один из горожан - Льюис Гэрнон. Говорит, у него к вам важный разговор.";
			link.l1 = "Впервые слышу это имя. Надеюсь, у него и вправду что-то важное, чтобы вот так отрывать меня от... дела. Пусть заходит...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_5");
		break;
		
		case "Lewis_1":
			dialog.text = "Здравствуйте, мистер "+pchar.lastname+". Мисс... Каспер.";
			link.l1 = ""+TimeGreeting()+", мистер "+npchar.lastname+". Не припомню, чтобы мы раньше встречались. Откуда же вы нас знаете?";
			link.l1.go = "Lewis_2";
		break;
		
		case "Lewis_2":
			dialog.text = "Не припомните? Ах, понимаю... Моё лицо было перепачкано кровью и пылью, я и сам пришёл в ужас, когда несколько часов назад увидел себя в зеркале...";
			link.l1 = "...";
			link.l1.go = "Lewis_2_add";
		break;
		case "Lewis_2_add":
			StartInstantDialog("Mary", "Lewis_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_3":
			dialog.text = "Вы... вы же тот мужчина, да, мы нашли вас и...";
			link.l1 = "...";
			link.l1.go = "Lewis_3_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_3_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_4":
			dialog.text = "И мою Сьюзен. Мою бедную Сьюзи...";
			link.l1 = "...";
			link.l1.go = "Lewis_4_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_4_add":
			StartInstantDialog("Mary", "Lewis_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_5":
			dialog.text = "Мы думали, что вы погибли. Как и... Она была вашей женой, да?";
			link.l1 = "...";
			link.l1.go = "Lewis_5_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_5_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_6", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_6":
			dialog.text = "Да, мэм. Она была моей женой, а я оцепенел от страха... и не смог ничего сделать. Боже мой, Боже мой...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_8");
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		
		case "Lewis_7":
			dialog.text = "(рыдает) Они избили меня и заставили на это смотреть...";
			link.l1 = "Встаньте, "+GetAddress_Form(NPChar)+". Вы ни в чем не виноваты. Никто не выстоял бы в одиночку против такого количества негодяев.";
			link.l1.go = "Lewis_8";
		break;
		
		case "Lewis_8":
			dialog.text = "Их было так много, так много... Но всё же я...";
			link.l1 = "Но всё же вы уцелели, а убийцы вашей жены горят в аду. Это слабое, но хоть какое-то утешение, мистер "+npchar.lastname+". Однако, я хотел кое-о-чем спросить...";
			link.l1.go = "Lewis_9";
			LAi_ActorAnimation(npchar, "ground_standup", "WildRose_Etap1_City_8_1", 7);
		break;
		
		case "Lewis_9":
			dialog.text = "Да, мистер "+pchar.lastname+"?";
			link.l1 = "Кто это был? Наёмники Бишопа или беглые рабы?";
			link.l1.go = "Lewis_10";
		break;
		
		case "Lewis_10":
			dialog.text = "Это сделали Джерри Каспер и остальные беглецы. Вы зря подумали на Брюса Праймера и его людей.";
			link.l1 = "Наёмников Бишопа?";
			link.l1.go = "Lewis_11";
		break;
		
		case "Lewis_11":
			dialog.text = "Да. Брюс, конечно, был тем ещё проходимцем и делал для Бишопа много грязной работы - но насильником он не был.";
			link.l1 = "Что-то мне так не показалось. Но не буду спорить с вами, "+npchar.name+". Однако, коль скоро вы были в сознании и всё видели, могли бы встать и...";
			link.l1.go = "Lewis_12";
		break;
		
		case "Lewis_12":
			dialog.text = "Простите меня, "+GetAddress_Form(NPChar)+". Можете считать жалким трусом - но я был не мог пошевелиться, так мне было страшно. Когда эти негодяи преградили мне и Сьюзи путь, я ведь сначала завопил что было сил, хотел позвать на помощь.";
			link.l1 = "И они избили вас.";
			link.l1.go = "Lewis_13";
		break;
		
		case "Lewis_13":
			dialog.text = "Джерри врезал мне прикладом мушкета, а потом сказал, что разрежет меня на куски, прямо на глазах у Сьюзен. Мне... мне стыдно в этом признаться, но, кажется, я на пару секунд даже потерял сознание от страха. А они в это время...";
			link.l1 = "Я понял вас, мистер "+npchar.lastname+". В вашем поведении нет ничего постыдного. Подобное способен вынести далеко не каждый. Жаль, что вы не вмешались - однако, сделанного не воротишь. Но я рад, что мы всё же отправили на тот свет одного из убийц вашей жены - пусть ему и почти удалось нас провести.";
			link.l1.go = "Lewis_14";
			link.l2 = "Значит, мы чуть не полегли в бою наёмниками Бишопа - просто потому, что вам было страшно, так? Прекрасная отговорка, "+npchar.name+". Хорошо, что мы вообще, пусть и запоздало, но сумели разобраться в ситуации...";
			link.l2.go = "Lewis_15";
		break;
		
		case "Lewis_14":
			dialog.text = "Да, "+GetAddress_Form(NPChar)+". Я пришёл поблагодарить вас за это. Пусть вы сперва и поверили ему...";
			link.l1 = "Брюс Праймер приложил для этого немало усилий. Ему стоило бы следить за тем, что говорит...";
			link.l1.go = "Lewis_16";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Lewis_15":
			dialog.text = "Да, "+GetAddress_Form(NPChar)+". Я пришёл поблагодарить вас за это. Пусть вы сперва и поверили ему...";
			link.l1 = "Брюс Праймер приложил для этого немало усилий. Ему стоило бы следить за тем, что говорит...";
			link.l1.go = "Lewis_16";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "Lewis_16":
			dialog.text = "Увы, все мы в этот день совершили ошибки... Нам со Сьюзен не следовало отправляться на прогулку в Реггед Пойнт, Брюсу следовало вовремя прикусить язык... А вам не следовало верить Джереми. Но благодаря мисс Каспер справедливость была восстановлена.";
			link.l1 = "...";
			link.l1.go = "Lewis_16_add";
		break;
		case "Lewis_16_add":
			StartInstantDialog("Mary", "Lewis_17", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_17":
			sld = CharacterFromID("WildRose_Lewis");
			dialog.text = "Я догадываюсь, о чем Вы хотите меня спросить, мистер "+sld.lastname+". Но я не имею к этому человеку никакого отношения.";
			link.l1 = "...";
			link.l1.go = "Lewis_17_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_17_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_18":
			dialog.text = "Я знаю, мисс. Я понял это сразу, как вошёл в эту комнату. У него и вас нет ни малейшего сходства. И всё же, Сьюзен... была уверена, что ничто в этом мире не происходит случайно.";
			link.l1 = "...";
			link.l1.go = "Lewis_18_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_18_add":
			StartInstantDialog("Mary", "Lewis_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_19":
			dialog.text = "Ваша жена была права. Я сама убеждалась в этом неоднократно, да. И "+pchar.name+" тоже.";
			link.l1 = "...";
			link.l1.go = "Lewis_19_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_19_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_20":
			dialog.text = "...";
			link.l1 = "Верно. Однако, не думаю, что сейчас время для философских разговоров. Вряд ли это поможет вам, "+npchar.name+". С подобным поможет справиться лишь время.";
			link.l1.go = "Lewis_21";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), pchar);
			CharacterTurnByChr(CharacterFromID("Mary"), pchar);
		break;
		
		case "Lewis_21":
			dialog.text = "Наверное, вы правы, мистер "+pchar.lastname+". Что ж, спасибо вам ещё раз и прощайте. Я буду молиться за вас и мисс Каспер.";
			link.l1 = "Всего доброго, "+npchar.name+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_10");
		break;
		
		case "Mary_31":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "Знаю, милая, я чуть не отпустил на волю ублюдка...";
			link.l1.go = "Mary_32";
		break;
		
		case "Mary_32":
			dialog.text = "Ублюдка по имени Джерри Каспер.";
			link.l1 = "Верно... Постой... ты что, думаешь, что он...";
			link.l1.go = "Mary_33";
		break;
		
		case "Mary_33":
			dialog.text = "Я знаю, что это очень глупо...";
			link.l1 = "Ещё как! А если бы ты носила фамилию Смит или Джонс? Которых по улицам ходит бессчётное количество - и кто-нибудь из них да творит злодеяния... И этот Джерри, гореть ему в адском пламени - может, он и вовсе не Каспер никакой...";
			link.l1.go = "Mary_34";
			link.l2 = "Так и есть, дорогая. Этот чёртов Джерри вообще мог назваться не своей фамилией - вот и всё.";
			link.l2.go = "Mary_35";
		break;
		
		case "Mary_34":
			dialog.text = "И всё же... Я знаю, что ты меня не понимаешь, но просто представь, что думал бы ты, будь у него фамилия "+pchar.lastname+".";
			link.l1 = "Это не одно и то же, Мэри. "+pchar.lastname+" - дворянская фамилия, а...";
			link.l1.go = "Mary_36";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Mary_35":
			dialog.text = "И всё же... Я знаю, что ты меня не понимаешь, но просто представь, что думал бы ты, будь у него фамилия "+pchar.lastname+".";
			link.l1 = "Это не одно и то же, Мэри. "+pchar.lastname+" - дворянская фамилия, а...";
			link.l1.go = "Mary_36";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Mary_36":
			dialog.text = "А Касперы - это так, люди без роду, без племени, да? Наверное, я должна ежедневно возносить хвалу Господу нашему за то, что ты вообще обратил внимание на меня, а не на какую-нибудь напыщенную...";
			link.l1 = ""+npchar.name+", я совсем не это имел в виду - ты ведь это понимаешь. Члены дворянского рода связаны меж собой узами крови - и это далеко не то же самое, что просто быть одной с кем-то фамилии. Которую, к тому же, как я уже сказал, этот самый кто-то мог просто присвоить...";
			link.l1.go = "Mary_37";
		break;
		
		case "Mary_37":
			dialog.text = "Дело не только в этом, "+pchar.name+"...";
			link.l1 = "Милая, у нас был долгий и тяжёлый день. Мы набродили не одну милю по сельве, могли погибнуть... а потом нам даже поспать толком не дали. Нет ничего удивительного в том, что у тебя в голове зародились всякие странные мысли. Нам обоим просто нужно как следует выспаться.";
			link.l1.go = "Mary_38";
		break;
		
		case "Mary_38":
			dialog.text = "Я вовсе не считаю, что это странно, но хорошо... поговорим завтра.";
			link.l1 = "На свежую голову, мы разберёмся во всём быстрее. Ложись, дорогая, нам нужно оставить этот день позади.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_1");
		break;
		
		case "Waitress_1":
			dialog.text = "С вами всё в порядке, "+GetAddress_Form(NPChar)+"? Вид у вас странный, как будто призрака увидели. Может быть, выпьете рому? Или вина? У нас отличный выбор, вам не помешало бы расслабиться.";
			link.l1 = "К чёрту выпивку. Я ищу девушку...";
			link.l1.go = "Waitress_2";
		break;
		
		case "Waitress_2":
			dialog.text = "Так это вы не по адресу, капитан. Здесь таверна, а не бордель. Вот выйдите на улицу, и напротив увидите...";
			link.l1 = "Послушай, мне не до шуток. Я ищу рыжую девушку, в красном камзоле, она вооружена. Зовут Мэри Каспер.";
			link.l1.go = "Waitress_3";
		break;
		
		case "Waitress_3":
			dialog.text = "Ну раз не до шуток, тогда мне нечего вам сказать. Моя смена началась час назад, и никого рыжего в красном камзоле я тут не видела.";
			link.l1 = "Значит, она ушла ночью... Но куда она могла пойти?!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_4");
		break;
		
		case "Mary_41":
			dialog.text = "Доброе утро, любимый! Долго же ты спал...";
			link.l2 = "Ну и заставила же ты меня поволноваться, "+npchar.name+". Больше не исчезай вот так, без предупреждения...";
			link.l2.go = "Mary_43";
			DelLandQuestMark(npchar);
		break;
		
		case "Mary_43":
			dialog.text = "Не хотелось тебя будить. Ну и потом, ты же тоже, бывает, вот так исчезаешь, не сказав ни слова...";
			link.l1 = "И ты решила ответить мне взаимностью?";
			link.l1.go = "Mary_44";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;
		
		case "Mary_44":
			dialog.text = "На самом деле, мне просто было необходимо побыть наедине со своими мыслями, да. Я не хотела, чтобы ты беспокоился.";
			link.l1 = "Тебя что-то тревожит?";
			link.l1.go = "Mary_46";
		break;
		
		case "Mary_46":
			dialog.text = "Наш вчерашний разговор. Про фамилии, кровные узы...";
			link.l1 = "Значит, ты всё-таки обиделась на меня...";
			link.l1.go = "Mary_47";
		break;
		
		case "Mary_47":
			dialog.text = "Вовсе нет, дорогой, я совсем не об этом. Просто я вдруг осознала, что совсем ничего не знаю о своих родных. Вот ты - сын дворянского рода. Ребята на корабле нет-нет да поведают что-то о своих семьях. А мне и рассказать-то нечего - я никогда не знала своих родителей. Чёрт, да я даже не знаю, где родилась...";
			link.l1 = "Разве не на Острове Справедливости?";
			link.l1.go = "Mary_48";
		break;
		
		case "Mary_48":
			dialog.text = "Эрик, человек, что меня вырастил, так и утверждал. Но раз так - почему никто из жителей Острова никогда не рассказывал о моих родителях, даже не упоминал о них? Я как-то спросила об этом Дональда Гринспи, но ничего внятного он не сказал.";
			link.l1 = "Или же не захотел говорить.";
			link.l1.go = "Mary_49";
		break;
		
		case "Mary_49":
			dialog.text = "Вот! И я подумала о том же, да. Знаешь, я раньше жила себе и жила, как-то не особо задаваясь этим вопросом. Но вчера, когда мы столкнулись с этой скотиной Джерри... я спросила себя - а кем был мой отец? Моя мама? Почему мне о них никогда не рассказывали, словно их и не было вовсе? Что, если мой отец был таким же негодяем, как этот Джерри?";
			link.l1 = "Это не имеет никакого значения, "+npchar.name+". Тебя вырастили другие люди - и сделали это достойно.";
			link.l1.go = "Mary_50";
			link.l1 = "Сомневаюсь, что это так. И слабо представляю, какое это имеет значение, учитывая, что раньше ты об этом почему-то не задумывалась.";
			link.l1.go = "Mary_51";
		break;
		
		case "Mary_50":
			dialog.text = "Но для меня это важно, "+pchar.name+", да. Я хочу, я имею право знать, кем были мои родители. Разве ты с этим не с этим не согласен?";
			link.l1 = "Конечно, я согласен, иначе и быть не может. Но если и пытаться узнать что-то о твоих отце и матери, то только на Острове Справедливости. Ведь ты даже не знаешь их имён, так ведь?";
			link.l1.go = "Mary_52";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		case "Mary_51":
			dialog.text = "Но для меня это важно, "+pchar.name+", да. Я хочу, я имею право знать, кем были мои родители. Разве ты с этим не с этим не согласен?";
			link.l1 = "Конечно, я согласен, иначе и быть не может. Но если и пытаться узнать что-то о твоих отце и матери, то только на Острове Справедливости. Ведь ты даже не знаешь их имён, так ведь?";
			link.l1.go = "Mary_52";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "Mary_52":
			dialog.text = "Так и есть, милый. При мне их ни разу не упоминали, да.";
			link.l1 = "Значит, в городские архивы английских колоний нам идти рановато. Сначала придётся вернуться на это корабельное кладбище и пытаться найти какие-то следы твоей родословной там.";
			link.l1.go = "Mary_53";
		break;
		
		case "Mary_53":
			dialog.text = "Я рада, что ты понимаешь меня, "+pchar.name+". Спасибо тебе.";
			link.l1 = ""+npchar.name+", ты меня, право слово, удивляешь. Это меньшее, что я могу для тебя сделать, любимая.";
			link.l1.go = "Mary_54";
		break;
		
		case "Mary_54":
			dialog.text = "Как-то же я прожила почти двадцать лет, ничего о них не зная...";
			// dialog.text = "В конце концов, больше двадцати лет меня это совершенно не волновало...";
			link.l1 = "...";
			link.l1.go = "Mary_55";
		break;
		
		case "Mary_55":
			dialog.text = "Так что я могу потерпеть и ещё какое-то время.";
			link.l1 = "Я вижу, что тебе это важно и нужно, "+npchar.name+". Так что я постараюсь не заставлять тебя ждать. А теперь пойдём, нужно возвращаться на корабль. Там мне за тебя спокойнее, во всяком случае.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_6");
		break;
		
		// ============================================================
		// ================== ЭТАП 2. «ДИТЯ ОСТРОВА» ==================
		// ============================================================
		case "Mary_61":
			dialog.text = "Родные берега... Знаешь, "+pchar.name+", мне кажется, окажись мы тут ещё лет через десять, всё это будет выглядеть точно так же, как и сейчас, да.";
			link.l1 = "Может быть, "+npchar.name+", может быть. Корабли внутреннего кольца останутся на плаву, но люди здесь будут жить уже другие.";
			link.l1.go = "Mary_62";
			link.l2 = "Сильно сомневаюсь - здесь всё уже на честном слове держится. И на гении Механика.";
			link.l2.go = "Mary_63";
		break;
		
		case "Mary_62":
			dialog.text = "А я ведь толком и не помню тех, кто жил на этих корабельных обломках ещё десять-пятнадцать лет назад. Лишь самых близких мне людей - Алана, Эрика...";
			link.l1 = "Наверное, так и должно быть. Нельзя помнить всё и всех. У меня тоже стираются из памяти имена и лица - времён Парижа, не говоря уже о Гаскони. А я думал, такое случается только со стариками.";
			link.l1.go = "Mary_64";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Mary_63":
			dialog.text = "А я ведь толком и не помню тех, кто жил на этих корабельных обломках ещё десять-пятнадцать лет назад. Лишь самых близких мне людей - Алана, Эрика...";
			link.l1 = "Наверное, так и должно быть. Нельзя помнить всё и всех. У меня тоже стираются из памяти имена и лица - времён Парижа, не говоря уже о Гаскони. А я думал, такое случается только со стариками.";
			link.l1.go = "Mary_64";
			AddCharacterExpToSkill(pchar, "Repair", 100);
		break;
		
		case "Mary_64":
			dialog.text = "Но это место... Словно другой мир, да? Представляешь, некоторые из тех, что прибыли сюда не так давно, утверждают, что время здесь течёт чуть ли не в три раза быстрее, чем на Большой земле...";
			link.l1 = "Ха-ха, это сколько ж тебе тогда лет?";
			link.l1.go = "Mary_65";
		break;
		
		case "Mary_65":
			dialog.text = "Я вообще-то серьёзно говорила, "+pchar.name+", да!";
			link.l1 = "Ну, если серьёзно, то пора заняться делом. Есть ли среди нарвалов кто-нибудь старше Гринспи?";
			link.l1.go = "Mary_66";
		break;
		
		case "Mary_66":
			dialog.text = "М-м, нет, кажется, нет. Но я тебе уже говорила, что он ничего мне не сказал, когда я его об этом спросила.";
			link.l1 = "И тем не менее, других идей относительно того, кто мог бы нам помочь разобраться в событиях двадцатилетней давности, у меня нет. По крайней мере, пока. Так что берём курс на 'Эсмеральду'.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_2");
		break;
		
		case "Schmidt_1":
			dialog.text = "А, "+pchar.name+" и Мэри, какая встреча! Рад видеть вас здесь... в живом виде, хе-хе. За последний месяц у внешнего кольца разбились два или три судна - море нынче чертовски неспокойно. Да, и не ломитесь в закрытую дверь - чего доброго замок сломаете, а мне его потом чинить. Вы же к Дональду собрались?";
			link.l1 = "И тебе доброго дня, приятель. К нему самому. Но, судя по тому, что дверь заперта, он либо перебрался на другое судно, либо не хочет видеть старых друзей.";
			link.l1.go = "Schmidt_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Schmidt_2":
			dialog.text = "Ни то, ни другое, ха-ха. Гринспи сейчас на внешнем кольце, на учениях.";
			link.l1 = "Учениях? В самом деле? Он что, готовится к новой войне с ривадос?";
			link.l1.go = "Schmidt_3";
		break;
		
		case "Schmidt_3":
			dialog.text = "Она так-то и не прекращалась, "+pchar.name+". Просто стычек в последнее время стало гораздо меньше, чем раньше. Но всё равно в таверне у Санчо то и дело кто-нибудь кому-нибудь морду начистит... а иной раз и нож в ход пойдёт.";
			link.l1 = "Хм, кажется, раньше члены кланов в таверне не появлялись.";
			link.l1.go = "Schmidt_4";
		break;
		
		case "Schmidt_4":
			dialog.text = "Ну, кое-что изменилось с момента вашего отбытия с Острова. Дональду и Эдди удаётся держать людей в узде. Пока что. Но кто знает, что случится завтра? Вот старина Донни и затеял всё это...";
			link.l1 = "Я с таким трудом предотвратил бойню на Острове, чтобы вы тут снова в солдатиков играли? И давно он торчит на внешнем кольце?";
			link.l1.go = "Schmidt_5";
			link.l2 = "Учения - дело хорошее, но не навредят ли они и без того шаткому перемирию? И сколько Гринспи уже муштрует ребят?";
			link.l2.go = "Schmidt_6";
		break;
		
		case "Schmidt_5":
			dialog.text = "Третий день как. Должен вернуться завтра до полудня. С таким рвением, как они там мушкеты полощут, к завтрашнему дню стрелять им будет уже нечем! Ха-ха!";
			link.l1 = "...";
			link.l1.go = "Schmidt_5_add";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Schmidt_6":
			dialog.text = "Третий день как. Должен вернуться завтра до полудня. С таким рвением, как они там мушкеты полощут, к завтрашнему дню стрелять им будет уже нечем! Ха-ха!";
			link.l1 = "...";
			link.l1.go = "Schmidt_5_add";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		case "Schmidt_5_add":
			StartInstantDialog("Mary", "Schmidt_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_7":
			dialog.text = "Моя каюта на 'Церес Смити' всё ещё свободна? Или туда успел кто-то заселиться?";
			link.l1 = "...";
			link.l1.go = "Schmidt_7_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
		break;
		case "Schmidt_7_add":
			StartInstantDialog("Schmidt_Clone", "Schmidt_8", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_8":
			dialog.text = "Там всё так же, как и в тот день, когда ты была там крайний раз. Мы даже дверь не отпирали. Замок всё это время, по правде сказать, тоже не чистили и не смазывали. Так что, если вдруг придётся его ломать - только скажите.";
			link.l1 = "...";
			link.l1.go = "Schmidt_8_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
		break;
		case "Schmidt_8_add":
			StartInstantDialog("Mary", "Schmidt_9", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_9":
			dialog.text = "Обязательно. Спасибо, Юрген.";
			link.l1 = "...";
			link.l1.go = "exit";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_3");
			
			//доп
		break;
		
		case "Mary_71":
			dialog.text = "И впрямь всё осталось как прежде. Все вещи на своих местах - будто я никуда отсюда и не уходила... Здесь мы с тобой впервые встретились, "+pchar.name+". Помнишь?";
			link.l1 = "Ещё бы! Ты так отделала тех двоих, что я подумал - как бы и мне не оказаться на их месте!";
			link.l1.go = "Mary_72";
			DelLandQuestMark(npchar);
		break;
		
		case "Mary_72":
			dialog.text = "Всё ведь было совсем не так, да! Ты буквально вырвал меня из лап смерти!";
			link.l1 = "Кажется, та встреча была мне предназначена самой судьбой.";
			link.l1.go = "Mary_73";
		break;
		
		case "Mary_73":
			dialog.text = "Ты правда так думаешь, дорогой?";
			link.l1 = "Конечно, любимая. И с тех пор я каждый день благодарю её за то, что она занесла меня прямо на 'Церес Смити'.";
			link.l1.go = "Mary_74";
		break;
		
		case "Mary_74":
			dialog.text = ""+pchar.name+"... Скажи, что ты подумал, когда увидел меня в первый раз?";
			link.l1 = "Ну... Я помню только, что, когда это случилось, сердце как будто пыталось вырваться из груди. Ты была такая...";
			link.l1.go = "Mary_75";
		break;
		
		case "Mary_75":
			dialog.text = "Какая?";
			link.l1 = "Не похожая ни на одну из тех, кого я знал раньше. Твоя грация, голос... и этот красный камзол. У меня не было ни единого шанса устоять перед тобой. Признаюсь, мне всегда было интересно: почему именно он? Почему красный камзол, а не платье, не рубашка или корсет?";
			link.l1.go = "Mary_76";
		break;
		
		case "Mary_76":
			dialog.text = "Я нашла его, когда мне было девять, на внешнем кольце. Тогда я обожала там прогуливаться - исследовать всё новое, находить предметы, которых не было на острове, особенно книги. Мне ужасно захотелось его примерить, но тогда я могла разве что утонуть в нём. Я спрятала его там, где и все остальные свои находки - в одном из вороньих гнёзд, торчащих из воды.";
			link.l1 = "И когда он стал тебе в пору, ты вспомнила о нём?";
			link.l1.go = "Mary_77";
		break;
		
		case "Mary_77":
			dialog.text = "Несколько лет назад, бродя по кольцу, я наткнулась на книгу о бравом капитане в красном мундире. Он ничего не боялся, сражался с сотнями врагов ради любви всей своей жизни и не знал страха. Вот тогда я впервые его примерила. Он придаёт мне уверенности...";
			link.l1 = "И неповторимый шарм, дорогая! Но знаешь что? Прямо сейчас я хочу только одного... снять его с тебя...";
			link.l1.go = "Mary_78";
		break;
		
		case "Mary_78":
			dialog.text = "Тогда чего же ты ждёшь, мой бравый капитан?";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_5");
		break;
		
		case "Mary_81":
			dialog.text = "Доброе утро, дорогой. Нарвалы только что вернулись на 'Эсмеральду' и 'Сан-Габриэль', и Дональд с ними. Я видела его в одной из шлюпок, да.";
			link.l1 = "Доброе, доброе... Признаться, после такой ночи я бы спал до полудня, а ты уже на ногах, порхаешь.";
			link.l1.go = "Mary_82";
		break;
		
		case "Mary_82":
			dialog.text = "Вчера мы говорили о камзоле и о вороньем гнезде, где я его когда-то прятала... И вдруг так нахлынула тоска по тем временам, когда я пряталась там ото всех, чтобы в тишине читать книги о большой земле... Я не удержалась и поплыла туда. Раньше я могла сидеть там часами, но сегодня... я просто встретила там рассвет. И поняла: больше всего на свете я хочу быть рядом с тобой.";
			link.l1 = "А я с тобой, "+npchar.name+". Ну, идём  Дональду? Нам будет о чём с поговорить.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_7");
		break;
		
		case "Grinspy_1":
			dialog.text = ""+pchar.name+", Мэри, рад вас видеть! Мне уже доложили о вашем вчерашнем визите. Думал сам заглянуть к вам на 'Церес Смити', но вы опередили старика. Э-эх, мне бы ваши годы...";
			link.l1 = "Ну, у тебя и в свои энергии хоть отбавляй, как мы поняли. Как прошли учения?";
			link.l1.go = "Grinspy_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Grinspy_2":
			dialog.text = "Лучше, чем я ожидал. Отработали высадку на корабли противника, штурм помещений... В общем, поработали на славу. Я, конечно, явно загонял парней, но им это только на пользу. Давненько кости не разминали, ох, давненько, ха-ха.";
			link.l1 = "И что же, позволь поинтересоваться, сподвигло тебя на такие подвиги? Скучно стало на Острове, да?";
			link.l1.go = "Grinspy_3";
		break;
		
		case "Grinspy_3":
			dialog.text = "Хм-м, мне слышится недовольство в твоём голосе, "+pchar.name+". Могу, конечно, понять его причины...";
			link.l1 = "Неужели, "+npchar.name+"?";
			link.l1.go = "Grinspy_4";
		break;
		
		case "Grinspy_4":
			dialog.text = "Тебе немало пришлось побегать по этим гнилым корабельным остовам, чтобы мы тут не перерезали друг друга - я этого не забыл. Никто этого не забыл.";
			link.l1 = "И вот как ты отплатил за мои усилия! Видать, правду говорят - настоящего воина мир лишь тяготит.";
			link.l1.go = "Grinspy_5";
			link.l2 = "И надо сказать, на твоё благоразумие я рассчитывал куда больше, чем на таковое со стороны пиратов или ривадос.";
			link.l2.go = "Grinspy_6";
		break;
		
		case "Grinspy_5":
			dialog.text = "Позволь мне договорить. Да, нам удалось сохранить мир - но наши противоречия никуда не делись. По крайней мере, с черномазыми безбожниками. На прошлой неделе в драке в таверне был убит один из нарвалов. Но и мы в долгу не остались...";
			link.l1 = "Да-да, именно так всё обычно и начинается.";
			link.l1.go = "Grinspy_7";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Grinspy_6":
			dialog.text = "Позволь мне договорить. Да, нам удалось сохранить мир - но наши противоречия никуда не делись. По крайней мере, с черномазыми безбожниками. На прошлой неделе в драке в таверне был убит один из нарвалов. Но и мы в долгу не остались...";
			link.l1 = "Да-да, именно так всё обычно и начинается.";
			link.l1.go = "Grinspy_7";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Grinspy_7":
			dialog.text = "Ты ошибаешься в двух вещах, "+pchar.name+". Во-первых, не начинается, а продолжается. Если ты наивно думал, что положил этому конец, то это не так. А во-вторых, я не святоша, чтобы подставлять другую щёку. Негры вновь распоясались, и мне это не по нраву. Декстеру, кстати, тоже, но он возомнил себя великим политиком и предпочитает держаться над схваткой. Поэтому после некоторых раздумий я избрал, на мой взгляд, наиболее... безболезненный способ сохранить худой мир.";
			link.l1 = "Ты решил припугнуть ривадос своими учениями?";
			link.l1.go = "Grinspy_8";
		break;
		
		case "Grinspy_8":
			dialog.text = "С пару недель назад к внешнему кольцу прибило английский галеон с грузом военного назначения - чего там только не было... Но самое главное - это полсотни новеньких фузей и хороший порох. А ещё шлюпки... На них ещё краска засохнуть не успела! Старые-то совсем прохудились, а после штормов остаётся в целости не так уж много лодок, скажу я тебе...";
			link.l1 = "И всё это стало собственностью нарвалов?";
			link.l1.go = "Grinspy_9";
		break;
		
		case "Grinspy_9":
			dialog.text = "Я, может, и поделился бы с Адмиралом, но коль скоро он считает себя самым умным, я тоже не хочу выглядеть дураком. Мой план, между прочим, сработал, вот так-то.";
			link.l1 = "Чёрный Эдди прислал тебе письмо, в котором обещал больше не сажать на ножи твоих парней?";
			link.l1.go = "Grinspy_10";
		break;
		
		case "Grinspy_10":
			dialog.text = "Чёрный Эдди приказал своим черномазым притихнуть. Я опасался, что в моё отсутствие провокации с их стороны участятся - но всё оказалось ровным счётом наоборот: ривадос сидят смирно и держатся подальше как от моих ребят, так и от мирных жителей, которых они тоже периодически задирали. Негры есть негры - понимают только силу. Так говорил Алан, и пусть эта посудина сию же секунду пойдёт ко дну, если он был неправ!";
			link.l1 = "А если через некоторое время они начнут своевольничать по-новой, ты для острастки обрушишь на 'Фурию' и 'Протектор' свинцовый дождь из своих новых мушкетов?";
			link.l1.go = "Grinspy_11";
		break;
		
		case "Grinspy_11":
			dialog.text = "Идея смелая и дерзкая, но, думаю, до этого не дойдёт. Может, мы лишь сделаем вид, что готовим рейд на их корабли - а дальше Лейтон возьмёт свои ядра в кулак и всё-таки вмешается. Он хоть и зазнался малость, но мужик всё же дальновидный. Уничтожение ни нашего клана, ни негров не в его интересах - три примерно равных центра силы обеспечивают хоть какой-то баланс. Стоит одному из них рухнуть - и всё полетит в тартарары. Он, уверен, это понимает - но почему-то его работу за него приходится выполнять мне.";
			link.l1 = "Я, может, загляну к нему, пока мы будем здесь - если, конечно, он не затеет свои учения в ответ, ха-ха.";
			link.l1.go = "Grinspy_12";
			link.l2 = "Постараюсь зайти к нему при случае - поговорить на этот счёт. Глядишь, и прислушается.";
			link.l2.go = "Grinspy_13";
		break;
		
		case "Grinspy_12":
			dialog.text = "Если кто и сумеет убедить его держать черномазых в узде, так это ты, "+pchar.name+". Однако, по вашим лицам я вижу, что вы пришли не за тем, чтобы поболтать о политике. Выкладывайте, что у вас.";
			link.l1 = "...";
			link.l1.go = "Grinspy_12_add";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		case "Grinspy_12_add":
			StartInstantDialog("Mary", "Grinspy_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_13":
			dialog.text = "Мои родители, Дональд.";
			link.l1 = "...";
			link.l1.go = "Grinspy_13_add";
		break;
		case "Grinspy_13_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_14":
			dialog.text = "Я не совсем понимаю, что хочешь от меня, Мэри.";
			link.l1 = "...";
			link.l1.go = "Grinspy_14_add";
		break;
		case "Grinspy_14_add":
			StartInstantDialog("Mary", "Grinspy_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_15":
			dialog.text = "Расскажи мне о них, прошу тебя, да. Ты ведь знал их! Я когда-то тебя о них уже спрашивала, но ты не стал отвечать на мои вопросы...";
			link.l1 = "...";
			link.l1.go = "Grinspy_15_add";
		break;
		case "Grinspy_15_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_16":
			dialog.text = "И поэтому ты решила притащить сюда Шарля, ха-ха-ха! Ну ты даёшь, девочка, разрази меня гром! Если я и не стал говорить с тобой о твоих отце и матери, то лишь потому что я никогда их не знал, вот и всё!";
			link.l1 = "...";
			link.l1.go = "Grinspy_16_add";
		break;
		case "Grinspy_16_add":
			StartInstantDialog("Mary", "Grinspy_17", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_17":
			dialog.text = "Но ведь ты самый пожилой член нашего клана, да! Ты находился здесь, сколько я себя помню...";
			link.l1 = "...";
			link.l1.go = "Grinspy_17_add";
		break;
		case "Grinspy_17_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_18":
			dialog.text = "Я появился на Острове чуть меньше двадцати лет назад, уже после твоего рождения. Ты была совсем крохой, бегавшей и ползавшей под столами и табуретами и не дававшей никакого покоя Эрику Удетту... Я, конечно, поинтересовался у него, откуда тут взялось такое неугомонное создание - и получил ответ, что ты родилась на Острове несколько лет назад. Он ничего не сказал ни про твоего отца, ни про твою мать. А если и сказал - то я либо не запомнил, либо забыл...";
			link.l1 = "...";
			link.l1.go = "Grinspy_18_add";
		break;
		case "Grinspy_18_add":
			StartInstantDialog("Mary", "Grinspy_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_19":
			dialog.text = "Столько лет прошло... Я понимаю, Дональд, да.";
			link.l1 = "...";
			link.l1.go = "Grinspy_19_add";
		break;
		case "Grinspy_19_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_20":
			dialog.text = "Жаль, что Эрика нет с нами - он-то оказался в этом месте ещё задолго до меня. К слову, когда он рассказывал о твоих очередных выходках, он нередко упоминал Орели Бертин. Эта старушка в тебе души не чаяла, вот это-то я хорошо помню... Я как-то не задавался этим вопросом, но, думаю, когда ты появилась на свет, она уже была на Острове. Может, она сумеет тебе помочь?";
			link.l1 = "...";
			link.l1.go = "Grinspy_20_add";
		break;
		case "Grinspy_20_add":
			StartInstantDialog("Mary", "Grinspy_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_21":
			dialog.text = "Может быть. Хороший повод навестить её - даже не помню, когда заходила к ней последний раз. Нехорошо получилось, да.";
			link.l1 = "...";
			link.l1.go = "Grinspy_21_add";
		break;
		case "Grinspy_21_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_22", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_22":
			dialog.text = "Не думаю, что она на тебя в обиде. Но не напрягайте её слишком сильно - я слышал, она занемогла. Чего доброго ещё...";
			link.l1 = "...";
			link.l1.go = "Grinspy_22_add";
		break;
		case "Grinspy_22_add":
			StartInstantDialog("Mary", "Grinspy_23", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_23":
			dialog.text = "Молчи, Дональд, беду навлечёшь! Орели всех нас переживёт, да.";
			link.l1 = "...";
			link.l1.go = "Grinspy_24";
		break;
		
		case "Grinspy_24":
			dialog.text = "Пойдём, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "Grinspy_24_add";
		break;
		case "Grinspy_24_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_25", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_25":
			dialog.text = "...";
			link.l1 = "Бывай, "+npchar.name+". Скоро увидимся.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_9");
		break;
		
		//
		case "Jillian_1":
			dialog.text = "Господь милосердный, у меня чуть сердце из груди не выпрыгнуло. Разве можно так пугать людей?..";
			link.l1 = "...";
			link.l1.go = "Jillian_1_add";
			DelLandQuestMark(npchar);
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_1_add":
			StartInstantDialog("Mary", "Jillian_2", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_2":
			dialog.text = "Джиллиан! Не ожидала тебя тут увидеть, да. Что ты здесь делаешь? И где Орели?";
			link.l1 = "...";
			link.l1.go = "Jillian_2_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_2_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_3":
			dialog.text = "И тебе привет, Мэри. И вам, "+pchar.name+". Орели больна, ты разве не знала? Я присматриваю за ней по просьбе брата Юлиана. Он передаёт микстуры, которыми я её отпаиваю, но... кажется, они не особо-то и помогают. Сейчас она в каюте, на корме, спит. Я отвела её туда, чтобы убраться здесь.";
			link.l1 = "...";
			link.l1.go = "Jillian_3_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_3_add":
			StartInstantDialog("Mary", "Jillian_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_4":
			dialog.text = "Мы узнали только сегодня, да. Дональд рассказал нам. Как она?";
			link.l1 = "...";
			link.l1.go = "Jillian_4_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_4_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_5":
			dialog.text = "Плохо. Жалуется на слабость в теле, практически не встаёт с постели. Иногда лопочет что-то невнятное, какую-то чушь... Я уже столько историй выслушала о давно минувших временах, что потеряла им счёт.";
			link.l1 = "...";
			link.l1.go = "Jillian_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_5_add":
			StartInstantDialog("Mary", "Jillian_6", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_6":
			dialog.text = "Хм-м, именно за одной такой историей мы как раз и пожаловали. Надеюсь, она не откажется с нами поговорить...";
			link.l1 = "...";
			link.l1.go = "Jillian_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_6_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_7":
			dialog.text = "Это в самом деле так необходимо, Мэри? Не думаю, что её стоит тревожить, в таком состоянии.";
			link.l1 = "...";
			link.l1.go = "Jillian_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_7_add":
			StartInstantDialog("Mary", "Jillian_8", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_8":
			dialog.text = "Это касается моих родителей. Орели могла их знать. Для меня это очень важно, Джиллиан, да.";
			link.l1 = "...";
			link.l1.go = "Jillian_9";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		
		case "Jillian_9":
			dialog.text = "На острове нет лекарства, которое улучшило бы её состояние?";
			link.l1 = "...";
			link.l1.go = "Jillian_9_add";
		break;
		case "Jillian_9_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_10", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_10":
			dialog.text = "Брат Джулиан готовит для неё настойки. Но они помогают лишь на некоторое время. И то, она отказывается их пить, и мне приходится заливать их ей в рот чуть ли не силой. Иногда я боюсь, что она может ими попросту захлебнуться - её ещё нужно заставить всё проглотить...";
			link.l1 = "...";
			link.l1.go = "Jillian_10_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_10_add":
			StartInstantDialog("Mary", "Jillian_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_11":
			dialog.text = "Бедная Орели! Неужели никто на Острове не может ей помочь?";
			link.l1 = "...";
			link.l1.go = "Jillian_11_add";
		break;
		case "Jillian_11_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_12":
			dialog.text = "Сама же знаешь, что толкового лекаря тут нет. Да и чем ты тут поможешь? Старость, как известно, никого не щадит...";
			link.l1 = "...";
			link.l1.go = "Jillian_12_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_12_add":
			StartInstantDialog("Mary", "Jillian_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_13":
			dialog.text = ""+pchar.name+", может, привести кого-нибудь с нашего корабля?";
			link.l1 = "Боюсь, "+npchar.name+", здесь не корабельный хирург нужен, а опытный лекарь.";
			link.l1.go = "Jillian_14";
		break;
		
		case "Jillian_14":
			dialog.text = "Я сейчас готова поверить даже в магию, если это поможет, да.";
			link.l1 = "Хм... Магию? Возможно, стоит обратиться к Чимисету...";
			link.l1.go = "Jillian_14_add";
		break;
		case "Jillian_14_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_15":
			dialog.text = "Чимисету? Колдуну чёрных? "+pchar.name+", вы что, серьёзно?";
			link.l1 = "Как никогда. Чёрный он или белый - последнее, что меня сейчас волнует. Кто ещё может помочь Орели - я не знаю. Думаю, вы тоже. А раз так - отойдите в сторону и не вздумайте мне мешать.";
			link.l1.go = "Jillian_16";
			link.l2 = "Более чем. Орели не помогают ни лекарства, ни молитвы брата Юлиана. Чимисет - наша последняя надежда.";
			link.l2.go = "Jillian_17";
		break;
		
		case "Jillian_16":
			dialog.text = "Ушам своим не верю! Но это же... безбожник!";
			link.l1 = "А это - умирающая женщина, которая в шаге от того, чтобы забыть, как её зовут. Да, он колдун, но я слышал, что они способны на многое, очень на многое. И если он сумеет вернуть ей разум - так ли уж сейчас важно, какой он веры?";
			link.l1.go = "Jillian_18";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddComplexSelfExpToScill(100, 100, 100, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Jillian_17":
			dialog.text = "Ушам своим не верю! Но это же... безбожник!";
			link.l1 = "А это - умирающая женщина, которая в шаге от того, чтобы забыть, как её зовут. Да, он колдун, но я слышал, что они способны на многое, очень на многое. И если он сумеет вернуть ей разум - так ли уж сейчас важно, какой он веры?";
			link.l1.go = "Jillian_18";
			AddCharacterExpToSkill(pchar, "Repair", 100);
		break;
		
		case "Jillian_18":
			dialog.text = ""+pchar.name+", послушайте, мне и самой дорога Орели... Господь свидетель - я делаю всё что в моих силах для облегчения её страданий! Но неужели вы и в самом деле собираетесь позволить чёрному еретику провести в этой каюте свой обряд? А что если в ходе него он спалит корабль, или решит принести кого-нибудь в жертву?";
			link.l1 = "Такого мы не допустим, "+npchar.name+", уверяю вас.";
			link.l1.go = "Jillian_19";
		break;
		
		case "Jillian_19":
			dialog.text = "А я уверяю вас обоих в том, что если об этом кто-то прознает... Вы хоть представляете, что здесь начнётся? Остальным жителям это не понравится, а уж нарвалам - в особенности!";
			link.l1 = "В этом вы правы. Нужно не Чимисета сюда тащить, а отвести Орели к нему.";
			link.l1.go = "Jillian_20";
		break;
		
		case "Jillian_20":
			dialog.text = "Вы не видели её - старуха едва на ногах стоит. Будет чудом, если она не свалится за борт!";
			link.l1 = "Что ж, иногда только на чудо нам и остаётся уповать. Да, и, Джиллиан...";
			link.l1.go = "Jillian_21";
		break;
		
		case "Jillian_21":
			dialog.text = "Что ещё?";
			link.l1 = "Надеюсь, что вы будете об этом молчать. Вы девушка умная, и рассудили всё верно... Волнения на Острове могут легко перерасти в кровопролитие, а никому это ведь не нужно, верно?";
			link.l1.go = "Jillian_22";
			link.l2 = "Никому ни слова, понятно? Мы вам доверились - не заставляйте нас пожалеть об этом. Думаю, вы понимаете, что если наша затея перестанет быть тайной - на Острове начнётся такая резня, какой он ещё не видел.";
			link.l2.go = "Jillian_23";
		break;
		
		case "Jillian_22":
			dialog.text = "Хорошо. Но тогда сделайте так, чтобы никто не видел, как вы тащите её на 'Протектор'... Иначе мне придётся отвечать на неудобные вопросы.";
			link.l1 = "Мы избавим вас от необходимости давать неудобные ответы. Сделаем это ночью.";
			link.l1.go = "Jillian_24";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Jillian_23":
			dialog.text = "Хорошо. Но тогда сделайте так, чтобы никто не видел, как вы тащите её на 'Протектор'... Иначе мне придётся отвечать на неудобные вопросы.";
			link.l1 = "Этого мы не допустим. Сделаем это ночью.";
			link.l1.go = "Jillian_24";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddComplexSelfExpToScill(100, 100, 100, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Jillian_24":
			dialog.text = "Приходите после полуночи. Она будет здесь. И Бога ради, будьте осторожны.";
			link.l1 = "Можете не волноваться, "+npchar.name+", мы будем предельно внимательны.";
			link.l1.go = "Jillian_25";
		break;
		
		case "Jillian_25":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_10");
		break;
		
		case "Jillian_26":
			if (GetHour() >= 3 && GetHour() <= 24)
			{
				dialog.text = "Приходите после полуночи. Она будет здесь...";
				link.l1 = "Хорошо.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Jillian_26";
			}
			else
			{
				dialog.text = "Орели готова. Можете вести её.";
				link.l1 = "Отлично. Тогда в путь.";
				link.l1.go = "exit";
				DelLandQuestMark(npchar);
				AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_10_2");
			}
		break;
		
		case "Oreli_1":
			dialog.text = "Молодые люди, а куда... куда мы идём?! Это же корабль ривадос! Где Эрик?!";
			link.l1 = "Эрик подружился с Эдди Блэком, ты разве не знала?";
			link.l1.go = "Oreli_2";
		break;
		
		case "Oreli_2":
			dialog.text = "Что ты такое говоришь, юноша! Да Эрик негров на дух не переносит!";
			link.l1 = "Ничего себе! Вот давай и спросим его, какого дьявола он тут тогда делает!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_11");
		break;
		
		case "Eddy_1":
			dialog.text = "Гляньте-ка, кто к нам пожаловал! "+GetFullName(pchar)+" собственной персоной! Рад приветствовать своего белого брата, ха-ха! Рассказывай, зачем пожаловал!";
			link.l1 = "И тебе привет, "+npchar.name+". Хотел бы я заглянуть просто на кружку рома, но, боюсь, у меня к тебе, а точнее Чимисету, неотложное дело.";
			link.l1.go = "Eddy_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Eddy_2":
			dialog.text = "Мы в неоплатном долгу перед тобой, мой друг. Сделаем всё, что в наших силах.";
			link.l1 = "Хорошо, если так. Потому что надеяться мне больше не на кого.";
			link.l1.go = "Eddy_3";
		break;
		
		case "Eddy_3":
			dialog.text = "С кем из этих дам тебе требуется помощь, "+pchar.name+"?";
			link.l1 = "Не знаю, серьёзно ты или шутишь, "+npchar.name+", но мне не до смеха. Помощь нужна Орели, конечно.";
			link.l1.go = "Eddy_3_add";
		break;
		case "Eddy_3_add":
			StartInstantDialog("LSC_Oreli", "Eddy_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Eddy_4":
			dialog.text = "Эрик! ЭРИК! Покажись, старый шельмец! Что это за выходки?! Немедленно тащи сюда свой тощий зад!";
			link.l1 = "...";
			link.l1.go = "Eddy_4_add";
		break;
		case "Eddy_4_add":
			StartInstantDialog("Eddy", "Eddy_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Eddy_5":
			dialog.text = "Так значит, не врали... Мои люди доносили мне о том, что у этой развалины мозги набекрень. Теперь вижу - правду говорили. Но я не совсем понимаю, что тебе нужно от ривадос...";
			link.l1 = "Позволь мне поговорить с Чимисетом, и ты всё поймёшь...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_12");
		break;
		
		case "Chimset_1":
			dialog.text = "Говори, мой дорогой друг. Я готов внимательно выслушать тебя.";
			link.l1 = "Буду краток, Чимисет. Орели владеет нужной нам с Мэри информацией. Но в силу её состояния, вызванного, если я правильно понимаю, просто-напросто возрастом, мы... не можем как получить от неё эти сведения, так и быть уверенными в том, что они окажутся верными. Я слышал о чудесах, на которые способны как индейские, так и африканские шаманы - поэтому я и пришёл просить тебя о помощи, Чимисет.";
			link.l1.go = "Chimset_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Chimset_2":
			dialog.text = "Я услышал тебя, мой друг. Шаманы обладают силами загадочными и мистическими, зачастую неподвластными и непонятными людям посторонним, даже своим соплеменникам, не говоря уж о белых. Кто-то называет это колдовством, кто-то - чудом. Мы и в самом деле способны на многое - но никому не под силу заставить реку течь вспять... И остановить её - тоже.";
			link.l1 = "Что ты имеешь в виду, Чимисет?";
			link.l1.go = "Chimset_3";
		break;
		
		case "Chimset_3":
			dialog.text = "Я говорю о реке времени, мой друг. Или о реке жизни - как тебе больше угодно. Видишь ли, ты совершенно прав - корень болезни этой несчастной лежит именно в её годах, ни в чём ином.";
			link.l1 = "Я об этом слышал немного. Знаю только, что проблемма это не такая уж и редкая.";
			link.l1.go = "Chimset_4";
		break;
		
		case "Chimset_4":
			dialog.text = "Ты прав. Людей в её годах нередко уносит в долины грёз, а иногда - ужасов. Они возвращаются обратно, чтобы потом уйти туда вновь - не столько по своей воле, сколько из-за неведомых сил, которые их туда утягивают. С течением времени болезнь становится всё сильнее - и вот, человек уже не помнит ни самого себя, ни своих друзей.";
			link.l1 = "Значит, ты ничего не можешь с этим сделать?";
			link.l1.go = "Chimset_5";
		break;
		
		case "Chimset_5":
			dialog.text = "Изгнать болезнь - нет. Такое мне не под силу. Но я могу сделать кое-что другое...";
			link.l1 = "Что именно?";
			link.l1.go = "Chimset_6";
		break;
		
		case "Chimset_6":
			dialog.text = "В момент, когда эта женщина будет в себе, я проведу быстрый ритуал, к которому заранее подготовлюсь...";
			link.l1 = "Он если не остановит, то хотя бы замедлит развитие болезни?";
			link.l1.go = "Chimset_7";
		break;
		
		case "Chimset_7":
			dialog.text = "Не совсем. Он заставит её призвать все свои жизненные силы, чтобы как можно дольше сохранять рассудок.";
			link.l1 = "Как можно дольше - это сколько?";
			link.l1.go = "Chimset_8";
		break;
		
		case "Chimset_8":
			dialog.text = "Это зависит не от ритуала, а от человека. У кого-то хватит сил на неделю, у кого-то - на месяц... Я слышал о мужчине, который прожил в здравом уме и твёрдой памяти чуть ли не больше года... И, когда все уже успели подумать, что он был излечен, болезнь вновь вернулась - и унесла его в ту же ночь.";
			link.l1 = "Чтобы узнать то, что нам нужно - хватит и часа. Когда ты сможешь провести ритуал, Чимисет?";
			link.l1.go = "Chimset_9";
		break;
		
		case "Chimset_9":
			dialog.text = "Я заберу женщину прямо сейчас, отведу её в трюм - там обустроено  святилище... как раз для таких дел. Дальше всё будет зависеть от того, когда она вернётся в нормальное состояние... Но, думаю, к утру мы управимся.";
			link.l1 = "Тогда не стану вам мешать. И да поможет тебе... твой Бог, Чимисет.";
			link.l1.go = "Chimset_10";
		break;
		
		case "Chimset_10":
			dialog.text = "Зикомо! Помоги мне отвести белую женщину в трюм.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_13");
		break;
		
		case "Chimset_11":
			dialog.text = "Всё получилось, белый брат. Нам удалось...";
			link.l1 = "...";
			link.l1.go = "Chimset_11_add";
			DelLandQuestMark(npchar);
		break;
		case "Chimset_11_add":
			StartInstantDialog("LSC_Oreli", "Chimset_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Chimset_12":
			dialog.text = "О, "+GetFullName(pchar)+"! Не знала, что вы с Мэри вернулись на Остров! До чего же приятная встреча!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_14_1");
		break;
		
		case "Chimset_13":
			dialog.text = "...";
			link.l1 = "Чимисет, спасибо тебе! Я даже не знаю, как тебя благодарить...";
			link.l1.go = "Chimset_14";
			link.l2 = "Ну надо же, Чимисет - справился! Ну я в тебе и не сомневался...";
			link.l2.go = "Chimset_15";
		break;
		
		case "Chimset_14":
			dialog.text = "Все ривадос в вечном долгу перед тобой, мой друг! Двери 'Протектора' для тебя всегда открыты.";
			link.l1 = "Надеюсь, мне не потребуется больше вас тревожить... Мэри, Орели, нам нужно вернуться на 'Плуто'.";
			link.l1.go = "Chimset_15_add";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Chimset_15":
			dialog.text = "Все ривадос в вечном долгу перед тобой, мой друг! Двери 'Протектора' для тебя всегда открыты.";
			link.l1 = "Надеюсь, мне не потребуется больше вас тревожить... Мэри, Орели, нам нужно вернуться на 'Плуто'.";
			link.l1.go = "Chimset_15_add";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		case "Chimset_15_add":
			StartInstantDialog("LSC_Oreli", "Chimset_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Chimset_16":
			dialog.text = "Я и забыла, как покинула свою каюту... Эх, эта старость - память совершенно ни к чёрту. ";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_15");
		break;
		
		case "Oreli_11":
			dialog.text = "Так-так, юная леди, а что это вы забыли в моей каюте?";
			link.l1 = "...";
			link.l1.go = "Oreli_11_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_11_add":
			StartInstantDialog("LSC_Jillian_clone", "Oreli_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_12":
			dialog.text = "Орели, я...";
			link.l1 = "...";
			link.l1.go = "Oreli_12_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_12_add":
			StartInstantDialog("Mary", "Oreli_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_13":
			dialog.text = "Орели, я попросила её у тебя тут прибраться, пока ты отсутствовала. Ни к чему тебе с больными коленями спину гнуть...";
			link.l1 = "...";
			link.l1.go = "Oreli_13_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
			
		break;
		case "Oreli_13_add":
			StartInstantDialog("LSC_Jillian_clone", "Oreli_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_14":
			dialog.text = "Прибраться?! Ты...";
			link.l1 = "Джиллиан, спасибо тебе за работу. (шёпотом) У нас всё получилось. Чимисет справился.";
			link.l1.go = "Oreli_15";
		break;
		
		case "Oreli_15":
			dialog.text = "Не может быть...";
			link.l1 = "Как видишь. А теперь, пожалуйста, дай нам поговорить.";
			link.l1.go = "Oreli_15_add";
		break;
		case "Oreli_15_add":
			StartInstantDialog("LSC_Oreli", "Oreli_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_16":
			dialog.text = "Что ж, молодые люди, спасибо, что проводили старушку. Боюсь, скоро я совсем перестану выходить наружу. Ноги мои ноги...";
			link.l1 = "Если позволите, "+npchar.name+", мы задержимся у вас - совсем ненадолго. У нас с Мэри к вам очень важное дело.";
			link.l1.go = "Oreli_17";
		break;
		
		case "Oreli_17":
			dialog.text = "Если мне снова не придётся волочиться на другой корабль, то помогу чем смогу. Слушаю вас.";
			link.l1 = "...";
			link.l1.go = "Oreli_17_add";
		break;
		case "Oreli_17_add":
			StartInstantDialog("Mary", "Oreli_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_18":
			dialog.text = "Орели, я хочу, чтобы ты рассказала мне о моих родителях. И дне, когда я появилась на свет. Это ведь случилось здесь, на Острове, да? Дональд утверждает, что так оно и есть, но ведь его тогда ещё тут не было, а раз так, он не может знать наверняка. Однако ты живёшь здесь гораздо дольше него, да! Ведь дольше двадцати лет, верно?";
			link.l1 = "...";
			link.l1.go = "Oreli_18_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_18_add":
			StartInstantDialog("LSC_Oreli", "Oreli_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_19":
			dialog.text = "Тихо-тихо, девочка, не тараторь так, прошу тебя! А то я за тобой не поспеваю...";
			link.l1 = "...";
			link.l1.go = "Oreli_19_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_19_add":
			StartInstantDialog("Mary", "Oreli_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_20":
			dialog.text = "Понятно, да. Хорошо, давай ещё раз...";
			link.l1 = "...";
			link.l1.go = "Oreli_20_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_20_add":
			StartInstantDialog("LSC_Oreli", "Oreli_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_21":
			dialog.text = "Не стоит, Мэри, я пока не так плоха, ха-ха... Я услышала, что ты мне сказала. Но, так как я и в самом деле живу на Острове дольше всех, надеюсь, ты отнесёшься к моему возрасту с уважением и пониманием...";
			link.l1 = "...";
			link.l1.go = "Oreli_21_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_21_add":
			StartInstantDialog("Mary", "Oreli_22", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_22":
			dialog.text = "Ну разумеется, Орели! Как ты могла подумать иначе?";
			link.l1 = "...";
			link.l1.go = "Oreli_22_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_22_add":
			StartInstantDialog("LSC_Oreli", "Oreli_23", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_23":
			dialog.text = "Эх-х, смотрю я на нынешнюю молодёжь и... нет-нет, мы так себя не вели со старшими. Но к тебе это не относится, конечно. Я только хотела сказать, что нам будет проще, если я буду отвечать на твои вопросы один за другим, а не на все сразу...";
			link.l1 = "...";
			link.l1.go = "Oreli_23_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_23_add":
			StartInstantDialog("Mary", "Oreli_24", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_24":
			dialog.text = "Я понимаю, Орели. Как тебе будет угодно, да. Значит, ты была на Острове, когда я родилась? Если это случилось здесь, конечно...";
			link.l1 = "...";
			link.l1.go = "Oreli_24_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_24_add":
			StartInstantDialog("LSC_Oreli", "Oreli_25", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_25":
			dialog.text = "Я попала на Остров в 1633 году, тот день мне порой снится в кошмарах. Шторм, наш 'Репризаль' - флейт, на котором мы с мужем плыли во Флориду - болтает по волнам, того и гляди опрокинется кверху килем, а мы вспоминаем все заученные молитвы и придумываем новые... А потом треск и...";
			link.l1 = "...";
			link.l1.go = "Oreli_25_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_25_add":
			StartInstantDialog("Mary", "Oreli_26", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_26":
			dialog.text = "Значит, ты оказалась здесь за пять лет до моего рождения, да.";
			link.l1 = "...";
			link.l1.go = "Oreli_26_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_26_add":
			StartInstantDialog("LSC_Oreli", "Oreli_27", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_27":
			dialog.text = "Примерно так. Тогда здесь всё было несколько иначе - 'Сан-Херонимо' ещё держался на воде, внешнее кольцо кораблей было меньше раза в полтора, если не в два... И это ещё далеко не все корабли остаются на плаву! Вот что я вам скажу, молодые люди, если вы взглянете в ясную погоду на дно - в ужас придёте, сколько же там корабельных остовов...";
			link.l1 = "...";
			link.l1.go = "Oreli_27_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_27_add":
			StartInstantDialog("Mary", "Oreli_28", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_28":
			dialog.text = "Нас интересует корабль, на котором прибыли сюда мои родители. Со мной... или без меня?";
			link.l1 = "...";
			link.l1.go = "Oreli_28_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_28_add":
			StartInstantDialog("LSC_Oreli", "Oreli_29", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_29":
			dialog.text = "С тобой, девочка, с тобой.";
			link.l1 = "...";
			link.l1.go = "Oreli_29_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_29_add":
			StartInstantDialog("Mary", "Oreli_30", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_30":
			dialog.text = "Значит, я родилась всё-таки на Большой земле?";
			link.l1 = "...";
			link.l1.go = "Oreli_30_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_30_add":
			StartInstantDialog("LSC_Oreli", "Oreli_31", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_31":
			dialog.text = "Нет, я имела в виду 'с тобой' несколько в ином смысле. Ты была в животе твоей матери и родилась спустя неделю.";
			link.l1 = "По-вашему, Орели, это смешно?";
			link.l1.go = "Oreli_32";
			link.l2 = "А вы с годами не утратили чувство юмора, Орели.";
			link.l2.go = "Oreli_33";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		
		case "Oreli_32":
			dialog.text = "Ну, над собой я посмеиваюсь куда чаще, чем над другими. Прости, Мэри, я не хотела тебя обидеть.";
			link.l1 = "...";
			link.l1.go = "Oreli_33_add";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		
		case "Oreli_33":
			dialog.text = "Ну, над собой я посмеиваюсь куда чаще, чем над другими. Прости, Мэри, я не хотела тебя обидеть.";
			link.l1 = "...";
			link.l1.go = "Oreli_33_add";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		case "Oreli_33_add":
			StartInstantDialog("Mary", "Oreli_34", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_34":
			dialog.text = "Всё в порядке, Орели. Прошу - продолжай, да. Что стало с моими родителями после моего рождения?";
			link.l1 = "...";
			link.l1.go = "Oreli_34_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_34_add":
			StartInstantDialog("LSC_Oreli", "Oreli_35", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_35":
			dialog.text = "После? Милая моя, то, что они оба дожили до него - это великое чудо! Какая страшная буря бушевала в ту июнскую ночь! Когда наутро шлюпка доставила на внутреннее кольцо твою мать, мало кто сразу поверил своим глазам - что женщина на сносях, которая должна вот-вот родить, пережила такое страшное кораблекрушение. Бедняжка Тереза, я как сейчас помню...";
			link.l1 = "...";
			link.l1.go = "Oreli_35_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_35_add":
			StartInstantDialog("Mary", "Oreli_36", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_36":
			dialog.text = "Тереза? Так её звали?";
			link.l1 = "...";
			link.l1.go = "Oreli_36_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_36_add":
			StartInstantDialog("LSC_Oreli", "Oreli_37", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_37":
			dialog.text = "Да, так она представилась - и это было едва ли не всё, что она произнесла. Под конец дня она впала в бред, в котором и пробыла аж до самых родов. Никто не был уверен, что она сумеет родить, и уж тем более, все сомневались в том, что ребёнок родится живым - после всего-то пережитого. Но Тереза справилась. Справилась - и испустила дух. Да хранит Господь её душу...";
			link.l1 = "...";
			link.l1.go = "Oreli_37_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_37_add":
			StartInstantDialog("Mary", "Oreli_38", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_38":
			dialog.text = "Мама погибла, и я осталась с отцом? Но почему все тогда утверждали, что меня воспитывал Эрик Удетт? И...";
			link.l1 = "...";
			link.l1.go = "Oreli_38_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_38_add":
			StartInstantDialog("LSC_Oreli", "Oreli_39", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_39":
			dialog.text = "Мэри, дорогая, я же просила... Не засыпай меня таким количеством вопросов...";
			link.l1 = "...";
			link.l1.go = "Oreli_39_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_39_add":
			StartInstantDialog("Mary", "Oreli_40", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_40":
			dialog.text = "Прости, Орели, я забылась, да. Мой отец, он же тоже пережил кораблекрушение?";
			link.l1 = "...";
			link.l1.go = "Oreli_40_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_40_add":
			StartInstantDialog("LSC_Oreli", "Oreli_41", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_41":
			dialog.text = "Твой отец... Знаешь, я мало что могу сказать про твоего отца - кроме того, что никому такого папашу не пожелаю. Через несколько дней после твоего появления на свет он исчез, бросив тебя на произвол судьбы. Тебе повезло, что у Эрика было столь доброе и мягкое сердце - словно сухарь, размоченный в кружке грога...";
			link.l1 = "...";
			link.l1.go = "Oreli_41_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_41_add":
			StartInstantDialog("Mary", "Oreli_42", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_42":
			dialog.text = "Скажи хотя бы, как его звали, да!";
			link.l1 = "...";
			link.l1.go = "Oreli_42_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_42_add":
			StartInstantDialog("LSC_Oreli", "Oreli_43", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_43":
			dialog.text = "О-ох... То ли Джеффри, то ли Джон, дай Бог мне памяти...";
			link.l1 = "Значит, вы не помните? Верно, "+npchar.name+"?";
			link.l1.go = "Oreli_44";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		
		case "Oreli_44":
			dialog.text = "Вы сомневаетесь в моих словах, молодой человек?!";
			link.l1 = "Тише, "+npchar.name+", тише. Я не хотел вас задеть. Просто мне показалось, что вы довольно... неплохо помните те дни, вот и всё.";
			link.l1.go = "Oreli_45";
			link.l2 = "Ни в чём я не сомневаюсь, "+npchar.name+". Просто пытаюсь верно запомнить все детали верно - не более того. Но вся эта путаница несколько осложняет задачу.";
			link.l2.go = "Oreli_46";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		
		case "Oreli_45":
			dialog.text = "Память - дама избирательная, "+pchar.name+", весьма избирательная. Тем более, когда минуло столько лет. Терезу сложно забыть - я наблюдала за её мучениями всю неделю! О-ох, как же мне было её жалко!";
			link.l1 = "А её муж, разве он не был рядом с ней?";
			link.l1.go = "Oreli_47";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Oreli_46":
			dialog.text = "Память - дама избирательная, "+pchar.name+", весьма избирательная. Тем более, когда минуло столько лет. Терезу сложно забыть - я наблюдала за её мучениями всю неделю! О-ох, как же мне было её жалко!";
			link.l1 = "А её муж, разве он не был рядом с ней?";
			link.l1.go = "Oreli_47";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Oreli_47":
			dialog.text = "Очень редко. Почти всю неделю он где-то пропадал - в поисках лекарств и микстур, кои тогда на Острове были в большом дефиците...";
			link.l1 = "Значит, он был хорошим мужем - раз пытался помочь жене.";
			link.l1.go = "Oreli_48";
		break;
		
		case "Oreli_48":
			dialog.text = "Мужем он, может, и был хорошим. Обратного я не утверждала, позволю себе заметить. Не пытайтесь меня запутать, юноша!";
			link.l1 = "И в мыслях такого не было, уверяю, "+npchar.name+". Просто очевидно, что вы о нём не самого высокого мнения. И то, что вы не помните его имени...";
			link.l1.go = "Oreli_49";
		break;
		
		case "Oreli_49":
			dialog.text = "Я видела этого мужчину чуть ли не мельком в темноте каюты 'Церес Смити', там, где сейчас проживает герр Юрген. Он приходил лишь ночью, и лицо его я помню очень смутно. Что же до его имени - так по имени его никто и не звал, только по фамилии. Каспер то, Каспер это...";
			link.l1 = "Я понял вас, "+npchar.name+". Значит, Мэри родилась, и через несколько дней он бесследно исчез. Его убили?";
			link.l1.go = "Oreli_50";
		break;
		
		case "Oreli_50":
			dialog.text = "Сложный вопрос, молодой человек. Видите ли, в этом месте сохранить что-то в тайне довольно-таки непросто - все у всех на виду. Когда случается очередная склока - даже внутри кораблей - на следующий день о ней знает весь Остров.";
			link.l1 = "Неудивительно.";
			link.l1.go = "Oreli_51";
		break;
		
		case "Oreli_51":
			dialog.text = "Тела убитых находят далеко не всегда - опытные дельцы утапливают трупы, обматывая руки и ноги книппелями, или привязывая к ним ядра или камни. А крабы на дне уже доделывают работу. Однако, личные вещи погибших сразу или через какое-то время всплывают вновь.";
			link.l1 = "Со дна?!";
			link.l1.go = "Oreli_52";
		break;
		
		case "Oreli_52":
			dialog.text = "Конечно нет! Я имела в виду, что они попадаются на глаза - колечко, пистоль именной, сабелька наградная... Вопросы на этот счёт задают редко. Человека-то уже не вернёшь, а лишние конфликты совсем ни к чему.";
			link.l1 = "У Джеффри или Джона Каспера были приметные вещи?";
			link.l1.go = "Oreli_53";
		break;
		
		case "Oreli_53":
			dialog.text = ""+pchar.name+", Господь с вами - я имени-то его вспомнить не могу, а вы мне такие вопросы задаёте! Если что и было, то я не слышала разговоров о том, чтобы эта вещь оказалась у другого жителя Острова. Тогда я работала подавальщицей в таверне, и мало какой слух проходил мимо меня. Но это вовсе не значит, что я знала совершенно всё.";
			link.l1 = "Когда говорят, что люди исчезают бесследно - обычно подразумевается, что они убиты. Вы же в случае мистера Каспера явно в этом не уверены...";
			link.l1.go = "Oreli_54";
		break;
		
		case "Oreli_54":
			dialog.text = "Я лишь говорю, что 'исчез' вовсе не означает 'погиб'. Тем более в те годы, когда между Островом и Кубой регулярно ходили тартаны контрабандистов и скупщиков краденого... Знаете, я не помню черты его лица, но вот его взгляд... Это был взгляд человека, который нигде не пропадёт. Или, во всяком случае, сам в это свято верит.";
			link.l1 = "Тартаны, тартаны... Ничего невозможного нет. Знай мы его имя - могли бы поднять колониальные архивы тех лет. Но куда проще было бы это сделать, будь у нас тип и название судна, на котором он 'прибыл' сюда.";
			link.l1.go = "Oreli_55";
		break;
		
		case "Oreli_55":
			dialog.text = "А что вы смотрите на меня, юноша? Думаете, я это вспомню?";
			link.l1 = "Мы надеемся на это, "+npchar.name+" - учитывая, как много вы уже нам поведали.";
			link.l1.go = "Oreli_56";
			link.l2 = "Хм-м... Есть большие сомнения на этот счёт.";
			link.l2.go = "Oreli_57";
		break;
		
		case "Oreli_56":
			dialog.text = "Может, вы ещё спросите, сколько на нём было пушек и какого они калибра? Дорогой мой, вы знаете, сколько судов погибло тут за эти годы? И вы считаете, что я помню их все? К тому же, с того корабля спаслось всего-навсего несколько человек - он и дня на поверхности воды не продержался поди...";
			link.l1 = "Ясно... Оно и понятно, двадцать лет прошло. Спасибо, что вы не забыли хотя бы то, что нам рассказали.";
			link.l1.go = "Oreli_58";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Oreli_57":
			dialog.text = "Может, вы ещё спросите, сколько на нём было пушек и какого они калибра? Дорогой мой, вы знаете, сколько судов погибло тут за эти годы? И вы считаете, что я помню их все? К тому же, с того корабля спаслось всего-навсего несколько человек - он и дня на поверхности воды не продержался поди...";
			link.l1 = "Ясно... Оно и понятно, двадцать лет прошло. Спасибо, что вы не забыли хотя бы то, что нам рассказали.";
			link.l1.go = "Oreli_58";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Oreli_58":
			dialog.text = "Надеюсь, вы не шутите и не пытаетесь посмеяться над старухой, память которой превратилась в решето.";
			link.l1 = "Ни в коей мере, "+npchar.name+". Вы правда нам очень сильно помогли. Выздоравливайте. Ну а мы пойдём.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_16");
		break;
		
		case "Mary_91":
			dialog.text = "Значит, Тереза... Так её звали. Бедная моя мама, да...";
			link.l1 = "Ну, зато теперь мы знаем, в кого у тебя столько сил и упрямства. Беременная женщина на терпящем крушение судне... Дрожь пробирает  от такой картины.";
			link.l1.go = "Mary_92";
		break;
		
		case "Mary_92":
			dialog.text = "Но что она делала в таком состоянии на этом корабле, "+pchar.name+"?! Это же надо быть сумасшедшей, чтобы решиться на такое!";
			link.l1 = "Ответить на этот вопрос может только твой отец - Джон, Джек, Джейкоб, Джаспер, Джордан...";
			link.l1.go = "Mary_94";
		break;
		
		case "Mary_94":
			dialog.text = "Ты решил вспомнить все английские имена начинающиеся на «Дж»? Орели ведь назвала только Джеффри и Джона, да.";
			link.l1 = "Возможно, она просто не вспомнила остальные, как я? Ну, знаешь, возраст и всё такое...";
			link.l1.go = "Mary_95";
		break;
		
		case "Mary_95":
			dialog.text = ""+pchar.name+", ты думаешь...";
			link.l1 = "Я бы не стал сейчас полностью доверять её памяти. Но даже если так, нам придётся поднять даже не колониальные - а флотские архивы за 1638 год, что куда сложнее: сведения ведь закрытого характера, особенно если это касается офицеров. А я сильно сомневаюсь, что простому матросу позволили бы протащить на борт жену.";
			link.l1.go = "Mary_96";
		break;
		
		case "Mary_96":
			dialog.text = "С другой стороны, найти сведения по офицеру куда проще, чем по обычному моряку.";
			link.l1 = "Если знать название судна. Или его полное имя. А не 'Джеффри или Джон или, на худой конец, Джек...'. Это нам ещё повезёт, если судно было военным. У торгашей со списками экипажа дела куда похуже.";
			link.l1.go = "Mary_97";
		break;
		
		case "Mary_97":
			dialog.text = "Но что же нам тогда делать, "+pchar.name+"? Поговорить с Орели ещё раз? Мы и без того вытянули из неё что могли, тебе так не кажется?";
			link.l1 = "Не с Орели. С Дональдом.";
			link.l1.go = "Mary_98";
		break;
		
		case "Mary_98":
			dialog.text = "А чем он нам поможет? Он же сказал, что в 1638 году его и близко на Острове Справедливости не было, да.";
			link.l1 = "Но другие-то нарвалы тут были, верно?";
			link.l1.go = "Mary_99";
		break;
		
		case "Mary_99":
			dialog.text = "Я не очень понимаю, к чему ты клонишь.";
			link.l1 = "Увидишь, дорогая, увидишь. Есть ещё одна ниточка, за которую можно потянуть. Идём.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_17");
		break;
		
		case "Grinspy_31":
			dialog.text = "А, снова вы! Ну, и как продвигаются ваши поиски?";
			link.l1 = "Здравствуй, "+npchar.name+". Могло быть и лучше - пока что блуждаем словно в этой пещере тайн и загадок. Но чувствуем, что выход уже близко.";
			link.l1.go = "Grinspy_32";
			link.l2 = "И тебе здравствуй, "+npchar.name+". Лучше, чем можно было бы представить в самом начале. Ситуация... не такая уж и безнадёжная.";
			link.l2.go = "Grinspy_33";
			DelLandQuestMark(npchar);
		break;
		
		case "Grinspy_32":
			dialog.text = "Рад это слышать. Честно. Однако, вам обоим вновь что-то нужно от меня, верно? Что вам удалось выяснить?";
			link.l1 = "Мэри родилась здесь, на Острове, в июне 1638 года. Её мать, Тереза, скончалась сразу после родов. Отец - некто по фамилии Каспер - как в воду канул через несколько дней после появления Мэри на свет. Ничего о нём, кроме того, что его имя начинается на 'Дж.', мы не знаем. Есть мнение, что он не стал пищей для крабов на местном мелководье, а покинул Остров на одной из тартан контрабандистов...";
			link.l1.go = "Grinspy_34";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Grinspy_33":
			dialog.text = "Рад это слышать. Честно. Однако, вам обоим вновь что-то нужно от меня, верно? Что вам удалось выяснить?";
			link.l1 = "Мэри родилась здесь, на Острове, в июне 1638 года. Её мать, Тереза, скончалась сразу после родов. Отец - некто по фамилии Каспер - как в воду канул через несколько дней после появления Мэри на свет. Ничего о нём, кроме того, что его имя начинается на 'Дж.', мы не знаем. Есть мнение, что он не стал пищей для крабов на местном мелководье, а покинул Остров на одной из тартан контрабандистов...";
			link.l1.go = "Grinspy_34";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Grinspy_34":
			dialog.text = "И бросил дочку? Странный поступок.";
			link.l1 = "Так и есть. Но никто, кроме этого самого мистера Дж., объяснить это не сможет.";
			link.l1.go = "Grinspy_35";
		break;
		
		case "Grinspy_35":
			dialog.text = "И вы думаете, что он ещё жив? И за этим его ищете?";
			link.l1 = "Не только за этим. Мы хотим узнать, кем он был, как он жил. Для Мэри это очень важно.";
			link.l1.go = "Grinspy_36";
		break;
		
		case "Grinspy_36":
			dialog.text = "Хм-м, понимаю. И мне жаль, что я толком ничем не могу вам помочь...";
			link.l1 = "На самом деле, можешь. Скажи, нарвалы ведь ведут некий учёт кораблей, погибших у Острова?";
			link.l1.go = "Grinspy_37";
		break;
		
		case "Grinspy_37":
			dialog.text = "Не совсем понимаю, что ты имеешь в виду, "+pchar.name+".";
			link.l1 = "Гринспи, Гринспи... Не забывай, что до сих пор греешь зад в этом кресле только благодаря мне. Так что будь добр - не испытывай моё терпение.";
			link.l1.go = "Grinspy_38";
			link.l2 = "Уверен, что понимаешь, Дональд. И во имя нашей дружбы не станешь юлить.";
			link.l2.go = "Grinspy_39";
		break;
		
		case "Grinspy_38":
			dialog.text = "Хм-м...";
			link.l1 = "К внешнему кольцу периодически прибивает корабли. Некоторые уходят на дно сразу, другие какое-то время удерживаются на плаву - их обыскивают и снимают с них всё ценное. Не знаю насчёт ривадос, но сомневаюсь, что нарвалы дерутся за каждую найденную на борту безделушку - скорее всего, всё скидывают в общий котёл, после чего проводится опись всего и вся, и только вслед за этим - раздел добычи.";
			link.l1.go = "Grinspy_40";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;
		
		case "Grinspy_39":
			dialog.text = "Хм-м...";
			link.l1 = "К внешнему кольцу периодически прибивает корабли. Некоторые уходят на дно сразу, другие какое-то время удерживаются на плаву - их обыскивают и снимают с них всё ценное. Не знаю насчёт ривадос, но сомневаюсь, что нарвалы дерутся за каждую найденную на борту безделушку - скорее всего, всё скидывают в общий котёл, после чего проводится опись всего и вся, и только вслед за этим - раздел добычи.";
			link.l1.go = "Grinspy_40";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;
		
		case "Grinspy_40":
			dialog.text = "Ты не глуп, "+pchar.name+". В отличие от многих здесь. Да, всё примерно так и происходит. Лично мне претит эта писанина, но это делалось и во времена Алана Милроу и тех, кто возглавлял клан 'Нарвал' до него. Мы составляем такие записи - и более того: фиксируем даже те корабли, до которых первыми добрались ривадос или пираты. Но в таких случаях мы, разумеется, не в курсе, кто и что было на борту...";
			link.l1 = "Судя по тому, что родителей Мэри доставили после кораблекрушения на 'Церес Смити', их корабль нашли именно нарвалы. А значит, должна быть соответствующая запись.";
			link.l1.go = "Grinspy_41";
		break;
		
		case "Grinspy_41":
			dialog.text = "Может быть и так. Точно сказать не могу. И не смогу.";
			link.l1 = "Теперь уже я не понимаю, что ты имеешь в виду, "+npchar.name+".";
			link.l1.go = "Grinspy_42";
		break;
		
		case "Grinspy_42":
			dialog.text = "Журналы учёта погибших кораблей. Когда Лейтон Декстер стал Адмиралом после отбытия Додсона, он изъял у нас эти документы.";
			link.l1 = "Просто взял и изъял? И ты не возражал?";
			link.l1.go = "Grinspy_43";
		break;
		
		case "Grinspy_43":
			dialog.text = "Ну, во-первых, он был достаточно вежлив. Во-вторых, обещал их вернуть в скором времени. А в-третьих... на кой чёрт мне дались эти бумажки?";
			link.l1 = "Не самые бесполезные записи, так-то.";
			link.l1.go = "Grinspy_44";
		break;
		
		case "Grinspy_44":
			dialog.text = "Говорю же, это просто традиция, направленная главным образом на то, чтобы члены нашего клана не перегрызли друг другу глотки за добычу с кораблей. Судно прибило, мы сняли с него всё, что смогли, сделали опись, что-то поделили, что-то упрятали в наши трюмы - вот и всё. Чего шкафы забивать? В них освободилось немного места - пожалуй, мне даже следует поблагодарить за это Адмирала.";
			link.l1 = "Что ж, ясно. Тогда берём курс на 'Сан-Августин'. Но, возможно, мы ещё заглянем к тебе, "+npchar.name+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_18");
		break;
		
		case "WildRose_Dexter_1":
            dialog.text = "А, "+pchar.name+", проходи, проходи. Ты по делу ко мне, дружище, или просто решил проведать?";
            link.l1 = "На этот раз, по делу. Оно, скажем так, личное.";
            link.l1.go = "WildRose_Dexter_2";
			DelLandQuestMark(npchar);
        break;

        case "WildRose_Dexter_2":
            dialog.text = "И достаточно важное для тебя - судя по тому, насколько взбудораженным ты выглядишь.";
            link.l1 = "В самом деле? Скорее уж, уставшим. Пришлось немало побродить по твоим владениям в последние дни. Суставы уже дают о себе знать - а я-то наивно полагал, что такое случается только со стариканами вроде тебя.";
            link.l1.go = "WildRose_Dexter_3_1";
            link.l2 = "Малость запыхался - вот и всё. Я, видишь ли, не только в кресле сижу. А вот тебя, я вижу, совсем ноги уже не держат, ха-ха-ха!";
            link.l2.go = "WildRose_Dexter_3_2";
        break;

        case "WildRose_Dexter_3_1":
            dialog.text = "А ты думал, почему я прирос задницей к этому креслу, хе-хе? Знаешь, мировоззрение может серьёзно поменяться, когда поймёшь, что здоровье не купишь даже за все богатства этого Острова.";
            link.l1 = "Забавно - именно об этом я и пришёл поговорить.";
            link.l1.go = "WildRose_Dexter_4";
			AddCharacterExpToSkill(pchar, "Defence", 100);
        break;
		
		case "WildRose_Dexter_3_2":
            dialog.text = "А ты думал, почему я прирос задницей к этому креслу, хе-хе? Знаешь, мировоззрение может серьёзно поменяться, когда поймёшь, что здоровье не купишь даже за все богатства этого Острова.";
            link.l1 = "Забавно - именно об этом я и пришёл поговорить.";
            link.l1.go = "WildRose_Dexter_4";
			AddComplexSelfExpToScill(100, 100, 100, 100);
        break;

        case "WildRose_Dexter_4":
            dialog.text = "О моём здоровье?";
            link.l1 = "Нет, о богатствах Острова. А если быть чуть более точным, об их описи. А если быть совсем точным, то о журналах, эти описи содержащих.";
            link.l1.go = "WildRose_Dexter_5";
        break;

        case "WildRose_Dexter_5":
            dialog.text = "Кхе-кхе... "+pchar.name+", я не совсем улавливаю, о чём ты?";
            link.l1 = "Не так давно ты изъял у нарвалов журналы учёта прибитых к Острову кораблей...";
            link.l1.go = "WildRose_Dexter_6";
        break;

        case "WildRose_Dexter_6":
            dialog.text = "Так, и этот болван Гринспи решил послать тебя за ними? Вот же наглец.";
            link.l1 = "Вовсе нет, "+npchar.name+", Дональд тут ни при чём. Я пришёл к нему с этим вопросом, а он направил меня к тебе. Но твоя реакция, признаться, меня позабавила. Не поделишься, зачем тебе понадобились записи нарвалов?";
            link.l1.go = "WildRose_Dexter_7";
        break;

        case "WildRose_Dexter_7":
            dialog.text = "Тебе почему бы и не рассказать? Мне, как ты мог догадаться, на сами корабли плевать. Да и на ценности, которыми набиты их трюмы, в общем-то, тоже. Здесь всем хватит, если не зарываться - так я считаю. Что меня действительно интересует - это оружие: мушкеты, сабли... пушки в конце концов. Да, эти умники и их порой снимают тоже. Пустоголовым черномазым на то ума не достаёт, а вот нарвалам...";
            link.l1 = "И ты решил оценить, насколько люди Гринспи готовы к новому витку противостояния?";
            link.l1.go = "WildRose_Dexter_8";
        break;

        case "WildRose_Dexter_8":
            dialog.text = "И намекнуть на то, что я и мои ребята держим ухо востро. Посыл весьма прозрачный, но с учётом того цирка, что Дональд устроил с этими учениями, я вполне допускаю, что он решил, будто меня интересуют его денежки.";
            link.l1 = "Да уж, вижу, что ситуация развивается несколько не в том ключе, на который ты рассчитывал. А что ривадос? Чёрный Эдди не доставляет хлопот?";
            link.l1.go = "WildRose_Dexter_9";
        break;

        case "WildRose_Dexter_9":
            dialog.text = "Ривадос, Эдди... Мерзкие негры - недаром Акула их так ненавидел.";
            link.l1 = "Значит, доставляет.";
            link.l1.go = "WildRose_Dexter_10";
        break;

        case "WildRose_Dexter_10":
            dialog.text = "В том-то и дело, что нет, будь я проклят! Черномазые притихли, засели у себя на кораблях...";
            link.l1 = "Ну и какого дьявола тогда тебя не устраивает, "+npchar.name+"?";
            link.l1.go = "WildRose_Dexter_11";
        break;

        case "WildRose_Dexter_11":
            dialog.text = "Как бы тебе объяснить, "+pchar.name+"... Видишь ли, это как ветер в открытом море. Он бывает слабым, бывает сильным, а иногда и вовсе разыгрывается шторм. Но так или иначе ветер двигает судно вперёд, и хороший капитан способен его обуздать.";
            link.l1 = "Лёгкий бриз всегда лучше жестокой бури.";
            link.l1.go = "WildRose_Dexter_12";
        break;

        case "WildRose_Dexter_12":
            dialog.text = "Да. Но иногда бывает и так, что ветра нет вовсе. Штиль - и вот с ним никакой шкипер ни черта не поделает. Ты просто сидишь на юте, смотришь на водную гладь и гадаешь, что же, чёрт побери, будет дальше. С Эдди и его дружком Чимисетом то же самое - они что-то затевают, я нутром это чую, и это не к добру, клянусь громом!";
            link.l1 = "Возможно, тебе стоило бы оторвать зад от кресла и пойти пообщаться с Эдвардом с глазу на глаз. А лучше - собраться втроём, ещё и с Дональдом, и всё откровенно обсудить. Это куда лучше, чем вновь утопить Остров в крови. Но да ладно... Вернёмся к тому, зачем я пришёл.";
            link.l1.go = "WildRose_Dexter_13";
        break;

        case "WildRose_Dexter_13":
            dialog.text = "Так тебя интересуют ценности нарвалов, я прав? Что ты хочешь там найти?";
            link.l1 = "Меня интересуют списки погибших здесь кораблей. Конкретно - за 1638 год. Дело в том, что мы пытаемся найти информацию о родителях Мэри. С матерью всё более или менее понятно - а вот об отце этого никак не скажешь. Сведения о нём весьма туманны, мы не знаем даже его имени, и если и можем за что-то зацепиться - так это за название корабля, разбившегося у внешнего кольца в июне 1638 года...";
            link.l1.go = "WildRose_Dexter_14";
        break;

        case "WildRose_Dexter_14":
            dialog.text = "Дело благородное - я и сам когда-то терзался мыслью о том, кем же был мой собственный папаша. Вот только помочь вам я не в силах.";
            link.l1 = "И почему же, если не секрет?";
            link.l1.go = "WildRose_Dexter_15";
        break;

        case "WildRose_Dexter_15":
            dialog.text = "От тебя никаких секретов, "+pchar.name+". Дело вовсе не во мне, а в Дональде - он передал мне бумаги лишь от 1651 года. Я поинтересовался, что насчёт более старых записей, хотя бы за предыдущее десятилетие - и получил ответ, что больше никаких бумаг нет. Это всё, что ему по этой части досталось в наследство от Алана Милроу - так он сказал.";
            link.l1 = "Не думаю, что у него были причины врать.";
            link.l1.go = "WildRose_Dexter_16";
        break;

        case "WildRose_Dexter_16":
            dialog.text = "Я думаю так же, дружище. Учитывая, что он безо всяких вопросов отдал мне новые записи. Более того, мне показалось, что он был даже в какой-то степени рад избавиться от этого хлама... Кто знает, может, Милроу попросту избавился от бумаг прошлых десятилетий... Спалил, или может быть...";
            link.l1 = "Нет, этого не может быть.";
            link.l1.go = "WildRose_Dexter_16_Add";
        break;

        case "WildRose_Dexter_16_Add":
            StartInstantDialog("Mary", "WildRose_Dexter_17", "Quest\CompanionQuests\WildRose.c");
        break;

        case "WildRose_Dexter_17":
            dialog.text = "Нет, этого не может быть. Алан бы так не поступил.";
            link.l1 = "Почему ты так в этом уверена, "+npchar.name+"?";
            link.l1.go = "WildRose_Dexter_17_1";
            link.l2 = "Мне казалось, он был больше по части ножа и топора, чем всей этой бюрократии. Удивлён, что он вообще умел читать.";
            link.l2.go = "WildRose_Dexter_17_2";
        break;

        case "WildRose_Dexter_17_1":
            dialog.text = "Он очень трепетно относился ко всем записям, касающимся Острова. Считал их частью его истории. А история, причём не только этого места, была настоящим увлечением Алана, да. Он изучал все доступные ему исторические документы, книги... Мне порой казалось, что учёный из него вышел бы куда лучше, чем рубака - один раз я даже ему об этом сказала.";
            link.l1 = "...";
            link.l1.go = "WildRose_Dexter_18";
        break;

        case "WildRose_Dexter_17_2":
            dialog.text = "Он очень трепетно относился ко всем записям, касающимся Острова. Считал их частью его истории. А история, причём не только этого места, была настоящим увлечением Алана, да. Он изучал все доступные ему исторические документы, книги... Мне порой казалось, что учёный из него вышел бы куда лучше, чем рубака - один раз я даже ему об этом сказала.";
            link.l1 = "Возможно, ему и впрямь стоило предпочесть очки, бумагу и перо клинку и пистолю - глядишь, ещё бы топтал гнилые доски здешних кораблей. Но раз Милроу был таким ценителем архивных материалов, куда же он подевал те записи? Допустим, одну бумажку он мог случайно залить чернилами - но их ведь были десятки, если не сотни, так ведь?";
            link.l1.go = "WildRose_Dexter_18";
        break;

        case "WildRose_Dexter_18":
            dialog.text = "Я знаю, только то, что он бережно хранил такие документы пуще зеницы ока. Быть может, их кто-то украл, или же он сам кому-то их отдал...";
            link.l1 = "Украл? Кому могли понадобиться сведения о давно выпотрошенных от квартердека до киля кораблях? Отдал - это куда вероятнее, вот только кому и зачем?";
            link.l1.go = "WildRose_Dexter_19_Add";
        break;

        case "WildRose_Dexter_19_Add":
            StartInstantDialogNoType("Dexter", "WildRose_Dexter_20", "Quest\CompanionQuests\WildRose.c");
        break;

        case "WildRose_Dexter_20":
            dialog.text = "Какому-нибудь такому же любителю истории, ха-ха-ха! Согласен с Шарлем - ума не приложу, кому ещё могли понадобиться эти древние писульки.";
            link.l1 = "Кому-то, однако, понадобились. Придётся пораскинуть мозгами на этот счёт. Ладно, "+npchar.name+", не будем более тебя отвлекать. Ещё увидимся.";
            link.l1.go = "Exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_19");
        break;
		
		case "WildRose_Betancur_1":
			dialog.text = ""+pchar.name+", рад новой встрече. Как у вас с Мэри дела?";
			link.l1 = "И мы рады тебя видеть, "+npchar.name+". А вот как у нас дела - будет зависеть от тебя.";
			link.l1.go = "WildRose_Betancur_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Betancur_2":
			dialog.text = "Интригующее начало разговора, должен признать. И несколько пугающее, учитывая выражения ваших лиц.";
			link.l1 = "Не пугайся, "+npchar.name+", ведь не ты тому виной. Мы просто малость устали бегать по этим скрипучим корабельным обломкам. Да и день сегодня душноватый, не находишь?";
			link.l1.go = "WildRose_Betancur_3_1";
			link.l2 = "Эта жара сил нам, отнюдь, не прибавляет. К тому же, нам пришлось побегать по Острову, пока тебя искали - помощь твоя нужна.";
			link.l2.go = "WildRose_Betancur_3_2";
		break;

		case "WildRose_Betancur_3_1":
			dialog.text = "Кхм, да, лёгкий бриз бы сейчас был бы весьма кстати. Так что же я могу для вас сделать?";
			link.l1 = "Видишь ли, мы с Мэри затеяли раследование, чтобы пролить свет на события двадцатилетней давности.";
			link.l1.go = "WildRose_Betancur_4";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "WildRose_Betancur_3_2":
			dialog.text = "Кхм, да, лёгкий бриз бы сейчас был бы весьма кстати. Так что же я могу для вас сделать?";
			link.l1 = "Видишь ли, мы с Мэри затеяли раследование, чтобы пролить свет на события двадцатилетней давности.";
			link.l1.go = "WildRose_Betancur_4";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Betancur_4":
			dialog.text = "Звучит увлекательно. И чего же оно касается?";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_4_add";
		break;
		
		case "WildRose_Betancur_4_add":
			StartInstantDialog("Mary", "WildRose_Betancur_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_5":
			dialog.text = "Моих родителей, Антонио. Мы с Шарлем пытаемся узнать, кем они были. И что с ними стало. Моя мама умерла при родах, это мы уже выяснили. Но с отцом всё не так просто...";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_5_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_6":
			dialog.text = "В каком году ты родилась, напомни-ка...";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_6_add":
			StartInstantDialog("Mary", "WildRose_Betancur_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_7":
			dialog.text = "В 1638-м. В июне.";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_7_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_8":
			dialog.text = "Мне тогда было всего двенадцать лет, Мэри. Я не очень хорошо помню те дни. Кое-какие воспоминания, конечно, сейчас мелькают в памяти, но собрать их в единую картину, честно говоря, будет малость затруднительно. Прости, но вряд ли я смогу помочь тебе...";
			link.l1 = "Нам нужно от тебя не совсем это, Антонио. Хотя, если ты что-то вспомнишь из событий того дня, когда Мэри появилась на свет, мы будем тебе очень признательны.";
			link.l1.go = "WildRose_Betancur_9";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;
		
		case "WildRose_Betancur_9":
			dialog.text = "Тогда чем же я могу вам помочь, "+pchar.name+"?";
			link.l1 = "Ты рассказывал мне, что увлекаешься историей. Как мировой, в целом, так и Острова, в частности.";
			link.l1.go = "WildRose_Betancur_10";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), pchar);
		break;

		case "WildRose_Betancur_10":
			dialog.text = "Это правда. Я прочитал всевозможные книги, изучил все рукописи, которые только смог достать...";
			link.l1 = "Именно о рукописях и пойдёт речь. Помимо тебя на Острове был лишь один человек, увлекающийся историей не меньше твоего...";
			link.l1.go = "WildRose_Betancur_12";
		break;

		case "WildRose_Betancur_12":
			dialog.text = "Алан Милроу. Да, мы общались на эту тему, когда он не был занят разработкой планов по уничтожению ривадос, а позже и пиратов. Умный был парень, весьма незаурядных талантов.";
			link.l1 = "Не сомневаюсь - парень был хоть куда. У него было кое-что, что может нам помочь. При этом не имеющее никакой практической ценности ни для кого на Острове Справедливости, кроме вас двоих. Журналы учёта судов разбившихся у Острова, содержащих также описание снятых с них грузов и ценностей и, возможно, имена пассажиров...";
			link.l1.go = "WildRose_Betancur_13";
		break;

		case "WildRose_Betancur_13":
			dialog.text = "Так и есть.";
			link.l1 = "Значит, ты их видел?";
			link.l1.go = "WildRose_Betancur_14";
		break;

		case "WildRose_Betancur_14":
			dialog.text = "Не просто видел - я переписывал содержащиеся в них сведения в свои записи. В ходе одной из наших бесед он обмолвился о существовании этих журналов, и я попросил у него их для изучения - я пытаюсь составить нечто вроде Хроник Острова Справедливости, и эти записи мне весьма пригодились\nАлан был в восторге от моей идеи - написать историю этого места. Правда, он отдал мне не все записи, оставив себе сведения за 1650-е, но на тот момент мне хватило и остального.";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_14_add";
		break;
		
		case "WildRose_Betancur_14_add":
			StartInstantDialog("Mary", "WildRose_Betancur_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_15":
			dialog.text = "Там ведь есть записи за 1638 год? Прошу, скажи, что есть, да!";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_15_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_15_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_16", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_16":
			dialog.text = "У меня целая стопка этих журналов - аж начиная с 1620 года. Именно тогда, по словам Алана, эти записи и начали вести. И да, 1638 год там тоже есть, Мэри.";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_16_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_16_add":
			StartInstantDialog("Mary", "WildRose_Betancur_17", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_17":
			dialog.text = "Ты позволишь нам с ними ознакомиться?";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_17_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;
		
		case "WildRose_Betancur_17_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_18":
			dialog.text = "Не похоже, чтобы у меня был выбор, ха-ха-ха! Секунду. Они все здесь, в нижнем ящике этого шкафа.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_19_1");
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_19":
			dialog.text = "Прошу. Располагайтесь, изучайте...";
			link.l1 = "Этим и займёмся.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_20");
			AddQuestRecordInfo("WildRose_Records", "1");
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), pchar);
		break;
		
		case "WildRose_Mary_101":
			dialog.text = "Вот, "+pchar.name+", смотри, да! Джошуа и Тереза Касперы! Поверить не могу - нам удалось, удалось, да! И название корабля - 'Рэнглер'! Теперь мы можем выяснить о моём отце всё - кем он был, как тут оказался...";
			link.l1 = "Боюсь, "+npchar.name+", ты слишком торопишься... Это может оказаться не так просто, как кажется. Корабль Его Королевского Величества... Придётся подумать, кто бы мог помочь нам получить информацию из архивов Королевского Флота...";
			link.l1.go = "WildRose_Mary_102";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Mary_102":
			dialog.text = "Подумаем! Подумаем и получим, "+pchar.name+"! Самое сложное уже позади, да!";
			link.l1 = "Возможно, имеет также смысл пообщаться с мистерами Янгом и Фриддиксом. Однако, я не припомню на Острове таких людей.";
			link.l1.go = "WildRose_Betancur_20_add";
		break;
		
		case "WildRose_Betancur_20_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_21":
			dialog.text = "Потому что их тут нет, "+pchar.name+". Эти двое умерли на следующую ночь после того, как их спасли вместе с Касперами.";
			link.l1 = "Любопытно. Беременная женщина прожила ещё неделю, а два моряка с Королевского Флота скоропостижно скончались...";
			link.l1.go = "WildRose_Betancur_22";
		break;

		case "WildRose_Betancur_22":
			dialog.text = "Они и без того были плохи, как мне помнится. Сейчас я вспомнил, "+pchar.name+" - я ведь находился неподалёку от 'Церес Смити', когда их подняли на её борт... Да, я был на 'Эсмеральде' - вместе с Орели Бертин, кажется. А ещё там был Чимисет - шаман этих чёрных нехристей, зачем-то явившийся в магазин. Сперва мне показалось, что те два моряка были уже мертвы - но умерли они лишь спустя сутки...";
			link.l1 = "Что ж, ничего не поделаешь. Но мы и без того выяснили немало. Спасибо тебе за помощь, Антонио.";
			link.l1.go = "WildRose_Betancur_23";
		break;

		case "WildRose_Betancur_23":
			dialog.text = "Я тут ни при чём, "+pchar.name+". Это всё Алан, его заслуга - мало кто ещё из этих кирасиров мог бы осознать всю ценность этих записей. А ведь именно по таким документам и воссоздаётся история!";
			link.l1 = "Надеюсь, однажды мы с Мэри прочтём твои Хроники, приятель. Держи журнал, не потеряй. Ну, нам пора. Возможно, ещё увидимся, дружище.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_21");
		break;
		
		case "WildRose_Betancur_21":
			dialog.text = "Потому что их тут нет, "+pchar.name+". Эти двое умерли на следующую ночь после того, как их спасли вместе с Касперами.";
			link.l1 = "Любопытно. Беременная женщина прожила ещё неделю, а два моряка с Королевского Флота скоропостижно скончались...";
			link.l1.go = "WildRose_Betancur_22";
		break;
		
		case "WildRose_Chimiset_21":
			dialog.text = "Рад видеть тебя снова, друг мой. С чем ты пришёл ко мне?";
			link.l1 = "С просьбой, "+npchar.name+"... Вернее, с вопросом.";
			link.l1.go = "WildRose_Chimiset_22";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Chimiset_22":
			dialog.text = "Задавай свой вопрос. Или излагай просьбу. Я сделаю всё, что в моих силах, чтобы тебе помочь.";
			link.l1 = "Хорошо. Как долго ты живёшь на Острове?";
			link.l1.go = "WildRose_Chimiset_23";
		break;

		case "WildRose_Chimiset_23":
			dialog.text = "Десятки и десятки лет, мой друг. Я попал сюда ребёнком, но уже смышлёным - на борту рабовладельческого судна. Моя история мало чем отличается от многих других, что ты здесь слышал. Шквал, кораблекрушение... Английский галеон, в трюме которого я был заперт, не дотянул даже до внешнего кольца, развалившись пополам после удара об один из рифов, на который швырнула его волна.";
			link.l1 = "Как же ты уцелел? Рифы ведь достаточно далеко от внешнего кольца, и доплыть оттуда по штормовым волнам - задача, скажем прямо, не из простых...";
			link.l1.go = "WildRose_Chimiset_24";
		break;

		case "WildRose_Chimiset_24":
			dialog.text = "Боги были на моей стороне в ту ночь. Мне удалось освободиться от кандалов, а после зацепиться за обломок того, что когда-то было шлюпкой. Со мной был соплеменник, Асана - вместе мы боролись с волнами, пока не потеряли сознание от усталости.";
			link.l1 = "Вас прибило к одному из кораблей?";
			link.l1.go = "WildRose_Chimiset_25";
		break;

		case "WildRose_Chimiset_25":
			dialog.text = "Да, мы залезли в дыру в трюме... Где я снова потерял сознание, настолько был обессилен. Вернулось оно когда Асана начал вопить - его рвал на куски гигантский краб, забравшийся на тот же корабль, куда нас выбросило. А я смотрел на это и понимал, что буду следующим - оцепенев от страха и бессилия, я не мог сдвинуться с места.";
			link.l1 = "Мог бы попытаться помочь другу. Впрочем, тогда мы бы с тобой сейчас не разговаривали. Как же ты спасся?";
			link.l1.go = "WildRose_Chimiset_26_1";
			link.l2 = "Повезло тебе, что он начал не с тебя, "+npchar.name+". Как же ты спасся - прыгнул обратно в воду и поплыл прочь?";
			link.l2.go = "WildRose_Chimiset_26_2";
		break;

		case "WildRose_Chimiset_26_1":
			dialog.text = "Крики Асаны услышали несколько ривадос, вышедшие на охоту за содержимым трюмов кораблей после очередного урагана. Они окружили гадину и убили её. Асане было уже не помочь, но мне повезло куда больше. Вот так я оказался здесь. Но ответь мне теперь ты, друг мой - зачем ты хотел узнать об этом?";
			link.l1 = "На самом деле, "+npchar.name+", я собирался узнать, не как ты здесь очутился, а когда это произошло.";
			link.l1.go = "WildRose_Chimiset_27";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "WildRose_Chimiset_26_2":
			dialog.text = "Вопли Асаны услышали несколько ривадос, вышедшие на охоту за содержимым трюмов кораблей после очередного урагана. Они окружили гадину и убили её. Асане было уже не помочь, но мне повезло куда больше. Вот так я оказался здесь. Но ответь мне теперь ты, друг мой - зачем ты хотел узнать об этом?";
			link.l1 = "На самом деле, "+npchar.name+", я собирался узнать, не как ты здесь очутился, а когда это произошло.";
			link.l1.go = "WildRose_Chimiset_27";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "WildRose_Chimiset_27":
			dialog.text = "Хм-м, по вашему календарю это был 1623 год, конец лета - более точно мне сказать не под силу...";
			link.l1 = "Это и не требуется. Значит, в 1638 году ты уже пятнадцать лет как был на Острове.";
			link.l1.go = "WildRose_Chimiset_28";
		break;

		case "WildRose_Chimiset_28":
			dialog.text = "Выходит так, друг мой.";
			link.l1 = "В июне того года к внешнему кольцу ураганом прибило бриг 'Рэнглер', корабль флота Его Величества Карла I, короля Англии. Из всего экипажа выжило только четверо - в том числе, родители Мэри: Джошуа и Тереза Касперы.";
			link.l1.go = "WildRose_Chimiset_29";
		break;

		case "WildRose_Chimiset_29":
			dialog.text = "Да, я помню это, друг мой. Смутно, будто в тумане, но помню...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_29_add";
		break;
		
		case "WildRose_Chimiset_29_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_30", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_30":
			dialog.text = "Помнишь, в самом деле? Расскажи же!";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_30_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_30_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_31", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_31":
			dialog.text = "Я могу сказать немногое. Четыре человека: офицер, его жена и два матроса. Женщина была беременна, и те, кто их спасли, думали, что она не доживёт до утра - но она оказалась сильной как львица, а вот те два моряка оставили этот мир уже меньше чем через сутки... Я видел их: они были слабы, но жизненных сил у них было всё же предостаточно...";
			link.l1 = "Намекаешь на то, что их убили?";
			link.l1.go = "WildRose_Chimiset_32";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_32":
			dialog.text = "Если и так, то свидетелей этому не было, как и ран на их телах, друг мой...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_32_add";
		break;
		
		case "WildRose_Chimiset_32_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_33", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_33":
			dialog.text = "Ты сказал 'офицер', да... Мой отец в самом деле был офицером?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_33_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_33_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_34", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_34":
			dialog.text = "На нём был офицерский мундир - это, пожалуй, единственное, что я вспоминаю, когда пытаюсь вспомнить, как он выглядел.";
			link.l1 = "Если он был офицером, то ничего иного носить он и не мог - вряд ли его гардероб отличался большим разнообразием... Может, вспомнишь ещё какие-нибудь детали, "+npchar.name+"? Особые приметы... Скажем, шрам на лице или ещё какое увечье...";
			link.l1.go = "WildRose_Chimiset_35";
		break;
		
		case "WildRose_Chimiset_35":
			dialog.text = "Ничего такого я не помню, мой друг. Его лицо почти стёрлось из моей памяти - два десятка лет прошло... Но вот взгляд - его я помню очень хорошо. Я разговаривал с этим человеком лишь однажды, но взгляд его серых глаз - таких, как у Мэри - мне не забудется. В нём смешались отчаяние, страх, как у загнанной антилопы, и в то же время - ярость и решительность, достойные льва...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_35_add";
		break;
		
		case "WildRose_Chimiset_35_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_36", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_36":
			dialog.text = "Ты говорил с ним, да? О чём?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_36_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_36_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_37", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_37":
			dialog.text = "Это произошло за несколько часов до твоего рождения. Он явился сюда, на 'Протектор', и потребовал встречи со мной. Главарь ривадос, Могеди, был поражён его наглостью - но мне вдруг стал интересен этот человек. Оказавшись предо мной, он упал на колени и стал умолять спасти его жену... Кто-то, за то короткое время, что они были здесь, успел поведать ему обо мне. Я согласился, хотя Могеди и возражал...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_37_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_37_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_38", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_38":
			dialog.text = "Так значит, я обязана тебе жизнью?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_38_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_38_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_39", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_39":
			dialog.text = "Нет смысла обманывать - мы успели добраться до твоей матери, но слишком поздно: нарвалы отказывались пускать меня на 'Церес Смити'. Твоему отцу удалось их... убедить, но бедную Терезу я увидел лишь на её последнем издыхании. Она успела родить тебя, и, появись я раньше, может, и спас бы ей жизнь, но...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_39_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_39_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_40", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_40":
			dialog.text = "Мама умерла, да.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_40_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_40_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_41", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_41":
			dialog.text = "Увы. Она взглянула на тебя и испустила дух, но перед этим, словно собравшись с силами, позвала какого-то Руперта. Выкрикнула во всё горло его имя, словно звала на помощь - и умерла.";
			link.l1 = "Руперта? Не Джошуа?";
			link.l1.go = "WildRose_Chimiset_42";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_42":
			dialog.text = "Пока я вам это рассказывал, мой друг, я будто заново пережил ту минуту. Я никогда этого не забуду - ни её предсмертного крика, ни её искажённого страданием лица. И да, последнее, что сорвалось с её уст - было именно 'Руперт'.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_42_add";
		break;
		
		case "WildRose_Chimiset_42_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_43", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_43":
			dialog.text = "Она была красивой, моя мама? Ты можешь описать, как она выглядела, Чимисет?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_43_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_43_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_44", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_44":
			dialog.text = "В этом нет смысла, Мэри. Тебе достаточно взглянуть в зеркало - вы с ней похожи как две капли воды. Лишь глаза достались тебе от отца.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_44_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_44_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_45", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_45":
			dialog.text = "А он, что стало с ним? Нам удалось выяснить, что через несколько дней после моего рождения он словно в воду канул, да! Но его же не убили, так ведь?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_45_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_45_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_46", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_46":
			dialog.text = "Как только ему сообщили о том, что Тереза при смерти, Джошуа пришёл в настоящую ярость - я готов поклясться, что даже львы в саванне не атаковали с такой злостью добычу, с какой бросился твой отец на тех нарвалов, что не пускали меня на флейт... Потребовалось полдюжины человек, чтобы скрутить его - после того, как он сбросил в воду двух бойцов клана в полном обмундировании.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_46_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_46_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_47", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_47":
			dialog.text = "И что с ним сделали - скажи, ну же!";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_47_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_47_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_48", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_48":
			dialog.text = "Его бросили в одну из камер на 'Тартарусе'. Судить его никто не взялся - хотели, чтобы эта история прежде утихла... Почти все ему сочувствовали, но и жить с таким человеком бок о бок желали немногие. Исчез Джошуа спустя несколько дней - тогда же с Острова отбыли несколько баркасов контрабандистов. В лодках его никто не видел - это и породило слухи о его смерти.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_48_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_48_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_49", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_49":
			dialog.text = "Значит, ты веришь, что он жив, да?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_49_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_49_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_50", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_50":
			dialog.text = "Я скажу лишь то, что вам уже наверняка скажут и другие - его тела никто не находил. Может, он всё же спрятался на дне одной из лодок, а может, ему перерезали горло в той камере и скормили крабам...";
			link.l1 = "То, что он исчез одновременно с отплытием этих барыг, говорит, скорее, в пользу первого - таких совпадений не бывает. И, быть может, он обмолвился кому о своих планах? Если он бежал, то бежал, оставив здесь новорождённую дочь, что, по-своему, вполне разумно - младенец мог и не выдержать плавания до берегов Кубы в утлом челне... Но он наверняка собирался за ней вернуться.";
			link.l1.go = "WildRose_Chimiset_51";
		break;
		
		case "WildRose_Chimiset_51":
			dialog.text = "Мне это неведомо, друг мой. Если Джошуа Каспер и разговаривал с кем в те дни, то разве что со своими тюремщиками - но все они давным-давно покинули этот грешный мир. Ах да, в один из дней к нему явился падре Доминго - он был у белых за священника до брата Юлиана...";
			link.l1 = "Он что, решил исповедаться? Видать, боялся умереть во время побега.";
			link.l1.go = "WildRose_Chimiset_52";
		break;

		case "WildRose_Chimiset_52":
			dialog.text = "Я не в силах пролить свет на то, чего не знаю, мой друг. Да и Доминго вам тоже уже ничего не расскажет - утонул лет пятнадцать уж как. То ли по голове кто дал, то ли просто напился - это дело он любил...";
			link.l1 = "Но, может, Доминго вёл дневник... или рассказывал о том разговоре с Джошуа брату Юлиану?";
			link.l1.go = "WildRose_Chimiset_52_add";
		break;
		
		case "WildRose_Chimiset_52_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_53", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_53":
			dialog.text = "Надо поговорить с ним, "+pchar.name+", да. И поскорее. Я не хочу даже думать о возвращении на корабль, пока мы с этим не разберёмся.";
			link.l1 = "Если есть в чём ещё разбираться. Юлиан может об этом и не знать - но мы это обязательно выясним. Спасибо тебе, Чимисет.";
			link.l1.go = "WildRose_Chimiset_53_add";
		break;
		
		case "WildRose_Chimiset_53_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_54", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_54":
			dialog.text = "Я всегда к твоим услугам, друг мой. Но позволь мне дать вам обоим совет.";
			link.l1 = "И какой же?";
			link.l1.go = "WildRose_Chimiset_55";
		break;
		
		case "WildRose_Chimiset_55":
			dialog.text = "Будучи на охоте, не забредайте слишком глубоко в заросли - можете оттуда и не выбраться.";
			link.l1 = "Мы будем помнить об этом, шаман. А теперь - прощай.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_22");
		break;
		
		case "WildRose_Julian_1":
			dialog.text = "Приветствую вас под сенью обители Божьей, дети мои. Решили исповедаться или просто хотите помолиться?";
			link.l1 = "Здравствуйте, брат Юлиан. Боюсь, перечисление наших грехов займёт слишком много времени - которого у нас, увы, нет. Но будьте уверены - мы, как добрые католики, посещаем церковь в каждом порту.";
			link.l1.go = "WildRose_Julian_2_1";
			link.l2 = "Приветствуем, брат Юлиан. Молитвой Господу нашему мы, как добрые католики, день начинаем и ею же его и заканчиваем.";
			link.l2.go = "WildRose_Julian_2_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Julian_2_1":
			dialog.text = "Добрые католики, живущие вне брака под одной крышей... Такое сродни богохульству, сын мой. А это, напомню, смертный грех!";
			link.l1 = "А разве не сказано в Писании, что любовь покрывает все грехи?";
			link.l1.go = "WildRose_Julian_3";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "WildRose_Julian_2_2":
			dialog.text = "Добрые католики, живущие вне брака под одной крышей... Такое сродни богохульству, сын мой. А это, напомню, смертный грех!";
			link.l1 = "А разве не сказано в Писании, что любовь покрывает все грехи?";
			link.l1.go = "WildRose_Julian_3";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Julian_3":
			dialog.text = "Любовь состоит в том, чтобы мы поступали по заповедям Его - нужно ли мне напомнить их тебе, сын мой?";
			link.l1 = "Как-нибудь в другой раз. Мы здесь по другому делу.";
			link.l1.go = "WildRose_Julian_4";
		break;

		case "WildRose_Julian_4":
			dialog.text = "Заблудшим душам никогда не поздно вернуться на путь истинный... Но я слушаю вас, дети мои.";
			link.l1 = "Мы и в самом деле малость заблудились, брат Юлиан. В дебрях прошлого. И, надеемся, в ваших силах помочь нам найти путь к свету.";
			link.l1.go = "WildRose_Julian_5";
		break;

		case "WildRose_Julian_5":
			dialog.text = "Очень остроумно, сын мой. Тебе следует помнить, что не человек ведёт к свету, но Господь - и, следуя за Ним, помни, что неисповедимы пути Его.";
			link.l1 = "Буду краток, брат Юлиан. Мы пытаемся разузнать всё возможное о родителях Мэри. С её матерью, Терезой, всё более или менее ясно - она попала на Остров вместе с мужем и спустя неделю умерла при родах. А вот отец... Он исчез спустя несколько дней после рождения Мэри, сбежав при этом с 'Тартаруса'. По слухам, последним человеком, с которым он общался здесь, был падре Доминго - ваш предшественник.";
			link.l1.go = "WildRose_Julian_6";
		break;

		case "WildRose_Julian_6":
			dialog.text = "Тогда вы опоздали более чем на полтора десятилетия, дети мои.";
			link.l1 = "Да, мы знаем, что падре погиб достаточно давно. И тогда вы, брат Юлиан, были ещё слишком молоды, чтобы оказаться на Острове в соответствующем сане, так ведь?";
			link.l1.go = "WildRose_Julian_7";
		break;

		case "WildRose_Julian_7":
			dialog.text = "Я очутился здесь спустя несколько лет после его смерти. Мне стоило большого труда привести здесь, на этом судне, всё в порядок, но с Божьей помощью я справился, сын мой.";
			link.l1 = "Когда вы здесь разбирались, не находили ли вы каких-либо записей падре Доминго?";
			link.l1.go = "WildRose_Julian_8";
		break;

		case "WildRose_Julian_8":
			dialog.text = "Вы имеете в виду что-то конкретное, сын мой?";
			link.l1 = "Нас интересуют дневники или какие-нибудь учётные книги... Надежды на чудо мало, но падре мог оставить содержание того разговора в одной из своих записей. Мы предполагаем, что отец Мэри покинул остров на одном из баркасов контрабандистов - может, он намекнул падре, куда собирается направиться и когда вернётся за дочерью?";
			link.l1.go = "WildRose_Julian_9";
		break;

		case "WildRose_Julian_9":
			dialog.text = "Дневников или чего-то на них похожего я не находил совершенно точно, а вот разнообразные записи... По части ведения церковных дел он был достаточно скрупулёзен - не каждого раба своего Господь одаривает такой педантичностью. Но его бумаги содержат лишь сухие цифры да имена - и ничего более.";
			link.l1 = "Насколько нам удалось выяснить, Джошуа Каспер - именно так его звали - в порыве гнева, вызванного смертью жены, убил двоих членов клана 'Нарвал', отказавшихся пустить колдуна ривадос Чимисета к матери Мэри...";
			link.l1.go = "WildRose_Julian_10";
		break;

		case "WildRose_Julian_10":
			dialog.text = "Они поступили как дети истинной церкви! По этому слуге Диавола плачут подвалы Инквизиции!";
			link.l1 = "Господь, думаю, ужаснулся бы - узнав, сколько людей было замучено во имя Его. Касперу повезло больше - его бросили в камеру на 'Тартарусе', но до приговора дело не дошло.";
			link.l1.go = "WildRose_Julian_11_1";
			link.l2 = "Да-да, несомненно. Каспера бросили в одну из камер 'Тартаруса', но приговора вынесено не было - не все осудили поступок мужа, потерявшего жену.";
			link.l2.go = "WildRose_Julian_11_2";
		break;

		case "WildRose_Julian_11_1":
			dialog.text = "Что было дальше - этот еретик сбежал?";
			link.l1 = "Меньше чем через неделю Джошуа исчез. А в ночь перед этим его навестил падре Доминго. Возникает вопрос - зачем? Вряд ли протестант, коим наверняка был Каспер, стал бы исповедоваться католическому священнику - как считаете?";
			link.l1.go = "WildRose_Julian_12";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Julian_11_2":
			dialog.text = "Что было дальше - этот еретик сбежал?";
			link.l1 = "Меньше чем через неделю Джошуа исчез. А в ночь перед этим его навестил падре Доминго. Возникает вопрос - зачем? Вряд ли протестант, коим наверняка был Каспер, стал бы исповедоваться католическому священнику - как считаете?";
			link.l1.go = "WildRose_Julian_12";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Julian_12":
			dialog.text = "Никогда не поздно обратиться к истинной вере, сын мой. Но ты мыслишь верно. Если ему была нужна не исповедь, то, возможно, он обсуждал с падре отпевание жены - если, конечно, она была католичкой. Или же крестины дочери, а вернее, отказ от них, ведь протестанты младенцев не крестят, считая, что человек должен принять решение о крещении самостоятельно и сознательно.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_12_add";
		break;
		
		case "WildRose_Julian_12_add":
			StartInstantDialog("Mary", "WildRose_Julian_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Julian_13":
			dialog.text = "Но меня крестили, брат Юлиан. Эрик Удетт говорил мне об этом.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_13_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_13_add":
			StartInstantDialog("Julian", "WildRose_Julian_14", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_14":
			dialog.text = "То лишь мои домыслы, дочь моя. Истина мне неведома. Господь открывает нам глаза лишь на то, что по-настоящему важно и нужно.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_14_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_14_add":
			StartInstantDialog("Mary", "WildRose_Julian_15", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_15":
			dialog.text = "И для меня так оно и есть, да. Может, на страницах записей падре Доминго всё же осталось что-то, чего вы не заметили, брат Юлиан? Ведь вы просто пролистывали их, не так ли?";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_15_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_15_add":
			StartInstantDialog("Julian", "WildRose_Julian_16", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_16":
			dialog.text = "Мне нечего было там искать, дочь моя. Я вижу, что вы давно и тщательно занимаетесь этим делом - Господь ведёт вас этой тернистой дорогой. Если тебе суждено найти то, что ты ищешь, такова воля Его, и не мне ей противиться. Я могу дать вам записи Доминго за год твоего рождения, возможно, в них вы обнаружите что-то полезное.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_16_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_16_add":
			StartInstantDialog("Mary", "WildRose_Julian_17", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_17":
			dialog.text = "Это было бы весьма великодушно с вашей стороны, брат Юлиан. Сохранились ли записи за 1638 год?";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_17_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;
		
		case "WildRose_Julian_17_add":
			StartInstantDialog("Julian", "WildRose_Julian_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Julian_18":
			dialog.text = "Так-так... (сдувает пыль). Кажется, вот оно. Учётная книга за 1638 год от Рождества Христова.";
			link.l1 = "Позвольте, брат Юлиан...";
			link.l1.go = "exit";
			AddQuestRecordInfo("WildRose_Records_2", "1");
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_23");
		break;
		
		case "WildRose_Mary_111":
			dialog.text = "Гляди, "+pchar.name+": 3 августа. В этот день крестили меня и Фабиана. А родилась я 22 июня. Но о моём отце ни слова, да.";
			link.l1 = "Всё, как и говорил брат Юлиан - сухие цифры да имена. Что интересно, падре Доминго настолько преисполнился в своём усердии, что отпевал даже протестантов - вряд ли ван Эккус, Янг и Фриддикс были католиками.";
			link.l1.go = "WildRose_Mary_111_add";
			DelLandQuestMark(npchar);
		break;
		
		case "WildRose_Mary_111_add":
			StartInstantDialog("Julian", "WildRose_Mary_112", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_112":
			dialog.text = "Они вполне могли обратиться к истинной вере на пороге вступления в Царство Божие, сын мой.";
			link.l1 = "Разумеется, брат Юлиан - чем же им ещё было заниматься? Особенно если они погибли как Соррен и Рохас - полагаю, это те самые нарвалы, которые преградили путь Чимисету.";
			link.l1.go = "WildRose_Mary_112_add";
		break;
		
		case "WildRose_Mary_112_add":
			StartInstantDialog("Mary", "WildRose_Mary_113", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_113":
			dialog.text = "Лучше бы падре Доминго полностью прописывал вторые имена, да. Что вот значат эти «В.» и «Дж.» после имён моей мамы и меня?";
			link.l1 = "А кто такой этот Фабиан, что был крещён с тобой в один день?";
			link.l1.go = "WildRose_Mary_114";
		break;
		
		case "WildRose_Mary_114":
			dialog.text = "Сын Сесиль Галард. Ох, только сейчас вспомнила! Она вскормила меня, хотя и никогда не относилась с особой теплотой. Наверняка потому что я выжила, а Фабиан - нет. Он умер спустя несколько месяцев после рождения, да.";
			link.l1 = "Возможно, стоит пообщаться с ней, коль уж из этой книжонки мы не почерпнули почти ничего полезного - если, конечно, не считать дат твоего рождения и крещения.";
			link.l1.go = "WildRose_Mary_115";
		break;

		case "WildRose_Mary_115":
			dialog.text = "Она не сильно моложе Орели, "+pchar.name+". Остаётся лишь надеяться, что хотя бы у неё всё в порядке с головой. Но что ты собираешься у неё выяснить?";
			link.l1 = "Ну, раз уж она была твоей кормилицей - вполне могла знать от падре Доминго какие-то подробности его разговора с Джошуа. Кому, как не ей, он мог это рассказать? Возможно, ещё Орели или Эрику. Но, сдаётся мне, из первой мы выжали всё что могли, а второй уже никому ничего не скажет.";
			link.l1.go = "WildRose_Mary_115_add";
		break;
		
		case "WildRose_Mary_115_add":
			StartInstantDialog("Julian", "WildRose_Mary_116", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_116":
			dialog.text = "Эта добрая женщина - верная прихожанка этой обители Божьей. Не пропускает ни одной мессы и регулярно исповедуется. Думаю, она и в самом деле может помочь вам, дети мои.";
			link.l1 = "Спасибо вам, отец. Прощайте.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_24");
		break;
		
		case "WildRose_Sesil_1":
			dialog.text = ""+GetFullName(pchar)+" и Мэри Каспер. Какая приятная встреча!";
			link.l1 = "Взаимно, "+npchar.name+". Мы, собственно, к вам. Хотели бы с вами кое-что обсудить.";
			link.l1.go = "WildRose_Sesil_2";
			DelLandQuestMark(npchar);
			LAi_SetStayType(npchar);
		break;
		
		case "WildRose_Sesil_2":
			dialog.text = "Вот как? Что ж, я вся внимание.";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_2_add";
		break;
		
		case "WildRose_Sesil_2_add":
			StartInstantDialog("Mary", "WildRose_Sesil_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Sesil_3":
			dialog.text = "Это касается моих родителей, Сесиль. О моей маме всё, что могли, мы уже выяснили... Она умерла сразу после моего появления на свет. Но отец... он бесследно исчез через несколько дней. Мы склонны думать, что он не погиб, да.";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_3_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_3_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_4", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_4":
			dialog.text = "Да уж, такого человека, как он, отправить на тот свет надо было постараться...";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_4_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_4_add":
			StartInstantDialog("Mary", "WildRose_Sesil_5", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_5":
			dialog.text = "Ты видела его?! Общалась с ним?";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_5_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_6":
			dialog.text = "Девочка моя, я видела, как он разобрался с двумя нарвалами чуть ли не голыми руками...";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_6_add":
			StartInstantDialog("Mary", "WildRose_Sesil_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_7":
			dialog.text = "Сорреном и Рохасом?";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_7_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_8":
			dialog.text = "У меня и тогда дел было по горло, чтобы запоминать имена этих проходимцев - а сейчас я их и вовсе не вспомню.";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_8_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_8_add":
			StartInstantDialog("Mary", "WildRose_Sesil_9", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_9":
			dialog.text = "Ладно, это неважно. Продолжай, пожалуйста, Сесиль.";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_9_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_9_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_10", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_10":
			dialog.text = "А что продолжать? Скинул он в воду тех двоих, они на дно камнем пошли, его же скрутили да на 'Тартарус' увели. И правильно сделали - мало ли кого ещё этот головорез решил бы утопить...";
			link.l1 = "Головорез? Как-то грубовато - не находите, миссис Галард? Мы говорим о человеке, об офицере, только что потерявшем жену...";
			link.l1.go = "WildRose_Sesil_11_1";
			link.l2 = "Вижу, вы о нём не самого высокого мнения - не о каждом офицере такое скажут.";
			link.l2.go = "WildRose_Sesil_11_2";
		break;

		case "WildRose_Sesil_11_1":
			dialog.text = "Офицере, ну-ну. Мундир-то у него был знатный, как сейчас помню. Чуть ли не с иголочки. Но я повидала многих офицеров, молодой человек. И все они вели себя куда достойнее этого... господина.";
			link.l1 = "Он сделал что-то ещё? Кроме убийства тех двоих?";
			link.l1.go = "WildRose_Sesil_12";
			ChangeCharacterComplexReputation(pchar, "honor", 1);
		break;

		case "WildRose_Sesil_11_2":
			dialog.text = "Офицере, ну-ну. Мундир-то у него был знатный, как сейчас помню. Чуть ли не с иголочки. Но я повидала многих офицеров, молодой человек. И все они вели себя куда достойнее этого... господина.";
			link.l1 = "Он сделал что-то ещё? Кроме убийства тех двоих?";
			link.l1.go = "WildRose_Sesil_12";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Sesil_12":
			dialog.text = "Он потребовал к себе в камеру священника - падре Де ла Круса...";
			link.l1 = "Ну надо же! Как раз об этом мы и хотели с вами поговорить. Вам известны подробности того разговора?";
			link.l1.go = "WildRose_Sesil_13";
		break;

		case "WildRose_Sesil_13":
			dialog.text = "Ну ещё бы, молодой человек! Этот негодяй-протестант потребовал от падре не крестить его дочь - даром, что её мать была ирландкой, то есть католичкой.";
			link.l1 = "Чуть ли не впервые слышу, чтобы англичанка так отзывалась о протестанте... Кхм, простите, что перебил, миссис "+npchar.lastname+".";
			link.l1.go = "WildRose_Sesil_14";
		break;

		case "WildRose_Sesil_14":
			dialog.text = "Когда-то я и сама была протестанткой, чего уж греха таить. Но брат Юлиан сумел наставить меня на путь истинный.";
			link.l1 = "Вот оно как... Воистину способный служитель Господень. Но мы отвлеклись. Значит, Каспер хотел, чтобы его дочь росла в протестантской вере.";
			link.l1.go = "WildRose_Sesil_15";
		break;

		case "WildRose_Sesil_15":
			dialog.text = "Именно так он и заявил нашему падре Де ла Круз. А ещё - приказал назвать девочку Джулией...";
			link.l1 = "Так вот, что значит эта 'Дж.'. Мэри Джулия Каспер... Но почему её тогда назвали Мэри?";
			link.l1.go = "WildRose_Sesil_16";
		break;

		case "WildRose_Sesil_16":
			dialog.text = "Потому что так хотела её мать, вот почему. Когда девочку достали из её утробы, она прошептала имя - Мэри. Я тому свидетелем не была, а вот Орели Бертин при родах присутствовала. Можете спросить у неё, если хотите...";
			link.l1 = "Значит, учли именно желание матери.";
			link.l1.go = "WildRose_Sesil_17";
		break;

		case "WildRose_Sesil_17":
			dialog.text = "А разве должно было быть иначе - ведь горе-папаша как сквозь землю провалился?";
			link.l1 = "Учитывая... таланты падре Де ла Круз, сомневаюсь, что мнение отца было бы учтено, даже останься он сидеть сиднем на 'Тартарусе'. Доминго не делился с вами - он не был в курсе планов Каспера касательно побега и возможного возвращения за девочкой?";
			link.l1.go = "WildRose_Sesil_18_1";
			link.l2 = "Пожалуй, вы правы. Но возвращаясь к разговору падре Доминго с мистером Каспером - священник не упоминал, может, Джошуа обсуждал с ним побег и возможные сроки своего возвращения за дочерью?";
			link.l2.go = "WildRose_Sesil_18_2";
		break;

		case "WildRose_Sesil_18_1":
			dialog.text = "Ни о чём таком он не рассказывал. Да и посудите сами, "+npchar.name+", собирайся вы сбежать из тюрьмы, стали бы вы рассказывать об этом первому встречному? Тот тип определённо не стал бы, так я вам скажу.";
			link.l1 = "Значит, и эта ниточка привела нас в никуда. Что ж, спасибо вам за уделённое время, миссис "+npchar.lastname+". Ещё увидимся.";
			link.l1.go = "WildRose_Sesil_19";
			ChangeCharacterComplexReputation(pchar, "honor", -1);
			AddCharacterExpToSkill(pchar, "charisma", 100);
		break;

		case "WildRose_Sesil_18_2":
			dialog.text = "Ни о чём таком он не рассказывал. Да и посудите сами, "+npchar.name+", собирайся вы сбежать из тюрьмы, стали бы вы рассказывать об этом первому встречному? Тот тип определённо не стал бы, так я вам скажу.";
			link.l1 = "Значит, и эта ниточка привела нас в никуда. Что ж, спасибо вам за уделённое время, миссис "+npchar.lastname+". Ещё увидимся.";
			link.l1.go = "WildRose_Sesil_19";
			ChangeCharacterComplexReputation(pchar, "honor", 1);
		break;
		
		case "WildRose_Sesil_19":
			StartInstantDialog("Mary", "WildRose_Mary_121", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_121":
			dialog.text = "Мы выяснили немало интересного, "+pchar.name+". Но практически не продвинулись вперёд, да.";
			link.l1 = "И даже малость запутались. Кто, интересно, этот Руперт, к которому твоя мать взывала перед смертью?";
			link.l1.go = "WildRose_Mary_122";
		break;

		case "WildRose_Mary_122":
			dialog.text = "Может, брат или... близкий друг?";
			link.l1 = "Друг, говоришь, ну-ну... Интересно, знал ли о нём Джошуа...";
			link.l1.go = "WildRose_Mary_123";
		break;

		case "WildRose_Mary_123":
			dialog.text = "На что это ты намекаешь, "+pchar.name+"?";
			link.l1 = "На то, что всё это нужно хорошенько обдумать. Благо, у нас будет на это полно времени, пока будем мы будем искать того, кто может помочь нам в поисках. Мы проделали большую работу. Но до конца пока что не добрались. Нам самим в канцелярию Королевского Флота хода нет, да и находится она за океаном, в Лондоне... Есть идеи, кто может нам в этом вопросе подсобить?";
			link.l1.go = "WildRose_Mary_127";
		break;
		
		case "WildRose_Mary_127":
			dialog.text = "Как насчёт Сержа Бенуа, Шарль?";
			link.l1 = "Аббат? У него большие связи, это верно, но добраться до архивов Королевского флота он вряд ли сможет.";
			link.l1.go = "WildRose_Mary_128";
		break;
		
		case "WildRose_Mary_128":
			dialog.text = "Не сможет сам - возможно, сведёт нас с тем, кому это под силу, да.";
			link.l1 = "Пожалуй, что так. Значит, курс на Сен-Пьер.";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_25");
		break;
		
		// =================================================================
		// =================== ЭТАП 3. «БУМАЖНАЯ РАБОТА» ===================
		// =================================================================
		
		case "WildRose_Mary_131":
			dialog.text = "Что ж, теперь нам остаётся только ждать, да.";
			link.l1 = "Уверен, он всё разузнает, "+npchar.name+". Время пролетит быстро, ты и не заметишь. А пока что - нам есть чем заняться.";
			link.l1.go = "WildRose_Mary_132";
		break;

		case "WildRose_Mary_132":
			dialog.text = "Ты намекаешь на что-то конкретное, любимый?";
			link.l1 = "У нас куча дел, но почему нам сейчас не вернуться на корабль, запереть дверь и уделить время друг другу? Что скажешь?";
			link.l1.go = "WildRose_Mary_133";
		break;

		case "WildRose_Mary_133":
			dialog.text = "А я знала, что ты это предложишь, да! Скажу вот что: не станем терять времени!";
			link.l1 = "Идём же, моя ненаглядная.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_3");
		break;
		
		case "WildRose_Mary_134":
			dialog.text = "Ох, "+pchar.name+", ты не представляешь, просто не представляешь, какой груз только что упал с моей души, да!";
			link.l1 = "Очень даже представляю, дорогая - ты вся буквально светишься, ха-ха! Как видишь, всё было не зря.";
			link.l1.go = "WildRose_Mary_135";
		break;

		case "WildRose_Mary_135":
			dialog.text = "Мой отец был прославленным офицером, подумать только! Но до чего же жаль, что нам так и не довелось встретиться. И ведь мы так и не узнали, добрался ли он до Большой земли, да...";
			link.l1 = "Случись это, он наверняка вернулся бы на службу, и где-то что-то о нём бы да услышали. Вряд ли такой человек спокойно усидел бы на одном месте - иначе, от кого это в тебе?";
			link.l1.go = "WildRose_Mary_136";
		break;

		case "WildRose_Mary_136":
			dialog.text = "Ты действительно думаешь, что он погиб? Оказался в руках испанцев на Кубе, или вовсе был убит на Острове Справедливости?";
			link.l1 = "Я стараюсь трезво смотреть правде в глаза, "+npchar.name+". В те годы с Островом существовало какое-никакое сообщение, контрабандисты ходили туда на своих тартанах с завидным постоянством. Сумей он покинуть Остров, не сомневаюсь, какое-то время спустя он вернулся бы туда за тобой.";
			link.l1.go = "WildRose_Mary_137";
		break;

		case "WildRose_Mary_137":
			dialog.text = "Чтобы забрать меня оттуда. Но тогда бы мы не встретились с тобой, да.";
			link.l1 = "Такова жизнь, дорогая. Никогда не знаешь, где найдёшь, а где потеряешь. Надеюсь, ты не жалеешь, что находишься со мной здесь и сейчас.";
			link.l1.go = "WildRose_Mary_138";
		break;

		case "WildRose_Mary_138":
			dialog.text = "В жизни не слышала большей глупости, да! "+pchar.name+", ты самый лучший, ты замечательный! Спасибо тебе, что приложил столько усилий, чтобы помочь мне выяснить всё это. Это так для меня важно, да! Но давай изучим документы - может, почерпнём из него что-то, чего нам не рассказал наш друг...";
			link.l1 = "Хорошая мысль. Прямо сейчас и начнём.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_7");
		break;
		
		case "WildRose_Mary_139":
			dialog.text = "Ну, "+pchar.name+", заметил что-нибудь интересное?";
			link.l1 = "Да, "+npchar.name+". Кое-что есть...";
			link.l1.go = "WildRose_Mary_140";
		break;

		case "WildRose_Mary_140":
			dialog.text = "Ты как будто привидение увидел, да.";
			link.l1 = "Здесь упоминается некий Руперт Нортвуд.";
			link.l1.go = "WildRose_Mary_141";
		break;

		case "WildRose_Mary_141":
			dialog.text = "Руперт Нортвуд?! Неужели - тот самый?";
			link.l1 = "Тише, "+npchar.name+" - не кричи так. Хм-м... Думаю, что да - это тот человек, о котором говорил Чимисет. Иначе и быть не может - таких совпадений не бывает.";
			link.l1.go = "WildRose_Mary_142";
		break;

		case "WildRose_Mary_142":
			dialog.text = "И что ты обо всём этом думаешь, "+pchar.name+"?";
			link.l1 = "Эта история начинает становиться всё запутанней. Получается... из Плимута отчалил 'Корнуэлл', на Антигуа прибыл также 'Корнуэлл', а на рифах Острова Справедливости разбился уже 'Рэнглер' - всё с тем же Джошуа Каспером во главе, который ухитрился втайне от Адмиралтейства вступить в брак с женщиной, которая в предсмертных муках взывала к некоему Руперту.";
			link.l1.go = "WildRose_Mary_143";
		break;

		case "WildRose_Mary_143":
			dialog.text = "Ничего не понимаю. Я даже не знаю, кто ещё способен пролить на него хоть какой-то свет. Чем больше мы пытаемся выяснить о моём отце, тем больше утопаем в болоте из всё новых и новых тайн и секретов, да.";
			link.l1 = "Если кто и способен хоть что либо прояснить - то это либо Джошуа Каспер, либо Руперт Нортвуд.";
			link.l1.go = "WildRose_Mary_144";
		break;

		case "WildRose_Mary_144":
			dialog.text = "Нортвуд? Но ведь он погиб, да. Ты же не думаешь, что отчёт, составленный по прибытии 'Корнуэлла' в Сент-Джонс, содержит ложные сведения?";
			link.l1 = "Ох уж эта твоя наивность, "+npchar.name+"... Я начинаю думать, что вся эта история буквально насквозь пропитана ложью. Подумай сама: Джошуа Каспер был образцовым офицером - множество наград и ни единого взыскания. Как-то не вяжется это с тем, что мы разузнали о нём на Острове Справедливости, где он, не колеблясь, отправил к праотцам двух человек, не находишь?";
			link.l1.go = "WildRose_Mary_145";
		break;

		case "WildRose_Mary_145":
			dialog.text = "Он бился за жизнь своей жены, моей матери, "+pchar.name+"!";
			link.l1 = "Безусловно, но давай подумаем, откуда она вообще взялась? Как и, главное - зачем он скрыл от Адмиралтейства свою женитьбу? Служака до мозга костей, верный уставу и долгу офицер - а иначе его дело не сверкало бы такой белизной - и вдруг такая выходка.";
			link.l1.go = "WildRose_Mary_146";
		break;

		case "WildRose_Mary_146":
			dialog.text = "А вдруг за этим скрывается какая-нибудь красивая и романтичная история? Так ведь, пусть и редко, но бывает, да.";
			link.l1 = "Не пойми меня не правильно, Мэри, но всё это не похоже на романтическую историю. Скорее уж, на какой-то спектакль, который опять же непонятно зачем был разыгран. Зачем было переименовывать корабль по пути на Провиденс? Это ведь военное судно - за такие шалости можно и под трибунал попасть.";
			link.l1.go = "WildRose_Mary_147";
		break;

		case "WildRose_Mary_147":
			dialog.text = "Согласна - хороший вопрос.";
			link.l1 = "Да и с этим Рупертом Нортвудом явно что-то нечисто. В сражении полегла чуть ли не половина команды, но, что удивительно, ни одного офицера, кроме него. И почему твоя мать перед смертью взывала именно к Руперту, а не к своему мужу Джошуа?";
			link.l1.go = "WildRose_Mary_148";
		break;

		case "WildRose_Mary_148":
			dialog.text = "Значит, ты всё же уверен в том, что старпом не погиб в бою с испанцами, так? И я дочь вовсе не Джошуа Каспера, а Руперта Нортвуда - ты к этому ведёшь?";
			link.l1 = "Как я уже говорил - истина известна только одному человеку. Либо Джошуа Касперу, который за каким-то образом назвал Терезу своей женой, либо же Руперту Нортвуду, который также непонятно с каких побуждений назвался именем своего капитана.";
			link.l1.go = "WildRose_Mary_149";
		break;

		case "WildRose_Mary_149":
			dialog.text = "Ну и дьявольщина, да! И как же нам теперь быть, "+pchar.name+"? Теперь я ещё больше хочу докопаться до истины, но мы и без того уже выжали из всех всё, что только могли.";
			link.l1 = "Если где и лежат ответы, то на Острове Справедливости - больше нигде не осталось людей, разве что за океаном, которые были, пусть и мимолётно, но знакомы с твоими родителями. Думаю, стоит ещё раз поговорить с Орели Бертин - возможно, она вспомнит что-нибудь ещё, за что мы сможем уцепиться.";
			link.l1.go = "WildRose_Mary_150";
		break;

		case "WildRose_Mary_150":
			dialog.text = "Но что ты хочешь у неё выяснить? Кажется, она и так рассказала нам всё, что знала.";
			link.l1 = "Она рассказала о том, что мы у неё спрашивали, и вполне могла упустить какую-нибудь важную деталь. Может, у твоего отца был шрам на лице, или на руке отсутствовал один из пальцев... Сомневаюсь, что человек, который измыслил все эти трюки со сменой названия корабля и, возможно, собственного имени, мог бесславно сгинуть на острове или в подвалах кастильцев.";
			link.l1.go = "WildRose_Mary_151";
		break;

		case "WildRose_Mary_151":
			dialog.text = "Пожалуй, ты прав...";
			link.l1 = "И если мы решим продолжить поиски - теперь уже не на пыльных полках Адмиралтейства, а здесь, на Архипелаге, нам понадобится нечто большее, чем просто имя, да ещё и ненастоящее.";
			link.l1.go = "WildRose_Mary_152";
		break;

		case "WildRose_Mary_152":
			dialog.text = "Знаешь, у меня от всего этого мурашки по коже, да. То ли оттого, насколько всё это... захватывающе, то ли от мысли, что мой отец мог не сильно отличаться от того ублюдка с плантации Бишопа.";
			link.l1 = "Как бы то ни было, обещаю, мы сделаем всё возможное, чтобы во всём разобраться. Так что, не станем терять времени. В путь!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_9");
		break;
		
		// =================================================================
		// ==================== ЭТАП 4. «ПУТЬ К СВЕТУ» =====================
		// =================================================================
		case "WildRose_Mary_161":
			dialog.text = "Пойдём же, "+pchar.name+", не станем попусту тратить время, да.";
			link.l1 = "Надеюсь, Орели у себя в каюте, и нам не придётся в её поисках обшаривать весь Остров...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_2");
		break;
		
		case "WildRose_Mary_162":
			dialog.text = "Похоже, нам снова не повезло, да. И куда она только могла подеваться?";
			link.l1 = "Надеюсь, болезнь не обрела вновь власть над её разумом...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_4");
		break;
		
		case "WildRose_Jillian_31":
			dialog.text = "А, вы снова здесь. Ну, здравствуйте... В чём дело, вам снова нужна Орели?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_31_add";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Jillian_31_add":
			StartInstantDialog("Mary", "WildRose_Jillian_32", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_32":
			dialog.text = "В сообразительности тебе не откажешь, Джиллиан. Не знаешь случаем, где она?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_32_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_32_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_33", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_33":
			dialog.text = "В церкви, собиралась исповедаться. Если поспешите, то найдёте её там.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_33_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_33_add":
			StartInstantDialog("Mary", "WildRose_Jillian_34", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_34":
			dialog.text = "Ну, раз уж она исповедуется, значит, точно в здравом уме и твёрдой памяти, да.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_34_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_34_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_35", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_35":
			dialog.text = "Сложно сказать... Последние три дня она сама не своя, места себе не находит. Знаете, она отчего-то страшно взволновалась, как увидела мачты вашего корабля за внешним кольцом.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_35_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_35_add":
			StartInstantDialog("Mary", "WildRose_Jillian_36", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_36":
			dialog.text = "Интересно, с чего бы это?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_36_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_36_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_37", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_37":
			dialog.text = "Ну, наверное, ей претит мысль о том, что она может подвергнуться новым расспросам от тебя. Но когда тебя волновали чужие проблемы, верно?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_37_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_37_add":
			StartInstantDialog("Mary", "WildRose_Jillian_38", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_38":
			dialog.text = "Не смей разговаривать со мной в таком тоне, Джиллиан. На этот раз я тебя прощу, но только попробуй сказать что-то подобное ещё раз...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_5");
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		
		case "WildRose_Jillian_41":
			dialog.text = "Какая нервная особа, чуть что не по ней, правда?";
			link.l1 = "Не стоит её провоцировать почём зря, "+npchar.name+". Знаете же, что клинок она не для красоты носит.";
			link.l1.go = "WildRose_Jillian_42";
		break;
		
		case "WildRose_Jillian_42":
			dialog.text = "И вы бы позволили такому случиться, "+pchar.name+"?";
			link.l1 = "Вы просто не видели Мэри в бою, "+npchar.name+". Иначе не питали бы себя иллюзиями, что её кто-то или что-то может остановить. Ещё увидимся.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_7");
		break;
		
		case "WildRose_Mary_163":
			dialog.text = "Ты, наверное, хочешь меня о чём-то спросить, "+pchar.name+", да...";
			link.l1 = "Если честно, меня не особо волнует, что за кошка между вами пробежала, хотя я и догадываюсь, как её зовут. Вернее, звали. Ты очень хочешь это обсудить?";
			link.l1.go = "WildRose_Mary_164_1";
			link.l2 = "Вы с Джиллиан чего-то не поделили? Или, лучше сказать, кого-то?";
			link.l2.go = "WildRose_Mary_164_2";
		break;

		case "WildRose_Mary_164_1":
			dialog.text = "Хм, на самом деле, нет.";
			link.l1 = "Как скажешь. А теперь пойдём искать Орели.";
			link.l1.go = "WildRose_Mary_165";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Mary_164_2":
			dialog.text = "Эта мокрица всё не простит, что Алан предпочёл меня ей. Хотя могла бы - учитывая, что его больше нет... По правде сказать, "+pchar.name+", я бы не очень хотела это обсуждать, да.";
			link.l1 = "Как скажешь, милая. Тогда идём искать Орели.";
			link.l1.go = "WildRose_Mary_165";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;
		
		case "WildRose_Mary_165":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_9");
		break;
		
		case "WildRose_Oreli_61":
			dialog.text = ""+pchar.name+", Мэри! Вы снова на Острове, радость-то какая!";
			link.l1 = "Рады видеть, что вы в добром здравии, "+npchar.name+". На самом деле, мы зашли на Остров, чтобы вновь поговорить с вами. Но не переживайте, много времени это не займёт.";
			link.l1.go = "WildRose_Oreli_62";
			DelLandQuestMark(npchar);
		break;
		
		case "WildRose_Oreli_62":
			dialog.text = "О-ох, молодые люди, совсем вы не жалеете старушку. Но я чувствовала, что вы придёте. Это ведь опять о твоих родителях, да, Мэри?";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_62_add";
		break;

		case "WildRose_Oreli_62_add":
			StartInstantDialog("Mary", "WildRose_Oreli_63", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Oreli_63":
			dialog.text = "Прошу, Орели. Я понимаю, что тебе тяжело это вспоминать с учётом того, сколько времени прошло, но постарайся ещё разок, пожалуйста, да.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_63_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;

		case "WildRose_Oreli_63_add":
			StartInstantDialog("LSC_Oreli", "WildRose_Oreli_64", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Oreli_64":
			dialog.text = "Я вам и так рассказала всё, что помню. Ума не приложу, что вы ещё хотите из меня вытянуть.";
			link.l1 = "Мы зададим вам пару вопросов, "+npchar.name+". А вы постарайтесь, пожалуйста, что-нибудь вспомнить - какие-нибудь детали или подробности. Давить на вас мы не будем...";
			link.l1.go = "WildRose_Oreli_65";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;

		case "WildRose_Oreli_65":
			dialog.text = "А разве вы прямо сейчас не этим занимаетесь?";
			link.l1 = "Вы уже столько сделали для нас, "+npchar.name+"... Мы лишь надеемся, что в лабиринтах вашей памяти найдётся кое-что ещё, что очень нам поможет.";
			link.l1.go = "WildRose_Oreli_66_1";
			link.l2 = "Мы проделали большой путь, "+npchar.name+". Вы даже не представляете, скольких усилий и времени он нам стоил. Но мы заплутали, и только вам и вашей памяти под силу вывести нас на тропу истины.";
			link.l2.go = "WildRose_Oreli_66_2";
		break;

		case "WildRose_Oreli_66_1":
			dialog.text = "Памяти... Что от неё осталось-то, от памяти этой. Я порой по утрам не могу вспомнить, как меня зовут, а вы от меня подробности хотите - событий двадцатилетней давности. Но так уж и быть, спрашивайте.";
			link.l1 = "Нас интересует мистер Каспер, отец Мэри. Вы можете припомнить что-нибудь примечательное из его внешности? Может, на его лице был шрам, или он сильно хромал...";
			link.l1.go = "WildRose_Oreli_67";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;

		case "WildRose_Oreli_66_2":
			dialog.text = "Памяти... Что от неё осталось-то, от памяти этой. Я порой по утрам не могу вспомнить, как до гальюна добраться, а вы от меня подробности хотите - того, что двадцать лет назад на этих корабельных обломках происходило. Но ладно, так уж и быть, спрашивайте.";
			link.l1 = "Нас интересует мистер Каспер, отец Мэри. Вы можете припомнить что-нибудь примечательное из его внешности? Может, на его лице был шрам, или он сильно хромал...";
			link.l1.go = "WildRose_Oreli_67";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Oreli_67":
			dialog.text = "Ох-х... Кажется, я уже упоминала, что видела его только в непроглядной темноте, в трюме 'Церес Смити', где устроили ложе для бедняжки Терезы. Не хромал он совершенно точно - напротив, он был весьма прытким мужчиной.";
			link.l1 = "А его возраст? Он был молод или уже в годах?";
			link.l1.go = "WildRose_Oreli_68";
		break;

		case "WildRose_Oreli_68":
			dialog.text = "Стариком я бы его точно не назвала... Но я не особо обращала на него внимание - меня больше заботила Тереза. Выглядел он, конечно, неважно - напоминал какое-то привидение. Впрочем, учтите, что всю неделю, пока его жена была на сносях, он толком и не спал... Всё носился по Острову, не переставая.";
			link.l1 = "Жену, стало быть, он очень любил. А вы ведь много времени проводили рядом с ней, так? Она ничего не говорила о муже?";
			link.l1.go = "WildRose_Oreli_69";
		break;

		case "WildRose_Oreli_69":
			dialog.text = "Тереза постоянно справлялась о нём. Она много спала, иногда бредила, но, когда приходила в себя, сразу же спрашивала, где он. И бедняжка очень, очень его ждала. Но в самый важный момент - он так и не пришёл.";
			link.l1 = "Понятно. Очевидно, их любовь была взаимной... Что ж, спасибо вам, Орели. Вы нам очень помогли.";
			link.l1.go = "WildRose_Oreli_70";
		break;

		case "WildRose_Oreli_70":
			dialog.text = "И это всё? Я думала, наш разговор затянется на час-другой.";
			link.l1 = "Мы ведь обещали долго вас не мучать. Берегите себя, "+npchar.name+". Всего хорошего.";
			link.l1.go = "WildRose_Oreli_71";
		break;

		case "WildRose_Oreli_71":
			dialog.text = "Погодите, молодые люди! У меня есть для вас кое-что ещё... Точнее - для тебя, Мэри.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_72_a";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		
		case "WildRose_Oreli_72_a": //
			dialog.text = "Вот, девочка моя, возьми... Как только я увидела паруса вашего корабля - взяла эту шляпу с собой, чтобы не забыть о ней. Однако выйти на пристань... не решилась.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_72_add";
		break;

		case "WildRose_Oreli_72_add":
			StartInstantDialog("Mary", "WildRose_Oreli_73", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Oreli_73":
			dialog.text = "Что это, Орели? Шляпа?..";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_73_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;

		case "WildRose_Oreli_73_add":
			StartInstantDialog("LSC_Oreli", "WildRose_Oreli_74", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Oreli_74":
			dialog.text = "Шляпа твоей матери, Терезы. Она была при ней, когда выживших в кораблекрушении доставили на 'Церес Смити'. Когда Тереза скончалась, я подобрала эту шляпу с пола подле её кровати - да и забыла потом о ней... Вспомнила только сегодня, во время нашего разговора.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_74_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;

		case "WildRose_Oreli_74_add":
			StartInstantDialog("Mary", "WildRose_Oreli_75", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Oreli_75":
			dialog.text = "Орели... Ты хранила её столько лет! И... и не выбросила, не продала её... Спасибо, спасибо тебе! Ты даже не представляешь, насколько это... ценно и важно для меня, да!";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_75_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;

		case "WildRose_Oreli_75_add":
			StartInstantDialog("LSC_Oreli", "WildRose_Oreli_76", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Oreli_76":
			dialog.text = "Прости, Мэри - следовало отдать её тебе давным-давно... Но у меня уже не память, а древнее решето - вот и...";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_76_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;

		case "WildRose_Oreli_76_add":
			StartInstantDialog("Mary", "WildRose_Oreli_77", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Oreli_77":
			dialog.text = "Лучше момента и не придумаешь, Орели! Я примерю её сейчас же, да!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_hat_1");
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		
		case "WildRose_Mary_166":
			dialog.text = "Ну, дорогой, как я тебе?..";
			link.l1 = "Ты - прекрасна. Да и шляпа... не успела выйти из моды, так что тоже смотрится замечательно.";
			link.l1.go = "WildRose_Mary_167";
		break;
		
		case "WildRose_Mary_167":
			dialog.text = "Правда? Я так рада, что тебе нравится, да!";
			link.l1 = "А разве может быть иначе?";
			link.l1.go = "WildRose_Mary_167_add";
		break;
		
		case "WildRose_Mary_167_add":
			StartInstantDialog("LSC_Oreli", "WildRose_Mary_168", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_168":
			dialog.text = "...";
			link.l1 = "Спасибо ещё раз, Орели - вы сделали этот день чуточку ярче! Всего доброго, отдыхайте.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_10");
		break;
		
		case "WildRose_Mary_171":
			dialog.text = "Значит, это всё-таки был Руперт. Руперт Нортвуд, да.";
			link.l1 = "Очевидно, что так, дорогая. Он сделал всё, чтобы спасти жену... или возлюбленную, не знаю. Это и неважно, на самом деле. Главное, что теперь мы знаем, кого нам искать.";
			link.l1.go = "WildRose_Mary_172";
		break;

		case "WildRose_Mary_172":
			dialog.text = "Но что случилось с настоящим Джошуа Каспером, капитаном 'Корнуэлла'?";
			link.l1 = "Хороший вопрос, но сейчас не главный. Почему Руперт не вернулся за тобой раз так любил Терезу - вот что куда интереснее. И это будет первое, о чём мы его спросим. Если он всё-таки жив и если мы его найдём. Одно ясно точно - на флот он не вернулся. Ни к чему ему было так рисковать.";
			link.l1.go = "WildRose_Mary_174";
		break;

		case "WildRose_Mary_174":
			dialog.text = "Что же могло заставило его назваться именем Джошуа Каспера? Что случилось на борту 'Корнуэлла', ставшего 'Рэнглером'? Неужели мой отец - преступник, "+pchar.name+"?";
			link.l1 = "Боюсь, нельзя отметать и такой вариант, "+npchar.name+". Нам стоит быть готовым абсолютно ко всему.";
			link.l1.go = "WildRose_Mary_175";
		break;

		case "WildRose_Mary_175":
			dialog.text = "Я не хочу даже думать о таком...";
			link.l1 = "Пока нам думать надо о другом - где его искать. Он мог примкнуть к пиратам или контрабандистам. Или же поселился в каком-нибудь городе и не высовывается. Всё возможно.";
			link.l1.go = "WildRose_Mary_176";
		break;
		
		case "WildRose_Mary_176":
			dialog.text = "И что ты предлагаешь делать? Как нам его найти? Заходить в каждую колонию, называть его имя и надеяться, что кто-то что-то слышал о Руперте Нортвуде?";
			link.l1 = "Или Джошуа Каспере. Он вполне мог продолжить жить под личиной своего бывшего капитана - скорее всего, мёртвого. Но это несло за собой определённые риски, ведь пропавший бриг могли начать искать. Тем более, что на нём был сундук серебра, предназначенный для гарнизона Провиденса.";
			link.l1.go = "WildRose_Mary_177";
		break;

		case "WildRose_Mary_177":
			dialog.text = "Верно говоришь, да.";
			link.l1 = "А вот якобы погибший у Азорских островов Руперт Нортвуд вряд ли бы представлял для кого-то интерес. Впрочем, тут ещё определённо есть над чем поразмыслить.";
			link.l1.go = "WildRose_Mary_178";
		break;

		case "WildRose_Mary_178":
			dialog.text = "Это сколько же времени нам ещё предстоит потратить, "+pchar.name+"?! Ведь он может быть где угодно, в любой колонии, да!";
			link.l1 = "Если он выжил, разумеется. Но я с тобой не согласен. Вряд ли он бегло говорил по-испански, а значит, ни на Кубе, ни на Эспаньоле ему делать нечего. Он мог болтать по-французски и отправиться на Тортугу или одну из колоний на Малых Антилах. А мог и обосноваться на Западном Мэйне, под крылышком соотечественников. Мы и впрямь можем потратить на его поиски многие месяцы - и не факт, что преуспеем.";
			link.l1.go = "WildRose_Mary_179";
		break;

		case "WildRose_Mary_179":
			dialog.text = "Но я не хочу сдаваться, "+pchar.name+". Только не сейчас, когда мы уже так много узнали, да!";
			link.l1 = "Я этого и не предлагал, "+npchar.name+". Нам не нужно искать его самим - лучше обратиться к человеку со связями. Один раз это уже сработало, почему бы не попробовать снова?";
			link.l1.go = "WildRose_Mary_180";
		break;

		case "WildRose_Mary_180":
			dialog.text = "Предлагаешь вновь попросить помощи у аббата? Мне казалось, он дал нам понять, что на дальнейшее содействие в этом деле нам рассчитывать не стоит, да.";
			link.l1 = "Это будет слишком уж нагло по отношению к старику, ты права.";
			link.l1.go = "WildRose_Mary_181";
		break;

		case "WildRose_Mary_181":
			dialog.text = "Но к кому же нам тогда пойти? У кого есть деньги и связи для подобного мероприятия?";
			link.l1 = "Ну, спонсировать поиски определённо придётся нам. А вот что до связей... Полагаю, нам мог бы помочь Фадей Московит. У него точно должны быть на примете грамотные ребята, которых можно было бы разослать по колониям. Или же он сможет подсказать, к кому нам обратиться.";
			link.l1.go = "WildRose_Mary_182";
		break;

		case "WildRose_Mary_182":
			dialog.text = "Значит, отправляемся в Бас-Тер?";
			link.l1 = "Да, заглянем к нашему другу. Не самая сложная для него задача, как мне кажется.";
			link.l1.go = "WildRose_Mary_183";
		break;

		case "WildRose_Mary_183":
			dialog.text = "Поднимем якоря завтра, что скажешь? Я бы хотела провести остаток этого дня и ночь с тобой вдвоём, на 'Церес Смити'.";
			link.l1 = "От таких предложений не отказываются, милая. Мы с тобой определённо заслужили небольшой отдых.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_12");
		break;
		
		case "WildRose_Jillian_51":
			dialog.text = "Что, уже покидаете Остров? Неужели даже на похороны не останетесь?";
			link.l1 = "Похороны?..";
			link.l1.go = "WildRose_Jillian_52";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Jillian_52":
			dialog.text = "А, так вы не в курсе. Понятно... Орели Бертин скончалась этой ночью.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_52_add";
		break;

		case "WildRose_Jillian_52_add":
			StartInstantDialog("Mary", "WildRose_Jillian_53", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_53":
			dialog.text = "Что?! Не может быть - мы же только вчера с ней разговаривали, и она была жива-здорова. Или её кто-то...";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_53_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_53_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_54", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_54":
			dialog.text = "Нет, Мэри. Орели умерла во сне. Я зашла к ней сегодня, занести мази для суставов, изготовленные братом Юлианом - и обнаружила её. Она лежала на кровати, со странной улыбкой на лице. Но уже побледневшая и холодная.\nПоследнюю неделю старушка была сама не своя, я даже подумала, что болезнь, которую изгнал чёрный колдун, вернулась. Но мыслила она вполне ясно и, кажется, не бредила.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_54_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_54_add":
			StartInstantDialog("Mary", "WildRose_Jillian_55", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_55":
			dialog.text = "По крайней мере, она не мучилась, да.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_55_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_55_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_56", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_56":
			dialog.text = "Так вы останетесь на похороны? Они состоятся завтра, на самом дальнем рифе - там достаточно глубоко, и крабы туда не забредают.";
			link.l1 = "Мы останемся, Джиллиан. Орели так много сделала для Мэри, что иначе просто нельзя поступить. Если никто не против, мы организуем процессию у нас на корабле. Похороним её в открытом море, со всеми почестями.";
			link.l1.go = "WildRose_Jillian_57";
		break;
		
		case "WildRose_Jillian_57":
			dialog.text = "Противиться никто не станет. Это удобнее, и в конце концов безопаснее, чем лазить по обломкам.";
			link.l1 = "Тогда занимайтесь организацией похорон - Мэри поможет вам. Мне же надо кое с кем пообщаться...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_14");
		break;
		
		case "WildRose_Chimiset_61":
			dialog.text = "И снова ты здесь, мой дорогой друг! Что я могу сделать для тебя на этот раз?";
			link.l1 = "Здравствуй, "+npchar.name+". Ты уже слышал о том, что случилось этой ночью?";
			link.l1.go = "WildRose_Chimiset_62";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Chimiset_62":
			dialog.text = "Ты о смерти Орели? Вижу, что о ней. Слышал, конечно. Она ведь жила на 'Плуто', а это практически территория ривадос. Да и люди на остальных кораблях только об этом и говорят.";
			link.l1 = "Мы виделись с ней не далее как вчера, и она была в добром здравии - если не считать, конечно, что была чем-то встревожена всю последнюю неделю. А когда увидела наше судно, и вовсе разволновалась.";
			link.l1.go = "WildRose_Chimiset_63";
		break;

		case "WildRose_Chimiset_63":
			dialog.text = "Человек чувствует, когда река его жизни иссякает. Кто-то демонстрирует это всем вокруг, кто-то таит в себе, но ощущают это, так или иначе, все - особенно те, кто умеет слушать своё сердце.";
			link.l1 = "Мне показалось, что она была здорова, практически как молодая лань, "+npchar.name+". И что-то тут не вяжется...";
			link.l1.go = "WildRose_Chimiset_64_1";
			link.l2 = "И всё же, она была явно не на последнем издыхании, "+npchar.name+".";
			link.l2.go = "WildRose_Chimiset_64_2";
		break;

		case "WildRose_Chimiset_64_1":
			dialog.text = "Друг мой, разум и тело - вещи совершенно разного порядка. Разум управляет телом, иногда тело пытается взять контроль над разумом. Они тесно связаны, но всё же единым целым не являются. Человек может выглядеть совершенно здоровым внешне, но душа его уже идёт тропою смерти.";
			link.l1 = "Ты умён, мой друг, очень умён. Если ты почувствуешь, что истина витает где-то рядом, то погонишься за ней, словно лев за зеброй - и будешь преследовать её до тех пор, пока не овладеешь ей. Я понял это сразу, в ту же минуту, как тебя увидел.";
			link.l1.go = "WildRose_Chimiset_65";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Chimiset_64_2":
			dialog.text = "Друг мой, разум и тело - вещи совершенно разного порядка. Разум управляет телом, иногда тело пытается взять контроль над разумом. Они тесно связаны, но всё же единым целым не являются. Человек может выглядеть совершенно здоровым внешне, но душа его уже идёт тропою смерти.";
			link.l1 = "Знаешь, мне пришла в голову мысль, что Орели словно ждала нас, знала, что мы к ней придём. Старушка ведь могла умереть днём раньше или позже, но случилось это чуть ли не сразу после того, как она рассказала нам кое-что важное об отце Мэри."
			link.l1.go = "WildRose_Chimiset_65";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Chimiset_65":
			dialog.text = "Ты умён, мой друг, очень умён. Если ты почувствуешь, что истина витает где-то рядом, то погонишься за ней, словно лев за зеброй - и будешь преследовать её до тех пор, пока не овладеешь ей. Я понял это сразу, в ту же минуту, как тебя увидел.";
			link.l1 = "Я не... Погоди-ка. Так тот обряд, что ты провёл в трюме 'Протектора'... он не замедлил развитие болезни Орели, верно? Но что же ты тогда сделал?";
			link.l1.go = "WildRose_Chimiset_66";
		break;

		case "WildRose_Chimiset_66":
			dialog.text = "Можно заполнить реку камнями, однако это не остановит её течения. Я знал, что вам нужно от Орели нечто важное - как и то, что вы не доберётесь до этого сразу. Но сколько времени займёт ваш путь, мне было неведомо. Поэтому я воздвиг плотину, призвав все её жизненные силы на сдерживание болезни до тех пор, пока она не выполнит своё предназначение. И, как только это случилось, преграда рухнула...";
			link.l1 = "Так выходит, Орели... в момент смерти она была вовсе не в себе, не сознавала себя - как мы думали?";
			link.l1.go = "WildRose_Chimiset_67";
		break;

		case "WildRose_Chimiset_67":
			dialog.text = "Она пустила все свои силы на то, чтобы пребывать в здравом уме и твёрдой памяти, и, когда это более стало не нужно, недуг накатил на неё огромной волной, унеся в долину смерти. Была ли её кончина легка, или же она ушла к вашему Богу, мучимая призраками прошлого и страшными кошмарами - я сказать не могу, ибо мне это неведомо.";
			link.l1 = "Ты прекрасно знал, к чему это приведёт, верно? Какого дьявола не предупредил меня о последствиях?! Ну, говори!";
			link.l1.go = "WildRose_Chimiset_68_1";
			link.l2 = "Ты ведь знал, что делал, "+npchar.name+". Почему ты не предупредил меня о том, к чему это может привести?";
			link.l2.go = "WildRose_Chimiset_68_2";
		break;

		case "WildRose_Chimiset_68_1":
			dialog.text = "Потому что я решил помочь тебе, друг мой, узнать то, что вам было нужно, а ей - исполнить своё предназначение. Скажи я тебе о том, что её ждёт, ты мог и не решиться на это - и Орели просто унесла бы свои тайны с собой на тот свет. Какая в этом была польза? Она бы умерла напрасно. Словно антилопа, задранная львом, но не съеденная им и оставленная вместо этого на растерзание стервятникам.";
			link.l1 = "Предназначение, польза... Ты прямо-таки вершитель судеб, "+npchar.name+". Бог в человеческом обличье.";
			link.l1.go = "WildRose_Chimiset_69";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "WildRose_Chimiset_68_2":
			dialog.text = "Потому что я решил помочь тебе, друг мой, узнать то, что вам было нужно, а ей - исполнить своё предназначение. Скажи я тебе о том, что её ждёт, ты мог и не решиться на это - и Орели просто унесла бы свои тайны с собой на тот свет. Какая в этом была польза? Она бы умерла напрасно. Словно антилопа, задранная львом, но не съеденная им и оставленная вместо этого на растерзание стервятникам.";
			link.l1 = "Предназначение, польза... Ты прямо-таки вершитель судеб, "+npchar.name+". Бог в человеческом обличье.";
			link.l1.go = "WildRose_Chimiset_69";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;

		case "WildRose_Chimiset_69":
			dialog.text = "Мне слышится в твоём голосе недовольство, мой друг. Но нет, я вовсе не считаю себя богом - и, поверь, даже он не всесилен. Ни тот, в которого верите вы, ни те, кому поклоняемся мы. Боги не способны дать человеку сил больших, чем те, которыми он был одарён при рождении. Мы же, шаманы, способны лишь пустить их в то или иное русло - и не более того.";
			link.l1 = "И ты пустил их в русло, которое обрекло её на гибель...";
			link.l1.go = "WildRose_Chimiset_70";
		break;

		case "WildRose_Chimiset_70":
			dialog.text = "Я лишь направил Орели по пути, пойдя которым, она помогла Мэри - человеку, с которым была тесно связана с самого её рождения. Ведь твоя спутница появилась на свет у неё на глазах. Прошу, не смотри на меня как на умалишённого. Ведь не скажешь же ты, что видел во мне добродушного чародея, способного взмахом руки повернуть реку времени вспять?";
			link.l1 = "Я не знаю, что сказать тебе, "+npchar.name+". Быть может, всё это и впрямь было не зря. Но так было нельзя. Ты должен был мне сказать, а я - принять решение. Однако сделанного не воротишь. Что ж, бывай, друг.";
			link.l1.go = "WildRose_Chimiset_71";
		break;

		case "WildRose_Chimiset_71":
			dialog.text = "Эх-х, не такой я представлял нашу последнюю встречу, мой друг...";
			link.l1 = "С чего же ты взял, что она - последняя?";
			link.l1.go = "WildRose_Chimiset_72";
		break;

		case "WildRose_Chimiset_72":
			dialog.text = "Какие-то реки впадают в другие, становясь их частью, другие - иссякают, а некоторые - как наша - встречают конец в виде огромного водопада...";
			link.l1 = "Опять загадки, Чимисет? Пожалуй, мне на сегодня хватит. Думаю, ещё увидимся.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_15");
		break;
		
		case "WildRose_Mary_191":
			dialog.text = "Так и думала, что найду тебя здесь, да. Что ты хотел от Чимисета, "+pchar.name+"? Что он тебе сказал?";
			link.l1 = "Не то, что я ожидал - вернее, хотел - услышать. Но о чём очень смутно догадывался.";
			link.l1.go = "WildRose_Mary_192";
		break;

		case "WildRose_Mary_192":
			dialog.text = "Ты ведь расскажешь мне, да?";
			link.l1 = "Нет, "+npchar.name+". На этот раз - нет. Всё сказанное в каюте 'Протектора' там и останется, между мной и Чимисетом.";
			link.l1.go = "WildRose_Mary_193";
		break;

		case "WildRose_Mary_193":
			dialog.text = "Давно я не слышала такой решительности в твоём голосе, "+pchar.name+". Но ладно, у нас есть и другие заботы, да. Похороны состоятся завтра, в на закате, в семь часов.";
			link.l1 = "Пойдём, я помогу вам всё подготовить.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_17");
		break;
		
		case "WildRose_Mary_201":
			dialog.text = "Похоже, все, кто хотел, собрались, да.";
			link.l1 = "Я думал, будет побольше народу. По крайней мере, из числа мирных.";
			link.l1.go = "WildRose_Mary_202";
			CharacterTurnToLoc(npchar, "quest", "quest1");
			CharacterTurnToLoc(pchar, "quest", "quest1");
		break;

		case "WildRose_Mary_202":
			dialog.text = "Ну, Куранаи никто не звал, как и ривадос. Эббот, мерзкий чванливый индюк, заявил, что у него есть дела поважнее, чем хоронить католичку, что-то подобное вякнули и Лодердейл с Маскеттом. Кассель, этот грубиян, просто сказал, что не придёт. А все остальные здесь.";
			link.l1 = "Некоторые вещи всегда будут выше моего понимания. Ну да Бог им судья. А вот и брат Юлиан... Сейчас всё начнётся.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_2");
		break;
		
		case "WildRose_funeral_1":
			dialog.text = "Хоть наши сердца преисполнены скорби, возблагодарим Бога за все блага, которыми Он одарил усопшую Орели, и возгласим: Благодарим Тебя, Боже, Отче наш\n"+
			"За все годы и дни, которые Орели прожила  с нами\n"+
			"За великий дар святого крещения, благодаря которому Орели стала Твоей дочерью\n"+
			"За способности и знания, которыми Ты её одарил\n"+
			"За её служение благу семьи и других людей\n"+
			"За её терпение к нашим ошибкам\n"+
			"Помолимся Богу, чтобы Он принял в Свою славу нашу усопшую сестру Орели и воззовём: Просим Тебя, Господи\n"+
			"Пусть благие дела Орели принесут обильные плоды\n"+
			"Пусть то, что она начала, будет продолжено\n"+
			"Прости ей грехи, которые она совершила\n"+
			"Пусть память о ней живёт в наших сердцах\n"+
			"Помолимся Богу, чтобы Он укрепил веру и надежду страдающих, и воззовём к Нему: Господи, приумножь нашу веру\n"+
			"Через Сына Твоего, ставшего человеком\n"+
			"Через Сына Твоего, Иисуса Христа, бесконечно возлюбившего нас\n"+
			"Через Сына Твоего, принявшего смерть за наши грехи и воскресшего ради нашего спасения\n"+
			"Через Сына Твоего, открывшего нам путь к небесам\n"+
			"Вместе со всеми верными, которые предварили нас в небесной обители, помолимся, как научил нас Спаситель.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_7");
			
			WildRose_Etap4_PathToLight_18_funeral_6_1();
		break;
		
		case "WildRose_funeral_2":
			dialog.text = "Всемогущий Боже, услышь наши молитвы, возносимые с верой в Воскресшего Твоего Сына, и укрепи нашу надежду на то, что вместе с усопшей рабой Твоей и все мы удостоимся воскресения. Через Господа нашего Иисуса Христа, Твоего Сына, который с Тобою живёт и царствует в единстве Святого Духа, Бог вовеки веков. Аминь.";
			link.l1 = "Боже, Отче Всемогущий, тайна креста - наша сила, а Воскресение Сына Твоего - основание нашей надежды; освободи усопшую рабу Твою от уз смерти и сопричти её к лику спасённых. Через Христа, Господа нашего. Аминь.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_8");
			WildRose_Etap4_PathToLight_18_funeral_7_1();
		break;
		
		case "WildRose_funeral_3":
			dialog.text = ""+pchar.name+", давай поскорее зайдём в каюту, да. Я вот-вот разрыдаюсь... Не хочу, чтобы это кто-то видел.";
			link.l1 = "Конечно, "+npchar.name+". Пойдём.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_13");
		break;
		
		case "WildRose_Mary_211":
			dialog.text = "По-настоящему ценить человека начинаешь лишь после его смерти - ты слышал такое, "+pchar.name+"?";
			link.l1 = "Да - и не единожды.";
			link.l1.go = "WildRose_Mary_212";
		break;

		case "WildRose_Mary_212":
			dialog.text = "Эрик любил это повторять. Думаю, он говорил о своей семье. Я никогда его о ней не спрашивала - считала, что ещё успеется. А потом он умер, да. Теперь не стало и Орели - и я лишь сейчас поняла, как редко уделяла ей время и внимание. Куда реже, чем она того заслуживала.";
			link.l1 = "Ты ни в чём не виновата. Нам не дано знать, когда Господь заберёт к себе наших близких. И общения с ними никогда не бывает достаточно. Никогда.";
			link.l1.go = "WildRose_Mary_213";
		break;

		case "WildRose_Mary_213":
			dialog.text = "Может быть и так, да. А ещё Эрик часто говорил - и Орели с ним соглашалась, что любое место - это, прежде всего, люди. Не дома, деревья, дороги - а люди. Когда думаешь о какой-то точке на карте - вспоминаешь в первую очередь именно тех, кто там живут. Или жили.";
			link.l1 = "Никогда о таком не задумывался. Но, наверное, Эрик был прав - в конце концов, чего стоит дом, войдя в который, больше не встретишь отца или брата?";
			link.l1.go = "WildRose_Mary_214_1";
			link.l2 = "Я бы поспорил. Когда я вспоминаю, например, Париж - в голове всплывают виды улочек, запахи... Из людей мне вспоминаются единицы - остальные почти уже исчезли из памяти, хотя всего-то несколько лет прошло.";
			link.l2.go = "WildRose_Mary_214_2";
		break;

		case "WildRose_Mary_214_1":
			dialog.text = "Думаю, Эрик и Орели говорили об Острове, да. И о тех людях, что тут жили - давным-давно. Я была маленькой и не понимала этого, но теперь - осознала в полной мере. Ведь дольше меня тут живут Антонио, Сесиль... и некоторые ривадос, вроде Чимисета - но ни с кем из них я никогда не была близка. Остальные же: Эрик, Орели, Алан и многие другие, - мертвы.";
			link.l1 = "Понимаю. Мир стал... чуточку меньше, верно?";
			link.l1.go = "WildRose_Mary_215";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "WildRose_Mary_214_2":
			dialog.text = "Думаю, Эрик и Орели говорили об Острове, да. И о тех людях, что тут жили - давным-давно. Я была маленькой и не понимала этого, но теперь - осознала в полной мере. Ведь дольше меня тут живут Антонио, Сесиль... и некоторые ривадос, вроде Чимисета - но ни с кем из них я никогда не была близка. Остальные же: Эрик, Орели, Алан и многие другие, - мертвы.";
			link.l1 = "Понимаю. Мир стал... чуточку меньше, верно?";
			link.l1.go = "WildRose_Mary_215";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Mary_215":
			dialog.text = "Скорее - опустел. Этот мир - что внутри внешнего кольца. Он опустел, да. А вскоре - может вовсе исчезнуть.";
			link.l1 = "О чём ты, Мэри?.";
			link.l1.go = "WildRose_Mary_216";
		break;

		case "WildRose_Mary_216":
			dialog.text = "Разве ты не почувствовал это, "+pchar.name+"? Сейчас, когда мы стояли у гроба Орели.";
			link.l1 = "Что именно?";
			link.l1.go = "WildRose_Mary_217";
		break;

		case "WildRose_Mary_217":
			dialog.text = "Не знаю, как объяснить. Знаешь, как пахнет воздух перед грозой? Вспомни - когда ты оказался здесь впервые, какое напряжение витало кругом... Все были готовы перегрызть друг другу глотки, многим чудился запах пороха и крови. После того, как ты убил Чада, всё изменилось - словно дышать стало легче... Но сейчас - это ощущение вновь вернулось.";
			link.l1 = "Да, я почувствовал нечто подобное. Но, возможно, всё дело в обстановке? Похороны всё-таки...";
			link.l1.go = "WildRose_Mary_218_1";
			link.l2 = "Ты переутомилась, "+npchar.name+". Отдохнёшь - и станет легче. Да и разве можно на похоронах чувствовать себя иначе?";
			link.l2.go = "WildRose_Mary_218_2";
		break;

		case "WildRose_Mary_218_1":
			dialog.text = "Когда мы предавали морю Эрика и многих других жителей Острова - такого не было, говорю тебе. Чувствовалось какое-то... единение. А сегодня - некоторые чуть ли не волками друг на друга смотрели, хотя и читали при этом одну молитву.";
			link.l1 = "Ты про Лейтона и Дональда?";
			link.l1.go = "WildRose_Mary_219";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;

		case "WildRose_Mary_218_2":
			dialog.text = "Когда мы предавали морю Эрика и многих других жителей Острова - такого не было, говорю тебе. Чувствовалось какое-то... единение. А сегодня - некоторые чуть ли не волками друг на друга смотрели, хотя и читали при этом одну молитву.";
			link.l1 = "Ты про Лейтона и Дональда?";
			link.l1.go = "WildRose_Mary_219";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;

		case "WildRose_Mary_219":
			dialog.text = "Значит, ты тоже заметил, да.";
			link.l1 = "Декстер нервно реагирует на поползновения Гринспи по части учений - а как иначе?";
			link.l1.go = "WildRose_Mary_220";
		break;

		case "WildRose_Mary_220":
			dialog.text = "Добром это не кончится, да.";
			link.l1 = "Если так, то сегодня состоялись не только похороны Орели Бертин, но и этого... города потерянных кораблей.";
			link.l1.go = "WildRose_Mary_221";
		break;

		case "WildRose_Mary_221":
			dialog.text = "Города потерянных кораблей?";
			link.l1 = "Уж прости, Мэри, но Островом Справедливости это место язык не поворачивается назвать.";
			link.l1.go = "WildRose_Mary_222";
		break;

		case "WildRose_Mary_222":
			dialog.text = "Теперь, когда я увидела мир и осознала, насколько он огромен, это место кажется мне... тюрьмой, да. Трудно поверить, что я здесь выросла.";
			link.l1 = "И мне не верится, что среди этих корабельных обломков могла расцвести такая дикая, прекрасная роза, как ты.";
			link.l1.go = "WildRose_Mary_223";
		break;

		case "WildRose_Mary_223":
			dialog.text = "Я хочу попрощаться с этим местом, "+pchar.name+"... Наверное, мы сюда больше никогда не вернёмся, да. Я не хочу возвращаться. Не хочу видеть собственными глазами то, что здесь может произойти.";
			link.l1 = "Я поговорю с Эдди и Дональдом. Может, удастся немного остудить их пыл.";
			link.l1.go = "WildRose_Mary_224";
		break;

		case "WildRose_Mary_224":
			dialog.text = "Ты не понимаешь... Это лишь отсрочит неизбежное, так что это не стоит твоих усилий. Настанет день, когда мы вернёмся - а здесь\nТак будет лучше, "+pchar.name+", да... Меня здесь больше ничего не держит.";
			link.l1 = "Как скажешь, дорогая. Закончим все дела - и уйдём отсюда навсегда.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_20");
		break;
		
		// =================================================================
		// ==================== ЭТАП 5. «ЧУЖИМИ РУКАМИ» ====================
		// =================================================================
		case "WildRose_Mary_231":
			dialog.text = "Руперт Каспер? Джошуа Нортвуд, да?";
			link.l1 = "Я думал над этим всю дорогу, "+npchar.name+". И пришёл к выводу, что твой отец не стал бы скрываться под именем и фамилией, что уже использовал. В то же время от настоящего имени и или фамилии он мог и не решиться отказаться: что будет, если в неподходящий момент он не отзовётся на чужое?";
			link.l1.go = "WildRose_Mary_232";
		break;

		case "WildRose_Mary_232":
			dialog.text = "Он мог назваться как угодно, да.";
			link.l1 = "Мог, конечно. И, быть может, так и поступил. Если выжил на Кубе, куда прибыл на тартане контрабандистов. Если прибыл, а не стал пищей для крабов Острова Справедливости. Теперь нам остаётся лишь ждать - благо, не так долго, как в тот раз. Думаю, месяц мы без труда осилим.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_3");
		break;

		case "WildRose_Mary_235":
			dialog.text = "Мой отец жив, "+pchar.name+". А ведь я всегда это знала, да!";
			link.l1 = "Как и я, дорогая. Что ж, настала пора повидаться с этим Жеромом - да поскорее.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_7");
		break;
		
		// =================================================================
		// ================= ЭТАП 6. «ЖИЗНЬ ПОСЛЕ СМЕРТИ» ==================
		// =================================================================
		case "WildRose_Mary_241":
			dialog.text = "Наконец-то добрались, да. Что теперь, "+pchar.name+"?";
			link.l1 = "Нужно найти Жерома. Он либо прохлаждается в комнате таверны, либо снимает домик - деньги на это дело у него наверняка имеются.";
			link.l1.go = "WildRose_Mary_242";
		break;

		case "WildRose_Mary_242":
			dialog.text = "Учитывая, сколько заплатил ему Фадей... Думаю, он наверняка предпочёл второй вариант.";
			link.l1 = "Согласен. Мы расспросить о нем хозяина 'Стеклянного глаза', или же поспрашивать у обычных горожан. Пойдём, время дорого.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_2");
		break;
		
		case "WildRose_BanditBeliz_1":
			dialog.text = "Так-так-так... А вот и наши голубки. Давайте, парни, сделаем дело - и доложим ему.";
			link.l1 = "Жером Совернье? Какого чёрта тут происходит?!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_5");
		break;
		
		case "WildRose_BanditBeliz_2":
			if (!CharacterIsAlive("WildRose_Bandit_1") && !CharacterIsAlive("WildRose_Bandit_2"))
			{
				dialog.text = "Ах вы ублюдки, кха-кха. Ну ничего...";
				link.l1 = "Советую прикусить язык, если тебе дорога собственная шкура... ";
				link.l1.go = "WildRose_BanditBeliz_2_1";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "...";
				link.l1 = "...";
				link.l1.go = "exit";
			}
		break;
		
		case "WildRose_BanditBeliz_2_1":
			dialog.text = "...";
			link.l1 = "То-то же. А теперь выкладывай: какого дьявола вы набросились на нас - да ещё и вместе с Совернье...";
			link.l1.go = "WildRose_BanditBeliz_3";
		break;

		case "WildRose_BanditBeliz_3":
			dialog.text = "Ваш Совернье - жадный трусливый ублюдок. Стоило Касперу как следует всыпать ему, а потом деньжат посулить - тут же как миленький то письмецо нацарапал, кха-кха...";
			link.l1 = "Значит, он действительно нашёл его.";
			link.l1.go = "WildRose_BanditBeliz_4";
		break;

		case "WildRose_BanditBeliz_4":
			dialog.text = "Нашёл, нашёл. Так что ты скоро сдохнешь. Как и твоя подружка. Каспер вас обоих на ремни порежет, хе-хе. Я и так уже не жилец, но найти тебе твою смерть помогу. Жаль, я не услышу, как вы будете, молить о пощаде, когда окажетесь в его руках...";
			link.l1 = "Да, не жилец, это верно. Так что говори побыстрее, пока дух не испустил.";
			link.l1.go = "WildRose_BanditBeliz_6";
		break;

		case "WildRose_BanditBeliz_6":
			dialog.text = "Хотите его встретить - отправляйтесь в бухту Четумаль, он обитает там. Искать его не придётся, он сам вас найдёт.";
			link.l1 = "Вот и славно. Теперь, можешь умирать сколько тебе влезет. А мне пора.";
			link.l1.go = "WildRose_BanditBeliz_Just_Deth";
			link.l2 = "Надеюсь на это. А теперь отправляйся в ад.";
			link.l2.go = "WildRose_BanditBeliz_Hit_Deth";
		break;
		
		case "WildRose_BanditBeliz_Just_Deth":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_8");
		break;
		
		case "WildRose_BanditBeliz_Hit_Deth":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_7");
		break;
		
		case "WildRose_Mary_251":
			dialog.text = "Боже, "+pchar.name+"... Я не могу поверить, просто не могу, да! Это устроил мой отец?!";
			link.l1 = "Видимо, да, "+npchar.name+". Я уж не знаю, что им двигало и кто он, чёрт побери, такой... Но вряд ли это какой-то другой Руперт Каспер. Таких совпадений не бывает.";
			link.l1.go = "WildRose_Mary_252";
		break;

		case "WildRose_Mary_252":
			dialog.text = "И как нам теперь быть? Что я скажу, взглянув ему в глаза?";
			link.l1 = "Сперва нужно до него добраться. Вероятно, он поставил себя вне закона, раз уж его поиски вызвали... столь нервную реакцию. Но, как бы то ни было, он остаётся твоим отцом. На розыски которого мы потратили уйму усилий, времени и денег.";
			link.l1.go = "WildRose_Mary_253";
		break;

		case "WildRose_Mary_253":
			dialog.text = "Но что если он не станет даже разговаривать с нами? Почему он приказал убить нас?";
			link.l1 = "Хотя бы потому, что он мог и не знать, кто именно его ищет. Фадей мог просто назвать имя, а подробности касательно тебя опустить. В противном случае, думаю, нам бы не пришлось сейчас пачкать клинки кровью.";
			link.l1.go = "WildRose_Mary_254";
		break;

		case "WildRose_Mary_254":
			dialog.text = "И что теперь? Отправимся в бухту Четумаль? Но если он подстроил нам ловушку здесь... кто знает, что ждёт нас там?";
			link.l1 = "У нас есть преимущество во времени, пока он не узнает о том, что здесь произошло. Воспользуемся им. Отправимся на корабле в бухту, а нам в помощь по суше отправим отряд во главе с одним из офицеров.";
			link.l1.go = "WildRose_Mary_255";
		break;

		case "WildRose_Mary_255":
			dialog.text = "Звучит разумно, да. Но кто его возглавит?";
			if (CheckPassengerInCharacter(pchar, "Tichingitu"))
			{
				link.l1 = "Тичингиту. В боях на суше он закалён. Никто не справится лучше него.";
				link.l1.go = "WildRose_Etap6_Tichingitu";
			}
			if (CheckPassengerInCharacter(pchar, "Duran"))
			{
				link.l2 = "Клод. Он, конечно, будет не в восторге, но ничего - переживёт.";
				link.l2.go = "WildRose_Etap6_Duran";
			}
			if (CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				link.l3 = "Эркюль. Уж он-то знает, как делаются такие дела.";
				link.l3.go = "WildRose_Etap6_Tonzag";
			}
			if (CheckPassengerInCharacter(pchar, "Irons"))
			{
				link.l4 = "Томми. Даже если что-то пойдёт не по плану, этот парень выкрутится, уж поверь.";
				link.l4.go = "WildRose_Etap6_Irons";
			}
			if (CheckPassengerInCharacter(pchar, "Longway"))
			{
				link.l5 = "Лонгвэй. Ему не впервой выслеживать врага в сельве.";
				link.l5.go = "WildRose_Etap6_Longway";
			}
			if (!CheckPassengerInCharacter(pchar, "Tichingitu") && !CheckPassengerInCharacter(pchar, "Duran") && !CheckPassengerInCharacter(pchar, "Tonzag") && !CheckPassengerInCharacter(pchar, "Irons") && !CheckPassengerInCharacter(pchar, "Longway"))
			{
				link.l99 = "Алонсо. Клинком он машет лихо, да и мозгами не обделён.";
				link.l99.go = "WildRose_Etap6_Alonso";
			}
		break;
		
		case "WildRose_Etap6_Tichingitu":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Tichingitu");
		break;
		
		case "WildRose_Etap6_Duran":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Duran");
		break;
		
		case "WildRose_Etap6_Tonzag":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Tonzag");
		break;
		
		case "WildRose_Etap6_Irons":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Irons");
		break;
		
		case "WildRose_Etap6_Longway":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Longway");
		break;
		
		case "WildRose_Etap6_Alonso":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Alonso");
		break;
		
		//
		case "WildRose_Tichingitu_1":
			dialog.text = "Тичингиту внимательно слушать, капитан "+pchar.name+".";
			link.l1 = "Друг мой, тебе предстоит ответственное задание. В бухте Четумаль засела банда негодяев. Их нужно выследить и уничтожить. Мы подойдём на нашем корабле со стороны моря.";
			link.l1.go = "WildRose_Tichingitu_2";
		break;

		case "WildRose_Tichingitu_2":
			dialog.text = "";
			link.l1 = "Тебе же во главе отряда наших бойцов надлежит пройти через сельву, чтобы выйти мерзавцам в тыл. У тебя есть вопросы ко мне?";
			link.l1.go = "WildRose_Tichingitu_3";
		break;

		case "WildRose_Tichingitu_3":
			dialog.text = "У индеец нет вопрос. Завтра в полдень часов отряд быть на месте и там дожидаться в засада.";
			link.l1 = "Очень хорошо, Тичингиту. Удачи тебе.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Duran_1":
			dialog.text = "Вызывал, кэп?";
			link.l1 = "Дело для тебя есть, Клод.";
			link.l1.go = "WildRose_Duran_2";
		break;

		case "WildRose_Duran_2":
			dialog.text = "";
			link.l1 = "Нужно собрать отряд бойцов и во главе него добраться через джунгли до бухты Четумаль. Там нас поджидает банда некоего Руперта Каспера. Хотят устроить нам неприятный сюрприз. На деле же его устроим им мы, а точнее - ты. Нападёшь на них по моему сигналу. Вопросы?";
			link.l1.go = "WildRose_Duran_3";
		break;

		case "WildRose_Duran_3":
			dialog.text = "Ненавижу таскаться по джунглям. Но, как говорится, приказ есть приказ. Встретимся на месте, думаю, где-то завтра в полдень.";
			link.l1 = "Удачи, Клод.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Tonzag_1":
			dialog.text = "Слушаю тебя, кэп.";
			link.l1 = "Эркюль, для тебя есть работа.";
			link.l1.go = "WildRose_Tonzag_2";
		break;

		case "WildRose_Tonzag_2":
			dialog.text = "Нужно всадить кому-нибудь пару пуль в буйную бестолковку? Это я завсегда, ты же знаешь.";
			link.l1 = "Почти угадал. Тебе нужно возглавить отряд бойцов с нашего корабля, провести их через джунгли к бухте Четумаль. Там вы устроите засаду на банду, которая, как я думаю, будет поджидать там нас.";
			link.l1.go = "WildRose_Tonzag_3";
		break;

		case "WildRose_Tonzag_3":
			dialog.text = "Я думал, ты о серьёзном деле толкуешь, кэп. А ты чуть ли не о походе в таверну речь завёл. Завтра в полдень считай, что мы на месте.";
			link.l1 = "Увидимся уже там. Удачи, Эркюль.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Irons_1":
			dialog.text = "Ха, кэп, а ты чего такой серьёзный - будто на похороны собрался?";
			link.l1 = "Всё шутишь, Томми? Хочешь, я тоже пошучу? Жалования за этот месяц ты не получишь. И за следующий - тоже. Что ж ты так напрягся?";
			link.l1.go = "WildRose_Irons_2";
		break;

		case "WildRose_Irons_2":
			dialog.text = "И пошутить нельзя...";
			link.l1 = "Всему своё время, Томми. Этому тебе ещё учиться и учиться. А сейчас слушай меня внимательно: собирай отряд и выдвигайся через сельву в бухту Четумаль. Как доберётесь - ждите моей команды.";
			link.l1.go = "WildRose_Irons_3";
		break;

		case "WildRose_Irons_3":
			dialog.text = "Топтать сельву? Мы же прибудем туда не раньше чем завтра в полдень.";
			link.l1 = "Значит, увидимся там завтра в полдень. Без приказа в бой не вступать, позиции не покидать. Ясно тебе? Вижу, что ясно. А теперь - за дело.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Longway_1":
			dialog.text = "Лонгвэй слушать ваш, господин капитан.";
			link.l1 = "Дружище, для тебя есть задание.";
			link.l1.go = "WildRose_Longway_2";
		break;

		case "WildRose_Longway_2":
			dialog.text = "...";
			link.l1 = "Ты должен возглавить отряд наших бойцов, которые через джунгли пройдут до бухты Четумаль. Там возможно столкновение с противником, поэтому подготовь своих людей как следует.";
			link.l1.go = "WildRose_Longway_3";
		break;

		case "WildRose_Longway_3":
			dialog.text = "Лонгвэй всё понять, не волноваться, господин капитан. Мы прибыть на место примерно завтра в полдень.";
			link.l1 = "Ступай и будь осторожен.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Alonso_1":
			dialog.text = "Вызывал, капитан?";
			link.l1 = "Да. Слушай внимательно, Алонсо.";
			link.l1.go = "WildRose_Alonso_2";
		break;
		
		case "WildRose_Alonso_2":
			dialog.text = "";
			link.l1 = "Тебе во главе отряда бойцов предстоит пройти через джунгли и выйти к бухте Четумаль. Там, скорее всего поджидает банда мерзавцев. Тебе нужно будет занять позиции и напасть на них с тыла по моему сигналу.";
			link.l1.go = "WildRose_Alonso_3";
		break;

		case "WildRose_Alonso_3":
			dialog.text = "Плёвое дело, капитан. Но не высаживайтесь в бухте раньше, чем завтра в полдень - быстрее мы с ребятами туда не доберёмся.";
			link.l1 = "Подготовься как следует, Алонсо. И да поможет нам Бог.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Mary_256":
			dialog.text = "Шарль, ты видел, да?";
			link.l1 = "Похоже, нас уже ждут. Наверняка затаились за тем поворотом.";
			link.l1.go = "WildRose_Mary_257";
		break;

		case "WildRose_Mary_257":
			dialog.text = "Однако, в решето нас ещё не превратили. И даже не пытаются это сделать, да.";
			link.l1 = "Быть может, сперва с нами всё же настроены поговорить. Не будем его провоцировать - пойдём туда сами, наш отряд нас подстрахует. Идём, покончим со всем этим.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_18_1");
		break;
		
		case "WildRose_Rupert_1":
			dialog.text = "Стоять! Дальше - ни шагу! Парни, если тот хлыщ дёрнется - понаделайте в нём дырок. Девчонку не трогать.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_1_add";
			// link.l1.go = "WildRose_Rupert_87";
		break;

		case "WildRose_Rupert_1_add":
			StartInstantDialog("Mary", "WildRose_Rupert_2", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_2":
			dialog.text = "Папа?..";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_2_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_2_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_3", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_3":
			if (CheckCharacterItem(sld, "MarysHat")) // У Мэри есть своя шляпа
			{
				dialog.text = "Да-а, немало я повидал за свою долгую и нелёгкую жизнь. Всякий раз думаю, что ничто меня уже не удивит - и всякий раз ошибаюсь. Значит, ты всё-таки выжила там... И даже шляпу Терезы сохранила. У же не думал, что когда-то увижу её снова.";
				link.l1 = "...";
				link.l1.go = "WildRose_Rupert_3_1_add";
			}
			else
			{
				dialog.text = "Да-а, немало я повидал за свою долгую и нелёгкую жизнь. Всякий раз думаю, что ничто меня уже не удивит - и всякий раз ошибаюсь. Значит, ты всё-таки выжила там, Джулия...";
				link.l1 = "...";
				link.l1.go = "WildRose_Rupert_3_add";
			}
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_1_add":
			StartInstantDialog("Mary", "WildRose_Rupert_3_2", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_3_2":
			dialog.text = "Мне передала её Орели, перед свой... кончиной.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_3_2_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_2_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_3_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_3_3":
			dialog.text = "Как трогательно... Сейчас расплачусь. А я-то уж думал, что Терезу похоронили вместе с ней. Она не расставалась с ней ни на секунду с тех пор, как я подарил её ей. Твоя мать, хоть и была простой подавальщицей, но дух авантюризма у неё разве что из ушей не лился. Когда при захвате 'Флёр-де-Лиз' я её нашёл, то сразу понял, что Тереза будет от её без ума. Выглядела она в ней смешно, но ей было плевать: снимала она эту шляпу только перед сном. Но тебе, Джулия, она к лицу.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_3_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_add":
			StartInstantDialog("Mary", "WildRose_Rupert_4", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_4":
			dialog.text = "Джулия? Нет, вы ошибаетесь, меня зовут Мэри...";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_4_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_4_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_5", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_5":
			dialog.text = "Хм-м, вот как, значит. Выходит, эти мерзавцы наплевали на мои слова и взяли дело в свои руки. Ну, от этих католических собак другого ожидать и не стоило.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_5_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_5_add":
			StartInstantDialog("Mary", "WildRose_Rupert_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_6":
			dialog.text = "Вы... Ты... Ты и вправду мой отец?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_6_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_6_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_7":
			dialog.text = "Ну, не будь это так, ты со своим дружком уже валялись бы на земле, нашпигованные свинцом. Я давно уже не верю ни в Бога, ни в Дьявола, но, наверное, они всё-таки существуют. Первый так уж точно - раз одарил тебя внешностью Терезы. И этим спас тебе сейчас жизнь. Как там говорят: пути Господни неисповедимы, да? Ха-ха-ха!";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_7_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_7_add":
			StartInstantDialog("Mary", "WildRose_Rupert_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_8":
			dialog.text = "Папа... Я... я не понимаю, да...";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_8_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_8_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_9", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_9":
			dialog.text = "Да куда уж тебе, понять-то...";
			link.l1 = "Как-то не похоже, что вы рады увидеть дочь, мистер Каспер. Тем более, что признали её сами.";
			link.l1.go = "WildRose_Rupert_10";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_10":
			dialog.text = "Сообразительности тебе не занимать, щегол... Как там тебя зовут?";
			link.l1 = ""+GetFullName(pchar)+". Пока мы вас разыскивали, то всё гадали, как же вы жили всё это время. Если выжили вообще. Но вижу - вы тут неплохо устроились, мистер... Нортвуд.";
			link.l1.go = "WildRose_Rupert_11";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_11":
			dialog.text = "А-а, так вы докопались даже до этого. Ну, моё почтение, месье лягушатник, что ещё сказать - учитывая, что я позаботился о том, чтобы обрубить все концы.";
			link.l1 = "Не только до этого. Мы знаем и про 'Корнуэлл', и про его груз, и про Джошуа Каспера, чьё имя вы себе присвоили на время, а фамилию - видимо, навсегда.";
			link.l1.go = "WildRose_Rupert_12";
		break;

		case "WildRose_Rupert_12":
			dialog.text = "Браво (аплодирует). Я впечатлён. Это ты сам до всего допетрил, или моё ненаглядное чадо тоже внесло свой вклад?";
			link.l1 = "Без Мэри у меня бы ничего не получилось. Она очень хотела знать всё о своих родителях. С судьбой Терезы разобраться труда не составило, а вот по вашим следам мы шли довольно долго...";
			link.l1.go = "WildRose_Rupert_13";
		break;
		
		case "WildRose_Rupert_13":
			dialog.text = "Это всё так мило, что аж слёзы наворачиваются. Ну как, доченька, ты удовлетворена? Довольна? Хочешь обнять папочку?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_13_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_13_add":
			StartInstantDialog("Mary", "WildRose_Rupert_14", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_14":
			dialog.text = "Я не понимаю, отец... Зачем ты надо мной издеваешься? За что?! (кричит) Ведь это ты бросил меня там - на этих корабельных обломках! А потом даже и не подумал вернуться, да! Почему? Кто ты вообще такой, кто эти люди у тебя за спиной?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_14_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_14_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_15", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_15":
			dialog.text = "Скажи, "+pchar.lastname+", она часто так истерит? Это у неё от матери. Тереза была замечательной девушкой, лучшей из всех, кого я только встречал. Но лить сопли и закатывать истерики она любила, это да-а... Что сказать... ирландка.";
			link.l1 = "Не смейте её оскорблять! Мэри не виновата в ваших злоключениях и совершенно точно не заслуживает такого отношения к себе.";
			link.l1.go = "WildRose_Rupert_16";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;
		
		case "WildRose_Rupert_16":
			dialog.text = "Затыкать меня вздумал, щенок?!";
			link.l1 = "Напротив. Я хочу, чтобы вы нам рассказали нам свою историю. Мэри очень важно это знать. Но я не позволю вам её унижать. Так что держите себя в руках.";
			link.l1.go = "WildRose_Rupert_17";
		break;
		
		case "WildRose_Rupert_17":
			dialog.text = "Думаешь, мне очень хочется поплакаться вам в жилетку? Жизнь моя сложилась так, как сложилась, и, как вы, паписты, говорите - Господь свидетель - я ни о чём не жалею. Кроме того, что я потерял Терезу тогда - из-за неё. Ненавижу ли я тебя, доченька? Когда-то, может, так оно и было - а сейчас плевать я на тебя хотел.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_17_add";
		break;

		case "WildRose_Rupert_17_add":
			StartInstantDialog("Mary", "WildRose_Rupert_18", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_18":
			dialog.text = "Ты винишь меня в смерти мамы?! Ты... В чём же я виновата: в том, что появилась на свет, да? Ладно, отец, "+pchar.name+", прав - расскажи нам всё, а потом мы повернёмся и уйдём. И я больше никогда не появлюсь пред тобой, раз ты... (начинает рыдать).";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_18_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_18_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_19", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_19":
			dialog.text = "Да-а-а, вылитая Тереза. Я будто вернулся на двадцать лет, ха-ха. Чёрт с вами. Не хочотел я всё это вспоминать... Так что, если к концу этого предания я решу всадить пулю тебе в лоб, дорогуша - пеняй только на себя.";
			link.l1 = "Тогда пулю получите и вы, Руперт. А мне кажется, в ваши планы это не входит - ведь вы выглядите как человек, который ценит свою жизнь.";
			link.l1.go = "WildRose_Rupert_20";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_20": //
			dialog.text = "Я знаю ей цену, парень. Это разные вещи. Но где такому как тебе это понять? Ладно, перейдём к делу. Хотите знать обо мне всё? Ну, извольте. Родился я на ферме, близ Истборна - небольшого городишки на берегу Ла-Манша - в 1611 году. Может, годом раньше или позже - моя мамашка постоянно путала даты, что было и неудивительно, учитывая, сколько пойла она в себя вливала.";
			link.l1 = "Тяжёлое детство? Понятно.";
			link.l1.go = "WildRose_Rupert_21";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_21":
			dialog.text = "Раз напросился - слушай с закрытым ртом, а не остри. Отца у меня не было, и я даже не знал, почему - но, в отличие от тебя, дочурка, мне не было до этого дела. Фамилия, доставшаяся мне от него, меня вполне устраивала. Когда мне было тринадцать лет, однажды ночью на побережье высадились дюнкеркские приватиры. Да-а, об этом сейчас вспоминать не очень любят, но доставалось от них не только голландцам, но и нам - тем, кто жил на восточном побережье старушки Англии.";
			link.l1 = "Слышал об этом. Те парни никого не щадили. Как же вам удалось уцелеть?";
			link.l1.go = "WildRose_Rupert_22_1";
			link.l2 = "Я знаю об их зверствах. Не жалели никого - ни стариков, ни детей. Тем более удивительно, что вы оттуда выбрались.";
			link.l2.go = "WildRose_Rupert_22_2";
		break;

		case "WildRose_Rupert_22_1":
			dialog.text = "Той ночью эта папистская падаль спалила несколько ферм, в том числе, и нашу. Я-то успел выбраться, а вот моя мамуля, обожравшаяся сидра так, что с кровати стащить свой жирный зад не могла, так прямо в ней и сгорела. Сама виновата, конечно - но всё же она была моей матерью.";
			link.l1 = "И тогда вы возненавидели всех папистов?";
			link.l1.go = "WildRose_Rupert_23";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Rupert_22_2":
			dialog.text = "Той ночью эта папистская падаль спалила несколько ферм, в том числе, и нашу. Я-то успел выбраться, а вот моя мамуля, обожравшаяся сидра так, что с кровати стащить свой жирный зад не могла, так прямо в ней и сгорела. Сама виновата, конечно - но всё же она была моей матерью.";
			link.l1 = "И тогда вы возненавидели всех папистов?";
			link.l1.go = "WildRose_Rupert_23";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_23":
			dialog.text = "Тогда я возненавидел голод, остряк. Тебе-то, поди, конечно неведомо, что это такое, но я познал это на своей шкуре сполна. Я отправился на север, в столицу, где завербовался во флот - плетьми там потчевали больше, чем харчами, но пары-дюжины мне вполне хватило, чтобы взяться за ум, а после я втянулся - и я полюбил жизнь на корабле. Тем паче, что скучать не приходилось...";
			link.l1 = "Да уж, охотно верю. Слава английского флота себя опережает.";
			link.l1.go = "WildRose_Rupert_24";
		break;

		case "WildRose_Rupert_24":
			dialog.text = "В 1633 году я сдал экзамен на чин лейтенанта и получил назначение на бриг 'Корнуэлл'.";
			link.l1 = "Под командование Джошуа Каспера.";
			link.l1.go = "WildRose_Rupert_26";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_26":
			dialog.text = "О-о да-а-а. Джошуа Каспер... Такую мразь днём с огнём было не сыскать на всём чёртовом флоте, так-то. Уж столько лет минуло, а эта паскуда до сих пор навещает меня во снах.";
			link.l1 = "Чем же он отличился? Ставил вас на внеочередную вахту - за излишнее рвение? Или он втайне был папистом?";
			link.l1.go = "WildRose_Rupert_27";
		break;

		case "WildRose_Rupert_27":
			dialog.text = "Этот жестокий подлец муштровал экипаж до такой степени, что люди от усталости начинали валиться за борт. Раз ты знаешь его имя и то, что он был командиром 'Корнуэлла', наверняка видел его бумаги - сияющие, словно вылизанный кошачий зад\nНаград у нашего героического Джошуа была целая шкатулка. Многие наивные мальчишки вроде тебя хотели служить под его началом - чего не говори, а вас, лягушатников, он косил как заточенный серп сырую после дождя траву - но, оказавшись на 'Корнуэлле', очень быстро осознавали свою ошибку\nМы смертельно устали это терпеть, "+pchar.lastname+". Кто-то даже писал прошения о переводах - но они исчезали на полках Адмиралтейства или в его печах. Однако жизнь всё же дала нам шанс - перевели не нас с 'Корнуэлла', а кое-кого другого - на него. Джон Лоусон - любимчик Кромвеля, ты наверняка о нём слышал.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_28";
		break;

		case "WildRose_Rupert_28":
			dialog.text = "Зад он лизать умел уже тогда - и может они с Каспером и спелись бы, но я этого не допустил. Я подставил малыша Джонни, а не разобравшийся в ситуации Джошуа в ярости отдубасил его своей тростью.";
			link.l1 = "Настоящее унижение для офицера. И Лоусон всё рассказал отцу?";
			link.l1.go = "WildRose_Rupert_32";
		break;

		case "WildRose_Rupert_32":
			dialog.text = "Ещё бы. Но, видишь ли, система не может съесть сама себя. Огласки это дело не получило - Лоусону предложили досрочное повышение, а Джошуа и 'Корнуэлл' задвинули в тень - из Лондона нас перевели в Плимут, на юг Англии. Мы могли бы и дальше наводить ужас на вас, жабоедов, но 'Корнуэлл' превратили в фуражное судно, перевозившее грузы военного назначения в Дандолк, маленький ирландский городишко.";
			link.l1 = "И там вы повстречали Терезу?";
			link.l1.go = "WildRose_Rupert_33";
		break;

		case "WildRose_Rupert_33":
			dialog.text = "В первый же наш заход туда. Тереза О`Фатт, как я уже говорил, была подавальщицей в одной из местных таверн. Трёх дней нам хватило, чтобы понять - мы были созданы друг для друга. Думаю, тут ты тоже поймёшь меня, "+pchar.lastname+", верно?";
			link.l1 = "Пожалуй, что так.";
			link.l1.go = "WildRose_Rupert_34_1";
			link.l2 = "Глядя на вас сейчас, не скажешь, что вам ведомо слово 'любовь'.";
			link.l2.go = "WildRose_Rupert_34_2";
		break;

		case "WildRose_Rupert_34_1":
			dialog.text = "Никого прекраснее я не встречал - ни до того, ни за все последующие двадцать лет. Наверное, впервые в жизни я почувствовал себя по-настоящему счастливым человеком, и она тоже - как она утверждала.";
			link.l1 = "И вы предложили ей уехать с вами?";
			link.l1.go = "WildRose_Rupert_35";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "WildRose_Rupert_34_2":
			dialog.text = "Никого прекраснее я не встречал - ни до того, ни за все последующие двадцать лет. Наверное, впервые в жизни я почувствовал себя по-настоящему счастливым человеком, и она тоже - как она утверждала.";
			link.l1 = "И вы предложили ей уехать с вами?";
			link.l1.go = "WildRose_Rupert_35";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Rupert_35":
			dialog.text = "Конечно нет - это было невозможно, ведь 'Корнуэлл' оставался военным кораблём с ублюдком-капитаном во главе. Через неделю, показавшуюся нам вечностью, наш бриг отбыл обратно в Плимут. В Дандолк мы вернулись спустя два месяца - и Тереза огорошила меня новостью: она была беременна.";
			link.l1 = "Да, такое случается, когда укладываешь девушку в постель.";
			link.l1.go = "WildRose_Rupert_36";
		break;

		case "WildRose_Rupert_36":
			dialog.text = "Не умничай, лягушатник. Тереза рыдала у меня на плече, а я думал, что с этим делать. Я хотел остаться с ней, очень хотел - но уже тогда словно чувствовал, что добра от этого ребёнка не жди\nЯ попытался убедить Терезу избавиться от неё, пока ещё было не слишком поздно - но вместо этого нарвался на ещё более яростную истерику. Что тогда делать, мы не придумали - решили выждать ещё два месяца, до следующего возвращения 'Корнуэлла' в Дандолк, ибо на тот момент Адмиралтейство ещё не сменило гнев в отношении Каспера на милость.";
			link.l1 = "И вы притащили её на 'Корнуэлл'?";
			link.l1.go = "WildRose_Rupert_37";
		break;

		case "WildRose_Rupert_37":
			dialog.text = "Решение пришлось принимать быстро. Я понимал, что Каспер не потерпит женщину на борту, и собирался следующей ночью после отплытия похитить шлюпку и на ней добраться до Дублина, который как раз был бы у нас по правому борту.";
			link.l1 = "И что произошло? Вас поймали?";
			link.l1.go = "WildRose_Rupert_38";
		break;

		case "WildRose_Rupert_38":
			dialog.text = "Терезу обнаружили раньше. Каспер уже успел влить в себя порцию виски, а потому оставался глух к каким-либо воззваниям, приказав просто вышвырнуть девушку за борт. На все мои мольбы он лишь смеялся до упаду - проклятье, я рассказываю это, а у меня в голове стоит его хохот...";
			link.l1 = "И тогда вы решили поднять бунт?";
			link.l1.go = "WildRose_Rupert_39";
		break;

		case "WildRose_Rupert_39":
			dialog.text = "Иного выбора у меня не было. Выхватив у стоявшего рядом вахтенного из-за пояса пистоль, я проделал во лбу этого ублюдка дыру. На борту тут же началась резня - капитана никто не любил, но страх трибунала был сильнее. Это стоило жизни почти трети экипажа - когда мы, наконец, опомнились, вся палуба 'Корнуэлла' была залита кровью и завалена телами наших мёртвых товарищей.";
			link.l1 = "После такого в Англию вы, конечно, решили не возвращаться. Там бы вас всех ждала петля.";
			link.l1.go = "WildRose_Rupert_40";
		break;
		
		case "WildRose_Rupert_40":
			dialog.text = "Я был уверен, что проведу 'Корнуэлл' через океан. Здесь наши рожи никому не были известны, и это давало нам шанс начать новую жизнь. Убедить остальных офицеров большого труда не составило - сказался не столько мой авторитет, сколько содержимое пары сундуков, о котором простые матросы не знали. Команда решила - Джошуа Каспер должен был остаться жив. Мы с горской офицеров решили выиграть нам немного времени и пожертвовать одним из сундуков\nНо какая-то сволочь проболталась про второй сундук - и это внесло в команду раскол.";
			link.l1 = "Бунт подняли теперь против вас?";
			link.l1.go = "WildRose_Rupert_45";
		break;

		case "WildRose_Rupert_45":
			dialog.text = "Нет, но число желающих продолжить службу нашему славному королю резко сократилось. Тех, кто готов был податься в пираты, тоже было немного. Так что нашли промежуточный вариант - мы решили бросить якорь в одном из французских портов. Там мы планировали продать корабль, поделить деньги, вырученные за него, и те, что были в сундуке, а после - разбежаться.";
			link.l1 = "И вам было наплевать, что придётся жить среди столь ненавистных вам католиков?";
			link.l1.go = "WildRose_Rupert_46";
		break;

		case "WildRose_Rupert_46":
			dialog.text = "Мне было уже всё равно, где сойти на берег: Тереза, пусть и напоказ держалась молодцом, но чувствовала себя ровно так, как и любая беременная женщина после трёх месяцев непрерывной качки. И, как и тремя месяцами ранее, я не имел ничего против общества католиков - лишь бы быть рядом с ней.";
			link.l1 = "Но на северо-западе Карибского моря нет и не было французских поселений.";
			link.l1.go = "WildRose_Rupert_47";
		break;

		case "WildRose_Rupert_47":
			dialog.text = "К тому моменту, когда ситуация на борту 'Корнуэлла' достигла точки кипения, мы преодолели уже полпути при попутном ветре, который теперь уже не позволил нам взять курс на Сент-Кристофер...";
			link.l1 = "И вы избрали пунктом назначения Тортугу?";
			link.l1.go = "WildRose_Rupert_48";
		break;

		case "WildRose_Rupert_48":
			dialog.text = "В те года она была ещё простой деревней. Чтобы отсрочить возможное преследование со стороны официальных властей, мы сменили кормовую доску с названием брига - так 'Корнуэлл' стал 'Рэнглером'.";
			link.l1 = "Но почему-то до Черепашки вы так и не добрались. Не могли же вы так сильно ошибиться с курсом, что вместо Тортуги оказались к западу от Кубы?";
			link.l1.go = "WildRose_Rupert_49";
		break;

		case "WildRose_Rupert_49":
			dialog.text = "Я, чтоб ты знал, опытнейший штурман - не чета многим. Никакой ошибки не было, мы держали курс чётко на север. Но едва мы вошли в Наветренный пролив, как налетел ужасный шквал. Я до сих пор задаюсь вопросом - каким чудом нас не расшибло о кубинский берег, а потащило вдоль него?..";
			link.l1 = "Настоящее чудо - не иначе.";
			link.l1.go = "WildRose_Rupert_50";
		break;

		case "WildRose_Rupert_50":
			dialog.text = "Прижав к себе рыдающую Терезу, истово взывал к Господу, умоляя послать нам спасение. И Он подсобил так подсобил.";
			link.l1 = "Вас прибило к Острову Справедливости.";
			link.l1.go = "WildRose_Rupert_51";
		break;

		case "WildRose_Rupert_51":
			dialog.text = "Справедливости - о да! От удара о риф 'Рэнглер' треснул пополам, но удивительным образом сохранил плавучесть - достаточную для того, чтобы его донесло до наваленных друг на друга иных кораблей. Шторм бушевал ещё чуть ли не двое суток, а когда утих - нас спасли жители того нещастного островка.";
			link.l1 = "Вас, Терезу и ещё двоих матросов. О том, что было дальше, у нас есть представление. Лучше расскажите, как вы выбрались из тюрьмы и покинули остров.";
			link.l1.go = "WildRose_Rupert_63";
		break;

		case "WildRose_Rupert_63":
			dialog.text = "Лучше бы они меня тогда расстреляли... Если бы я только знал, что меня ждёт впереди, я бы сам себя приковал к решётке и с места бы не сдвинулся.";
			link.l1 = "Неужели на тартане было не так комфортно, как на бриге, а, "+npchar.name+"?";
			link.l1.go = "WildRose_Rupert_64_1";
			link.l2 = "Только не говорите, что вы угодили в шторм ещё и на тартане.";
			link.l2.go = "WildRose_Rupert_64_2";
		break;

		case "WildRose_Rupert_64_1":
			dialog.text = "Тартане? Ха-ха-ха... Да-а-а, таков был мой план. Мне, как я думал, повезло. Старшим охраны тюрьмы оказался бывший офицер английского флота, который проникся моей бедой. Он-то и рассказал мне и про тартаны кубинских контрабандистов, и про то, что меня собирались казнить. Наверное, его можно было бы назвать человеком чести - он сам предложил выпустить меня, чтобы я вверил себя в руки судьбы.";
			link.l1 = "Не понимаю... Если не на тартанах, то как же вы покинули остров?";
			link.l1.go = "WildRose_Rupert_68";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_64_2":
			dialog.text = "Тартане? Ха-ха-ха... Да-а-а, таков был мой план. Мне, как я думал, повезло. Старшим охраны тюрьмы оказался бывший офицер английского флота, который проникся моей бедой. Он-то и рассказал мне и про тартаны кубинских контрабандистов, и про то, что меня собирались казнить. Наверное, его можно было бы назвать человеком чести - он сам предложил выпустить меня, чтобы я вверил себя в руки судьбы.";
			link.l1 = "Не понимаю... Если не на тартанах, то как же вы покинули остров?";
			link.l1.go = "WildRose_Rupert_68";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;
		
		case "WildRose_Rupert_68":
			dialog.text = "Если ты заткнёшься и послушаешь, то поймёшь. Я плыл к тартанам, плыл долго - пока за стеной дождя не увидел свет. Это было нечто совершенно невероятное, чёрт побери. Он сиял, словно солнце, на палубе одного из полузатопленных галеонов, и я направился к нему. Ещё не ведая, что совершаю самую страшную ошибку в своей жизни. Я выбрался из воды по бортовому трапу - и оказался напротив света. Он сверкал над золотой статуей и...";
			link.l1 = "Идол Кукулькана. Да, тогда 'Сан-Херонимо' ещё не затонул...";
			link.l1.go = "WildRose_Rupert_69";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_69":
			dialog.text = "Значит, ты тоже видел его, "+pchar.lastname+"?";
			link.l1 = "Не просто видел. Я перемещался в пространстве с его помощью, причём, несколько раз.";
			link.l1.go = "WildRose_Rupert_70";
		break;

		case "WildRose_Rupert_70":
			dialog.text = "Лжёшь! Несколько раз, говоришь?! Как ты можешь тогда стоять здесь, весь пышущий здоровьем?!";
			link.l1 = "После перемещения я пил индейское зелье, оно и помогло мне остаться в живых и восстановить силы.";
			link.l1.go = "WildRose_Rupert_71";
		break;

		case "WildRose_Rupert_71":
			dialog.text = "А-а-а, вот оно что. А знаешь, сколько я силы восстанавливал? Знаешь?!";
			link.l1 = "Догадываюсь. Вы прикоснулись к идолу, и он перенёс вас на Доминику - к деревне индейцев, там вас принесли в жертву статуе и вы оказались на Мэйне, так?";
			link.l1.go = "WildRose_Rupert_72";
		break;

		case "WildRose_Rupert_72":
			dialog.text = "Именно. Так больно, как тогда, когда я лежал возле той статуи, мне не было никогда. Я не знаю, с чем это сравнить. Наверное, если на тебя обрушится каменный дом - даже тогда ты не испытаешь таких страданий. Едва придя в себя я увидел, как ко мне снова идёт толпа аборигенов. Если бы я говорил на их языке - клянусь, я бы взмолился о том, чтобы меня убили прямо на месте.";
			link.l1 = "Это были индейцы-мискито из деревни неподалёку?";
			link.l1.go = "WildRose_Rupert_76";
		break;

		case "WildRose_Rupert_76":
			dialog.text = "Они самые. Они притащили меня в одну из хижин, где какой-то странный абориген, на них не похожий, что-то влил мне прямо в рот. Боль немного утихла, но не прошла полностью. К вечеру меня вытащили к костру, и тот разукрашенный негодяй принялся проводить какой-то ритуал. Жалкий ублюдок.";
			link.l1 = "Змеиный Глаз... Вам следовало быть ему благодарным ему за спасение своей шкуры.";
			link.l1.go = "WildRose_Rupert_77";
		break;

		case "WildRose_Rupert_77":
			dialog.text = "Спасение?.. Три года, "+pchar.lastname+". Три года я лежал почти без движения, испражнялся и мочился прямо под себя, просыпался в собственной рвоте - потому что терпеть не мог уже все эти вонючие варева и тинктуры, которые мне насильно заливали в глотку! А потом ещё почти год учился заново ходить.";
			link.l1 = "Душераздирающая история. Но по-правде, мне вас даже жаль.";
			link.l1.go = "WildRose_Rupert_78";
		break;

		case "WildRose_Rupert_78":
			dialog.text = "Засунь свою жалось вашему Папе в его жирный католический зад. Я не нуждаюсь в чьём-либо сожалении. Мне продолжить, или тебе нужно время, чтобы поплакать, щегол?";
			link.l1 = "Манер это путешествие вам точно не прибавило. Но ничего, ради Мэри я потерплю. Хоть главное мы уже, полагаю, узнали - всё же дослушаем вас до конца.";
			link.l1.go = "WildRose_Rupert_79";
		break;

		case "WildRose_Rupert_79":
			dialog.text = "Встав кое-как на ноги, я покинул эту проклятую деревню и добрался до побережья, до бухты Аматике. Там я повстречал контрабандистов, чьё судно бросило якорь поблизости, и присоединился к ним, назвавшись Рупертом Каспером - от своего имени я отказываться не стал, но и фамилию одного из виновников всех своих бед тоже оставил. Чтобы не забывать, почему я здесь оказался.";
			link.l1 = "Все-то у вас виноваты, Нортвуд... Кроме непосредственно вас. Впрочем, вас можно понять - годы унижений и мучений, теперь сидите в этих лесах. Как тут не сбрендить?";
			link.l1.go = "WildRose_Rupert_80_1";
			link.l2 = "Через многое вы прошли, Нортвуд - не поспоришь. И вот, где вы оказались... В лесах, на краю цивилизации. Не сойдёшь тут с ума...";
			link.l2.go = "WildRose_Rupert_80_2";
		break;

		case "WildRose_Rupert_80_1":
			dialog.text = "Я - хозяин этих лесов, "+pchar.lastname+". За пятнадцать с лишним лет я проделал путь от жалкого матроса на корабле контрабандистов до их главаря. Не капитана какого-то кораблика - а хозяина всего побережья, от бухты Аматике до залива Гибели.";
			link.l1 = "Что ж, возрождение достойное, признаю.";
			link.l1.go = "WildRose_Rupert_81";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_80_2":
			dialog.text = "Я - хозяин этих лесов, "+pchar.lastname+". За пятнадцать с лишним лет я проделал путь от жалкого матроса на корабле контрабандистов до их главаря. Не капитана какого-то кораблика - а хозяина всего побережья, от бухты Аматике до залива Гибели.";
			link.l1 = "Что ж, возрождение достойное, признаю.";
			link.l1.go = "WildRose_Rupert_81";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		
		case "WildRose_Rupert_81":
			dialog.text = "Кто-то говорит, что здесь вотчина Лесного Дьявола... Наглая ложь - это мои земли. И Свенсон это знает, ха-ха-ха. Он не раз посылал сюда своих людей, пытался выяснить мою личность - и никто из них не вернулся к нему. В живом виде, хе-хе. Лишь по пальцам одной руки можно пересчитать тех, кто знает то имя, под которым я начинал карьеру контрабандиста, и где в этих лесах я живу.";
			link.l1 = "Значит, сейчас вы называете себя иначе. Теперь-то понятно, почему вести о том, что некто разыскивает Руперта Каспера, вызвали у вас такую панику.";
			link.l1.go = "WildRose_Rupert_82";
		break;
		
		case "WildRose_Rupert_82":
			dialog.text = "Панику? Ты серьёзно, парень? Паникуешь здесь только ты - на моей территории, в окружении моих людей, в полной моей власти! Я могу сделать с тобой всё, что захочу. И с ней тоже - просто за то, что она стала причиной всех тех мытарств, что я испытал!";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_82_add";
		break;

		case "WildRose_Rupert_82_add":
			StartInstantDialog("Mary", "WildRose_Rupert_83", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_83":
			dialog.text = "Ты сумасшедший, просто сумасшедший и всё, да. Я не знаю такого лекарства или лекаря, что могли бы тебя вылечить, Руперт Нортвуд! Ты прошёл через ужасные муки, но... как ты можешь винить во всём меня?!";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_83_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_83_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_84", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_84":
			dialog.text = "Я уже сказал - не будь тебя, ничего бы этого не было. Просто признай это, и всё.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_84_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_84_add":
			StartInstantDialog("Mary", "WildRose_Rupert_85", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_85":
			dialog.text = "...";
			link.l1 = "Оставь его, "+npchar.name+". Мы услышали достаточно. Некоторые дороги и впрямь не стоит преодолевать до самого конца. У меня было неприятное предчувствие, когда мы решили всем этим заняться. Но я к нему не прислушался. А жаль.";
			link.l1.go = "WildRose_Rupert_85_add";
		break;
		
		case "WildRose_Rupert_85_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_86", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_86":
			dialog.text = "Да-а-а, тогда бы вы оба не оказались здесь, в западне, бессильные что-либо предпринять. Почувствуй же теперь на своей шкуре, доченька, что испытывал я!";
			link.l1 = "А кто тебе сказал, что мы бессильны что-либо предпринять? Отря-а-а-д, к бою!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_20");
		break;
		
		case "WildRose_Rupert_87":
			dialog.text = "В чём дело, салага? Потерял кого-то? Ха-ха-ха... Ха-ха-ха. ХА-ХА-ХА-ХА-ХА-ХА!!! Ох-х, видел бы ты сейчас свою рожу, болван! Эй, Мэйсон, приведи сюда мой подарок нашим гостям.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_22");
		break;
		
		case "WildRose_Rupert_88":
			dialog.text = "...";
			link.l1 = "Мерзавец! Где мои люди?";
			link.l1.go = "WildRose_Rupert_89";
		break;
		
		case "WildRose_Rupert_89":
			dialog.text = "Ты о той горстке болванов, что вздумали устроить на меня засаду? Мой друг трактирщик вовремя меня предупредил о твоём появлении в городе, и я встретил их как положено... Нескольким и удалось улизнуть. Но не переживай - одного я захватил живьём. Чтобы ты своими глазами увидел, какая судьба ждёт вас сегодня.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_25");
			
			// WildRose_Etap6_LifeAfterDeath_24_1();
		break;
		
		case "WildRose_Rupert_90":
			dialog.text = "Негодяй! Ты ответишь за это! (плачет) Клянусь, да!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_29");
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Alonso_11":
			dialog.text = "...";
			link.l1 = "Алонсо! Как же я рад тебя видеть!";
			link.l1.go = "WildRose_Alonso_12";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Alonso_12":
			dialog.text = "А я-то как рад вас видеть, кэп! Этому мерзавцу кто-то шепнул о том, что вы его ищите — и нас встретили градом картечи прямо на полпути. Мне с горсткой ребят удалось отступить, и мы со всех ног помчались в порт, чтобы предупредить. К счастью, вахтенный на дозоре как только увидел меня на баркасе, который я в наспех прикупил в городе, сразу смекнул, что к чему, Он быстро собрал людей - и мы отправились сюда, на выручку.";
			link.l1 = "Спасибо тебе, друг. Ты спас нас от неминуемой смерти.";
			link.l1.go = "WildRose_Alonso_13";
		break;

		case "WildRose_Alonso_13":
			dialog.text = "Пустяки. Что будем делать дальше, кэп?";
			link.l1 = "Собирай людей и отправляйтесь на корабль. Нам с Мэри нужно побыть наедине.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		case "WildRose_Mary_261":
			dialog.text = "Бог мой, "+pchar.name+"... Я до сих пор не могу, просто не могу поверить. Мой отец... Он чудовище... За что он так со мной? Неужели он и впрямь сошёл с ума?";
			link.l1 = "Ему пришлось пройти через ужасные муки. Бунт на 'Корнуэлле', побег через Атлантику, буря и смерть твоей матери. Не представляю, как он пережил путешествие через порталы этих идолов без зелья команчей - но это и погубило его рассудок.";
			link.l1.go = "WildRose_Mary_262";
			locCameraFromToPos(-3.80, 1.10, 52.00, false, 0.61, 0.27, 49.69);
			LAi_ActorAnimation(pchar, "sharle_mary_sit", "", 50.0);
			LAi_ActorAnimation(npchar, "sharle_mary_sit", "", 50.0);
			CharacterTurnAy(pchar, 6.00);
			CharacterTurnAy(npchar, 6.00);
		break;

		case "WildRose_Mary_262":
			dialog.text = "А что если он таким и был до этого? Или был таким же негодяем, только чуть помягче, но любил мою маму искренне? Вдруг эти события лишь дали волю тому, что сидело у него внутри? И если так... что, если и во мне есть что-то от него? Такое ведь может быть, "+pchar.name+", да?";
			link.l1 = "Ты определённо переняла что-то от него, "+npchar.name+". В сегодняшнем бою я приметил - ты дерёшься с тем же упорством, с тем же огнём в глазах и той самой яростью, что и он. Но вот его безумия в тебе нет. Ты - совсем иная. Живая, открытая, с сердцем нараспашку. Именно за это я тебя и полюбил. И, похоже, Нортвуд был прав: нравом ты вся в матушку пошла.";
			link.l1.go = "WildRose_Mary_263";
		break;

		case "WildRose_Mary_263":
			dialog.text = "Ты правда так думаешь, дорогой?";
			link.l1 = "Конечно, любимая. Если бы я встретил его просто так, не зная кто он - никогда бы не подумал, что вы родня.";
			link.l1.go = "WildRose_Mary_264";
		break;

		case "WildRose_Mary_264":
			dialog.text = "Знаешь, на Острове Справедливости развлечений не так уж и много. С детства я полюбила фехтование - сперва я сражалась с мальчишками, деревянными палками, а потом уж и со взрослыми мужчинами, настоящими клинками, да. Мне всегда хотелось быть наравне с ними... но я как будто всегда ощущала себя слабее, даже когда одерживала верх\nТогда я просто возвращалась домой - и снова упражнялась. Тренировалась часами, пока руки не начинали дрожать, да. Это и есть тот самый огонь? Та ярость, о которой ты говоришь?";
			link.l1 = "В каком-то смысле - да. Мне кажется, этот огонь даёт тебе куда больше силы, чем ты сама в себе видишь. И, хочешь не хочешь, это дар от твоего отца. Хоть он и не собирался тебе ничего дарить.";
			link.l1.go = "WildRose_Mary_265";
			locCameraSleep(false);
			locCameraFromToPos(-1.95, 1.81, 48.29, true, -2.11, -0.04, 52.55);
		break;

		case "WildRose_Mary_265":
			dialog.text = "Думаешь, мы правильно поступили, что стали ворошить прошлое?";
			link.l1 = "Теперь, когда мы всё узнали... это не выглядит такой уж хорошей идеей. Но если хочешь узнать правду - нужно быть готовым к тому, что она тебе может не понравиться.";
			link.l1.go = "WildRose_Mary_266";
		break;

		case "WildRose_Mary_266":
			dialog.text = "Ты прав, "+pchar.name+", да... Давай ещё побудем здесь. Не хочется сейчас возвращаться на корабль. Хочу просто... посидеть здесь, в тишине.";
			link.l1 = "Конечно, любимая. Я и сам хотел это предложить.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_38");
		break;
	}
} 
