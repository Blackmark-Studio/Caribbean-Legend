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
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//--------------------------------- леди в резиденции ---------------------------------
		case "ResWoman":
			NextDiag.TempNode = "ResWoman";
			if (LAi_grp_playeralarm <= 0 && CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Done") && !CheckAttribute(npchar, "quest.chickengod") && sti(npchar.nation) == SPAIN) {
				link.chickengod = "Senora, please excuse me, but I was asked to tell you that you have... a date inside an old pagan pyramid.";
				link.chickengod.go = "chickengod";
			}
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("Tanrım! Böyle iğrenç bir adam odamda! Defol buradan yoksa muhafızları çağırırım!","Bu olamaz... Kim bu sıçanı evime soktu? Defol buradan, alçak herif! Burada işin yok! Hadi git!","Böyle tuhaf zamanlar geldi. Fareler yatak odama giriyor! Defol git!");
				link.l1 = RandPhraseSimple("Sakin ol...","Ağzını topla...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Benim yatak odamda ne yapıyorsun? Defol buradan!","Ne yazık! Sizden hemen burayı terk etmenizi istiyorum!","Affedersiniz efendim, ama buraya davet edilmediniz. Lütfen odamdan çıkın!");
				link.l1 = RandPhraseSimple("Affedersiniz... Ben gidiyorum.","Affedersiniz, yanlış kapı. Gitmem gerek.");
				link.l1.go = "exit";
			}
		break;
		case "Woman_FackYou":
			dialog.text = "Ah, bu da neydi?! Ne aptalım ben! Etrafıma bakmadan dolaşıyorum... Muhafızlar!!!";
			link.l1 = "Kapa çeneni!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- слуга в резиденции ---------------------------------
		case "ResMan":
			NextDiag.TempNode = "ResMan";
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("Defol buradan, pis fare!","Valinin konağından hemen defol, fare!","Valinin evinde ne yaptığın umurumda değil "+XI_ConvertString("Colony"+npchar.city+"Gen")+"Ama benim tavsiyem, şimdi kaybol!");
				link.l1 = RandPhraseSimple("Sakin ol, dostum...","Ağzından çıkanı kulağın duysun!");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Selamlar! Ben vali beyin hizmetkarıyım. Adım "+GetFullName(NPChar)+".","Ben burayı gözetlerim, "+GetAddress_Form(NPChar)+".","Biliyor musun, "+GetAddress_Form(NPChar)+", valimiz iyi bir adamdır ve bize iyi ödeme yapar...");
				link.l1 = RandPhraseSimple("Güzel.","Hm, peki öyle olsun...");
				link.l1.go = "exit";
			}
		break;
		case "Man_FackYou":
			dialog.text = "Yani valiyi soymaya mı karar verdin?! Muhafızlar, hırsızı yakalayın!!";
			link.l1 = "Kapa çeneni!";
			link.l1.go = "fight";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- солдат в резиденции ---------------------------------
		case "ResGuard":
			NextDiag.TempNode = "ResGuard";
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("Buradan gitmen senin için daha iyi olur, "+GetSexPhrase("kanka","kız")+"...","Defol!","Kapıyı ıskaladın, "+GetSexPhrase("kanka","kız")+"? ?   Bu mülk valiye ait "+XI_ConvertString("Colony"+npchar.city+"Gen")+".");
				link.l1 = RandPhraseSimple("Ne zaman istersem o zaman giderim!","Bu seni ilgilendirmez...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Bugün burada hizmet etmem emredildi. Güzel bir yer...","Malikaneyi koruyorum "+GetAddress_Form(NPChar)+".","Emrim, valinin malikanesini korumak.");
				link.l1 = RandPhraseSimple("Öyleyse iyi şanslar...","Hmm, anlıyorum...");
				link.l1.go = "exit";
			}
		break;
		
		case "chickengod":
			pchar.questTemp.ChickenGod.Tasks.o2.Counter = sti(pchar.questTemp.ChickenGod.Tasks.o2.Counter) + 1;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o2.Counter) >= 3) {
				dialog.text = "Ah, evet. Sonunda! Seninle gitmeye hazırım, kaptan.";
				link.l1 = "Bu kadar mı? Señora, gerçekten bunu mu istiyorsunuz?";
				link.l1.go = "chickengod_accept";
			} else {
				sld = CharacterFromID(npchar.city + "_Mayor");
				dialog.text = "Ne?! Sarhoş musunuz, señor? Ne saçma bir şaka bu! Lütfen gidin, yalvarıyorum! "+sld.name+"! Muhafızlar! Yardım edin!";
				link.l1 = "Lanet olsun, gitme vakti.";
				link.l1.go = "chickengod_decline";
			}
			npchar.quest.chickengod = true;
		break;
		
		case "chickengod_accept":
			dialog.text = "Tabii ki! Ah, Señor Aruba ile uzun zamandır mektuplaşıyoruz!";
			link.l1 = "Madem öyle, lütfen gemiye buyurun!";
			link.l1.go = "chickengod_accept_take";
			link.l2 = "Hayır, señora, bu olmaz. Onurum bir kadının tehlikeye atılmasına izin vermez ve açıkça kandırılmışsınız!";
			link.l2.go = "chickengod_accept_nottake";
		break;
		
		case "chickengod_accept_take":
			DialogExit();
			
			pchar.questTemp.ChickenGod.Tasks.o2.Done = true;
			pchar.questTemp.ChickenGod.Tasks.o2.Lady = npchar.id;
			AddDialogExitQuestFunction("ChickenGod_TakeLady");
		break;
		
		case "chickengod_accept_nottake":
			dialog.text = "Öyleyse, sevgili kaptanım, o köylü onur anlayışını al da götüne sok! Ben başka bir haberciyi beklerim, senin kadar dar kafalı olmayan birini!";
			link.l1 = "Büyüleyici!";
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
