#include "DIALOGS\%language%\Common_Duel.c"

#define MAX_PGG_STORIES 		9
#define MAX_PGG_QUEST_STORIES 	3
#define MAX_PGG_MEET_REP 		5

string PGG_Stories[MAX_PGG_STORIES] = {
"... only devil and I know the location and the last man standing will take it all!\n",
"... and Maynard said: 'I don't expect mercy so shouldn't you'.\n",
"... he was that drunk that proposed to arrange the very special hell right there, just to see who of us will endure it longer.\n",
"... funny story of my old pal from Porto Belo...\n",
"... No, gentlemen, those are crappy anecdotes. I've got some good stories to fill your ears\n",
"... Can't say much about the 'Flying Dutchman'. Never seen it. I once boarded some odd brigantine, empty, not a single soul onboard. Guess what? 1700 barrels of fine wine in her hold!.. That is what I call luck!\n",
"... I tend to believe that this 'Flying Dutchman' crap is a fake\n",
"... Ever heard about me being shell shocked at Key West? Although there was no visible damage, I lain for two months. And then my passion persuaded me to confess. They say, with God's help, the matter will go well ... Well, I went, and the priest asked: 'Did you kill many people, my son?' 'And how many ships sunk?' - 'Many' - I answer. And he does not let up: 'Have you seduced many wives?' Then I say: 'Padre, I did not come here to brag'. Ha-ha-ha-ha\n",
"... But in Santa Cruz there was a case during mooring. With a cry of 'Beware!' My sailor throws a whip and hits the local onlooker straight in the forehead! That screams and falls without feelings. The sailor was frightened, not waiting for the ramp he jumped on the pier and gave that poor guy some water. Finally, he woke up and told the sailor: 'You have to shout 'Watch out' when danger is coming, not 'Beware' you idiot! Ha-ha-ha! " 
};

string PGG_QuestStories[MAX_PGG_QUEST_STORIES] = {
"... Got stuck in Florida once...",
"... Can't say much about the 'Flying Dutchman'. Never seen it. I once boarded some odd brigantine, empty, not a single soul onboard. Guess what? 1700 barrels of fine wine in her hold!.. That is what I call luck!...",
"... She killed the poor bastard right in the middle of the tavern after he suggested testing her 'officer skills' upstairs..."
}

string PGG_Meet_GoodRep[MAX_PGG_MEET_REP] = {
"Decent captains are rare breed in these waters.",
"Nobility is out of fashion these days.",
"Oh, now there's a decent captain, not like you at all, cutthroats! He-he!",
"Gentlemen, we have a decent captain at our table, who had been through fire and water countless times. So, what can you tell us, esteemed one?",
"Now there's another glorious corsair, who is not used to look for royal roads.", 
};

string PGG_Meet_BadRep[MAX_PGG_MEET_REP] = {
"Now there's another pirate!",
"Gentlemen, we have a gentleman of fortune at our table, I guess?",
"I smell gunpowder and blood! A filibuster aboard!",
"Ohh, gentlemen, now this is a seasoned corsair, who surely has something to tell in a nice company over a mug of rum... Would you like to join us?",
"Oh, I smell gunpowder... Gentlemen, we now have here another glorious corsair, who sure as hell will have a lot to tell on his confession... Ha-ha-ha!",
};

void ProcessDialogEvent()
{
	int i, n;
	int iRnd = -1;
	int iAns;
	bool bOk;
   	float locx, locy, locz;
	string sTmp, sLoc;
	ref NPChar, sld;
	aref link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    ProcessDuelDialog(NPChar, link, NextDiag);

	if (Dialog.CurrentNode == "First time" && CheckAttribute(NPChar, "meeting")) Dialog.CurrentNode = "Second time";
	switch(Dialog.CurrentNode)
	{
//	Dialog.Text = "Bir hata görürseniz... lütfen Donanma için QA'ya bildirin.";
//	link.l1 = "Elbette!";
//	link.l1.go = "exit.";
	case "First time":
		if (CheckAttribute(NPChar, "PGGAi.location.town.back") && CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			Dialog.text = "Hey, defol git, olur mu! Eğer anlaşmamı bozarsan, kalbini sökerim!";
			link.l1 = RandPhraseSimple("Bana tehdit mi savuruyorsun, köpek herif?!","Sözlerini sana yutturacağım, alçak!");
			link.l1.go = "Exit_Smugglers_Fight";
			link.l2 = "Anladım. İş iştir. Bol şans.";
			link.l2.go = "Exit";
			break;
		}
//		Dialog.Text = "İyi günler, benim adım "+GetFullName(NPChar)+", ya seninki?";
		if(rand(10) == 3)
		{
			iRnd = rand(MAX_PGG_QUEST_STORIES - 1);
			Dialog.Text = PGG_QuestStories[iRnd];
		}
		else
		{
			iRnd = rand(MAX_PGG_STORIES - 1);
			iAns = rand(MAX_PGG_MEET_REP - 1);
			Dialog.Text = PGG_Stories[iRnd]+PCharRepPhrase(PGG_Meet_GoodRep[iAns],PGG_Meet_BadRep[iAns]);
		}		 
//		link.l1 = "Benim adım "+GetFullName(pchar)+".";
		link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Herkese içki! Ben kaptanım "+GetFullName(pchar)+".","'nin kaptanıyım "+PChar.Ship.Name+" ve birkaç yüz gerçek şeytan! He-he! Benim adım "+GetFullName(pchar)+"."),RandPhraseSimple("İzin verin kendimi tanıtayım, beyler. Ben Kaptan "+GetFullName(pchar)+".","Henüz tanışmadık. Ben ' gemisinin kaptanıyım."+PChar.Ship.Name+"   bayrağı altında "+NationNameGenitive(sti(PChar.nation))+" . Benim adım "+GetFullName(pchar)+"."));
		link.l1.go = "Meeting";
		break;

	case "Meeting":
		Dialog.Text = "Herkes burada beni tanır! Ben "+GetFullName(NPChar)+". Tanıştığımıza memnun oldum! Size nasıl yardımcı olabilirim?";
		link.l1 = RandPhraseSimple("Seninle bir işim var!","Seninle konuşmak istiyorum...");
		link.l1.go = "quest";
		if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
		{
			sld = GetRealShip(sti(NPChar.Ship.Type));
			
			Dialog.Text = "Buradaki herkes beni tanır! Ben "+GetFullName(NPChar)+", kaptan "+xiStr(sld.BaseName+"Acc")+" "+NPChar.Ship.Name+".";
			link.l2 = "Benimle gelmeye ne dersin? İki gemi birden daha iyidir. Birlikte iyi işler yapabiliriz.";
			link.l2.go = "companion";
		}
		if (sti(NPChar.Ship.Type) == SHIP_NOTUSED)
		{
			link.l3 = RandPhraseSimple("Gemimde subay olarak hizmet etmek ister misin?","Bence gemimde subay olarak gayet iyi iş çıkarırsın. Ne dersin?");
			link.l3.go = "officer";
		}
		if (bBettaTestMode)
		{
			link.l7 = "(Beta-test) Görevler.";
			link.l7.go = "BT_Quest";
			link.l8 = "(Beta-test) Düellolar.";
			link.l8.go = "outraged";
		}
		link.l9 = "Hiçbir şey.";
		link.l9.go = "exit";
		NextDiag.TempNode = "Second time";
		NPChar.meeting = true;
		break;

	case "Second time":
		if (CheckAttribute(NPChar, "PGGAi.location.town.back") && CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			Dialog.text = "Hey, defol şuradan, hadi! Pazarlığımı bozarsan, kalbini sökerim!";
			link.l1 = RandPhraseSimple("Bana tehdit mi savuruyorsun, köpek?!","Sözlerini sana yutturacağım, alçak!");
			link.l1.go = "Exit_Smugglers_Fight";
			link.l2 = "Anladım. İş iştir. Bol şans.";
			link.l2.go = "Exit";
			break;
		}

		if (CheckAttribute(NPChar, "QuestTalk") && GetNpcQuestPastDayParam(NPChar, "QuestTalk") < 1)
		{
			Dialog.Text = "Bugün için sana zaten her şeyi anlattım!";
			link.l1 = "Ah, evet...";
			link.l1.go = "exit";
			break;
		}

		Dialog.text = RandPhraseSimple("Ne istiyorsun"+GetFullName(pchar)+"?","Kim o? Aa, sensin... Defol, keyfim yok şimdi...");
		link.l1 = RandPhraseSimple("Bir iş hakkında ne dersin?","Seninle konuşmak istiyordum...");
		link.l1.go = "quest";

		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) > 49)
		{
//			Dialog.Text = RandPhraseSimple("Bakın, kim gelmiş! Bu da "+GetFullName(pchar)+" . Yeni bir haber var mı?","Nasıl gidiyor? Size nasıl yardımcı olabilirim?");
			if(rand(10) == 3)
			{
				iRnd = rand(MAX_PGG_QUEST_STORIES - 1);
				Dialog.Text = PGG_QuestStories[iRnd]+PCharRepPhrase(" Ne var ne yok?"," Takımadalar civarında ne haber var?");
			}
			else
			{
				iRnd = rand(MAX_PGG_STORIES - 1);
				iAns = rand(MAX_PGG_MEET_REP - 1);
				Dialog.Text = PGG_Stories[iRnd]+PCharRepPhrase(PGG_Meet_GoodRep[iAns]+" Ne var ne yok?",PGG_Meet_BadRep[iAns]+" Takımadalar civarında ne haber var?");
			}		
			if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
			{
				link.l2 = RandPhraseSimple("Benimle gelmeye ne dersin? İki gemi birden daha iyidir. Birlikte iyi işler yapabiliriz.","Tecrübeli bir kaptana benziyorsun. Benim bayrağım altında yelken açmak ister misin?");
				link.l2.go = "companion";
			}
			if (sti(NPChar.Ship.Type) == SHIP_NOTUSED)
			{
				Dialog.Text = RandPhraseSimple("Ah, vah bana... Gemim battı!","Kimler gelmiş?! Seni buraya ne getirdi? Bu arada, gemimi kaybettim...");
				link.l3 = RandPhraseSimple("Ne yazık. Belki bir dahaki sefere daha şanslı olursun.","Yok artık... Neyse, benim gitmem gerek. Görüşürüz.");
				link.l3.go = "exit";
				if (FindFreeRandomOfficer() > 0)
				{
					link.l3 = RandPhraseSimple("Gemimde subay olarak hizmet etmek ister misin?","Bence gemimde subay olarak iyi iş çıkarırsın. Ne dersin?");
					link.l3.go = "officer";
				}
			}
//			link.l4 = "Ne haber?";
//			link.l4.go = "rumours_capitan";
		}
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 20 || bBettaTestMode)
		{
			link.l8 = PCharRepPhrase("Ne çirkin bir surat. Dövülmeyi hak ediyor.","Ah, bizim 'dostumuz'. Göğsünde birkaç yeni delik ister misin?");
			link.l8.go = "outraged";
		}
		link.l9 = "Hiçbir şey.";
		link.l9.go = "exit";
		NextDiag.TempNode = "Second time";
		break;

	case "no_ship":
		break;

