// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
    int i, tempQty, chComp, iShip, iBaseType;
    string tempStr;
    switch (Dialog.CurrentNode)
	{
		case "quests":
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal.Villemstad") && pchar.location == "villemstad_townhall")
			{
				dialog.text = RandPhraseSimple("Ne tür sorular?","Ne istersiniz?");
				link.l1 = "Hollanda Batı Hindistan Şirketi'nin ünlü korsan Bartolomeo Portekizli'nin başına iyi bir ödül koyduğunu biliyorum. Onu yakalamayı başardım. Şu anda gemimin ambarında tutuluyor ve yetkililere teslim etmeye hazırım.";
				link.l1.go = "Portugal";
				break;
			}
            dialog.text = RandPhraseSimple("Ne tür sorular?","Ne istiyorsunuz?");
			link.l1 = RandPhraseSimple("Önemli bir şey yok, efendim.","Söyleyecek bir şeyim yok, özür dilerim.");
		    link.l1.go = "exit";
		break;
		
		case "work_1":  // работа на благо короны - линейка нации
			if (CheckAttribute(npchar, "notQuestLine"))
			{
                dialog.text = "Ne yazık ki, sana bir iş veremem. Şu anda birlikte çalışmak istediğim biri değilsin. Hoşça kal.";
                link.l1 = "Ciddi olamazsınız... ama peki, öyle olsun.";
                link.l1.go = "exit";
				break;
			}                   
		break;
		
		//Португалец
		case "Portugal":
			dialog.text = "Bart Portekizli mi?! Onu yakaladın mı? Canlı mı?";
			link.l1 = "Biliyorum, onu öldürmeni istemiyorsun. Hayatta. Onu hayatta tutmak için büyük çaba harcamak zorunda kaldım!";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Harika! Şimdi bize her şeyi anlatacak... Bayım, mahkumu nakle hazırlayın. Hemen geminize bir askeri barç göndereceğiz. ";
			link.l1 = "Öncelikle ödülümü konuşmak isterim, Efendim... Sakıncası yoksa.";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "Ödülünüz için endişelenmeyin, kaptan. Onu alacaksınız. Bartolomeo the Portuguese'nin başına bin beş yüz dublon ödül koyduk. Teğmen! Kaptana ödülünü getir!";
			link.l1 = "Hm... Demek ki Hugo bana iki bin dublon hakkında yalan söylemiş... Peki, öyle olsun.";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			TakeNItems(pchar, "gold_dublon", 1500);
			Log_Info("You have received 1500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ve şimdi, kaptan, Portekizliyi Şirkete teslim etme nezaketini gösterir misiniz? Onunla konuşmak için sabırsızlanıyoruz.";
			link.l1 = "Elbette, efendim, tekneyi gemime gönderin.";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			DialogExit();
			DoQuestReloadToLocation("Villemstad_town", "reload", "reload1", "Portugal_Final");
			DeleteAttribute(pchar, "questTemp.Portugal.Villemstad");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
