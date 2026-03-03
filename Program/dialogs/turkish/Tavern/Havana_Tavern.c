// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Tüm dedikodular "+GetCityName(npchar.city)+" hizmetinizdeyim. Ne öğrenmek istersiniz?","Biz de tam bundan bahsediyorduk. Herhalde unuttun...","Bugün bu soruyu üçüncü kez gündeme getiriyorsunuz...","Kendini papağan gibi tekrar ediyorsun...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Biliyor musun, "+NPChar.name+", belki bir dahaki sefere.","Doğru, nedense unuttum...","Evet, gerçekten de üçüncü kez...","Evet...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Slavetrader") && pchar.questTemp.Slavetrader == "FindRatHavana")
            {
                link.l1 = "Francois Gontier tesadüfen kasabanıza uğradı mı? Bir korveti var '"+pchar.questTemp.Slavetrader.ShipName+"', her ihtimale karşı... ";
                link.l1.go = "Havana_ratT_1";
            }
			if (CheckAttribute(npchar, "quest.batabano"))
            {
                link.l1 = "Söyle bakalım dostum, Don Diego de Montoya'yı nerede bulabilirim? Geç mi kaldım? Ana Kıta'ya çoktan yola çıktı mı?";
                link.l1.go = "guardoftruth";
            }
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Dinle, buradan Joachim Merriman adında bir adam geçti mi? Orta yaşlı bir doktor, Portekizli, bıyıklı, keçi sakallı ve delici bakışlı? Belki bir oda kiralamak istemiştir?";
				link.l1.go = "caleuche";
			}
		break;

		case "Havana_ratT_1":
			dialog.text = "Ha, o kasvetli adam mı? Evet, buraya uğradı. Sana bir şey söyleyeyim: Oregon ve Haskon'la bir randevusu vardı. Patent başvurusu yaptı. Ama işi yolunda gitmedi ve gitti.";
			Link.l1 = "Peki nereye gittiğini biliyor musun? Porto Bello'dan beri onun peşindeyim ama bir türlü bulamıyorum.";
			Link.l1.go = "Havana_ratT_2";
		break;
		
		case "Havana_ratT_2":
			dialog.text = "What do you need from him? He's afraid of outsiders, always hiding from everyone; as soon as he sees an armed stranger, he grabs his sword. He only walks around surrounded by four guards. Are you, by any chance, the one he's so wary of?";
			Link.l1 = "Tanrım, insanlar bunu tekrar tekrar söylüyor! Ne yani, katil gibi mi görünüyorum? O benim eski bir dostum, sadece ona bir haber iletmek için acelem var. Artık saklanmasına gerek olmadığını öğrenince çok sevinecek—kimse onu aramıyor.";
			Link.l1.go = "Havana_ratT_3";
		break;
		
		case "Havana_ratT_3":
			dialog.text = "Saklanmasına gerek yok mu? Ha-ha-ha! Havana'dan ayrılmadan sadece bir gün önce, bir grup serseri onu ormanda öldürmeye kalkıştı... Tabii ki yanında kendi adamları vardı ve onları bir anda lime lime ettiler. Ve şimdi sen diyorsun ki...";
			Link.l1 = "Aman, hadi ama. Muhtemelen cüzdanını almak isteyen birkaç yerel hayduttu. Sen de biliyorsun, ormanda ne kadar serseri dolaşıyor. Peki, nereye gitmiş?";
			Link.l1.go = "Havana_ratT_4";
		break;
		
		case "Havana_ratT_4":
			dialog.text = "Yani, konaktan uzaklara ve uzun süreliğine gönderildikten sonra, sürekli kendini kurbağa yiyenlere, kendi milletine teslim edeceğinden bahsedip durdu. Tortuga'ya, bir d'Ogeron'a doğru yola çıktı... Bir de sevgilisiyle ilgili bir şeyler mırıldandı ama tam olarak anlayamadım.";
			Link.l1 = "Yani, Tortuga mı? Harika! Umarım onu orada yakalarım. Teşekkür ederim, "+npchar.name+", çok yardımcı oldun. Hoşça kal.";
			Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_7");
			pchar.questTemp.Slavetrader = "FindRatTortuga";
			pchar.quest.Slavetrader_findTortugaRat.win_condition.l1 = "location";
            pchar.quest.Slavetrader_findTortugaRat.win_condition.l1.location = "Tortuga_HouseHut";
            pchar.quest.Slavetrader_findTortugaRat.win_condition = "Slavetrader_findTortugaRat";
		break;

		case "guardoftruth":
			dialog.text = "Hm... Bir Fransız neden Don Diego'yla ilgilensin ki, ha?";
			link.l1 = "Fransız olmamın bir önemi yok. Önemli olan Engizitör tarafından imzalanmış bu belge. Bakın... şimdi anlıyor musunuz? Diego'ya acil bir mesajım var.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "A-ha, demek Rahip Vincento için çalışıyorsun? Bu işleri değiştirir. Don Diego de Montoya iki gün önce filosuyla ayrıldı, ama kısa süre sonra kurye lügeriyle geri döndü. Gemilerinden biri Küba'nın güneyindeki kayalıklarda karaya oturmuş, bu yüzden bugün tamir malzemeleri satın alıyordu\nGüneydeki körfeze bak, orada bir gemi ve kendisini bulacaksın. Delikleri çoktan yamalamış olabileceklerini sanmam.";
			link.l1 = "Sağ ol dostum! Bana çok yardımcı oldun!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Hiç de değil, her zaman. Bir Cizvit kardeşe yardım etmekten her zaman mutluluk duyarım.";
			link.l1 = "Evet, pax vobiscum ve işte böyle.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			DialogExit();
			DeleteAttribute(npchar, "quest.batabano");
			AddQuestRecord("Guardoftruth", "47");
			pchar.quest.GuardOT_Batabano.win_condition.l1 = "location";
			pchar.quest.GuardOT_Batabano.win_condition.l1.location = "Shore13";
			pchar.quest.GuardOT_Batabano.function = "GuardOT_SanAntonioPrepare";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Şeytan bilir dostum. Belki gelmiştir, ama benim haberim yok. Kusura bakma.";
			link.l1 = "Anladım. Yazık. Aramaya devam edeceğim...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
