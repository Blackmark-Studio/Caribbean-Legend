// заместитель Маркуса Тиракса в Ла Веге
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ------------------------------------------блок angry-----------------------------------------------
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    }
// ------------------------------------------блок angry-----------------------------------------------

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            dialog.text = NPCStringReactionRepeat("Bana söyleyecek bir şeyin var mı? Yok mu? O zaman defol buradan!","Bence kendimi yeterince açık ifade ettim, beni daha fazla rahatsız etmeyin.","Ne kadar açık konuşsam da, beni rahatsız etmeye devam ediyorsun!","Doğrusu, bu kabalıktan bıkmaya başladım.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ben zaten gidiyorum.","Elbette"+npchar.name+"...","Üzgünüm, "+npchar.name+"...","Oops...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+",   sizi görmekten memnun oldum!   Ne istiyorsunuz?","Başka ne var?"," Yine sen mi? Yapacak bir işin yoksa insanları rahatsız etme!","Sizin dürüst bir adam olduğunuzu biliyorum. Ama artık sizinle konuşmak istemiyorum.","repeat",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Hiçbir şey. Sadece sizi görmek istedim.","Hiçbir şey...","Pekâlâ, "+npchar.name+", üzgünüm...","Lanet olsun, hepsi benim suçum...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Hırsızlık mı?! Ciddi misiniz?! Senin işin bitti, dostum...","Ne yani, bu da ne? Meğer hırsızmışsın! İşin bitti...");
			link.l1 = LinkRandPhrase("Kahretsin!","Caramba!!","Lanet olsun!!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+GetSexPhrase("Defol","Çekil git ")+" buradan!","Evimden defol!");
			link.l1 = "Oops...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Beni ucuz laflarınla oyalama. Bir dahaki sefere sonucu hiç beğenmeyeceksin...";
        			link.l1 = "Anladım.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = "Bitti, konuşmak yok.";
			link.l1 = RandPhraseSimple("Nasıl isterseniz...","Pekâlâ o zaman...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Bana daha fazla saygı göstereceğinizi ve kaba davranmayı bırakacağınızı umuyorum. Aksi takdirde, sizi öldürmek zorunda kalırım. Bu hiç hoş olmaz.";
        			link.l1 = ""+npchar.name+", emin olabilirsin, yapacağım.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Lavega_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		
		// Rebbebion, квест "Путеводная звезда"
		case "PZ_1":
			dialog.text = "Ah, demek sensin, de Maure. Ne sürpriz ama. Deniz şeytanı adına, gelişin uzun zamandır başımıza gelen en ilginç şey, kahretsin.";
			link.l1 = "Seni görmek de güzel, Vensan. Köyü yönetmekten keyif alıyor musun?";
			link.l1.go = "PZ_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_2":
			dialog.text = "Nasıl yapabilirim ki? Ben bir kaptanım, hem de lanet olası iyi bir kaptan, öyle sıradan bir muhasebeci değilim. Ve Marcus'un habercilerinin beni yeni bir sefere çağırmasını Noel'i beklediğimden bile daha uzun süredir bekliyorum, kahrolası lanetler!";
			link.l1 = "Noel ve lanetler aynı cümlede, bu gerçekten ilginç. Sana gıpta etmiyorum doğrusu. Yine de, birçok kişi senin yerinde olmak isterdi. Ama ben buraya iş için geldim, Vensan.";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "İş mi?! O halde söyle bakalım - bir şey mi düşündün? İyi bir ipucu buldun mu? Şu lanet hesaplamalardan sıkıntıdan yerel mahzenin dibini göreceğim neredeyse.";
			link.l1 = "Aslında, size bir sorum var, hepsi bu.";
			link.l1.go = "PZ_4";
		break;
		
		case "PZ_4":
			dialog.text = "Kahretsin! Peki, dinliyorum, Charles.";
			link.l1 = "Sizi görmeye bir kadın geldi mi? Ya da belki onu La Vega'da gördünüz mü? Belle Étoile adını kullanıyor, ama bu sadece bir takma ad, kendini başka bir isimle de tanıtmış olabilir. Önemli olan şu ki... teni sarı. Ama bir köle ya da işçi değil - zengin bir kadın.";
			link.l1.go = "PZ_5";
		break;
		
		case "PZ_5":
			dialog.text = "Sarısımsı tenli ama zengin mi? Burada hiç öyle birini görmedik, hiç! Demek hâlâ o ilginç hayatını sürdürüyorsun, de Maure! Neredeyse kıskanacağım.";
			link.l1 = "Öyle mi... Peki, zamanını ayırdığın için teşekkürler, Vensan. Muhasebenden daha fazla alıkoymayayım seni, heh-heh.";
			link.l1.go = "Exit";
			
			AddQuestRecord("PZ", "40");
			
			pchar.quest.PZ_SetHeavyFrigate.win_condition.l1 = "location";
			pchar.quest.PZ_SetHeavyFrigate.win_condition.l1.location = "Hispaniola1";
			pchar.quest.PZ_SetHeavyFrigate.win_condition = "PZ_SetHeavyFrigate";
			DelMapQuestMarkCity("LaVega");
			AddMapQuestMarkCity("PortPax", false);
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", true);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", true);
		break;
	}
}
