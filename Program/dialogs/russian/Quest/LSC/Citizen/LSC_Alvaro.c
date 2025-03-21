// Альваро Гомец - капитан
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Я не желаю с тобой общаться. Ты нападаешь без причины на мирных граждан, провоцируешь их на драку. Уходи прочь!";
				link.l1 = "Гм...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "О, новое лицо! Приветствую вас. Когда вы это успели у нас очутиться? Что-то я не припомню за последние дни ни одного кораблекрушения.";
				link.l1 = TimeGreeting()+". Меня зовут "+GetFullName(pchar)+". Моё судёнышко затонуло так быстро и так тихо, что никто этого и не заметил. А я так же тихо и незаметно доплыл до Острова. Как-то так всё получилось...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "А, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Вы что-то хотели?";
				link.l1 = LinkRandPhrase("Что-нибудь интересное мне расскажете?", "Что нового произошло на острове в последнее время?", "Не расскажете ли последние сплетни?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Я хочу задать вам пару вопросов об острове.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Да просто решил узнать как у вас дела. Ещё увидимся!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Понятно. Ох, я не представился. Прошу простить меня, сеньор. Моё имя - Альваро Гомец, и когда-то я был капитаном собственного брига. Эх, теперь мой славный корабль лежит на дне за внешним кольцом... Сколько воды утекло с того грустного дня. Ах, да ладно. Будем знакомы!";
			link.l1 = "Приятно было познакомиться, сеньор Гомец.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Что-нибудь интересное мне расскажете?", "Что нового произошло на острове в последнее время?", "Не расскажете ли последние сплетни?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Я хочу задать вам пару вопросов об острове.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Внимательно вас слушаю, сеньор.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Вы сказали, что были капитаном. Как вы угодили на Остров?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Что вы можете сказать про жизнь на Острове?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Скажите, а островитяне живут в мире между собой, или нет? Ну, не считая кланов, конечно.";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "А откуда на острове берётся провизия?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Нет вопросов. Извините...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Так же, как и большинство - попал во внезапно налетевший шторм, лишился грот-мачты и рулевого управления, затем нас подхватило течением и выбросило на рифы. Мой корабль даже не дотянул до внешнего кольца и развалился на части. Спастись удалось очень немногим.";
			link.l1 = "Грустная история...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "А что тут скажешь? С большего, у нас всё есть для нормальной жизни. Только скука бывает, одолевает не на шутку. Да и тоска... Первый год вообще тяжело было, ну а потом - привык. Жаль только мою бедную жену, Сабину - она наверняка уверена в том, что я погиб. Надеюсь, ей удалось во второй раз выйти замуж\nТак что не расстраивайтесь - вы тоже привыкните. Сходите в таверну, в магазин, в церковь, познакомьтесь с остальными жителями. Только не суйтесь без нужды к нарвалам и ривадос - это черти ещё те.";
			link.l1 = "Понятно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "В общем да, ссоры и драки у нас негласно запрещены. Если вы кого-нибудь изобьёте без причины, или не дай Бог прикончите - вас просто будут чураться все остальные и вы останетесь в одиночестве. А то и вовсе, могут тихонько ночью за борт выбросить. Были уже на Острове буяны - один исчез бесследно, второй умер в клетке на 'Тартарусе' после нескольких месяцев заключения\nКонечно, это не означает, что вы должны терпеть, если кто-то решит вас оскорбить или покуситься на жизнь и здоровье. Но вообще, у нас все вполне дружелюбны. Эббот хоть и чванлив, но не агрессивен, Кассель, конечно, редкостный мерзавец, но рук не распускает, а Пратт, хоть и бывший каторжник, совершенно безобиден\nЕсть у нас два бывших военных офицера, Лодердэйл и Сольдерра. Они оба попали сюда, когда сцепились на своих кораблях в море недалеко отсюда. По иронии судьбы оба остались живы, и теперь без конца строят кровожадные планы в отношении друг друга.";
			link.l1 = "Ясно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Из трюмов кораблей, конечно. Всю провизию, собираемую с попадающих сюда судов, раньше складировали на 'Сан-Августине', и она была общим достоянием, пока не появились пираты. Теперь они держат весь остров в кулаке - запасы продовольствия-то у них\nКонечно, имеются у нас и заначки, так что не пропадём. Стреляем птиц из мушкетов, ловим рыбу... Но самое милое дело - это убить гигантского краба. У них очень вкусное и питательное мясо. Правда, на поверхность они редко выползают, и то, только на внешнем кольце\nА спуститься под воду охотиться за ними никто не рискнёт. Хотя нет, был такой смельчак у нас, охотник на крабов. Однако в один прекрасный день он вместо охотника стал добычей. Так что больше желающих достать крабов из-под воды нет.";
			link.l1 = "Занятно...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Что ты там копаешься, а? Да ты вор!", "Вот это да! Чуть я загляделся, а ты сразу в сундук с головой!", "По сундукам шарить вздумал?! Тебе это даром не пройдёт!");
			link.l1 = "А-ать, дьявол!!!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Ах, вот, значит, как?! По сундукам шарить вздумал?! Тебе это даром не пройдёт!";
			link.l1 = "Вот дура!..";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Слушай, ты бы убрал оружие. А то нервируешь немного...", "Знаешь, у нас тут не принято сабелькой размахивать. Убери оружие.", "Слушай, что ты, как д'Артаньян, бегаешь тут, шпагой машешь? Убери оружие, не к лицу это серьёзному мужчине...");
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажешь...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнажённым клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнажённым клинком.");
				link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Осторожней на поворотах, приятель, когда бежишь с оружием в руках. Я ведь могу и занервничать...", "Мне не нравится, когда мужчины ходят передо мной с оружием на изготовку. Это меня пугает...");
				link.l1 = RandPhraseSimple("Понял.", "Убираю.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}