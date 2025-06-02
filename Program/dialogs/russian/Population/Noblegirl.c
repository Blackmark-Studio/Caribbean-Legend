//Jason общий диалог дворянок
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//первая встреча
            if(NPChar.quest.meeting == "0")
			{
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)//проверка межнациональных отношений
				{
					dialog.text = "Хм. Вы ходите под флагом "+NationNameGenitive(sti(pchar.nation))+", капитан. У меня нет никакого желания общаться с врагом моей державы. Уходите прочь!";
					link.l1 = "Тоже мне, патриотка...";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = RandPhraseSimple("Что вы хотели от меня, "+GetAddress_Form(NPChar)+"? Не пристало морякам приставать с расспросами к знатной даме, но я всё же выслушаю вас.", "Ой, и что же может быть от меня нужно такому бравому капитану, а?");
					link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+". Я не задержу вас надолго, просто хочу спросить...";
					link.l1.go = "question";
					link.l2 = RandPhraseSimple("Мне нужно узнать, что творится в вашей колонии.", "Мне нужна информация.");
					link.l2.go = "quests";//(перессылка в файл города)
				}
				npchar.quest.meeting = "1";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("Весь город на ушах - прибыл дон Фернандо де Аламида, королевский ревизор. Знаете, я тут многое повидал, но такого... Людей меняет не горе, а то, как они с ним справляются. Говорят, после гибели отца он стал другим человеком. Теперь во всём Архипелаге не сыскать более неподкупного и... безжалостного служаки.", "Вы только гляньте на 'Святое Милосердие'! Говорят, сам король приказал построить его по особым чертежам. И заметьте - ни единой царапины. Словно сама Дева Мария хранит его. Хотя слухи слышал такие... может, и не Дева вовсе.", "Знаете, сколько раз пытались убить дона Фернандо? Двенадцать атак в открытом море - и это только за последний год! Ну, с таким верным и обученным экипажем, да ещё и под защитой Господа - переживёт и тринадцатую!"), LinkRandPhrase("Слышали? Дон Фернандо де Аламида прибыл в наш город, и, говорят, сейчас где-то на улицах. Увидеть бы его своими глазами...", "Сложный человек этот дон Фернандо. Одни говорят - спаситель, чистит Отечество от скверны. Другие шепчутся - мол, после смерти отца что-то надломилось в нём и скоро наплачемся. А я скажу так: бойтесь не его. Бойтесь тех, кто его таким сделал.", "Такой видный мужчина, этот дон Фернандо! Но знаете что странно? Он словно и не замечает никого. Всё служба да служба. Я слышала, была одна девушка... но после встречи с каким-то священником он полностью отверг мирские радости. Словно дал обет."), RandPhraseSimple(RandPhraseSimple("Чёртов ревизор! Пока он здесь - город словно мёртвый. Ни торговли, ни веселья. Даже дышать, кажется, нужно тише. А знаете, что самое жуткое? В каждом порту одно и то же. Как по писаному. Ну не мог Его Королевское Величество специально придумать эту пытку для всех нас!", "Дон Фернандо опять посетил приют. Щедро жертвует, молится часами. Такого достойного человека нужно ставить в пример этим проклятым казнокрадам!"), RandPhraseSimple("Ха! 'Святой' Фернандо опять закрыл все бордели. Ну, ничего, скоро он отчалит и сразу откроют обратно.", "Рези... ревизор приплыл, вот что! Дон Фернандо де Альмейда, или, как его, Аламида! Такой важный, что сам губернатор перед ним на цыпочках ходит. Говорят, он в глаза смотрит и сразу видит все грехи. Жуть!")));
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== прибыла инспекция на Святом Милосердии
				//==> Леди Бет в порту города
				if (CheckAttribute(pchar, "questTemp.LadyBeth.CaptainInColony") && pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_town")
				{
					dialog.Text = findLedyBethRumour(npchar);
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== Леди Бет в порту города
			}
			else
			{
				//повторные обращения
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "Я что, непонятно выражаюсь? Я не желаю, чтобы меня заподозрили в связи с "+NationNameAblative(sti(pchar.nation))+"! Уходите, или я позову стражу! Они-то точно будут рады с вами побеседовать.";
					link.l1 = "Ладно-ладно, не кипятитесь. Ухожу.";
					link.l1.go = "exit";
				}
				else
				{
				dialog.text = NPCStringReactionRepeat("Что? Опять? Поищите для болтовни кого-нибудь другого. Тут полно бездельников, слоняющихся по улицам. А мне пора - вечером приём у губернатора, а у меня ещё причёска не готова...", 
					"Нет, это уже начинает действительно утомлять! Вы что, не понимаете с первого раза? Вы медленно соображаете?", 
					"Судар"+GetSexPhrase("ь","ыня")+", я начинаю подозревать, что вы не "+GetSexPhrase("тупица","дура")+", а деревенщина и хам"+GetSexPhrase("","ка")+". Предупреждаю: будете приставать с глупыми расспросами - позову мужа!",
					"Так, ещё одно слово - и я сообщу коменданту, чтобы в отношении вас были приняты меры!", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Понятно. Всего доброго.", 
					"Да-да, я помню, просто забыл"+GetSexPhrase("","а")+" спросить вот что...",
					"Вы меня неправильно поняли...", 
					"Не злитесь, сударыня, я уже ухожу.", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
				}
			}
			NextDiag.TempNode = "First time";
		break;

		//сюда вставляем любые проверки и направления на квесты
		case "question":
			dialog.text = LinkRandPhrase("Ну, давайте послушаем, так и быть.","Ох, ну хорошо. Что вы хотите?","Вопросы задавать будем? Ладно, моря"+GetSexPhrase("к","чка")+", слушаю.");
			link.l1 = LinkRandPhrase("Не расскажете последние новости вашего города?","Расскажите пожалуйста, что интересного в последнее время произошло?","Что интересного творится на архипелаге, сударыня, вы не в курсе?");
			link.l1.go = "rumours_noblegirl";
			NextDiag.TempNode = "First time";
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнажённым клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнажённым клинком.");
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
