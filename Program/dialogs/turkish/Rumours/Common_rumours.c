// Слухи - диалог по типажам

#define MAX_RUMOURS_ABOUT_OWNERS 7

void ProcessCommonDialogRumors(ref NPChar, aref Link, aref NextDiag);
{
    string strum;
    string srum;
	bool bOk1, bOk2;
	switch(Dialog.CurrentNode)
	{
/////////////////////////////////////////////////---слухи мещанок---////////////////////////////////////////////
		case "rumours_towngirl":	
		NextDiag.CurrentNode = "rumours";
		
		//--> Тёмные воды исцеления
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		if (bOk1 || bOk2)
        {
			dialog.text = "Duymuş muydun? Diyorlar ki Thomas Morrison'ın kızı altı aydır yatakta. Doktorlar hastalığına karşı tamamen çaresiz kalmış. Ona yardım edebilecek tek kişi, ölüm döşeğindekileri bile iyileştiren iksirleriyle tanınan çingene kadın. Ama zavallı kız için hiçbir şey yapmayı kesin bir dille reddetmiş.";
			link.l1 = "Teşekkür ederim, şimdi gitmeliyim.";
			link.l1.go = "exit";
			DWH_Start();
			break;
        }
		//<-- Тёмные воды исцеления
		//--> Грани справедливости
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "İki gün önce, Liman Şefi'nin hayatına cüretkâr bir saldırı yapıldı! Sözde suikastçı, ofisinin kapısında pusuya yatmış, ama Şef yardım için bağırmayı başarmış. Bir tüfekçi hızla yetişip herifi yaralamış, ama o alçak şehir kapılarından kaçıp kurtulmuş\nSöylentiye göre Liman Şefi, o herifin kafası için yüklü bir ödül vaat ediyormuş! Şimdiye kadar, bu işe cesaret eden kimse çıkmamış.";
			link.l1 = "Teşekkür ederim, artık gitmeliyim.";
			link.l1.go = "exit";
			GS_Start();
			break;
        }
		//<-- Грани справедливости
		//--> Торговля по закону
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		if (bOk1 || bOk2)
        {
			dialog.text = "Haberi duydun mu?! Bu tam bir rezalet! Meyhanede bir damla rom ya da şarap kalmamış - bu lanet sıcakta insan nasıl ferahlayacak? Bir haftadır meyhaneci içki yine gelecek diye bizi oyalıyor, ama ortada hiçbir şey yok! Kıyamete kadar boğazımızı kurutmaya mı mahkumuz yani?";
			link.l1 = "Teşekkür ederim, artık gitmeliyim.";
			link.l1.go = "exit";
			TPZ_Start();
			break;
        }
		//<-- Торговля по закону
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
		{
			dialog.text = "Liman civarında konuşulanlara göre, valinin yeğeni Julie d'Armagnac, eski neşesinden eser kalmamış. Bir zamanlar capcanlı ve ışıl ışıl olan o kız, şimdi sokaklarda yüzünde silinmez bir hüzünle dolaşıyor. Kasaba halkı fısıldaşıp başına ne geldiğini merak ediyor ama kimse gerçeği bilmiyor. Belki de bir alçak onun kalbini kırmıştır?"+GetSexPhrase(" Belki de sendin, kaptan?","")+"";
			link.l1 = ""+GetSexPhrase("Sanmam ","")+". Teşekkür ederim, şimdi gitmem gerek.";
			link.l1.go = "exit";
			UV_Start();
			break;
        }
		//<-- Украденное воспоминание
		//--> В плену великого улова andre39966
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		if (bOk1 || bOk2)
        {
			dialog.text = "Rivayet odur ki, balıkçı Pierre Carno izini kaybettirmiş. İki sabah önce denize açılmış, o günden beri ondan eser yok. Karısı Lea, kederden perişan halde. Gündüz de gece de iskelede nöbet tutuyor, gözleri ufukta, sevgilisinin yelkenini görebilmek için dua ediyor.";
			link.l1 = "Teşekkür ederim, artık gitmeliyim.";
			link.l1.go = "exit";
			VPVL_Start();
			break;
        }
		//<-- В плену великого улова 
		//--> Тайна Бетси Прайс
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		if (bOk1 || bOk2)
        {
			dialog.text = "Kaptan, duydun mu? Bizim meyhanede yeni bir garson kız çalışıyor. Söylentilere göre çok güzelmiş. Her yerden adamlar sırf onu bir kez görmek için akın akın geliyor. Ama üç gün önce işe gelmemiş, bu da meyhaneciyi çok üzmüş; kız geldiğinden beri kazancı katlanmıştı. Duyduğuma göre, şimdi kızı bulana iyi bir ödül vermeye bile razıymış.​";
			link.l1 = "Teşekkür ederim, şimdi gitmeliyim.";
			link.l1.go = "exit";
			TBP_Start();
			break;
        }
		//<-- Тайна Бетси Прайс
		//--> Оковы азарта
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.OZ_Start") && npchar.city == "PortSpein" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.OZ_Start") && npchar.city == "PortSpein";
		if (bOk1 || bOk2)
        {
			dialog.text = "Duymadın mı? Demircimiz kartlarda Javier Castillo'ya öyle fena kaybetmiş ki, adam onu soyup soğana çevirmiş, çok değerli bir şeyi ortaya koymaya zorlamış. O günden beri demirci kendine gelemedi, yeni sipariş de almıyor – sürekli amiralin onu canlı canlı yüzmesinden korkup duruyor. Zavallı ahmak, burada herkes bilir ki o üçkağıtçı Castillo'yla oyun oynanmaz!";
			link.l1 = "Teşekkürler, şimdi gitmem gerek.";
			link.l1.go = "exit";
			OZ_Start();
			break;
        }
		//<-- Оковы азарта
		//--> Письмо от покойника
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.LFD_Start") && npchar.city == "PortoBello";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.LFD_Start") && npchar.city == "PortoBello";
		if (bOk1 || bOk2)
        {
			dialog.text = "Duymuş muydun? 'Águila' adlı flütün kaptanı, tavernada çavuşunu öyle bir azarlamış ki, duvarlar titremiş! Meğerse kaptan, gelgitle birlikte denize açılmayı planlıyormuş, ama çavuş bütün tayfayı karaya salıvermiş. Şimdi denizciler şehre dağılmış, zamanında dönmezlerse gemi onları bırakıp gidecekmiş – kaptan beklemeye hiç niyetli değil! Merak ediyorum, bu acele ne için? Kârlı bir yük mü, iyi bir ticaret mi, yoksa valinin acil bir işi mi var?";
			link.l1 = "Teşekkürler, şimdi gitmeliyim"+GetSexPhrase("","")+".";
			link.l1.go = "exit";
			LFD_Start();
			break;
        }
		//<-- Письмо от покойника
		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2 )
        srum = SelectRumourEx("towngirl", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        string posrep1, posrep2, answ1, answ2, answ3, answ4;
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" That's it...", " You might find it interesting.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "That's very interesting, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Interesting! There is one more question I want to ask...","One more question.");
            answ3 = RandPhraseSimple("Well, anything can happen. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. Maybe " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I've got anything of interest to tell you.","It will be a pleasure for me, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,srum+posrep1,srum+posrep2,RandPhraseSimple("Ne yazık ki, sana anlatacak başka bir şeyim yok, izin ver geçeyim.","Senin sorularından bıktım, affedersin, ilgilenmem gereken başka işlerim var."),"block",1,npchar,Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,answ2,answ3,answ4,npchar,Dialog.CurrentNode);
		link.l1.go = "new question";
		link.l2 = RandPhraseSimple("Teşekkürler, gitmeliyim.","Elveda.");
		link.l2.go = "exit";
	break;

/////////////////////////////////////////////////---слухи мещан---////////////////////////////////////////////
	case "rumours_townman":	
		NextDiag.CurrentNode = "rumours";
		
		//--> Тёмные воды исцеления
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		if (bOk1 || bOk2)
        {
			dialog.text = "Duymuş muydun? Diyorlar ki Thomas Morrison'ın kızı altı aydır yatakta. Doktorlar hastalığına karşı tamamen çaresiz kalmış. Ona yardım edebilecek tek kişi, ölüm döşeğindekileri bile iyileştiren iksirleriyle bilinen çingene kadınmış. Ama zavallı kız için hiçbir şey yapmayı kesinlikle reddetmiş.";
			link.l1 = "Teşekkür ederim, şimdi gitmem gerek.";
			link.l1.go = "exit";
			DWH_Start();
			break;
        }
		//<-- Тёмные воды исцеления
		//--> Грани справедливости
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "İki gün önce, Liman Şefi'nin hayatına cüretkâr bir saldırı yapıldı! Sözde suikastçı, ofisinin kapısında pusuya yatmış, ama Şef yardım için bağırmayı başarmış. Bir tüfekçi hızla yetişip alçağı yaralamış, fakat o herif şehir kapılarından kaçmayı başarmış.\nDuyduğuma göre Liman Şefi, o haydudun kellesi için yüklü bir ödül vaat ediyormuş! Şimdiye kadar, buna cesaret eden çıkmamış. Düşünsene, bin doblon için bile... ben başımı böyle bir işe sokmam...";
			link.l1 = "Teşekkür ederim, şimdi gitmem gerek.";
			link.l1.go = "exit";
			GS_Start();
			break;
        }
		//<-- Грани справедливости
		
		//--> Торговля по закону
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		if (bOk1 || bOk2)
        {
			dialog.text = "Haberi duydun mu?! Tam bir rezalet! Meyhanede bir damla rom ya da şarap kalmamış - bu lanet sıcakta insan nasıl ferahlayacak? Bir haftadır meyhaneci içki tekrar gelecek diye bizi oyalıyor, ama ortada hiçbir şey yok! Kıyamete kadar boğazımız kurusun mu istiyorlar?";
			link.l1 = "Teşekkür ederim, şimdi gitmem gerek.";
			link.l1.go = "exit";
			TPZ_Start();
			break;
        }
		//<-- Торговля по закону
		
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
        {
			dialog.text = "Liman civarında konuşulanlara göre, vali'nin yeğeni Julie d'Armagnac eskisi gibi değilmiş. Bir zamanlar capcanlı ve hayat doluyken, şimdi sokaklarda yüzünde silinmez bir hüzünle dolaşıyormuş. Kasaba halkı fısıldaşıp başına ne geldiğini merak ediyor ama gerçeği bilen yok. Belki de bir alçak onun kalbini kırmıştır?"+GetSexPhrase(" Belki de sendin, Kaptan?","")+"";
			link.l1 = ""+GetSexPhrase("Sanmam ","")+". Teşekkür ederim, şimdi gitmeliyim.";
			link.l1.go = "exit";
			UV_Start();
			break;
        }
		//<-- Украденное воспоминание
		
		//--> В плену великого улова andre39966
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		if (bOk1 || bOk2)
        {
			dialog.text = "Bir söylentiye göre balıkçı Pierre Carno hiçbir iz bırakmadan ortadan kaybolmuş. İki sabah önce denize açılmış, o zamandan beri ondan tek bir haber yok. Karısı Lea, üzüntüden perişan halde. Gündüz de gece de iskelede bekleyip duruyor, gözleri ufukta, sevgilisinin yelkenini görebilmek için dua ediyor.";
			link.l1 = "Teşekkür ederim, şimdi gitmem gerek.";
			link.l1.go = "exit";
			VPVL_Start();
			break;
        }
		//<-- В плену великого улова 
		//--> Тайна Бетси Прайс
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		if (bOk1 || bOk2)
        {
			dialog.text = "Kaptan, duydun mu? Meyhanemizde yeni bir garson kız çalışmaya başlamış. Duyduğuma göre çok güzelmiş. Her yerden adamlar sırf onu bir kez görebilmek için akın akın geliyormuş. Ama üç gün önce işe gelmemiş, bu da meyhaneciyi çok üzmüş; kız geldiğinden beri kasasını dolduruyordu çünkü. Söylentiye göre, kızı bulana iyi bir ödül verecekmiş.";
			link.l1 = "Teşekkür ederim, artık gitmeliyim.";
			link.l1.go = "exit";
			TBP_Start();
			break;
        }
		//<-- Тайна Бетси Прайс
		//--> Оковы азарта
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.OZ_Start") && npchar.city == "PortSpein" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.OZ_Start") && npchar.city == "PortSpein";
		if (bOk1 || bOk2)
        {
			dialog.text = "Duymadın mı? Demircimiz, Javier Castillo'ya kart oyununda öyle fena kaybetmiş ki, adam onu soyup soğana çevirmiş, sonunda çok değerli bir şeyini ortaya koymaya zorlamış. O günden beri demirci kendine gelemedi, yeni sipariş de almıyor – sadece amiralin onu canlı canlı yüzmesinden korkup duruyor. Zavallı ahmak, burada herkes bilir ki o hilebaz Castillo'yla oyun oynanmaz!";
			link.l1 = "Teşekkürler, şimdi gitmeliyim.";
			link.l1.go = "exit";
			OZ_Start();
			break;
        }
		//<-- Оковы азарта
		//--> Письмо от покойника
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.LFD_Start") && npchar.city == "PortoBello";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.LFD_Start") && npchar.city == "PortoBello";
		if (bOk1 || bOk2)
        {
			dialog.text = "Duymuş muydun? 'Águila' adlı flütün kaptanı, tavernada çavuşuna öyle bir fırça çekmiş ki, duvarlar titremiş! Meğerse kaptan, gelgitle birlikte denize açılmayı planlıyormuş, ama çavuş bütün tayfayı karaya salıvermiş. Şimdi denizciler şehre dağılmış, zamanında dönmezlerse gemi onları bırakıp gidecekmiş – kaptan beklemeye hiç niyetli değilmiş! Merak ediyorum, bu acele neden? Kârlı bir yük mü, iyi bir ticaret mi, yoksa valinin acil bir işi mi var?";
			link.l1 = "Teşekkürler, artık gitmeliyim"+GetSexPhrase("","")+".";
			link.l1.go = "exit";
			LFD_Start();
			break;
        }
		//<-- Письмо от покойника
		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2 )
        srum = SelectRumourEx("townman", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" That's it...", " You might find it interesting.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "That's very interesting, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Interesting! There is one more question I want to ask...","One more question.");
            answ3 = RandPhraseSimple("Well, everything can happen in our world. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. Maybe " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I've got anything of interest to tell you.","It will be a pleasure for me, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,srum+posrep1,srum+posrep2,RandPhraseSimple("Ne yazık ki, anlatacak başka bir şeyim yok, izin ver geçeyim.","Senin sorularından bıktım, affedersin, ilgilenmem gereken başka işlerim var."),"block",1,npchar,Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,answ2,answ3,answ4,npchar,Dialog.CurrentNode);
		link.l1.go = "new question";
		link.l2 = RandPhraseSimple("Sağ ol, gitmeliyim.","Elveda.");
		link.l2.go = "exit";
	break;
	
	///////////////////////////////////---слухи тёмных личностей---////////////////////////////////////////////
	case "rumours_marginal":	
		NextDiag.CurrentNode = "rumours";

		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2 )
        srum = SelectRumourEx("townman", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" That's it...", " You might find it interesting.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "That's very interesting, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("Well, everything can happen in our world. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. Maybe " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I've got anything of interest to tell you.","It will be a pleasure for me, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,srum+posrep1,srum+posrep2,RandPhraseSimple("Ne yazık ki, sana anlatacak başka bir şeyim yok, müsaade et geçeyim.","Sorularından bıktım, affedersin, ilgilenmem gereken başka işlerim var."),"block",1,npchar,Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,answ2,answ3,answ4,npchar,Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Teşekkürler, gitmeliyim.","Elveda.");
		link.l2.go = "exit";
	break;
	
/////////////////////////////////////////////////---слухи дворян---////////////////////////////////////////////
	case "rumours_nobleman":	
        srum = SelectRumourEx("nobleman", NPChar);
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
			if (bOk1 || bOk2){
				
			dialog.text = "Liman civarında konuşulanlara göre, vali'nin yeğeni Julie d'Armagnac, eski halinden eser kalmamış. Bir zamanlar capcanlı ve ışıl ışılken, şimdi sokaklarda yüzüne kazınmış bir hüzünle dolaşıyor. Kasaba halkı fısıldaşıp başına ne geldiğini merak ediyor ama kimse gerçeği bilmiyor. Belki de bir alçak kalbini kırmıştır?"+GetSexPhrase(" Belki de sendin, Kaptan?","")+"";
			link.l1 = ""+GetSexPhrase("Sanmam ","")+". Teşekkür ederim, artık gitmeliyim.";
			link.l1.go = "exit";
			UV_Start();
			break;
        }
		//<-- Украденное воспоминание
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" That's it...", " You might find it interesting.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "That's very interesting, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("Well, everything can happen in our world. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. Maybe " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of a help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I've got anything of interest to tell you.","It will be a pleasure for me, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,srum+posrep1,srum+posrep2,RandPhraseSimple("Sanırım derdimi anlattım - işim bitti.","Sorularından bıktım artık, kaptan. Git kendine daha iyi bir iş bul!"),"block",1,npchar,Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,answ2,answ3,answ4,npchar,Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Teşekkürler, gitmeliyim.","Elveda.");
		link.l2.go = "exit";
	break;
	
/////////////////////////////////////////////////---слухи дворянок---////////////////////////////////////////////
	case "rumours_noblegirl":	
        srum = SelectRumourEx("noblegirl", NPChar);
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
        {
			dialog.text = "Liman civarında konuşulanlara göre, vali'nin yeğeni Julie d'Armagnac eskisi gibi değilmiş. Bir zamanlar ışıl ışıl ve hayat dolu olan kız, şimdi sokaklarda yüzünde silinmez bir hüzünle dolaşıyormuş. Kasaba halkı aralarında fısıldaşıp başına ne geldiğini merak ediyor ama kimse işin aslını bilmiyor. Belki de bir alçak kalbini kırmıştır?"+GetSexPhrase(" Belki de sendin, Kaptan?","")+"";
			link.l1 = ""+GetSexPhrase("Sanmam ","")+". Teşekkür ederim, şimdi ayrılmam gerek.";
			link.l1.go = "exit";
			UV_Start();
			break;
        }
		//<-- Украденное воспоминание
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" That's it...", " You might find it interesting.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "That's very interesting, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("Well, everything can happen in our world. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I've got anything of interest to tell you.","It will be my pleasure, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,srum+posrep1,srum+posrep2,RandPhraseSimple("Sanırım derdimi anlattım - işim bitti.","Sorularından bıktım artık, kaptan. Git kendine daha iyi bir iş bul!"),"block",1,npchar,Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,answ2,answ3,answ4,npchar,Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Teşekkür ederim, artık gitmeliyim.","Elveda.");
		link.l2.go = "exit";
	break;
	
	///////////////////////////////////////////---слухи матросов---////////////////////////////////////////////
	case "rumours_sailor":	
		NextDiag.CurrentNode = "rumours";

		//--> Грани справедливости
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "İki gün önce, Liman Şefi'nin hayatına cüretkâr bir suikast girişimi oldu! Sözde suikastçı, ofisinin kapısında pusuya yatmış, ama Şef yardım için bağırmayı başarmış. Bir musketeer hızla yetişip alçağı yaralamış, ama herif şehir kapılarından kaçmayı başarmış\nSöylenene göre Liman Şefi, o haydudun kellesi için yüklü bir ödül vaat ediyormuş! Şimdiye dek, buna cesaret edecek kimse çıkmamış. Vous savez, même s'il offrait mille doublons - je n'accepterais pas...";
			link.l1 = "Teşekkür ederim, şimdi gitmeliyim.";
			link.l1.go = "exit";
			GS_Start();
			break;
        }
		//<-- Грани справедливости
		//--> Письмо от покойника
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.LFD_Start") && npchar.city == "PortoBello";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.LFD_Start") && npchar.city == "PortoBello";
		if (bOk1 || bOk2)
        {
			dialog.text = "Duymuş muydun? 'Águila' adlı flüt gemisinin kaptanı, tavernada çavuşunu öyle bir azarlamış ki, duvarlar titremiş! Meğerse kaptan, gelgitle birlikte denize açılmayı planlıyormuş ama çavuş bütün tayfayı karaya salıvermiş. Şimdi denizciler şehre dağılmış durumda, zamanında dönmezlerse gemi onları bırakıp gidecekmiş – kaptan beklemeyecekmiş! Merak ediyorum, bu acele neden? Kârlı bir yük mü, iyi bir ticaret mi, yoksa validen acil bir görev mi var?";
			link.l1 = "Teşekkürler, artık gitmem gerek"+GetSexPhrase("","")+".";
			link.l1.go = "exit";
			LFD_Start();
			break;
        }
		//<-- Письмо от покойника
		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2) srum = SelectRumourEx("sailor", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" That's it...", " You might find it interesting.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "That's very interesting, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Whatever, just tell me something else...","Yeah, you were not much of a help, got anything else to share with me?");
            answ3 = RandPhraseSimple("Well, everything can happen in our world. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I've got anything of interest to tell you.","It will be my pleasure, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,srum+posrep1,srum+posrep2,RandPhraseSimple("Ne yazık ki, sana anlatacak başka bir şeyim yok, izin ver geçeyim.","Senin sorularından bıktım, affedersin, ilgilenmem gereken başka işlerim var."),"block",1,npchar,Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,answ2,answ3,answ4,npchar,Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Teşekkür ederim, artık gitmeliyim.","Elveda.");
		link.l2.go = "exit";
	break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case "rumours_habitue":
		//-->работорговец
		if (pchar.questTemp.Slavetrader == "FindRatJamaica_H" && npchar.location == "FortOrange_tavern")
        {
			dialog.text = "(singing) We're rascals and scoundrels, we're villains and knaves; Drink up me 'earties, yo ho! We're devils and black sheep, we're really bad eggs, Drink up me 'earties, yo ho!! Hey, matey, how are you doing? How is the sea?";
            link.l1 = "Deniz mi? Her zamanki kaltak işte. Tuzlu ve ıslak. Söylesene, benim dostum nereye gitti, hani şu kısa süre önce burada bir oda kiralayan? Adı François Gontier’di.";
            link.l1.go = "Jamaica_ratH_1";
			break;
        }
		if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_H" && npchar.location == "Villemstad_tavern")
        {
			dialog.text = "(şarkı söylüyor) Güzel kız, benimle gelir misin, güzel kız, yanıma uzanır mısın? Sabah olmadan bütün kurdelelerini toplarım, seni bırakmadan önce!";
            link.l1 = "Bir içki al dostum! Deniz nasıl?";
            link.l1.go = "EscapeSlave_Villemstad_H1";
			break;
        }
		//<--работорговец
				
		//Голландский Гамбит, против всех
		if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "LetterToLucasSent" && npchar.location == "Villemstad_tavern")
        {
			dialog.text = "Ah, deniz... Keşke senin yerinde olsaydım!";
            link.l1 = "Bir sorun görmüyorum, dostum. Mürettebatıma istediğin zaman katılabilirsin.";
            link.l1.go = "Lucas_Tavern";
			break;
        }
		//Голландский Гамбит
		
		//--> поиск дезертира
		if (CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE && !CheckAttribute(npchar, "quest.fugitive"))
        {
			dialog.text = LinkRandPhrase("Bilirsin, rom insanları dost yapar! Ha-ha!","Güzel bir yudum romdan sonra cellat bile göze hoş görünür! Ha-ha!","İçince uyursun, uyuyunca günah işlemezsin! Rom ve bira seni cennete götürür, o yüzden iç, kahretsin! Ha!");
            link.l1 = "Tabii, hadi bir içki paylaşalım... Söylesene dostum, biliyor musun "+pchar.GenQuest.FindFugitive.Name+"? O benim eski dostumdur. Bazı adamlar buraya taşındığını söylediler...";
            link.l1.go = "FindFugitiveHb";
			break;
        }
		//<-- поиск дезертира
		
		//--> карибские нравы
		if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy" && npchar.location == "Portobello_tavern")
		{
			dialog.text = "Haber mi? Ha! Daha duymadın mı? Askerlerimiz bir Fransız casusunu yakalamış. Kahrolası sahtekâr, tüccar gibi davranmaya kalkmış ama *hik* - bizim komutan tam bir belalı adam!";
            link.l1 = "Yok artık! O Fransız neyin peşindeymiş peki?";
            link.l1.go = "trial_spy";
			break;
		}
		if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	    {
			dialog.text = "Eh, "+GetAddress_Form(pchar)+" ne dünyada yaşıyoruz... Her taraf pislik heriflerle dolu!";
			link.l1 = "Ne demek istiyorsun?";
			link.l1.go = "Alcogol_GenQuest_Church_2_1";
			break;
		}
		//<-- карибские нравы
		
		//--> Sinistra Длинные тени старых грехов
		if (CheckAttribute(pchar, "questTemp.DTSG_NightIskat") && npchar.city == "SentJons")
        {
			dialog.text = "Duymadın mı?! İnanamıyorum! Meşhur Kaptan Fleetwood Londra'da vahşice öldürülmüş! Şöhretin peşinden koştu, her şeye sahipti ve sonunda sadece ölümü buldu... Burada kalsaydı, daha güvende olurdu. Bence bazen elindekinin kıymetini bilmek, para ya da makam peşinde koşmaktan iyidir, benden söylemesi efendim!";
            link.l1 = "Dostum, kolonide herkesin nerede yaşadığını biliyorsun, değil mi?";
            link.l1.go = "DTSG_NightIskat";
			break;
        }
		//<-- Длинные тени старых грехов
		
		//--> Rebbebion, квест "Путеводная звезда"
		if (CheckAttribute(pchar, "questTemp.PZ_Beliz.AskForLatterAndSotta") && !CheckAttribute(npchar, "questTemp.PZ_Sotta") && !CheckAttribute(npchar, "questTemp.PZ_Lutter") && npchar.city == "Beliz")
		{
			link.l1 = "Demek günün kahramanı, Kaptan Edgardo Sotta. Halk onun hakkında ne diyor? Sen ne düşünüyorsun? Onunla tanışmayı dört gözle bekliyordum.";
			link.l1.go = "Sotta1";
			link.l2 = "Dostum, neden tek başına içiyorsun? Herkes şu anda Geveze Matt'in asılmasını izlemek için toplanıyor.";
			link.l2.go = "Lutter1";
			break;
		}
		
		if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && !CheckAttribute(pchar, "questTemp.PZ.TortugaHabitueBlock") && npchar.city == "Tortuga")
		{
			link.l1 = "Dinle dostum, Joep van der Vink adında birini arıyorum. Ona bir mesaj iletmem gerekiyor. Nasıl biri olduğunu ya da hakkında bir şey biliyor musun?";
			link.l1.go = "Sepp1";
			break;
		}
		//<-- квест "Путеводная звезда"
		
		//--> Тёмные воды исцеления
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		if (bOk1 || bOk2)
        {
			dialog.text = "Duymuş muydun? Diyorlar ki Thomas Morrison'ın kızı altı aydır yatakta. Doktorlar hastalığına karşı tamamen çaresiz kalmış. Ona yardım edebilecek tek kişi, ölüm döşeğindekileri bile iyileştiren iksirleriyle tanınan çingene kadın. Ama zavallı kız için hiçbir şey yapmayı kesin bir dille reddetmiş.";
			link.l1 = RandPhraseSimple(RandSwear()+"Bu bir bardak daha hak ediyor...","Pekala, hadi bir içki daha içelim.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Teşekkürler, gitmeliyim.","Eh, ne rommuş be. Neyse, ben gideyim, burada iyi eğlenceler.");
			link.l2.go = "exit_sit";
			DWH_Start();
		break;
		}
		//<-- Тёмные воды исцеления
		//--> Грани справедливости
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "İki gün önce, Liman Şefi'nin hayatına cüretkâr bir saldırı girişimi oldu! Sözde suikastçı, ofisinin kapısında pusuya yatmış, ama Şef yardım için bağırmayı başarmış. Bir tüfekçi hızla yetişip alçağı yaralamış, yine de o herif şehir kapılarından kaçmayı başarmış.\nDuyduğuma göre Liman Şefi, o haydudun kellesi için yüklü bir ödül vaat ediyor! Şimdiye kadar, bu işe cesaret eden kimse çıkmamış. Düşünsene, bin doblon için bile... ben canımı tehlikeye atmam...";
			link.l1 = RandPhraseSimple(RandSwear()+"Bu bir bardak daha eder...","Pekala, birer içki daha içelim.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Teşekkür ederim, artık gitmeliyim.","Eh, ne rommuş be. Neyse, ben gideyim, burada iyi eğlenceler.");
			link.l2.go = "exit_sit";
			GS_Start();
			break;
        }
		//<-- Грани справедливости
		//--> Торговля по закону
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		if (bOk1 || bOk2)
        {
			dialog.text = "Haberi duydun mu?! Tam bir rezalet! Meyhanede bir damla rom ya da şarap kalmamış - bu lanet sıcakta insan nasıl ferahlayacak? Meyhaneci bir haftadır içki tekrar gelecek diye boş vaatler verip duruyor, ama ortada hiçbir şey yok! Kıyamete kadar boğazımızı kurutmaya mı mahkûmuz yani?";
			link.l1 = RandPhraseSimple(RandSwear()+"Bu bir bardak daha eder...","Pekâlâ, bir içki daha içelim.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Teşekkür ederim, artık gitmeliyim.","Eh, ne rommuş be. Neyse, ben gideyim, burada iyi eğlenceler.");
			link.l2.go = "exit_sit";
			TPZ_Start();
			break;
        }
		//<-- Торговля по закону
		//--> Старые счёты
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
		if (bOk1 || bOk2)
        {
			dialog.text = "Limanlarda konuşulanlara göre bizim meyhaneci fena halde dertte! Birisi adamın cinini çalmış! Hem de bir şişe falan değil, koca bir fıçı - bu adalarda başka yerde bulamazsın öyle bir şeyi! Avrupa'dan getirmişler diyorlar. Kurnaz herif kimin için sakladığını söylemiyor ama bir şey kesin: o fıçı yakında bulunmazsa, zavallı adamın başı büyük belaya girecek!";
			link.l1 = RandPhraseSimple(RandSwear()+"Bu bir bardak daha eder...","Pekâlâ, birer içki daha içelim.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Teşekkürler, gitmeliyim.","Eh, ne rommuş be. Tamam, ben gideyim, burada iyi eğlenceler.");
			link.l2.go = "exit_sit";
			OS_Start();
			break;
        }
		//<-- Старые счёты
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
        {
			dialog.text = "Liman civarında konuşulanlara göre, vali'nin yeğeni Julie d'Armagnac, eskisinin gölgesi haline gelmiş. Bir zamanlar capcanlı ve neşeliyken, şimdi sokaklarda yüzünde silinmez bir hüzünle dolaşıyor. Kasaba halkı fısıldaşıp başına ne geldiğini merak ediyor, ama kimse gerçeği bilmiyor. Belki de bir alçak kalbini kırmıştır?"+GetSexPhrase(" Belki de sendin, Kaptan?","")+"";
			link.l1 = RandPhraseSimple(RandSwear()+"Bu bir bardak daha eder...","Pekâlâ, bir içki daha içelim.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Teşekkürler, artık gitmeliyim.","Eh, ne rommuş be. Tamam, ben gideyim, burada iyi eğlenceler.");
			link.l2.go = "exit_sit";
			UV_Start();
			break;
        }
		//<-- Украденное воспоминание
		//--> В плену великого улова andre39966
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		if (bOk1 || bOk2)
        {
			dialog.text = "Rivayet odur ki, balıkçı Pierre Carno hiçbir iz bırakmadan ortadan kaybolmuş. İki sabah önce denize açılmış, o günden beri ondan tek bir haber yok. Karısı Lea, üzüntüden perişan halde. Gün ışığında da, lamba ışığında da iskelede bekliyor, gözleri sonsuz sulara dikilmiş, sevdiğinin yelkenini görebilmek için dua ediyor.";
			link.l1 = RandPhraseSimple(RandSwear()+"Bu bir bardak daha eder...","Pekala, hadi birer kadeh daha içelim.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Sağ ol, gitmeliyim.","Eh, ne romdu ama. Peki, ben gideyim, burada iyi eğlenceler.");
			link.l2.go = "exit_sit";
			VPVL_Start();
			break;
        }
		//<-- В плену великого улова
		//--> Тайна Бетси Прайс
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		if (bOk1 || bOk2)
        {
			dialog.text = "Kaptan, duydun mu? Bizim meyhanede yeni bir garson kız çalışmaya başlamış. Diyorlar ki, güzelliği dillere destan. Her yerden adamlar, sırf onu bir kez görebilmek için akın akın geliyor. Ama üç gün önce işe gelmemiş, bu da meyhaneciyi çok üzmüş; kız geldiğinden beri kazancı katlanmıştı. Şimdi ise, kızı bulana ödül bile verecekmiş, öyle diyorlar.​";
			link.l1 = RandPhraseSimple(RandSwear()+"Bu bir bardak daha hak ediyor...","Pekala, hadi bir kadeh daha içelim.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Teşekkürler, gitmeliyim.","Eh, ne romdu ama. Peki, ben gideyim, burada iyi eğlenceler.");
			link.l2.go = "exit_sit";
			TBP_Start();
			break;
        }
		//<-- Тайна Бетси Прайс
		//--> Оковы азарта
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.OZ_Start") && npchar.city == "PortSpein" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.OZ_Start") && npchar.city == "PortSpein";
		if (bOk1 || bOk2)
        {
			dialog.text = "Duymadın mı? Bizim demirci, Javier Castillo'ya kart oyununda öyle fena kaybetmiş ki, adam onu resmen soymuş, çok değerli bir şeyini ortaya koymaya zorlamış. O günden beri demirci kendine gelemedi, yeni sipariş de almıyor – sadece durmadan amiralin onu canlı canlı yüzmesinden korkup duruyor. Zavallı adam, burada herkes bilir ki o hilebaz Castillo'yla oyun oynanmaz!";
			link.l1 = RandPhraseSimple(RandSwear()+"Bu bir bardak daha hak ediyor...","Pekala, bir içki daha içelim.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Teşekkürler, gitmeliyim.","Eh, ne romdu ama. Peki, ben gideyim, burada iyi eğlenceler.");
			link.l2.go = "exit_sit";
			OZ_Start();
			break;
        }
		//<-- Оковы азарта
		//--> Письмо от покойника
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.LFD_Start") && npchar.city == "PortoBello";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.LFD_Start") && npchar.city == "PortoBello";
		if (bOk1 || bOk2)
        {
			dialog.text = "Duymuş muydun? 'Águila' adlı flütün kaptanı, tavernada çavuşuna öyle bir fırça çekmiş ki duvarlar titremiş! Meğerse kaptan, gelgitle birlikte denize açılmayı planlıyormuş, ama çavuş bütün tayfayı karaya salıvermiş. Şimdi denizciler kasabaya dağılmış, zamanında dönmezlerse gemi onları bırakıp gidecekmiş – kaptan beklemeyecekmiş! Merak ediyorum, bu acele niye? Kârlı bir yük mü, iyi bir ticaret mi, yoksa validen acil bir iş mi var acaba?";
			link.l1 = RandPhraseSimple(RandSwear()+"Bu bir bardak daha eder...","Pekala, birer içki daha içelim.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Teşekkürler, gitmeliyim.","Eh, ne rommuş be. Neyse, ben gideyim, burada iyi eğlenceler.");
			link.l2.go = "exit_sit";
			LFD_Start();
			break;
        }
		//<-- Письмо от покойника
		//--> LaEspadaDelRey
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.LEDR_Start") && npchar.city == "Pirates";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.LEDR_Start") && npchar.city == "Pirates";
		if (bOk1 || bOk2)
        {
			dialog.text = "Onu duydum, "+GetSexPhrase("dostum","missy")+"? Şehirde dolaşan deli bir ihtiyar var. Sabu-Matilla Körfezi'nde çürümüş bir teknenin enkazından sağ çıkan tek kişi olduğunu iddia ediyor ve şimdi oraya dönmek için yanıp tutuşuyor. Ama tek başına gitmeye cesareti yok. Her sabah kabile kıyafetli bir iskeletin ortaya çıkıp onunla ölümüne dövüştüğünden durmadan bahsedip duruyor. Ben mi? *hik* Ona beş yüz dublon verseler bile gitmem. Kim bilir o budalanın kafasında ne şeytanlar cirit atıyor.";
			link.l1 = RandPhraseSimple(RandSwear()+"Bu bir bardak daha eder...","Pekâlâ, birer kadeh daha içelim.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Teşekkürler, gitmeliyim.","Eh, ne romdu ama. Neyse, ben gideyim, burada iyi eğlenceler.");
			link.l2.go = "exit_sit";
			LEDR_Start();
			break;
        }
		//<-- LaEspadaDelRey
		
		Dialog.Text = LinkRandPhrase("Şey... hık! ","Ah, güzel rom! ","Pekâlâ... ")+SelectRumourEx("habitue",NPChar);
		link.l1 = RandPhraseSimple(RandSwear()+"Bu bir bardak daha eder...","Peki, hadi bir kadeh daha içelim.");
		link.l1.go = "sit_3";
		link.l2 = RandPhraseSimple("Teşekkürler, gitmeliyim.","Eh, ne rommuş be. Peki, ben gideyim, burada iyi eğlenceler.");
		link.l2.go = "exit_sit";
	break;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_trader":
            if (!CheckAttribute(NPChar, "quest.repeat.rumours_trader") || NPChar.quest.repeat.rumours_trader!= 3 )
            strum = SelectRumourEx("trader", NPChar);
            else strum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
			Dialog.Text = NPCStringReactionRepeat(strum,strum+"Evet.   Anlatacak başka bir şey yok.",strum+" Şimdi işime geri dönmeliyim.",RandPhraseSimple("Sana zaten söyledim, boş lakırdıya vaktim yok!","Ben meşgul bir adamım, dedikoduya vaktim yok!"),"block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(pcharrepphrase(RandSwear()+"İlginçmiş! Ama sadede gelelim","Teşekkür ederim, bir şey daha var."),pcharrepphrase(""+GetSexPhrase("Lanet olsun bana","İlginç")+"! Güzel hikaye anlatıcısı. Ama bir sorum daha var.","Daha fazla vakit kaybetmeyelim, iş konuşalım."),pcharrepphrase(RandSwear()+" Bir şey daha, sonra gideceğim.","Doğru söylüyorsun, zaman paradır."),pcharrepphrase("Her zaman sadece kendi çıkarını düşünüyorsun! Peki, aklını kaçırma bari.","Beni affet. Hadi iş konuşalım."),npchar,Dialog.CurrentNode);
			link.l1.go = "business";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Elveda, sen yaşlı ayyaş.","Hoşça kal, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"."),pcharrepphrase("Caramba! Çok uzaklaşma. Hemen döneceğim.","Seni görmek güzel, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"! Elveda!")),NPCharRepPhrase(npchar,pcharrepphrase("Demir alın!","Elveda!"),pcharrepphrase("Hey! Orada ne saklıyorsun? Rom mu? Hayır mı?! Neyse, ben kendime bir içki alırım.","Üzgünüm, şehirde önemli işlerim var.")),NPCharRepPhrase(npchar,pcharrepphrase("Heh! Görüşürüz!","Gitmeliyim. Hoşça kal, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!"),pcharrepphrase("Benimle tartışmaya kalkma! Bunu hiç istemiyorum!","Sanırım gemime bakmalıyım. Görüşürüz, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),NPCharRepPhrase(npchar,pcharrepphrase("Ne oldu sana, dostum? Benim - "+GetFullName(pchar)+"! Biraz kestir, sonra konuşuruz.","Korkarım ki bir dahaki gelişimde seni ciğerin öldürmüş olacak."),pcharrepphrase("Paranı iyi say, tilki! Sonra görüşürüz.","Seni görmek güzel, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),npchar,Dialog.CurrentNode);
			link.l2.go = "Exit";
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_capitan":
			Dialog.Text = SelectRumourEx("kaptan",NPChar);
			Link.l1 = RandPhraseSimple(RandSwear()+"İlginç! Bir şey daha sormak istiyorum...","Bir soru daha.");
			Link.l1.go = "quests";
			Link.l2 = RandPhraseSimple("Teşekkürler, gitmeliyim.","Elveda.");
			Link.l2.go = "exit";
			NextDiag.TempNode = "quests";
            NPChar.talk_date =  lastspeakdate();
		break;
		
		 case "rumours_landcaptain":
			Dialog.Text = SelectRumourEx("landcaptain",NPChar);
			Link.l1 = RandPhraseSimple(RandSwear()+"İlginç! Bir şey daha sormak istiyorum...","Bir soru daha.");
			Link.l1.go = "question";
			Link.l2 = RandPhraseSimple("Sağ ol, artık gitmeliyim.","Elveda.");
			Link.l2.go = "exit";
			NextDiag.TempNode = "question";
            NPChar.talk_date =  lastspeakdate();
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_tavern":  // homo 03/08/06
				if(startHeroType == 4)
				{
					Dialog.Text = NPCStringReactionRepeat(LinkRandPhrase("Fiyatı biliyorsun. Bilgi de oda, yemek ya da içki gibi - bedeli var. Bunun için bin peso isterim.","Fiyatı biliyorsun. Bilgi de oda, yemek ya da içki gibi – bir bedeli var. Bin peso isterim.","Fiyatı biliyorsun. Bilgi de oda, yemek ya da içki gibi - bedeli var. Bin peso isterim."),"Burada ekleyecek başka bir şey yok. Şimdi, müsaadenizle, gitmeliyim.","","","block",1,npchar,Dialog.CurrentNode);
				 
					link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Aslında, neden bunu sana soruyorum ki? Başkasına da sorabilirim. Rahatsız ettiğim için kusura bakma.","Aslında, neden sana soruyorum ki? Başkasına da sorabilirim. Rahatsız ettiğim için kusura bakma."),"","","",npchar,Dialog.CurrentNode);
					link.l1.go = HeroStringReactionRepeat("rumours_tavern_no", "first time", "first time", "first time", npchar, Dialog.CurrentNode);//"rumours_tavern_no";
					NextDiag.CurrentNode = NextDiag.TempNode;
					if (makeint(pchar.money) >= 1000)
					{
						link.l2 = HeroStringReactionRepeat(RandPhraseSimple("Elbette biliyorum. İşte ödemen.","Elbette biliyorum. İşte ödemen."),"","","",npchar,Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_yes", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
					else
					{
						link.l2 = HeroStringReactionRepeat("Bende o kadar para yok.","","","",npchar,Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_no", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
				}
				else
				{
					Dialog.Text = NPCStringReactionRepeat(LinkRandPhrase("Bilgi parayla satılır. 1000 peso ver, bildiğim her şeyi anlatayım.","Hafızamda bir tuhaflık var, belki bin sekizlik altın hafızamı tazeler.","Seninle bilgi paylaşmaya hazırım. Ama bunun bedeli 1000 sekizli. Pazarlık yok."),"Burada ekleyecek başka bir şey yok. Şimdi müsaadenizle, gitmeliyim.","","","block",1,npchar,Dialog.CurrentNode);
				 
					link.l1 = HeroStringReactionRepeat(RandPhraseSimple(RandSwear()+"Boş lakırdıya para vermem.","Bu parayı harcamanın daha iyi yollarını düşüneceğim."),"Konu değiştirelim.","Konu değiştirelim.","Konu değiştirelim.",npchar,Dialog.CurrentNode);
					link.l1.go = HeroStringReactionRepeat("rumours_tavern_no", "first time", "first time", "first time", npchar, Dialog.CurrentNode);//"rumours_tavern_no";
					NextDiag.CurrentNode = NextDiag.TempNode;
					if (makeint(pchar.money) >= 1000 )
					{
						link.l2 = HeroStringReactionRepeat(RandPhraseSimple("Senden değerli bir şey öğrenirsem onları alırsın.","Sana değerli bir şey verirsen, öderim."),"","","",npchar,Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_yes", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
					else
					{
						link.l2 = HeroStringReactionRepeat("Bende o kadar para yok.","","","",npchar,Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_no", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
				}

		break;
		
		case "rumours_tavern_yes":
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation"))
			{
				bool bOk = (pchar.questTemp.Saga.BarbTemptation == "silk") || (pchar.questTemp.Saga.BarbTemptation == "give_silk");
				if (bOk && npchar.location == "Marigo_tavern" && !CheckAttribute(npchar, "quest.barbtemptation"))
				{
					AddMoneyToCharacter(pchar, -1000);
					Dialog.Text = "Devriyemiz yakın zamanda Morel adında Fransız bir kaçakçının brigantinini batırdı. Adam şimdi zindanda oturuyor, idamı bekliyor. Komutanımız gemisinde tam yük olmadığını düşünüyor, bu yüzden hâlâ onu arıyor... Komutan kayıp yükü bulduğunda Fransız da ölecek.";
					link.l1 = "İlginç... Peki, al parayı. Başka söyleyeceğin bir şey var mı?";
					link.l1.go = "rumours_tavern";
					Saga_CreateMorelle(); //ставим Мореля
					npchar.quest.barbtemptation = "true";
					pchar.questTemp.Saga.BarbTemptation.Prison = "true";
					break;
				}
			}	
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_portobello" && npchar.location == "portobello_tavern")
			{
				DelLandQuestMark(npchar);
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text = "Valinin sarayında büyük bir eğlence vardı. Ekselanslarının dostu Don Carlos de Milyar geri döndü. Bir deniz savaşında esir alınmıştı ama bir Fransız teğmenin yardımıyla kaçmayı başarmış. Don Carlos sadece zeki değil, aynı zamanda çok cömert bir adam. Onun desteğiyle, bu teğmen Jean Deno şimdi 'Sario'nun kaptanı olmuş. Duyduğuma göre küçük bir plantasyon da hediye etmişler. Şimdi o kurbağa yiyeni Juan diye çağırıyorlar! Ne hikaye ama!";
				link.l1 = "İlginç... Peki, para senin. Al bakalım. Başka söyleyeceğin bir şey var mı?";
				link.l1.go = "rumours_tavern";
				pchar.questTemp.FMQG = "headhunter_juan";
				AddQuestRecord("FMQ_Guadeloupe", "10");
				pchar.quest.FMQG_Juanship.win_condition.l1 = "location";
				pchar.quest.FMQG_Juanship.win_condition.l1.location = "PortoBello";
				pchar.quest.FMQG_Juanship.function = "FMQG_CreateJuanship";
				break;
			}	
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(pchar, "questTemp.FMQN") && pchar.questTemp.FMQN == "town" && npchar.location == "Marigo_tavern")
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text = "Komutanımız, ormanda devriye gezmek için ek kuvvetler gönderdi ve kasabadaki nöbetçi sayısını artırdı. İngilizlerin Philipsburg'a sızıp esir subayları serbest bırakmayı planladığına dair söylentiler dolaşıyor.";
				link.l1 = "Yok artık! Gerçekten böyle bir numara yapmaya cesaretleri var mı? Ve tam olarak hangi subaylardan bahsediyorsun?";
				link.l1.go = "FMQN_r";
				break;
			}	
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_3" && npchar.location == "Havana_tavern")
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text = "Geçen gün bütün kasaba bir arı kovanı gibi ayağa kalktı. Askeri bir şalopadan bir subay benim meyhanemde sızıp kaldı, neredeyse evli bir kadına saldıracaktı. Sonra da karısını korumaya çalışan adamı dövdü, hatta ona kılıç çekip tehdit etti. Düşünsene, bütün bunlar kasabanın muhafızlarının gözünün önünde oldu! Derler ya, güçlünün sözü geçer. Askerler ise bu alçak ortalığı birbirine katarken sadece başka tarafa baktılar. Ama kim derdi ki, bu herifi tüccar bir geminin tayfaları silahsızlandıracak. Neredeyse elleriyle bağlayacaklardı, ama alçak kaçıp gemisine saklandı. Komutan ve Belediye Başkanı olayı örtbas etmeye çalıştı, ama öfkeli koca saygın bir vatandaş, işin ucunu Ekselansları Don Diego de Toledo'ya kadar götürdü, yerel soylular arasında da epey gürültü kopardı. Subayın tutuklanması için emir çıkardılar. Söylentilere göre kaptanına limandan ayrılması ve bu alçağı başka bir yere göndermesi tavsiye edilmiş. Ama şalopa kaptanı Esberdo Cabanas onurlu bir adamdır. Subayının ne halt ettiğini öğrenir öğrenmez hemen tutuklatıp karaya göndermiş. O alçak şimdi hapiste çürüyüp duruyor, bana sorarsan da yeri orası. Sonra da belki sıradan bir askere düşürülüp kamçılanır, başkalarına ibret olsun diye.";
				link.l1 = "Bir dakika, Kaptan Esberdo Cabanas mı dedin? Hah... gerçekten heyecanlı bir hikaye! Peki, paranı hak ettin, al bakalım. Bana başka anlatabileceğin bir şey var mı?";
				link.l1.go = "rumours_tavern";
				Mtraxx_CreateOfficer(); // ставим офицера-негодяя
				pchar.questTemp.Mtraxx = "jewelry_4";
				pchar.GenQuest.PrisonQuestLock = "true";
				AddQuestRecord("Roger_1", "7");
				DelLandQuestMark(characterFromId("Havana_tavernkeeper"));
				AddLandQuestMarkToPhantom("havana_prison", "havanaJailOff");
				break;
			}
			// Jason Исла Мона
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "rumours" && rand(2) == 1)
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text = "Birilerinin bazı suçluları ıssız adalardan birine terk ettiğini söylüyorlar! Sözde öyle acımasız canavarlarmış ki, ne cellat ne de kutsal babalar onlarla başa çıkmaya cesaret edememiş! Ama neden sonunda hep buraya getiriyorlar bunları?!";
				link.l1 = "Hmm... ne ilginç! Belki peşlerine düşüp onları ekibime katmalıyım – çaresiz ruhlara her zaman ihtiyacım var... Neden böyle solgunlaştın? Şaka yapıyorum, şaka yapıyorum... Paranı hak ettin – al bakalım. Duyduğun başka ilginç bir şey var mı?";
				link.l1.go = "rumours_tavern";
				IslaMona_TerksCreateHimenes();
				break;
			}
			// Гаспар во фриплее 
			if ((SandBoxMode) && npchar.city == "Tortuga" && (sti(pchar.reputation.nobility) < 41))
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text = "İtibarınız sizden önce geliyor, kaptan. Bahse girerim bu küçük ıvır zıvırları ve parlayan taşları nereye satacağınızı sık sık düşünmüşsünüzdür...";
				link.l1 = "Bu konuda bana yardımcı olabilecek birini mi tanıyorsun?";
				link.l1.go = "About_Gaspar";
				break;
			}
            string RumText = SelectRumourEx("tavern", NPChar); //fix
			
		    if(!RumourHasInformation(RumText))
            {
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; //fix
				if(startHeroType == 4)
				{
					link.l1 = "Meğerse hiçbir şey bilmiyormuşsun. Beni böyle kandırmanı beklemezdim. Pek akıllıca değilmiş. Neyse, hoşça kal.";
				}
				else
				{
					link.l1 = RandPhraseSimple("Beş para etmez bir saçmalık. Sana tek bir peso bile vermem! Hoşça kal.","Senin verdiğin bilgi beş para etmez, bu yüzden hiçbir şey alamayacaksın.");
				}
			    link.l1.go = "Exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
            }
            else
            {
                AddMoneyToCharacter(pchar, -1000);
                Dialog.Text = RumText;
				if(startHeroType == 4)
				{
					link.l1 = "Gerçekten mi? İlginç, sağ ol. Neyse, gitmem gerek, bir dahaki sefere görüşürüz.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = RandPhraseSimple("Teşekkürler, al parayı. Başka diyeceğin bir şey var mı?","Peki, al parayı. Başka diyeceğin bir şey var mı?");
					link.l1.go = "rumours_tavern";
				}
    			NextDiag.CurrentNode = NextDiag.TempNode;    
            }
		break;

		case "rumours_tavern_no":
			if(startHeroType == 4)
			{
				Dialog.Text = "Birkaç kuruşla yardım edebilirdin. Senin gibi değilim Helen, beni Kardeşler Baronu desteklemiyor.";
				link.l1 = "Koca bir mekânın var. Ben ise kendi başıma geldim bu noktaya. Gerçi, Baron'un verdiği gemi, toplar, tayfa ve erzak hariç. Neyse, boşver.";
				link.l1.go = "exit";
				NextDiag.CurrentNode = NextDiag.TempNode;
			}
			else
			{
				Dialog.Text = "Beni yanlış anlama, ailemi doyurmam lazım.";
				link.l1 = "Konu değiştirelim.";
				link.l1.go = "first time";
				NextDiag.CurrentNode = NextDiag.TempNode;
				link.l2 = LinkRandPhrase("Teşekkür ederim, artık gitmeliyim.","Elveda.","Hoşça kal.");
				link.l2.go = "Exit";
			}
		break;	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_poor":
			if (!CheckAttribute(NPChar, "quest.repeat.rumours_poor") || NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("fakir",NPChar);
				Link.l1 = RandPhraseSimple(RandSwear()+"İlginç. Bir soru daha...","Hmm, başka bir şey sorayım...");
				Link.l1.go = "rumours_poor_2";
				Link.l2 = RandPhraseSimple("Pekala, hoşça kal.","Hoşça kal, dostum.");
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else 
			{
				Dialog.Text = RandPhraseSimple("Sana bildiğim her şeyi söyledim.","Paylaşacak başka bir şeyim yok, üzgünüm...");
				Link.l1 = RandPhraseSimple("Anladım. Hoşça kal.","Hoşça kal, dostum...");
				Link.l1.go = "exit";			
			}
            NPChar.talk_date = lastspeakdate();
		break;
        case "rumours_poor_2":
			if (NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("fakir",NPChar);
				Link.l1 = RandPhraseSimple(RandSwear()+"İlginç. Bir soru daha...","Hm, sana başka bir şey sorayım...");
				Link.l1.go = "rumours_poor";
				Link.l2 = RandPhraseSimple("Pekâlâ, elveda.","Hoşça kal, dostum.");
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else 
			{
				Dialog.Text = RandPhraseSimple("Sana bildiğim her şeyi anlattım.","Paylaşacak başka bir şeyim yok, üzgünüm...");
				Link.l1 = RandPhraseSimple("Anladım. Hoşça kal.","Anlaşıldı. Hoşça kal, dostum...");
				Link.l1.go = "exit";			
			}
			NPChar.talk_date = lastspeakdate();
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_LSC":
			if (CheckNPCQuestDate(NPChar, "quest.repeat.rumours"))
			{
				Dialog.Text = SelectRumourExSpecial("LSC",NPChar);
				Link.l1 = RandPhraseSimple("Anlaşıldı...","Anladım...");
				Link.l1.go = "exit";
				SetNPCQuestDate(NPChar, "quest.repeat.rumours");
			}
			else  
			{
				Dialog.Text = NPCharSexPhrase(npchar,RandPhraseSimple("Sana bildiğim her şeyi söyledim.","Yeni bir şey duymadım, üzgünüm..."),RandPhraseSimple("Sana bildiğim her şeyi anlattım.","Yeni bir şey duymadım, üzgünüm..."));
				Link.l1 = RandPhraseSimple("Anladım, o zaman hoşça kal.","Anlaşıldı. Hoşça kal.");
				Link.l1.go = "exit";			
			}
		break;
		
//Jason -------------слухи смотрителей маяков, идентичны таверне, но бесплатны, по 1 шт за день--------------------
		case "rumours_lighthouse": 
			Dialog.Text = NPCStringReactionRepeat(RandPhraseSimple("Eh, kaptan! Seninle sohbet etmek her zaman güzel. Burada tek başıma olmak bazen oldukça sıkıcı olabiliyor...","Yalnız yaşıyorum, misafirler nadiren gelir. O yüzden sohbet etmeye her zaman hazırım."),"Konuşmayı seviyor musun, kaptan? Eh, sana anlatacak başka bir şeyim daha olabilir...","Bir dahaki gelişinde bir şişe rom getir. Sohbet içkiyle daha güzel olur...","Ne yazık ki, bildiğim her şeyi anlattım. Ekleyebileceğim başka bir şey yok.","block",1,npchar,Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("O zaman paylaş bakalım bildiklerini. İnsanlarla sohbet etmeyi severim, biliyorsun...","Söyle bana! Derler ya, bilgiyi elinde tutan dünyayı elinde tutar mı?"),"Ne gibi?","Elbette!   Başka anlatacak bir şeyin var mı?","Pekâlâ, yine de güzel bir sohbet ettik.",npchar,Dialog.CurrentNode);
    		link.l1.go = HeroStringReactionRepeat("rumours_lighthouse_yes", "rumours_lighthouse_void", "rumours_lighthouse_void", "exit", npchar, Dialog.CurrentNode);
		break;
		
		case "rumours_lighthouse_yes":
            RumText = SelectRumourEx("tavern", NPChar);
		    if(!RumourHasInformation(RumText))
            {
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
                link.l1 = RandPhraseSimple("Teşekkürler! Başka bir şey var mı?","Çok ilginç! Başka bir şey var mı?");

			    link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("Teşekkürler! Oldukça eğlenceliydi...","Bana söylediğin için teşekkür ederim!");
			    link.l2.go = "exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
            }
            else
            {
                Dialog.Text = RumText;
    			link.l1 = RandPhraseSimple("Teşekkürler! Başka bir şey var mı?","Çok ilginç! Başka bir şey var mı?");
    			link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("Teşekkürler! Oldukça eğlenceliydi...","Bana söylediğin için teşekkür ederim!");
			    link.l2.go = "exit";
    			NextDiag.CurrentNode = NextDiag.TempNode;    
            }
		break;
		
		case "rumours_lighthouse_void":
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
                link.l1 = RandPhraseSimple("Teşekkürler! Başka bir şey var mı?","Çok ilginç! Başka bir şey var mı?");

			    link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("Teşekkürler! Oldukça eğlenceliydi...","Bana söylediğin için teşekkür ederim!");
			    link.l2.go = "exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
		break;
//Jason ------------------------------------почтовый генератор 2 уровня-------------------------------------------
		case "Postcureer_LevelUp_ForAll":
			//начинаем проверять
			if (!CheckCharacterItem(pchar, pchar.questTemp.WPU.Current.Item))
			{
				dialog.text = "Peki ya paket nerede? O sende değil mi?";
	        	link.l1 = "Şey... Aslında onu sana teslim etmem gerekiyordu. Ama... dürüst olmak gerekirse, elimden aldılar. Karşı koyamadım ve paketi o saldırganlara kendi ellerimle verdim. ";
	        	link.l1.go = "Postcureer_LevelUp_complete_fail";
				break;
			}
			
			if (sti(pchar.questTemp.WPU.Postcureer.AgentChance) == 4)//раскрыли обман
			{
				dialog.text = "Hm. Affedersiniz, ama paket daha önce açılmış! Bu benim için apaçık. Mühür yeniden basılmış...";
	        	link.l1 = ""+GetAddress_FormToNPC(NPChar)+", bu   liman ofisinde bana verilen paketti "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+", ve en ufak bir fikrim yok...";
	        	link.l1.go = "Postcureer_LevelUp_complete_Agentfail";
				break;
			}
			
			if (pchar.questTemp.WPU.Postcureer == "late")//опоздали
			{
				int iTime = makeint(GetQuestPastDayParam("questTemp.Postcureer.Late"))+1;
				pchar.questTemp.WPU.Postcureer.Money = makeint(sti(pchar.questTemp.WPU.Postcureer.Money)/(sti(iTime)+1));//сильно снижаем оплату
				dialog.text = "Seni bekliyordum. Ama sen "+FindRussianDaysString(iTime)+" geç kaldın! Taşıdığın bilgi artık pek işe yaramıyor... Yine de biraz değeri var tabii, bu yüzden sana ödeme yapacağım "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+". Lütfen, parayı alın ve elveda.";
	        	link.l1 = "Sağ ol. Sanırım.";
	        	link.l1.go = "Postcureer_LevelUp_complete";
				pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
				pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-1;//опоздавший рейс не засчитываем
				AddQuestRecord("Postcureer", "8");
				AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(iTime));
				AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
				AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
				break;
			}
			
			if (pchar.questTemp.WPU.Postcureer == "lost")//опоздали совсем
			{
				dialog.text = "Demek sensin! Seni bir süredir bekliyordum, paketi almak için de bazı önlemler aldım. Ver onu bana. Artık gerçekten ihtiyacım yok, tam zamanında geldin, ama yine de onu kendime saklamak isterim\nAnlayacağın, sana herhangi bir ödeme yapamam, ama iyi adının geri kazanılmasını sağlayacağım.";
	        	link.l1 = "Teşekkürler... sanırım. Geciktiğim için gerçekten üzgünüm. Hoşça kal.";
	        	link.l1.go = "Postcureer_LevelUp_complete_bad";
				break;
			}
			dialog.text = "Seni bekliyordum. Tam zamanında geldin, getirdiğin bilgiler çok işime yarayacak. Lütfen, emeğinin karşılığı olarak bu parayı kabul et - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+" . Zamanlamanız için teşekkür ederim.";
        	link.l1 = "Rica ederim. Hoşça kal!";
        	link.l1.go = "Postcureer_LevelUp_complete";
			pchar.quest.PostcureerTime_Over.over = "yes";//снять таймер
			AddQuestRecord("Postcureer", "10");
		break;
		
		case "Postcureer_LevelUp_complete":
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Postcureer.Money));
			CloseQuestHeader("Postcureer");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			pchar.questTemp.WPU.Postcureer = "complete";
			AddCharacterExpToSkill(pchar, "Sailing", 120);//навигация
			AddCharacterExpToSkill(pchar, "Sneak", 120);//скрытность
			AddCharacterExpToSkill(pchar, "Leadership", 150);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 150);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
		
		case "Postcureer_LevelUp_complete_bad":
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			AddQuestRecord("Postcureer", "9");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), 33);
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			pchar.questTemp.WPU.Postcureer = "complete";
			DialogExit();
		break;
		
		case "Postcureer_LevelUp_complete_fail":
			dialog.text = "Eh, bunun böyle biteceğini biliyordum... Askeri bir kurye gemisi tutmalıydım, sivil bir kaptan değil... Neyse, "+GetAddress_Form(NPChar)+", sen bir asker değilsin, bu yüzden seni suçlayacak bir şey yok. Hoşça kal.";
			link.l1 = "Hoşça kal, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			if (pchar.questTemp.WPU.Postcureer == "begin") pchar.quest.PostcureerTime_Over.over = "yes";//снять таймер
			if (pchar.questTemp.WPU.Postcureer == "late") pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), -2);
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-3;//скрутим счетчик
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			pchar.questTemp.WPU.Postcureer = "complete";
		break;
		
		case "Postcureer_LevelUp_complete_Agentfail":
			dialog.text = "Efendim,  liman müdürünü tanıyorum "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+" şahsen, o dürüst bir adamdır. Ayrıca, paketi açması için hiçbir sebep yoktu. "+GetAddress_Form(NPChar)+", sen bir sahtekârsın! Sana bir kuruş bile ödemeyeceğim. Defol git!";
			link.l1 = "Hm...";
			link.l1.go = "Postcureer_LevelUp_complete_Agentfail_1";
		break;
		
		case "Postcureer_LevelUp_complete_Agentfail_1":
			if (pchar.questTemp.WPU.Postcureer == "begin") pchar.quest.PostcureerTime_Over.over = "yes";//снять таймер
			if (pchar.questTemp.WPU.Postcureer == "late") pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			AddQuestRecord("Postcureer", "17");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), -2);
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-3;//скрутим счетчик
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.AgentChance");
			pchar.questTemp.WPU.Postcureer = "complete";
			DialogExit();
		break;
		
