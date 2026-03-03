void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		//----------------- уничтожение банды ----------------------
		case "DestroyGang_begin":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //боевке можно
			DeleteAttribute(&locations[FindLocation(pchar.GenQuest.DestroyGang.Location)], "DisableEncounters"); //энкаунтеры можно 
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
			sTemp = GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.DestroyGang.MayorId)]);
			dialog.text = LinkRandPhrase("Peşin ödeme "+GetSexPhrase("dostum","kız")+"! Benim adım "+GetFullName(npchar)+", ve itirazlara alışık değilim...","Şimdi keseni göster bakalım, "+GetSexPhrase("dostum","kız")+", ve çabuk ol! Benim adım  "+GetFullName(npchar)+", ve umarım hakkımda bir şeyler duymuşsundur...","Üzerindeki tüm değerli eşyaları ver, cüzdanındaki paraya da el koyuyorum. Hadi acele et, sabır bana göre değil. Ama kan dökmeye gelince aynı şeyi söyleyemem!");
			Link.l1 = LinkRandPhrase("Heh, demek o meşhur haydut sensin "+GetFullName(npchar)+", yerel vali hakkında "+sTemp+" hiç susmaz mı?","Demek yerel vali tarafından aranan o haydut sensin "+sTemp+"?!","Memnun"+GetSexPhrase("","")+"seni görmek, "+GetFullName(npchar)+". Yerel vali, "+sTemp+" sadece senden bahsediyor.");
			Link.l1.go = "DestroyGang_1";
		break;		
		case "DestroyGang_1":
			dialog.text = LinkRandPhrase("Evet, bu topraklarda adım bilinir, he-he... Dur bakayım, sen de bir başka  değil misin "+GetSexPhrase("pis köpek","pislik kaltak")+" beni bulmak için onu gönderen valinin mi?","Vali benim iyi arkadaşımdır, bu doğru. Ve sen de, acaba, "+GetSexPhrase("başka bir kahraman, gönderildi","başka bir kahraman, gönderildi")+" onun tarafından başıma mı kondu?","Vali benim en yakın dostumdur, bu sır değil, he-he. Ama bunu nereden biliyorsun? Yoksa seni benim peşime o mu gönderdi?");
			Link.l1 = LinkRandPhrase("Aynen öyle, alçak. Ölümüne hazır ol!","Ne kadar da zekiymişsin! Peki, şimdi tasfiyene geçelim. Yeterince konuştuk.","Evet, benim. Çek silahını, dostum! Bakalım kanının rengi neymiş.");
			Link.l1.go = "DestroyGang_ExitFight";	
			Link.l2 = LinkRandPhrase("Ah, boşver! Böyle dertlere hiç ihtiyacım yok...","Hayır, hayır, ben hiçbir şekilde kahraman değilim...","Hayır, hayır, asla yapmam! Başımı belaya sokmak istemem...");
			Link.l2.go = "DestroyGang_2";	
		break;
		case "DestroyGang_2":
			dialog.text = LinkRandPhrase("Bu daha iyi, "+GetSexPhrase("dostum","kız")+"...Ve şimdi defol!","Ve bu doğru bir karar. Keşke şimdiye kadar kaç kahramanı öteki dünyaya yolladığımı bilseydin... Neyse, yeter bu kadar laf. Kaybol şimdi, "+GetSexPhrase("pislik parçası","orospu")+"!","İyi "+GetSexPhrase("oğlan","kız")+"! Çok akıllıca bir karar - başkalarının işlerine karışmamak... Peki, hadi git bakalım, "+GetSexPhrase("ahbap","kız")+".");
			Link.l1 = "Elveda, sana bol şanslar...";
			Link.l1.go = "DestroyGang_ExitAfraid";	
		break;

		case "DestroyGang_ExitAfraid":
			pchar.GenQuest.DestroyGang = "Found"; //флаг нашёл, но струсил
			npchar.money = AddMoneyToCharacter(npchar, sti(pchar.money));
			pchar.money = 0;
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, LAi_GetCharacterHP(npchar)-1, false, "DestroyGang_SuddenAttack");
			for(i = 1; i < 4; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;	
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
				LAi_SetImmortal(sld, true);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "DestroyGang_SuddenAttack");
			}
			DialogExit();
		break;

		case "DestroyGang_ExitFight":
			for(i = 0; i < 4; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "DestroyGang_Afrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		// ОЗГ - пассажир
		case "ContraPass_abordage":
			dialog.text = "Arghh, seni alçak! Gemime nasıl saldırırsın?! Bunun bedelini ödeyeceksin!";
			link.l1 = "Aksine, aslında bunun için bana para ödüyorlar. Geminizde bir adam var, adı "+pchar.GenQuest.TakePassenger.Name+" . O, ihtiyacım olan kişi.";
			link.l1.go = "ContraPass_abordage_1";
		break;
		
		case "ContraPass_abordage_1":
			dialog.text = "Bu düzenbazın başımıza bela açacağını biliyordum... Ama beni öyle kolayca ele geçiremeyeceksin! Kendini savun, pis korsan!";
			link.l1 = " Savunmayı düşünmesi gereken sensin, köpek.";
			link.l1.go = "ContraPass_abordage_2";
		break;
		
		case "ContraPass_abordage_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "ContraPass_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Tempsailor":
			dialog.text = "Kaptan, emrettiğiniz gibi kamaraları ve ambarı aradık. O alçak saklanmaya çalıştı ama onu bulduk.";
			link.l1 = "Mükemmel! Şimdi nerede?";
			link.l1.go = "Tempsailor_1";
		break;
		
		case "Tempsailor_1":
			dialog.text = "Emir ettiğiniz gibi, ambarın içinde.";
			link.l1 = "Harika! Şimdi bu eski tekneyi terk edelim. Dönme vakti geldi.";
			link.l1.go = "Tempsailor_2";
		break;
		
		case "Tempsailor_2":
			dialog.text = "Hemen, kaptan!";
			link.l1 = "...";
			link.l1.go = "Tempsailor_3";
		break;
		
		case "Tempsailor_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			sld = GetCharacter(NPC_GenerateCharacter("ContraPass", "citiz_"+(rand(9)+11), "man", "man", 10, sti(pchar.GenQuest.TakePassenger.Nation), -1, true, "quest"));
			sld.name = pchar.GenQuest.TakePassenger.Name;
			sld.lastname = "";
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(sld);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.GenQuest.TakePassenger.PrisonerIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
		break;
		
		case "Fugitive_city": // ходит по городу
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = "Ne istiyorsunuz, efendim?";
			link.l1 = "Demek, demek... Yani sen "+pchar.GenQuest.FindFugitive.Name+", değil mi? Sizi gördüğüme çok sevindim...";
			link.l1.go = "Fugitive_city_1";
		break;
		
		case "Fugitive_city_1":
			dialog.text = "Eh, evet, o benim, gerçekten de, ama beni gördüğüne neden sevindin? Bana tuhaf geldi, çünkü seni daha önce hiç görmedim... Açıklamak ister misin?";
			link.l1 = "Elbette. Ben geldim "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity+"Gen")+", yerel valinin emriyle. Tutuklusun ve seni tam da o şehre teslim etmem gerekiyor... Ha, bir de elini kılıcına götürme! Aptalca bir şey deneme, iyi adam, yoksa sonun kötü olur!";
			link.l1.go = "Fugitive_city_2";
		break;
		
		case "Fugitive_city_2":
			dialog.text = "Demek sonunda beni buldunuz... Efendim, lütfen beni dinleyin, belki fikrinizi değiştirirsiniz. Evet, garnizondan firar ettim. Ama ordumuzun bu hale gelmesini izleyemedim!\nSakin bir hayat istedim ve burada, bu köyde böyle bir hayat buldum... Beni rahat bırakın, onlara beni bulamadığınızı ya da korsanlarla açık denize kaçtığımı söyleyin. Karşılığında size bu kehribar kesesini vereceğim. Çok değerli bir şeydir, söylemeliyim...";
			link.l1 = "Beni rüşvetle kandırmayı aklınızdan bile geçirmeyin, efendim! Silahınızı teslim edin ve beni takip edin!";
			link.l1.go = "Fugitive_city_fight";
			link.l2 = "Hmm... Çürüme mi? Sessiz ve huzurlu bir hayat mı? Peki, sanırım dileğini yerine getirebilirim. Kehribarın nerede?";
			link.l2.go = "Fugitive_city_gift";
		break;
		
		case "Fugitive_city_fight":
			dialog.text = "O halde kılıcını çek, paralı asker! Beni öyle kolayca alt edemezsin!";
			link.l1 = "Pekâlâ, görelim neye değersin!";
			link.l1.go = "Fugitive_fight_1";
		break;
		
		case "Fugitive_city_gift":
			TakeNItems(pchar, "jewelry8", 50+hrand(25));
			TakeNItems(pchar, "jewelry7", 2+hrand(5));
			PlaySound("interface\important_item.wav");
			Log_Info("You have received amber");
			dialog.text = "Al bakalım... Ve umarım ne seni ne de başka bir 'elçiyi' bir daha asla görmem.";
			link.l1 = "Sizi temin ederim, olmayacak. Hoşça kalın, efendim!";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_gift_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.FindFugitive = "Found"; //флаг провалил
			AddQuestRecord("MayorsQuestsList", "12-4");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity));
		break;
		
		case "Fugitive_fight_1":// в городе и бухте
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			Diag.currentnode = "Fugitive_afterfight";
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "Fugitive_afterfight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Fugitive_afterfight":
			dialog.text = "Ah! Kazandın, kahretsin seni! Teslim oluyorum...";
			link.l1 = "Diline dikkat et, bayım! Şimdi, lütfen kılıcını bana ver... Peşimden gel, ve sakın aptalca numaralar yapma!";
			link.l1.go = "Fugitive_afterfight_1";
		break;
		
		case "Fugitive_afterfight_1":
			DialogExit();
			RemoveAllCharacterItems(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			//DeleteAttribute(npchar, "LifeDay");
			npchar.lifeday = 0;
			LAi_SetImmortal(npchar, true);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.GenQuest.FindFugitive.PrisonerIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
			pchar.GenQuest.FindFugitive = "Execute"; //флаг выполнил успешно
			pchar.quest.FindFugitive1.win_condition.l1 = "location";
			pchar.quest.FindFugitive1.win_condition.l1.location = pchar.GenQuest.FindFugitive.Startcity+"_townhall";
			pchar.quest.FindFugitive1.function = "FindFugitive_inResidence";
			SetFunctionTimerCondition("FindFugitive_Over", 0, 0, 30, false);
		break;
		
		case "Fugitive_shore": // в бухте
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = "Efendim, sizinle konuşacak havada değilim, o yüzden...";
			link.l1 = "Bununla birlikte, benimle konuşmak zorundasın. Sen "+pchar.GenQuest.FindFugitive.Name+", değil mi? Bence bunu inkar etmemelisin.";
			link.l1.go = "Fugitive_shore_1";
		break;
		
		case "Fugitive_shore_1":
			dialog.text = "Ve bunu inkar edecek değilim, o kişi benim. Ama ne istiyorsun?";
			link.l1 = "Seni   götürmem   gerekiyor "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity)+", yerel vali sizi görmek için sabırsızlanıyor. Lütfen saçmalık yapmayın! Silahınızı teslim edin ve beni takip edin!";
			link.l1.go = "Fugitive_shore_2";
		break;
		
		case "Fugitive_shore_2":
			dialog.text = "Anlıyorum... Efendim, aceleyle hareket etmeden önce size bir şey söylememe izin verin. Evet, garnizondan firar ettim. Ama bunun sebepleri vardı. Hizmette kalamam, bu bana fazla geliyor! Beni anlıyor musunuz? Yapamam!\nHuzurlu bir hayat istiyorum ve onu burada, bu köyde buldum... Beni rahat bırakın, onlara beni bulamadığınızı ya da korsanlarla açık denize kaçtığımı söyleyin. Karşılığında size haftalık inci avımı veririm. Sahip olduğum tek şey bu.";
			link.l1 = "Beni rüşvetle kandırmayı aklınızdan bile geçirmeyin, efendim! Silahınızı teslim edin ve beni takip edin!";
			link.l1.go = "Fugitive_city_fight";
			link.l2 = "Hmm... Askerlikten bıktın mı? Sakin bir hayat mı istiyorsun? Peki, sanırım dileğini gerçekleştirebilirim. İncilerin nerede?";
			link.l2.go = "Fugitive_shore_gift";
		break;
		
		case "Fugitive_shore_gift":
			TakeNItems(pchar, "jewelry52", 100+hrand(40));
			TakeNItems(pchar, "jewelry53", 400+hrand(100));
			PlaySound("interface\important_item.wav");
			Log_Info("You have received pearls");
			dialog.text = "Al bakalım... Ve umarım ne seni ne de başka 'elçileri' bir daha asla görmem.";
			link.l1 = "Sizi temin ederim, olmayacak. Elveda, efendim!";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_tavern": // в таверне
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = "Ehhh... hık! Bayım, ben kimsenin eşliğini aramıyorum - hele sizin hiç. Defolun!";
			link.l1 = "Ama ben SENİN yanında olmak istiyorum, "+pchar.GenQuest.FindFugitive.Name+"! Ve sen de gemimin ambarında bana katlanacaksın. Gidiyoruz  "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity)+", kasabanın valisine. Sizi görmek için can atıyor.";
			link.l1.go = "Fugitive_tavern_1";
		break;
		
		case "Fugitive_tavern_1":
			dialog.text = "H-Hık!"+RandSwear()+" Demek sonunda beni bulmuş! Dinle dostum, ne olduğunu bilmiyorsun, orada değildin! Hizmette kalamazdım, gerçekten yapamazdım! Hâlâ her akşam içiyorum, unutmak için.\nBak, bir anlaşma yapalım. Ona beni bulamadığını ya da korsanlarla açık denize kaçtığımı söyle. Karşılığında, yerel mağarada bulduğum bütün külçeleri sana vereceğim. Hepsi bu kadar, anladın mı? Sahip olduğum her şeyi veriyorum, yeter ki bir daha onu görmek zorunda kalmayayım "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity)+"...";
			link.l1 = "Rüşvet vermeyi aklınızdan bile geçirmeyin, efendim! Silahınızı teslim edin ve beni takip edin!";
			link.l1.go = "Fugitive_tavern_fight";
			link.l2 = "Hmm... Hoş olmayan bir hikaye mi? Kâbuslar mı seni rahatsız ediyor, yoksa vicdan azabı mı çekiyorsun? Peki, sanırım seni bununla baş başa bırakabilirim. Nerede senin altınların?";
			link.l2.go = "Fugitive_tavern_gift";
		break;
		
		case "Fugitive_tavern_gift":
			TakeNItems(pchar, "jewelry5", 50+hrand(30));
			TakeNItems(pchar, "jewelry6", 100+hrand(50));
			PlaySound("interface\important_item.wav");
			Log_Info("You have received nuggets");
			dialog.text = "Al bakalım... Ve umarım ne seni ne de başka bir 'elçiyi' bir daha asla görmem.";
			link.l1 = "Sizi temin ederim, olmayacak. Elveda, efendim!";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_tavern_fight":
			dialog.text = "O halde kılıcını çek, paralı asker! Beni öyle kolayca alt edemezsin!";
			link.l1 = "Pekâlâ, görelim neye değersin!";
			link.l1.go = "Fugitive_fight_2";
		break;
		
		case "Fugitive_fight_2":// в таверне
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetImmortal(npchar, false);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			Diag.currentnode = "Fugitive_afterfight";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "Fugitive_afterfight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
	}
}
