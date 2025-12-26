// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Konuş, dinliyorum";
			link.l1 = "Yanılmışım. Hoşça kal.";
			link.l1.go = "Exit";
			//искушение барбазона
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.Prison"))
            { 
                link.l1 = "Simon Morelle burada tutuklu. Birkaç gün önce devriye tarafından şilebi batırılan bir kaçakçı. Onu görebilir miyim?";
                link.l1.go = "BarbTemptation";
				DeleteAttribute(pchar, "questTemp.Saga.BarbTemptation.Prison");
            }
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "way_div")
			{
				link.l1 = "Memur bey, buraya Philipsburg valisi tarafından gönderildim. Adada ve çevresindeki sularda İngiliz casuslarını aramamı istedi. Ekselansları ayrıca bana faydalı bilgiler verebileceğinizi söyledi.";
				link.l1.go = "FMQN";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "way_div_2")
			{
				link.l1 = "Subay, kayıp devriyeyi buldum. Ayrıca İngiliz casuslarını da buldum. Onlar burada, adada.";
				link.l1.go = "FMQN_3";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "hol_peace_rew")
			{
				link.l1 = "Yine ben, memur bey. Casusları yakaladınız mı?";
				link.l1.go = "FMQN_8";
			}
		break;
		
		//искушение барбазона
		case "BarbTemptation":
			dialog.text = "Ve neden ona ihtiyacınız var, efendim?";
			link.l1 = "Ona lanet olası bir piç ve alçak olduğunu söylemek istiyorum. Umarım darağacında dururken işine yarar.";
			link.l1.go = "BarbTemptation_1";
		break;
		
		case "BarbTemptation_1":
			dialog.text = "Ha-ha! Mizah anlayışınız var, efendim... Peki, iki bin peso öderseniz devam edebilirsiniz.";
			if(sti(Pchar.money) >= 2000)
			{
				link.l1 = "Alın, subay. Teşekkür ederim!";
				link.l1.go = "BarbTemptation_2";
			}
			link.l2 = "Hm... Biliyor musun, fikrimi değiştirdim. Paramı meyhanede harcamayı tercih ederim.";
			link.l2.go = "BarbTemptation_4";
		break;
		
		case "BarbTemptation_2":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "Rica ederim... Yürüyün gidin!";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
		break;
		
		case "BarbTemptation_4":
			dialog.text = "Nasıl isterseniz, bir dahaki sefere böyle bir teklif alamazsınız.";
			link.l1 = "Buna zaten ihtiyacım yok. Görüşürüz, subay!";
			link.l1.go = "exit";
		break;
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN":
			DelLandQuestMark(npchar);
			dialog.text = "Faydalı mı? Ha! Bir dakika, bekle. Aslında sana faydalı bir şey söyleyebilirim. Devriyelerimizden biri ormanda kayboldu. Şimdiye kadar kışlalarına dönmeleri gerekiyordu, ama anlaşılan papağanlarla vakit geçirmeyi tercih ettiler. Ya da belki gerçekten bir şey oldu. Eğer aramalarında onları bulursan, gecikmeleri için düzgün bir bahane bulmalarını söyle, yoksa sonuçları hoşlarına gitmeyecek... Devriyenin komutanının adı Jannes Hoffman.";
			link.l1 = "Hepsi bu kadar mı, memur?";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "Evet, kahretsin. Üzgünüm, ama sana başka söyleyecek bir şeyim yok. İyi şanslar, kaptan.";
			link.l1 = "Teşekkür ederim...";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			DialogExit();
			pchar.questTemp.FMQN = "way_div_1";
			AddQuestRecord("FMQ_Nevis", "10");
			FMQN_SetSoldiersInCave();
		break;
		
		case "FMQN_3":
			DelLandQuestMark(npchar);
			dialog.text = "Ne?! Umarım şaka yapmıyorsun. Bana bir rapor ver!";
			link.l1 = "Ormanda bir mağaranın yakınında bir devriye ile karşılaştım. Beni durdurup nereye ve neden gittiğimi sordular, sonra da yoluma devam etmeme izin verdiler. Şaşırdım doğrusu, meğer onlar Hollanda üniforması giymiş İngilizlermiş! Ayrıca ormanda, çalılıkların arasında saklanmış bir grup çıplak adam gördüm. Sanırım İngiliz baskın ekibi devriyenizi silahsızlandırıp üniformalarını almış.";
			link.l1.go = "FMQN_4";
		break;
		
		case "FMQN_4":
			dialog.text = "...";
			link.l1 = "Anlayacağınız üzere, eğitimli kırmızı ceketlilerle çatışmaya girmeye cesaret edemedim, bu yüzden hemen size rapor vermeye koştum.";
			link.l1.go = "FMQN_5";
		break;
		
		case "FMQN_5":
			dialog.text = "Pekâlâ, pekâlâ... Bir mağara mı dedin? Kaç kişi saydın?";
			link.l1 = "Beş adam. Evet, sanırım o mağaraya girdiler.";
			link.l1.go = "FMQN_6";
		break;
		
		case "FMQN_6":
			dialog.text = "I am sending a squad to the cave immediately! Captain, if the men you met are really British spies, you will receive a well-deserved reward. You are free to join the squad if you wish to assist the authorities in detaining those bastards and receive an extra reward; these are the governor's orders, after all. So, are you coming along?";
			link.l1 = "Hayır, memur, casusları kovalamak senin işin. İyi silahlanmış bir ekip gönderdiğinden emin ol, bu pislikler fazlasıyla tehlikeli...";
			link.l1.go = "FMQN_7";
			link.l2 = "Bunu yapabilirim sanırım. Yardımım olursa adamlarınız casusları daha çabuk bulur.";
			link.l2.go = "FMQN_10";
		break;
		
		case "FMQN_7":
			dialog.text = "Senin seçimin, kaptan, tavsiyeni dikkate alacağım. Operasyonumuzun sonuçlarını öğrenmek için yarın yanıma gel.";
			link.l1 = "Yarın görüşürüz.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandPeace");
		break;
		
		case "FMQN_8":
			DelLandQuestMark(npchar);
			dialog.text = "Bilgileriniz doğruymuş, kaptan. O alçakları mağaranın içinde bulduk. Teslim olma niyetleri yoktu ve bizimle çatışmaya girdiler. Sonuç olarak, hepsini etkisiz hale getirdik. Kayıp devriyeyi de bulduk. Biraz hırpalanmış olsalar da, sağ ve iyi durumdalar... Tüm Philipsburg'un iyi vatandaşları adına size teşekkür ederim, kaptan. Gösterdiğiniz dikkat söz verildiği gibi ödüllendirilecek. Lütfen, bunu kabul edin.";
			link.l1 = "Teşekkür ederim!";
			link.l1.go = "FMQN_9";
		break;
		
		case "FMQN_9":
			AddMoneyToCharacter(pchar, 10000);
			dialog.text = "Sint Maarten'de her zaman hoş karşılanan bir misafirsiniz. Şimdi, lütfen beni mazur görün, ilgilenmem gereken başka işlerim var.";
			link.l1 = "Ben de. Hoşça kal.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandPeaceComplete");
		break;
		
		case "FMQN_10":
			dialog.text = "Pekala. Yardımınız için minnettarız. Şehir kapılarına gidin, ceza birliği bir saat içinde orada toplanacak.";
			link.l1 = "Sana küçük bir tavsiye, bu görev için elindeki en iyi askerleri göndermelisin. O casuslar tehlikelidir.";
			link.l1.go = "FMQN_11";
		break;
		
		case "FMQN_11":
			dialog.text = "Endişelenmeyin. Philipsburg'un usta kılıç ustası Subay Hans Shulte komutasında en deneyimli askerlerimizi gönderiyorum.";
			link.l1 = "Harika! O zaman hiç vakit kaybetmeyelim.";
			link.l1.go = "exit";
			WaitDate("",0,0,0,1,5);
			AddDialogExitQuestFunction("FMQN_HollandBattle");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