// <--почтовый генератор 2 уровня

//Jason --> ---------------------------------генератор Неудачливый вор--------------------------------------------
		case "Device_Common":
			dialog.text = "Çöpten farksızdı. Ya bir serseri ya da bir dilenci. Nereye gittiğini tam göremedim, peşinden gitmek de istemedim.";
			link.l1 = "Hiç yoktan iyidir. Teşekkür ederim! Gitmeliyim.";
			link.l1.go = "Device_Common_1";
		break;
		
		case "Device_Common_1":
			string sNation = pchar.GenQuest.Device.Shipyarder.Nation;
			sld = GetCharacter(NPC_GenerateCharacter("Device_poorman", "panhandler_"+(rand(5)+1), "man", "man", sti(pchar.rank)+5, sNation, 20, true, "quest"));
			SetFantomParamFromRank(sld, sti(pchar.rank)+5, true);         
			GiveItem2Character(sld, "slave_02");
			EquipCharacterbyItem(sld, "slave_02");
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, sNation+"_CITIZENS");
			sld.Dialog.Filename = "Quest\Other_Quests_NPC.c"; 
			sld.dialog.currentnode = "Device_poorman"; 
			sld.greeting = "Gr_poorman";
			switch (sti(pchar.GenQuest.Device.Shipyarder.Chance2))
			{
				case 0://в городе
					sld = characterFromId("Device_poorman");
					GetCharacterPos(pchar, &locx, &locy, &locz);
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.City +"_town", "goto", LAi_FindFarLocator("goto", locx, locy, locz));
				break;
				case 1://за воротами
					sld = characterFromId("Device_poorman");
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.City + "_ExitTown", "goto", "goto1");
				break;
				case 2://в бухте
					sld = characterFromId("Device_poorman");
					pchar.GenQuest.Device.Shipyarder.Shore = SelectQuestShoreLocation();
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.Shore, "goto", "goto1");
				break;
				case 3://в доме
					sld = characterFromId("Device_poorman");
					pchar.GenQuest.Device.Shipyarder.Location = GetDeviceLocation(npchar); //определяем локацию
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.Location, "goto", "goto1");
					if (pchar.GenQuest.Device.Shipyarder.Location == "none" || CheckAttribute(pchar, "GenQuest.SeekSpy.Location"))//если вдруг мимо или взят поиск шпиона
					{
						pchar.GenQuest.Device.Shipyarder.Shore = SelectQuestShoreLocation();
						ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.Shore, "goto", "goto1");
					}
				break;
			}
			pchar.GenQuest.Device.Shipyarder = "inSeek";
			DialogExit();
			AddQuestRecord("Device", "9");
		break;
		//<-- генератор Неудачливый вор
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN_r":
			DelLandQuestMark(npchar);
			if (GetNationRelation(SPAIN, ENGLAND) == RELATION_NEUTRAL) {"Not long ago, an English ship was intercepted off the coast of Sint Maarten, and aboard it were several high‑ranking officers. They planned to send them to Willemstad pending investigation, but for the time being they were locked up in prison. There’s word that one of the captured soldiers, in exchange for his freedom, told the commandant that the English intended to send in a sabotage team and stage a jailbreak. They even had their plan ready. So our brave commandant is keeping a sharp lookout. If such important birds fly the coop — he’ll surely be stripped down to a common soldier. That’s not all — we can’t afford another war starting again.";}
			else {Dialog.Text = "Not long ago, an English vessel was captured in the waters of Sint-Maarten; she was carrying a few high-ranking officers. It was decided to send them to Willemstad, but at this moment they are being held here in our comfortable dungeons. They say that one of the captured soldiers told our commandant about the English intention to send a raiding party here to rescue the officers. That's why our good old commandant is ready and armed. Why wouldn't he be? If the prisoners escape, he'll be demoted to a common soldier!";}
			link.l1 = "İlginç... Peki, para senin. Al bakalım. Başka söylemek istediğin bir şey var mı?";
			link.l1.go = "rumours_tavern";
			pchar.questTemp.FMQN = "governor";
			pchar.quest.FMQN_governor.win_condition.l1 = "location";
			pchar.quest.FMQN_governor.win_condition.l1.location = "Marigo_town";
			pchar.quest.FMQN_governor.function = "FMQN_ToGovernor";
			if (Whr_IsDay()) AddDialogExitQuest("FMQN_GetRumoursDay");
			else AddDialogExitQuest("FMQN_GetRumoursNight");
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Квесты мэра, проникновение во враждебный город
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "IntelligenceForAll":
            Dialog.Text = RandPhraseSimple("Pekâlâ o zaman. Paket burada, teslimata hazır. Al bunu\nBir daha buraya gelme ve benimle konuşma, çok tehlikeli. Kendine dikkat et...","Hm, peki. Paketi al ve az önce konuştuğumuz adama teslim ettiğinden emin ol\nHoşça kal, bir daha benimle konuşma, bu çok tehlikeli.");
            link.l1 = RandPhraseSimple("Anladım. Hoşça kal...","Elveda ve bol şanslar.");
			link.l1.go = "exit";
			pchar.GenQuest.Intelligence = "Execute";
			GiveItem2Character(pchar, "sicretLetter");
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			ref rItem = ItemsFromID("sicretLetter");
			rItem.City = XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId)].city+"Gen")); 
			rItem.Mayor = GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)); 
			AddQuestRecord("MayorsQuestsList", "7");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId)].city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Voc")); // belamour gen
			AddQuestUserData("MayorsQuestsList", "sWho", GetWorkTypeOfMan(&characters[GetCharacterIndex(pchar.GenQuest.Intelligence.SpyId)], "Gen"));
			AddQuestUserData("MayorsQuestsList", "SpyName", GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.Intelligence.SpyId)]));			
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Гаспар во фриплее
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "About_Gaspar":
			dialog.text = "Biliyorum. Adı Gaspar Parmentier, ama arkadaşları ona Altın Diş der. Güvenilir bir adamdır ve en önemlisi, hiçbir tefecinin hayal edemeyeceği miktarlarda alım yapar. Eminim çabucak anlaşacaksınız. Sadece şunu unutma: yabancıları sevmez. Yanına gidersen mutlaka benden geldiğini söyle. Evi liman idaresinin yakınındadır.";
			link.l1 = "Peki, paranı hak ettin — al. Başka dikkat çekici bir şey biliyor musun?";
			link.l1.go = "rumours_tavern";
			AddDialogExitQuestFunction("CreateGaspar_Sandbox");
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Грабеж среди бела дня, попытка залезть в сундуки
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "Man_FackYou":
			dialog.text = LinkRandPhrase("Gündüz vakti soygun mu olur?! Gerçekten mi?! Olduğun yerde kal, dostum...","Hey, orada ne yapıyorsun?! Az kalsın beni soyacaklardı. Senin işin bitti...","Dur, nereye gidiyorsun? Hırsız! Yolun sonu, dostum...");
			link.l1 = LinkRandPhrase("Lanet olsun!","Caramba!","Lanet olsun!");
			link.l1.go = "fight_owner";
		break;
		case "fight_owner":
			LAi_SetOwnerTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
	}
}

