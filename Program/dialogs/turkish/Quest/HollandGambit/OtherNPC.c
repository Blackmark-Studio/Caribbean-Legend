// диалоги прочих НПС
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Bir hata var. Geliştiricilere söyle.";
			link.l1 = "Yapacağım!";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			if (npchar.id == "HWICFernando") NextDiag.CurrentNode = "Fernando";
			DialogExit();
		break;
	
//---------------------------------------за Голландию--------------------------------------------------
		//сопроводить торговца
		case "Baltazar":
			pchar.quest.Create_BaltazarOver.over = "yes";//снять прерывание
			dialog.text = "Ne şans ama! Kaptan, tesadüfe bakın ki benim de acilen Philipsburg'a bir refakate ihtiyacım var...";
			link.l1 = "Balthazar Ridderbock sen misin?";
			link.l1.go = "Baltazar_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Baltazar_1":
			dialog.text = "Ne oluyor yahu, ben zaten genel validen daha ünlüyüm! Sen kimsin? Ne istiyorsun?";
			link.l1 = "Ben Kaptanım "+GetFullName(pchar)+". Lucas Rodenburg tarafından size gönderildim. Sizi ve geminizi korumam altına almam için yetkilendirildim.";
			link.l1.go = "Baltazar_2";			
		break;
		
		case "Baltazar_2":
			dialog.text = "Ah, Rodenburg Bey kesin benim yardım çağrılarımı duymuş olmalı! Bakın, bir korsan var...";
			link.l1 = "Hikayenin ayrıntılarını atlayalım, zaten biliyorum.";
			link.l1.go = "Baltazar_3";			
		break;
		
		case "Baltazar_3":
			dialog.text = "Elbette! Zaten çok fazla zaman kaybettim... En geç iki hafta içinde Philipsburg'a ulaşmalıyım.";
			link.l1 = "O halde gemine git ve sefere hazırlık yap. Hemen yola çıkıyoruz!";
			link.l1.go = "Baltazar_4";			
		break;
		
		case "Baltazar_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 4);
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //всегда друзья
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
			AddQuestRecord("Holl_Gambit", "1-3");
			AddMapQuestMarkCity("Marigo", true);
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Baltazar_ConvoyOver", 0, 0, 28, false);
			}
			else SetFunctionTimerCondition("Baltazar_ConvoyOver", 0, 0, 14, false); //таймер
			pchar.quest.BaltazarConvoy_fail.win_condition.l1 = "NPC_Death";//прерывание на потопление сопровождаемого
			pchar.quest.BaltazarConvoy_fail.win_condition.l1.character = "Baltazar";
			pchar.quest.BaltazarConvoy_fail.function = "Baltazar_fail";
			pchar.quest.BaltazarConvoy_complete.win_condition.l1 = "location";//прерывание на выполнение
			pchar.quest.BaltazarConvoy_complete.win_condition.l1.location = "Marigo_town";
			pchar.quest.BaltazarConvoy_complete.function = "Baltazar_complete";
			if (rand(1) == 0)
			{
				BaltazarPirateGlobalCreate();
			}
			else
			{
				pchar.questTemp.HWIC.Holl.BaltazarAttack = "true";
				pchar.quest.BaltazarConvoy_Attack.win_condition.l1 = "location";//прерывание на выполнение
				pchar.quest.BaltazarConvoy_Attack.win_condition.l1.location = "SentMartin";
				pchar.quest.BaltazarConvoy_Attack.function = "BaltazarPirateSeaCreate";
			}
		break;
		
		case "Baltazar_5":
			dialog.text = "Yardımınız için teşekkür ederim, Kaptan! Korumanız tam zamanında yetişti. Lütfen minnettarlığımı ve bu 5.000 pesoyu kabul edin.";
			link.l1 = "Hmm... Bir hayat kurtarmak için bu ödül pek cömert sayılmaz...";
			link.l1.go = "Baltazar_6";			
		break;
		
		case "Baltazar_6":
			dialog.text = "Ayrıca, fırsat bulduğumda Bay Rodenburg’a da bir mektup göndereceğim – yaptıklarınızı en yüksek şekilde takdir ettiğimi belirteceğim. Şimdi gitmem gerek.";
			link.l1 = "Pekala, öyleyse elveda, Balthazar.";
			link.l1.go = "Baltazar_7";			
		break;
		
		case "Baltazar_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 3.0);
			AddQuestRecord("Holl_Gambit", "1-6");
			AddMoneyToCharacter(pchar, 5000);
			ChangeCharacterComplexReputation(pchar,"nobility", 2); 
			ChangeCharacterNationReputation(pchar, HOLLAND, 1);
			ChangeOfficersLoyality("good_all", 1);
			pchar.questTemp.HWIC.Holl = "BaltazarCom";
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddMapQuestMarkCity("Villemstad", true);
		break;
		
		//командировка в Сантьяго
		case "Santiago_Trip":
			dialog.text = "Beyefendi! Bekleyin... galiba bir şey düşürdünüz...";
			link.l1 = "Ne? Ha?!";
			link.l1.go = "Santiago_Trip_1";
		break;
		
		case "Santiago_Trip_1":
			DialogExit();
			PlaySound("People Fight\Death_NPC_08.wav");
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("You were knocked unconscious from behind", "", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 15, 10); //крутим время
			RecalculateJumpTable();
			DoQuestFunctionDelay("SantiagoTripInHouse", 4.0);
		break;
		
		case "Santiago_Trip_2":
			dialog.text = "Üzgünüm dostum – sana hafifçe vurmak zorunda kaldım, yoksa başımıza iş açardın. Başının ağrıdığını tahmin ediyorum ama neyse, ölmezsin ya. Tabii vaktimiz kalırsa...";
			link.l1 = "Sen kimsin, lanet olsun, burada neler oluyor?";
			link.l1.go = "Santiago_Trip_3";
		break;
		
		case "Santiago_Trip_3":
			dialog.text = "Sakin ol, sakin ol dostum – yoksa seni yine sakinleştirmek zorunda kalacağım. O düzenbazların paslı kılıçlarını şakırdatarak içeri dalmasını istemeyiz, değil mi? Sessizce konuşmamız lazım.";
			link.l1 = "Kılıcımı geri ver, alçak, sonra güzelce konuşacağız, yemin ederim!";
			link.l1.go = "Santiago_Trip_4";
		break;
		
		case "Santiago_Trip_4":
			dialog.text = "Sen hızlı bir adamsın, değil mi? Şimdilik çeliğe başvurmaya gerek yok. Bana bilmek istediğimi söyle, belki de buradan tek parça halinde çıkarsın. Anlaştık mı? O zaman biraz sohbet edelim.\nSessiz kalıyorsun ha? Güzel, demek anlaştık. Rodenburg'dan bankacıya ne taşıdın?";
			link.l1 = "Bir mektup.";
			link.l1.go = "Santiago_Trip_5";
		break;
		
		case "Santiago_Trip_5":
			dialog.text = "Zekice. O çiçek buketi olmadığını biliyorum. O mektupta ne yazıyordu, çocuk?";
			link.l1 = "Ben nereden bileyim? Bana emanet edilen mektupları okumak gibi bir alışkanlığım yok. Belki de bir aşk mektubuydu. Güç sahibi insanlar hakkında neler söylenir, bilirsin...";
			link.l1.go = "Santiago_Trip_6";
		break;
		
		case "Santiago_Trip_6":
			dialog.text = "...Bu sefil zamanlarda dürüst bir kaptan görmek gerçekten nadir bir şey. Eh, bu senin için kötü haber. Şu lanet bankacı paketi alınca ne dedi? Hollandalılarla ne tür bir işi varmış?";
			link.l1 = "Fransa'dan kaçak parfüm ticareti yapıyorlar... ya da Bavyera inek gübresi, sanırım.";
			link.l1.go = "Santiago_Trip_7";
			link.l2 = "Soru, bir şeyin karşılığında ödenecek tazminat hakkındaydı. Bildiğim tek şey bu.";
			link.l2.go = "Santiago_Trip_8";
		break;
		
		case "Santiago_Trip_7":
			dialog.text = "Sen cesur bir adamsın... Üstelik mizah anlayışın da var. Seni öldürmek yazık olurdu. Gaston da senden hoşlanırdı. Yine de... şimdilik burada kal. Ben gidip bir şeye bakmalıyım, yokluğumda Miguel sana göz kulak olacak.";
			link.l1 = "Yemin ederim, 'dostum' – bunun bedelini ödeyeceksin! ";
			link.l1.go = "Santiago_Trip_9";
		break;
		
		case "Santiago_Trip_8":
			dialog.text = "Kibir yine baş gösterdi... İşler kötüye gidince, bizim cesur kaptan biraz akıllanıyor. Bunu daha önce de yapabilirdin, hem zamanımızı hem de başımızı kurtarırdın. Neyse, şimdi gidip bir şey kontrol etmem lazım, sonra dönerim ve hâlâ gerekirse konuşuruz. Şimdilik burada kal. Ben yokken Miguel sana göz kulak olacak.";
			link.l1 = "Yemin ederim, 'dostum' – bunun bedelini ödeyeceksin! ";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_9":
			dialog.text = "Elbette. Sessiz ol, 'kahraman' - belki her şey hâlâ yoluna girebilir.";
			link.l1 = "...";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_10":
			dialog.text = "Burada kal ve esnekliğinin işe yarayacağını um.";
			link.l1 = "...";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_11":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-44");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "Santiago_HouseSp2", "goto", "goto4", "", -1);
			pchar.quest.Santiago_Trip1.win_condition.l1 = "item";
			pchar.quest.Santiago_Trip1.win_condition.l1.item = "slave_01";
			pchar.quest.Santiago_Trip1.function = "SantiagoTrip_wait";
		break;
		
		case "Santiago_Trip_12":
			dialog.text = "Ne oluyor böyle?!";
			link.l1 = "Ölmeye hazır ol, seni alçak!";
			link.l1.go = "Santiago_Trip_13";
		break;
		
		case "Santiago_Trip_13":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "SantiagoTripExitFromRoom");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Santiago_Trip_14":
			dialog.text = "Ne karmaşa ama! Bu gürültünün sebebini merak ediyordum. Tebrikler – akıllı adammışsın!";
			link.l1 = "Sandığından daha akıllıymışsın... Bakalım şimdi silahlı bir rakibe karşı neler yapabileceksin!";
			link.l1.go = "Santiago_Trip_15";
		break;
		
		case "Santiago_Trip_15":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "SantiagoTripExitHouse");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		//офицер-посланник по 5 заданию
		case "HollQuest_Officer":
			dialog.text = "Mynheer Lucas Rodenburg sizi hemen görmek istiyor. Derhal yanına gidin.";
			link.l1 = "Yoldayım.";
			link.l1.go = "HollQuest_Officer_exit";			
		break;
		
		case "HollQuest_Officer_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			pchar.questTemp.HWIC.Holl = "MerdokStart";
			AddQuestRecord("Holl_Gambit", "1-36");
		break;
		
