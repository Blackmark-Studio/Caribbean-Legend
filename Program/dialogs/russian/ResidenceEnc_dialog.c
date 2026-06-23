
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;

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

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(int(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//--------------------------------- леди в резиденции ---------------------------------
		case "ResWoman":
			NextDiag.TempNode = "ResWoman";
			if (LAi_grp_playeralarm <= 0 && CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Done") && !CheckAttribute(npchar, "quest.chickengod") && int(npchar.nation) == SPAIN) {
				link.chickengod = "Сеньора, прошу извинить, но меня просили передать, что у вас... свидание в одной старой языческой пирамиде.";
				link.chickengod.go = "chickengod";
			}
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("Вот это да! Отпетый мерзавец - и у меня в покоях! Убирайся немедленно, не то позову стражу!", "Кошмар какой-то... И как эту пакость вообще пустили в мой дом? Прочь, негодяй! Нечего здесь шастать! Пошёл вон!!", "Ну и времена настали. Всякая мерзость заглядывает ко мне прямо в спальню! Вон!!");
				link.l1 = RandPhraseSimple("Полегче...", "Аккуратней в выражениях...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Что вы делаете в моей спальне? Уходите отсюда немедленно!", "Что за бестактность! Попрошу вас немедленно покинуть мои покои!", "Простите, судар"+GetSexPhrase("ь","ыня")+", но вас сюда не приглашали. Потрудитесь покинуть помещение!");
				link.l1 = RandPhraseSimple("Простите... Я уже ухожу.", "Извините, я ошиб"+GetSexPhrase("ся","лась")+" дверью. Ухожу.");
				link.l1.go = "exit";
			}
		break;
		case "Woman_FackYou":
			dialog.text = "Ой, что же это делается?! А я-то, дура, хожу, ничего не замечаю... Охрана!!!";
			link.l1 = "Заткнись, дура...";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(int(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- слуга в резиденции ---------------------------------
		case "ResMan":
			NextDiag.TempNode = "ResMan";
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase(""+ GetSexPhrase("Пошёл вон отсюда, мерзавец","Пошла вон отсюда, мерзавка") +"!", "Немедленно убирайся из дома губернатора, "+ GetSexPhrase("негодяй","негодяйка") +"!", "Мне нет дела до того, что тебе нужно в доме губернатора " + XI_ConvertString("Colony" + npchar.city + "Gen") + ". Но дам тебе совет - убирайся отсюда!");
				link.l1 = RandPhraseSimple("Полегче, родной...", "Смотри, не подавись своими словами!");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Здравствуйте. Я - слуга губернатора. Меня зовут " + GetFullName(NPChar) + ".", "Я присматриваю здесь за порядком, " + GetAddress_Form(NPChar) + ".", "Вы знаете, " + GetAddress_Form(NPChar) + ", наш губернатор - хороший человек, и неплохо платит прислуге...");
				link.l1 = RandPhraseSimple("Очень хорошо.", "Хм, прекрасно...");
				link.l1.go = "exit";
			}
		break;
		case "Man_FackYou":
			dialog.text = "Да ты никак "+ GetSexPhrase("вздумал","вздумала") +" обворовать губернатора?! Охрана, держи "+ GetSexPhrase("вора","воровку") +"!!";
			link.l1 = "Закрой пасть...";
			link.l1.go = "fight";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(int(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- солдат в резиденции ---------------------------------
		case "ResGuard":
			NextDiag.TempNode = "ResGuard";
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase(""+ GetSexPhrase("Шёл бы отсюда, приятель","Шла бы отсюда, подруга") +"...", "Проваливай отсюда!", "Ты, часом, дверью не "+ GetSexPhrase("ошибся","ошиблась") +"? Это дом губернатора " + XI_ConvertString("Colony" + npchar.city + "Gen") + ". Тебе лучше уйти!");
				link.l1 = RandPhraseSimple("Уйду, когда захочу!", "Не лезь не в своё дело...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Сегодня меня поставили в наряд к губернатору. Неплохое место...", "Я охраняю дом губернатора, " + GetAddress_Form(NPChar) + ".", "Моя задача - охранять дом губернатора.");
				link.l1 = RandPhraseSimple("Здорово.", "Хм, понятно...");
				link.l1.go = "exit";
			}
		break;
		
		case "chickengod":
			pchar.questTemp.ChickenGod.Tasks.o2.Counter = int(pchar.questTemp.ChickenGod.Tasks.o2.Counter) + 1;
			if (int(pchar.questTemp.ChickenGod.Tasks.o2.Counter) >= 3) {
				dialog.text = "Да-да, я готова отправится с вами, капитан!";
				link.l1 = "Вот так просто? Сеньора, вы точно этого хотите?";
				link.l1.go = "chickengod_accept";
			} else {
				sld = CharacterFromID(npchar.city + "_Mayor");
				dialog.text = "Что за идиотские шутки! Нахал"+GetSexPhrase("","ка")+"! " + sld.name + "! Стража! Помогите!";
				link.l1 = "А-ать! Пора удирать!";
				link.l1.go = "chickengod_decline";
			}
			npchar.quest.chickengod = true;
		break;
		
		case "chickengod_accept":
			dialog.text = "Ну, разумеется! Ах, мы с сеньором Арубой уже давно состоим в эпистолярной связи, вы разве не знали?";
			link.l1 = "Раз так, то прошу на борт!";
			link.l1.go = "chickengod_accept_take";
			link.l2 = "Нет, сеньора, так не пойдёт. Моя честь не позволит поставить женщину под удар, а вас явно ввели в заблуждение!";
			link.l2.go = "chickengod_accept_nottake";
		break;
		
		case "chickengod_accept_take":
			DialogExit();
			
			pchar.questTemp.ChickenGod.Tasks.o2.Done = true;
			pchar.questTemp.ChickenGod.Tasks.o2.Lady = npchar.id;
			AddDialogExitQuestFunction("ChickenGod_TakeLady");
		break;
		
		case "chickengod_accept_nottake":
			dialog.text = "В таком случае забирайте свою грошовую честь и бахвальтесь ею в другом месте, капитан. А я дождусь другого посланника, не такого узколобого, как вы!";
			link.l1 = "Очаровательно.";
			link.l1.go = "exit";
			
			pchar.questTemp.ChickenGod.Tasks.o2.Done = true;
			SetFunctionTimerCondition("ChickenGod_NotTakeLadyConsequence", 0, 1, 0, false);
		break;
		
		case "chickengod_decline":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_LadyRefuse");
		break;
		
	}
}
