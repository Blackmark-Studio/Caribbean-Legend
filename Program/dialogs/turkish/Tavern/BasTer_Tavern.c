// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hangi sorularınız var?","Size nasıl yardımcı olabilirim, "+GetAddress_Form(NPChar)+"?"),"Ne oldu, "+GetAddress_Form(NPChar)+"...","Bu üçüncü kez beni rahatsız ediyorsun artık...","Sanırım daha fazla sorunuz var?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Ah, hafızam nereye kayboldu böyle...","Evet, gerçekten de üçüncü kez...","Hayır, ne soruları?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin"))
			{
				link.l1 = "Eski dostum Fernand Luc'u arıyorum. Ona birkaç sorum var. Bir hafta önce burada epey vakit geçirdiğini duydum...";
				link.l1.go = "terrapin";
			}
			//Sinistra Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerTavern"))
			{
				link.l1 = "Arkadaşımla burada buluşmak üzere sözleştik, ama onu hiçbir yerde göremiyorum. Nerede olduğunu biliyor musunuz? Hâlâ şehirde mi, yoksa en azından adada mı? Adı Longway – Çinli.";
				link.l1.go = "PZ_BasTerTavern_1";
			}
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_2"))
			{
				link.l2 = "Güzel haberler, "+npchar.name+" . Durumunuzu kurtaracak tam olarak ihtiyacınız olan şey bende var. Yüz şişe enfes şarap ve yüz şişe rom. Böyle bir sevkiyatla müşterileriniz yine içki nehirlerinde yüzecek. Ödemeye hazır mısınız?";
				link.l2.go = "TPZ_Tavern2_1";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_3"))
			{
				link.l2 = "Pekala, "+npchar.name+", anlaşmanın şartlarını konuşmaya hazır mısın?";
				link.l2.go = "TPZ_Tavern2_11";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_4"))
			{
				link.l2 = "Peki, "+npchar.name+" . Benim tarafımda her şey halledildi ve mallar çoktan meyhaneye doğru yola çıktı. Ödemeye geçelim mi?";
				link.l2.go = "TPZ_Tavern3_1";
			}
			//<-- Торговля по закону
		break;
		
		//суп из черепахи
		case "terrapin":
			dialog.text = "Cehennemde bile hâlâ keyif çatıyor olabilir. Dostun öldü, bu yüzden biraz geç kaldın, kaptan. Şurada, en köşedeki masada oturan adam cenazesinin parasını ödedi, ama nedense o cenazeye sebep olanın da o olduğunu düşünüyorum. Suratında darağacı havası var, derler ya. Adı Robert Martene. İstersen gidip kendin sorabilirsin. ";
			link.l1 = "Sağ ol dostum. Gidip Mösyö Robert'le konuşacağım. Zavallı yaşlı Luc'un ruhuna içeceğiz, huzur içinde yatsın...";
			link.l1.go = "terrapin_1";
			npchar.quest.terrapin = "true";
		break;
		
		case "terrapin_1":
			DialogExit();
			AddQuestRecord("Terrapin", "4");
			pchar.questTemp.Terrapin = "rober";
		break;
		
		// Sinistra - Квест "Длинные тени старых грехов" ==>
		case "DTSG_BasTerTavern_1":
			dialog.text = "Ne konuşulacak ki? O, seni ve arkadaşını saldırdı, sen de karşılık verdin, bunu neredeyse her gün görüyorum. İyi iş çıkardın. Şimdi bana sadece bu karmaşayı temizlemek kaldı...";
			Link.l1 = "Bunu temizlersin, artık alışmışsındır. Onun hakkında ne biliyorsun?";
			Link.l1.go = "DTSG_BasTerTavern_2";
		break;
		
		case "DTSG_BasTerTavern_2":
			dialog.text = "Pek bir şey yok aslında. Birkaç gün önce geldi. Burasını sevdi, hatta kasabanın dışında bir ev kiraladı. Sık sık uğrardı, ödemelerini de düzenli yapardı. Ve en önemlisi, bu süre boyunca hep düzgün davrandı, kimseye kötü bir laf etmedi. Sizi ve arkadaşınızı saldırdığına hâlâ inanamıyorum.   Buraya temelli yerleşir diye düşünmüştüm.";
			Link.l1 = "Bir bakıma, yaptı. Pek bir şey değil ama yine de teşekkür ederim dostum. Görüşürüz.";
			Link.l1.go = "exit";
			AddDialogExitQuestFunction("DTSG_BasTerTavern_3");
		break;
		// <== Квест "Длинные тени старых грехов" - Sinistra
		
		// Sinistra - Квест "Путеводная звезда" ==>
		
		case "PZ_BasTerTavern_1":
			dialog.text = "Bu isim bana hiçbir şey ifade etmiyor ve genellikle onun gibi insanları mekânıma almam, onlarla da ilgilenmem.";
			Link.l1 = "Pekala. Tamam, sonra görüşürüz.";
			Link.l1.go = "PZ_BasTerTavern_2";
		break;
		
		case "PZ_BasTerTavern_2":
			DialogExit();
			bDisableLandEncounters = true;
			DeleteAttribute(pchar, "questTemp.PZ_BasTerTavern");
			DeleteAttribute(pchar, "questTemp.PZ_BasTerAlkash");
			pchar.questTemp.PZ_BasTerTavern2 = true;
			DeleteQuestCondition("PZ_BasTer_Opozdal");
			DelMapQuestMarkIsland("Guadeloupe");
			
			PChar.quest.PZ_BasTer_Strazha.win_condition.l1 = "location";
			PChar.quest.PZ_BasTer_Strazha.win_condition.l1.location = "BasTer_town";
			PChar.quest.PZ_BasTer_Strazha.win_condition = "PZ_BasTer_Strazha";
		break;
		
		// <== Квест "Путеводная звезда" - Sinistra
		
		//--> Торговля по закону
		case "TPZ_Tavern_1":
			dialog.text = "Oh, "+GetAddress_Form(NPChar)+", durum bundan da kötü. Antigua’daki tedarikçim damıtımevini kaybetti — korsanlar basmış, her şey kül olmuş. Şimdi en az iki ay boyunca rom ya da şarap beklemememiz gerektiğini söylüyor.";
			link.l1 = "O zaman yeni bir tedarikçi bul. İki ay boyunca öylece oturup bekleyecek değilsin herhalde, değil mi?";
			link.l1.go = "TPZ_Tavern_2";
		break;
		
		case "TPZ_Tavern_2":
			dialog.text = "Güvenilir bir tedarikçi bulmak kolay değil. Küçük tüccarlarla çalışmayı denedim, ama güvenilir değiller. Bazen mallar gelir, bazen gelmez. Büyük bir tedarikçiyle ise her şey saat gibi işler — teslimatlar düzenli, kalite yüksek.";
			link.l1 = "Normal tedarikçiler sorun oluyorsa, belki de gölgelerde birini aramalısınız? Onlar nadiren sizi yarı yolda bırakır, malları da her zaman ellerinde olur.";
			link.l1.go = "TPZ_Tavern_3";
		break;
		
		case "TPZ_Tavern_3":
			dialog.text = "Anlıyorsun, "+GetAddress_Form(NPChar)+",   bu meyhane şu anda herkesin gözü önünde. Yetkililerle başımın belaya girmesini istemem. Eğer itibarlı biri bu malları getirseydi, sadece bir kısmını almakla kalmaz, nereden geldiğine de göz yumardım\nSonuçta, işler bu kadar kötüye gitmişken kim böyle önemsiz şeylerle ilgilenir? Asıl mesele şüphe çekmemek. Ama uzun vadede, sadece ciddi ve dürüst tüccarlarla iş yaparım.";
			link.l1 = "Anladım. Belki daha sonra tekrar uğrarım. Akıllıca bir yaklaşımla her sorun çözülebilir.";
			link.l1.go = "TPZ_Tavern_4";
		break;
		
		case "TPZ_Tavern_4":
			DialogExit();
			AddQuestRecord("TPZ", "2");
			pchar.questTemp.TPZ_ContraInfo = true;
			AddLandQuestMark(characterFromId("BasTer_Smuggler"), "questmarkmain");
		break;
		
		case "TPZ_Tavern2_1":
			dialog.text = "Kaptan, bu inanılmaz! Bunu nasıl başardınız? Gerçi, önemli değil. Söyleyin bana, bu kadar lüks bir içki sevkiyatı karşılığında ne istiyorsunuz? Ve evraklarda her şey yolunda olacak mı?";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "Evraklar mı? Elbette hepsi tamamen düzgün. Gerçekten kontrol etmeyi düşünmüyorsun, değil mi?";
				link.l1.go = "TPZ_Tavern2_2";
				Notification_Reputation(true, 40, "low");
			}
			else
			{
				link.l1 = "Evrak işleri mi?";
				link.l1.go = "TPZ_Tavern2_2_badrep";
				Notification_Reputation(false, 40, "low");
			}
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_2");
			DelLandQuestMark(npchar);
		break;
		
		case "TPZ_Tavern2_2_badrep":
			dialog.text = "Kaptan, lütfen anlayın, bu alkol sevkiyatını almam benim için çok önemli. Ama özgürlüğüm ve itibarım da en az bunun kadar değerli. Vali, kaçakçılara karşı acımasızdır, en küçüklerine bile. Eğer insanlar sizin için iyi konuşsaydı, evrak eksikliğine göz yumabilirdim, ama şu anda... üzerinize fazla dikkat çekiyorsunuz...";
			link.l1 = "Görünüşe bakılırsa biraz iyi iş yapmanın zamanı geldi. Beni bekle, yakında döneceğim.";
			link.l1.go = "exit";
			pchar.questTemp.TPZ_Tavern_3 = true;
		break;
		
		case "TPZ_Tavern2_2":
			dialog.text = "Bu sefer sana güveneceğim sanırım. Peki, bu parti için ne kadar istiyorsun?";
			link.l1 = "Her on şişe şarap için otuz dublon, her on şişe rom içinse beş dublon isterim. Tüm parti — yani her birinden yüz şişe — sana toplam üç yüz elli dublona mal olur.";
			link.l1.go = "TPZ_Tavern2_3";
		break;
		
		case "TPZ_Tavern2_3":
			dialog.text = "Dur hele, Kaptan! Bu bildiğin soygun! Evet, durumum vahim ama zararına iş yapacak değilim!";
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 50)
			{
				link.l1 = "Belki sana bir indirim yapabilirim. Ama hepsi bu kadar değil. Senin düzenli tedarikçin olmak istiyorum. Sorunsuz ve zamanında teslimat garantisi veriyorum. Basse-Terre'de bir depo kiralayacağım ve stokun oradan doğrudan, gecikmeden gelecek. Her zaman yeterince içki depolanmış olacak, böylece hiçbir zaman eksik kalmayacaksın. İndirimle birlikte fiyat iki yüz kırk dublon olacak. Ne dersin?";
				link.l1.go = "TPZ_Tavern2_4";
				Notification_Skill(true, 50, SKILL_COMMERCE);
			}
			else
			{
				link.l1 = "Pekâlâ, fiyatı sevkiyat başına iki yüz kırk dublona indirmeye hazırım — uzun vadeli bir ortaklık hedefliyorum. Gelecekte tüm ihtiyaçlarınızı karşılayabilir ve güvenilir bir tedarik sağlayabilirim. Ne dersiniz?";
				link.l1.go = "TPZ_Tavern2_7";
				Notification_Skill(false, 50, SKILL_COMMERCE);
			}
		break;
		
		case "TPZ_Tavern2_4":
			dialog.text = "Bu yine de eskiden ödediğimden fazla. Ama dersimi aldım — istikrarın bir bedeli var. Şartlarını kabul ediyorum, ama şunu bil: en ufak bir hata olursa, başka bir tedarikçi bulurum. Fazladan neye para verdiğimi anlamam gerek. Bir de — yetkililerle nasıl başa çıkmayı düşünüyorsun?";
			link.l1 = "Bunu hemen halledeceğim. Her şey yoluna girdikten sonra mallarla geri döneceğim.";
			link.l1.go = "TPZ_Tavern2_5";
		break;
		
		case "TPZ_Tavern2_5":
			dialog.text = "Lütfen gecikmeyin. Müşterilerimin kupalarının tekrar dolmasını sabırsızlıkla bekliyorum.";
			link.l1 = "Merak etme, seni bekletmeyeceğim.";
			link.l1.go = "TPZ_Tavern2_6";
		break;
		
		case "TPZ_Tavern2_6":
			DialogExit();
			AddQuestRecord("TPZ", "5");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_3");
			AddLandQuestMark(characterFromId("BasTer_Mayor"), "questmarkmain");
			pchar.questTemp.TPZ_guber_1 = true;
			pchar.questTemp.TPZ_Vino240 = true;
			
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
	    case "TPZ_Tavern2_7":
			dialog.text = "Hâlâ çok pahalı, Kaptan. Bu fiyat, önceki tedarikçime ödediğimden daha yüksek. Şimdi kabul etsem bile, birkaç ay sonra üretim başlayınca yine ona döneceğim. Fazladan para ödemek için bir sebep göremiyorum.";
			link.l1 = "Anladım. Peki. Son teklifim — iki yüz dublon. Eğer bu kabul edilemezse, bu konuşmayı sürdürmenin bir anlamı yok.";
			link.l1.go = "TPZ_Tavern2_8";
		break;
		
		case "TPZ_Tavern2_8":
			dialog.text = "Pekâlâ, anlaştık. İki yüz kabul edilebilir. Ama söyle bakalım, adanın yetkilileriyle nasıl başa çıkmayı düşünüyorsun? Daha önce de söyledim, vali kaçakçılık konusunda adayı sıkı denetliyor. Burnunun dibinde yapılan anlaşmalara asla göz yummaz.";
			link.l1 = "Ha-ha, buna itiraz ederdim ama içiniz rahat olsun — tüm bürokratik engelleri hızla halletmeyi düşünüyorum.";
			link.l1.go = "TPZ_Tavern2_9";
		break;
		
		case "TPZ_Tavern2_9":
			dialog.text = "Lütfen gecikmeyin. Müşterilerimin kupalarının tekrar dolmasını sabırsızlıkla bekliyorum.";
			link.l1 = "Merak etme, seni bekletmeyeceğim.";
			link.l1.go = "TPZ_Tavern2_10";
		break;
		
		case "TPZ_Tavern2_10":
			DialogExit();
			AddQuestRecord("TPZ", "6");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_3");
			AddLandQuestMark(characterFromId("BasTer_Mayor"), "questmarkmain");
			pchar.questTemp.TPZ_guber_1 = true;
			pchar.questTemp.TPZ_Vino200 = true;
		break;
		
		case "TPZ_Tavern2_11":
			if (sti(pchar.reputation.nobility) >= 40)
			{
				dialog.text = "Elbette, Kaptan! Peki, yükünüz için ne kadar istiyorsunuz?";
				link.l1 = "On şişe şarap için otuz dublon, on şişe rom içinse beş dublon isterim. Tüm sevkiyat — her birinden yüz şişe — sana toplam üç yüz elli dublona mal olacak.";
				link.l1.go = "TPZ_Tavern2_3";
				Notification_Reputation(true, 40, "low");
			}
			else
			{
				dialog.text = "Üzgünüm Kaptan, ama itibarınız hâlâ pek parlak sayılmaz.";
				link.l1 = "Lanet olsun...";
				link.l1.go = "exit";
				Notification_Reputation(false, 40, "low");
			}
		break;
		
		case "TPZ_Tavern3_1":
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino240"))
			{
				dialog.text = "Elbette, Kaptan, elbette! 240 dublon, anlaştığımız gibi. Buyurun!";
				link.l1 = "Sizinle iş yapmak büyük zevkti! Şimdi meyhanemiz yine rom ve şarapla dolup taşacak.";
				link.l1.go = "TPZ_Tavern3_2";
				AddItems(pchar, "gold_dublon", 240);
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino200"))
			{
				dialog.text = "Elbette, Kaptan, elbette! 200 dublon, anlaştığımız gibi. Buyurun!";
				link.l1 = "Sizinle iş yapmak büyük keyifti! Artık meyhanemiz yine rom ve şarapla dolup taşacak.";
				link.l1.go = "TPZ_Tavern3_2";
				AddItems(pchar, "gold_dublon", 200);
			}
			DelLandQuestMark(npchar);
		break;
		
		case "TPZ_Tavern3_2":
			dialog.text = "Sen benim kurtarıcımsın, Kaptan! Bundan sonra her iki haftada bir benzer teslimatlar bekleyeceğim. Umarım yükümlülüklerine sıkı sıkıya bağlı kalırsın. Bir daha böyle bir kuraklık olursa, meyhanem ayakta kalamaz...";
			link.l1 = "Endişelenmene gerek yok, "+npchar.name+". Şehirdeki temsilcim Christian Deluce. O, tavernanızda asla şarap ya da rom eksik olmayacağından emin olacak.";
			link.l1.go = "TPZ_Tavern3_3";
		break;
		
		case "TPZ_Tavern3_3":
			dialog.text = "Christian mı? Tanırım onu. Sorumludur, gerçi... neyse. Yetkililerle işini hallettiğine göre, ona güvenebilirim sanırım.";
			link.l1 = "Mükemmel. Şimdi, izninizle, bu kasabada halletmem gereken bir işim daha var.";
			link.l1.go = "TPZ_Tavern3_4";
		break;
		
		case "TPZ_Tavern3_4":
			dialog.text = "Bizi daha sık ziyaret edin!";
			link.l1 = "Elbette yapacağım.";
			link.l1.go = "TPZ_Tavern3_5";
		break;
		
		case "TPZ_Tavern3_5":
			DialogExit();
			AddQuestRecord("TPZ", "7");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_4");
			
			sld = CharacterFromID("TPZ_Kristian");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
			sld.dialog.currentnode = "Kristian_31";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Торговля по закону
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
