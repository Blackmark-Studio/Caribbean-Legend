// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne istiyorsunuz? Sorunuzu sorun.","Dinliyorum, sorun nedir?"),"Bu ikinci kez sormaya çalışıyorsunuz...","Bu, üçüncü kez sormaya çalıştığınız sefer...","Bu ne zaman bitecek?! Ben sömürge işleriyle meşgul, yoğun bir adamım ve sen hâlâ beni rahatsız ediyorsun!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim, üzgünüm.","Şimdi değil. Yeri ve zamanı değil."),"Doğru, şu anda söyleyecek bir şeyim yok, üzgünüm.","Daha sonra soracağım.","Üzgünüm, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal.Villemstad"))
			{
				link.l1 = "Hollanda Batı Hindistan Şirketi'nin, bir korsanın - Portekizli Bartolomeo'nun - başına ödül koyduğunu biliyorum. Onu yakalamayı başardım. Şu anda gemimin ambarında tutuyorum ve yetkililere teslim etmeye hazırım.";
                link.l1.go = "Portugeze";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("Zaten her şeyi aldınız. Daha ne istiyorsunuz?","Almadığın bir şey kaldı mı?");
            link.l1 = RandPhraseSimple("Sadece etrafa bakıyorum...","Sadece kontrol ediyorum, belki bir şeyi almayı unutmuşumdur...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		//Португалец
		case "Portugeze":
			dialog.text = "Bart Portekizli mi?! Onu canlı mı yakaladınız?!";
			link.l1 = "Biliyorum, ölü olarak sana hiçbir faydası yok. Hayatta, ve Tanrılar beni kahretsin, onu o halde tutmak için kendimi zor tuttum!";
			link.l1.go = "Portugeze_1";
		break;
		
		case "Portugeze_1":
			dialog.text = "Harika! Şimdi bize her şeyi anlatacak... Mösyö, mahkûmu nakle hazırlayın. Geminize hemen bir askeri barç göndereceğiz. ";
			link.l1 = "Ödülüm hakkında önce konuşmak isterim, Efendim, eğer sakıncası yoksa.";
			link.l1.go = "Portugeze_2";
		break;
		
		case "Portugeze_2":
			dialog.text = "Ödülünüz için endişelenmeyin, Efendim. Onu alacaksınız. Bartolomeo Portekizli'nin başına bin beş yüz dublon ödül koyduk. Teğmen! Kaptana ödülünü getirin!";
			link.l1 = "Hm... Hugo bana iki bin dublon demişti... Peki öyleyse.";
			link.l1.go = "Portugeze_3";
		break;
		
		case "Portugeze_3":
			TakeNItems(pchar, "gold_dublon", 1500);
			Log_Info("You have received 1500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ve şimdi, efendim, Portekizliyi Şirkete teslim etme nezaketini gösterir misiniz? Onunla konuşmak için sabırsızlanıyoruz.";
			link.l1 = "Elbette, Efendim, barkı gemime gönderin.";
			link.l1.go = "Portugeze_4";
		break;
		
		case "Portugeze_4":
			DialogExit();
			DoQuestReloadToLocation("Villemstad_town", "reload", "reload1", "Portugal_Final");
			DeleteAttribute(pchar, "questTemp.Portugal.Villemstad");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