//==================================================
// Officer 
//==================================================
	case "officer":
		//раз в день.
		if (CheckAttribute(NPChar, "Officer_Talk") && GetNpcQuestPastDayParam(NPChar, "Officer_Talk") < 1 && !bPGGLogShow)
		{
			Dialog.Text = RandPhraseSimple("Sana zaten ilgilenmediğimi söyledim.","Sanırım her şeyi zaten konuşmuştuk.");
			link.l1 = RandPhraseSimple("Nasıl unuturum?","Adil bir cevap. Hoşça kal.");
			link.l1.go = "exit";
			break;
		}
		//если уже был офицером, то посылает нафиг.
		if (CheckAttribute(NPChar, "PGGAi.Officer"))
		{
			Dialog.Text = RandPhraseSimple("Hmm... belki de hayır. İkinci kez olmaz.","Ve sen, bu numarayı ikinci kez yiyeceğimi mi sandın?!");
			link.l1 = RandPhraseSimple("Peki, nasıl istersen...","Pekala. O zaman görüşürüz.");
			link.l1.go = "exit";
			break;
		}
		//если отношение ниже 70, то в 70% случаев откажет...
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70 && rand(100) < 70)
		{
			Dialog.Text = RandPhraseSimple("Hmm... Hayır, sanırım değil.","Hayır, ben bir kaptanım ve subay olarak hizmet etmek istemiyorum.");
			link.l1 = RandPhraseSimple("Peki, nasıl istersen...","Pekala. O zaman görüşürüz.");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Officer_Talk");
			break;
		}
		//Проверка на ПИРАТЕС, не было! :) //navy 04.04.07
		if (FindFreeRandomOfficer() < 1)
		{
			Dialog.Text = RandPhraseSimple("Zaten tam bir setin var.","Sana emir vermeye hazır olduğunu sanmıyorum.");
			link.l1 = RandPhraseSimple("Yazık...","Kader başka türlü hükmetti.");
			link.l1.go = "exit";
			break;
		}
		if (!CheckAttribute(NPChar, "Quest.Officer.Price"))
		{
			NPChar.Quest.Officer.Price = 10000 + sti(NPChar.rank)*500*MOD_SKILL_ENEMY_RATE - MakeInt(GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE)*1000);
		}
		Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("Tam da ihtiyacım olan buydu! Kılıçlarımız düşmanlarımızın kanını tadacak! Ama bir sorun var - hâlâ ihtiyacım olan bir şey var "+NPChar.Quest.Officer.Price+" borçlarımı ödemek için pesoya ihtiyacım var.","Gerçekten denizciye benziyorsun. Ve eğer ödemeye hazırsan "+NPChar.Quest.Officer.Price+" peso, birlikte iyi çalışabiliriz."),LinkRandPhrase("Teklifiniz oldukça gurur verici. Oldukça makul bir ücret karşılığında sizin için çalışmayı kabul ediyorum "+NPChar.Quest.Officer.Price+" pesos.","Hmm... Tecrübeli bir denizciye benziyorsun. Eğer bana ödeme yapmaya hazırsan teklifini kabul edebilirim "+NPChar.Quest.Officer.Price+" pesos.","Bence birlikte iyi çalışacağız, kaptan. Sadece "+NPChar.Quest.Officer.Price+" peso, ve anlaşmamız tamam."));

		MakeRandomLinkOrderTwo(link, PCharRepPhrase(RandSwear() + RandPhraseSimple("That suits me fine. I just hope you're not going to charge me on daily basis.", "That's very expensive, but I hope you're worth it."), 
				LinkRandPhrase("I agree. Consider yourself a part of the crew.", "Hm... I think, I can afford it.", "Looks like you are worth it. Take the coins!")), "officer_hired",
									PCharRepPhrase(RandSwear() + RandPhraseSimple("You're not worth that much. See you...", "Too damn expensive for me."), 
				LinkRandPhrase("Yeah... Greed is not a sin...", "Are you laughing at me? I can buy a dozen like you for such money.", "That's a rip off. Where am I supposed to find such money?")), "exit");
		link.l3 = "Hmm... peki, ne kadar yetkin olduğunu söyleyebilir misin?";
		link.l3.go = "Exit_ShowParam";
		break;

	case "officer_hired":
		if (sti(pchar.money) < sti(NPChar.Quest.Officer.Price))
		{
			Dialog.Text = "Bence nakit sıkıntınız var, kaptan.";
			link.l1 = "Ah... gerçekten.";
			link.l1.go = "exit";
			break;
		}
		pchar.questTemp.HiringOfficerIDX = NPChar.index;
		AddMoneyToCharacter(pchar, -(makeint(NPChar.Quest.Officer.Price)));
		AddDialogExitQuestFunction("PGG_BecomeHiredOfficer");
		NPChar.loyality = MakeInt(PGG_ChangeRelation2MainCharacter(NPChar, 0)*0.3)

		DeleteAttribute(NPChar, "Quest.Officer");
		DeleteAttribute(NPChar, "PGGAi.Task");
		DeleteAttribute(NPChar, "PGGAi.LockService");

		Dialog.Text = RandPhraseSimple("Harika!","Sana hiç şüphem olmadı, kaptan.");
		link.l1 = "Yola çıkışa geç kalma.";
		link.l1.go = "exit";
		break;

