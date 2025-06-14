void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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
		
		//--> Встреча
		case "DiegoDeLanda_Meeting":
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 1)
			{
				dialog.text = "Печальная история, не правда ли?";
				link.l1 = "Кто вы?";
				link.l1.go = "DiegoDeLanda_Meeting_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 2)
			{
				dialog.text = "Здравствуйте, капитан.";
				link.l1 = "Погодите! Мы с вами уже встречались!";
				link.l1.go = "DiegoDeLanda_Meeting_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 3)
			{
				dialog.text = "Раз. Два. Три.";
				link.l1 = "Давайте прекратим этот спектакль. Кто вы такой?";
				link.l1.go = "DiegoDeLanda_Meeting_Third_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 4)
			{
				
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 5)
			{
				
			}
			DelLandQuestMark(npchar);
		break;
		
		case "DiegoDeLanda_Meeting_2":
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_SantaMisericordia"))
			{
				dialog.text = "Знаете, что особенного в этом склепе? Здесь покоятся две души, связанные... узами крови. Отец и сын де Аламида. Один пал от рук грешников, другой... Хм, нашел свой путь к Господу.";
				link.l1 = "Дневник дона Фернандо привёл меня сюда.";
				link.l1.go = "DiegoDeLanda_SantaMisericordia_2";
			}
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_LadyBeth"))
			{
				dialog.text = "Видели госпожу Бишоп? Печальная судьба, не правда ли? Но, боюсь, заслуженная.";
				link.l1 = "Вы знаете Элизабет?";
				link.l1.go = "DiegoDeLanda_LadyBeth_2";
			}
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_Memento"))
			{
				dialog.text = "Мортимер Грим.";
				link.l1 = "Вы его, разумеется, знали?";
				link.l1.go = "DiegoDeLanda_Memento_2";
			}
		break;
		
		case "DiegoDeLanda_Meeting_Third_2":
			dialog.text = "\nЕщё три. На счёт шесть вы всё узнаете.";
			link.l1 = " Если я не получу от вас внятных ответов прямо сейчас, то я...";
			link.l1.go = "DiegoDeLanda_Meeting_Third_3";
		break;
		
		case "DiegoDeLanda_Meeting_Third_3":
			dialog.text = "\nВы хорошо идёте, капитан. Вы заслуживаете узнать моё имя. Меня зовут Диего де Ланда.";
			link.l1 = " Вы действительно священник?";
			link.l1.go = "DiegoDeLanda_Meeting_Third_4";
		break;
		
		case "DiegoDeLanda_Meeting_Third_4":
			dialog.text = "Прежде всего, я художник. Но давайте не будем торопиться...";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Meeting_2";
		break;
		//<-- Встреча
		
		//--> Святое Милосердие
		case "DiegoDeLanda_SantaMisericordia_2":
			dialog.text = "Ах... Дневник. Удивительная вещь - написанное слово. Оно словно... тропинка во тьме. Приводит туда, где ждёт... откровение. Наш приход часто навещал дон Фернандо. Особенно в последний год.";
			link.l1 = "Вы служите в местном приходе? Вы знали дона Фернандо?";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_3";
		break;
		
		case "DiegoDeLanda_SantaMisericordia_3":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_4";
		break;
		
		case "DiegoDeLanda_SantaMisericordia_4":
			dialog.text = "Я... наблюдал его путь. А эта книга, что вы забрали. Знаете, что в ней особенного?";
			link.l1 = "Она выглядит старой.";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_5";
		break;
		
		case "DiegoDeLanda_SantaMisericordia_5":
			dialog.text = "Старой? О нет. Она... просветленная. Библия дона де Аламиды-старшего. Каждое слово в ней - как маяк во тьме. Возьмите. Помогайте братьям во Христе и тогда, быть может... и вас она приведет к чему-то... большему.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
		break;
		//<-- Святое Милосердие
		
		//--> Леди Бет
		case "DiegoDeLanda_LadyBeth_2":
			dialog.text = "О, да. Бедная женщина. Её муж... не самый добрый человек. Говорят, его плантации - самые продуктивные на Барбадосе. И самые жестокие. Знаете, сколько рабов умирает у него ежемесячно? Недавно он забил до смерти настоящего врача из Англии - человека большого ума и таланта. Но её судьба не многим лучше, поверьте.";
			link.l1 = "Вы, кажется, хорошо осведомлены.";
			link.l1.go = "DiegoDeLanda_LadyBeth_3";
		break;
		
		case "DiegoDeLanda_LadyBeth_3":
			dialog.text = "Люди приходят ко мне на исповедь, капитан. Я слышу то, что они боятся рассказать даже близким. Их страхи, их грехи... их боль.";
			link.l1 = "А вы не боитесь преследований? Католическому священнику непросто на английских территориях.";
			link.l1.go = "DiegoDeLanda_LadyBeth_4";
		break;
		
		case "DiegoDeLanda_LadyBeth_4":
			dialog.text = "Мои страхи несравнимы с тем, что вы только что оставили за дверью этого дома. А та книжица, что вы забрали у этой несчастной женщины… Если бы страх имел форму, то она была бы именно такой\n"+
			"Доброго дня, капитан.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
		break;
		
		//<-- Леди Бет
		
		//--> Мементо
		case "DiegoDeLanda_Memento_2":
			dialog.text = "Тигр, Тигр, жгучий страх\n"+
			"Ты горишь в ночных лесах\n"+
			"Чей бессмертный взор, любя, создал страшного тебя?\n"+
			"Разумеется, знал, капитан. А вот знали ли его вы";
			link.l1 = "Мне никогда не встречался человек с более трагичной судьбой.";
			link.l1.go = "DiegoDeLanda_Memento_3";
		break;
		
		case "DiegoDeLanda_Memento_3":
			dialog.text = "Встречался, но вы пока не оценили\n"+
			"Значит, Грима вы не знали. Хоть и держите в руках его череп.";
			link.l1 = "Что?!";
			link.l1.go = "DiegoDeLanda_Memento_4";
		break;
		
		case "DiegoDeLanda_Memento_4":
			dialog.text = "Это не по-христиански так обходиться с покойником. Вот, возьмите небольшую post mortem инструкцию. Мой вам подарок\n"+
			"Доброго дня, капитан.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
			SetAlchemyRecipeKnown("blade_SP_3low");	// рецепты от Катласа
			SetAlchemyRecipeKnown("blade_SP_3");
		break;
		
		//<-- Мементо
		
		//--> Прощание
		case "DiegoDeLanda_Leaving":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving");
		break;
		
		case "DiegoDeLanda_Leaving_1":
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 1)
			{
				dialog.text = "Скажите... Зачем? Это было опасно и глупо. В чём ваш огонь, капитан? Что вами движет?";
				link.l1 = "Это не ваше дело.";
				link.l1.go = "DiegoDeLanda_leaving_First_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 2)
			{
				dialog.text = "Второй.";
				link.l1 = "В прошлый раз вы говорили загадками. Сейчас тоже будете?";
				link.l1.go = "DiegoDeLanda_leaving_Second_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 3)
			{
				dialog.text = "...";
				link.l1 = "Погодите, де Ланда. Я не могу просто так позволить вам взять и уйти.";
				link.l1.go = "DiegoDeLanda_Leaving_Third_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 4)
			{
				
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 5)
			{
				
			}
		break;
		
		case "DiegoDeLanda_Leaving_First_2": // Первое прощание
			dialog.text = "Не могу понять. Вот остальных - могу. А вас - пока нет.";
			link.l1 = "Остальных?";
			link.l1.go = "DiegoDeLanda_Leaving_First_3";
		break;
		
		case "DiegoDeLanda_Leaving_First_3":
			dialog.text = "Один, например, стремится к справедливости. Или вот, был другой... одержимый тёмными водами смерти. Люди так легко теряют себя в своих желаниях. Не правда ли?";
			link.l1 = "Вы странный священник, святой отец.";
			link.l1.go = "DiegoDeLanda_Leaving_First_4";
		break;
		
		case "DiegoDeLanda_Leaving_First_4":
			dialog.text = "...";
			link.l1 = "Я пойду, пожалуй.";
			link.l1.go = "DiegoDeLanda_Leaving_First_5";
		break;
		
		case "DiegoDeLanda_Leaving_First_5":
			dialog.text = "Конечно. Ваша работа ещё только начинается, капитан.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Leaving_End";
		break;
		
		case "DiegoDeLanda_leaving_Second_2": // Второе прощание
			dialog.text = "\nНастоящая загадка стоит сейчас передо мной. Вы собрали уже две… реликвии. Вам нравится собирать такие вещи? Вы коллекционер?";
			link.l1 = "Откуда вы знаете?";
			link.l1.go = "DiegoDeLanda_leaving_Second_3";
		break;
		
		case "DiegoDeLanda_leaving_Second_3":
			dialog.text = "Охотник за трофеями?";
			link.l1 = "Я повторяю свой вопрос: откуда вы знаете?";
			link.l1.go = "DiegoDeLanda_leaving_Second_4";
		break;
		
		case "DiegoDeLanda_leaving_Second_4":
			dialog.text = "Любитель острых ощущений?";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving_Second_5";
		break;
		
		case "DiegoDeLanda_leaving_Second_5":
			dialog.text = "\nА. Ну конечно. Разумеется. Что же, капитан, не буду вас задерживать.";
			link.l1 = "Постойте-ка, святой отец. Вы всё ещё не ответили на мой вопрос.";
			link.l1.go = "DiegoDeLanda_leaving_Second_6";
		break;
		
		case "DiegoDeLanda_leaving_Second_6":
			dialog.text = "О, капитан. Я не могу. Иногда ответы ранят сильнее любого невежества. Идите с миром. И берегите свою коллекцию... трофеев. Они могут пригодиться в путешествии, которое вам предстоит.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Leaving_End";
		break;
		
		case "DiegoDeLanda_Leaving_Third_2": // Третье прощание
			dialog.text = "Ну же, капитан. Разве вам не интересно? Вам не весело? Вам хватило трофеев?\n"+
			"В этом ваш огонь, капитан. Вам интересно что будет дальше. Вы любите красивые корабли и занятные вещицы\n"+
			"Вы просто не можете не собрать их все.\n"+
			"\n"+
			"Вы можете пристрелить меня прямо сейчас.";
			link.l1 = "Что?!";
			link.l1.go = "DiegoDeLanda_Leaving_Third_3";
		break;
		
		case "DiegoDeLanda_Leaving_Third_3":
			dialog.text = "Давайте. Но тогда вы не узнаете всего и не получите полный набор трофеев. Корабли, впрочем, все получите\n"+
			"Доброго дня, капитан.";
			link.l1 = "(Отпустить)";
			link.l1.go = "DiegoDeLanda_Leaving_End";
			link.l2 = "(Пристрелить)";
			link.l2.go = "DiegoDeLanda_Leaving_Shoot";
		break;
		
		case "DiegoDeLanda_Leaving_End":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving_End");
		break;
		
		case "DiegoDeLanda_Leaving_Shoot":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving_Shoot");
		break;
		
		
		//<-- Прощание
	}
} 