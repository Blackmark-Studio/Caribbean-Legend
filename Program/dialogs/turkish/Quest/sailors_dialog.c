// реплики солдат на палубе при разговоре в море
// форт-стража и комендант форта
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
        case "exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
        case "First time":
			dialog.text = "Kaptanımızla konuş. Sana söyleyecek bir şeyim yok.";
			Link.l1 = "Pekala.";
			Link.l1.go = "exit";
			
			NextDiag.TempNode = "first time";
		break;
		//  на палубе -->
		case "On_Deck":
			dialog.text = "Kaptanımızla konuş. Sana söyleyecek bir şeyim yok.";
			Link.l1 = "Pekala.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Deck";
/*			
			// Первый церковный генератор
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern"))
			{
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"))
				{
					dialog.text = "Beyefendi, birini mi arıyorsunuz?";
					Link.l1 = "Evet, dostum. Kaptanı görebilir miyim?";
					Link.l1.go = "ChurchQuest1_Node1";
				}
				else
				{
					dialog.text = "Eğer kaptanımızı arıyorsanız, o yakın zamanda karaya çıktı.";
					Link.l1 = "Pekâlâ";
					Link.l1.go = "exit";
				}
				break;
			}
*/			
			//--> eddy. квест мэра, закрываем выход с палубы и ноду даем нужную
			if (CheckAttribute(pchar, "GenQuest.DestroyPirate") && pchar.GenQuest.CaptainId == "MQPirate")
			{
	    		dialog.text = RandPhraseSimple("Ah, buraya tek başına gelmişsin. Ha! O halde kaptanımıza git. Ona yaptığın rezillikleri anlat...","Vay canına, galiba delirmişsin dostum. Kaptanımıza git, seninle konuşacak.");
				Link.l1 = "Ne yazık...";
				Link.l1.go = "exit";
			}
			//<-- eddy. квест мэра, закрываем выход с палубы
		break;