//==================================================
// Companion 
//==================================================
	case "companion":
		Dialog.Text = "Bir hata var, geliştiricilere bildir";
		link.l1 = "Yapacağım!";
		link.l1.go = "exit";
		//раз в день.
		if (CheckAttribute(NPChar, "Companion_Talk") && GetNpcQuestPastDayParam(NPChar, "Companion_Talk") < 1 && !bPGGLogShow)
		{
			Dialog.Text = RandPhraseSimple("Sana zaten ilgilenmediğimi söyledim.","Sanırım her şeyi zaten konuşmuştuk.");
			link.l1 = RandPhraseSimple("Nasıl unutabilirim ki?","Adil bir cevap. Hoşça kal.");
			link.l1.go = "exit";
			break;
		}
		//разница в один класс.. нефиг халявить
		if (GetCharacterShipClass(NPChar) < GetCharacterShipClass(PChar)-1)
		{
			Dialog.Text = RandPhraseSimple("Seninle denize açılmak mı?! Önce biraz büyü de gel!","Sanırım bununla ilgilenmiyorum!");
			link.l1 = RandPhraseSimple("Peki, nasıl istersen...","Pekala. Görüşürüz, o zaman.");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
			break;
		}
		//если отношение ниже 70, то в 70% случаев откажет...
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70 && rand(100) < 70)
		{
			Dialog.Text = RandPhraseSimple("Hmm... Hayır, sanırım değil.","Hayır, teşekkürler. Kimsenin emrinde çalışmayı sevmem.");
			link.l1 = RandPhraseSimple("Peki, nasıl istersen...","Pekala. Görüşürüz, o zaman.");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
			break;
		}
		//есть ли место для компаньона.
		if (SetCompanionIndex(pchar, -1, sti(NPChar.index)) != -1)
		{
			Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("Senden hoşlandım! Anlaştık! Şimdiden ceplerimizdeki peso seslerini duyabiliyorum!","Sen akıllı birisin "+GetSexPhrase("adam","kız")+"... Birlikte iyi çalışacağımızı düşünüyorum!"),LinkRandPhrase("Teklifini beğendim. Kabul ediyorum.","Bu ilginç. Biliyor musun, birlikte çok daha fazlasını başarabiliriz bence!","Bu eğlenceli olacak. Anlaştık!"));
			link.l1 = RandPhraseSimple("Harika! Seni denizde bekliyor olacağım!","Anlaştık! Harika bir tayfa olacağız.");
			link.l1.go = "exit";
			NPChar.PGGAi.IsPGG = false;
			NPChar.PGGAi.location.town = "none";
			NPChar.Dialog.TempNode = "hired";
			NPChar.Dialog.FileName = "Enc_Officer_dialog.c";
            NPChar.Payment = true;
            NPChar.Money   = 0;
            
            SetBaseShipData(NPChar);
            DeleteAttribute(NPChar,"ship.sails");
			DeleteAttribute(NPChar,"ship.masts");
			DeleteAttribute(NPChar,"ship.blots");
			DeleteAttribute(NPChar,"ship.hulls");
			
			Fantom_SetCannons(NPChar, "pirate");
			Fantom_SetBalls(NPChar, "pirate");
    
			DeleteAttribute(NPChar, "PGGAi.Task");
			DeleteAttribute(NPChar, "PGGAi.LockService");
			SetCharacterRemovable(NPChar, true);
			SaveCurrentNpcQuestDateParam(NPChar, "Companion.CheckRelation");
		}
		else
		{
			Dialog.Text = RandPhraseSimple("Bence zaten yeterince yoldaşın var.","Zaten yeterince gemin var – neden daha fazlasına ihtiyacın olsun ki?");
			link.l1 = "Evet... Belki de haklısın.";
			link.l1.go = "exit";
		}
		break;

	case "companion_leave":
		Dialog.Text = RandSwear()+" "+NPCharRepPhrase(NPChar,RandPhraseSimple("Senden sıkıldım!!! Filondan ayrılıyorum!","Sabrım tükendi! Gidiyorum."),RandPhraseSimple("Senin maceralarından bıktım, 'amiral'... Müsaadenle artık gideceğim.","Senin komutanlığından bıktım ve filondan ayrılıyorum."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Pekâlâ, defol o zaman.","Pekala, nereye istersen git."),RandPhraseSimple("Pekâlâ. Seni tutmayacağım.","Bu senin seçimin. Yolun açık olsun."));
		link.l1.go = "Exit_Companion_Leave";
		link.l2 = PCharRepPhrase(RandPhraseSimple("Ehh... biraz daha fazlası olur mu?","Caramba! Amanın, belki kalabilirsin? Mürettebatına da biraz fazladan ödeme yapabilirim!"),RandPhraseSimple("Senden ayrılmak istemem... Belki küçük bir tazminat aramızdaki meseleyi çözebilir?","Maaşını artırmaya ne dersin?"));
		link.l2.go = "companion_stay";
		break;

	case "companion_stay":
		if (CheckAttribute(NPChar, "Quest.Companion"))
		{
			Dialog.Text = RandPhraseSimple("Bir kere bana yetti. Sözlerine artık güvenmeyeceğim!","Beni parayla kandıramazsın! Kararım kesin!");
			link.l1 = RandPhraseSimple("Pekala, sana bol şans.","O zaman defol ve bir daha seni asla görmeyeyim!");
			link.l1.go = "Exit_Companion_Leave";
			break;
		}
		NPChar.Quest.Companion.Price = 2*GetSalaryForShip(NPChar);
		Dialog.Text = RandSwear()+" "+NPCharRepPhrase(NPChar,RandPhraseSimple("Bir bedel mi? Peki! Toplamda "+NPChar.Quest.Companion.Price+"   peso bana yeter.","Pekâlâ, belki de, eğer mürettebatıma ödeme yapmaya hazırsan "+NPChar.Quest.Companion.Price+" peso, onları kalmaya ikna edebilirim."),RandPhraseSimple("Pekala! Küçük bir ücret karşılığında kalabilirim "+NPChar.Quest.Companion.Price+" peso!",NPChar.Quest.Companion.Price+" bir süreliğine beni ve mürettebatımı memnun edecek."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Bana mı gülüyorsun yoksa ne?! Defol, hemen!","Ha! Bu parayı çok daha faydalı bir şeye harcamayı tercih ederim!"),RandPhraseSimple("Ah, hayır. O kadar zengin değilim!","Elveda. Bu kadar ödeyeceğim."));
		link.l1.go = "Exit_Companion_Leave";
		if (sti(pchar.money) >= sti(NPChar.Quest.Companion.Price))
		{
			link.l2 = PCharRepPhrase(RandPhraseSimple("Mükemmel! İşte ödülünüz!","Hiçbir zaman bunun tamamen para ile ilgili olduğundan şüphe etmedim!"),RandPhraseSimple("Harika! Kaldığına sevindim.","İşte sana söz verdiğim şey."));
			link.l2.go = "Exit_Companion_Stay";
		}
		break;

	case "Exit_Companion_Leave":
		chrDisableReloadToLocation = false;
		RemoveCharacterCompanion(pchar, NPChar);

		NPChar.PGGAi.IsPGG = true;
		NPChar.RebirthPhantom = true;
		NPChar.PGGAi.location.town = GetCurrentTown();

		LAi_SetWarriorTypeNoGroup(NPChar);
		NextDiag.CurrentNode = "Second Time";
		DialogExit();
		break;

	case "Exit_Companion_Stay":
        GetCharacterPos(NPChar, &locx, &locy, &locz);
        sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		LAi_ActorGoToLocation(NPChar, "reload", sTmp, "none", "", "", "", 5.0);

		AddMoneyToCharacter(pchar, -(makeint(NPChar.Quest.Companion.Price)));
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

//==================================================
// Quests
//==================================================
//==== BETTA_TEST ====
	case "BT_Quest":
		Dialog.Text = "Bir şablon seç!";
		link.l1 = " Görev 1 şablonu - deniz. ";
		link.l1.go = "BT_Quest_1";
		link.l2 = "SEÇİLDİ! Görev 1 şablonu - kara.";
		link.l2.go = "BT_Quest_2";
		break;

	case "BT_Quest_1":
		NPChar.PGGAi.ActiveQuest.QstNumber = 0;
		NPChar.PGGAi.ActiveQuest.QstNumber.Template = 1;
		Dialog.Text = " Görev 1 şablonu - deniz. ";
		link.l1 = "Ah, evet...";
		link.l1.go = "quest";
		break;
	case "BT_Quest_2":
		NPChar.PGGAi.ActiveQuest.QstNumber = 0;
		NPChar.PGGAi.ActiveQuest.QstNumber.Template = 0;
		Dialog.Text = "SEÇİLDİ! Görev 1 şablonu - kara.";
		link.l1 = "Ah, evet...";
		link.l1.go = "quest";
		break;
//==== BETTA_TEST ====

	case "quest":
		chrDisableReloadToLocation = false;
		if (CheckAttribute(NPChar, "QuestTalk") && GetNpcQuestPastDayParam(NPChar, "QuestTalk") < 1)
		{
			Dialog.Text = "Sana zaten her şeyi anlattım!";
			link.l1 = "Ah, evet...";
			link.l1.go = "exit";
			break;
		}
		Dialog.Text = RandPhraseSimple("Ne işin var?.. Hık! Görmüyor musun - ben ve çocuklar keyfimize bakıyoruz!.. Hık...","Ehh... Bugün iş yok!");
		link.l1 = "Anladım...";
		link.l1.go = "exit";
		if (!PGG_IsQuestAvaible()) break; //квест нельзя брать.
		//if (!CheckAttribute(NPChar, "PGGAi.ActiveQuest") && !bBettaTestMode) break; //для релиза возможно надо будет закрыть. если закоментить, то ГГ сам может предложить дело
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest.QstNumber")) iRnd = sti(NPChar.PGGAi.ActiveQuest.QstNumber); //тип квеста, который хочет от нас ПГГ
		if (iRnd == -1 && !CheckAttribute(pchar, "GenQuest.PGG_Quest")) iRnd = rand(1); // может и не быть
		switch (iRnd)
		{
		case 0:
			if (sti(NPChar.Ship.Type) != SHIP_NOTUSED && sti(PChar.Ship.Type) != SHIP_NOTUSED && GetCharacterShipClass(PChar) <= 4 && GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				//квест от ПГГ
				/*if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
				{ */
				if (!CheckAttribute(pchar, "GenQuest.PGG_Quest"))
				{  // не занят другими квестами ПГГ
					Dialog.Text = "Ne konuşması? Gerçi, tam zamanında geldin. İş olunca, her zaman hazırım!";
					link.l1 = "Hmm. Neden bahsediyorsun?";
					link.l1.go = "Quest_1_Work";
					NPChar.PGGAi.ActiveQuest = 1; // чтоб говорил от своего имени
					PChar.GenQuest.PGG_Quest = 1; // чтоб не достовали другие ПГГ
				}
				/* }
				//квест от ГГ
				else
				{
					if ()
					{
						Log_TestInfo("The test sentence of the protagonist");

						Dialog.Text = LinkRandPhrase("...o yeri yalnızca ben ve şeytan biliyoruz, hayatta kalan son kişi ise her şeyi alacak!..","...ve Meinard şöyle cevap verdi: 'Senden merhamet beklemiyorum, ben de sana göstermeyeceğim'","...ve açık denize çıktığımızda, o zaten biraz sarhoşken, şöyle dedi: 'Ortalığı birbirine katalım ve en sona kim kalacak görelim'.")+PCharRepPhrase(LinkRandPhrase("Şimdi bir korsan daha var!","Beyler, masamızda bir talihli beyefendi var mı, merak ediyorum?","Barut ve kan kokusu alıyorum! İskele tarafında bir korsan var!"),LinkRandPhrase("Bu sularda düzgün kaptanlar nadir bulunur.","Asalet bu devirde artık moda değil.","Bak işte, gerçek bir kaptan var orada, sizin gibi çapulculara hiç benzemez! He-he!"));
						link.l1 = "Bağırmıyorum, sana söylüyorum - kârlı bir anlaşma var!";
						link.l1.go = "Quest_1_Work";
					}
				}  /**/
			}
			break;
		}
		SaveCurrentNpcQuestDateParam(NPChar, "QuestTalk");
		break;

	case "quest_onStay": // ПГГ сам подходит
		chrDisableReloadToLocation = false;
		Dialog.Text = "Dikkat et, dikkat et! Ah! Seni tanıyorum. Sen "+GetFullName(PChar)+". Sizin hakkınızda çok şey duydum.";
		if (!CheckAttribute(NPChar, "meeting") || !sti(NPChar.meeting))
		{
			link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Ben kaptanım "+GetFullName(pchar)+".","'nin kaptanıyım "+PChar.Ship.Name+" ve birkaç yüz gerçek şeytan! He-he! Benim adım "+GetFullName(pchar)+".")+" Ama seni hatırlamıyorum.",RandPhraseSimple("İzin verirseniz kendimi tanıtayım, beyler. Ben Kaptan "+GetFullName(pchar)+".","Henüz tanışmadık. Ben ' gemisinin kaptanıyım."+PChar.Ship.Name+"   bayrağı altında "+NationNameGenitive(sti(PChar.nation))+" . Benim adım "+GetFullName(pchar)+".")+" Ama seni hatırlamıyorum.");
//			link.l1 = "Hmm... sen de kimsin? Seni hatırlamıyorum.";
			link.l1.go = "Quest_1_Meeting";
		}
		else
		{
			link.l1 = "Merhaba, "+GetFullName(NPChar)+". Hayat nasıl?";
			link.l1.go = "Quest_1_Work";
		}
		SaveCurrentNpcQuestDateParam(NPChar, "QuestTalk");
		break;

	//=========== Первый квест ==========
	case "Quest_1_Meeting":
		sld = GetRealShip(sti(NPChar.Ship.Type));
		Dialog.Text = "Ben "+GetFullName(NPChar)+", kaptan "+xiStr(sld.BaseName+"Acc")+" "+NPChar.Ship.Name+NPCharRepPhrase(NPChar,". Tüm İspanyol Ana Karası'ndaki en namlı korsan.",". Sadece bir denizci.");
		link.l1 = "Evet, şimdi seni hatırlayacağım.";
		link.l1.go = "Quest_1_Work";
		NPChar.meeting = true;
		break;

	case "Quest_1_Work":
		PChar.GenQuest.PGG_Quest.Template = rand(1);
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest.QstNumber.Template"))
		{
			PChar.GenQuest.PGG_Quest.Template = NPChar.PGGAi.ActiveQuest.QstNumber.Template;
		}
		PChar.GenQuest.PGG_Quest.Parts = GetCompanionQuantity(PChar)+1;
		PChar.GenQuest.PGG_Quest.Nation = rand(NON_PIRATES);
		PChar.GenQuest.PGG_Quest.Island = GetRandIslandId();
		while(PChar.GenQuest.PGG_Quest.Island == Islands[GetCharacterCurrentIsland(pchar)].id)
		{
			PChar.GenQuest.PGG_Quest.Island = GetRandIslandId();
		}
		PChar.GenQuest.PGG_Quest.Island.Shore = GetIslandRandomShoreId(PChar.GenQuest.PGG_Quest.Island);
		while(PChar.GenQuest.PGG_Quest.Island.Shore == "")
		{
			PChar.GenQuest.PGG_Quest.Island = GetRandIslandId();
			PChar.GenQuest.PGG_Quest.Island.Shore = GetIslandRandomShoreId(PChar.GenQuest.PGG_Quest.Island);
			if (sti(PChar.GenQuest.PGG_Quest.Template)) 
			{
				if (!isLocationFreeForQuests(PChar.GenQuest.PGG_Quest.Island)) PChar.GenQuest.PGG_Quest.Island.Shore = "";
			}
			else
			{
				if (!isLocationFreeForQuests(PChar.GenQuest.PGG_Quest.Island.Shore)) PChar.GenQuest.PGG_Quest.Island.Shore = "";
			}
		}
		PChar.GenQuest.PGG_Quest.Island.Town = FindTownOnIsland(PChar.GenQuest.PGG_Quest.Island);
		PChar.GenQuest.PGG_Quest.Days = 3 + GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(pchar)].id, PChar.GenQuest.PGG_Quest.Island);
		PChar.GenQuest.PGG_Quest.Goods = GetRandomGood(FLAG_GOODS_TYPE_CROWN, FLAG_GOODS_NONE);
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = "Sizinle bir işim var, "+GetSexPhrase("dostum","kız")+". Sana güvenebileceğimi biliyorum, ama bunu meyhanede konuşamam - yanlış yerde fazla kulak var. Seni gemimde bekleyeceğim. Eski tekneciğimin adı '"+NPChar.Ship.Name+"'.";
//			link.l1 = "Şimdi söyle, ziyaretçilere ayıracak vaktim yok.";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("Sana ve adamlarına ilginç bir işim var.","Eğer güçlerimizi birleştirirsek, gerçekten büyük bir ödül kazanabiliriz! Tabii, bu arada birini öldürmemiz gerekecek. He-he."),RandPhraseSimple("Sana bir iş teklifim var, kaptan.","Kaptan, şöhretiniz eşsiz, bu yüzden sizi son derece cazip bir girişime davet ediyorum."))+RandPhraseSimple("Sadece ikimizin arasında kalsın. Bunu ' kamarasında konuşalım "+NPChar.Ship.Name+" en iyi biranın fıçısı başında. Bugün.","Burada konuşmamalıyız, detayları şurada konuşalım: '"+NPChar.Ship.Name+" huzur ve sessizlik içinde. Ve lütfen çok oyalanmayın.");
			link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Bu gecikmelere lanet olsun! Eğer iyi bir haber varsa hemen bilmek isterim, kötü bir şeyse daha da çabuk öğrenmek isterim!","Böylesine kısa tellerin hiçbir anlamı yok! Meyhanede uygun bir oda var - hadi oraya gidelim!"),RandPhraseSimple("Ve neden teklifinizi şu anda, meyhanenin odasında konuşamıyoruz?","Ne yazık ki geminizi ziyaret etmek gibi bir isteğim yok. Bir şey istiyorsanız, hemen burada söyleyin!"));
		}
		else
		{
			PChar.GenQuest.PGG_Quest.Nation = FindEnemyNation2NationWithoutPirates(sti(PChar.Nation));
			Dialog.Text = "Pssst... İş konuşmak için meyhane pek uygun değil - fazla istenmeyen kulak var. Seni gemimde bekliyorum '"+NPChar.Ship.Name+". Orada konuşacağız.";
			link.l1 = "Vaktim yok ve ziyaret etmeyi de sevmem.";
		}
		link.l1.go = "Quest_1_Work_1";
		link.l2 = PCharRepPhrase(RandPhraseSimple("Geleceğim. Ama eğer sadece vaktimi harcıyorsan, dilini koparırım!",RandSwear()+"Pekala, beni bekle. Umarım teklifin buna değer. Ve sakın bana oyun oynamayı düşünme!"),RandPhraseSimple("Davetinizi memnuniyetle kabul edeceğim, kaptan.","Beni meraklandırdınız. Elbette, geleceğim."));
		link.l2.go = "Exit_Quest_1_AfterTavernTalk";
		break;

	case "Quest_1_Work_1":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("Deniz tutmuş galiba seni, ha? Git de annenin eteğinin altına saklan o zaman!","Korktun mu?! Defol!"),RandPhraseSimple("Olmaz. Altını istemiyorsan, sen bilirsin.","Bu iş böyle olur, başka yolu yok. İstemiyorsan sorun değil, başkaları da var."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Ha! Cesursun, değil mi? Peki, geliyorum!","Silahına sadık kalabildiğini görüyorum, kaptan. Peki, beni bekle."),RandPhraseSimple("Pekala, kabul ediyorum.","Sen gerçekten lafı uzatmayı seviyorsun. Geminde iş konuşmaya hazırım."));
		link.l1.go = "Exit_Quest_1_AfterTavernTalk";
		link.l2 = PCharRepPhrase(RandPhraseSimple("Ha! Beni gemine çekip orada öldüreceğini mi sandın? O iş öyle olmaz!","Sözlerin beş para etmez! Seninle hiçbir işim olmaz!"),"Şüpheli bir teklif. Reddetmeliyim.");
		link.l2.go = "Quest_1_NotWork";
		break;

	case "Quest_1_NotWork":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("Bana rom ver! Ve sen de gözümün önünden kaybol!","Her şeyi zaten konuşmadık mı?"),RandPhraseSimple("Kendi işine bak. Benim de yapacak işlerim var.","Sanırım konuşacak bir şeyimiz yok."));
		link.l1 = RandSwear();
		link.l1.go = "exit_2";
		break;

	case "Quest_1_Work_2":
		Dialog.Text = "Sana gemimde seni bekleyeceğimi söylemiştim!";
		link.l1 = "Ah... tabii...";
		link.l1.go = "exit";
		NextDiag.TempNode = "Quest_1_Work_2";
		break;

	case "Exit_Quest_1_AfterTavernTalk":
		PChar.GenQuest.PGG_Quest = 1;
		PChar.GenQuest.PGG_Quest.Stage = 0;
		PChar.GenQuest.PGG_Quest.PGGid = NPChar.id;

		Group_AddCharacter("PGGQuest", NPChar.id);
		Group_SetGroupCommander("PGGQuest", NPChar.id);
		Group_SetAddress("PGGQuest", Islands[GetCharacterCurrentIsland(PChar)].id, "Quest_Ships", "Quest_Ship_1");
		Group_SetTaskNone("PGGQuest");

		SetTimerConditionParam("PGGQuest1_RemoveShip_Timer", "PGGQuest1_RemoveShip_Timer", 0, 0, 0, MakeInt(GetHour() + 6), false);
		PChar.Quest.PGGQuest1_RemoveShip_Timer.function = "PGG_Q1RemoveShip";

		NPChar.Ship.Mode = "Pirate";
		NPChar.DeckDialogNode = "Quest_1_Ship";
		NPChar.Nation.Bak = NPChar.Nation;
		NPChar.Nation = GetCityNation(GetCurrentTown());
		NPChar.AlwaysFriend = true;
		NPChar.Abordage.Enable = false; //нельзя брать на абордаж
		SetCharacterRelationBoth(sti(PChar.index), sti(NPChar.index), RELATION_FRIEND);

		ReOpenQuestHeader("Gen_PGGQuest1");
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Tavern");
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Tavern_1");
			AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("",""));
		}
		AddQuestUserData("Gen_PGGQuest1", "sShipName", NPChar.Ship.Name);

		NextDiag.CurrentNode = "Quest_1_Work_2";
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;

	case "Quest_1_Ship":
		PChar.Quest.PGGQuest1_RemoveShip_Timer.Over = "yes";
		if (GetCompanionQuantity(PChar) == COMPANION_MAX)
		{
			Dialog.Text = RandPhraseSimple("Ah, hayır, bu olmaz... Bu kadar çok gemi sana fazla gelmez mi? "+GetSexPhrase("dostum","kız")+"?","Ha! Böyle kalabalık bir yerde sır saklamak imkânsız. Defol.");
			link.l1 = RandPhraseSimple("Nasıl isterseniz!","Pekâlâ. Umurumda bile değil.");
			link.l1.go = "Exit";
			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_RemoveEnd.function = "PGG_Q1RemoveShip";
			break;
		}
		PChar.GenQuest.PGG_Quest.Stage = 1;
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = "Harika. Artık etrafta istenmeyen kulaklar olmadığına eminim ve tayfam da çoktan bilgilendirildi. Teklifim, sahipsiz malları ele geçirmek.";
//			link.l1 = "Peki bunda ne zorluk var? Neden bunun için ilk başta bana ihtiyacın olsun ki?";
			Dialog.Text = RandPhraseSimple("Hoş geldiniz, kaptan!","Harika. Artık etrafta istenmeyen kulaklar olmadığından eminim ve tayfam da zaten bilgilendirildi. Yani teklifim, sahipsiz bazı malları ele geçirmek.")+" Yani teklifim, sahipsiz bazı malları ele geçirmek.";
			link.l1 = RandPhraseSimple("Peki bunda ne zorluk var? Neden bunun için bana ihtiyacın olsun ki en başta?","Sahipsiz mi?! Şaka yapıyor olmalısın!");
		}
		else
		{
			Dialog.Text = "Artık etrafta istenmeyen kulakların olmadığından eminim - hadi, söyle bakalım!";
			link.l1 = "Yani teklifim, sahipsiz bazı malları ele geçirmek.";
		}
		link.l1.go = "Quest_1_Ship_1";
		break;

	case "Quest_1_Ship_1":
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			Dialog.Text = RandPhraseSimple("Pekala, burayı kendilerine ait görenler var ve onları aksine ikna etmek gerekiyor.","Elbette, birinin öldürülmesi gerekecek - ama eminim bu bir sorun olmayacaktır, değil mi?");
			link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Hadi işe koyulalım!","Bu tam bir katliam kokuyor!   Peki, onlar nerede?"),RandPhraseSimple("Teklifiniz hakkında daha fazla ayrıntı öğrenmek isterim.","Bana tam olarak ne teklif ediyorsun?"));
			link.l1.go = "Quest_1_Ship_Detail";
			link.l2 = PCharRepPhrase(RandPhraseSimple("Beni kandırmaya çalışıyorsun. Buna asla katılmam!","Bu kolay görünüyor, ama sana güvenmiyorum! Senin için ateşten kestane mi çıkartayım istiyorsun? Kusura bakma, kabul etmiyorum!"),RandPhraseSimple("Kulağa hoş geliyor, ama ben almayayım.","Hayır, çalmam, bana hediye vermelerini tercih ederim."));
			link.l2.go = "Quest_1_Ship_Refuse";
		}
		else
		{
			Dialog.Text = "Bunda ne var ki? İlk başta bunun için neden bana ihtiyacın olsun ki?";
			link.l1 = "Pekala, burayı kendine ait görenler var ve onları aksine ikna etmek gerekiyor.";
			link.l1.go = "Quest_1_Ship_Detail";
		}
		break;

	case "Quest_1_Ship_Detail":
		sTmp = "A caravan belonging to " + NationNameGenitive(sti(PChar.GenQuest.PGG_Quest.Nation)) + ", transporting ";
		if (sti(PChar.GenQuest.PGG_Quest.Goods) == GOOD_SLAVES)
		{
			sTmp += "Slaves";
			PChar.GenQuest.PGG_Quest.Goods.Text = "Slaves";
		}
		else
		{
			sTmp += XI_ConvertString(Goods[sti(PChar.GenQuest.PGG_Quest.Goods)].Name);
			PChar.GenQuest.PGG_Quest.Goods.Text = XI_ConvertString(Goods[sti(PChar.GenQuest.PGG_Quest.Goods)].Name);
		}

		if (PChar.GenQuest.PGG_Quest.Island.Town == "" || PChar.GenQuest.PGG_Quest.Island.Town == "Caiman" ||
			PChar.GenQuest.PGG_Quest.Island.Town == "Terks" || PChar.GenQuest.PGG_Quest.Island.Town == "Dominica")
		{
			sLoc = GetIslandNameByID(PChar.GenQuest.PGG_Quest.Island);
		}
		else
		{
			sLoc = XI_ConvertString("Colony" + PChar.GenQuest.PGG_Quest.Island.Town + "Gen");
		}
		
		if (sti(PChar.GenQuest.PGG_Quest.Template)) 
		{
			sTmp +=	", stopped not far from " + sLoc + " at the cove of " + GetLocationNameByID(PChar.GenQuest.PGG_Quest.Island.Shore) + " to resupply.";
		}
		else
		{
			sTmp += ", was caught in the storm not far from " + sLoc + " and went down. But they managed to secure part of the cargo and landed in the cove of " + GetLocationNameByID(PChar.GenQuest.PGG_Quest.Island.Shore) +
				" Now they are waiting their squadron to come.";
		}
		
		Dialog.Text = sTmp;
		link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Uzatma, söyle hadi!","Senin hakkında haklıymışım, başka ne biliyorsun?"),RandPhraseSimple("Bu çok ilginç, lütfen devam edin!","Ben "+GetSexPhrase("hepsi","hepsi")+" kulaklar!"));
		link.l1.go = "Quest_1_Ship_Detail_1";

		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			link.l2 = PCharRepPhrase(RandPhraseSimple("Bu kulağa cazip bir teklif gibi geliyor, ama yine de reddediyorum. Kavga etmeme gerek yok "+NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation))+".","Bir kervan mı? Sahipsiz mi?! Onu koruyan bin asker olmalı! Hayır, bu iş olmaz. Gidiyorum."),RandPhraseSimple("Hayır, ben savaşta değilim "+NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation))+", bu yüzden ilgilenmiyorum.","Cevabım hayır! İlişkilerimi mahvetmeyeceğim "+NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation))+"!"));
			link.l2.go = NPCharRepPhrase(NPChar, "Quest_1_Ship_BadWay", "Quest_1_Ship_Refuse");
		}
		else
		{
			Dialog.Text = "Bu tam bir katliam kokuyor!   Peki ya ayrıntılar?";
			link.l1 = sTmp;
		}
		if (sti(PChar.GenQuest.PGG_Quest.Template)) 
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Detail_A");
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Detail_B");
		}
		AddQuestUserData("Gen_PGGQuest1", "sNation", NationNameGenitive(sti(PChar.GenQuest.PGG_Quest.Nation)));
		AddQuestUserData("Gen_PGGQuest1", "sGoods", PChar.GenQuest.PGG_Quest.Goods.Text));
		AddQuestUserData("Gen_PGGQuest1", "sColony", sLoc);
		AddQuestUserData("Gen_PGGQuest1", "sShore", GetLocationNameByID(PChar.GenQuest.PGG_Quest.Island.Shore));
		break;

	case "Quest_1_Ship_Detail_1":
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = "Sadece elimizde var "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" onları durdurmak için.";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("In "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" kervan çok uzaklaşacak ve ona yetişemeyeceğiz.","Tam olarak "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" hepsini öldürüp ganimeti almak için günler!"),RandPhraseSimple("Sadece elimizde var "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" operasyonun tamamı için elimizde   gün var.","Acele etmeliyiz, "+PChar.Name+". Sadece elimizde var "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+"."));
			link.l1 = RandPhraseSimple("Bunu zamanında yapacağız! Hadi bugün denize açılalım.","O halde vakit kaybetmeyelim. Bugün yelken açmamız için emri ver.");
			link.l1.go = "Exit_Quest_1_Accept";
			AddQuestRecord("Gen_PGGQuest1", "q1_Accept");
		}
		else
		{
			Dialog.Text = "Bu çok ilginç, lütfen devam edin.";
			link.l1 = "Sadece elimizde var "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" onları durdurmak için.";
			link.l1.go = "Quest_1_Ship_Accept";
			AddQuestRecord("Gen_PGGQuest1", "q1_Accept_1");
		}
		AddQuestUserData("Gen_PGGQuest1", "nDays", FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)));
		break;

	case "Quest_1_Ship_Accept":
		Dialog.Text = "Vakit kaybetmeyelim! Hadi gidelim!";
		link.l1 = "Hadi gidelim!";
		link.l1.go = "Exit_Quest_1_Accept";
		break;

	case "Exit_Quest_1_Accept":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) < 2)
		{
			PChar.GenQuest.PGG_Quest.Stage = 2;
			PGG_Q1RemoveShip("");

			if (sti(PChar.GenQuest.PGG_Quest.Template)) 
			{
				PGG_Q1PlaceShipsNearIsland();
			}
			else
			{
				Locations[FindLocation(PChar.GenQuest.PGG_Quest.Island.Shore)].DisableEncounters = true;

				PChar.Quest.PGGQuest1_CheckStartState.win_condition.l1 = "Location";
				PChar.Quest.PGGQuest1_CheckStartState.win_condition.l1.Location = PChar.GenQuest.PGG_Quest.Island.Shore;
				PChar.Quest.PGGQuest1_CheckStartState.function = "PGG_Q1CheckStartState";
			}
			PChar.Quest.PGGQuest1_PGGDead.win_condition.l1 = "NPC_Death";
			PChar.Quest.PGGQuest1_PGGDead.win_condition.l1.Character = PChar.GenQuest.PGG_Quest.PGGid;
			PChar.Quest.PGGQuest1_PGGDead.function = "PGG_Q1PGGDead";

			SetTimerCondition("PGGQuest1_Time2Late", 0, 0, sti(PChar.GenQuest.PGG_Quest.Days), false);
			PChar.Quest.PGGQuest1_Time2Late.function = "PGG_Q1Time2Late";

			NPChar.PGGAi.IsPGG = false;
			NPChar.PGGAi.location.town = "none";
			DeleteAttribute(NPChar, "PGGAi.Task");
			DeleteAttribute(NPChar, "PGGAi.LockService");
			DeleteAttribute(NPChar, "AlwaysFriend");

			SetCompanionIndex(PChar, -1, sti(NPChar.index));
			SetCharacterRemovable(NPChar, false);
			
			SetBaseShipData(NPChar);
            DeleteAttribute(NPChar,"ship.sails");
			DeleteAttribute(NPChar,"ship.masts");
			DeleteAttribute(NPChar,"ship.blots");
			DeleteAttribute(NPChar,"ship.hulls");
			
			Fantom_SetCannons(NPChar, "pirate");
			Fantom_SetBalls(NPChar, "pirate");
		}
		NextDiag.CurrentNode = "Quest_1_Ship_Accept";
		DialogExit();
		break;

	case "Quest_1_Ship_Refuse":
		Dialog.Text = RandSwear()+"Beni hayal kırıklığına uğrattın, kaptan. Beni davet edeceğimi mi sandın "+RandPhraseSimple("Pazar ayini?!!","çocuk oyunu mu!??"));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Bu senin işin. Ve karar vermek de bana kalmış.","Birkaç peso için ipte sallanacak değilim."),RandPhraseSimple("Kararım kesin, kaptan.","Konuşacak başka bir şeyimiz kalmadı."));
		link.l1.go = "Exit_Quest_1_Refuse";
		break;

	case "Exit_Quest_1_Refuse":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_RemoveShip.function = "PGG_Q1RemoveShip";

			AddQuestRecord("Gen_PGGQuest1", "q1_Close");
			AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Gen_PGGQuest1");
			DeleteAttribute(NPChar, "AlwaysFriend");
		}
		NPChar.Dialog.CurrentNode = "Quest_1_Ship_Refuse";
		NPChar.DeckDialogNode = "Quest_1_Ship_Refuse";
		DialogExit();
		break;

	case "Quest_1_Ship_BadWay":
		Dialog.Text = PCharRepPhrase("Aman, hadi ama! Her şey yolunda gidecek, kimsenin ruhu duymayacak. Herkesi öldüreceğiz."),RandPhraseSimple("Nereye gidiyorsun, kaptan? Yoksa yetkililere mi?","Bir kaplanın inine kolayca çıkabileceğini sanarak girmek hiç akıllıca değil."));
		link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("Deniz şeytanını öp de gel! Ben kaptanım "+GetFullName(PChar)+" ve senin umurunda değilim! Gidiyorum!","Şeytana yemin ederim, beni gerçekten deli ediyorsun!"),RandPhraseSimple("Teklifinizle ilgilenmiyorum ve konuşacak başka bir şeyimiz yok. Hoşça kalın.","Sanırım aramızda konuşacak başka bir şey kalmadı. Üzgünüm, meşgulüm ve gitmem gerekiyor."));
		link.l1.go = "Quest_1_Ship_BadWay_1";
		break;

	case "Quest_1_Ship_BadWay_1":
		Dialog.Text = RandSwear()+PCharRepPhrase(RandPhraseSimple("Ele geçir "+GetSexPhrase("onu","onu")+"! Berabere "+GetSexPhrase("onu","onu")+" topa! Bakalım hangi renk "+GetSexPhrase("onun","onu")+" bağırsakların!!!","Hey! Johnny! Henderson! Şunu kap "+GetSexPhrase("serseri","kız")+"! Sakın izin verme "+GetSexPhrase("onu","onu")+" cankurtaran sandalına ulaşmak için!!!"),RandPhraseSimple("Yazık oldu, kaptan! Yine de umarım ambarımızı beğenirsiniz. Sonra sizinle ne yapacağımıza karar veririz.","Beyaz köleler uzun yaşamaz, kaptan, o yüzden seçimini yap: ya Hends kafana sıkar, ya da hayatının geri kalanını bir taş ocağında geçirirsin."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Sana o pis bağırsaklarını yedireceğim, "+GetFullName(NPChar)+"!!!","Yol verin! Serseriler! Sizi olduğunuz yerde öldürürüm!"),RandPhraseSimple("Teklifin kabul edilemez... Hem de son derece akılsızca!!!"," Pek misafirperver değilsin gördüğüm kadarıyla... Çekil önümden!!! "));
		link.l1.go = "Exit_Quest_1_DeckFight";
		break;

	case "Exit_Quest_1_DeckFight":
        GetCharacterPos(NPChar, &locx, &locy, &locz);
		DeleteAttribute(NPChar, "AlwaysFriend");
        sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		LAi_SetImmortal(NPChar, true);
		LAi_SetActorType(NPChar);
		LAi_ActorRunToLocation(NPChar, "reload", sTmp, "none", "", "", "", 5.0);

		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		//группа может быть занята, а проверок по группам у нас нет... :(
		if (!CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			sTmp = "PGGTmp";
		}
		else
		{
			sTmp = "PGGQst";
		}
		PChar.GenQuest.PGG_Quest.GrpID = sTmp;

		for (i=1; i<5; i++)
		{
			sld = CharacterFromID("saylor_0" + i);
			LAi_group_MoveCharacter(sld, sTmp);
		}
		LAi_group_FightGroups(LAI_GROUP_PLAYER, sTmp, true);
		LAi_group_SetCheck(sTmp, "PGG_Q1AfterDeckFight");
		chrDisableReloadToLocation = true;

		PGG_ChangeRelation2MainCharacter(NPChar, -20);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LAi_SetFightMode(pchar, true);
		break;

	case "Quest_1_Time2Late":
		chrDisableReloadToLocation = false;

		//перенес сюда.. х.з. вроде будет лучше (Баг Изгоя.)
		PChar.Quest.PGGQuest1_PGGDead.Over = "Yes";
		PChar.Quest.PGGQuest1_GroupDead.Over = "Yes";
		PChar.Quest.PGGQuest1_CheckStartState.Over = "Yes";

//		Dialog.Text = "Yani, "+GetFullName(PChar)+", seninle uğraşarak hata yaptığımı anladım. Şimdi bize ganimet yok. Elveda!";
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("Lanet olsun! Geç kaldık – hepsi o tembel aptallar yüzünden! Şimdi seninle paylaşacak ganimet de kalmadı, "+GetFullName(PChar)+". Flok yelkenini kaldırın! Buradan gidiyoruz! ","Yani, "+GetFullName(PChar)+", seninle uğraşmakla hata yaptığımı şimdi anladım. Artık bize ganimet yok. Elveda!"),RandPhraseSimple("Onlar kayboldu – ve hepsi senin gecikmen yüzünden! Şimdi yollarımız ayrılıyor, "+GetFullName(PChar)+".","Artık kervana yetişmemiz imkânsız. Seninle uğraşmakla hata ettim. Elveda!"))link.l1 = PCharRepPhrase(RandPhraseSimple("O kervan da neymiş! İstiridye dalgıçları daha iyi, hem hiç risk yok!","Şans bizden yana ve yarın yeni bir gün! Denizlerde, paramızı almamızı bekleyen bir sürü zavallı tüccar var!"),RandPhraseSimple("Ne yazık ki, böylesine parlak bir operasyon tam bir fiyasko ile sonuçlandı! Elveda!","İnsan plan yapar, Tanrı ise karar verir... Elveda!"));
		link.l1.go = "Exit_Quest_1_2Late";

		AddQuestRecord("Gen_PGGQuest1", "q1_Time2Late");
		CloseQuestHeader("Gen_PGGQuest1");
		break;

	case "Exit_Quest_1_2Late":
        LAi_SetPlayerType(PChar);
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			RemoveCharacterCompanion(pchar, NPChar);

			NPChar.PGGAi.IsPGG = true;
			NPChar.RebirthPhantom = true;

			LAi_SetWarriorTypeNoGroup(NPChar);
			LAi_group_MoveCharacter(NPChar, "GroupDeck");

			PChar.Quest.PGGQuest1_Clear.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_Clear.win_condition.l1.Location = PChar.location;
			if (PChar.location == "Ship_deck")
			{
/*				PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1 = "ExitFromSea";
				PChar.Quest.PGGQuest1_RemoveShip.function = "PGG_Q1RemoveShip";
				PChar.Quest.PGGQuest1_Clear.win_condition.l1 = "ExitFromSea";
*/				PChar.quest.Munity = "Deads";
			}
			PChar.Quest.PGGQuest1_Clear.function = "PGG_Q1EndClear";
		}
		NextDiag.CurrentNode = "Quest_1_Failed";
		DialogExit();
		break;

	case "Quest_1_CheckResult":
		if (PChar.location == PChar.GenQuest.PGG_Quest.Island.Shore)
		{
			Locations[FindLocation(PChar.GenQuest.PGG_Quest.Island.Shore)].DisableEncounters = false;
		}
		else
		{
			PChar.quest.Munity = "Deads";
		}
		chrDisableReloadToLocation = false;

		//не взяли груз...
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			PChar.GenQuest.PGG_Quest.FailedPaySum = sti(PChar.GenQuest.PGG_Quest.Days)*10000;
//			Dialog.Text = "Ah, ben neden seninle uğraştım ki. Her şeyi mahvettin. Şimdi bana bir ceza ödemek zorundasın "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+".";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("Kan dökücü "+GetSexPhrase("alçak","pislik")+"! Her şey deniz şeytanının dibine gitti!"+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+" parayı peşin ver, sonra da gözümün önünden kaybol!","Kendini Amiral Nelson mı sandın? Tüm ganimeti batırdın, "+GetSexPhrase("aptal","akılsız kadın")+" ! Şimdi ver onu bana "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+" peso ver git başımdan!"),RandPhraseSimple("Burada savaş çıkarmaya mı karar verdiniz! Bu kesinlikle kabul edilemez! Ama sanırım, bize ödeme yaparsanız bunu unutabiliriz "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+" pesos.","Yöntemleriniz tamamen kabul edilemez! Her şeyi mahvettiniz! Hemen payımızı ödeyin, miktarı ise "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+" peso al ve istediğin yere git!"));
			link.l1 = PCharRepPhrase(RandPhraseSimple("Ben olmasaydım, şimdiye kadar yengeçlere yem olmuştun, açgözlü herif!","Ah evet, amiral gemilerinin seni ele geçirmesine izin vermeliydim – o zaman şimdi havayı zehirlemez, serenlerden sallanıyor olurdun!"),RandPhraseSimple("Talepleriniz yersiz, imalarınız ise hakaret niteliğinde!","Ceza konusunda anlaşmadık, bu yüzden sana hiçbir şey ödemiyorum!"));
			link.l1.go = "Quest_1_NotPay";
			if (sti(pchar.money) >= sti(PChar.GenQuest.PGG_Quest.FailedPaySum))
			{
				link.l2 = PCharRepPhrase(RandPhraseSimple("Şu anda seninle savaşamam, bunu sen de biliyorsun! Paralarına tıkanıp kal!"," pesos?!! Bugün şans benden yana değil galiba. Kabul ediyorum."),RandPhraseSimple("İsteklerin çok fazla, ama sanırım başka seçeneğim yok.","İsteklerin çok fazla, ama kabul etmeliyim!"));
				link.l2.go = "Exit_Quest_1_Failed";
			}
		}
		else
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			Dialog.Text = "Ah, ben neden seninle uğraştım ki. Her şeyi mahvettin.";
			link.l1 = "Aman, hadi ama! Sen de gördün, başka bir yol yoktu.";
			link.l1.go = "Exit_Quest_1_Failed";
		}

		//минимум треть если взял, то гуд!
		if (sti(PChar.GenQuest.PGG_Quest.Goods.Taken) > MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Qty)/3))
		{
			PChar.GenQuest.PGG_Quest.Ok = 1;
//			Dialog.Text = "Yani, ganimetimiz toplamda "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+". Hadi ayrılalım.";
			Dialog.Text = PCharRepPhrase("Bu harika bir anlaşmaydı! Yani, ganimetimiz toplamda "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+".","Harika iş çıkardınız, kaptan! Ganimetimiz şunu oluşturuyor "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+".");
			i = sti(PChar.GenQuest.PGG_Quest.Parts);
			PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
			if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
			{
				Dialog.Text = Dialog.Text+PCharRepPhrase(" Payıma düşen "," Gemimin payı - ");
			}
			else
			{
				Dialog.Text = Dialog.Text+" Payın   ";
			}
			Dialog.Text = Dialog.Text+PChar.GenQuest.PGG_Quest.Goods.Part+".";
			link.l1 = PCharRepPhrase(RandPhraseSimple("Her şey doğru! Sandallar zaten yükleniyor!","Evet, her şey doğru. Anlaşma, anlaşmadır."),RandPhraseSimple("Hesapların doğru. Katılıyorum.","Bölüşme konusunda sana diyecek hiçbir şey yok."));
			link.l1.go = "Exit_Quest_1_End";
			link.l2 = PCharRepPhrase(RandPhraseSimple("Hakkını istemeye nasıl cüret edersin? Derhal seren direğine asılmalısın!","Payını mı istiyorsun? Burada herkes kendi başının çaresine bakar. Sana bir şey kalmadıysa, bu senin sorunun!"),RandPhraseSimple("Hiçbir pay bekleyebileceğini sanmıyorum.","Cevabım hayır! Senin gibi alçaklarla paylaşmam!"));
			link.l2.go = "Quest_1_NotPay";
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Fail");
		}
		break;

	case "Quest_1_NotPay":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("Peki, tamam o zaman, tartışmayacağım! Hoşça kal!","Kan dökmeyelim, işleri daha da kötüleştirmeyelim! Bir dahaki sefere şansımız daha iyi olacak!"),RandPhraseSimple("Pekâlâ, elveda kaptan, talepte bulunacak durumda değilim...","Gemilerimdeki kayıplar ve hasar, adil bir karar için ısrar etmeme engel oluyor. Bunu sizin vicdanınıza bırakıyorum, kaptan!"));
		link.l1 = PCharRepPhrase(RandPhraseSimple("Sana rüzgarlar hep arkandan essin!","Kıç altında yedi ayak!"),RandPhraseSimple("Elveda! Umarım taze deniz havası sana iyi gelir!","Umarım talihsizliklerimiz sizi daha da çekilmez yapmaz, kaptan! Hoşça kalın!"));
		link.l1.go = "Exit_Quest_1_Failed";
		PChar.GenQuest.PGG_Quest.Stage = -1;

		bOk = makeint(NPChar.reputation) < 41 && PGG_ChangeRelation2MainCharacter(NPChar, 0) < 75;
		if (bOk || CheckAttribute(PChar, "GenQuest.PGG_Quest.Ok"))
		{
			PChar.GenQuest.PGG_Quest.Stage = 4;
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("Anlamadın mı! Hayatını satın alabilirdin! Yakalayın şu alçağı!","Yoksa bizimle oyun oynadığımızı mı sanıyorsun? Seni omurgadan geçirdiğimizde daha uysal olursun herhalde!"),RandPhraseSimple("O zaman ömrünü kısaltmamız gerekecek, kaptan! Dostça gitmeyeceksen, yakında Aziz Martin'le tanışırsın!","Bana başka seçenek bırakmıyorsun, "+GetFullName(PChar)+"! İster beğen ister beğenme, hakkım olanı alacağım!"));
			link.l1 = PCharRepPhrase(RandPhraseSimple("Şeytana yemin ederim, bunun bedelini ödeyeceksin!!!","Yo-ho! O zaman git ve beni bul, Kaptan "+GetFullName(PChar)+"! "),RandPhraseSimple("Kesik uzun ve derin olacak!","Çabucak mı ölmek istersin, yoksa biraz acı çekerek mi?"));
			link.l1.go = "Exit_Quest_1_FailedFight";
		}
		break;

	case "Exit_Quest_1_Failed":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			AddMoneyToCharacter(PChar, -(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)));
			AddQuestRecord("Gen_PGGQuest1", "q1_FailPay");
		AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("",""));
		AddQuestUserData("Gen_PGGQuest1", "sSex1", GetSexPhrase("",""));
		}
		CloseQuestHeader("Gen_PGGQuest1");
		RemoveCharacterCompanion(pchar, NPChar);

		if (PChar.Location == "Ship_deck")
		{
			PChar.Quest.PGGQuest1_FailedExitSea.win_condition.l1 = "ExitFromSea";
			PChar.Quest.PGGQuest1_FailedExitSea.function = "PGG_Q1EndClear";
		}
		else
		{
			PChar.Quest.PGGQuest1_FailedExitLoc.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_FailedExitLoc.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_FailedExitLoc.function = "PGG_Q1EndClear";
		}
		PGG_ChangeRelation2MainCharacter(NPChar, -5);

		LAi_SetImmortal(NPChar, true);
		//что б не били сопровождение.
		for (i = 1; i < sti(PChar.GenQuest.PGG_Quest.GrpID.Qty); i++)
		{
			sld = CharacterFromID("pirate_" + i);
			LAi_SetImmortal(sld, true);
		}

		NextDiag.CurrentNode = "Quest_1_Failed";
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;

	case "Quest_1_Failed":
		Dialog.Text = "Artık seninle uğraşmak istemiyorum!";
		link.l1 = "Hiç sorun değil.";
		link.l1.go = "Exit";
		NextDiag.TempNode = "Quest_1_Failed";
		break;

	case "Quest_1_End":
		Dialog.Text = "Sizinle iş yapmak güzeldi. Bol şans.";
		link.l1 = "Sana da aynısı.";
		link.l1.go = "Exit";
		NextDiag.TempNode = "Quest_1_End";
		break;

	case "Exit_Quest_1_FailedFight":
		RemoveCharacterCompanion(pchar, NPChar);

		LAi_LockFightMode(pchar, false);
		LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
		LAi_group_SetRelation("PGGTmp", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);	
		LAi_group_FightGroups(LAI_GROUP_PLAYER, "PGGTmp", true);
		LAi_group_SetCheck("PGGTmp", "PGG_Q1AfterDeckFight");
	
		PChar.GenQuest.PGG_Quest.GrpID = "PGGTmp";
		chrDisableReloadToLocation = true;

		Group_AddCharacter("PGGQuest", NPChar.id);
		Group_SetGroupCommander("PGGQuest", NPChar.id);
		Group_SetAddress("PGGQuest", PChar.GenQuest.PGG_Quest.GrpLocation, "Quest_Ships", PChar.GenQuest.PGG_Quest.GrpLoc);
		Group_SetTaskNone("PGGQuest");

		PGG_ChangeRelation2MainCharacter(NPChar, -15);

		GetCharacterPos(NPChar, &locx, &locy, &locz);
        sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		NextDiag.CurrentNode = "Second Time";
		DialogExit();

		Log_TestInfo("go to loc " + sTmp + " " + NPChar.location);
		NPChar.location = PChar.location;
		if (PChar.location != "Ship_Deck") sTmp = "reload1_back";

		PChar.questTemp.Chr2Remove = NPChar.id;
		LAi_ActorRunToLocator(NPChar, "reload", sTmp, "RemoveCharacterFromLocation", 5.0);

		LAi_SetImmortal(NPChar, true);
		LAi_SetFightMode(pchar, true);
		break;

	case "Exit_Quest_1_End":
		RemoveCharacterCompanion(PChar, NPChar);

		i = sti(PChar.GenQuest.PGG_Quest.Goods.Part);
