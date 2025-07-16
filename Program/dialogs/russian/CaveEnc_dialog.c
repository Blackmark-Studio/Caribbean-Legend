// пещерные энкаунтеры
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp, sGroup;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	sTemp = "CaveBandos" + locations[FindLocation(npchar.location)].index + "_";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ты что-то хотел?";
			link.l1 = "Да нет, ничего.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "CaveBanditosSit":
			if (hrand(2) == 1) 
			{
				dialog.text = NPCStringReactionRepeat("Хо-хо, кто к нам пожаловал"+GetSexPhrase("","а")+"! Сегодня твой счастливый день, "+GetSexPhrase("дружок","подруга")+". Мы добрые, вот, кушать готовим... Присоединиться не приглашаю, а вот унести ноги побыстрее возможность у тебя есть.", "Давай-давай, топай отсюда, не мешай нам. Завтра приходи, и кошель не забудь, ха-ха!", "Не зли меня, "+GetSexPhrase("морячок","красавица")+". Надеюсь, запомнил"+GetSexPhrase("","а")+", где выход из пещеры? Туда и вали, да поживее!", "Ну всё, ты меня достал"+GetSexPhrase("","а")+". Придётся оторваться от дел насущных и заняться тобой!", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Какой ты добрый, приятель...", "Ты, посмотрю, шутник, однако...", "Ладно, сиди, жарь свои лепёшки...", "Вот это деловой разговор!", npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit_talk", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = LinkRandPhrase("Хо-хо, ну надо же! Даже "+GetSexPhrase("искать добычу","в бордель идти")+" не пришлось - сама явилась... Ну-ка, ребята, "+GetSexPhrase("порастрясём этого пижона","поразвлекаемся с этой девицей")+"!",""+GetSexPhrase("Приятель","Красавица")+", тебя никто сюда не звал... но, раз приш"+GetSexPhrase("ёл","ла")+" - мы очень рады! Ну-ка, поглядим, "+GetSexPhrase("тяжёл ли твой кошель","что там у тебя под юбкой")+"!","А ведь тебя никто сюда не тянул, хе-хе... Но, раз явил"+GetSexPhrase("ся","ась")+" - то мы "+GetSexPhrase("тебя малость пощекочем, посмотрим, что высыпется из карманов...","с тобой сейчас покувыркаемся... чур я первый!")+"");
				link.l1 = LinkRandPhrase("Сейчас я тебе "+GetSexPhrase("язычок-то","кое-что")+" подкорочу...","Надеюсь, саблей владеешь так же мастерски, как трепешься языком?","Ну что же, пришло время проделать в твоём бренном теле дополнительных пару дырок...");
				link.l1.go = "fight";
			}
			NextDiag.TempNode = "CaveBanditosSit";
		break;
		
		case "CaveBanditosStay":
			dialog.text = LinkRandPhrase("Хо-хо, ну надо же! Даже "+GetSexPhrase("искать добычу","в бордель идти")+" не пришлось - сама явилась... Ну-ка, ребята, "+GetSexPhrase("порастрясём этого пижона","поразвлекаемся с этой девицей")+"!",""+GetSexPhrase("Приятель","Красавица")+", тебя никто сюда не звал... но, раз приш"+GetSexPhrase("ёл","ла")+" - мы очень рады! Ну-ка, поглядим, "+GetSexPhrase("тяжёл ли твой кошель","что там у тебя под юбкой")+"!","А ведь тебя никто сюда не тянул, хе-хе... Но, раз явил"+GetSexPhrase("ся","ась")+" - то мы "+GetSexPhrase("тебя малость пощекочем, посмотрим, что высыпется из карманов...","с тобой сейчас покувыркаемся... чур я первый!")+"");
			link.l1 = LinkRandPhrase("Сейчас я тебе "+GetSexPhrase("язычок-то","кое-что")+" подкорочу...","Надеюсь, саблей владеешь так же мастерски, как трепешься языком?","Ну что же, пришло время проделать в твоём бренном теле дополнительных пару дырок...");
			link.l1.go = "fight";
		break;
		
		case "CaveBanditosTreasure":
			dialog.text = NPCStringReactionRepeat("Проваливай отсюда, "+GetSexPhrase("приятель","деваха")+". Нечего тут шастать!", "Слушай, по-хорошему прошу: уйди отсюда. Не ровён час...", "Последний раз предупреждаю: не уйдёшь - пожалеешь об этом.", "Ну всё, "+GetSexPhrase("приятель","красавица")+", ты сам"+GetSexPhrase("","а")+" напросил"+GetSexPhrase("ся","ась")+"...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Не указывай мне, что делать, ладно?", "И что тут такого особенного? Пещера и пещера...", "Да ладно тебе...", "Ха! Ну давай, посмотрим, кто крепче!", npchar, Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "CaveBanditosTreasure";
		break;
		
		case "CaveCaribSit":
			if (hrand(2) == 2) 
			{
				dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Бледнолицый","Белая скво")+" уходить прочь. Он"+GetSexPhrase("","а")+" радоваться, что "+npchar.name+" добр. Боги сжалиться над тобой сегодня.", "Убираться из мой пещера, пока я и мой братья не злиться!", "Проваливать прочь, бледнолицый пёс!", "Твоя удача и жизнь подойти к концу, белая собака!", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Ну спасибо, приятель, удружил...", "Пещера не твоя - хочу и хожу.", "Меньше гонору, сын болота.", "Сейчас я заткну эти слова тебе обратно в глотку, скотина...", npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit_talk", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = LinkRandPhrase(""+GetSexPhrase("Проклятый бледнолицый пёс сам","Наглая белая скво сама")+" явиться на наш костёр! О-ей! Тебе конец!","Глуп"+GetSexPhrase("ый","ая")+" яланауи сам"+GetSexPhrase("","а")+" прийти в пасть ягуар. Я поджарить твой печень на костёр!",""+GetSexPhrase("Наглый бледнолицый","Наглая белая скво")+" посметь прийти мой пещера? Тогда он"+GetSexPhrase("","а")+" не выйти отсюда никогда!");
				link.l1 = LinkRandPhrase("Сейчас я тебе язычок-то подкорочу...","Сейчас несколькими каннибалами на земле меньше станет...","Похоже, настало время проделать в твоём бренном теле пару дырок, краснорожая обезьяна...");
				link.l1.go = "fight";
			}
			NextDiag.TempNode = "CaveCaribSit";
		break;
		
		case "CaveCaribStay":
			dialog.text = LinkRandPhrase("Подл"+GetSexPhrase("ый","ая")+" бледнолиц"+GetSexPhrase("ый","ая")+" собака прийти наш пещера! О-ей! Я вырезать твой сердце и зажарить его!","Глуп"+GetSexPhrase("ый","ая")+" яланауи сам"+GetSexPhrase("","а")+" прийти в пасть ягуар. Братья, рубить проклят"+GetSexPhrase("ый","ая")+" бел"+GetSexPhrase("ый","ая")+" "+GetSexPhrase("пёс","собака")+"!",""+GetSexPhrase("Наглый бледнолицый","Наглая белая скво")+" посметь прийти мой пещера? Тогда он"+GetSexPhrase("","а")+" не выйти отсюда никогда!");
			link.l1 = LinkRandPhrase("Сейчас я тебе язычок-то подкорочу...","Сейчас несколькими каннибалами на земле меньше станет...","Похоже, настало время проделать в твоём бренном теле пару дырок, краснорожая обезьяна...");
			link.l1.go = "fight";
		break;
		
		case "exit_talk":
			DialogExit();
			sGroup = "CaveGroup_" + locations[FindLocation(pchar.location)].index;
			for(i=0; i<4; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_CharacterDisableDialog(sld);
			}
			LAi_CharacterEnableDialog(npchar);
		break;
		
		case "fight":
			DialogExit();
			sGroup = "CaveGroup_" + locations[FindLocation(pchar.location)].index;
			for(i=0; i<4; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "CaveEnc_RaidersAfrer");
			chrDisableReloadToLocation = true;
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}