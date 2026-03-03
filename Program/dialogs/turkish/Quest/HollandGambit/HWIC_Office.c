// НПС офиса ГВИК
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Bir şey mi istiyorsun?";
			link.l1 = "Hayır.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// офицер
		case "HWIC_officer":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Alarm! Düşman burada! Silahlara!";
				link.l1 = "Lanet olsun!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "Sen orada, dur! Yüzün bana tanıdık geliyor... tabii ya! Suçların için aranıyorsun! Çocuklar, yakalayın onu!";
				link.l1 = "Lanet olsun!";
				link.l1.go = "fight";
				break;
			}
			chrDisableReloadToLocation = true;
			if (CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Holl") && !CheckAttribute(pchar, "questTemp.HWIC.Eng") && !CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				dialog.text = "Hollanda Batı Hint Şirketi'ne hoş geldiniz. Çabuk konuşun, zaman paradır.";
				link.l1 = "Ticaret işleri için buradayım. Ruhsatlar, seyir aletleri ve benzeri şeyler...";
				link.l1.go = "HWIC_officer_3";
				link.l2 = "Şirket'e hizmetlerimi sunmak istiyorum. Tabii ki altın karşılığında. Eleman alıyor musunuz?";
				link.l2.go = "HWIC_officer_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				dialog.text = "Hollanda Batı Hindistan Şirketi'ne hoş geldiniz. Çabuk konuşun, zaman paradır.";
				link.l1 = "Üzgünüm, sanırım yanılmışım. Gidiyorum.";
				link.l1.go = "HWIC_officer_exit";
				link.l2 = "Ticaret işi için buradayım. Ruhsatlar, seyir aletleri, vesaire...";
				link.l2.go = "HWIC_officer_3";
				break;
			}
			dialog.text = "Çabuk konuş, zaman para.";
			link.l1 = "Ticaret işi için buradayım. Ruhsatlar, seyir aletleri, vesaire...";
			link.l1.go = "HWIC_officer_3";
			link.l2 = "Şirket'e hizmetlerimi sunmak istiyorum. Tabii ki altın karşılığında. Eleman alıyor musunuz?";
			link.l2.go = "HWIC_officer_2";
		break;
		
		case "HWIC_officer_1":
			dialog.text = "O zaman yukarı çıkıp Bay Rodenburg'un ofisine gidin.";
			link.l1 = "Teşekkürler, gidiyorum.";
			link.l1.go = "HWIC_officer_exit";
			// belamour legendary edition переехали по другому адресу
			LocatorReloadEnterDisable("GVIK", "reload2", false);//кабинет откроем
		break;
		
		case "HWIC_officer_2":
			dialog.text = "Şirket şu anda eleman almıyor.";
			link.l1 = "Ne yazık. Sizi rahatsız ettiğim için üzgünüm.";
			link.l1.go = "HWIC_officer_exit";
		break;
		
		case "HWIC_officer_3":
			dialog.text = "Mynheer Gerritz ile konuş. İçeri girince solundaki masada oturuyor. Sözleşmeli kaptanlarla iş yapar.";
			link.l1 = "Teşekkür ederim, subayım...";
			link.l1.go = "HWIC_officer_exit";
		break;
		
		case "HWIC_officer_exit":
			DialogExit();
			// belamour legendary edition переехали
			LAi_ActorGoToLocation(npchar, "soldiers", "soldier3", "GVIK", "soldiers", "soldier3", "", 5);
			DoQuestCheckDelay("ReturnTalkerToOfficer", 5.0); // 140313
			NextDiag.TempNode = "HWIC_officer";
		break;
		
		// солдаты
		case "HWIC_soldier":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Alarm! Düşman burada! Silah başına!";
				link.l1 = "Lanet olsun!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "Aha! Sanırım kim olduğunu biliyorum... Tabii ya! Suçların için aranıyorsun! Çocuklar, yakalayın onu!";
				link.l1 = "Lanet olsun!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Memurlarımızla ya da Bay Gerritz ile konuşun. Size söyleyecek bir şeyim yok. Görev başındayım.";
			link.l1 = "Disiplinin gerçekten takdire şayan.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "HWIC_soldier";
		break;
		
		// клерки
		case "HWIC_clerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Alarm! Düşman burada! Askerler!";
				link.l1 = "Lanet olsun!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Mynheer Gerritz ile konuş.";
			link.l1 = "Pekala, anladım.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "HWIC_clerk";
		break;
		
		// главный клерк - минхер Герритц
		case "HWIC_headclerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Alarm! Düşman burada! Askerler, onu yakalayın!";
				link.l1 = "Lanet olsun!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "Hm. Sende bir tuhaflık var gibi... Ama tabii ki! Hollanda'ya karşı işlediğin sayısız suçtan aranıyorsun! Askerler, yakalayın onu!";
				link.l1 = "Lanet olsun!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Bir şey ister misiniz, efendim?";
			if (!CheckCharacterItem(pchar, "HolTradeLicence"))
			{
				link.l1 = "Hollanda Batı Hindistan Şirketi'nden bir ticaret lisansı almak istiyorum.";
				link.l1.go = "licence";	
			}
			if (!CheckAttribute(npchar, "quest.trade"))
			{
				link.l2 = "Burada seyrüsefer aletleri ve başka işe yarar eşyalar satın almak mümkünmüş, doğru mu?";
				link.l2.go = "trade";	
			}
			else
			{
				link.l2 = "Bugün ne satıyorsun?";
				link.l2.go = "trade_1";	
			}
			if (CheckCharacterItem(pchar, "Cromvel_depeshe"))
			{
				link.l3 = "Sizin için ilginç bir belge var, efendim. İlk birkaç satırına bir göz atın. Bu, Cumhuriyetin bekası ve Şirketin kazançlarıyla ilgili. Ayrıca, belirli bir buluşmanın koordinatları da içinde. Eğer ilgilenirseniz, size satabilirim. Tabii ki cömert bir ücret karşılığında.";
				link.l3.go = "depeshe";	
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.Garpiya") && pchar.questTemp.Caleuche.Garpiya == "gwik")
			{
				link.l4 = "Reginald Jackson adında bir kaptan sizin için çalışıyor olmalı. 'Harpy' adında bir xebec ile seyahat ediyor. Onu nasıl bulabileceğimi söyler misiniz? Onunla önemli bir işim var.";
				link.l4.go = "caleuche";	
			}
			// Sinistra Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_RazgovorGerrits"))
			{
				link.l4 = "Mynheer Rodenburg'u acilen görmem gerek. Bu çok önemli. Nerede kendisi?";
				link.l4.go = "PZ_RazgovorGerrits_1";
			}
			link.l9 = "Hayır, bir şey değil.";
			link.l9.go = "exit";			
			NextDiag.TempNode = "HWIC_headclerk";
		break;
		
		// торговые лицензии
		case "licence":
			if (!CheckAttribute(npchar, "quest.licence"))
			{
				dialog.text = "Pekâlâ, satın almakta özgürsünüz. Ama sizi uyarmalıyım, Şirket tarafsızlığına büyük önem verir, bu yüzden bu lisansa sahipken herhangi bir ülkenin ticaret gemilerine saldırmak kesinlikle yasaktır.\nBöyle bir eylem gerçekleştiğini öğrenirsek, lisansınızı iptal ederiz. Ayrıca, herhangi bir nedenle Hollandalılarla ya da Şirketle çatışmaya girerseniz, lisansınız yine iptal edilir. Anlaştık mı?";
				link.l1 = "Gayet açık. Bunu aklımda tutacağım.";
				link.l1.go = "licence_0";
				npchar.quest.licence = true;
			}
			else
			{
				dialog.text = "Bir lisans satın almakta özgürsünüz. Peki, kaç gün?";
				link.l1.edit = 6;
				link.l1 = "";	
				link.l1.go = "licence_1";
			}
		break;
		
		case "licence_0":
			dialog.text = "Lisans, herhangi bir ulusun herhangi bir limanına serbest geçiş hakkı tanır, barışçıl niyetlerinizi gösterir ve amacınızı - ticaret yapmak istediğinizi - açıklar. Ama eğer kanunla başınız derde girerse, bu belge size yardımcı olmaz. O durumda sadece elinizden alırlar. Unutmayın, \nHerhangi bir limana yanaşmadan önce dostça bir bayrak çekmeyi unutmayın. Devriye ve kale topçuları önce ateş edip sonra soru sormayı tercih ederler\nLisansın asgari süresi yirmi gündür, azami süresi ise altı ay ya da 180 gündür\nEvet, az kalsın unutuyordum... Kıymetli geleneklerimize göre, lisansla ilgili tüm anlaşmalar dublon ile ödenir.  Şimdi şartları konuşalım. Lisansın ne kadar süreyle geçerli olmasını istersiniz?";
			link.l1.edit = 6;
			link.l1 = "";	
			link.l1.go = "licence_1";
			link.l2 = "Üzgünüm, ama bunu biraz daha düşünmem gerekiyor. Sonra görüşürüz.";	
			link.l2.go = "exit";
		break;
		
		case "licence_1":
			float fQty = stf(dialogEditStrings[6]);
			npchar.quest.lcc_summ = makeint(sqrt(fQty)*10)*7;
			if (fQty < 1)
			{
				dialog.text = "Beyefendi, lütfen daha açık konuşun. Sizi tam olarak duyamadım. Peki, ne kadar süreyle?";
				link.l1 = "Bir düşüneyim...";
				link.l1.go = "licence_r";
				break;
			}
			if (fQty > 0 && fQty < 20)
			{
				dialog.text = "Lisansın asgari süresi yirmi gün. Ee? Yirmi gün mü, yoksa daha uzun mu?";
				link.l1 = "Bir düşüneyim...";
				link.l1.go = "licence_r";
				break;
			}
			if (fQty > 180)
			{
				dialog.text = "Lisansın azami süresi yarım yıl. Yüz seksen gün ya da daha az mı?";
				link.l1 = "Bir düşüneyim...";
				link.l1.go = "licence_r";
				break;
			}
			dialog.text = "İçin "+FindRussianDaysString(sti(fQty))+"? Çok iyi. Bunun sana maliyeti olacak "+FindRussianDublonString(sti(npchar.quest.lcc_summ))+". Bu şartlar kabul edilebilir mi?";
			if (PCharDublonsTotal() >= sti(npchar.quest.lcc_summ))
			{
				link.l1 = "Evet, öyleyim.";
				link.l1.go = "licence_2";
			}
			link.l2 = "Ne yazık ki, şu anda yanımda o kadar param yok. Lisans için sonra tekrar geleceğim.";
			link.l2.go = "exit";
		break;
		
		case "licence_r":
			dialog.text = "";
			link.l1.edit = 6;
			link.l1 = "";	
			link.l1.go = "licence_1";
			link.l2 = "Üzgünüm, ama hâlâ biraz düşünmem gerekiyor. Sonra görüşürüz.";	
			link.l2.go = "exit";
		break;
		
		case "licence_2":
			int iQty = sti(dialogEditStrings[6]);
			RemoveDublonsFromPCharTotal(sti(npchar.quest.lcc_summ));
			GiveNationLicence(HOLLAND, iQty);
			// belamour legendary edition на пару с Акулой
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "start")
			{
				if(iQty < 180) 
				{
					Log_info("Quest: 'Together with the Shark' - your license is less than 180 days");
				}
				else 
				{
					pchar.questTemp.SharkGoldFleet.LicenceOk = true;
					AddQuestRecord("SharkGoldFleet", "2");
				}
				pchar.questTemp.SharkGoldFleet = "afterGvik";
			}
			dialog.text = "Bir dakika... Şuraya bir işaret ve mühür koyayım... mühürlendi ve tamam. Al belgeni.";
			link.l1 = "Teşekkürler! Hoşça kal, efendim.";
			link.l1.go = "exit";
		break;
		
		case "trade":
			dialog.text = "Evet, elimizde var. Burada pusula, usturlap, kronometre ve kum saati gibi seyir aletleri satın alabilirsiniz. Ancak, kum saatleri hariç, diğer aletler her zaman stokta olmuyor. Müteahhitlerimiz ve kaptanlarımız bu aletleri çok hızlı alıp götürüyor. Aradığınızı bulamazsanız, stoklarımızı yenilediğimizde, yani bir hafta sonra tekrar uğrayın.\nAyrıca harita ve dürbün de satıyoruz. Nelerimiz olduğuna bakmak ister misiniz?";
			link.l1 = "Evet, lütfen.";
			link.l1.go = "trade_1";
			npchar.quest.trade = "true";
		break;
		
		case "trade_1":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 7)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		// депеша Кромвеля
		case "depeshe":
			dialog.text = "Hm, göster bakalım...(okuyor) Demek öyle... Cromwell’in iştahı giderek artıyor. Kanker! O Püriten köpekler kendi adalarında yeterince kan dökmediler mi ki pisliklerini buraya da taşıyorlar!? Bu raporu nereden buldun?";
			link.l1 = "Onu bir İngiliz kuryesinden aldım. Peki, satın almak ister misiniz?";
			link.l1.go = "depeshe_1";
		break;
		
		case "depeshe_1":
			dialog.text = "Evet. Eminim Peter Stuyvesant bunu okumaktan gerçekten memnun olacak. Ve bunu durdurmak için etkili önlemler alacak... Altın doblonlarla ödeyebilirim ya da sana altı aylık bir ruhsat yazabilirim. Hangisini tercih edersin?";
			link.l1 = "Altını seçiyorum.";
			link.l1.go = "depeshe_dublon";
			link.l2 = "Lisansı istiyorum.";
			link.l2.go = "depeshe_licence";
		break;
		
		case "depeshe_dublon":
			TakeNItems(pchar, "gold_dublon", 700);
			Log_Info("You have received 700 doubloons");
			dialog.text = "Çok iyi. İşte yedi yüz dublonun. İyi yapılmış bir hizmet için güzel bir ödül.";
			link.l1 = "İşte iletiniz.";
			link.l1.go = "depeshe_exit";
		break;
		
		case "depeshe_licence":
			GiveNationLicence(HOLLAND, 180);
			dialog.text = "Güzel. İşte altı aylık süren için lisansın.";
			link.l1 = "Teşekkür ederim! Ve işte sevkiyatınız.";
			link.l1.go = "depeshe_exit";
		break;
		
		case "depeshe_exit":
			RemoveItems(pchar, "Cromvel_depeshe", 1);
			pchar.quest.Terrapin_CromvelScuadron.over = "yes"; //снять прерывание
			ChangeCharacterNationReputation(pchar, HOLLAND, 15);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			dialog.text = "Teşekkürler. Vicdanını ve Cumhuriyet'e olan sadakatini gösterdiğin iyi oldu. Matthias Beck ve Peter Stuyvesant'a bu iyiliğinden bahsedeceğim.";
			link.l1 = "Bunu bilmek güzel. Hoşça kal!";
			link.l1.go = "exit";
		break;
		
		// Sinistra Путеводная звезда
		case "PZ_RazgovorGerrits_1":
			dialog.text = "Korkarım, Schneur ailesiyle birlikte Eski Dünya'ya çoktan gitti. Sanırım bunu size söylemişti.";
			link.l1 = "Evet, doğru. Ama ben, takımadalardaki son işlerinden dolayı gecikmiş olabileceğini ummuştum. Söylesene Gerritz, Şirket’te Rodenburg’la irtibatı sürdüren biri var mı? Belki de kurye gemileriyle?";
			link.l1.go = "PZ_RazgovorGerrits_2";
		break;
		
		case "PZ_RazgovorGerrits_2":
			dialog.text = "Hiç de değil - gitmeden önce, bize asla onu rahatsız etmememizi söyledi - yeni, daha iyi bir hayata başladığını söyledi.";
			link.l1 = "Umarım bizim hayatımız da daha iyi olur. Hoşça kal.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PZ_RazgovorGerrits");
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Manifest kayıtlarını bir kontrol edeyim... Ikema, Immerzeel, Jacobs... Jackson, buldum. Hmm, Kapitein Reginald Jackson şu anda Port Royal ile Philipsburg arasında düzenli sevkiyat yapıyor. Onu bu hatta arayın. Şimdi, kapitein, sizi önceden uyarayım—eğer bir dalavere peşindeyseniz, hiç bulaşmayın, çünkü o Kapitein Jackson bizim korumamız altında. Anlaştık mı, mynheer?";
			link.l1 = "Onunla sadece bir işim var. Sadece basit bir ticaret. Ona hiçbir şekilde zarar vermek gibi bir niyetim yok.";
			link.l1.go = "caleuche_1";
			DelLandQuestMark(npchar);
			DelLandQuestMarkToPhantom();
		break;
		
		case "caleuche_1":
			dialog.text = "Mükemmel. Kapitein Jackson genellikle Port Royal ya da Philipsburg'da uzun süre kalmaz. Sonuçta zaman paradır. Gemisi boşaltılıp tekrar yüklendiği anda genellikle hemen yelken açar. Onu deniz yollarında yakalama şansın daha yüksek olur.";
			link.l1 = "Teşekkür ederim!";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			DialogExit();
			AddDialogExitQuestFunction("Caleuche_PrepareCreateGarpiya");
		break;
		
		// новый босс ГВИК
		case "HWIC_Boss":
			if(CheckAttribute(pchar,"questTemp.HWIC.Detector") && (pchar.questTemp.HWIC.Detector == "holl_win"))
			{
				if (!CheckAttribute(npchar, "quest.silk_info"))
				{
					if (sti(pchar.reputation.nobility) > 60)
					{
						dialog.text = "Aha, Kaptan "+GetFullName(pchar)+"! Geldiğine sevindim. Sana bir iş teklifim var.";
						link.l1 = "İlginç! Sizi dinliyorum, efendim.";
						link.l1.go = "silk_info";
						break;
					}
					else Notification_Reputation(false, 61, "low");
				}
			}
			dialog.text = "Günaydın, Kapitein "+GetFullName(pchar)+"! Size nasıl yardımcı olabilirim?";
			if(CheckAttribute(pchar,"questTemp.HWIC.Detector") && (pchar.questTemp.HWIC.Detector == "holl_win"))
			{
				if(CheckAttribute(npchar, "quest.silk")) // торговля шелком
				{
					if (GetDataDay() == 1 || GetDataDay() == 15)
					{
						link.l1 = "Şu geminin ipeği hakkında...";
						link.l1.go = "trade_silk";
					}
				}
			}
			link.l2 = "Günaydın. Hayır, bir şeye ihtiyacım yok, sadece merhaba demek istedim.";
			link.l2.go = "exit";			
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "silk_info":
			dialog.text = "Yakın zamanda Lyonlu bir tüccarla Karayipler'e gemi ipeği tedarik etmek için ticari bağlantılar kurdum. Bunu duydun mu? Dünyanın en iyi yelkenleri bu ipekten yapılıyor, o yüzden ilgini çekecektir.";
			link.l1 = "Beni çarpsın, evet, bu kulağıma müzik gibi geliyor. Şartların nedir?";
			link.l1.go = "silk_info_1";
		break;
		
		case "silk_info_1":
			dialog.text = "Küçük ama düzenli sevkiyatlar. Her iki haftada bir sizin için otuz rulo ayırabilirim. Bir rulonun fiyatı yirmi dublondur. Şöyle yapalım: Her ayın birinci ve on beşinci gününde sizin için otuz rulo ayıracağım. O günlerde gelip almazsanız, ruloları başka bir müşteriye satarım.";
			link.l1 = "Yani, hiçbir yükümlülük yok mu?";
			link.l1.go = "silk_info_2";
		break;
		
		case "silk_info_2":
			dialog.text = "Kesinlikle, kaptan. İsterseniz ipeği satın alın. Tüm parti için altı yüz doblon ödersiniz. Umarım düzenli müşterimiz olursunuz.";
			link.l1 = "Teklifiniz için teşekkür ederim, mynheer. Anlaştık.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HWIC_Boss";
			npchar.quest.silk_info = "true";
			npchar.quest.silk = "true";
			AddQuestRecordInfo("Unique_Goods", "3");
		break;
		
		// торговля шелком
		case "trade_silk":
			if (CheckAttribute(pchar, "questTemp.UpgradeSilk"))
			{
				dialog.text = "Tabii, kaptan. İpeğiniz sizi bekliyor. Ödemeye hazır mısınız?";
				if (PCharDublonsTotal() >= 2550)
				{
					link.l1 = "Tabii! Al, burada 2.550 dublon var.";
					link.l1.go = "trade_silk_1";
				}
				else
				{
					link.l1 = "Lanet olsun, parayı gemimde unuttum. Hemen getiririm!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Elbette, kaptan. İpeğiniz sizi bekliyor. Ödemeye hazır mısınız?";
				if (PCharDublonsTotal() >= 600)
				{
					link.l1 = "Tabii! Al, altı yüz dublon burada.";
					link.l1.go = "trade_silk_1";
				}
				else
				{
					link.l1 = "Kahretsin, parayı gemimde unuttum. Hemen getiririm!";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.GVIKSilk) >= 1 && !CheckAttribute(pchar, "questTemp.GVIKSilkBlock")) // увеличить объём поставок шёлка
			{
				link.l4 = "Mijnheer "+npchar.name+", ipek tedariklerinin artırılması olasılığını görüşmek isterim.";
				link.l4.go = "UpgradeSilk";
			}
			if(sti(pchar.questTemp.GVIKSilk) >= 1 && CheckAttribute(pchar, "questTemp.GVIKSilkPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок шёлка, если в первый раз не принесли
			{
				link.l4 = "Altınlarınızı getirdim, Mijnheer "+npchar.name+". Lütfen onları kabul edin.";
				link.l4.go = "UpgradeSilk_Agreed";
			}
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "trade_silk_1":
			RemoveDublonsFromPCharTotal(600);
			Log_Info("You have given 600 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Sizinle iş yapmak bir zevkti, kaptan. İpeğiniz uzun kayıkla geminize teslim edilecek.";
			link.l1 = "Teşekkürler!";
			link.l1.go = "trade_silk_2";
		break;
		
		case "trade_silk_2":
			dialog.text = "Umarım yakında görüşürüz. Yine beklerim.";
			link.l1 = "Tabii. Görüşürüz!";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_SHIPSILK, 30);
			DeleteAttribute(npchar, "quest.silk");
			SetFunctionTimerCondition("Silk_TraderAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 150);
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk": //
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "İş yaklaşımınızı takdir ediyorum ve talebinizi değerlendirmeye hazırım. Belki de hacmi, diyelim ki, beş katına çıkarabiliriz. Ancak, böyle bir tedarik için ciddi kaynaklar gerekecek. Depolama alanını genişletmemiz, güvenliği artırmamız ve teslimat yollarını güvenceye almamız gerekecek. Bu sizin de yararınıza olduğundan, masrafları aramızda paylaşmayı öneriyorum.";
				link.l1 = "Tüm bunlar mantıklı geliyor. Bu masrafları karşılamak için ne kadar bir miktar gerektiğini düşünüyorsunuz?";
				link.l1.go = "UpgradeSilk_1";
				Notification_Skill(true, 80, SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "İkmal miktarını artırma isteğinizi anlıyorum, ancak şu aşamada böyle bir değişikliğe onay vermem zor. Gelişme arzunuzdan şüphem yok, fakat bu tür bir anlaşma ticaret konusunda çok daha fazla tecrübe ve kendi adımlarınızda daha fazla özgüven gerektirir. Size, müzakere sanatında bilginizi derinleştirmenizi ve ardından bana daha somut bir teklifle dönmenizi öneririm. Hazır olduğunuzda, iş birliğimizi güçlendirmekten memnuniyet duyarım.";
				link.l1 = "Hmm... Pekala. Bu konuşmaya sonra döneceğim.";
				link.l1.go = "exit";
				Notification_Skill(false, 80, SKILL_COMMERCE);
			}
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk_1":
			dialog.text = "Tüm ayrıntıları göz önünde bulundurursak, masraflardaki payınız üç bin altın dublon olacak. Bu meblağ, gerekli önlemleri gecikmeden almamıza olanak sağlayacak.";
			link.l1 = "Mijnheer "+npchar.name+" , üç bin dublon mu? Bu bir şaka mı? Size dürüst bir teklifle geldim, ama siz benden sadece erzak ayarlamak için bu kadar fahiş bir miktar ödememi mi bekliyorsunuz?";
			link.l1.go = "UpgradeSilk_2";
		break;
		
		case "UpgradeSilk_2":
			dialog.text = "Sizi doğru anlamanızı rica ediyorum. Sizi kandırmaya çalışmıyorum. Bu para, tedariklerin düzenli bir şekilde yürütülmesini sağlayacak miktardır. Söz konusu olan sadece depoları büyütmek ve güvenliği artırmak değil, aynı zamanda bu işin tüm öngörülemezliğine rağmen malların zamanında ve kayıpsız teslimatını garanti altına almaktır. Bu hacimler için standart giderlerdir. Sonuçta, yatırımlarınız kendini fazlasıyla karşılayacak ve malları zamanında, eksiksiz teslim alacaksınız.";
			link.l1 = "Açıklamalarınız bir nebze içimi rahatlattı, mijnheer. Yine de, bu miktar hâlâ çok yüksek. Fiyatı en az iki bin beş yüz dublona indirirseniz şartlarınızı kabul etmeye hazırım. Bu miktarın, erzakları temin etmek ve tüm güvenlik önlemlerini almak için yeterli olacağına eminim.";
			link.l1.go = "UpgradeSilk_3";
		break;
		
		case "UpgradeSilk_3":
			dialog.text = "Anlıyorum, miktar büyük, ama daha önce de söylediğim gibi, işin düzgün yürütülmesi için bu gerekli. Bunu azaltamam, çünkü bu durumda tüm çabalarımız tehlikeye girer. Yine de, kendinizi kandırılmış hissetmemeniz için, size tüm gelecekteki tedariklerde yüzde on beş indirim sunmaya hazırım. Umarım bu, masraflarınızı telafi etmenizi sağlar.";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Hmm, yüzde on beşlik bir indirim elbette bir ilerleme. Peki. Fiyat bana oldukça yüksek gelse de teklifinizi kabul etmeye hazırım. Umarım iş birliğimiz beklentilerimi karşılar. İşte paranız.";
				link.l1.go = "UpgradeSilk_Agreed";
			}
			link.l2 = "Mijnheer "+npchar.name+", teklifiniz bana başka seçenek bırakmıyor. Olsun, üç bin dublon olsun, gerçi bu hatırı sayılır bir meblağ. Fakat şu anda hepsini birden ödeyemem. Parayı bulur bulmaz geri döneceğim.";
			link.l2.go = "UpgradeSilk_5";
			link.l3 = "Yüzde on beş indirim mi? Mijnheer "+npchar.name+", bu beklediğim gibi değil. Bu miktar sadece masraf değil, resmen ve açıkça soygun! Ama seninle ticari ilişkilerimizi kesmeye niyetim yok. Önceki şartlara döneceğiz - 30 top ipek, her biri 20 dublon.";
			link.l3.go = "UpgradeSilk_4";
		break;
		
		case "UpgradeSilk_Agreed":
			dialog.text = "Kabul ettiğine sevindim, "+pchar.name+". Şimdi, ayrıntılara gelecek olursak: 150 top ipek, tanesi 17 dublona. Toplamda - tüm parti için 2550 dublon. Malları her zamanki gibi ayın 1’i ve 15’inde alabilirsin. Bu anlaşmanın iki taraf için de iyi kâr getireceğini düşünüyorum.";
			link.l1 = "Harika! İşte şimdi oldu. Hoşça kalın, mijnheer. Yakında görüşürüz.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HWIC_Boss";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "3_1");
			pchar.questTemp.UpgradeSilk = true;
			pchar.questTemp.GVIKSilkBlock = true;
			DeleteAttribute(pchar, "questTemp.GVIKSilkPotom");
		break;
		
		case "UpgradeSilk_4":
			dialog.text = "This is simply a business arrangement, not robbery, as it may have seemed to you. But, as you wish. Come as usual, on the 1st and 15th, for a batch of silk; I will be glad to strike a new deal.";
			link.l1 = "Elbette, mijnheer. Hoşça kalın.";
			link.l1.go = "exit";
			pchar.questTemp.GVIKSilkBlock = true;
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk_5":
			dialog.text = "Doğru kararı verdiğine sevindim. Parayı getirir getirmez, anlaşmanın tüm ayrıntılarını konuşur ve uygulamaya başlarız.";
			link.l1 = "Hoşça kal, Mijnheer "+npchar.name+". Gerekli miktarı toplar toplamaz görüşürüz.";
			link.l1.go = "exit";
			pchar.questTemp.GVIKSilkBlock = true;
			pchar.questTemp.GVIKSilkPotom = true;
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "fight":
			DialogExit();
			sld = characterFromId("HWIC_officer");
			LAi_SetGuardianTypeNoGroup(sld);
			LAi_group_Attack(sld, Pchar);
			for (i=1; i<=6; i++)
			{	
				sld = characterFromId("HWIC_sold_"+i);
				LAi_group_Attack(sld, Pchar);
			}
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
