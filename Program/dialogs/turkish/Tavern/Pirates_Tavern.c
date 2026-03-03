// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hangi sorularınız var?","Sana nasıl yardımcı olabilirim, "+GetAddress_Form(NPChar)+"?"),"Bana kısa bir süre önce bir soru sormaya çalıştın, "+GetAddress_Form(NPChar)+"...","Bugün boyunca bu soruyu üçüncü kez gündeme getiriyorsun...","Yine sorularınız var, sanırım?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Ah, hafızam nereye kayboldu böyle...","Evet, gerçekten de üçüncü kez...","Hayır, ne soruları?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(PChar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "islatesorotavern")
			{
				link.l1 = "Dinle, "+npchar.name+", Miguel Dichoso adında bir adamı duydun mu? Onun gemisinin Isla Tesoro sularında görüldüğünü söylüyorlar...";
				link.l1.go = "guardoftruth";
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "Dinle, "+npchar.name+", son zamanlarda Isla Tesoro'da Miguel Dichoso'yu görmedin mi?";
				link.l1.go = "tieyasal";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Evet, duydum. O İspanyol soylusu, Shark Dodson'a burada yaşarken harika bir gemi sattı, bir fırkateyn. Ah, o gemi... Gerçekten inanılmazdı...";
			link.l1 = "Dur tahmin edeyim: Modern, zarif bir gövdesi vardı ve on altı knot hıza ulaşabiliyordu, değil mi? Ve adı da 'Santa Quitaria' mıydı?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Çerçeve ve hız konusunda tamamen haklısın, ama onun adı başkaydı: 'San Martin'. Shark o gemi için o düzenbaza bir yığın altın ödedi.";
			link.l1 = "Emin misin, 'San Martin' olduğunu, 'Santa Quiteria' değil? Ne zaman aldı onu? Ve neden Dichoso'ya serseri dedin?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Gözlerim kör olsun, kesinlikle 'San Martin'di, çünkü o papanın saçmalıklarıyla dolu levhayı kıçtan söken Alexus'un adamlarını bizzat gördüm. Shark Dodson ona 'Fortune' adını verdi, böylesine güzel bir gemiye çok daha uygun bir isim. (tükürür) Onu '54 kışında satın aldı, Blaze öldürülmeden çok kısa bir süre önceydi\nDon Miguel'e neden alçak dedim? Çünkü lanet gemiyi Providence'tan İspanyol donanmasından çaldı! Dodson, St. Juan kalesi ve garnizonu için ateş ve dumanla bir gösteri sahneledi, sarhoşken bana hep anlatırdı. Shark, iki hasarlı luggeri feda etti ki fırkateynle dövüş gerçek görünsün diye\nGece bastırınca, 'San Martin'i gizlice Isla Tesoro'ya götürdü. Shark gemiyi aldı, Dichoso ise parayı. O kurnaz herif, sonra üstlerine fırkateynin korsan filosuyla çatışmada battığını söyledi, St. Juan kalesinin komutanı da bunu doğruladı.";
			link.l1 = "Ah, şu İspanyol soyluları ceplerini nasıl da dolduruyor! Ne kurnaz adam! Söylesene, bu gerçekten 1654 kışında mı oldu? Belki de ilkbaharda olmuş olabilir mi? O fırkateyn de fırtınadan yıpranmış gibi görünmüyor muydu?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Eminim kıştı... Kim bilir. Belki de bahardı. Tam olarak hatırlamıyorum. Muhtemelen sarhoştum. Fırkateynin hiçbir yıpranmışlığı yoktu, yepyeni bir gemiydi.";
			link.l1 = "Ve o güzel fırkateyn şimdi nerede?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "Karanlık bir hikaye bu... Blaze öldürüldüğünde herkes Shark'tan şüphelendi, çünkü cesedin üzerinde onun kolyesi, bir köpekbalığı dişi bulundu. Üstelik o gece bazıları Shark'ı Blaze'in evinde görmüş.\nShark, ona kara işaret verilmeden önce Isla Tesoro'dan kaçtı. Karanlık Papaz'a uğrayıp fırkateynini bir brik karşılığında takas etti. Şimdi nerede olduğu hakkında en ufak bir iz yok. Zachary ise fırkateyni daha sonra William Paterson'a sattı.";
			link.l1 = "Kim bu Paterson?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Ne, Willie Paterson'ı hiç duymadın mı? İskoçtur, daha yeni Karayiplere geldi. Kendini kraliyet filosunun kaptanı sanıyor, Albay Fox'un gözdesi! Bu arada, Jackman'la da yeni yeni iş yapmaya başlamış. Paterson'ın amiral gemisi de bizzat 'Fortune'.";
			link.l1 = "Anladım. Şu anda Dichoso'nun nerede olduğunu biliyor musun?";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Hiçbir fikrim yok. 'Fortune' ile yaşanan o karmaşadan sonra onu Isla Tesoro'da bir daha görmedim, hakkında da hiçbir şey duymadım.";
			link.l1 = "Pekâlâ, "+npchar.name+", verdiğin ayrıntılı bilgiler için teşekkürler! Gerçekten harika bir meyhanecisin! Keşke senin gibi daha çok insan olsaydı... Hoşça kal!";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "İyi şanslar, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			DialogExit();
			AddQuestRecord("Guardoftruth", "60_1");
			pchar.questTemp.Guardoftruth.Archy = "guadeloupe";
			// маленькая развлекуха
			pchar.quest.GuardOT_cabinattack.win_condition.l1 = "EnterToSea";
			pchar.quest.GuardOT_cabinattack.function = "GuardOT_PrepareCreateBandosInCabin";
		break;
		
		case "tieyasal":
			dialog.text = "İkiniz de birbirinizi kovalıyor gibisiniz, dostum. Evet, Dichoso buradaydı, tam senin durduğun yerde. Ve tıpkı senin gibi, en son Sharptown'dayken o da seni soruyordu.";
			link.l1 = "Lanet olsun! Demek haber bu... Peki Miguel şu anda nerede?";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Hiçbir fikrim yok. Denize açıldı, orada... Blueweld'den bahsetmişti. Muhtemelen seni bulmak için oraya gitti.";
			link.l1 = "Onu Blueweld'e gönderen sen misin?";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Hayır. Ona sadece seni uzun zamandır görmediğimi söyledim.";
			link.l1 = "Anladım. Peki, o zaman. Teşekkürler, dostum!";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			DialogExit();
			AddQuestRecord("Tieyasal", "3");
			npchar.quest.tieyasal = "true";
			pchar.quest.Tieyasal_ITAttack.win_condition.l1 = "location";
			pchar.quest.Tieyasal_ITAttack.win_condition.l1.location = "Bermudes";
			pchar.quest.Tieyasal_ITAttack.function = "Tieyasal_CreateITShips";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
