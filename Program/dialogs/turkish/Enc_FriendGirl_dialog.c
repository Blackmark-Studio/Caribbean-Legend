void ProcessDialogEvent()
{	
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iRank, iMassive;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{		
		case "exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
			dialog.text = LinkRandPhrase("Aman Tanrım, sizinle tanıştığıma çok sevindim!","Sonunda, biri geldi!","Aman Tanrım, seni gördüğüme çok sevindim!");
			Link.l1 = LinkRandPhrase("Ne oluyor, sevgilim?","Bir sorun mu var, canım?","Bukadar telaşlanma - genç bir hanımın sağlığı için iyi değildir. Şimdi, bana sadece söyle - ne oldu?");
			Link.l1.go = "Step_1";
		break;
		case "Step_1":
			dialog.text = LinkRandPhrase("Arkadaşım... o kadar cesur ki... terk edilmiş bir kuyuya indi!","Arkadaşım terk edilmiş bir kuyuya indi ve hâlâ dışarı çıkmadı! Saatlerdir orada!","Arkadaşım terk edilmiş bir kuyuda aniden kayboldu!");
			Link.l1 = "Ve o lanet olası yere neden girdi ki?!";
			Link.l1.go = "Step_2";
		break;
		case "Step_2":
			dialog.text = "Ah, bilirsin, o her şeyden korkar! Altın dolu bir zindan olduğunu duymuş, hemen oraya gitmiş... Ama ben aptal değilim, aklımdan bile geçirmem!";
			Link.l1 = "Evet, senin gibi biri için burada yapılacak hiçbir şey yok.";
			Link.l1.go = "Step_3";
		break;		
		case "Step_3":
			dialog.text = "Şimdi ne yapmam gerekiyor? Ne olur, Allah aşkına, ona yardım edin!";
			Link.l1 = "Pekala, ben hallederim. Sen de en iyisi evine git, burada yapacak bir şeyin yok.";
			Link.l1.go = "Step_agree";
			Link.l2 = "Bunlar senin sorunların, zamanımı harcamak istemiyorum. Hoşça kal...";
			Link.l2.go = "Step_disAgree";
		break;

		case "Step_agree":
			pchar.quest.Enc_FriendGirl_after.over = "yes";
			if (rand(1))
			{ //бандюганы
				LAi_LocationDisableMonGenTimer(pchar.GenQuest.EncGirlF.locationId, 1); //монстров не генерить 1 день
				LAi_LocationDisableOffGenTimer(pchar.GenQuest.EncGirlF.locationId, 1); //офицеров не пускать 1 день
				LocatorReloadEnterDisable(pchar.GenQuest.EncGirlF.locationId, "reload2", true);
				pchar.GenQuest.OpenTheRopeExit = pchar.GenQuest.EncGirlF.locationId; //флаг для открытия релоада
				string model[10];
				model[0] = "citiz_41";
				model[1] = "citiz_42";
				model[2] = "citiz_43";
				model[3] = "citiz_44";
				model[4] = "citiz_45";
				model[5] = "citiz_46";
				model[6] = "citiz_47";
				model[7] = "citiz_48";
				model[8] = "citiz_49";
				model[9] = "citiz_50";
				i = 0;
				while(i < 3)
				{
					iMassive = rand(9);
					if (model[iMassive] != "")
					{
						iRank = sti(pchar.rank) - rand(5) + rand(5);
						if (iRank < 1) iRank = 1; 
						sld = GetCharacter(NPC_GenerateCharacter("CaveGandMan" + i, model[iMassive], "man", "man", iRank, PIRATE, 1, true, "marginal"));
						SetFantomParamFromRank(sld, iRank, true);
						sld.SaveItemsForDead = true;
						sld.DontClearDead = true; 
						sld.money = iRank*200+1000+rand(500);
						LAi_SetWarriorType(sld);
						LAi_warrior_SetStay(sld, true);
						//LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
						LAi_group_MoveCharacter(sld, LAI_GROUP_ENEMY);// лесник изменил группу чтобы ядом таино травить можно было
						LAi_group_Attack(sld, Pchar);// лесник добавил атаку на пчара а то у некоторых баг что они не нападают.
						ChangeCharacterAddressGroup(sld, pchar.GenQuest.EncGirlF.locationId, "quest", "quest" + i);
						i++;
						model[iMassive] = "";	
					}
				}
			}
			else
			{ //и правда девка 
				sld = GetCharacter(NPC_GenerateCharacter("UndergroundGirl", "women_"+(rand(5)+11), "woman", "towngirl", 5, PIRATE, 1, false, "citizen"));
				sld.dialog.filename = "Enc_FriendGirl_dialog.c";
				int iTemp = rand(1);
				sld.dialog.currentnode = "Underground"+ iTemp; //здесь рендом поведения девки: 0-помогите, 1-сама крутая// лесник - раскоментил itemp
				sld.greeting = "Enc_RapersGirl_" + (iTemp+1); //соотв. озвучка
			   // LAi_SetStayType(sld);
				LAi_SetCitizenType(sld);// чтоб ходила по пещере. лесник
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				GetCharacterPos(pchar, &locx, &locy, &locz); // и ниже - ищем ближейший локатор лесник.
	            ChangeCharacterAddressGroup(sld, pchar.GenQuest.EncGirlF.locationId, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			}
			LAi_SetActorTypeNoGroup(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Step_disAgree":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			LAi_SetCitizenTypeNoGroup(npchar);
			pchar.quest.Enc_FriendGirl_after.over = "yes";
			NextDiag.CurrentNode = "FackYou";
			DialogExit();
		break;			
		case "FackYou":
            NextDiag.TempNode = "FackYou";
            dialog.text = "Böylesine duyarsız biriyle konuşmak istemiyorum "+GetSexPhrase("clot","fahişe")+". Defol!";
			Link.l1 = "Heh, ne kaltak ama...";
			Link.l1.go = "exit";
		break;

		case "Underground0": //девка реально заблудилась
            dialog.text = "Aman Tanrım, seni gördüğüme çok sevindim!";
			Link.l1 = "Ne haber, güzelim?";
			Link.l1.go = "Underground0_1";
		break;
		case "Underground0_1": 
            dialog.text = "Burada kayboldum! Aman Tanrım, çok korkuyorum!!!";
			Link.l1 = "Artık iyisin. Beni takip et, sana yolu göstereceğim. Yüzeye çıktığında hemen evine koş ve bir daha seni burada görmemem için dua et!";
			Link.l1.go = "Underground0_2";
		break;
		case "Underground0_2": 
            dialog.text = "Dediğiniz gibi, "+GetAddress_Form(NPChar)+".";
			Link.l1 = "Pekâlâ.";
			Link.l1.go = "exit";
			npchar.LifeDay = 0;
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
		break;

		case "Underground1": //крутая мочалка
            dialog.text = "Vay canına, galiba bu zindana başka biri daha göz dikmiş!";
			Link.l1 = "Güzelim, burada ne yapıyorsun?";
			Link.l1.go = "Underground1_1";
		break;
		case "Underground1_1": 
            dialog.text = "Sana ne!";
			Link.l1 = "Vay canına, bu cevap milyon peso eder...";
			Link.l1.go = "Underground1_2";
		break;
		case "Underground1_2": 
            dialog.text = "İki milyon için. Kendi yoluna mı gideceksin? Umurumda bile değilsin.";
			Link.l1 = "Eh, hissettiklerimiz karşılıklı, ama yukarıdaki arkadaşın senin için çok endişeliydi...";
			Link.l1.go = "Underground1_3";
		break;
		case "Underground1_3": 
            dialog.text = "Ne aptal! Korkudan altına yapardı, ama beni de kendisi gibi sanıyor.";
			Link.l1 = "Vay canına, onu hiç sevmiyorsun belli. Etek giymiş şeytan gibisin sen.";
			Link.l1.go = "Underground1_4";
		break;
		case "Underground1_4": 
            dialog.text = "Hey, ağzını topla! Hatta en iyisi, kaybol buradan.";
			Link.l1 = "Pekâlâ, eğer yardımıma ihtiyacın yoksa...";
			Link.l1.go = "Underground1_5";
		break;
		case "Underground1_5": 
            dialog.text = "Hayır, istemiyorum!";
			Link.l1 = "O halde elveda, sana bol şans.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
		break;
		case "Underground1_again": 
            dialog.text = "Yine sen mi? Defol git, artık seni görmek istemiyorum...";
			Link.l1 = "Hmm...";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
		break;

	}
}
