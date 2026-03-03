// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne istiyorsunuz? Sorunuzu sorun.","Sizi dinliyorum, sorunuz nedir?"),"Bu, ikinci kez sormaya çalışmanız...","Bu üçüncü kez sormaya çalışıyorsunuz...","Bu ne zaman bitecek?! Ben meşgul bir adamım, sömürge işleriyle uğraşıyorum ve sen hâlâ beni rahatsız ediyorsun!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şimdi değil. Yeri ve zamanı değil."),"Doğru... Ama sonra, şimdi değil...","Soracağım... Ama biraz sonra...","Üzgünüm, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_2" && !CheckAttribute(npchar, "quest.patria") && !CheckAttribute(pchar, "questTemp.Patria.Visiter_Late"))
			{
				link.l1 = TimeGreeting()+" Monsieur. Valiliğin emriyle buradayım; General-Governor Chevalier de Poincy tarafından gönderildim. Görevim, anavatanımızdan gelen ve kolonileri denetlemekle görevlendirilen Baron Noel Forget’yi Tortuga’ya ulaştırmak. Asıl amacı, Fransız Batı Hint Ticaret Şirketi’ni kurmak. Size kendisini takdim etmeme izin verin... Tüm ayrıntıları bizzat kendisi açıklayacaktır.";
                link.l1.go = "patria_portpax";
			}
			// Rebbebion, квест "Путеводная звезда"
			if (CheckAttribute(pchar, "questTemp.PZ.PortPaxMayorTalk"))
			{
				link.l1 = "Efendim, beni görmek istemişsiniz?";
				link.l1.go = "PZ_1";
			}
			// Украденное воспоминание
			if (CheckAttribute(pchar, "questTemp.UV_DialogMayor"))
			{
				link.l1 = "Majesteleri, dikkatinizi gerektiren son derece hassas bir bilgiyle geldim.";
				link.l1.go = "UV_1";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("Zaten her şeyi aldınız. Daha ne istiyorsunuz?","Henüz eline geçirmediğin bir şey kaldı mı?");
            link.l1 = RandPhraseSimple("Sadece etrafa bakıyorum...","Sadece kontrol ediyorum, bir şeyi almayı unutabilirim...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		// Jason НСО
		case "patria_portpax":
			dialog.text = "Sizi görmekten büyük memnuniyet duydum, Kaptan Charles de Maure ve Baron. Monsieur Forget'nin kolonimizdeki konaklamasının mümkün olduğunca rahat geçmesi için elimden geleni yapacağım. Böyle yüksek rütbeli bir Monsieur'nun beni ziyaret etmesinden istifade ederek, size bir konuda ricada bulunmak isterim.";
			link.l1 = "Çok ilginç! Bize işinizden bahsedin, Ekselansları.";
			link.l1.go = "patria_portpax_1";
		break;
		
		case "patria_portpax_1":
			dialog.text = "Son aylarda, valinin hiçbir temsilcisi kolonimizi ziyaret etmedi, sanki Saint Kitts'te tamamen unutulmuşuz gibi! Bu arada, İspanyollar, Hispaniola'nın tamamını yalnızca İspanyol yapmak isteyen ve adanın batısındaki Fransız yerleşimciler ile korsanları büyük bir baş belası olarak görenler, bir saldırı hazırlığında! Devriye subaylarım, ticaret kaptanlarımız ve hatta sıradan balıkçılarımız, Santiago'da güçlü bir İspanyol filosunun toplandığını ve Port-au-Prince'e saldırmaya hazırlandığını bildirdi!";
			link.l1 = "Deliller yeterince açık mı, Majesteleri?";
			link.l1.go = "patria_portpax_2";
		break;
		
		case "patria_portpax_2":
			dialog.text = "Kesin bilgilerim yok, ama tamamen rastgele insanlardan gelen bu kadar çok bilgi sadece söylenti olamaz. Kolonimiz Fransa için çok önemli, burada en iyi plantasyonlara sahibiz, Barones de bunu kendi gözleriyle görebilir. Bu koloniyi kaybetmek ya da yağmalanma riskiyle karşı karşıya bırakmak kabul edilemez!";
			link.l1 = "Delillerinizi dikkate alacağım ve Chevalier de Poincy'yi bilgilendireceğim. Eminim derhal gereken önlemleri alacaktır.";
			link.l1.go = "patria_portpax_3";
		break;
		
		case "patria_portpax_3":
			dialog.text = "Teşekkür ederim, kaptan...";
			link.l1 = "";
			link.l1.go = "patria_portpax_4";
		break;
		
		case "patria_portpax_4":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_9";
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "governor1");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			npchar.quest.patria = "true";
		break;
		
		case "PZ_1":
			DeleteAttribute(pchar, "questTemp.PZ.PortPaxMayorTalk");
			dialog.text = "Hayır, sizi ben çağırmadım, monsieur. Bir şey mi istemiştiniz?";
			link.l1 = "How could I? But your messenger met us; he said you had prepared one of the houses in the town for me...";
			link.l1.go = "PZ_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_2":
			dialog.text = "Hangi ev, hangi haberci, bu ne cüret?!";
			link.l1 = "Ne demek, hangi ulak... Adı Henri Thibaut, ve...";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "NE? Onun kim olduğunu biliyor musun? Görünüşe göre bilmiyorsun. Ama önemli değil. Levasseur'un yeğeni benim şehrimde ne arıyor?";
			link.l1 = "Aman Tanrım...";
			link.l1.go = "PZ_4";
		break;
		
		case "PZ_4":
			dialog.text = "De Maure, beni duyabiliyor musunuz? Mösyö?";
			link.l1 = "...";
			link.l1.go = "PZ_5";
		break;
		
		case "PZ_5":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "reload", "reload1", "PZ_SharleBezhitObratno", -1);
			bDisableCharacterMenu = true;
			InterfaceStates.Buttons.Save.enable = false;
			SetMusic("music_teleport");
			pchar.questTemp.lockedMusic = true;
		break;
		
		//--> Украденное воспоминание
		case "UV_1":
			dialog.text = "Hassas bir mesele, diyorsunuz? İlgimi çektiniz, Kaptan. Lütfen devam edin—tüm dikkatim sizde.";
			link.l1 = "Konu yeğeniniz Julie ile ilgili. Ondan çalınan bir kolyeyi geri almak için yardımımı istedi.";
			link.l1.go = "UV_2";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			DelLandQuestMark(npchar);
		break;

		case "UV_2":
			dialog.text = "Bir kolye mi? İlginç. Eşyaları arasında böyle bir şey olduğunu hiç hatırlamıyorum.";
			link.l1 = "İzin verin, Valim, olayları sırayla sunayım. Bahsi geçen kolyeyi başarıyla geri aldım. Yaptığım araştırmada, hırsızın yeğeninizin hizmetçisi Giselle olduğunu ortaya çıkardım. Çalınan eşyayı satın alan tüccarı gözlemlerken, bu kadının ne ilk ne de son kez böyle bir suç işlediğinden şüpheleniyorum.";
			link.l1.go = "UV_3";
		break;

		case "UV_3":
			dialog.text = "Çok aydınlatıcı. Lütfen anlatmaya devam edin.";
			link.l1 = "Dikkatimi çeken şey, Ekselansları, Julie'nin bu konuda sizin yardımınıza başvurmamayı tercih etmesiydi. Görünüşe göre kolye, onunla görüşmesini açıkça yasakladığınız birinden gelen bir hediyeydi. Sizin kısıtlamalarınızın en akıllıca ve koruyucu niyetlerden kaynaklandığına inanarak, bu meseleyi size bildirmeyi ve kolyeyi doğrudan size iade etmeyi kendime görev bildim.";
			link.l1.go = "UV_4";
			TakeItemFromCharacter(pchar, "SM_necklace_Julie");
		break;

		case "UV_4":
			dialog.text = "Yargınızın isabetli olduğu anlaşılıyor"+GetSexPhrase(", Kaptan","")+"   Bu meseleyi doğrudan bana getirerek yeğenimin gençlik taşkınlıklarına göz yummadığınız için takdir ediyorum.";
			link.l1 = "Valinin iyiliğini düşünerek hareket ediyorum, Vali. Sizin rehberliğinizin de aynı endişe ve bilgelik kaynağından doğduğuna hiç şüphem yok.";
			link.l1.go = "UV_5";
		break;

		case "UV_5":
			dialog.text = "Gerçekten de, Kaptan. Onun amcası ve koruyucusu olarak, refahı benim için her şeyden önce gelir. Sizin sağduyulu davranışınız için minnettarlığımın bir göstergesi olarak lütfen bu yüz elli doblonu kabul edin. Ayrıca size bu seyir pusulasını takdim ediyorum—tehlikeli sularda yolculuklarınızda size güvenli bir rota göstersin.";
			link.l1 = "Bu cömertliğinizle onurlandım Ekselansları, fakat böyle bir ödül gereksizdi. Ne yazık ki şimdi veda etmeliyim—gelgit hiçbir denizciyi beklemez ve gemim beni bekliyor.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_End");
			AddItems(pchar, "gold_dublon", 150);
			GiveItem2Character(PChar, "compass1");
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		//<-- Украденное воспоминание
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