string sRumourAboutOwners_CityRumour(string sCity, string sOwnerType) // Здесь идёт распределение по городам
{
	string sRetRumour = "Oh, seems like you've found a bug. Contact Jason and tell him about it, look for a 'Blackmark'.";
	// флаг - PChar.QuestTemp.RumoursAboutOwners.(sOwner) - для проверок, какой вопрос выпал. Ножно будет юзать для квестов
	switch(sCity)
	{
		case "Tortuga":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 0;
		break;
		
		case "PortRoyal":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 1;
		break;
		
		case "FortOrange":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 2;
		break;
		
		case "Beliz":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 3;
		break;
		
		case "PortoBello":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 4;
		break;
		
		case "Cartahena":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 5;
		break;
		
		case "Maracaibo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 6;
		break;
		
		case "Caracas":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 7;
		break;
		
		case "Cumana":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 8;
		break;
		
		case "SantaCatalina":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 9;
		break;
		
		case "SanJuan":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 10;
		break;
		
		case "Marigo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 11;
		break;
		
		case "Charles":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 12;
		break;
		
		case "SentJons":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 13;
		break;
		
		case "FortFrance":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 14;
		break;
		
		case "BasTer":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 15;
		break;
		
		case "Bridgetown":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 16;
		break;
		
		case "PortSpein":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 17;
		break;
		
		case "Havana":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 18;
		break;
		
		case "Villemstad":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 19;
		break;
		
		case "Santiago":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 20;
		break;
		
		case "PortPax":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 21;
		break;
		
		case "SantoDomingo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 22;
		break;
	}
	
	return sRetRumour;
}