//---------------------------------------------против всех----------------------------------------------
		//убрать испанского идальго
		case "Fernando":
			dialog.text = "Benden ne istiyorsun?";
			link.l1 = "Kafanı koparırım!";
			link.l1.go = "Fernando_fight";
			link.l2 = "Boşver, önemli değil.";
			link.l2.go = "exit";	
			NextDiag.TempNode = "Fernando_repeat";
		break;
		
		case "Fernando_repeat":
			dialog.text = "Yine sen misin? Benden ne istiyorsun?! Açıkla kendini!";
			link.l1 = "Kafanı koparırım!";
			link.l1.go = "Fernando_fight";
			link.l2 = "Boşver, önemli değil.";
			link.l2.go = "exit";	
			NextDiag.TempNode = "Fernando_repeat";		
		break;
		
		case "Fernando_fight":
			chrDisableReloadToLocation = true;//выходы закроем
			LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "SPAIN_CITIZENS");
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
			pchar.quest.HWIC_Fernando.win_condition.l1 = "NPC_Death";
			pchar.quest.HWIC_Fernando.win_condition.l1.character = "HWICFernando";
			pchar.quest.HWIC_Fernando.function = "Fernando_died";
		break;
		
		//в доме Флитвуда
		case "Fleetwood_soldier"://для любителей сунуть нос куда не надо
			if (CheckAttribute(npchar, "quest.talked"))
			{
			dialog.text = "Yine sen mi geldin? Burada ne diye dolanıyorsun? Hiç hoşuma gitmiyor bu. Tamam, seni tutuklayıp komutanın ofisine sorguya göndereceğim. Çocuklar, bunu yakalayın!";
			link.l1 = "Ama ben sadece...";
			link.l1.go = "Fleetwood_soldier_4";	
			}
			else
			{
			dialog.text = "Sen kimsin ve ne istiyorsun? Kendini açıkla!";
			link.l1 = "Üzgünüm efendim, galiba yanlış eve geldim. Affınıza sığınıyorum.";
			link.l1.go = "Fleetwood_soldier_1";	
			link.l2 = "Richard Fleetwood'u görmek istiyorum.";
			link.l2.go = "Fleetwood_soldier_2";		
			}
		break;
		
		case "Fleetwood_soldier_1":
			dialog.text = "Doğru. Yanlış adamla konuşuyorsun. Lütfen hemen buradan ayrıl!";
			link.l1 = "Evet. Tabii.";
			link.l1.go = "Fleetwood_soldier_3";			
		break;
		
		case "Fleetwood_soldier_2":
			dialog.text = "Gerçekten mi? Sana burada yaşadığını kim söyledi? Bu kulağa şüpheli geliyor... Pekâlâ, seni tutuklayıp sorgulanmak üzere komutanın ofisine göndereceğim. Çocuklar, bu adamı yakalayın!";
			link.l1 = "Ama ben sadece Richard'ı görmek istemiştim...";
			link.l1.go = "Fleetwood_soldier_4";	
		break;
		
		case "Fleetwood_soldier_3":
			DialogExit();
			npchar.quest.talked = "true";
			DoQuestReloadToLocation("SentJons_town", "reload", "houseSP3", "");
			pchar.quest.Fleetwood_Soldier.win_condition.l1 = "location";
			pchar.quest.Fleetwood_Soldier.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Fleetwood_Soldier.function = "Fleetwood_Soldier";//для настырных
		break;
		
		case "Fleetwood_soldier_4":
			DialogExit();
			GoToPrison("SentJons", 1000, 10);			
		break;
		
		case "Theft_soldier":
			dialog.text = "Ah! Hırsızlar mı? Casuslar mı? Şapkanızı sıkı tutun şimdi!";
			link.l1 = "Hup!";
			link.l1.go = "Attack_Theft_soldier";			
		break;
		
		case "Attack_Theft_soldier":
			LAi_group_Delete("EnemyFight");
			LAi_SetHP(npchar, 500, 500);
			LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Attack_soldier":
			dialog.text = "Ah! Bu adam burada ne arıyor? Çocuklar, aramızda bir casus var! Silah başına!";
			link.l1 = "Hup!";
			link.l1.go = "Attack_soldier_fight";			
		break;
		
		case "Attack_soldier_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//снять запрет драки
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=4; i++)
			{
			sld = characterFromId("Attack_sold_"+i);	
			LAi_SetWarriorType(sld);
            LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PrepareToStreetFight");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		//Книппель-пленник в трюме
		case "Sailor_deck":
			chrDisableReloadToLocation = true;
			dialog.text = "Kaptan, bu herifi sorguladık, dediğiniz gibi. Biraz dağlamak zorunda kaldık... Üzerinde bu mektup vardı. Yutmaya kalktı ama izin vermedik. Dediğimiz gibi, Willemstad'da bir kızı alıp patronuna götürmesi gerekiyormuş.";
			link.l1 = "Bir mektup mu? Göster bakalım. Sonra kendim konuşurum onunla.";
			link.l1.go = "Sailor_deck_1";			
		break;
		
		case "Sailor_deck_1":
			DialogExit();
			AddLandQuestMark(characterFromId("KnippelClone"), "questmarkmain");
			GiveItem2Character(pchar, "NPC_Letter");
			AddQuestRecordInfo("LetterToAbi", "1");
		break;
		
		case "Sailor_deck_2":
			dialog.text = "Emirleriniz nedir, Kaptan?";
			link.l1 = "Cesedi denize atın. Ve karaya çıkmaya hazırlanın!";
			link.l1.go = "Sailor_deck_3";			
			// belamour legendary edition -->
			link.l2 = "Onu tam askeri törenle denize gömün. O yaşlı adam sonuna kadar cesurca savaştı. Top arabasından düşen o topu bile tekrar doldurup nişan aldı. Gerçekten yazık. Başka bir dünyada belki de yoldaş olabilirdik...";
			link.l2.go = "Sailor_deck_3a";
		break;
		
		case "Sailor_deck_3a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			dialog.text = "Evet, Kaptan!";
			link.l1 = "...";
			link.l1.go = "Sailor_deck_4";			
		break;
		
		case "Sailor_deck_3":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 120);
			AddCharacterExpToSkill(pchar, "FencingL", 30);
			AddCharacterExpToSkill(pchar, "FencingS", 30);
			AddCharacterExpToSkill(pchar, "FencingH", 30);
			AddCharacterExpToSkill(pchar, "Pistol", 30);
			// <-- legendary edition
			dialog.text = "Başüstüne, Kaptan!";
			link.l1 = "...";
			link.l1.go = "Sailor_deck_4";			
		break;
		
		case "Sailor_deck_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			AddQuestRecord("Holl_Gambit", "3-21");
			LAi_SetActorType(pchar);
			sld = characterFromId("KnippelClone");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("Sailor_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "ReturnMCPlayer", 3);
			}
			pchar.questTemp.HWIC.Self = "toVillemstad";
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_2";
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("Villemstad", false);
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//откроем дом Аби
			LocatorReloadEnterDisable("Villemstad_houseSP2", "reload2", true);//закроем комнату Аби
		break;
		
		//Лонгвэй-пленник в трюме
		case "Sailor_deck_5":
			chrDisableReloadToLocation = true;
			dialog.text = "Çinliyi sorguya hazırladık, emrettiğiniz gibi, Kaptan. Üzerinde hiçbir şey yoktu, ne belge ne de başka bir şey. Bir mangal kurduk, kelepçeleri ve kerpetenleri kıpkırmızı olana kadar ısıtıyoruz.";
			link.l1 = "Güzel iş, Alonso. Ama başlamadan önce, onunla konuşmayı denemek istiyorum. Belki de kendi isteğiyle iş birliği yapmaya karar verir?";
			link.l1.go = "Sailor_deck_6";			
		break;
		
		case "Sailor_deck_6":
			dialog.text = "Dediğiniz gibi, Kaptan.";
			link.l1 = "...";
			link.l1.go = "exit";	
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
		break;
		
		case "Sailor_deck_7":
			dialog.text = "Evet, Kaptan?";
			link.l1 = "Onu kelepçeye vurun ve Guadeloupe'a varana kadar gözünüzü üzerinden ayırmayın. Siz üçünüz her zaman burada olacaksınız. Onun için canınızla hesap verirsiniz.";
			link.l1.go = "Sailor_deck_8";			
		break;
		
		case "Sailor_deck_8":
			dialog.text = "Başüstüne, Kaptan!";
			link.l1 = "";
			link.l1.go = "Sailor_deck_9";			
		break;
		
		case "Sailor_deck_9":
			chrDisableReloadToLocation = false;
			AddQuestRecord("Holl_Gambit", "3-48");
			sld = characterFromId("LongwayClone");
			LAi_SetActorType(sld);
			LAi_SetGroundSitType(sld);
			DialogExit();
			pchar.quest.Longway_Shore.win_condition.l1 = "location";
			pchar.quest.Longway_Shore.win_condition.l1.location = "Shore31";
			pchar.quest.Longway_Shore.function = "LongwayInShore";
			AddMapQuestMarkShore("Shore31", true);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		//пьяница - передача письма Флитвуду
		case "Drunkard":
			DelLandQuestMark(npchar);
			dialog.text = "H-ık! İyi akşamlar, efendim! Ne alırdınız? Belki yaşlı bir sarhoşa bir içki ısmarlarsınız? Ve ben...";
			link.l1 = "Dinle bakalım, yaşlı ayyaş... Sen Jack Harrison mısın?";
			link.l1.go = "Drunkard_1";			
		break;
		
		case "Drunkard_1":
			dialog.text = "Oh! Evet, o benim. Başka kim olabilir ki? Neden? Ne ya-pa-ca-ğız sa-rhoş bir de-niz-ci-i-yle...";
			link.l1 = "Aman Tanrım, bana sabır ver! Hangi denizci? Suratından anlaşılıyor ki sen karacısın... Biraz para kazanmak ister misin?";
			link.l1.go = "Drunkard_2";			
		break;
		
		case "Drunkard_2":
			dialog.text = "Her zaman para kazanmak isterim. Ne yapmalıyım? Ama kimseyi öldürmem. Bir şey de çalmam. Hem sen de bana göre değilsin.";
			link.l1 = "Kimseyi öldürmek zorunda kalmayacaksın, zaten bunu yapabileceğinden de şüpheliyim. Fazla beceriksizsin. Şimdi. Al bu mektubu. Valinin konutunun solundaki eve götür ve teslim et. Mektup Richard Fleetwood'a gönderildi.";
			link.l1.go = "Drunkard_3";			
		break;
		
		case "Drunkard_3":
			dialog.text = "Richard Fleetwood için mi? Hayır... Beni görür görmez tutuklarlar.";
			link.l1 = "Sessiz ol ve dinle. Kimse seni tutuklamayacak. Abigail hakkında Charlie Knippel'den geldiğini söyleyeceksin. Seni içeri alacaklar. Söylediklerimi tekrar et.";
			link.l1.go = "Drunkard_4";			
		break;
		
		case "Drunkard_4":
			dialog.text = "Abigail kim? Knippel'i biliyorum...";
			link.l1 = "Bu seni ilgilendirmez. Ne kadar az bilirsen, o kadar uzun yaşarsın. Hadi, bekliyorum. Tekrar et.";
			link.l1.go = "Drunkard_5";			
		break;
		
		case "Drunkard_5":
			dialog.text = "Charlie Knippel'den geldim, senin... Abigail'in hakkında. Evet, doğru. ";
			link.l1 = "Aferin. Bu iş için 5.000 peso alacaksın.";
			link.l1.go = "Drunkard_6";			
		break;
		
		case "Drunkard_6":
			if (makeint(Pchar.money) >= 5000)
			{
				dialog.text = "5000 peso mu? Ah... Sadece bir mektup teslim etmek için mi?";
				link.l1 = "Hayır. Sana başka bir mektup verilecek. Onu meyhaneye getirip burada oturacaksın. Mektubu senden ben alacağım. Aptalca bir şey yapma ve korkma – seni izleyeceğim ve yakınında olacağım. Şunu da avans olarak al, rahat olman için.";
				link.l1.go = "Drunkard_7";	
			}
			else
			{
				dialog.text = "Beş bin mi? O kadar paran var mı gerçekten?";
				link.l1 = "Ha! Tabii ki aldım. Hemen getiriyorum.";
				link.l1.go = "Drunkard_no_money";	
				NextDiag.CurrentNode = "Drunkard_no_money";
			}
		break;
		
		case "Drunkard_no_money":
			dialog.text = "Beş bin getirdin mi?";
			if (makeint(Pchar.money) >= 5000)
			{
				link.l1 = "Evet. Buyurun. Merak etmeyin.";
				link.l1.go = "Drunkard_7";
			}
			else
			{
				link.l1 = "Hayır. Bekle. Yakında döneceğim.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Drunkard_no_money";
			}
		break;
		
		case "Drunkard_7":
			AddMoneyToCharacter(pchar, -5000);
			RemoveItems(PChar, "MC_Letter", 1);
			dialog.text = "Hmm... Şimdi gitmeli miyim, efendim?";
			link.l1 = "Hayır, Perşembe sabahı... Tabii ki, tam şimdi, seni sersem! Şimdi romunu bitir ve defol!";
			link.l1.go = "Drunkard_8";			
		break;
		
		case "Drunkard_8":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-26");
			LAi_SetStayType(npchar);
			LAi_RemoveLoginTime(npchar);//удалить время загрузки
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, "sentjons_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "sentjons_town", "reload", "reload4_back", "DrunkardGoTown", -1);
			chrDisableReloadToLocation = true;//закрыть локацию
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", true);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", true);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", true);//чтобы не сбежал
		break;
		
		case "Drunkard_9":
			DelLandQuestMark(npchar);
			dialog.text = "Ah, işte buradasınız efendim... Keşke bunu yapmasaydım. Richard okumayı bitirdiğinde öfkelendi. Beni öldürecek sandım.";
			link.l1 = "Ama işte buradasın! Merak etme - buna asla cesaret edemezdi - o anda sen onun için fazlasıyla değerliydin, ha-ha! Ne kadar değerli olduğunu tahmin bile edemezsin...";
			link.l1.go = "Drunkard_10";			
		break;
		
		case "Drunkard_10":
			dialog.text = "Bir içkiye ihtiyacım var... İşte sana verdiği cevap.";
			link.l1 = "Bunu bana ver! Ve çeneni kapa!";
			link.l1.go = "Drunkard_11";			
		break;
		
		case "Drunkard_11":
			GiveItem2Character(pchar, "MC_Letter");
			ChangeItemDescribe("MC_Letter", "itmdescr_MC_Letter1");
			AddQuestRecordInfo("FleetwoodAnswer", "1");
			dialog.text = "Önümüzdeki birkaç gün konuşmam zor olacak... Hoşça kal... Umarım bir daha seni hiç görmem.";
			link.l1 = "Sakin ol, yaşlı ayyaş, ha-ha-ha! Ne ya-pa-ca-ğız sa-rhoş deniz-ciy-le... İç ve rahatla - artık her şey bitti!";
			link.l1.go = "Drunkard_12";			
		break;
		
		case "Drunkard_12":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Holl_Gambit", "3-27");
			pchar.questTemp.HWIC.Self = "FleetwoodAgree";
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		//кэп курьерского судна
		case "Cureer_abordage":
			dialog.text = "Neden gemime saldırdın, Allah aşkına? Ne değerli eşyam var, ne de param—sadece bir kaç evrak, onlar da sana hiçbir fayda sağlamaz!";
			link.l1 = "Kes sesini. Kaybettin, şimdi beni dinleyeceksin. Ne gemine ne de evraklarına ihtiyacım var. Bana lazım olan tek şey, bu mesajı patronuna, o pis fare Lucas Rodenburg'a iletmen. Ona de ki, Kaptan Fleetwood selamlarını gönderiyor.";
			link.l1.go = "Cureer_abordage_1";			
		break;
		
		case "Cureer_abordage_1":
			dialog.text = "Kaptan Fleetwood? Ama...";
			link.l1 = "Bu mektubu patronuna verecek misin – yoksa seni doğramamı mı istersin? Teslimat için başka bir aday da bulabilirim. Sırf can sıkıntısından her hafta sonu senin o pis Kompaninin gemilerini soyuyorum, haberin olsun.";
			link.l1.go = "Cureer_abordage_2";			
		break;
		
		case "Cureer_abordage_2":
			dialog.text = "Pekâlâ, Bay Fleetwood. Onu teslim edeceğim.";
			link.l1 = "Harika. Artık birbirimize veda edebiliriz, Mynheer. Bugün kendini gerçekten şanslı sayabilirsin. Ve vardığında bir kiliseye uğramayı unutma!";
			link.l1.go = "Cureer_abordage_3";			
		break;
		
		case "Cureer_abordage_3":
			DialogExit();
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			sld.ShipEnemyDisable  = true;
			pchar.quest.HWICCureer_AfterBattle.over = "yes";
			pchar.quest.HWICCureerOnMapOver.over = "yes";
			AddQuestRecord("Holl_Gambit", "3-39");
			Log_TestInfo("THE LETTER HAS BEEN DELIVERED!");
			RemoveItems(PChar, "MC_Letter", 1);
			pchar.questTemp.HWIC.Self = "LetterToLucasSent";
			pchar.quest.Curacao_exploring.win_condition.l1 = "location";
			pchar.quest.Curacao_exploring.win_condition.l1.location = "Curacao";
			pchar.quest.Curacao_exploring.function = "CuracaoExploring";
			DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
			AddComplexSeaExpToScill(50, 50, 50, 100, 50, 50, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
			AddMapQuestMarkIsland("Curacao", true);
		break;
		
		//Матиас Бек в тюрьме
		case "MatiasBek"://на случай если геймер захочет пообщаться
			dialog.text = "Ben yasa dışı olarak tutuklandım! İngilizlerle hiçbir bağlantım yok! Bunların hepsi Rodenburg'un entrikaları. Boşver. Peter Stuyvesant yakında gelecek - her şeyi çözecek!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "MatiasBek";
		break;
		
		//стражник у входа в резиденцию
		case "QuestGuard":
			dialog.text = "Mynheer Lucas Rodenburg şu anda kimseyle görüşmek istemiyor. Lütfen hemen konuttan ayrılın.";
			link.l1 = "Hm. Anladım. Bir hafta içinde uğramaya çalışırım...";
			link.l1.go = "exit";
			NextDiag.TempNode = "QuestGuard";		
		break;
		
		//Питер Стайвесант
		case "Stivesant":
			dialog.text = "Malikaneye gidiyoruz, Kaptan. Adamlarımı Matthias Beck hakkında bilgi almak için kaleye gönderdim bile. Eğer şu anda gerçekten hapisteyse, muhtemelen çoktan serbest bırakılmış ve kasabaya getirilmiştir. Beni takip edin!";
			link.l1 = "Evet, Bay Stuyvesant.";
			link.l1.go = "Stivesant_1";			
		break;
		
		case "Stivesant_1":
			DialogExit();
			AddLandQuestMark(npchar, "questmarkmain");
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "Villemstad_townhall", "goto", "goto2", "OpenVillemstadResidence", -1);
		break;
		
		case "ArestLucas_1":
			dialog.text = "Lucas! Burada neler oluyor? Matthias Beck nerede? Onu hapse yolladığın doğru mu?";
			link.l1 = "";
			link.l1.go = "ArestLucas_2";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_2":
			StartInstantDialog("Lucas", "ArestLucas_3", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_3":
			dialog.text = "Merhaba, Bay Stuyvesant. Onun İngiliz istihbaratıyla ve doğrudan Kaptan Fleetwood'la bağlantısına dair elimde kanıt var. Şirketimizin gizli yazışmalarını taşıyan kurye brigantinimize saldırıp mektupları ele geçirmesi için o lanet İngiliz'e haber uçurdu.";
			link.l1 = "";
			link.l1.go = "ArestLucas_4";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 4.5);
		break;
		
		case "ArestLucas_4":
			StartInstantDialog("Stivesant", "ArestLucas_5", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_5":
			dialog.text = "Bu bilgiyi nereden aldın?";
			link.l1 = "";
			link.l1.go = "ArestLucas_6";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_6":
			StartInstantDialog("Lucas", "ArestLucas_7", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_7":
			dialog.text = "It was claimed by the captain of the courier brigantine. Richard Fleetwood boarded his ship and took away his papers; then the ship was set free. Nobody except me, you and Matthias Beck had any information about either the route or the schedule.";
			link.l1 = "";
			link.l1.go = "ArestLucas_8";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));
		break;
		
		case "ArestLucas_8":
			StartInstantDialog("Stivesant", "ArestLucas_9", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_9":
			dialog.text = "And that's why you have decided that Beck tipped off Fleetwood to attack the brigantine? What rubbish! Fleetwood is an ordinary pirate; he only attacks merchant ships. Why would he need the papers, which, by the way, only contained bookkeeping information?";
			link.l1 = "";
			link.l1.go = "ArestLucas_10";		
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_10":
			StartInstantDialog("Lucas", "ArestLucas_11", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_11":
			dialog.text = "Mynheer, kuryer sadece sıradan raporları değil, Şirket’in diğer önemli belgelerini de taşıyordu. Şimdi ise hepsi İngilizlerin elinde. Bu yüzden Beck’i tutuklamaya karar verdim.";
			link.l1 = "";
			link.l1.go = "ArestLucas_12";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));			
		break;
		
		case "ArestLucas_12":
			StartInstantDialog("Stivesant", "ArestLucas_13", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_13":
			dialog.text = "Lanet olsun! Bu tam anlamıyla bir yetki gaspı! Lucas, gerçekten ne yaptığının farkında mısın? Kurye brigantin kaptanı nerede?";
			link.l1 = "";
			link.l1.go = "ArestLucas_14";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 4.5);
		break;
		
		case "ArestLucas_14":
			StartInstantDialog("Lucas", "ArestLucas_15", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_15":
			dialog.text = "Philipsburg'a gitti, efendim.";
			link.l1 = "";
			link.l1.go = "ArestLucas_16";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));	
		break;
		
		case "ArestLucas_16":
			StartInstantDialog("Stivesant", "ArestLucas_17", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_17":
			dialog.text = "Pekâlâ, o zaman. Beck'in serbest bırakılmasını emrettim. Buraya getirilecek ve sonra üçümüz konuşacağız.";
			link.l1 = "";
			link.l1.go = "ArestLucas_18";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_18":
			StartInstantDialog("Lucas", "ArestLucas_19", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_19":
			dialog.text = "Pekâlâ, benim için sorun yok. Üçümüz - tamam. Konuşalım.";
			link.l1 = "";
			link.l1.go = "ArestLucas_20";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));	
		break;
		
		case "ArestLucas_20":
			DialogExit();
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "governor1", "DoubleTalkWithLucas", -1.0);
			locCameraFromToPos(4.70, 2.92, -4.19, false, 3.60, -0.70, 5.00);
			DoQuestCheckDelay("PiterTalkWithLucas_2", 4.5);
		break;
		
		case "ArestLucas_40":
			dialog.text = "You will pay for your lawlessness, Rodenburg! Your accusations are absurd. You didn't even let me see the captain of the brigantine! You haven't presented any evidence; all the accusations come from you personally.\nI swear to the Lord, I am innocent! I do not and did not have any contact with the Brits!";
			link.l1 = "";
			link.l1.go = "ArestLucas_41";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_41":
			StartInstantDialog("Lucas", "ArestLucas_42", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_42":
			dialog.text = "Gerçekten mi? O zaman Fleetwood bizim brigantinimizi ve gemide sıradan belgelerden fazlası olduğunu nasıl öğrendi?";
			link.l1 = "";
			link.l1.go = "ArestLucas_43";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Villemstad_Mayor"));
		break;
		
		case "ArestLucas_43":
			dialog.text = "...";
			link.l1 = "Rodenburg yalan söylüyor. Richard Fleetwood'un kurye brigantinine saldırmış olması imkânsız.";
			link.l1.go = "ArestLucas_44";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			sld = characterFromId("Stivesant");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			sld = characterFromId("Villemstad_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "ArestLucas_44":
			dialog.text = "Ve siz kimsiniz, Bayım? Hangi hakla böyle laflar ediyorsunuz?";
			link.l1 = "Benim adım "+GetFullName(pchar)+". Kaptan Fleetwood'u şahsen tuzağa düşürüp ortadan kaldırdım. Cesedini şimdi Turks kıyılarında martılar yiyor. Yetkililer, biz Hollandalı tüccarları onun saldırganlığından koruyamadı, bu yüzden işini kendim bitirdim. Ve tüm bunlar, kurye brigantini yağmalanmadan önce oldu...";
			link.l1.go = "ArestLucas_46";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "ArestLucas_46":
			dialog.text = "";
			link.l1 = "Fleetwood bunu kesinlikle yapamazdı, çünkü o zaten ölmüştü. Meyhanedeki yerlilerden Mathias Beck'in tutuklandığını öğrendim, bu yüzden meseleyi araştırmaya karar verdim; çünkü her zaman Bay Beck'in lekesiz bir itibara sahip olduğuna inanmışımdır...";
			link.l1.go = "ArestLucas_47";			
		break;
		
		case "ArestLucas_47":
			dialog.text = "";
			link.l1 = "People in the port told me that you loaded your xebec with all kinds of criminals and mercenaries, while the Company's guardsmen were left ashore. I followed your ship and captured her, slaying every cutthroat you hired. I interrogated Captain Longway; in exchange for his freedom, he told me everything, Mynheer Rodenburg...";
			link.l1.go = "ArestLucas_48";			
		break;
		
		case "ArestLucas_48":
			dialog.text = "";
			link.l1 = "Curacao'nun kontrolünü ele geçirmeyi planladınız ve Longway'e mynheer Stuyvesant'ın kalyonunu batırmasını emrettiniz. Sizin yöntemlerinizi bildiğimden, zavallı brigantin kaptanının öldüğünden eminim. Muhtemelen bir emsal oluşturmak için kurye gemisine saldırı düzenlediniz, öyle değil mi? Ve bu işi sizin suikastçiniz Jacob van Berg gerçekleştirdi? Longway bana o adam hakkında çok şey anlattı.";
			link.l1.go = "ArestLucas_49";			
		break;
		
		case "ArestLucas_49":
			dialog.text = "Bu ... bu apaçık bir yalan! Neyden bahsediyorsunuz, Mynheer? Siz de kimsiniz?";
			link.l1 = "Ben, denizleri ve karayı o alçak Fleetwood’dan temizlemek isteyen bağımsız bir kaptanım ve sizin siyasi entrikalarınıza bulaştım! Stuyvesant’a da başına gelecek tehlikeden bahsettim. Ve şimdi, Curacao’daki yağmalarınıza yasal otoritelerle birlikte son vermeye geldim!";
			link.l1.go = "ArestLucas_50";			
		break;
		
		case "ArestLucas_50":
			dialog.text = "Ne küstahlık! Sözlerinin hesabını vereceksin, Bay 'bağımsız kaptan'! Sen...";
			link.l1 = "";
			link.l1.go = "ArestLucas_51";
		break;
		
		case "ArestLucas_51":
			StartInstantDialog("Stivesant", "ArestLucas_52", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_52":
			dialog.text = "Yeter artık, Lucas. Suçlarının bedelini ödeyeceksin! Duyduklarım ve gördüklerim bana fazlasıyla yetti. Lucas Rodenburg, Şirketin direktörüne suikast girişiminde bulunmak, zorla iktidarı ele geçirmeye çalışmak ve kurye gemisinin kaptanını öldürmekten şüphelenilmek suçlarıyla seni tutukluyorum.\nAyrıca, resmi soruşturma sırasında hayatının ilginç ayrıntılarını da öğrenme fırsatımız olacağına eminim. Gözaltında tutulacak ve Amsterdam’a gönderileceksin, orada yargılanacaksın. Götürün onu!";
			link.l1 = "";
			link.l1.go = "ArestLucas_53";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
			sld = characterFromId("Lucas");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromID("Stivesant"));					
		break;
		
		case "ArestLucas_53":
			StartInstantDialog("Lucas", "ArestLucas_54", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_54":
			dialog.text = "Ama...";
			link.l1 = "";
			link.l1.go = "ArestLucas_55";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));			
		break;
		
		case "ArestLucas_55":
			DialogExit();
			LAi_ActorTurnToCharacter(pchar, characterFromID("Lucas"));
			sld = characterFromId("Lucas");
			LAi_SetImmortal(sld, true);//защита от хитреца
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "goto", "goto6");
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "LucasGoToPrison", -1);
			for (i=3; i<=5; i++)
			{
			sld = characterFromId("StivesantGuard_"+i);
			LAi_ActorFollow(sld, characterFromID("Lucas"), "", -1);
			}
			LAi_SetActorType(PChar);
			locCameraFromToPos(4.70, 2.92, -4.19, false, -4.60, -1.70, 5.50);
			DoQuestFunctionDelay("SecondDayInVillemstad", 6.0);
		break;
		
		case "Stivesant_10":
			dialog.text = "Kaptan "+GetFullName(pchar)+"! Willemstad koloni yönetimi adına, o tehlikeli suçlunun yakalanmasına yardımcı olan eylemleriniz için en içten teşekkürlerimizi kabul etmenizi rica ederim. Ayrıca size şahsen de teşekkür etmek isterim, çünkü muhtemelen hayatımı size borçluyum.";
			link.l1 = "Tüm Hollanda kolonilerinin iyiliği için hareket ettim, Mijnheer.";
			link.l1.go = "Stivesant_11";			
		break;
		
		case "Stivesant_11":
			dialog.text = "Mütevazılığınız gerçekten saygı uyandırıyor, dostum. Şimdi bazı resmî meseleleri halletmek isterim: Meifeng’i yalnızca iyi niyetlerle ve çaresiz bir durumda ele geçirdiğiniz için size karşı herhangi bir iddiamız olamaz. Fakat bu gemi Şirkete ait ve onu bize geri vermenizi rica ediyorum.";
			link.l1 = "Elbette, Mynheer.";
			link.l1.go = "Stivesant_12";			
		break;
		
		case "Stivesant_12":
		//удаляем Мейфенг
		DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//удаляем атрибут квестового корабля
		if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)
		{
			pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
			pchar.Ship.name = "A boat";
			SetBaseShipData(pchar);
			SetCrewQuantityOverMax(PChar, 0);//сажаем на тартану
		}
		else
		{
			for(i = 1; i < COMPANION_MAX; i++)
			{
			int iTemp = GetCompanionIndex(PChar, i);
			if(iTemp > 0)
				{
				sld = GetCharacter(iTemp);
				if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
					{
						pchar.questTemp.HWIC.Self.CompanionIndex = sld.Index;
						sld = GetCharacter(sti(pchar.questTemp.HWIC.Self.CompanionIndex));
						RemoveCharacterCompanion(PChar, sld);
						AddPassenger(PChar, sld, false);
					}
				}
			}
		}
			dialog.text = "Lütfen yarın konutuma gelin – Özgür Eyaletler Cumhuriyeti adına, çıkarları doğrultusunda gösterdiğiniz başarılar için onurlandırılacaksınız. Sizden ricam, şehirden ayrılmamanızdır.";
			link.l1 = "Pekala, Efendim. Yarın uğrarım.";
			link.l1.go = "Stivesant_13";			
		break;
		
		case "Stivesant_13":
			DialogExit();
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			sld.dialog.currentnode = "Bek_2";
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "Bek_2":
			dialog.text = "Sana ayrıca şahsen teşekkür etmek isterim, Kaptan, girişimci ruhun ve zamanında yardımın için. Yarın mutlaka buraya uğra, senin için değerli bir hediye hazırlayacağım.";
			link.l1 = "Teşekkür ederim, Bay Beck. Orada olacağım!";
			link.l1.go = "Bek_3";			
		break;
		
		case "Bek_3":
			DialogExit();
			pchar.quest.Award_FromPiter.win_condition.l1 = "Timer";
			pchar.quest.Award_FromPiter.win_condition.l1.date.hour  = 9.0;
			pchar.quest.Award_FromPiter.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Award_FromPiter.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Award_FromPiter.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Award_FromPiter.function = "OpenResidenceDoor";
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Villemstad_town", "reload5_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload10_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload3_back", true);//закрыть вход в резиденцию
			LocatorReloadEnterDisable("Villemstad_town", "reloadR2", true);//закрыть боковой вход в резиденцию
			AddQuestRecord("Holl_Gambit", "3-53");
			DoQuestReloadToLocation("Villemstad_prison", "goto", "goto23", "TalkWithLucasPrisoner");
			for (i=4; i<=5; i++)
			{
				sld = characterFromId("StivesantGuard_"+i);
				sld.lifeday = 0;//подчистим солдат
			}
		break;
		
		case "Stivesant_14":
			dialog.text = ""+GetFullName(pchar)+", Özgür Eyaletler Cumhuriyeti adına, tüm Hollandalıların düşmanı olan devlet suçlusu Richard Fleetwood’un ortadan kaldırılmasındaki girişiminiz için size şahsi bir silah ve 100.000 peso ödül verildi. Tebrikler!";
			link.l1 = "Teşekkür ederim, Bay Stuyvesant!";
			link.l1.go = "Stivesant_15";			
		break;
		
		case "Stivesant_15":
			dialog.text = "Ayrıca, gösterdiğiniz eşi benzeri görülmemiş cesaretiniz, Şirket içindeki hain komployu ortaya çıkarmanız ve Şirket'in eski başkan yardımcısını cesurca ele geçirmeniz nedeniyle size 150.000 peso ödül veriliyor. Ayrıca Hollanda Batı Hindistan Şirketi ile sözleşme yapmanıza da izin verilecek.\nEminim ki yeni başkan yardımcımız sizin gibi cesur bir kaptana iyi maaşlı bir görev bulacaktır.";
			link.l1 = "Teşekkür ederim! Bunu aklımda tutacağım.";
			link.l1.go = "Stivesant_16";			
		break;
		
		case "Stivesant_16":
			AddMoneyToCharacter(pchar, 250000);
			GiveItem2Character(pchar, GetGeneratedItem("blade_16")); // belamour legendary edition используем GetGeneratedItem иначе пачка одинаковых клинков из первой части массива
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			dialog.text = "Unutma, Hollanda'nın tarafında ve çıkarları doğrultusunda hareket ettiğin sürece her işinde desteğime güvenebilirsin. Şimdi gel, Willemstad valisi Matthias Beck'in ne söyleyeceğini dinleyelim.";
			link.l1 = "";
			link.l1.go = "Stivesant_17";			
		break;
		
		case "Stivesant_17":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_SetActorType(sld);
			sld.dialog.currentnode = "Bek_4";
			LAi_ActorDialog(sld, pchar, "", -1, 0);		
		break;
		
		case "Bek_4":
			dialog.text = "Cesurca davranışınız ve devlete karşı kurulan komployu ortaya çıkarmanızdaki öngörünüz için size en içten teşekkürlerimi sunuyorum, Kaptan. Her savaş gemisi subayı için vazgeçilmez olan bu değerli seyir aletini size takdim etmek isterim.";
			link.l1 = "Teşekkür ederim, Bay Beck";
			link.l1.go = "Bek_5";			
		break;
		
		case "Bek_5":
			GiveItem2Character(pchar, "bussol");
			dialog.text = "Bilmeni isterim ki: Artık benim dostumsun ve bu benim için çok şey ifade ediyor. Evimde her zaman hoş bir misafir olacaksın. Ne zaman ve hangi sebeple istersen uğrayabilirsin – sana ihtiyacın olan her türlü yardımı memnuniyetle sunarım.";
			link.l1 = "Bunu duyduğuma sevindim, Mösyö!";
			link.l1.go = "Bek_6";			
		break;
		
		case "Bek_6"://наведем порядок в городе
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-54");
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_SetHuberStayType(sld);
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("StivesantGuard_"+i);
				sld.lifeday = 0;//подчистим солдат
			}
			sld = characterFromId("Stivesant");
			LAi_ActorGoToLocator(sld, "goto", "goto6", "StivesantSitDown", -1);
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			DelMapQuestMarkCity("Villemstad");
		break;
		
		case "Bek_7":
			dialog.text = "Hollanda seninle gurur duyuyor, Efendim. Senin gibi kaptanlar, Karayipler'deki Hollanda Donanması'nın bel kemiğidir. Buyurun, lütfen ödülünüzü kabul edin.";
			link.l1 = "Teşekkür ederim, Efendim. Hollanda'ya hizmet etmek benim için bir onur!";
			link.l1.go = "Bek_8";
		break;
		
		case "Bek_8":
			TakeNItems(pchar, "gold_dublon", 1000);
			ChangeCharacterComplexReputation(pchar,"authority", 5);
			ChangeCharacterNationReputation(pchar, HOLLAND, 20);
			DialogExit();
			sld = characterFromId("Lucas");
			LAi_SetActorType(sld);
			sld.dialog.currentnode = "LucasAward_2";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Stivesant_18":
			dialog.text = "Seni gördüğüme sevindim. Nasılsın?";
			link.l1 = "İyiyim. Sadece seni görmek için uğradım.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "Stivesant_18";
		break;
		
		// Jason НСО
		case "Stivesant_19":
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10)
			{
				dialog.text = "Bak hele kim gelmiş! Bu "+GetFullName(pchar)+". Sizi buraya getirmeleri için kısa süre önce adamlarımızı gönderdik. Ve bu hizmet bize epey pahalıya mal oldu.";
				link.l1 = "Uhm... Gitmeliyim...";
				link.l1.go = "arest";
				break;
			}
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (pchar.questTemp.Patria == "epizode_4" && IsUniformEquip())
			{
				dialog.text = "Fransız Donanması'nda bir kaptan mısınız? Güzel, vaktim dar ama sizi dinleyeceğim. Sizi buraya getiren nedir?";
				link.l1 = "Sayın Stuyvesant, Fransız kolonilerinin Genel Valisi Chevalier de Poincy'den bir mesajla Saint Christopher'dan geldim.";
				link.l1.go = "Stivesant_20";
			}
			else
			{
				dialog.text = "Affedersiniz Kaptan, ama şu anda çok meşgulüm ve size yeterince vakit ayıramam. Mynheer Mathias Beck ile konuşun, söyleyeceklerinizi ona anlatın.";
				link.l1 = "Hmm...";
				link.l1.go = "Stivesant_19_1";
			}
		break;
		
		case "Stivesant_19_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_19";
		break;
		
		case "Stivesant_20":
			sld = characterFromId("Patria_FlautCap");
			dialog.text = "Chevalier de Poincy'den mi? Açıkçası bu kadar az süreceğini hiç beklememiştim... öhöm... Chevalier nasıl, iyi mi?";
			link.l1 = "Her şey yolunda, Efendim. Monsieur de Poincy bu mektubu size teslim etmemi emretti. Diğer görevim ise size eşlik etmekti "+sld.ship.name+"Şirketiniz için yükle birlikte Willemstad limanına geldim. Gemi iskelede ve yük sapasağlam.";
			link.l1.go = "Stivesant_21";
		break;
		
		case "Stivesant_21":
			dialog.text = "Şirketimiz için yük taşıyan bir filo mu? İlginç... Peki ya mektup, Kaptan?";
			link.l1 = "Al, lütfen bunu kabul et.";
			link.l1.go = "Stivesant_22";
		break;
		
		case "Stivesant_22":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Hmmm... (okuyor). Ana devletten bir teftiş... Hımm... Ha, şey... bu ilginçmiş, heh-heh... Bu arada Kaptan, duydum ki Fransa Karayipler'de İspanya'yla savaş halinde? San Jose kalesinin kuşatılması ve yağmalanması, Küba'nın doğu kıyısında İspanyol savaş filosunun yok edilmesi...";
			link.l1 = "Hispaniola'nın batı kıyısında, Port-au-Prince yakınlarında, Efendim. San Jose kuşatmasının tek amacı, İspanyolların Saint-Pierre'e saldırısına karşılık onlardan maddi tazminat almaktı. İspanya ile bir süredir aramız hiç iyi değil... Cevabı almak için ne zaman geri dönmemi istersiniz?";
			link.l1.go = "Stivesant_23";
		break;
		
		case "Stivesant_23":
			dialog.text = "Sizi alıkoymayacağım, Kaptan, siz askeri birisiniz, muhtemelen birçok işiniz vardır ve eminim Şövalye de dönüşünüzü sabırsızlıkla bekliyordur. Lütfen burada, salonda, iki saat kadar bekleyin, ben de o mektuba bir cevap yazayım. Oturun ve dinlenin, isterseniz size şarap ya da rom ikram edilecek...";
			link.l1 = "Teşekkür ederim, efendim, ama ben bir kadeh kaliteli şarap tercih ederim...";
			link.l1.go = "Stivesant_24";
		break;
		
		case "Stivesant_24":
			chrDisableReloadToLocation = true;//закрыть локацию
			pchar.quest.Patria_CureerTimeOver.over = "yes"; //снять таймер
			pchar.quest.Patria_CureerFail.over = "yes"; //снять прерывание
			sld = characterFromId("Patria_FlautCap");
			RemoveCharacterCompanion(pchar, sld);
			sld.lifeday = 0;
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_25";
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "Villemstad_townhall", "goto", "goto6");
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "Patria_StivesantWait", -1);
			pchar.questTemp.Patria = "epizode_4_return";
		break;
		
		case "Stivesant_25":
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_2");
			dialog.text = "Monsieur de Poincy için cevabınız hazır. Buyurun, lütfen alın... İyi şanslar, Kaptan.";
			link.l1 = "Teşekkür ederim, Mösyö. Hoşça kalın!";
			link.l1.go = "Stivesant_26";
		break;
		
		case "Stivesant_26":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_19";
			chrDisableReloadToLocation = false;
			AddQuestRecord("Patria", "23");
			SetFunctionTimerCondition("Patria_CureerBackOver", 0, 0, 31, false);
		break;
		
		case "Stivesant_27":
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10)
			{
				dialog.text = "Bak hele kim gelmiş! Bu "+GetFullName(pchar)+". Sizi buraya getirmeleri için yakın zamanda adamlarımızı gönderdik. Ve bu hizmet bize epey pahalıya mal oldu.";
				link.l1 = "Uhm... Gitmeliyim...";
				link.l1.go = "arest";
				break;
			}
			if (pchar.questTemp.Patria == "epizode_6" && IsUniformEquip())
			{
				dialog.text = "Yine Valiler Genel Philippe de Poincy'den bir mesajla geldin, değil mi?";
				link.l1 = "Evet, Bay Stuyvesant. Sint Maarten kıyılarında talihsiz bir yanlış anlaşılma oldu - Paris'ten gelen müfettişi, Baron Noël Forget'i taşıyan gemiye Philipsburg’daki kale ateş açtı ve...";
				link.l1.go = "Stivesant_28";
			}
			else
			{
				dialog.text = "Affedersiniz Kaptan, ama şu anda çok meşgulüm ve size yeterince vakit ayıramam. Mynheer Mathias Beck ile konuşun, söyleyeceklerinizi ona anlatın.";
				link.l1 = "Hmm...";
				link.l1.go = "Stivesant_27_1";
			}
		break;
		
		case "Stivesant_27_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_27";
		break;
		
		case "Stivesant_28":
			if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "self_win")
			{
				dialog.text = "Ve işte bu yüzden buradasınız, Kaptan. Diplomatik tartışmalara girmeyeceğim: Şövalye'ye söyleyin, Sint Maarten artık onun yönetiminde değil. Yeter artık ondan. Ana devletten gelecek denetimle ilgili ise – bir şeyler uydursun. De Poincy için her şeyi altüst etmek hiç zor olmadı.";
				link.l1 = "Ona tam olarak bunu mu söylemeliyim?";
				link.l1.go = "Stivesant_29";
			}
			else
			{
				dialog.text = "Ve işte bu yüzden buradasınız, Kaptan. Diplomatik tartışmalara girmeyeceğim: efendiniz son zamanlarda Sint Maarten'de fazlasıyla açgözlü davrandı, artık onun doymak bilmez iştahını dizginlemenin vakti geldi. Ve eminim ki bunu gayet iyi anlıyordur. Size gelince, Kaptan Charles de Maure, son zamanlarda Richard Fleetwood adındaki İngiliz haydutla ilgili bazı olaylar hakkında da sorularımız var, bu yüzden bir süre burada kalmanız gerekecek. Çavuş! Kaptanın silahlarını alın ve onu komutanın ofisine götürün!";
				link.l1 = "Fransız bir subayı görev başında oyalamak kabul edilemez!";
				link.l1.go = "Stivesant_31";
			}
		break;
		
		case "Stivesant_29":
			dialog.text = "Ben de daha iyi ifade edemezdim, Kaptan. Komutanınız her şeyi anlayacaktır, ama ayrıntılara girmenize gerek yok, bu hiçbir şeyi değiştirmez. Size en iyisini dilerim. Çavuş, Mösyö Charles de Maure'u çıkışa götür!";
			link.l1 = "...";
			link.l1.go = "Stivesant_30";
		break;
		
		case "Stivesant_30":
			DialogExit();
			DoQuestReloadToLocation("Villemstad_town", "reload", "reload3", "Patria_DiplomatGetOut");
		break;
		
		case "Stivesant_31":
			dialog.text = "Maalesef, ben farklı düşünüyorum. Çavuş! Direnirlerse, güç kullanın!";
			link.l1 = "Sen daha kiminle uğraştığını bilmiyorsun, Mynheer ...";
			link.l1.go = "Stivesant_32";
		break;
		
		case "Stivesant_32":
			DialogExit();
			Patria_DiplomatFight();
		break;
		
		case "Stivesant_33":
			dialog.text = "Sizi bu rolde görmek biraz garip, Kaptan Charles de Maure ... Size müzakere için gelenlere dokunulmazlık garantisi verebileceğinizi umuyorum..";
			link.l1 = "Bundan emin olabilirsiniz, Bay Stuyvesant.";
			link.l1.go = "Stivesant_34";
		break;
		
		case "Stivesant_34":
			dialog.text = "Yani, hazırladığınız anlaşmayı okumam için bana bir şans verebilir misiniz? Anladığım kadarıyla, mektuptaki içerik de içinde mi?";
			link.l1 = "Kesinlikle, Efendim, sadece resmî bir biçimde. Fransa tarafından – ilişkilerin tekrar tarafsıza döndürülmesi, Sint Maarten adası üzerindeki tüm hak iddialarından vazgeçilmesi. İngiltere tarafından – ticaret savaşının sona erdirilmesi. Tüm ayrıntılar burada yazılı ... Ve elbette, başlattığınız askerî harekâtlar yüzünden uğradığımız zararın maddi tazmini.";
			link.l1.go = "Stivesant_35";
		break;
		
		case "Stivesant_35":
			dialog.text = "Lütfen bana belgeyi verir misiniz?";
			link.l1 = "Elbette.";
			link.l1.go = "Stivesant_36";
		break;
		
		case "Stivesant_36":
			dialog.text = "...(okuyor)...";
			link.l1 = "...";
			link.l1.go = "Stivesant_37";
		break;
		
		case "Stivesant_37":
			LAi_Fade("", "");
			dialog.text = "Bana başka seçenek bırakmadığınız için bu anlaşmayı imzalayacağım. Ama benim için Willemstad'ın ve halkının korunması her şeyden önemli";
			link.l1 = "O zaman üç nüshayı da imzalarla onaylayacağız. Fransa adına belgeyi onaylamam için Genel Vali Philippe de Poincy tarafından yetkilendirildim, Albay Doily de İngiltere adına imzalayacak.";
			link.l1.go = "Stivesant_38";
		break;
		
		case "Stivesant_38":
			dialog.text = "...(imzalıyor)...";
			link.l1 = "Mükemmel! Şimdi bunu imzalamalıyız...";
			link.l1.go = "Stivesant_39";
		break;
		
		case "Stivesant_39":
			LAi_Fade("", "");
			dialog.text = "Yani, şimdi kuşatmayı kaldıracağına güvenebilir miyim?";
			link.l1 = "Hiç şüphem yok. Umarım anlaşmanın tüm şartlarına Hollandalılar tarafından eksiksiz uyulur, hiçbir ihlal olmaz.";
			link.l1.go = "Stivesant_40";
		break;
		
		case "Stivesant_40":
			dialog.text = "Eğer İngiltere ya da Fransa tarafından bir ihlal olmazsa, biz de sözleşmenin şartlarına uyacağız, o yüzden endişelenmeyin.";
			link.l1 = "Her zaman ticaret yapmak savaşmaktan iyidir, Bay Stuyvesant. Artık güvenle Willemstad'a dönebilirsiniz. Kuşatma kaldırılacak ve filomuz yakında Curaçao sularından ayrılacak.";
			link.l1.go = "Stivesant_41";
		break;
		
		case "Stivesant_41":
			DialogExit(); // Стайвесант уходит, подходит д'Ойли
			Patria_CuracaoStivesantGo();
		break;
		
		case "Stivesant_42":
			dialog.text = "Demek Baron Noel Forget sizsiniz? Hımm, o zaman siz de bizzat Mösyö Charles de Maure olmalısınız! Selamlar, Koramiral! Takımadaların en kurnaz entrikacısı olarak anılmanız boşuna değilmiş – insan sizin hangi tarafta olduğunuzu asla kestiremiyor...";
			link.l1 = "Amiral Yardımcısı Kral'ın tarafında ve şu anda, onun yetkili temsilcisi olarak, sizin de tarafınızda.";
			link.l1.go = "Stivesant_43";
		break;
		
		case "Stivesant_43":
			dialog.text = "Kral buradan çok uzakta, Fransa da öyle, Baron, ama Saint Christopher ve Şövalye de Poincy burada, yanı başımızda. Fransız kolonilerinin gerçek sahibi odur. Fiilen... Ancak, buraya de Poincy'yi maliye bakanının gözünde zor duruma düşürecek bir şey bulmak için mi geldiniz?";
			link.l1 = "Kesinlikle, Mynheer.";
			link.l1.go = "Stivesant_44";
		break;
		
		case "Stivesant_44":
			dialog.text = "Bu belgeler bende var. Burada, madenle ve bazı başka işlerle ilgili kendi hesaplarımın ve de Poincy'nin hesaplarının tamamını içeren bir muhasebe defteri var. İçinde ayrıca bu işle ilgili, her biri Philippe de Poincy'nin şahsi imzasını taşıyan bir yığın evrak bulacaksınız. Emin olun, bu belgelerin içeriği, ilgilenen birinin eline geçerse, Şövalye'yi Karayip Denizi'nin dibinden de derine batırır.";
			link.l1 = "Bu defter için ne istiyorsun?";
			link.l1.go = "Stivesant_45";
		break;
		
		case "Stivesant_45":
			dialog.text = "Bunu neredeyse bedavaya satıyorum. Sadece bir milyon peso gümüş.";
			link.l1 = "Bir milyon peso mu?!!";
			link.l1.go = "Stivesant_46";
		break;
		
		case "Stivesant_46":
			dialog.text = "Doğru, Baron. Bu miktar en azından son savaşın yol açtığı kayıpların bir kısmını karşılayacak. Size bir tavsiye vereyim: Monsieur Charles de Maure'a başvurun. De Poincy ve hmm... başka kişiler için çalışırken muhtemelen büyük bir servet kazandı, bir milyon bulmak onun için sorun olmayacaktır. Bundan neredeyse eminim.\nSize bir süre tanıyorum - bir ay. Bu sürenin sonunda, belirtilen miktarı getirmezseniz, Şövalye'ye bir mektup göndereceğim ve bana yaptığınız ziyareti tüm ayrıntılarıyla anlatacağım. Sonrasını tahmin edebilirsiniz.";
			link.l1 = "Beni şantaj mı yapıyorsun! Anlamalısın ki, kolonilerde asla bir milyonum olamaz!";
			link.l1.go = "Stivesant_47";
		break;
		
		case "Stivesant_47":
			dialog.text = "Elbette anlıyorum. Bu yüzden, bu milyonun kimde olduğunu size hemen gösterdim. Eğer Mösyö de Maure reddederse, Baron, size en iyisi Avrupa'ya doğru yelken açmanız olur, yoksa Şövalye mektubumu alınca burada sonsuza dek kalma riskiniz var. Mösyö de Maure'a gelince... elbette amiral rütbesini kaybedecek, ama kurtulacak... ve belki de kendi yöntemleriyle de Poincy'den de kurtulacak, ki bu benim için gayet uygun.\nPekâlâ baylar, beni duydunuz. Bir ay sonra konutumda sizi ve milyonunuzu bekliyor olacağım. Giriş çıkış serbest, garanti ediyorum.";
			link.l1 = "...";
			link.l1.go = "Stivesant_48";
		break;
		
		case "Stivesant_48":
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			locCameraTarget(pchar);
			locCameraFollow();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = true;
			bDisableCharacterMenu = false;
			sld = CharacterFromID("Noel");
			sld.dialog.currentnode = "noel_84";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			sld = CharacterFromID("Stivesant");
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "Patria_CondotierStivesantInHall", 12.0);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("Stivesant_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			}
		break;
		
		case "Stivesant_49":
			if (sti(pchar.money) >= 1000000)
			{
				dialog.text = "I never doubted, Vice Admiral Charles de Maure, that you would bring me this money. Perhaps I even asked too little of you, but oh well... The Baron is just a pawn in your next game, isn't he? Rank and money are not enough for you; now you want to take de Poincy's place, am I right? You must admit, a million is a small sum for the post of Governor General of the French colonies! You'll get this money back in a matter of months, given your iron grip.";
				link.l1 = "Al milyonunu al, Mynheer. Söz verdiğin defteri almak istiyorum.";
				link.l1.go = "Stivesant_50";
			}
			else
			{
				dialog.text = "Milyonu toplamaya odaklansanız daha iyi olur, Mösyö, vaktinizi gereksiz ziyaretlerle harcamak yerine.";
				link.l1 = "...";
				link.l1.go = "Stivesant_49_1";
			}
		break;
		
		case "Stivesant_49_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_49";
		break;
		
		case "Stivesant_50":
			pchar.quest.Patria_CondotierStivesantTimeOver.over = "yes"; // снять таймер
			AddMoneyToCharacter(pchar, -1000000);
			GiveItem2Character(pchar, "Reserve_item_01");
			ref itm = ItemsFromID("Reserve_item_01");
			itm.picIndex = 15;
			itm.picTexture = "ITEMS_26";
			itm.price = 0;
			itm.Weight = 2.0;
			itm.name = "itmname_Reserve_item_01_1";
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_4");
			dialog.text = "Elbette, Koramiral. Ve surat asmayın: Genel Vali olduğunuzda göreceksiniz ki Hollanda Batı Hint Ticaret Şirketi, açgözlü ve savaşçı İngilizlerden çok daha kârlı bir iş ortağıdır. Bir İngiliz’e parmağınızı verirseniz, bütün elinizi alacağını bilmiyor musunuz? Bilmiyorsanız, bunu acı bir şekilde öğreneceksiniz. Yani size henüz veda etmiyorum. Belgelerinizi saklayın. Baro’nuzun Şövalyeyi alt edecek kadar yetenekli olmasını umuyorum.";
			link.l1 = "Teşekkür ederim. Hoşça kalın, Bay Stuyvesant.";
			link.l1.go = "Stivesant_51";
		break;
		
		case "Stivesant_51":
			DialogExit();
			AddQuestRecord("Patria", "84");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
			pchar.quest.Patria_CondotierCabin.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierCabin.win_condition.l1.location = "Curacao";
			pchar.quest.Patria_CondotierCabin.function = "Patria_CondotierCabin";
		break;
		
		case "vanberg_sold":
			dialog.text = "Ha-ha-ha! Şuna bak! Jacob her zamanki gibi haklıydı – bu tilki adaya boşuna gelmemiş. Sandıkta epeyce altın var gibi görünüyor. Buraya tek başına gelmen büyük bir dikkatsizlik olmuş, dostum. Ama bu da bizim işimizi bir hayli kolaylaştırıyor!";
			link.l1 = "O pislikler beni bulmuş! Hiç beklemiyordum... Ama kolay lokma olmayacağım!";
			link.l1.go = "vanberg_sold_1";			
		break;
		
		case "vanberg_sold_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("vanberg_sold_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PrepareMassakraInShore");
			AddDialogExitQuest("MainHeroFightModeOn");			
		break;
		
		case "Abihouselady":
			dialog.text = "Birini mi arıyorsunuz?";
			link.l1 = "Evet, benim. Solomon ve Abigail Shneur nerede?";
			link.l1.go = "Abihouselady_1";			
		break;
		
		case "Abihouselady_1":
			dialog.text = "They don't live here anymore. They simply couldn't afford the place. Abigail, poor girl, is working as one of the governor's servants. She works hard every day to provide for herself and her father. Solomon drinks in the tavern every day; he can't bear what happened to them. They are now living in a small hut not far from the sea...";
			link.l1 = "Ah... Peki, verdiğiniz bilgi için teşekkürler. Gitmem gerek.";
			link.l1.go = "Abihouselady_2";
		break;
		
		case "Abihouselady_2":
			DialogExit();
			NextDiag.CurrentNode = "Abihouselady_3";
		break;
		
		case "Abihouselady_3":
			dialog.text = "Başka ne bilmek istersiniz, Bayım?";
			link.l1 = "Hiçbir şey, boş ver.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abihouselady_3";
		break;
		
		//удаление Мейфенг при провале квеста
		case "TempOffGuard":
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//удаляем атрибут квестового корабля
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
				pchar.Ship.name = "A boat";
				SetBaseShipData(pchar);
				SetCrewQuantityOverMax(PChar, 0);//сажаем на тартану
			}
			else
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
						iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							pchar.questTemp.HWIC.Self.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Self.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			dialog.text = "Kaptan, Hollanda Batı Hint Şirketi'ne ait bir gemiyi izinsiz ele geçirdiniz. Onu el koymaya ve direnmeniz halinde güç kullanmaya yetkiliyim. Bu, Peter Stuyvesant'ın emridir.";
			link.l1 = "Pekâlâ, madem bu emir bizzat Peter Stuyvesant'tan geliyor... Bir gemi için Hollanda'yla savaşa girecek değilim. Alın, sizin olsun.";
			link.l1.go = "TempOffGuard_1";			
		break;
		
		case "TempOffGuard_1":
			dialog.text = "Mantıklı davranman iyi oldu.";
			link.l1 = "...";
			link.l1.go = "TempOffGuard_2";
		break;
		
		case "TempOffGuard_2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");
		break;
		
		// Jason НСО
		case "arest":
			dialog.text = "Elbette gitme zamanı geldi, üstelik seni eşlik edecekler de var. Muhafızlar! Yakalayın onu!";
		    link.l1 = "Yaptırsana!";
		    link.l1.go = "fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Hey, dinle! Bu kasabanın bir vatandaşı olarak, senden kılıcını kınından çıkarmadan dolaşmamanı rica ediyorum.","Biliyor musunuz, bu kasabanın bir sakini olarak sizden rica ediyorum, lütfen kılıcınız çekili halde dolaşmayın.");
			link.l1 = LinkRandPhrase("Pekâlâ.","Pekâlâ.","Dediğiniz gibi...");
			link.l1.go = "exit";
		break;
	}
}
