// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Devam et, ne istiyorsun?","Biz de tam bundan bahsediyorduk. Herhalde unuttunuz...","Bugün üçüncü kez bir şey soruyorsun...","Bakın, burası bir dükkân. İnsanlar burada alışveriş yapar. Beni rahatsız etmeyin!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Biliyor musun, "+NPChar.name+", belki bir dahaki sefere.","Evet, nedense unuttum...","Evet, gerçekten de üçüncü kez...","Hm, yapmam...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
			{
				Link.l1 = "Dinleyin, monsieur, iş arıyorum. Tam zamanlı bir pozisyon ya da yük taşımak değil, daha çok ufak tefek işler yapmak istiyorum, tabiri caizse. Yardıma ihtiyacınız var mı acaba?";
				Link.l1.go = "Sharlie_storehelper";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
			{
				Link.l1 = "İşinizi hallettim. Gralam Lavoie'yi buldum.";
				Link.l1.go = "Sharlie_storehelper_2";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
			{
				Link.l1 = "Yeni yardımcınızla tanışın, monsieur.";
				Link.l1.go = "Sharlie_storehelper_11";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
			{
				Link.l1 = "Yine ben geldim, monsieur. Ödülümü almaya geldim.";
				Link.l1.go = "Sharlie_storehelper_13";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
			{
				link.l1 = "Şu küpelere bir bakın, monsieur. Onları ormanda öldürülen bir haydutun üzerinde buldum. Bunlar kesinlikle usta bir kuyumcunun işi ve eminim ki buralardan değil. Bu küpeler hakkında söyleyebileceğiniz bir şey var mı?";
                link.l1.go = "Sharlie_junglejew";
			}
			//<-- Бремя гасконца */
		break;
		
		//--> Бремя гасконца
		case "Sharlie_storehelper":
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") 
			{
				dialog.text = "Affedersiniz efendim, ama kılıcınız nerede? Şehirden bir silah olmadan çıkmak güvenli değildir. Ormanda neyle karşılaşacağınızı asla bilemezsiniz!";
				link.l1 = "Lanet olsun, tamamen unuttum! Her şey alıp götürülmüş!";
				link.l1.go = "Store_noweapon";
				break;
			}
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("Fortfrance_town", "reload", "reload6_back");
			dialog.text = "A job? Hm. I suppose I've got a job you might want. My assistant is missing; he used to work in my warehouse. He has been missing for a week already and this is damn annoying, because I am forced to do his duties and I don't have time.\nPlease, find this idiot and find out why the hell he abandoned his work. Or even better – bring him back to me. I'll pay you a thousand pieces of eight.";
			link.l1 = "Pekala, kabul ediyorum. Adını söyle ve nasıl göründüğünü tarif et. Onu nerede arayacağımız hakkında bir fikrin var mı?";
			link.l1.go = "Sharlie_storehelper_1";
			link.l2 = "Tanrı bilir nerede bir adamı bulmak için sırf bin akçe mi? Şaka yapıyor olmalısınız!";
			link.l2.go = "Sharlie_storehelper_exit";
			npchar.quest.storehelper = "true";
		break;
		
		case "Sharlie_storehelper_exit":
			AddTimeToCurrent(2,0);
			LocatorReloadEnterDisable("Fortfrance_town", "reload10_back", false);// пу откр
			dialog.text = "Hey, monsieur. İş mi arayan sensin, yoksa ben mi? İstemiyorsan, kimse seni zorlamıyor. İyi günler.";
			link.l1 = "Hm... Think I'll go check the port authority; perhaps they'll offer something more substantial there.";
			link.l1.go = "exit";
		break;
		
		case "Sharlie_storehelper_1":
			dialog.text = "Adı Gralam Lavois. Nasıl biri mi? Otuz beş yaşlarında, sakallı ve bıyıklı, uzun kahverengi pardösü, beyaz gömlek giyer. Ha, bir de o aptal üç köşeli şapkasını hep takar, kendini amiral sanır, sanki kıçında çapa varmış gibi davranır.\nSt. Pierre'de değil, bütün kasabayı aradım. Muhtemelen ormanda ya da Les Francois'da, oradaki korsanlarla saklanıyor.\nAma büyük ihtimalle adam korsan yerleşimi Le Francois'da, adanın doğu tarafında. Belki oradaki korsanlarla sohbet ediyordur, ya da meyhanede vakit geçiriyordur, ya da dükkandaki yerel tüccarla tartışıyordur.\nLe Francois'ya nasıl gidilir? Şehir kapısından çıkıp ormana gir, yol ayrımında sola sap, sonra yolu takip et ve sağa dön, ardından kayaların arasındaki sol geçidi kullan, Le Francois'ya varırsın. Sanmam ki yolunu kaybedesin.";
			link.l1 = "Pekala. Araştırmaya başlayacağım. Bir şey çıkar çıkmaz, sizi hemen bilgilendireceğim.";
			link.l1.go = "exit";
			AddQuestRecord("SharlieA", "1");
			pchar.questTemp.Sharlie.Storehelper = "true";
			pchar.questTemp.Sharlie.Storehelper.Chance = rand(2);
			AddDialogExitQuestFunction("Sharlie_CreateStorehelper");
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload3_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload1_back");
		break;
		
		case "Sharlie_storehelper_2":
			DelLandQuestMark(npchar);
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload6_back");
			dialog.text = "Öyle mi? Peki, o nerede?";
			link.l1 = "Onu Le Francois'ta buldum. Artık sizin için çalışmayacak. Ayrıca sizin hakkınızda oldukça ağır şeyler söyledi... Duymak ister misiniz?";
			link.l1.go = "Sharlie_storehelper_3";
		break;
		
		case "Sharlie_storehelper_3":
			dialog.text = "Hayır. Ayrıntılara girmeyin... Ne yazık! Şimdi asistanım olmadan ne yapacağım?";
			link.l1 = "Başkasını tutun. Yoksa Gralam'ın söylediği kadar büyük bir sorun mu gerçekten?";
			link.l1.go = "Sharlie_storehelper_4";
		break;
		
		case "Sharlie_storehelper_4":
			dialog.text = "Gerçekten de şanssızlık. Peki o aylak ne dedi?";
			link.l1 = "Öncelikle, adamın boş durmadığı belli, he-he. Şöyle dedi: Saint Pierre’de kimse seninle çalışmak istemezmiş çünkü... işçilerine yeterince ödeme yapmıyormuşsun. Evet, bu arada, "+npchar.name+", söz verdiğin gibi bin peso borcun var.";
			link.l1.go = "Sharlie_storehelper_5";
		break;
		
		case "Sharlie_storehelper_5":
			AddMoneyToCharacter(pchar, 1000);
			dialog.text = "Lütfen, paranı al. Ha! Asla yetmiyor! Tabii ki kimse benim için çalışmak istemiyor. O alçak elinden geleni yaptı, pis dedikodular yaydı. Ne yapabilirim ki? Her şeyi tek başıma yapamam!\nHer bir yükü saymadan uyuyamıyorum, çünkü şu lanet işçiler mutlaka bir şey çalıyor. Son yüklemeden sonra beş varil romum eksik. Eminim işçiler onları 'yanlışlıkla' almıştır...";
			link.l1 = "Pekala, ne tavsiye edeceğimi bilmiyorum. Tamam, her şey gönlünce olsun. Artık gitmem gerek.";
			link.l1.go = "Sharlie_storehelper_6";
		break;
		
		case "Sharlie_storehelper_6":
			dialog.text = "Bekle! Sanırım bana yardım edebilirsin. O herifi bulabildiysen, belki de şunu da yapabilirsin...";
			link.l1 = "Ve bu kasabada kimse sana inanmıyorsa, ben ne yapabilirim ki, merak ediyorum? Ben buraya yeni geldim ve...";
			link.l1.go = "Sharlie_storehelper_7";
		break;
		
		case "Sharlie_storehelper_7":
			dialog.text = "Bitirmeme izin verin, efendim. Le Francois'ya gittiniz. Oraya tekrar gitmenizi ve benim için bir çalışan bulmanızı istiyorum. Belki Gralam o korsan ininde itibarımı tamamen mahvetmemiştir\nİş kolay - yükleri saymak ve liman işçilerini hırsızlık yapmamaları için gözetmek. Bazen de ben yokken burada benim yerime çalışmak, tabii ki ek bir ücret karşılığında\nOnlara mağazada kalacak bir oda ve haftada beş yüz sekizlik teklif ettiğimi söyleyin. Monsieur, işimi büyütmeyi planlıyorum ve nihayet işler yoluna girmeye başladı, bir yardımcıya ihtiyacım var!\nBu arada, bir çalışan bulmak için en iyisi yerel meyhaneci Cesare Craig'den yardım istemek olur. O düzenbaz kesinlikle size yardımcı olur, tabii ki bedavaya değil, benim için çalışmak isteyecek birilerini bulmakta.";
			link.l1 = "Hm. Deneyebilirim, ama emin değilim... Bu iş için bana ne kadar ödeyeceksiniz?";
			link.l1.go = "Sharlie_storehelper_8";
		break;
		
		case "Sharlie_storehelper_8":
			dialog.text = "Bu, tutabileceğin işçiye bağlı olacak. Ne kadar iyi çıkarsa, emeğin için o kadar fazla öderim. Bu adil, değil mi?";
			link.l1 = "Beni körlemesine karar vermeye zorluyorsun, farkında değil misin? Bir işçiyi nasıl değerlendireceğini nereden bileceğim? İstediğin herkese kötü diyebilirsin ya da...";
			link.l1.go = "Sharlie_storehelper_9";
		break;
		
		case "Sharlie_storehelper_9":
			dialog.text = "Monsieur! Biraz cimri olduğumu söylemek belki doğru olabilir, ama kimse bana dürüst değil diyemez! Size, işin sonucuna göre emeğinizin karşılığını ödeyeceğimi söylüyorsam, bunu gerçekten kastediyorum. Bir de benim açımdan bakın. Belki bana, bütün gün yan gelip yatan ve hiçbir iş yapmayan, hatta geceleri beni soyabilecek tembel bir çingeneyi getirirsiniz!";
			link.l1 = "Pekala. Kabul ediyorum. Sözünüze güveniyorum, "+npchar.name+". Bir daha asla çingene getirmem, merak etmeyin.";
			link.l1.go = "Sharlie_storehelper_10";
		break;
		
		case "Sharlie_storehelper_10":
			DialogExit();
			SetLaunchFrameFormParam("Back to Le Francois...", "Reload_To_Location", 0, 3.0);
			SetLaunchFrameReloadLocationParam("LeFransua_tavern", "reload", "reload1", "SharlieA_TeleportLF");
			LaunchFrameForm();
		break;
		
		case "Sharlie_storehelper_11":
			dialog.text = "Benim için bir işçi buldun mu? Harika. Onunla konuşmama izin ver, ödülünü almak için bir saat sonra gel.";
			link.l1 = "Pekâlâ. Bir saat sonra geri geleceğim.";
			link.l1.go = "Sharlie_storehelper_12";
			DelLandQuestMark(npchar);
		break;
		
		case "Sharlie_storehelper_12":
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.questTemp.Sharlie.Storehelper = "final";
			DialogExit();
			SetLaunchFrameFormParam("One hour passed...", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0); //крутим время
			RecalculateJumpTable();
			AddQuestRecord("SharlieA", "5");
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "Sharlie_storehelper_13":
			switch (sti(pchar.questTemp.Sharlie.Storehelper.Quality))
			{
				case 0:
					AddMoneyToCharacter(pchar, 3000);
					dialog.text = "Bulduğun işçiden oldukça memnunum, gerçi lafı çok ama işi o kadar iyi yapmıyor, ama merak etme, zamanla o gevezeliğini de alırım elinden. Ödülün üç bin sekizlik. Al bakalım.";
					link.l1 = "Teşekkür ederim! Söyler misiniz, Mösyö, kasabada başka birinin de önemli bir konuda yardıma ihtiyacı olup olmadığını biliyor musunuz?";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
				
				case 1:
					AddMoneyToCharacter(pchar, 5000);
					dialog.text = "Gerçekten değerli bir çalışan bulmayı başarmışsınız! Hatta o düzenbaz Gralam'dan bile daha iyi. Çok, çok memnun kaldım efendim. Buyurun, ödülünüz - beş bin sekizlik.";
					link.l1 = "Teşekkür ederim! Söyler misiniz, Mösyö, kasabada başka birinin de önemli bir konuda yardıma ihtiyacı olup olmadığını biliyor musunuz?";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
				
				case 2:
					AddMoneyToCharacter(pchar, 4000);
					dialog.text = "İyi bir işçi bulmuşsunuz. Her ne kadar mesleğin tüm inceliklerini bilmese de, kısa sürede işi kavrayacağından eminim. Sizi takdir ediyorum, efendim. Alın, ödülünüz burada - dört bin sekizlik.";
					link.l1 = "Teşekkür ederim! Söyler misiniz, Mösyö, kasabada başka birinin de önemli bir konuda yardıma ihtiyacı olup olmadığını biliyor musunuz?";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
			}
		break;
		
		case "Sharlie_storehelper_14a":
			LocatorReloadEnterDisable("Fortfrance_town", "reload10_back", false);// пу откр
			dialog.text = "Hmm... Just recently, I saw the port master, clearly upset, heading to the port authority. Check with him; who knows what might have happened.";
			link.l1 = "Tam da bunu yapacağım. Teşekkür ederim, Mösyö.";
			link.l1.go = "Sharlie_storehelper_14";
			DelLandQuestMark(npchar);
		break;
		
		case "Sharlie_storehelper_14":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Sharlie.Storehelper");
			CloseQuestHeader("SharlieA");
			
			QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload6_back");
			
			QuestPointerToLoc("fortfrance_town", "reload", "reload10_back");
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "Ne diyebilirim ki, harika küpeler bunlar. Sana... bakalım... dört bin sekizlik verebilirim. Kimsenin daha fazlasını teklif edeceğini sanmam. Anlaştık mı?";
			link.l1 = "Anlaştık! Onlar senin.";
			link.l1.go = "Sharlie_junglejew_1";
			link.l2 = "Hayır. Sanırım bu mücevherleri kendime saklayacağım.";
			link.l2.go = "exit";
			npchar.quest.junglejew = "true";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info("You've given the earrings");
			RemoveItems(pchar, "jewelry25", 1);
			AddMoneyToCharacter(pchar, 4000);
			AddQuestRecord("SharlieE", "4");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			}
		break;
		
		case "Store_noweapon":
			dialog.text = "Bu olmaz. Size valimize başvurup yardım istemenizi öneririm.";
			link.l1 = "Tavsiyen için teşekkürler. Zaten öyle yapmayı düşünüyorum.";
			link.l1.go = "exit";
		break;
		//<-- Бремя гасконца
	}
	UnloadSegment(NPChar.FileDialog2);
}
