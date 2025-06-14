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
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Alamida_church":
			dialog.text = "... и святого духа. Аминь.";
			link.l1 = "Нечасто вижу военных в церквях.";
			link.l1.go = "Alamida_church_2";
		break;
		
		case "Alamida_church_2":
			dialog.text = "Многие считают, что вера и меч несовместимы. Но разве хирург не режет, чтобы исцелить? Разве отец не наказывает, чтобы уберечь?";
			link.l1 = "Звучит как оправдание.";
			link.l1.go = "Alamida_church_3";
			link.l2 = "В этом есть своя мудрость. Иногда жестокость необходима.";
			link.l2.go = "Alamida_church_4";
		break;
		
		case "Alamida_church_3":
			dialog.text = "Вы ошибаетесь. Это не оправдание - это понимание. Когда я только начинал службу, каждая смерть была... непростой. Но потом... мои глаза открылись. 'Жестокость - это проявление высшей любви'.";
			link.l1 = "Оставлю вас наедине с молитвами.";
			link.l1.go = "Alamida_church_5";
		break;
		
		case "Alamida_church_4":
			dialog.text = "Да... да! Именно так говорил и тот, кто направил меня на этот путь. 'Милосердие без силы бесполезно, как меч без руки'.";
			link.l1 = "Оставлю вас наедине с молитвами.";
			link.l1.go = "Alamida_church_5";
		break;
		
		case "Alamida_church_5":
			dialog.text = "Молитесь и вы. За всех нас. За то, что мы делаем... и что нам предстоит сделать.";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_guber":
			dialog.text = "Семь процентов недостачи. В прошлый раз было пять. Всё растёт, как сорняки в заброшенном саду...";
			link.l1 = "В городе новый губернатор?";
			link.l1.go = "Alamida_guber_2";
		break;
		
		case "Alamida_guber_2":
			dialog.text = "Что? А, нет. Его Светлость там, в углу. Я дон Фернандо де Аламида, королевский ревизор.";
			link.l1 = "Должно быть, тяжёлая работа.";
			link.l1.go = "Alamida_guber_3";
		break;
		
		case "Alamida_guber_3":
			dialog.text = "Знаете, что самое сложное в борьбе с коррупцией? Виновные - не обязательно плохие люди. У них дети, семьи. И каждый раз нужно напоминать себе: яд остаётся ядом, даже если подать его в золотом кубке.";
			link.l1 = "Но разве можно судить так строго? Все мы люди...";
			link.l1.go = "Alamida_guber_4";
			link.l2 = "Вы слишком мягки. Только тюрьма таких исправит.";
			link.l2.go = "Alamida_guber_5";
		break;
		
		case "Alamida_guber_4":
			dialog.text = "Милосердие к волку - жестокость к овцам. Так говорил... один мудрый человек. И я с каждым днём всё больше понимаю его правоту.";
			link.l1 = "Не буду больше отвлекать от работы.";
			link.l1.go = "Alamida_guber_6";
		break;
		
		case "Alamida_guber_5":
			dialog.text = "Хм. Знаете, раньше я думал так же. Но тюрьма - это слишком просто. Нужно что-то большее... Очищение.";
			link.l1 = "Не буду больше отвлекать от работы.";
			link.l1.go = "Alamida_guber_6";
		break;
		
		case "Alamida_guber_6":
			dialog.text = "Да. Бумаги не ждут. Хотя порой мне кажется, что за каждой цифрой здесь прячется чья-то судьба.";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_city":
			dialog.text = "Внимательно вас слушаю, "+GetAddress_Form(NPChar)+"? Что заставило вас подойти ко мне просто так, на улице?";
			link.l1 = "Вы выделяетесь среди остальных.";
			link.l1.go = "Alamida_city_2";
		break;
		
		case "Alamida_city_2":
			dialog.text = "Дон Фернандо де Аламида, королевский ревизор. Вы сегодня первый так"+GetSexPhrase("ой","ая")+" любопытн"+GetSexPhrase("ый","ая")+". Все прячутся, все меня боятся. А ведь честному человеку бояться нечего. О чём это говорит?";
			link.l1 = "Что ваша репутация их устрашает?";
			link.l1.go = "Alamida_city_3";
			link.l2 = "Что честных людей мало?";
			link.l2.go = "Alamida_city_4";
		break;
		
		case "Alamida_city_3":
			dialog.text = "Забавно. Я тоже так думал. Пока не понял - страх очищает. Когда человек боится, он становится честнее. Ближе к своей истинной природе. К Богу.";
			link.l1 = "Интересная мысль. Мне пора идти. Доброго дня, дон Фернандо.";
			link.l1.go = "Alamida_city_5";
		break;
		
		case "Alamida_city_4":
			dialog.text = "Интересно... Вы рассуждаете совсем как один человек, которого я знал. Жаль, что не все способны принять эту истину.";
			link.l1 = "Интересная мысль. Мне пора идти. Доброго дня, дон Фернандо.";
			link.l1.go = "Alamida_city_5";
		break;
		
		case "Alamida_city_5":
			dialog.text = "Доброго? Да, наверное. Главное - чтобы он был праведным.";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_exit":
			DialogExit();
			
			sld = CharacterFromID("SantaMisericordia_clone_church");
			sld.dialog.filename = "Quest\ShipsPack\SantaMisericordia_dialog.c";
			sld.dialog.currentnode = "Alamida_repeat";
			sld = CharacterFromID("SantaMisericordia_clone_city");
			sld.dialog.filename = "Quest\ShipsPack\SantaMisericordia_dialog.c";
			sld.dialog.currentnode = "Alamida_repeat";
			sld = CharacterFromID("SantaMisericordia_clone_guber");
			sld.dialog.filename = "Quest\ShipsPack\SantaMisericordia_dialog.c";
			sld.dialog.currentnode = "Alamida_repeat";
		break;
		
		case "Alamida_repeat":
			dialog.text = "Что-нибудь ещё, капитан?";
			link.l1 = "Нет, дон Фернандо, просто поздороваться, не более.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alamida_repeat";
		break;
		
		case "Alamida_abordage":
			if (startHeroType == 4)
			{
				dialog.text = "Дева с мечом? Вот уж не думал, что доживу до такого. И кто же вы, сеньорита, что осмелились напасть на 'Святое Милосердие'?";
				link.l1 = "Капитан Элен МакАртур. И удивление на вашем лице мне хорошо знакомо.";
				link.l1.go = "Alamida_HelenaCaptain";
			}
			else
			{
				dialog.text = "Как вы посмели?! Напасть на 'Святое Милосердие'?! На корабль, что несёт волю короля и... Что ж. Раз уж вы здесь, скажите - зачем? Зачем вы решились на это безумие?";
				link.l1 = "Я пират. А ваш галеон точно набит ценностями.";
				link.l1.go = "Alamida_abordage_Gold";
				link.l2 = "Такой прекрасный корабль... Я должен им завладеть.";
				link.l2.go = "Alamida_abordage_Ship";
				link.l3 = "Я враг вашей страны, дон Фернандо.";
				link.l3.go = "Alamida_abordage_Hater";
				link.l4 = "Просто так. Почему нет?";
				link.l4.go = "Alamida_abordage_Prikol";
			}
		break;
		
		case "Alamida_HelenaCaptain":
			dialog.text = "Как же вы похожи на Деву Марию-заступницу нашего корабля... Такая же прекрасная. Но Она защищает праведников, а вы...";
			link.l1 = "А я пришла за вашим кораблём. И комплименты тут не помогут, дон Фернандо.";
			link.l1.go = "Alamida_HelenaCaptain_2";
		break;
		
		case "Alamida_HelenaCaptain_2":
			dialog.text = "Печально. Придётся научить вас смирению. Силой, раз уж иначе не получается.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Gold":
			dialog.text = "Ах да. Конечно. Золото. Всегда золото. Яд, что разъедает души. За него вы и умрёте.";
			link.l1 = "Не драматизируйте. Это просто работа.";
			link.l1.go = "Alamida_abordage_Gold_2";
		break;
		
		case "Alamida_abordage_Gold_2":
			dialog.text = "Каждая монета в трюме - плата грешников за очищение. Хотите его получить? Тогда разделите их судьбу.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Ship":
			dialog.text = "Многие заглядывались на 'Святое Милосердие'. Красота его погубила не одного капитана.";
			link.l1 = "Значит, я стану первым, кто его получит.";
			link.l1.go = "Alamida_abordage_Ship_2";
		break;
		
		case "Alamida_abordage_Ship_2":
			dialog.text = "Милосердие без силы бесполезно, как меч без руки. Этот урок вы сегодня усвоите.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Hater":
			dialog.text = "Вот оно что. Очередной завистник величия Империи.";
			link.l1 = "Какое величие? Ваша косность мешает этому миру двигаться вперёд.";
			link.l1.go = "Alamida_abordage_Hater_2";
		break;
		
		case "Alamida_abordage_Hater_2":
			dialog.text = "Не лгите себе. Страх перед Испанией делает вас честнее. Ближе к вашей истинной природе. Сейчас сами увидите.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Prikol":
			dialog.text = "Безумец. А может, вы посланы мне как испытание?";
			link.l1 = "Не всё требует причины, сеньор.";
			link.l1.go = "Alamida_abordage_Prikol_2";
		break;
		
		case "Alamida_abordage_Prikol_2":
			dialog.text = "Он говорил, что такие как вы опаснее всего. Но это только укрепит мою руку в бою.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_SecondRound":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetImmortal(npchar, false);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_BRDENEMY);
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, false);
			LAi_SetCheckMinHP(npchar, 1, true, "SantaMisericordia_TrirdRound");
		break;
		
		case "Alamida_abordage_TrirdRound":
			if (startHeroType == 4)
			{
				dialog.text = "Такая сила духа... Такая воля...";
				link.l1 = "Удивлены?";
			}
			else
			{
				dialog.text = "Неплохо. Давно не встречал достойного противника.";
				link.l1 = "Я не дам вам передышки.";
			}
			link.l1.go = "Alamida_abordage_TrirdRound_2";
		break;
		
		case "Alamida_abordage_TrirdRound_2":
			if (startHeroType == 4)
			{
				dialog.text = "Я был предупреждён... о подобном испытании. О красоте, что может пошатнуть веру воина.";
				link.l1 = "Вы всегда так усложняете простые вещи, дон Фернандо?";
			}
			else
			{
				dialog.text = "Господь даёт силы тем, кто служит благому делу. Хотя... иногда я уже не уверен, чему служу.";
				link.l1 = "Сомневаетесь?";
			}
			link.l1.go = "Alamida_abordage_TrirdRound_3";
		break;
		
		case "Alamida_abordage_TrirdRound_3":
			if (startHeroType == 4)
			{
				dialog.text = "Простые? Нет... В этом должен быть высший смысл. Это - испытание. Я не могу ошибаться.";
			}
			else
			{
				dialog.text = "Нет. Он научил меня не сомневаться. Никогда.";
			}
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_TrirdRound_4";
		break;
		
		case "Alamida_abordage_TrirdRound_4":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetImmortal(npchar, false);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			npchar.MultiFighter = 2.5;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_BRDENEMY);
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, false);
			LAi_SetCheckMinHP(npchar, 1, true, "SantaMisericordia_Molitva");
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			PlaySound("Ambient\Horror\Fear_breath_01.wav");
		break;
		
		case "Alamida_abordage_Molitva":
			dialog.text = "Стойте... Стойте. Вы победили. Я ранен, истекаю кровью. Позвольте помолиться перед смертью.";
			link.l1 = "Хорошо.";
			link.l1.go = "Alamida_abordage_Molitva_2";
		break;
		
		case "Alamida_abordage_Molitva_2":
			if (startHeroType == 4)
			{
				dialog.text = "Господи... прости мне грехи мои и дай сил в этот час испытаний. Благослови души моих павших товарищей. Верные моряки, они погибли, веря что несут правосудие\nОтец, я старался жить по твоим заветам, бороться с несправедливостью. Но твой сын запятнал честь семьи де Аламида. Прости меня\nОтечество... Я клялся служить тебе верой и правдой. Но мой пыл, мой гнев... Я стал тем, с кем сам хотел бороться\nДиего... Может, он лгал? Всё это время... Горе мне, если так\nИ благослови, Господи, эту женщину. Быть может, в своем последнем милосердии ты послал мне именно её... чтобы я увидел, как далеко зашёл. Аминь.";
			}
			else
			{
				dialog.text = "Господи... прости мне грехи мои и дай сил в этот час испытаний. Благослови души моих павших товарищей. Верные моряки, они погибли, веря что несут правосудие\nОтец, я старался жить по твоим заветам, бороться с несправедливостью. Но твой сын запятнал честь семьи де Аламида. Прости меня\nОтечество... Я клялся служить тебе верой и правдой. Но мой пыл, мой гнев... Я стал тем, с кем сам хотел бороться\nДиего... Может, он лгал? Всё это время... Горе мне, если так\nСвятая Дева Мария, моли Бога о нас и даруй нам свое милосердие. Аминь.";
			}
			link.l1 = "Я вас не узнаю, дон Фернандо. Вы словно другой человек сейчас. И о ком это вы?";
			link.l1.go = "Alamida_abordage_Molitva_3";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "Church_Stay_1", "", 5.0);
		break;
		
		case "Alamida_BitvaEnd":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "SantaMisericordia_CanLeaveCauta", 5);
		break;
			
		case "Alamida_abordage_Molitva_3":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			
			DoQuestFunctionDelay("Alamida_abordage_OfficerPodhodit", 2.0);
		break;
		
		//Элен
		case "Alamida_Helena":
			dialog.text = "Мой капитан, я тебя поздравляю! Какое жаркое сражение. Этот капитан был умел, ох как умел. Но ты... ты оказался ещё лучше. Как же я тобой горжусь...";
			link.l1 = "Спасибо тебе, любимая. Ты не ранена?";
			link.l1.go = "Alamida_Helena_2";
		break;
		
		case "Alamida_Helena_2":
			dialog.text = "Нет-нет. Но пару раз подумала, что мы на волоске - и перед абордажем, и во время него. Ну а ты, в порядке?";
			link.l1 = "В порядке, спасибо ещё раз. Иди в каюту и отдохни, я скоро к тебе присоединюсь.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Мэри
		case "Alamida_Mary":
			dialog.text = "Шарль, ты цел? Я прибежала сразу же, как только смогла, да.";
			link.l1 = "Цел, спасибо, родная. Хотя пришлось изрядно попотеть.";
			link.l1.go = "Alamida_Mary_2";
		break;
		
		case "Alamida_Mary_2":
			dialog.text = "Я рада! Но... Послушай, Шарль? А зачем мы напали на этих людей? Господь нам этого не простит, нет. Этот корабль... словно большой храм. Когда я его увидела, моё сердце затрепетало, как когда я увидела настоящую церковь в самый первый раз, а не только в книгах. А теперь оно обливается кровью!";
			link.l1 = "Мэри... Ты же знаешь, что внешность обманчива. И за личиной благочестия скрывались те, кто отнимал деньги у простых верующих - совсем таких же, как ты. Понимаешь?";
			link.l1.go = "Alamida_Mary_3";
		break;
		
		case "Alamida_Mary_3":
			dialog.text = "Я... я верю тебе, Шарль. Да. Только... давай пожертвуем хоть немного золота, что нашли здесь, тем, кто действительно в этом нуждается? Мне было бы легче от этого.";
			link.l1 = "Так и поступим, Мэри. Обещаю. А теперь соберись с мыслями и постарайся успокоиться. Всё кончилось.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Томми
		case "Alamida_Tommi":
			dialog.text = "Хе, ну что же, поздравляю тебя с победой, капитан! Вот это я понимаю, дело! Сколько же всякой всячины на этом галеоне!..";
			link.l1 = "Твоя ухмылка сегодня ещё шире обычного, Томми.";
			link.l1.go = "Alamida_Tommi_2";
		break;
		
		case "Alamida_Tommi_2":
			dialog.text = "Ещё бы! Такая добыча. И такой бой. Я аж Революцию вспомнил. Да и... хех.";
			link.l1 = "Что такое, Томми? Ну говори.";
			link.l1.go = "Alamida_Tommi_3";
		break;
		
		case "Alamida_Tommi_3":
			dialog.text = "Как они расфуфырили весь корабль, словно собор плавучий. И золота столько понабрали отовсюду. Настоящие святоши-паписты! Позор и смехота.";
			link.l1 = "Это казначейский корабль, Томми. А золото нужно охранять.";
			link.l1.go = "Alamida_Tommi_4";
		break;
		
		case "Alamida_Tommi_4":
			dialog.text = "Ну, может быть. В любом случае, я был рад преподать хороший урок донам и папистам! Терпеть не могу ни тех, ни других. Я насладился этим днём сполна, ха-ха-ха!";
			link.l1 = "Ну ты как всегда! Ладно, иди, вольно. У меня здесь всё в порядке.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Тичингиту
		case "Alamida_Tichingitu":
			if (startHeroType == 1)
			{
				dialog.text = "Капитан Шарль, наш одержать победа. Это быть нелёгкий бой. Даже Тичингиту прийтись трудно, а ведь мой быть один из лучший воин деревня.";
				link.l1 = "Верно, друг мой. Это были весьма достойные противники.";
			}
			if (startHeroType == 2)
			{
				dialog.text = "Сеньор де Монтойя, корабль быть наш.";
				link.l1 = "Очень хорошо, Тичингиту. Я как раз здесь закончил.";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Капитан Патерсон, последний очаг сопротивление подавлен на корабль.";
				link.l1 = "Опаздываешь, Тич! В следующий раз лучше иди со мной. Не то чтобы я не справился один, впрочем...";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Капитан МакАртур, ваш быть порядок?";
				link.l1 = "Да, Тичингиту, я в порядке, спасибо, что спросил. И перестань уже сомневаться в своём капитане - я отлично справилась и сама.";
			}
			link.l1.go = "Alamida_Tichingitu_2";
		break;
		
		case "Alamida_Tichingitu_2":
			if (startHeroType == 1)
			{
				dialog.text = "Духи сказать мне это во время бой. И спрашивать, зачем мой их губить. А теперь мой об этом спрашивать ваш. Тичингиту видеть по их глаза, что они не быть негодяи. Пока не быть.";
				link.l1 = "Эх, и вот что тебе скажешь? Нет у меня ответа, Тичингиту.";
			}
			if (startHeroType == 2)
			{
				dialog.text = "Мой хотеть спросить ваш, капитан де Монтойя.";
				link.l1 = "Слушаю тебя.";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Тичингиту хотеть задать ваш вопрос, капитан Вильям, если ваш разрешить.";
				link.l1 = "Разрешаю.";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Мой не сомневаться, мой волноваться за ваш, капитан.";
				link.l1 = "Хорошо, хорошо. Вижу по твоим глазам, что ты хочешь что-то ещё у меня спросить.";
			}
			link.l1.go = "Alamida_Tichingitu_3";
		break;
		
		case "Alamida_Tichingitu_3":
			if (startHeroType == 1)
			{
				dialog.text = "Хм-м-м, как ваш сказать, капитан. Наш закончить здесь?";
				link.l1 = "СДа. Я ещё осмотрюсь немного, а потом присоединюсь к остальным.";
				link.l1.go = "Alamida_BitvaEnd";
			}
			if (startHeroType == 2)
			{
				dialog.text = "Этот люди, разве они не быть из тот же племя, что и ваш? Разве они не быть испанец? Почему ваш решить напасть?";
				link.l1 = "Всё так. Но разве племена индейцев не воюют друг с другом тоже? Или разве внутри одного племени не бывает ссор и распрей?";
				link.l1.go = "Alamida_Tichingitu_4";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Этот корабль выглядеть, как церковь. Ваш ненавидеть церковь и белый бог?";
				link.l1 = "Отнюдь. Но это лишь украшение, понимаешь? Это казначейский корабль. Впрочем, куда тебе - я слышал, что у вас, краснокожих, даже понятия налогов нет.";
				link.l1.go = "Alamida_Tichingitu_4";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Да. Быть так. Капитан МакАртур, а зачем наш напасть на этот плавучий церковь?";
				link.l1 = "Плавучая церковь, ха-ха-ха! Нет-нет. Это казначейский корабль. Хм, вижу, немного не понимаешь. В общем, они перевозили золото. Представляю, как мной будет гордиться Ян, когда я ему скажу, что одолела Фернандо де Аламиду!";
				link.l1.go = "Alamida_Tichingitu_4";
			}
		break;
		
		case "Alamida_Tichingitu_4":
			if (startHeroType == 2)
			{
				dialog.text = "Хм, ваш быть прав, капитан. Но у индеец это случаться реже, чем у белый человек.";
				link.l1 = "Возможно. Что ж, этот человек мне... мешал.";
				link.l1.go = "Alamida_Tichingitu_5";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Быть так, у маскоги нет замки и налоги.";
				link.l1 = "Вот-вот. Можешь идти, всё равно припоздал. Потом будем решать, что делать с этим красавцем-галеоном. Не люблю эти бочки, но, чёрт, как же он хорош.";
				link.l1.go = "Alamida_BitvaEnd";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Тичингиту тоже гордиться ваш, капитан. И поздравлять с этот славный победа.";
				link.l1 = "Спасибо тебе. А теперь давай займёмся дележом добычи.";
				link.l1.go = "Alamida_BitvaEnd";
			}
		break;
		
		case "Alamida_Tichingitu_5":
			dialog.text = "Мешал, сеньор де Монтойя?";
			link.l1 = "Именно. Этот Архипелаг слишком мал для нас двоих. И от меня в нём гораздо больше пользы нашему государству. Вспомни Листа Какао - от него было больше вреда, нежели пользы для его собратьев. Так и здесь.";
			link.l1.go = "Alamida_Tichingitu_6";
		break;
		
		case "Alamida_Tichingitu_6":
			dialog.text = "Теперь мой понять. Тичингиту мочь идти, капитан?";
			link.l1 = "Да, иди. Я тоже скоро к вам всем присоединюсь.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			dialog.text = LinkRandPhrase("Чего вы клинком размахиваете?! Немедленно уберите оружие!", "Приказываю вам немедленно убрать оружие!", "Эй, " + GetAddress_Form(NPChar) + ", не пугайте народ! Уберите оружие.");
			link.l1 = LinkRandPhrase("Хорошо, убираю...", "Уже "+ GetSexPhrase("убрал","убрала") +".", "Как скажешь...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Чёрта с два!", "Сейчас пущу его в дело!", "Уберу, когда время придёт.");
			link.l2.go = "fight";
		break;
		
	}
} 