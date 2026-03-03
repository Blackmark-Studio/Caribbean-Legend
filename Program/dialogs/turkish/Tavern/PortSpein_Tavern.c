// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Hangi sorularınız var?","Size nasıl yardımcı olabilirim, "+GetAddress_Form(NPChar)+"?"),"Bana kısa bir süre önce bir soru sormaya çalıştın, "+GetAddress_Form(NPChar)+"...","Bütün gün boyunca, bu soruyu üçüncü kez gündeme getiriyorsun...","Sanırım daha fazla sorunuz var?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şu anda konuşacak bir şeyim yok."),"Ah, hafızam nereye kayboldu...","Evet, gerçekten de üçüncü kez...","Hayır, ne soruları?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption") && pchar.questTemp.Consumption == "begin" && sti(pchar.money) >= 3000)
			{
				link.l1 = "Kalede verem salgınının hızla yayıldığını duydum. Salgının kasabaya da sıçrayacağını düşünüyor musun?";
				link.l1.go = "Consumption";
			}
			if (CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.Commandant") && pchar.questTemp.Consumption == "begin")
			{
				link.l1 = "Kaledeki komutan hakkında ne söyleyebilirsin?";
				link.l1.go = "Consumption_8";
			}
			if (!CheckAttribute(npchar, "quest.Consumption_1") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Bana söyle, 'Juan' ismi sana bir şey ifade ediyor mu?";
				link.l1.go = "Consumption_12";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Dinle, Nisan 1654'te Kaptan Miguel Dichoso'nun komutasındaki bir fırkateyn limanına yanaştı ve ardından ortadan kayboldu. Bu konuda bana anlatabileceğin bir şey var mı?";
				link.l1.go = "guardoftruth";
			}
			//--> Оковы Азарта
			if (CheckAttribute(pchar, "questTemp.OZ_Tavern_1"))
			{
				link.l2 = "Söyle bana, "+npchar.name+", bu Javier Castillo kim?";
				link.l2.go = "OZ_Tavern_1";
			}
			if (CheckAttribute(pchar, "questTemp.OZ_Tavern_2"))
			{
				link.l2 = "Javier’i etkileyebilecek adam hakkında konuşmaya geri dönelim.";
				link.l2.go = "OZ_Tavern_2_1";
			}
			//<-- Оковы Азарта

		break;
		
		//--> Цена чахотки
		case "Consumption":
			dialog.text = "Komutan tehlike olmadığını söylüyor. Fazla meraklı olanlar zindana kapatılıyor. Ben onlardan değilim, üzgünüm.";
			link.l1 = "Öyle mi? Dedikoduları dinlemek istemeyen bir meyhaneci – bu gerçekten yeni bir şey! Belki birkaç peso şıngırtısı merakınızı yeniden uyandırır?";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = " Gümüş elbette cazip, ama kendi canım daha değerli. Belki sana başka bir şeyden bahsedebilirim, señor? Aslında sohbet etmeye her zaman hazırım, yeter ki sen başlat!";
			link.l1 = "Demek mesele böyle gelişiyor... Peki, bu kesede üç bin sekizlik var ve biz de havadan sudan güzel bir sohbet edeceğiz, anlaştık mı?";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			AddMoneyToCharacter(pchar, -3000);
			dialog.text = "Ah, ısrarcısınız señor. Ama unutmayın, bu konuşma hiç yaşanmadı. (fısıldayarak) Bir yıldır defalarca duydum, bizim zindanlarımızda insanlar çürüyüp gidiyor, veremden ölüyorlar. Yetkilileri suçlayabilirsiniz, Tanrı’yı ya da Şeytan’ı suçlayabilirsiniz, ama çoğu kötü talihin eseri sayılır. Bu lanet hastalık hayatları öyle hızlı alıyor ki. Bazen sapasağlam bir adamı içeri atıyorlar, bir-iki hafta sonra yok olup gidiyor. İşte böyle...";
			link.l1 = "Vay canına... Koca bir yıl mı diyorsun? Ve kimse de bu konuda bir şey yapmayı düşünmemiş mi?";
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = "Who cares, señor? Who cares about prisoners? The scum of society - or so the great men in silk say. There was a physician who worked in the dungeons. Tried to heal those poor souls. He didn't last long; it seems the illness claimed him too.\nThe commandant doesn't let people in now, and our authorities pay no mind to such matters, especially when they have to pay less for prison rations.";
			link.l1 = "İlginç, ama bu hastalıkta seni bu kadar korkutan ne ki, güvenli duvarların ardında kilitliyken, itiraf odasındaki rahibeler gibi fısıldıyoruz?";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "Bunu sana söylemek zor ama burada bir adam vardı. Kaçakçılıktan yakalandı ve arkadaşları onu kurtarana kadar yaklaşık yarım yıl hapis yattı. Yani, ne gerekiyorsa altın ödediler, istenen parayı verdiler, adam da serbest kaldı. Ama o günden beri aklını kaçırmış gibi.";
			link.l1 = "Sintisinden daha mı çılgın?";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "Sanırım öyle. O andan itibaren arkadaşlarına hiçbir faydası kalmadı, bütün gününü burada geçirip kendini içkiye vurdu. Sanki aklından bir şeyi silmek ister gibiydi. Ne zaman sarhoş olsa, insanları sessizce götüren veremden bahsederdi\nAynen böyle söylerdi. Ona göre, 'verem' bir adama olabilecek en kötü şeymiş.";
			link.l1 = "Bir ayyaşın saçmalıkları. Ne olmuş yani?";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			if (CheckAttribute(pchar, "questTemp.Consumption.Commandant"))
			{
				dialog.text = "Hiçbir şey, sadece biraz cesaret içkisi buldu, konuşmaya başladı ve sonra birdenbire, birisi boğazını kesti ve onu sokağa attı... Bunu kimin yaptığı ve neden yaptığı benim için hiç fark etmez.";
				link.l1 = "Komutan hakkında ne söyleyebilirsin?";
				link.l1.go = "Consumption_8";
			}
			else
			{
				dialog.text = "Hiçbir şey, sadece cesaretlenip daha fazla konuşmaya başladı ve sonra bir bakmışsın, birisi boğazını kesip onu sokağa atıvermiş... Kimin yaptığı ya da neden yaptığı umurumda değil. (sesini yükseltir) Evet, koylar ve resifler burada gerçekten tehlikelidir, señor. Büyük Antiller'den fırtınalar bastırınca dikkatli olmalısınız, rüzgarı kaçırırsanız yandınız! İyi dinlenmeler, señor, uğradığınız için teşekkürler!";
				link.l1 = "Fırtınalar... doğru. Sana da teşekkür ederim.";
				link.l1.go = "Consumption_7";
			}
			pchar.questTemp.Consumption.Contra = "true";
		break;
		
		case "Consumption_7":
			DialogExit();
			npchar.quest.Consumption = "true";
			AddQuestRecord("Consumption", "2");
		break;
		
		case "Consumption_8":
			dialog.text = "Onun hakkında ne söylenebilir ki? Kendisi bir albay, birkaç yıl önce Avrupa'dan buraya bu göreve atanarak geldi. Sözde, Eski Dünya'da karanlık işlere bulaştığı için rütbesi düşürülmüş. Bunun doğru olup olmadığını bilmiyorum ama başta böyle söylentiler vardı. Ama kim hakkında dedikodu yok ki, değil mi?";
			link.l1 = "Kirli işler, diyorsun... Bu ilginç. Başka bir şey var mı?";
			link.l1.go = "Consumption_9";
		break;
		
		case "Consumption_9":
			dialog.text = "Ne diyebilirim ki... Albay, kendi güvenliğinden fazlasıyla endişe eden birine benziyor. Elbette, buralar korsanlar, haydutlar, yerliler ve başka serseriler yüzünden pek güvenli sayılmaz, ama Senyor Komutan asla birkaç koruması olmadan evinden dışarı adımını atmaz.\nKonağı bu şehirde ve orayı adeta küçük bir kaleye çevirmiş - hizmetkârları silahlı ve pencereler sürekli kapalı tutuluyor.";
			link.l1 = "Ama gündüzleri hapishanede görev yapıyor, değil mi?";
			link.l1.go = "Consumption_10";
		break;
		
		case "Consumption_10":
			dialog.text = "Evet, ama o köşk aslında pusuya ya da bir baskına davetiye çıkarıyor. Neyse, Señor Komutan görünüşe göre oraya pek sık dönmüyor — gerçek bir kale daha çok onun tarzı, he-he.";
			link.l1 = "Teşekkür ederim, çok yardımcı oldunuz. Sonra görüşürüz, "+npchar.name+"!";
			link.l1.go = "Consumption_11";
		break;
		
		case "Consumption_11":
			DialogExit();
			if (CheckAttribute(npchar, "quest.Consumption")) AddQuestRecord("Consumption", "4");
			else AddQuestRecord("Consumption", "5");
			DeleteAttribute(pchar, "questTemp.Consumption.Commandant");
			pchar.questTemp.Consumption = "current";
		break;
		
		case "Consumption_12":
			dialog.text = "Juan? Hangisi? Burada onlardan çok var, genelde insanların soyadı da olur... ya da en azından bir lakabı...";
			link.l1 = "Az önce düşünüyordum... Belki de lakabı 'Tüketim'dir, bunu hiç duydun mu?";
			link.l1.go = "Consumption_13";
		break;
		
		case "Consumption_13":
			dialog.text = "Aman Tanrım, yine ondan mı bahsediyorsun! Hayır, Allah'a şükür, duymadım. Vallahi! Şimdi, konuyu değiştirelim. Lütfen!";
			link.l1 = "Peki, tamam, kalp krizi geçirme...";
			link.l1.go = "exit";
			pchar.questTemp.Consumption.AskJuan = sti(pchar.questTemp.Consumption.AskJuan)+1;
			if(sti(pchar.questTemp.Consumption.AskJuan) == 3)
			{
				pchar.quest.Consumption2.win_condition.l1 = "location";
				pchar.quest.Consumption2.win_condition.l1.location = "PortSpein_town";
				pchar.quest.Consumption2.function = "Consumption_CreateSergio";
			}
			npchar.quest.Consumption_1 = "true";
		break;
		//<-- Цена чахотки
		
		//--> Оковы Азарта
		case "OZ_Tavern_1":
			dialog.text = "Javier bir iskambil oyuncusu, bir üçkağıtçı ve bir dolandırıcıdır. Her zaman meyhanede takılır, birkaç peso koparacak birini arar.";
			link.l1 = "Yani, başka karanlık işlerde de görülmemiş mi? Belki de düşmanları vardır?";
			link.l1.go = "OZ_Tavern_2";
			DeleteAttribute(pchar, "questTemp.OZ_Tavern_1");
			DelLandQuestMark(npchar);
		break;
		
		case "OZ_Tavern_2":
			dialog.text = "Şöyle diyelim, onun dostu olanlardan çok, boynunu sıkmayı hayal edenler var. Ama gerçekten ona etki edebilecek birinin adını istiyorsan, bu sana bin peso'ya mal olur. Öde – sana her şeyi anlatırım.";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "Pekâlâ, al paranı, seni yaşlı paragöz.";
				link.l1.go = "OZ_Tavern_3";
			}
			else
			{
				link.l1 = "Bu konuşmaya sonra döneriz. Şu anda o kadar param yok.";
				link.l1.go = "exit";
				pchar.questTemp.OZ_Tavern_2 = true;
				AddLandQuestMark(npchar, "questmarkmain");
			}
		break;
		
		case "OZ_Tavern_2_1":
			dialog.text = "Kaptan, bin peso getirdiniz mi?";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "Var. Al bakalım, seni kurnaz ihtiyar.";
				link.l1.go = "OZ_Tavern_3";
			}
			else
			{
				link.l1 = "Lanet olsun. Yakında döneceğim.";
				link.l1.go = "exit";
			}
		break;
		
		case "OZ_Tavern_3":
			dialog.text = "İşte bu daha iyi. Bak, Javier’in sadece kumar borçları yok. Bir keresinde antika işine de bulaşmaya kalktı ama tahmin edersin ki sonu pek iyi olmadı. Başta işler fena gitmedi aslında, ama sonra nadir bir eşyayı ele geçirme fırsatı çıktı karşısına\nBu fikre öyle bir kaptırdı ki kendini, para bulmak için bütün tefecilerin kapısını çaldı. Tabii ki kimse ona beş kuruş vermedi. Sonra, antikalara en az onun kadar kafayı takmış başka bir adam buldu ve ondan yüz elli bin peso borç aldı. Gerisini sanırım tahmin edersin\nKandırıldı ve şimdi o borç boynunda bir taş gibi asılı duruyor. Geriye sadece üç beş kuruş ödedi, ve anlaşılan kalanını ödemeye de hiç niyeti yok, üstelik alacaklısı onu korkutmak için adamlar bile tutmuşken\nBorçlu olduğu adam Felipe Alarcon. Evi bankanın tam karşısında – kolayca tanırsın, girişinde sütunları olan görkemli bir konaktır.";
			link.l1 = "Teşekkürler!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000);
			DeleteAttribute(pchar, "questTemp.OZ_Tavern_2");
			AddDialogExitQuestFunction("OZ_Felip_1");
			DelLandQuestMark(npchar);
		break;
		//<-- Оковы Азарта
		
		case "guardoftruth":
			dialog.text = "Onu hatırlıyorum. Sık sık taverneme uğrardı ama pek konuşmazdı. Birkaç kadeh rom içer, bazı müşterilerle fısıldaşır, sonra da giderdi. Çok kasvetli ve ciddi biriydi, o fırkateyndeki herkes gibi. Kılıçlarını her an çekmeye hazır, tehlikeli görünümlü paralı askerlerdi\nFırkateynin hazineyle dolu olduğuna dair bir söylenti vardı ama ben böyle hikayelere inanmam. Değerli yük asla tek bir gemiyle, konvoysuz taşınmaz. Burada bir gün kaldılar, sonra ayrıldılar. Avrupa'ya gitmişler, öyle duydum. Bildiğim bu kadar.";
			link.l1 = "Anladım. Eh, en azından bir şey bu...";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
			AddQuestRecord("Guardoftruth", "40");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