string sRumourAboutOwners_Init(string sOwnerType, int iRumourNum) // База слухов жителей. Можно менять без новой игры
{
	
	string STR_MAYOR[MAX_RUMOURS_ABOUT_OWNERS]; // Губернаторы
	STR_MAYOR[0] = "Oh, sir governor is an excellent man. He manages our colony with great skill, never had a single conflict since the day of foundation\nHis only flaw is... he is... well... he is quite thrifty. It might be just another virtue though.";
	STR_MAYOR[1] = "Oh, sir governor is an excellent man. He manages our colony with great skill, never had a single conflict since the day of foundation\nHis only flaw is... he is... well... he is quite thrifty. It might be just another virtue though.";
	STR_MAYOR[2] = "Our governor is a good man but he is weak character. If he had a little firmness in his soul, our merchants could've got small tax breaks ... And it's already time to allocate subsidies for repairing the fort.";
	STR_MAYOR[3] = "Hmm ... He's recently become our governor. He is quite young and therefore very initiative. With him our colony is flourishing.";
	STR_MAYOR[4] = "Our governor is still relatively young. They say he is a good-for-nothing younger son of a Spanish count, sent far away from the yard to stop shaming his family. He has been appointed here quite recently, and didn't have time to create anything memorable.";
	STR_MAYOR[5] = "Hmm ... He's recently become our governor. He is quite young and therefore very initiative. With him our colony is flourishing";
	STR_MAYOR[6] = "Well... Nothing... I can't say anything bad about him...";
	
	string STR_TAVERNKEEPER[MAX_RUMOURS_ABOUT_OWNERS]; // Тавернщики
	STR_TAVERNKEEPER[0] = "Hm, I wouldn't trust my property to this rogue. Don't misunderstand me, but it seems to me that this is the most unreliable person in our town\nI heard he's working with pirates and smugglers whom often can be seen in his tavern.";
	STR_TAVERNKEEPER[1] = "What can we say about him! Cowardly, also not the smartest person I know. Besides, he is greedy for money, which is why he constantly gets into various troubles! But he is always up to date with all the news.";
	STR_TAVERNKEEPER[2] = "Quite a pleasant guy. It is always nice spending time in his tavern, he also got a great sense of humor. The most important thing about him is that he keeps a tavern in order and prevents drunk lowlifes from pestering good citizens.";
	STR_TAVERNKEEPER[3] = "Incredible man. He shouldn't keep a tavern but should be an informant for intelligence office. Sometimes it seems that he knows literally everything that happens in our town. It even scares me.";
	STR_TAVERNKEEPER[4] = "I don't know what to tell you. A man. Keeps a tavern. Knows everything about the town and its citizens.";
	STR_TAVERNKEEPER[5] = "They say that one can rely on it. On the other hand, I heard that he doesn't like unnecessary risk and always careful in doing his business. Yes, and dark affairs is not his type of business.";
	STR_TAVERNKEEPER[6] = "He's got the tavern from his father. His father kept a tavern not far from here, on the island of Highrock on another archipelago. Then his father moved here, built a new tavern here, and now his son runs it..";
	
	string STR_SHIPYARDER[MAX_RUMOURS_ABOUT_OWNERS]; // Верфисты
	STR_SHIPYARDER[0] = "Builds ships. I dunno. He's a quiet and peaceful. I guess, he's a good man.";
	STR_SHIPYARDER[1] = "Builds ships. I dunno. He's a quiet and peaceful. I guess, he's a good man.";
	STR_SHIPYARDER[2] = "A good man, but they say that he is too harsh. Constantly scolds all employees. Therefore, they often leave. Still, in spite of this, he is an excellent shipbuilder.";
	STR_SHIPYARDER[3] = "He is a very educated person. I heard that he studied shipbuilding in England, then in Holland. And in the end, he ended up here - far from the metropolis, in the provincial archipelago\nPeople say that he had troubles with the Holy Inquisition, and he had to flee to the colony.";
	STR_SHIPYARDER[4] = "This old man has to retire already and give the road for some fresh blood. He constantly dreams of past times, and grumbles when someone orders something from him besides caravels or galleons.";
	STR_SHIPYARDER[5] = "Great lad. Always willing to help. I have to say, he builds fine ships for such a shithole like this place.";
	STR_SHIPYARDER[6] = "He was a prisoner, exiled from Europe to our colony until it turned out that he had a talent for shipbuilding. After two magnificent brigs had been built under his leadership at the shipyard of our colony, he was forgiven for his transgressions, and now he is a full member of our society.";
	
	string STR_TRADER[MAX_RUMOURS_ABOUT_OWNERS]; // Магазинщики
	STR_TRADER[0] = "I can't say anything bad about him. A decent citizen, often visits our chapel. People seem to like him. Never heard of anyone being angry at him.";
	STR_TRADER[1] = "He is the main supplier of our governor, and this gives him a good income. But he conducts his affairs honestly. Well, at least he hasn't been noticed in anything shaming for him.";
	STR_TRADER[2] = "This fat man has a big respect in our city. His goods are always excellent, and I don't remember a single case he has ever cheated someone.";
	STR_TRADER[3] = "He's good-for-nothing, really. Trades, but no sense. Sometimes one good is out of stock, sometimes another, sometimes a half of goods... He can't even get himself out of debts.";
	STR_TRADER[4] = "He is not a good man, monsieur. I heard that he was Piere Thiers's right hand, previous trader, but he ruined his business it and then bought the store. I don't know how about the quality of the goods that he sells, but as a person he is very unpleasant to me.";
	STR_TRADER[5] = "Oh! He is an ugly man, I wouldn't advise you to have any business with him\nHe keeps a half of the inhabitants of our city in debt! And the goods those are sold in his store are always of poor quality.";
	STR_TRADER[6] = "Nobody really knows anything about him. He has recently moved here, and immediately opened his business. Trades honestly, wasn't caught at smuggling.";
	
	string sTempMayor = STR_MAYOR[iRumourNum];
	string sTempTavernkeper = STR_TAVERNKEEPER[iRumourNum];
	string sTempShipyarder = STR_SHIPYARDER[iRumourNum];
	string sTempTrader = STR_TRADER[iRumourNum];
	
	if(sOwnerType == "Mayor") return sTempMayor;
	if(sOwnerType == "TavernKeeper") return sTempTavernkeper;
	if(sOwnerType == "ShipYarder") return sTempShipyarder;
	if(sOwnerType == "Trader") return sTempTrader;
}

string GetDeviceLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.locationId") || CheckAttribute(pchar, "GenQuest.SeekSpy.Location")) //если взят квест по доставке малявы или шпиона
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != pchar.GenQuest.SeekSpy.Location)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != pchar.GenQuest.SeekSpy.Location && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2" && arCommon.name != "reload1") // mitrokosta fix
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	else
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2" && arCommon.name != "reload1") // mitrokosta fix
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[hrand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); //открываем дверь
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId) 
		{			
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}