/*		
		case "ChurchQuest1_Node1":
			dialog.text = "Onu limanda arasan iyi edersin.";
			Link.l1 = "Teşekkür ederim, dostum.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "On_Deck";
			PChar.GenQuest.ChurchQuest_1.CapWaitOnTavern = true; 
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"); // Не спрашиваем моряков
		break;
*/		
        //  на палубе <--
				
		// ugeen --> разговор с боцманом по генератору "Повод для спешки"
		case "On_MyShip_Deck":
			dialog.text = "Vay be, bu tam bir karmaşaydı, kaptan! Her zamanki gibi meyhanede içiyorduk, birden çığlıklar duyduk. Meyhaneden dışarı koştuk ve seni tutuklamaya çalıştıklarını gördük. Kahretsin onları! Biz de bu dostça olmayan limandan ayrılmaya karar verdik.";
			link.l1 = "Evet, bazı insanların adalet anlayışı gerçekten tuhaf.";
			link.l1.go = "On_MyShip_Deck_1";
		break;
		
		case "On_MyShip_Deck_1":
		    if(pchar.questTemp.ReasonToFast == "speakSuccess_chain_A") 
			{
				// карты не было
				dialog.text = "Kaptan! Böyle telaş yapma! Sessizce kaçmanın imkânsız olduğu belliydi, bu yüzden yerel bankere uğrayıp kasalarını kontrol etmeye karar verdik. İşte payınız - "+sti(pchar.questTemp.ReasonToFast.p9)+" pesos...";
			}
			if(pchar.questTemp.ReasonToFast == "speakSuccess_chain_B")
			{
				// карту отобрали
				GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
				dialog.text = "Kaptan! Bu kadar telaşlanma! Sessizce kaçmanın imkânsız olduğu belliydi, bu yüzden yerel bankacıya uğrayıp kasalarını kontrol etmeye karar verdik. Rehin kutusunda güzel bir kılıç da vardı. İşte payınız - "+sti(pchar.questTemp.ReasonToFast.p9)+" peso ve bir kılıç...";
			}		
			link.l1 = "Aferin çocuklar! Aferin! Sizinle gurur duyuyorum.";
			link.l1.go = "On_MyShip_Deck_End";
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.ReasonToFast.p9));			
			pchar.Ship.Crew.Morale = MORALE_MAX;
			chrDisableReloadToLocation = false; // Откроем выход
			AddQuestRecord("ReasonToFast", "17");		
			AddQuestUserData("ReasonToFast", "sSex", GetSexPhrase("",""));		
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"TownEscape");
			DeleteAttribute(pchar,"questTemp.ReasonToFast");
			QuestOpenSeaExit();
		break;
		
		case "On_MyShip_Deck_End":
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		// разговор с боцманом по генератору 'Операция Галеон'
		case "CapComission_OnShipDeck":
			dialog.text = "Kaptan, arkadaşınız kaçtı.";
			link.l1 = "Hangi arkadaş?";
			link.l1.go = "CapComission_OnShipDeck1";
		break;
		
		case "CapComission_OnShipDeck1":
			dialog.text = "Pekala, zindanlardan çıkardığın o arkadaş.";
			link.l1 = "Onu nasıl oldu da kaybettin, söylesene?!";
			link.l1.go = "CapComission_OnShipDeck2";
		break;
		
		case "CapComission_OnShipDeck2":
			dialog.text = "Bizim suçumuz değildi, Kaptan. Tuvaletten denize atladı... Ona ateş etmeye çalıştık ama orası çok karanlıktı...";
			link.l1 = "Lanet olsun! Gerçekten kontrolden çıktınız! Hepinizi karaya çıkarıp şeker kamışı tarlalarında çalışmaya göndereceğim! Böyle değerli bir adamı kaybetmek mi? İnanılır gibi değil!";
			link.l1.go = "CapComission_OnShipDeck3";
		break;
		
		case "CapComission_OnShipDeck3":
			chrDisableReloadToLocation = false; // Откроем выход
			AddQuestRecord("CaptainComission2", "25");	
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));			
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");	
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputationABS(pchar, "authority", 1);
			DeleteAttribute(pchar,"TownEscape");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.canSpeakBoatswain");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			QuestOpenSeaExit();		
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		// <-- ugeen
		
		// разговор с боцманом по ситуациям в трюме
		case "Hold_GenQuest_OnShipDeck":
			dialog.text = "Kaptan, affedin bizi, bizim hatamızdı – mahkum kaçtı.";
			link.l1 = "Hangi mahkum? Kim kaçtı?";
			link.l1.go = "Hold_GenQuest_OnShipDeck1";
		break;
				
		case "Hold_GenQuest_OnShipDeck1":
			dialog.text = "Ah, şey, adını unuttum, "+pchar.GenQuest.Hold_GenQuest.CapName+", değil mi?";
			link.l1 = "Kahretsin! Nereye bakıyordun?";
			link.l1.go = "Hold_GenQuest_OnShipDeck2";
		break;
		
		case "Hold_GenQuest_OnShipDeck2":
			dialog.text = "Ambarın içinden çıktı ve bordadan atladı. Gürültü olmasın diye ateş etmedik, biz sandalı hazırlarken o lanet balıkçılar tarafından kurtarıldı.";
			link.l1 = "Ve neden sana para ödüyorum! Nöbet başını kırbaçlayın ve bir hafta romdan mahrum bırakın. Yerlerinize geçin! Demir alıyoruz...";
			link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;
		
		case "Hold_GenQuest_OnShipDeck3":
			chrDisableReloadToLocation = false; // Откроем выход
			sld = characterFromId(pchar.GenQuest.Hold_GenQuest.CapId);
			ReleasePrisoner(sld);			
			CloseQuestHeader("HoldQuest");	
			DeleteAttribute(pchar, "TownEscape");
			DeleteAttribute(pchar, "GenQuest.Hold_GenQuest.canSpeakSailor");
			DeleteAttribute(pchar, "GenQuest.Hold_GenQuest");
			QuestOpenSeaExit();					
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		case "Hold_GenQuest_OnShipDeck4":
			dialog.text = "Selamlar, kaptan. Hiçbir kaza yaşanmadı sizin...";
			link.l1 = "Peki, peki, anladım.... Ambarımızda bir mahkum var. Adı "+pchar.GenQuest.Hold_GenQuest.CapName+" . Birkaç adam al ve onu limana kadar götür. Artık özgür.";
			link.l1.go = "Hold_GenQuest_OnShipDeck5";
		break;
		
		case "Hold_GenQuest_OnShipDeck5":
			dialog.text = "Gerçekten serbest mi? Onu bir sandalla mı götüreceğiz?";
			link.l1 = "Hayır, lanet olası bir kaplumbağada... Yeterince açık olduğumu sanıyordum. Ve acele et! Gelgit başlamadan demir almamız lazım.";
			link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;
		
		// Warship 09.07.09 Базар с нашим матросом на палубе Мэри Селест -->
		case "On_MaryCeleste_Deck":
			Dialog.text = "Kaptan, gemide tek bir canlı yok! Burada bir gariplik var... Tommy, kokpitte bir kedi gördüğünü söyledi ve o, gördüğü tek canlıydı...";
			Link.l1 = "Aptal, kedilerin ruhu olmaz. Görünen o ki, uzun zamandır kiliseye gitmemiş, belki de hiç gitmemiştir. Kaptanın kamarasına baktın mı? Seyir defterine ihtiyacım var.";
			Link.l1.go = "On_MaryCeleste_Deck_1";
		break;
		
		case "On_MaryCeleste_Deck_1":
			Dialog.text = "Hayır, ruhları var. Ne bir seyir defteri vardı, ne de tek bir seyir aleti. Hatta bir sandal bile yoktu...";
			Link.l1 = "Hayır, kovulmadı. Bir fırtına mı sürükledi onu?";
			Link.l1.go = "On_MaryCeleste_Deck_2";
		break;
		
		case "On_MaryCeleste_Deck_2":
			Dialog.text = "Yaparlar, Kaptan. Kedilerin ruhu vardır. Kaptan, filika kesilmiş ve kokpitin zemininde bir kılıç bulduk. Paslı ve kanlı. Buyurun, bir bakın...";
			Link.l1 = "Bana bu saçmalıkları bırak, at gitsin ve kedilerden bahsetmeyi kes, yeter artık! Ambarı kontrol edelim ve gidelim... Ah, burada bir tuhaflık var ve hiç hoşuma gitmedi...";
			Link.l1.go = "On_MaryCeleste_Last";
			NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;
		
		case "On_MaryCeleste_Last":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetCitizenType(NPChar); // Чтоб по палубе ходил
			
			NPChar = GetRealShip(GetCharacterShipType(CharacterFromID("MaryCelesteCapitan")));
			NPChar.TurnRate = sti(PChar.QuestTemp.MaryCeleste.TurnRate); // Вернем манёвренность, для интерфейса
			
			chrDisableReloadToLocation = false; // Откроем выход
			
			LaunchTransferMain(PChar, CharacterFromID("MaryCelesteCapitan"), "MaryCelesteTransfer");
		break;
		
		case "On_MaryCeleste_Deck_SailorLast":
			switch(rand(2))
			{
				case 0:
					Dialog.text = "Kaptan, bu yer hakkında kötü bir his var içimde... Belki de gitme vakti gelmiştir?";
					Link.l1 = "Evet... Geminin sandalına git.";
					Link.l1.go = "exit";
				break;
				
				case 1:
					Dialog.text = "Kaptan, eğer bu garip gemiyi limana götürmeyi düşünüyorsan, burada kalmam. Kendimi denize atmayı tercih ederim.";
					Link.l1 = "Bunu yapmak istemiyorum... Ayrıca biraz korkuyorum...";
					Link.l1.go = "exit";
				break;
				
				case 2:
					Dialog.text = "Belki de batıralım, Kaptan?";
					Link.l1 = "Burada yaşayan ölü denizcilerin ruhlarının kabuslarımızda bizi ziyaret etmesine izin vermek için mi?";
					Link.l1.go = "On_MaryCeleste_Deck_SailorLast_1";
				break;
			}
			
			NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;
		
		case "On_MaryCeleste_Deck_SailorLast_1":
			Dialog.text = "Aman Tanrım, hayır! Kaptan... neden böyle söylüyorsunuz?";
			Link.l1 = "Korkma, şaka yapıyordum... Şimdi filikaya git. Ve sanırım haklısın, belki de kedilerin gerçekten ruhu vardır...";
			Link.l1.go = "exit";
		break;
		// <-- Базар с нашим матросом на палубе Мэри Селест
		
        //  на палубе <--
        case "On_Fort":
			dialog.text = RandPhraseSimple("Patronla konuş. Sana söyleyecek bir şeyim yok.","Yerimdeyim. Tüm sorular kale komutanına yöneltilmeli.");
			Link.l1 = "Pekala.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Fort";
		break;
		
		case "On_Fort_Head":
			dialog.text = RandPhraseSimple("Şu anda gerçekten meşgulüm. Beni rahat bırak.","Beni işimden alıkoyma. Konuşacak bir şey yok.");
			Link.l1 = "Yazık...";
			Link.l1.go = "exit";

			NextDiag.TempNode = "On_Fort_Head";
		break;
		
		case "Morgan_wait_you":
			Dialog.defAni = "dialog_stay1";
			Dialog.defCam = "1";
			Dialog.defSnd = "dialogs\0\017";
			Dialog.defLinkAni = "dialog_1";
			Dialog.defLinkCam = "1";
			Dialog.defLinkSnd = "dialogs\woman\024";
			Dialog.ani = "dialog_stay2";
			Dialog.cam = "1";
			Dialog.snd = "dialogs\0\009";

			dialog.text = RandPhraseSimple("Morgan sana 'bir iki şey' söylemek istedi... O burada bir yerde, güvertede.","Heh, Morgan'ı bul. Kötü haberler seni bekliyor...");
			Link.l1 = "Pekala.";
			Link.l1.go = "exit";

			NextDiag.TempNode = "Morgan_wait_you";
		break;
	}
}