/*		i *= (sti(PChar.GenQuest.PGG_Quest.Parts)-1);
		i += sti(PChar.GenQuest.PGG_Quest.StartGoods);
		n = GetCompanionQuantity(PChar);
		SetCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), i);
		for (i = 1; i < n; i++)
		{
			iRnd = GetCompanionIndex(PChar, i);
			if (iRnd != -1)
			{
				sld = GetCharacter(iRnd);
				if (GetRemovable(sld))
				{
					Log_TestInfo("" + sld.id);
					SetCharacterGoods(sld, sti(PChar.GenQuest.PGG_Quest.Goods), 0);
				}
			}
		}
*/
		RemoveCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), i);
/*		if (PChar.Location == "Ship_deck")
		{
			PChar.Quest.PGGQuest1_EndExitSea.win_condition.l1 = "ExitFromSea";
			PChar.Quest.PGGQuest1_EndExitSea.function = "PGG_Q1EndClear";
		}
		else
		{*/
			PChar.Quest.PGGQuest1_EndExitLoc.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_EndExitLoc.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_EndExitLoc.function = "PGG_Q1EndClear";
		//}
		AddQuestRecord("Gen_PGGQuest1", "q1_OkShare");
		CloseQuestHeader("Gen_PGGQuest1");

		//что б не били сопровождение.
		for (i = 1; i < sti(PChar.GenQuest.PGG_Quest.GrpID.Qty); i++)
		{
			sld = CharacterFromID("pirate_" + i);
			LAi_SetImmortal(sld, true);
		}

		LAi_SetImmortal(NPChar, true);
		NextDiag.CurrentNode = "Quest_1_End";
		DialogExit();
  		LAi_SetWarriorType(NPChar); // сброс группы ГГ
		LAi_group_MoveCharacter(NPChar, LAI_GROUP_PLAYER);
		break;

	case "Quest_1_SharePrise":
		chrDisableReloadToLocation = false;
		Dialog.Text = PCharRepPhrase("Gerçekten tam bir katliamdı! Keşke aralarında birkaç kadın da olsaydı! Neyse ki ganimet buna değdi  "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+".","Fena değil, kaptan! Ganimet telafi ediyor "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+".");

		i = sti(PChar.GenQuest.PGG_Quest.Parts);
		PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
        SetCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), sti(PChar.GenQuest.PGG_Quest.Goods.Taken) + GetCargoGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods)));
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			Dialog.Text = Dialog.Text+" Payıma düşen ";
		}
		else
		{
			Dialog.Text = Dialog.Text+" Payın bu ";
		}
		Dialog.Text = Dialog.Text+PChar.GenQuest.PGG_Quest.Goods.Part+".";
		link.l1 = PCharRepPhrase(RandPhraseSimple("Tamamen adil, kahretsin!","Her şey gayet yolunda, kahretsin!"),RandPhraseSimple("Hesapların doğru. Katılıyorum.","Bölüşme konusunda üstüne yok."));
		link.l1.go = "Exit_Quest_1_End";
		break;
//===================================
//              Exits 
//===================================
	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;
		
	case "Exit_2":
		if (CheckAttribute(pchar, "GenQuest.PGG_Quest")) DeleteAttribute(pchar, "GenQuest.PGG_Quest"); //fix
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;		

	case "Exit_Smugglers_Fight":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();

		LAi_group_FightGroups(LAI_GROUP_PLAYER, "PGGTmp", true);
		LAi_SetFightMode(pchar, true);
		break;

	case "Exit_ShowParam":
		NextDiag.CurrentNode = "Second Time";
//		NPChar.quest.meeting = true;
		DialogExit();

		PChar.SystemInfo.OnlyShowCharacter = true;
		LaunchCharacter(NPChar);
		break;
	}
}
/* TEMPLATE
		Dialog.Text = "";
		link.l1 = "";
		link.l1.go = "";
		link.l2 = "";
		link.l2.go = "";
		link.l3 = "";
		link.l3.go = "";
*/
