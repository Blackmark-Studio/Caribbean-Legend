// Филипп де Пуанси - генерал-губернатор французских колоний
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Terrapin_KathyFox"))
			{
				dialog.text = "Selamlar, "+pchar.name+". Come in; I've already been informed.";
				link.l1 = "Bilgilendirildim mi? Bir yanlışlık olmalı, Ekselansları. Görevinizi başarıyla tamamladığımı bildirmek için geldim, fakat görüyorum ki keyfiniz pek yerinde değil.";
				link.l1.go = "PZ_PoincyAngry1";
				DeleteAttribute(pchar, "questTemp.Terrapin");
				DeleteAttribute(pchar, "questTemp.Terrapin_KathyFox");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "done")
			{
				dialog.text = "Seni görmek güzel, "+pchar.name+". Başarılarından haberdar edildim ve en önemlisi, görevinin üstesinden geldin! Kendini en iyi şekilde gösterdin ve senin hakkında yanılmadığıma sevindim.";
				link.l1 = "Kardeşimi şimdi serbest bırakmanız için yazılı bir emir alabilir miyim?";
				link.l1.go = "serve";
				AddCharacterExpToSkill(pchar, "Sneak", 500);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga") && CheckAttribute(pchar, "questTemp.Sharlie.LevasserDied"))
			{
				dialog.text = "Seni gördüğüme sevindim, "+pchar.name+". Yaptıklarını duydum ve en önemlisi, görevin başarıyla tamamlandı! Yine de, doğrudan saldırıdan daha akıllıca bir fikir beklerdim. Ölen Fransız askerleri için üzüldüm.\nAma savaş, savaştır; her zaman kayıplar olur. Görevini yerine getirdin ve seninle ilgili yanılmadığıma sevindim.";
				link.l1 = "Şimdi kardeşimi serbest bırakmanız için sizden yazılı bir emir alabilir miyim?";
				link.l1.go = "serve";
				DeleteAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga");
				DeleteAttribute(pchar, "questTemp.Sharlie.LevasserDied");
				break;
			}
			// Jason НСО 
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && GetCharacterIndex("Noel") == -1 && pchar.questTemp.Patria != "epizode_12_barondie" && pchar.questTemp.Patria != "epizode_12_baronfail" && pchar.questTemp.Patria != "epizode_12_baronkilled" && pchar.questTemp.Patria != "fail" && pchar.questTemp.Patria != "end")
			{
				if (CheckCharacterItem(pchar, "patent_fra"))
				{
					dialog.text = "Seni görmek güzel, Charles. Öncelikle, Saint-Pierre kolonisini İspanyol istilacılardan koruma gibi zorlu bir görevi başarıyla tamamladığın için seni tebrik etmek isterim. Harika bir iş çıkardın, dostum!";
					link.l1 = "Teşekkür ederim, Şövalye.";
					link.l1.go = "patria";
					Patria_SetInspector();
				}
				else
				{
					dialog.text = "Seni görmek güzel, Charles. Öncelikle, Saint-Pierre kolonisini İspanyol istilacılardan başarıyla koruma konusundaki karmaşık görevi tamamladığın için seni tebrik etmek isterim. Harika bir iş çıkardın, dostum! Sana Donanma ile iş birliği yapman için bir fırsat daha sunuyorum. Fransa, senin gibi subaylara gerçekten muhtaç. Umarım bu sefer daha akıllıca davranırsın ... Al bu patenti, Kaptan Charles de Maure!";
					link.l1 = "Teşekkür ederim, Şövalye. Ülkeme yardım etmekten mutluluk duyuyorum ve ona hizmet etmeye devam etmeye hazırım!";
					link.l1.go = "patria";
					if (!CheckCharacterItem(pchar, "suit1")) GiveItem2Character(pchar, "suit1");
					GiveItem2Character(pchar, "patent_fra");
					EquipCharacterbyItem(pchar, "patent_fra");
					Items[sti(pchar.EquipedPatentId)].TitulCur = 2; 
					Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
					ChangeCharacterNationReputation(pchar, FRANCE, 100);
					Patria_SetInspector();
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria != "fail" && pchar.questTemp.Patria != "end")
			{
				if (!CheckCharacterItem(pchar, "patent_fra"))
				{
					dialog.text = "Charles, beni hayal kırıklığına uğrattın. Düşüncesizce yaptığın hareketlerin sonucu olarak, patentini ve Kraliyet Donanması'ndaki rütbeni kaybettin. Bundan sonra birlikte çalışmamız mümkün değil. Gidebilirsin.";
					link.l1 = "Hmm...";
					link.l1.go = "patria_patentfail";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_1_return")
				{
					dialog.text = "Seni görmek güzel, Charles. Rapor ver!";
					if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
					{
						link.l1 = "İş tamamlandı, San Jose kolonisinden fidye alındı. Ama kötü bir haberim var: kale ile çatışmada 'Eclatant' battı. Kaptanı dikkatli olması için uyarmıştım ama beni dinlemedi ve...";
						link.l1.go = "patria_8_1";
					}
					else
					{
						link.l1 = "İş tamamlandı, San Jose kolonisinden fidye alındı.";
						link.l1.go = "patria_8";
					}
					break;
				}
				// belamour legendary edition фикс проверки мундира с мушкетом
				if(!IsUniformEquip())
				{
					dialog.text = "Monsieur, bugünden itibaren salonuma yalnızca uygun kıyafetle girin!";
					link.l1 = "...";
					link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_2_return" && IsUniformEquip())
				{
					dialog.text = "Baron, Kaptan! Sizi görmek ne güzel!";
					link.l1 = "Görev tamamlandı, Şövalye.";
					link.l1.go = "patria_14";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_3_return" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+", kaptan. Ne haber getirdiniz?";
					if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
					{
						link.l1 = "İspanyollar gerçekten Port-au-Prince’e saldırı planlamıştı. Hispaniola’nın batı ucunda güçlü bir düşman filosuyla karşılaştık. Tamamen yok edildi. Ancak, 'Eclatant' battı.";
						link.l1.go = "patria_26_1";
					}
					else
					{
						link.l1 = "İspanyollar gerçekten Port-au-Prince'e saldırı planlamışlar. Hispaniola'nın batı ucunda güçlü bir düşman filosuyla karşılaştık. Onu tamamen yok ettik.";
						link.l1.go = "patria_26";
					}
					break;
				}
				if (pchar.questTemp.Patria == "epizode_4_return" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+", Charles. Mynheer Stuyvesant nasıl?";
					link.l1 = "Everything's fine, Chevalier. The delivery was successful; here's the reply to your letter.";
					link.l1.go = "patria_31";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_5_return" && IsUniformEquip())
				{
					dialog.text = "Charles, Baron... Şimdiden döndünüz mü?";
					link.l1 = "...";
					link.l1.go = "patria_36";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_6_return" && IsUniformEquip())
				{
					dialog.text = "Bu asık suratını beğenmedim, Charles. Stuyvesant ne dedi? Anlat bakalım!";
					if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "self_win") link.l1 = "Kelimesi kelimesine şöyle dedi: 'Şövalyeye söyle, Sint-Maarten artık onun yönetiminde değil. Yeter artık. Ana devletten gelecek denetim konusunda da - bir şeyler uydursun. De Poincy için her şeyi altüst etmek hiç zor olmadı.' Bu mesajı ilettikten sonra, mynheer beni konuttan kovdu. Görüşmelerimiz böylece sona erdi.";
					else link.l1 = "Şöyle dedi: 'efendin son zamanlarda Sint-Maarten'da fazlasıyla açgözlü davrandı, artık o doymaz iştahını biraz dizginlemenin vakti geldi.' Sonra beni tutuklamaya kalktı. Kılıcımla dövüşerek gemiye ulaşmak zorunda kaldım. Hollanda diplomasisi dedikleri de bu kadar işte.";
					link.l1.go = "patria_43";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_7_go" && IsUniformEquip())
				{
					dialog.text = "Kaptan, sizi bekliyorduk. Mevcut durumu barona anlattım ve kararımı tamamen destekledi. Hollandalılar küstahlıklarının bedelini ödeyecekler.";
					link.l1 = "Savaş mı yani?";
					link.l1.go = "patria_51";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_7_continue" && IsUniformEquip() && pchar.location.from_sea == "Charles_town") // add-7
				{
					Patria_HunterShipChecker();
					if (CheckAttribute(pchar, "questTemp.Patria.Hunter.GiveShip"))
					{
						dialog.text = "Demek, dostum, mallarla birlikte Doğu Hindistan gemisini ele geçirmişsin. Mükemmel!";
						link.l1 = "Gemiyi sana teslim ediyorum, liman görevlilerine emir ver, Şövalye.";
						link.l1.go = "patria_55";
					}
					else
					{
						dialog.text = "Bir sorunuz var mı, Charles?";
						link.l1 = "Şu anda değil, Mösyö. O halde ben gideyim...";
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8" && IsUniformEquip())
				{
					dialog.text = "Nihayet geldiniz, Kaptan! Saint Christopher'da bir acil durum var!";
					link.l1 = "Düşman bir filo mu?";
					link.l1.go = "patria_59";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8_wait" && IsUniformEquip() && GetCompanionQuantity(pchar) < COMPANION_MAX)
				{
					dialog.text = "Bizim kurye lugger'ını üstlenmeye hazır mısın?";
					link.l1 = "Benim.";
					link.l1.go = "patria_64";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8_return")
				{
					dialog.text = "Yüzbaşı de Maure, Mösyö Doily! Sizi görmek ne güzel! Şehrin tamamı, kolonimize göz diken o İspanyol-Hollanda alçaklarına nasıl ders verdiğinizi izledi!";
					link.l1 = "Bu benim görevimdi, Şövalye.";
					link.l1.go = "patria_66";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_9_start" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+", Charles. Başlayalım, olur mu?";
					link.l1 = "Elbette, Şövalye. Bu yüzden buradayım.";
					link.l1.go = "patria_69";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_9_return" && IsUniformEquip())
				{
					dialog.text = "Fransa Kraliyet Donanması'nın Koramiralini ofisimde ağırlamaktan memnuniyet duyuyorum! Evet, dostum, yanılmadın: ataman için emri bizzat ben imzaladım. Resmi olarak Fransa'da da onaylanması gerekiyor, ama bu konuda hiçbir şüphen olmasın. Tebrik ederim!";
					link.l1 = "Ülkeme hizmet ediyorum!";
					link.l1.go = "patria_76";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_10_return" && IsUniformEquip())
				{
					if (GetQuestPastDayParam("questTemp.Patria.Curacao.Date") < 30) sTemp = "will be ready soon and"; // в зависимости от времени сколько добирался
					else sTemp = "is ready and";
					dialog.text = "Başarıya ulaşabildiniz mi? Albay Doily memnun kaldı mı?";
					link.l1 = "Her şey mükemmel geçti, Şövalye. Stuyvesant'ın kervanı ele geçirildi, tüm köleler Jamaika'ya getirildi, albayın filosu "+sTemp+" Curaçao'ya giderken.";
					link.l1.go = "patria_81";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_11_return" && IsUniformEquip())
				{
					dialog.text = "Zafer kazananlara şan olsun! Tebrikler, tebrikler, dostum! Beni şaşırtmaktan hiç vazgeçmiyorsun.";
					link.l1 = "Teşekkür ederim, Şövalye. Stuyvesant cezalandırıldı ve tazminat ödemeye hazır, barış sağlandı ve Saint Martin artık tamamen Fransa'ya ait.";
					link.l1.go = "patria_85";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_continue")
				{
					dialog.text = "Demek tekrar geldin dostum, seni görmek güzel. İyi dinlendin mi?";
					link.l1 = "Evet, Şövalye. Bu ara gerçekten iyi geldi... Hassas bir meseleden bahsetmiştiniz?";
					link.l1.go = "patria_88";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronalive")
				{
					dialog.text = "Arkadaşım, sen kesinlikle bir büyücüsün! Gerçekten büyük bir iş başardın! Baronumuz artık burada bir Ticaret Şirketi kurmak istemiyor.";
					link.l1 = "Şu anda tek dileğinin Paris'e geri dönmek olduğuna inanıyorum.";
					link.l1.go = "patria_103";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_barondie")
				{
					dialog.text = "Charles, baronu duydun mu? Korsanlar tarafından kaçırılmış...";
					link.l1 = "Evet, Şövalye. Ne yazık ki baron öldü. Bundan tamamen eminim.";
					link.l1.go = "patria_112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronfail")
				{
					dialog.text = "Charles, ilerlemen nasıl? Baronu gemine aldığını duydum...";
					link.l1 = "Evet, Şövalye. Gemideydi, onunla ilgileniyordum ama... ateşten öldü.";
					link.l1.go = "patria_x112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronkilled")
				{
					dialog.text = "Charles, ilerlemen nasıl? Baronu gemine aldığını duydum...";
					link.l1 = "Evet, Şövalye. Gemideydi, onunla ilgileniyordum ama... savaşta öldü.";
					link.l1.go = "patria_y112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronwin")
				{
					dialog.text = "Arkadaşım, sen kesinlikle bir büyücüsün! Gerçekten büyük bir iş başardın! Baronumuz artık burada bir Ticaret Şirketi kurmak istemiyor.";
					link.l1 = "Muhtemelen şimdi Paris'e gidiyordur.";
					link.l1.go = "patria_117";
					break;
				}
				dialog.text = "Bir sorunuz var mı, Charles?";
				link.l1 = "Şu anda değil, monsieur. O halde ben yoluma devam edeyim...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Ne istiyorsunuz, monsieur?";
			link.l1 = "Önemli bir şey yok, sadece nezaket ziyareti. Şimdi gidiyorum...";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// в тюрьме при старте игры
		case "Puancie_Jail":
			dialog.text = "İyi günler Charles. Kendimi tanıtmama izin ver: Ben Philippe de Poincy ve...";
			link.l1 = "Beni neden hapishaneye attınız, ne cüretle? Bu kabul edilemez! Ben bir Fransız soylusuyum ve...";
			link.l1.go = "Puancie_Jail_1";			
			// belamour legendary edition -->
			link.l2 = "İyi... günler mi demeliyim? Güzel şaka, efendim. Benim kim olduğumu nereden biliyorsunuz?";
			link.l2.go = "Puancie_Jail_1a";	
		break;
		
		case "Puancie_Jail_1a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			dialog.text = "Genç adam, sözümü kesmemenizi rica ediyorum! Karayip takımadalarındaki Fransız kolonilerinin Genel Valisi ile konuşuyorsunuz! Küstah tavrınızı yalnızca karşınızda kimin olduğunu bilemeyeceğiniz için affediyorum. Ama size daha temkinli davranmanızı tavsiye ederim.";
			link.l1 = "Hmm... Üzgünüm, Ekselansları.";
			link.l1.go = "Puancie_Jail_2";
		break;
		
		case "Puancie_Jail_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "FencingL", 10);
			AddCharacterExpToSkill(pchar, "FencingS", 10);
			AddCharacterExpToSkill(pchar, "FencingH", 10);
			AddCharacterExpToSkill(pchar, "Pistol", 10);
			// <-- legendary edition
			dialog.text = "Beni iyi dinle, genç adam, ve sakın sözümü kesme! Karayip takımadalarındaki Fransız kolonilerinin Genel Valisiyle konuşuyorsun! Kime hitap ettiğini bilmediğinden dolayı sana bu üslubunu affediyorum. Ama sana tavsiyem, bundan sonra daha ölçülü olman.";
			link.l1 = "Hm... Affedersiniz, Ekselansları.";
			link.l1.go = "Puancie_Jail_2";			
		break;
		
		case "Puancie_Jail_2":
			dialog.text = "Daha iyi. Şimdi, önceki soruna gelirsek – yanlışlıkla İspanyol casusu sanıldın ve durumun netleşene kadar tutuklandın. Şu lanet Kastilyalılar son zamanlarda iyice hareketlendi, bu yüzden şüpheli görünen herkesi tutuklatma emri verdim. Ama artık kim olduğunu biliyoruz – sen gerçekten Michel de Monper’in kardeşi Charles de Maure’sun ve seni serbest bırakmak için bizzat buraya geldim. Ama sen bana küçük bir çocuk gibi bağırıyorsun!";
			link.l1 = "Affedersiniz Ekselansları, tekrar soruyorum. Artık gidebilir miyim?";
			link.l1.go = "Puancie_Jail_3";			
		break;
		
		case "Puancie_Jail_3":
			dialog.text = "Evet, öylesin. Ama çavuş hücreni açmadan önce seninle baş başa konuşmak istiyorum. Biliyor musun, Malta Tarikatı'nın en değerli savaşçılarından biri olan kardeşin tutuklandı ve gözetim altına alındı?";
			link.l1 = "Kardeşimin başının dertte olduğunu ve yardıma ihtiyacı olduğunu biliyordum. Bu yüzden Paris'ten buraya geldim.";
			link.l1.go = "Puancie_Jail_4";			
		break;
		
		case "Puancie_Jail_4":
			dialog.text = "Bunu duyduğuma sevindim. Bilmeni isterim ki, Mösyö de Monper ciddi bir belada. Ona yetkiyi kötüye kullanma, mal varlığını zimmete geçirme ve yalan beyanda bulunma suçlamaları yöneltmem için her türlü sebebim var. Ama ona yardım edebilirsin.";
			link.l1 = "Monsieur, bana daha fazlasını anlatır mısınız? Anlamıyorum, Michel Tarikat'ın gururuydu ve...";
			link.l1.go = "Puancie_Jail_5";			
		break;
		
		case "Puancie_Jail_5":
			dialog.text = "Ben de öyle düşünmüştüm. Hepimiz öyle düşünmüştük! Ama son zamanlardaki davranışları bizi... Tarikata olan sadakati konusunda şüpheye düşürdü, bu yüzden tutuklandı. Ayrıntıları sana Michel'in kendisi anlatacak. Sana, suçlamalarla başa çıkmasına ve rezaletten kurtulmasına nasıl yardımcı olabileceğini açıklayacak.";
			link.l1 = "Kardeşim şimdi nerede? Onun hapiste olduğunu söylediniz, ama etrafta hiç görmedim...";
			link.l1.go = "Puancie_Jail_6";			
		break;
		
		case "Puancie_Jail_6":
			dialog.text = "Ben hapsedildi mi dedim, genç adam? Beni dinliyor musun?! Tutuklu dedim! Bu aynı şey değil. Michel de Monper, Malta Şövalyeleri'ne ait olan Saint Pierre'in yeraltı üssünde tutuklu olarak tutuluyor.\nSana üsse sınırsızca girme ve kardeşinle istediğin sıklıkta konuşma izni veriyorum. Şövalyelerin subayları ve askerleri talimatlarımı biliyorlar ve seni durdurmayacaklar.";
			link.l1 = "O yeraltı üssü nerede?";
			link.l1.go = "Puancie_Jail_7";			
		break;
		
		case "Puancie_Jail_7":
			dialog.text = "Tabii ki burada, Saint Pierre'de. Yerel hapishaneyi bul ve Tarikat'ın sembolleriyle işaretlenmiş kapıdan gir. Bodrumun ikinci katındaki cephaneliğe in. Monsieur Monper orada olacak. Ama endişelenme: hapishaneden çıkarken seni karşılayıp kardeşinin yanına götürecekler – her şeyi ayarladım... Hepsi bu. Umarım tekrar görüşürüz, Charles. Çavuş!";
			link.l1 = "Lütfen bekleyin, Ekselansları! Peki ya... eşyalarım? Kılıcım ve diğerleri?";
			link.l1.go = "Puancie_Jail_8";			
		break;
		
		case "Puancie_Jail_8":
			dialog.text = "Eşyalarınız, kardeşinizin borcunu ödemek için el konuldu. Elveda, Mösyö de Maure.";
			link.l1 = "Ne halt...";
			link.l1.go = "Puancie_Jail_9";			
		break;
		
		case "Puancie_Jail_9":
			DialogExit();
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Sharlie_GoFromPrison", 3.5);
			NextDiag.CurrentNode = "First time";
			locCameraFromToPos(-11.09, 0.65, 3.05, true, -12.59, 0.09, -4.66);
		break;
		
		// возвращаем деньги
		case "saga":
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Charles_townhall", "reload1_back", false);
			dialog.text = "Aha, Charles de Maure bizzat kendisi! Sizi görmek güzel. Sanırım buraya kardeşinizin kaderini konuşmaya geldiniz?";
			link.l1 = "Michel de Monper’in Düzen’e ve size şahsen borçlu olduğu her şeyi ödemeye hazırım.";
			if (sti(pchar.money) >= 1000000) link.l1.go = "saga_1";
			else link.l1.go = "saga_exit";			
		break;
		
		case "saga_exit":
			dialog.text = "Hm... Ama para nerede? Tuhaf bir mizah anlayışın var, delikanlı, ve ben bunu anlamıyorum.";
			link.l1 = "Affedersiniz, Şövalye. Paramı gemideki dolabımda unuttum. Hemen döneceğim.";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_repeat";	
		break;
		
		case "saga_repeat":
			dialog.text = "Parayı getirdin mi, Charles?";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "Elbette! Umarım bu miktar tüm masraflarınızı tamamen karşılar.";
				link.l1.go = "saga_1";
			}
			else
			{
				link.l1 = "Henüz değil...";
				link.l1.go = "exit";
				NextDiag.TempNode = "saga_repeat";
			}		
		break;
		
		case "saga_1":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Charles");
			AddMoneyToCharacter(pchar, -1000000);
			dialog.text = "Harika! Onları senden alacağım. Kendini en iyi şekilde gösterdin, Charles!";
			link.l1 = "Michel de Monper'in serbest bırakılması emrini ne zaman alacağım?";
			link.l1.go = "saga_2";			
		break;
		
		case "saga_2":
			dialog.text = "Acele etme, delikanlı. Borçlarını ödeyip aileni korumak için kendi hayatını tehlikeye atmanı takdir ediyorum. Bu devirde nadir rastlanan bir asalet... Ama bu üzücü hikâyenin asıl meselesi para değil. Kardeşin, çok hassas bir görevi yerine getirmek şartıyla bu kadar büyük bir meblağ aldı.\nSadık bir Katolik olarak Michel de Monper, Tarikat ve Kutsal Kilise'nin şanı için küstah bir sapkını cezalandırmaya ve onun çiğnediği adaleti yeniden sağlamaya yemin etmişti...";
			link.l1 = "Ama tutukluyken sözünü tutamaz! Onu serbest bırakırsanız, ikimiz birlikte görevi benim tek başıma yapmamdan çok daha hızlı tamamlayabiliriz.";
			link.l1.go = "saga_3";			
		break;
		
		case "saga_3":
			dialog.text = "Bakın, dostum, kardeşiniz bana ona güvenmemem için sağlam bir sebep verdi. Onun kaçıp yeminini bozmayacağına dair hiçbir garanti yok. Yani, üzerindeki tüm suçlamaları kaldırmak istiyorsanız – yemin eden siz olun. Ayrıntıları size Monsieur de Monper anlatacak.";
			link.l1 = "Hm... Bunu beklemiyordum. Ama bana başka seçenek bırakmıyorsun. Son kararımı kardeşimle konuştuktan sonra vereceğim.";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_4":
			dialog.text = "Sana gerçekten ısınmaya başladım, Charles. Belki bir gün dost olabiliriz. Her neyse, bu kardeşini son kez serbest bırakışım. Sana söz veriyorum, eğer kardeşinin yapmadığını sen yaparsan, ailenin itibarı zarar görmeyecek. Ve gelecekte dostluğuma güvenebilirsin.";
			link.l1 = "Sizi tamamen anlıyorum. Hoşça kalın!";
			link.l1.go = "saga_5";			
		break;
		
		case "saga_5":
			DialogExit();
			pchar.questTemp.Saga = "mishelle";//Сага - старт
			AddQuestRecord("Sharlie", "21");
			NextDiag.CurrentNode = "First time";
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
		break;
		
		case "serve":
			dialog.text = "Endişelenme, "+pchar.name+", sözümü tutacağım. Kardeşin serbest bırakılacak ve tüm suçlamalar düşecek. Aileni artık kimse lekeleyemez. Bunu tamamen senin çabalarına borçluyuz, sadece senin. Baban böyle bir evlat yetiştirdiği için gurur duyabilir.";
			link.l1 = "Güzel sözleriniz için teşekkür ederim, Şövalye. Hemen Martinique'e gidebilir miyim?";
			link.l1.go = "serve_1";	
			Island_SetReloadEnableGlobal("Tortuga", true);
			CloseQuestHeader("Terrapin");
			SetFunctionTimerCondition("Terrapin_SetFontene", 0, 0, 5, false); // таймер
		break;
		
		case "serve_1":
			dialog.text = "Bir dakika bekle, dostum. Sana dostum diyebilirim, değil mi? Şükranlarımı bizzat sunmak istiyorum. Buraya geldiğinden beri ilerlemeni izliyorum ve yaptıklarının çoğundan haberdarım. Karayipler'de kendine epey bir isim yaptın ve hiç şüphesiz, bazı çevrelerde tanınıyor ve saygı görüyorsun. Fransa'nın senin gibi insanlara ihtiyacı var\nKaptan "+GetFullName(pchar)+"! Majesteleri Fransa Kralı'nın bana verdiği yetkiyle, size Kraliyet Donanması'nda kaptanlık rütbesi teklif etme ve Fransız donanmasına ait bir gemiyi, hafif fırkateyn 'Gryffondor'u, emrinize verme onuruna sahibim!\nÖnceki kaptanı de Fontenot, sizin sayenizde Tortuga'nın valisi olacak ve Karayipler'in en iyi hafif fırkateyni yeni bir kaptana ihtiyaç duyuyor. Bu teklifi kabul ediyor musunuz?";
			link.l1 = "İlginç.   Peki, karşılığında ne istiyorsun?";
			link.l1.go = "serve_2";		
		break;
		
		case "serve_2":
			dialog.text = "Sadece biraz. Avının onda biri ve ara sıra hassas görevleri tamamlamak. Kararını bekliyorum.";
			link.l1 = "Böyle bir teklifi kimse reddetmez, Ekselansları! Ülkeme hizmet etmek benim için bir onurdur!";
			link.l1.go = "serve_3";
			link.l2 = "Kusuruma bakmayın, haddimi aşmak istemem ama teklifinizi şimdilik kabul edemem. Aile işlerim, derhal memlekete dönmemi gerektirebilir.";
			link.l2.go = "serve_no";
			InterfaceStates.Buttons.Save.enable = true;
		break;
		
		case "serve_no":
			ChangeCharacterComplexReputation(pchar, "fame", 7);
			dialog.text = "Pity. I had hoped that you would agree... But nevertheless, I am forced to ask you for one more favour; actually, it is in your interest as well. Martinique is under attack. There is heavy fighting in the port and in the city itself.\nAlas, I have no one else to send there to help the garrison but you. I ask you, as a patriot of your Fatherland, to repel the assault by any means necessary. I hope that you have enough resources to do so.\nBesides, your brother is still there; you can save his life.";
			link.l1 = "Kardeşim tehlikede mi? Hemen gidiyorum!";
			link.l1.go = "serve_exit";			
		break;
		
		case "serve_3":
			dialog.text = "Ne kadar onurlu sözler! Gerçek bir asker ve vatanına sadık bir evladın sözleri bunlar! Tebrikler, monsieur "+GetFullName(pchar)+". Fransa deniz kuvvetlerinin komutanı rütbesine terfi ettiniz. Bu üniformayı benden kabul edin. Onu gururla taşıyın ve layık olun!";
			link.l1 = "Ülkeme hizmet ediyorum!";
			link.l1.go = "serve_4";	
			locCameraFromToPos(-2.63, 2.20, -4.96, true, 2.64, 0.22, -4.96);
			npchar.greeting = "puancie_1";			
		break;
		
		case "serve_4":
			dialog.text = "Artık ağır korvet 'Gryffondor' sizin emrinizde. Bu andan itibaren, bu mükemmel gemi size ait. Onun üstün niteliklerini Majestelerinin şanı ve Fransız etkisini Karayip takımadalarında güçlendirmek için kullanın!";
			link.l1 = "Hemen!";
			link.l1.go = "serve_5";
			LAi_Fade("SharlePutsSuit", "");
		break;
		
		case "serve_5":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "Ama filonuz zaten çok kalabalık, bu yüzden bir gemiden kurtulduğunuzda 'Gryffondor'u almak için geri gelin.";
				link.l1 = "Pekâlâ. Bunu yapacağım.";
				link.l1.go = "serve_wait";		
			}
			else
			{
				dialog.text = "Gemiyle birlikte, mevcut kaptanı ve mürettebatı da alacaksınız. İsterseniz kaptanı komutanız altında tutabilir ya da gemiden alabilirsiniz, biz de ona başka bir görev buluruz.";
				link.l1 = "Anladım!";
				link.l1.go = "serve_6";
			}
		break;
		
		case "serve_6":
			dialog.text = "Ama kötü haberlerim var kaptan. Az önce Martinique'in saldırı altında olduğunu öğrendim. Limanda ve şehrin içinde şiddetli çatışmalar yaşanıyor.\nNe yazık ki garnizona yardım gönderecek kimsem yok, sadece seni gönderebilirim. İşte ilk görevin:\n Saint Pierre'i koru! Ayrıca, kardeşin hâlâ orada, onun hayatını kurtarabilirsin.";
			link.l1 = "Kardeşim tehlikede mi? Hemen geliyorum!";
			link.l1.go = "serve_7";
		break;
		
		case "serve_7":
			DialogExit();
			locCameraTarget(PChar);
			locCameraFollow();
			CreateGriffondor();
			sld = characterFromId("GriffOfficer");
			SetCharacterRemovable(sld, true);
			SetCompanionIndex(pchar, -1, sti(sld.index));
			sld.loyality = MAX_LOYALITY;
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Terrapin");
			pchar.questTemp.Sharlie = "senpierbattle";
			pchar.questTemp.Sharlie.DefendSP = "true";
			AddQuestRecord("Sharlie", "24");
			pchar.quest.DefendSP_prepare.win_condition.l1 = "location";
			pchar.quest.DefendSP_prepare.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_prepare.function = "DefendSP_PrepareMartinique";
			AddCharacterExpToSkill(pchar, "Leadership", 2000);
			AddCharacterExpToSkill(pchar, "Fortune", 500);
		break;
		
		case "serve_wait":
			DialogExit();
			NextDiag.CurrentNode = "serve_shipcheck";
		break;
		
		case "serve_shipcheck":
			dialog.text = "'Gryffondor'u komutanız altına almaya hazır mısınız?";
			if (GetCompanionQuantity(pchar) > 4)
			{
				link.l1 = "Henüz değil, filodaki gemilerimi yeniden konumlandırıyorum...";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "Benim.";
				link.l1.go = "serve_5a";
			}
			NextDiag.TempNode = "serve_wait";
		break;
		
		case "serve_5a":
			dialog.text = "Harika! Gemiyle birlikte, mevcut kaptanı ve mürettebatı da alacaksınız. İsterseniz kaptanı emrinizde tutabilir ya da gemiden aldırıp ona başka bir görev bulmamızı isteyebilirsiniz.";
			link.l1 = "Anlaşıldı!";
			link.l1.go = "serve_6";
		break;
		
		case "serve_exit":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Terrapin");
			pchar.questTemp.Sharlie = "senpierbattle";
			pchar.questTemp.Sharlie.DefendSP = "true";
			AddQuestRecord("Sharlie", "23");
			pchar.quest.DefendSP_prepare.win_condition.l1 = "location";
			pchar.quest.DefendSP_prepare.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_prepare.function = "DefendSP_PrepareMartinique";
			AddCharacterExpToSkill(pchar, "Leadership", 1000);
			AddCharacterExpToSkill(pchar, "Fortune", 250);
		break;
		
		// Jason НСО
		case "patria":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) DeleteAttribute(pchar, "questTemp.Mtraxx.CharleePrince"); // Rebbebion, удалить команду пиратов на всякий
			DelCharleePrince("");
			dialog.text = "Ve bu sadece başlangıç, Mösyö! Böyle askeri yeteneklerle çok ilerleyeceğinizden eminim! Ayrıca, sizin gibi mükemmel bir deniz subayı için bir başka görevim daha var ve bundan da en az öncekiler kadar başarıyla çıkacağınıza inanıyorum. Üstelik, bu görev doğrudan önceki vazifenizle ilgili.";
			link.l1 = "Sizi dinliyorum, monsieur";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "Ama önce, ofisime giren kişiyi size tanıtayım. Karşınızda Baron Noel Forget, Fransız Batı Hint Ticaret Şirketi'nin fahri üyesi. Takımadalarımıza, kolonilerimizi denetlemek, şeker kamışı ve diğer mahsullerin üretimini genişletmek ve bölgemizde ticaret ilişkilerini geliştirme imkanlarını araştırmak için geldi. Paris'ten, bu konularda kendisine her türlü destek ve yardımın sağlanması emredildi; biz de elbette bunu yerine getireceğiz. Baron, size Fransa'nın hizmetindeki en yetenekli kaptanlardan biri olan Mösyö Charles de Maure'u takdim ediyorum...";
			link.l1 = "";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			DialogExit();
			sld = characterFromId("Noel");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "patria_3":
			dialog.text = "Yani Charles, baronla birlikte Saint Christopher'ı teftiş ederken sana şu görevi veriyorum. Hiç kimse Fransız yerleşimlerine saldırıp cezasız kalamaz ve İspanyollar, Martinique'e yaptıkları saldırıdan dolayı zaten bir ders almış olsalar da, suçlarının bedelini ceplerinden ödemeli ve kolonide verdikleri zararı telafi etmeliler.\nFransız baronla birlikte, güçlü bir filo geldi; içinde kudretli 66 toplu 'Eclatant' gemisi de var. Geminin kaptanı tecrübeli bir denizci ama Karayipler'de ilk kez bulunuyor, bu yüzden senin komutanlığın altına giriyor. 'Eclatant' ile birlikte, İspanyollara ait Trinidad adasının kıyılarına yelken açacak ve Saint Pierre'e yapılan saldırı için İspanyollardan üç yüz bin peso tazminat talep edeceksin.";
			link.l1 = "Chevalier, gerçekten İspanyolların kabul edeceğine inanıyor musunuz?";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "Bundan eminim - 'Eclatant' ve filonuz Fort San Jose'yi yerle bir ettikten sonra. Asker çıkarmak ve şehri ele geçirmek, asker kaybetmek sanırım gerekmeyecek. Hiçbir uyarı vermeden saldırın, kaleyi yok edin ve ardından komutana şartlarınızı bildirmek istediğinizi işaret edin. Bu durumda, İspanyolların kaçacak yeri kalmayacak ve ödemeyi tercih edeceklerdir. Siz olsaydınız, korumasız kalan bir şehrin valisi olarak ne yapardınız?";
			link.l1 = "Hmm, makul görünüyor, Şövalye.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "Ne yapman gerektiği açık mı?";
			link.l1 = "Evet, Ekselansları.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			// belamour legendary edition фикс проверки мундира с мушкетом
			if(IsUniformEquip())
			{
				dialog.text = " O halde hemen başla. İşte 'Eclatant' gemisinin kaptanına yetkini onaylayan bir mektup. Bu mükemmel gemi ve eğitimli mürettebatı artık emrinde. Charles, artık Fransa'ya hizmet ettiğini unutma ve benim gibi yetkililerle düzgün iletişim kurmak için üniforma giymen tavsiye edilir. Sana çok yakışıyor. İyi şanslar, Kaptan de Maure!";
			}
			else
			{
				dialog.text = " O halde hemen işe koyul. İşte 'Eclatant' gemisinin kaptanına yetkini onaylayan bir mektup. Bu mükemmel gemi ve eğitimli mürettebatı artık emrinde. Ha, bu arada Charles: Sana emrediyorum, bir kaptan üniforması giy! Birincisi, Fransız Kraliyet Donanması'nın bir subayının bir tüccar ya da sıradan bir korsan gibi görünmesi yakışık almaz; ikincisi ise, üniforma sana gerçekten çok yakışıyor. Emrimi derhal yerine getir, Kaptan de Maure!";
			}
			link.l1 = "";
			link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "1");
			pchar.questTemp.Patria = "epizode_1";
			Patria_SetEcliaton();
			pchar.questTemp.GoldenGirl_Block = true;	// Запрещаем квест Дороже Золота
		break;
		
		case "patria_8_1":
			if (sti(pchar.money) >= 300000) AddMoneyToCharacter(pchar, -300000);
			else pchar.questTemp.Patria.NoMoney = "true";
			dialog.text = "'Eclatant' battı mı? Charles, bu tam bir felaket! Bakan şimdi ne diyecek? Beni hayal kırıklığına uğrattın, Charles! Tecrübene güvenebileceğimden emindim, ama sen... Ne yazık ki, bunun hesabını sen vereceksin. Bir rapor yazacağım, ve senin bir süre ortadan kaybolsan iyi olur. Kraliyet Donanması'ndaki hizmetin sona erdi.";
			link.l1 = "Hmm... Üzgünüm, Mösyö. Görünen o ki, bakanın öfkesi dinene kadar bir-iki ay ortadan kaybolmam en iyisi olacak. Hoşça kalın ve tekrar söylüyorum, sizi hayal kırıklığına uğrattığım için gerçekten üzgünüm.";
			link.l1.go = "patria_8_2";
		break;
		
		case "patria_8_2":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Patria = "fail";
			AddQuestRecord("Patria", "8");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			RemoveItems(pchar, "patent_fra", 1);
			if (CheckAttribute(pchar, "questTemp.Patria.NoMoney"))
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -20);
				ChangeCharacterNationReputation(pchar, FRANCE, -30);
				DeleteAttribute(pchar, "questTemp.Patria.NoMoney");
			}
			else
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -5);
				ChangeCharacterNationReputation(pchar, FRANCE, -5);
			}
			pchar.quest.Patria_SanJoseReturnOver.over = "yes"; // снять таймер
		break;
		
		case "patria_8":
			if (sti(pchar.money) >= 300000)
			{
				dialog.text = "Mükemmel!";
				link.l1 = "Buyurun, lütfen bu üç yüz bin altını alın.";
				link.l1.go = "patria_9";
			}
			else
			{
				dialog.text = "Mükemmel, ama para nerede, Charles?";
				link.l1 = "Hah, gemideki sandıkta. Hemen getiririm!";
				link.l1.go = "patria_8_3";
			}
		break;
		
		case "patria_8_3":
			DialogExit();
			npchar.dialog.currentnode = "patria_8_4";
		break;
		
		case "patria_8_4":
			dialog.text = "Peki Charles, Trinidad'dan fidyeyi getirdin mi?";
			if (sti(pchar.money) >= 300000)
			{
				link.l1 = "Evet, Mösyö. İşte burada.";
				link.l1.go = "patria_9";
			}
			else
			{
				link.l1 = "Hemen getiriyorum!";
				link.l1.go = "patria_8_3";
			}
		break;
		
		case "patria_9":
			AddMoneyToCharacter(pchar, -300000);
			dialog.text = "Senden memnunum Charles, beni hiç hayal kırıklığına uğratmıyorsun. Görev kolay değildi ve ödül olarak kurtarma bedelinden 50.000 peso sana veriliyor. Al, hepsi senin.";
			link.l1 = "Teşekkür ederim, Şövalye.";
			link.l1.go = "patria_10";
		break;
		
		case "patria_10":
			AddMoneyToCharacter(pchar, 50000);
			dialog.text = "Sana şimdiden yeni bir görev var. Monsieur Forget, Saint Christopher'daki denetimini tamamladı ve şimdi kuzey kolonilerimizi ziyaret etmek istiyor. Baronu Tortuga ve Hispaniola'ya götürmeni, işlerinde ona her şekilde yardımcı olmanı ve taleplerini yerine getirmeni istiyorum. Anlaşıldı mı, Charles?";
			link.l1 = "Elbette, Şövalye.";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "Baronun zamanı kısıtlı, bu yüzden sizden başka işlerle oyalanmamanızı ve yolculuğu iki aydan fazla geciktirmemenizi rica ediyorum.";
			link.l1 = "Elbette, Mösyö. Adalar arasındaki yolculuk fazla zaman almaz, tabii Mösyö Forget'nin kolonilerdeki işleri uzun sürmezse.";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "Mükemmel. O halde Baron sizin geminizle seyahat edecek. Ona en iyi kamarayı ayarlayın.";
			link.l1 = "Elbette, Şövalye!";
			if(IsUniformEquip()) link.l1.go = "patria_13";
			else link.l1.go = "patria_13_1";
		break;
		
		case "patria_13_1":
			dialog.text = "And one more thing, Charles: you're without your officer's uniform again! This is your last warning. From this moment onwards, I ask you to come to me only in uniform; otherwise, I will not listen to you. You are on duty, and discipline should be everything, especially in the appearance of a naval officer!";
			link.l1 = "Beni affedin, Şövalye. Bir daha olmayacak.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "9");
			pchar.questTemp.Patria = "epizode_2";
			Patria_VisiterBegin();
			pchar.quest.Patria_SanJoseReturnOver.over = "yes"; // снять таймер
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterComplexReputation(pchar, "nobility", 3); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "patria_14":
			sld = characterFromId("Noel");
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto4");
			dialog.text = "Seyahatinizin başarılı olacağından hiç şüphem yoktu. Tortuga'dan ya da Port-au-Prince'den bir haber var mı?";
			link.l1 = "...";
			link.l1.go = "patria_15";
		break;
		
		case "patria_15":
			DialogExit(); // переключение на инспектора
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Noel"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_16";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "patria_16":
			dialog.text = "";
			link.l1 = "Evet, Şövalye, haberlerim var ama pek hoş sayılmaz. Öncelikle, Port-au-Prince Valisi, İspanyolların koloniyi saldırıya hazırladığından emin ve bunun için... hmm, adı neydi... evet, Santiago'da bir askeri filo topluyorlar. Ve bu sadece bir söylenti gibi durmuyor. Bence bu meseleyi görmezden gelemeyiz, özellikle de Port-au-Prince'in plantasyonları şimdiye kadar gördüklerimin en iyileri arasında.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "İspanyollar Port-au-Prince'e saldırmaya mı hazırlanıyor? Hımm... Pekâlâ. Bu işle ilgilenmeni emredeceğiz Kaptan Charles de Maure. 'Eclatant' yeni onarıldı, donatıldı ve yelken açmaya hazır...";
			link.l1 = "Bir de şu var, Mösyö: Paris'te buranın kuzeyinde yer alan Saint Martin adası Fransız kolonisi olarak biliniyor, ama Kaptan Charles de Maure bana orada Hollandalıların hâkim olduğunu söyledi. Bu doğru mu, Şövalye?";
			link.l1.go = "patria_18";
		break;
		
		case "patria_18":
			dialog.text = "Hmm... Bu bir yere kadar doğru. Saint Martin bir Fransız kolonisi. Ancak Baron, ekonomik açıdan bakarsak, bu ada tamamen işe yaramaz - alanı küçük, toprağı verimsiz ve çorak, tatlı su neredeyse yok denecek kadar az, kuyularda olan azıcık su da çamurlu ve acı. Hatta orada içmek için yağmur suyu toplandığını bile duydum.\nBu yüzden Saint Martin, uzun vadeli bir kira sözleşmesiyle Hollanda Batı Hint Ticaret Şirketi'ne devredildi; şirket de adayı bölgeden metropole giden gemileri için kuzeyde bir aktarma noktası olarak kullanıyor. Hollandalılar orada Philipsburg yerleşimini büyüttüler, bir kale ve liman inşa ettiler ve takımadaya görece yakın zamanda gelenler için, mesela Kaptan Charles de Maure gibi, Saint Martin bir Hollanda kolonisi gibi görünebilir.";
			link.l1 = "Ama hukuken ada bize mi ait?";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			dialog.text = "Elbette. Ama dediğim gibi, kiradan para kazanmak, oradaki kıt kaynakları kullanmaktan daha kârlı.";
			link.l1 = "Bana öyle geliyor ki, bu ada Karayipler'de ortaya çıktığında Fransız Batı Hint Ticaret Şirketi için çok faydalı olacak. Az önce açıkladığınız anlamı - Avrupa yolundaki kuzey karakolu. Bu koloniyi ziyaret etmem gerekiyor ve adanın Hollandalılara kiralanmasının sona erdirilmesi de çok muhtemel.";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "Öncelikle Willemstad'a, Hollanda Batı Hindistan Ticaret Şirketi'nin müdürü Peter Stuyvesant'ın Mint'ine bir dilekçe göndermelisin. Adada inceleme yapılabilmesi için onun izni şart – sonuçta Hollandalılar orada uzun zamandır bulunuyor.";
			link.l1 = "O zaman Willemstad'a bir ulak göndermemiz gerekiyor.";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			dialog.text = "Sorun şu ki, Bay Stuyvesant Willemstad'da nadiren bulunuyor, sürekli seyahat ediyor ve Şirket'in işlerini kalyonunda hallediyor...";
			link.l1 = "En azından arada sırada orada bulunuyordur, öyle değil mi? Her neyse, Hollandalıların adanın asıl sahipleri tarafından denetlenmesini sağlaması gerekiyor. Neden Philipsburg Valisi'ne bir mektup göndermiyoruz?";
			link.l1.go = "patria_22";
		break;
		
		case "patria_22":
			dialog.text = "Mynheer Martin Thomas, with all due respect to him, is just a simple employee; the real management is carried out by the Company. Baron, I will solve this problem, don't worry. It will take some time.";
			link.l1 = "Eh, vaktim bol. Sonuçta, güney kolonilerini, Guadeloupe ve Martinique'i de ziyaret etmemiz gerekiyor. Ne yazık ki bu sefer Kaptan Charles de Maure bana eşlik etmeyecek – yine Hispaniola'ya gitmesi gerekiyor...";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetActorType(pchar); // 17-add
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_24";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
		break;
		
		case "patria_24":
			dialog.text = "Evet, evet, sevgili kaptanımızı sıkıcı sohbetlerimizle oyalıyoruz! Charles, 'Eclatant' ile filoya katıl, Hispaniola'ya ilerle ve İspanyollardan Port-au-Prince için gerçek bir tehdit olup olmadığını öğren. Eğer varsa, gereğini yap. Ama sana bunları öğretmek bana düşmez, sen benden çok daha iyi bilirsin. Eğer bir şey bulamazsan, zamanını boşa harcama, burada sana ihtiyacım var. Raporunu en geç bir ay içinde bekliyorum. İyi şanslar, dostum!";
			link.l1 = "Teşekkür ederim, Şövalye. Hemen yelken açacağım.";
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10) link.l1.go = "patria_25_1";
			else link.l1.go = "patria_25_2";
		break;
		
		case "patria_25_1":
			dialog.text = "And one more thing, Charles: I heard you have problems with the Dutch authorities? Please, settle this issue as soon as possible; in the near future, you will have to visit their colonies. As you understand, that would be impossible under fire from the forts.";
			link.l1 = "Pekâlâ, Mösyö, dediğiniz gibi olacak.";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25_2":
			dialog.text = "Ve bir şey daha, Charles: Seni uyarıyorum, Hollandalılarla herhangi bir çatışmadan kaçın. Yakın zamanda onların kolonilerini ziyaret etmen gerekecek. Anladığın gibi, kalelerden ateş açılırken bu imkânsız olur...";
			link.l1 = "Pekâlâ, Mösyö. Hollandalılarla hiçbir sorunum yok.";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "15");
			pchar.questTemp.Patria = "epizode_3";
			Patria_PortPaxBegin();
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_26_1":
			dialog.text = "'Eclatant' battı mı? Charles, bu tam bir felaket! Bakan şimdi ne diyecek? Beni hayal kırıklığına uğrattın, Charles! Tecrübenle sana güvenebileceğimden emindim, ama sen ... Ne yazık ki, bunun sorumluluğunu sen üstleneceksin. Bir rapor yazacağım, ve senin bir süre ortalarda görünmemen en iyisi olur. Kraliyet Donanması'ndaki hizmetin sona erdi.";
			link.l1 = "Hmm ... Üzgünüm, Mösyö. Görünen o ki, bakan öfkesini yatıştırana kadar bir iki ay ortadan kaybolmam gerçekten daha iyi olacak. Hoşça kalın ve tekrar söylüyorum, sizi hayal kırıklığına uğrattığım için çok üzgünüm.";
			link.l1.go = "patria_26_2";
		break;
		
		case "patria_26_2":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Patria = "fail";
			AddQuestRecord("Patria", "19");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			RemoveItems(pchar, "patent_fra", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterNationReputation(pchar, FRANCE, -5);
			pchar.quest.Patria_PortPaxOver.over = "yes"; // снять таймер
		break;
		
		case "patria_26":
			dialog.text = "Excellent! While we have captains in our navy like you, we need not fear the trickery of the Castilians. I will send a courier to Port-au-Prince tomorrow with a dispatch and a letter from France, and at the same time I will drop a hint in a personal letter to Monsieur Jeremy Deschamps du Mussaca that it would be fitting to thank you for your service, so I can assure you, Charles, that you will receive a well-deserved reward.\nAnd now, let's move on to your next assignment. Yes, my friend, I have a new task for you; however, this time it is not a military one, but rather a very delicate matter, and I would like you to handle it.";
			link.l1 = "Sizi dinliyorum, Şövalye.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "Sanırım Saint Martin hakkında Monsieur Forget ile yaptığım konuşmayı hatırlıyorsun? Barona koloninin denetlendiğini garanti etmemiz gerekiyor ve bu yüzden Curaçao'ya, Willemstad'a, Şirketin direktörü Peter Stuyvesant'a gideceksin. Şu anda orada ve üç hafta daha orada olacak. Ayrıca, Şirketin mallarını taşıyan fluyt'u Curaçao'ya kadar eşlik etmen ve Bay Stuyvesant'a benden bir mektup vermen gerekecek.";
			link.l1 = "Bunlar   tüm   görevler   mi?";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			dialog.text = "Evet, kaptan. Mynheer Stuyvesant'ın cevabını bana bildir. Bay Forget, Martinique ve Guadeloupe gezisinden dönmeden hemen önce varmış olacağız ve sonunda uzun zamandır görmek istediği Saint Martin'i ziyaret edebilecek.";
			link.l1 = "Pekâlâ. Gidebilir miyim?";
			link.l1.go = "patria_29";
		break;
		
		case "patria_29":
			dialog.text = " Gidebilirsin, Charles. Ama fazla oyalanma, baron beklemeyi sevmez. Ve Peter Stuyvesant'ı ziyaret ederken mutlaka üniformanı giy! Her şey resmî görünmeli, ne demek istediğimi anlıyorsun.";
			link.l1 = "Elbette, Şövalye. Hoşça kalın!";
			link.l1.go = "patria_30";
		break;
		
		case "patria_30":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "20");
			pchar.questTemp.Patria = "epizode_4";
			Patria_CureerBegin();
			pchar.quest.Patria_PortPaxOver.over = "yes"; // снять таймер
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_1");
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterComplexReputation(pchar, "nobility", 5); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
		case "patria_31":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Teşekkür ederim, kaptan, verin bana... (okuyor)... Pekâlâ, harika! Peter Stuyvesant, Baron Forget'nin denetim için Saint Martin'i ziyaret edebileceğini ve Philipsburg valisinin bilgilendirilip iş birliği yapacağını söylüyor. Sanırım ziyaretten sonra baron doğru kararı verecek - adanın Hollandalılara kiralanmasına izin verecek.\nVe şimdi, kaptan, en iç ısıtan haber! Size birkaç şey söylemem gerekiyor. Birincisi: tüm askeri başarılarınızı göz önünde bulundurarak, 'Komodor' rütbesine terfi ettiniz. Tebriklerimi kabul edin, Mösyö!";
			link.l1 = "Fransa'ya hizmet ediyorum!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			dialog.text = "Ve ikincisi: Port-au-Prince valisi, senin için ticaret gemisiyle dolu bir mal gönderdi: 500 büyük çuval kahve ve 500 çuval kakao. Bunların hepsi, Hispaniola'daki İspanyol baskınlarından koruduğun plantasyonların hasadı. Ayrıca, sana özel olarak çok değerli bir yük de gönderildi - 50 birim lignum vitae. Ne olduğunu sana açıklamama gerek yok sanırım. Malların Capsterville'deki dükkanda depoda, istediğin zaman gidip tüccardan alabilirsin.";
			link.l1 = "Teşekkür ederim, Şövalye! Harika bir haber bu!";
			link.l1.go = "patria_33";
		break;
		
		case "patria_33":
			dialog.text = "Ve şimdi, sıradaki görevinize gelince: Baron Forget her an Saint-Christopher'a dönebilir. Onu Saint Martin'e kadar eşlik edecek ve iyi korunduğundan emin olacaksınız. Ayrıca, tabiri caizse, Philipsburg'da olup bitenleri yakından gözlemleyecek ve bana rapor edeceksiniz. Baron gelir gelmez şehirden ayrılmayın kaptan, adamım sizi bulacak ve haber verecek.";
			link.l1 = "Her şey açık. Gidebilir miyim?";
			link.l1.go = "patria_34";
		break;
		
		case "patria_34":
			dialog.text = "İzinlisin. Karada geçireceğin birkaç gün dinlenmek sana iyi gelecek ve faydalı olacaktır.";
			link.l1 = "...";
			link.l1.go = "patria_35";
		break;
		
		case "patria_35":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "25");
			pchar.questTemp.Patria = "epizode_5";
			pchar.quest.Patria_CureerBackOver.over = "yes"; // снять таймер
			Items[sti(pchar.EquipedPatentId)].TitulCur = 4; 
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
			pchar.quest.Patria_SanMartin_wait.win_condition.l1 = "Timer";
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.hour  = 8+rand(2);
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l2 = "Location_Type";
			pchar.quest.Patria_SanMartin_wait.win_condition.l2.location_type = "town";
			pchar.quest.Patria_SanMartin_wait.function = "Patria_SanMartinBaron";
			pchar.questTemp.Patria.Goods = "true"; // товары-призы
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_36":
			DialogExit(); // переключение на инспектора
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Noel"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_37";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "patria_37":
			dialog.text = "";
			link.l1 = "Evet, Şövalye, geri döndüm! Saint Martin yakınlarındaki Hollandalı dostlarınız bizi kale toplarıyla karşıladı ve üç gemilik bir filoyla saldırdılar. Sadece Charles de Maure ve mürettebatının ustalığı sayesinde kaçmayı başardık! Görünüşe bakılırsa Bay Peter Stuyvesant, Fransız kralının elçilerini Philipsburg'da görmek istemiyor. Siz ne düşünüyorsunuz, Şövalye?";
			link.l1.go = "patria_38";
		break;
		
		case "patria_38":
			dialog.text = "Ne?! Burada Stuyvesant’ın kendi imzasıyla yazılmış bir mektup var, içinde garanti veriyor...";
			link.l1 = "Fakat Philipsburg kalesinin komutanı belli ki Stuyvesant'tan farklı bir mektup almış, ona istediği gibi ateş açmasını ve bir filoyla bize pusu kurmasını söylemiş! Bu bir tesadüf müydü, Şövalye?! Hayır! Belli ki orada bizi bekliyorlardı! Top gülleleri ve saçmalarla!";
			link.l1.go = "patria_39";
		break;
		
		case "patria_39":
			dialog.text = "Baron, size yalvarırım... Bu işi ben halledeceğim. Sevgili kaptanımız Charles de Maure'u hemen tekrar Curaçao'ya, Stuyvesant ile görüşmeye göndereceğiz. Kaptan, hassas meseleleri çözme konusunda uzun bir geçmişe sahip... Şimdi ise hizmetkârlara size bir banyo ve güzel bir öğle yemeği hazırlamalarını söyleyeceğim.";
			link.l1 = "...";
			link.l1.go = "patria_40";
		break;
		
		case "patria_40":
			DialogExit();
			LAi_SetActorType(pchar); // 14-add
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_41";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "patria_41":
			dialog.text = "Charles, dostum, Willemstad'a aceleyle gitmelisin. Belki Stuyvesant hâlâ oradadır. Değilse, nerede olduğunu öğren ve onu bul. Toplantıda ona olayı anlat ve açıklama iste. Tecrüben ve otoriten benim için çok önemli, bu görüşmeleri sana emanet ediyorum. Sonra, tek bir dakika bile kaybetmeden geri dön ve toplantının sonucunu bana bildir.";
			link.l1 = "Görev açık, Şövalye. Gemiyi hazırlayıp hemen yola çıkacağım.";
			link.l1.go = "patria_42";
		break;
		
		case "patria_42":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "29");
			pchar.questTemp.Patria = "epizode_6";
			Patria_DiplomatBegin();
			ChangeCharacterComplexReputation(pchar, "nobility", 3); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "patria_43":
			dialog.text = "Buna inanamıyorum...";
			link.l1 = "Üstelik, dönüş yolunda bir Hollanda donanma filosu tarafından saldırıya uğradım. Lütfen bana açıklar mısınız, Şövalye, burada neler oluyor?";
			link.l1.go = "patria_44";
		break;
		
		case "patria_44":
			dialog.text = "Arkadaşım, ne kadar sezgili olduğunu biliyorum, bu yüzden senden hiçbir şeyi saklamayacağım. Tek isteğim, burada duydukların bu odadan dışarı çıkmasın. Söz veriyor musun?";
			link.l1 = "Elbette, Şövalye.";
			link.l1.go = "patria_45";
		break;
		
		case "patria_45":
			dialog.text = "Pekala. Eminim Fransız donanmasında seni parlak bir kariyer bekliyor. Tabii ki benim yardımla, amiral yardımcılığına kadar yükselebilirsin! Neyse, konumuza dönelim... Şimdi ise Hollandalılar ve Saint Martin meselesine gelelim.\nSen Saint Martin'e gelmeden çok önce, orada büyük tuz yatakları keşfedilmişti. Başta kimse önemsemedi, ama sonra Küba ve Hispaniola'daki İspanyollar büyük ilgi gösterdiler – boğa karkaslarını tuzlamak için. Elbette senin de anlayacağın gibi, İspanya ile doğrudan ticaret yapamayız, bu yüzden...";
			link.l1 = "...Hollanda Batı Hindistan Şirketi şeklinde bir 'arabulucu' yaratmışsınız...";
			link.l1.go = "patria_46";
		break;
		
		case "patria_46":
			dialog.text = "Kesinlikle! Hızlı ve doğru düşünüyorsun, Charles! Şimdi ise, Paris'ten denetim geleceğini öğrenen Stuyvesant, tuz işini tamamen kendi eline almaya cesaret etti, çünkü İspanyollarla yaptığımız anlaşmayı herkese anlatmaya hevesli olmadığımızı düşünüyor. Ama işte burada yanıldı. Hiç kimse Fransız Genel Valisi'nin elinden cezasız bir şey alamaz! Bunu ona göstereceğiz.";
			link.l1 = "Anladığım kadarıyla, Baron Forget bundan haberdar olmamalı...";
			link.l1.go = "patria_47";
		break;
		
		case "patria_47":
			dialog.text = "Dostum, kesinlikle haklısın, baronun ayrıntıları bilmesine gerek yok. Zaten fazlasıyla şey yaşandı: Fransız kralının temsilcisine suikast girişimi, diplomatik misyonun gemilerine — yani sana — saldırı ve en önemlisi: Saint Martin adasının fiilen ilhakı! Bunlar Hollandalılara karşı askeri harekatı haklı çıkarmak için fazlasıyla yeterli.";
			link.l1 = "Savaş mı?!";
			link.l1.go = "patria_48";
		break;
		
		case "patria_48":
			dialog.text = "Kesinlikle! Dostum, senin için amiral yardımcılığı makamı o kadar da uzak değil, anlıyor musun? Düşünsene, Louvre'daki görüşmelerde amiral üniformasıyla bulunuyorsun ve bizzat XIV. Louis böyle onurlu bir misafiri kabul ediyor... Hollandalılara yerlerini göstermeliyiz! Stuyvesant yaptıklarına pişman olacak. Katılıyor musun?";
			link.l1 = "Katılıyorum, Şövalye. Hollandalılar bu alçakça ve iğrenç davranışlarının hesabını vermeli.";
			link.l1.go = "patria_49";
		break;
		
		case "patria_49":
			dialog.text = "Mükemmel. Kararımızı barona bildireceğim ve hemen Fransız kolonilerine ulaklar göndereceğim! Sen ise, dostum, uzun yolculuğunun ardından biraz dinlen, ve lütfen yarın sabah dokuzdan sonra beni ziyaret et. Senin için bir muharebe görevi hazırlayacağım.";
			link.l1 = "Pekâlâ, Mösyö. Müsaadenizle ayrılıyorum.";
			link.l1.go = "patria_50";
		break;
		
		case "patria_50":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "33");
			pchar.questTemp.Patria = "epizode_7";
			Patria_HunterBegin();
			pchar.quest.Patria_DiplomatTimeOver.over = "yes"; // снять таймер
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_51":
			dialog.text = "Ben buna savaş demezdim, aslında daha çok barışı zorlamak diyebilirim. Ve eğer Stuyvesant fikrini değiştirirse, bu bizi ancak daha mutlu eder. Bu yüzden şimdi ona göstermeliyiz ki, Saint Martin Adası'nı ele geçirmeye kalkışırsa, kazanacağından çok daha fazlasını kaybedecek. İşte burada devreye sen giriyorsun, Charles.";
			link.l1 = "Dinliyorum.";
			link.l1.go = "patria_52";
		break;
		
		case "patria_52":
			dialog.text = "Saint Martin, Avrupa'ya giden Hollanda gemileri için bir aktarma üssüdür. Şirketin gemileri düzenli olarak Philipsburg koyunda demirler. Şimdiye kadar, bu sular onlar için oldukça güvenliydi. Şimdiye kadar, Kaptan!.. Saint Martin kıyılarına yelken açacak, oraları devriye gezecek ve Şirketin ticaret gemilerini ele geçireceksiniz.\nDeğerli malları taşımak için Şirket, büyük ambarlara sahip, sağlam ve iyi silahlanmış Doğu Hindistan gemilerini kullanır. Hedefiniz bunlar olacak. Bu türden beş gemiyi yükleriyle birlikte ele geçirip ganimet olarak Casterville'e getirin. Bundan sonra Stuyvesant ile görüşmelere devam edeceğiz ve belki de kayıpları hesaba kattıktan sonra fikrini değiştirir.";
			link.l1 = "Görev açık. Gidebilir miyim?";
			link.l1.go = "patria_53";
		// belamour legendary edition -->
			link.l2 = "Monsieur, sormak zorundayım, bu operasyonun finansmanına katkıda bulunabilir misiniz? Bu, aylarca sürecek bir seyahat, sürekli onarımlar ve kayıplar demek...";
			link.l2.go = "patria_53a";
		break;
		
		case "patria_53a":
			AddMoneyToCharacter(pchar, 20000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			dialog.text = "Korkarım ki kaynaklarımız tükendi, Charles. Ecliaton'un bakımı ve savaşlar, Fransız kolonilerinin yarım yıllık bütçesine mal oldu bile. Şimdi, sana verebileceğim hepsi bu. Gelecekteki ödülleri düşün, Charles! Seni büyük bir gelecek bekliyor!";
			link.l1 = "Evet, efendim!";
			link.l1.go = "patria_54";
		break;
		// <-- legendary edtion
		case "patria_53":
			dialog.text = "Git, dostum, ve şans her adımında yanında olsun.";
			link.l1 = "...";
			link.l1.go = "patria_54";
		break;
		
		case "patria_54":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "34");
			pchar.questTemp.Patria = "epizode_7_continue";
			Patria_HunterContinue();
		break;
		
		case "patria_55":
			pchar.questTemp.Patria.Hunter = sti(pchar.questTemp.Patria.Hunter)+1;
			if (sti(pchar.questTemp.Patria.Hunter) > 4) // все собрал
			{
				dialog.text = " Görevi tamamladınız, kaptan. Mükemmel hizmetiniz için teşekkür ederim! Ganimetlerin satışından payınızı almaya hak kazandınız - iki yüz bin peso.";
				link.l1 = "Bunu duymak güzel, Mösyö!";
				link.l1.go = "patria_57";
			}
			else
			{
				dialog.text = "Yani, sadece "+FindRussianQtyString(5-sti(pchar.questTemp.Patria.Hunter))+" Limana getirmemiz gereken sadece Hollanda gemileri kaldı.";
				link.l1 = "Evet, Şövalye!";
				link.l1.go = "patria_56";
			}
		break;
		
		case "patria_56":
			DialogExit();
			AddQuestRecord("Patria", "35");
			AddQuestUserData("Patria", "sQty", 5-sti(pchar.questTemp.Patria.Hunter));
			DeleteAttribute(pchar, "questTemp.Patria.Hunter.GiveShip");
		break;
		
		// belamour legendary edition -->
		case "patria_57":
			AddMoneyToCharacter(pchar, 200000);
			dialog.text = "Ve bu hepsi değil. Geçen gün düşünüyordum da... Charles, Fransa için gerçekten çok şey yaptın. Açıkçası, hain Levasseur'un ortadan kaldırılması, Saint-Pierre'in İspanya'nın alçakça saldırısından savunulması, San Jose kolonisindeki kalenin başarıyla ele geçirilmesi ve İspanyolların cüretkâr oyunlarının cezası olarak tazminat alınması... Ve ardından, Avrupa'dan gelen Fransız tacı temsilcisini bizzat sen eşlik ederek getirdin ve hatta Philipsburg yakınlarındaki sularda Hollanda pususundan kaçarak onun hayatını kurtardın!";
			link.l1 = "Monsieur, gerçekten, beni mahcup ediyorsunuz... Ben sadece görevimi yapıyorum.";
			link.l1.go = "patria_57_1";
		break;
		
		case "patria_57_1":
			PlaySound("interface\important_item.wav");
			dialog.text = "Her zamanki gibi mütevazısın, dostum. Ve şimdi, Hollanda'yı barışa zorlamak gibi son görevi de yerine getirirken beni yine yanıltmadın. Abartısız söylüyorum, sen ulusun gerçek kahramanısın! Fransız kolonilerinin genel valisi olarak, yanımda Fransa'nın en yüksek nişanından birkaç tane bulundururum ve... Ama, bu arada, senden şu belgeyi okumanı rica ediyorum.";
			link.l1 = "Fransa'ya gösterdiğiniz üstün hizmetler için... Majesteleri Fransa Kralı adına... Fransa hizmetindeki bir deniz subayına, Kaptan Charles de Maure'a, Henri de Montpe'nin oğluna... Şövalye, şaka mı yapıyorsunuz?";
			link.l1.go = "patria_57_2";
		break;
		
		case "patria_57_2":
			dialog.text = "Hiç de değil, dostum. Sana hak ettiğin ödülü vermek benim için bir onurdur: Fransa'nın en yüksek nişanı - Aziz Louis Nişanı! Ülkemizin her vatandaşı kahramanını tanımalı! Saint-Pierre sana minnettar! Bu Nişanı hak ettin, Charles.";
			link.l1 = "Gerçekten, ne diyeceğimi bilemiyorum... Teşekkür ederim, Genel Vali! Fransa'ya gururla hizmet etmeye ve düşman karşısında asla geri çekilmemeye yemin ederim!";
			link.l1.go = "patria_57_3";
		break;
		
		case "patria_57_3":
			GiveItem2Character(pchar, "talisman9");
			Log_Info("You've received the Order of Saint Louis! You are the hero of the nation!");
			PlaySound("interface\important_item.wav");
			DoQuestCheckDelay("sea_victory", 0.5);
			dialog.text = "Gerçek bir subayın sözleri! Seninle gerçekten gurur duyuyorum, Charles. Şimdi biraz dinlen. Bunu hak ettin. Bu arada, Stuyvesant ile görüşmelere ben bakacağım – belki de bizimle anlaşmazlık içinde olmanın, dostumuz olmaktan çok daha az kârlı olduğunu artık anlamıştır. Şehirden ayrılma, iki gün içinde sana ihtiyacım olacak.";
			link.l1 = "Pekala, Mösyö. Daha fazla talimat bekleyeceğim.";
			link.l1.go = "patria_58";
		break;
		// <-- legendary edtion
		case "patria_58":
			DialogExit();
			AddQuestRecord("Patria", "36");
			pchar.questTemp.Patria = "epizode_7_end";
			pchar.quest.Patria_siege_begin.win_condition.l1 = "Timer";
			pchar.quest.Patria_siege_begin.win_condition.l1.date.hour  = 9.00;
			pchar.quest.Patria_siege_begin.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l2 = "location";
			pchar.quest.Patria_siege_begin.win_condition.l2.location = "Charles_town";
			pchar.quest.Patria_siege_begin.function = "Patria_SiegeBegin";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			ChangeCharacterComplexReputation(pchar, "nobility", 5); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
		case "patria_59":
			dialog.text = "Evet. Görünüşe göre Stuyvesant, İspanya ile ittifak kurarak askeri karşılık vermeye başladı. Ortak bir Hollanda-İspanyol filosu Saint-Christopher'ı kuşatmış durumda. Gözetleme kaleleri bana her saat onların her hareketini bildiriyor.";
			link.l1 = "Bir kuşatma mı?";
			link.l1.go = "patria_60";
		break;
		
		case "patria_60":
			dialog.text = "Elbette. Doğrudan saldırıya geçmediler, bu da aslında iyi bir şey. Düşman tüm adayı ablukaya almadan önce hızlı davranmamız lazım, kaptan.";
			link.l1 = "Ne yapmamız gerekiyor?";
			link.l1.go = "patria_61";
		break;
		
		case "patria_61":
			dialog.text = "Antigua'daki Saint-John's'ta, Albay Doily komutasındaki İngiliz Donanması filosu konuşlanmış durumda. Şu anda Sir Jonathan Fox'u ziyaret ediyor. Düşman gemilerinin arasından sıyrılıp Antigua'ya ulaşmalısın. Orada Albay ile buluşacak, ona mektubumu verecek ve yardım isteyeceksin.";
			link.l1 = "Sence Albay bize yardım etmeyi kabul edecek mi?";
			link.l1.go = "patria_62";
		break;
		
		case "patria_62":
			dialog.text = "I hope so. The letter should convince him that the reward for his help will be quite sizeable... Also, we need to send a letter to the captain of the 'Eclatant', currently near the shores of Guadeloupe; he must hurry to Saint-Christopher. The firepower of the 'Eclatant' will help us considerably in battle. As you can't be in two places at once, our courier lugger will join your squadron - you must get it through the circle of enemies undamaged, and it will depart for Guadeloupe before the 'Eclatant' heads south...";
			link.l1 = "Anladım. Kuşatmadan sağ çık, kurye teknesine eşlik et ve mektubunla birlikte Saint-Jones'a, Albay Doily'nin yanına acele et.";
			link.l1.go = "patria_63";
		break;
		
		case "patria_63":
			dialog.text = "Kesinlikle. Filonuza başka bir gemi daha katmaya hazır mısınız?";
			if (GetCompanionQuantity(pchar) > 4)
			{
				link.l1 = "Bir gemiden kurtulup sana geri döneceğim.";
				link.l1.go = "patria_63_1";
			}
			else
			{
				link.l1 = "Evet.";
				link.l1.go = "patria_64";
			}
		break;
		
		case "patria_63_1":
			DialogExit();
			pchar.questTemp.Patria = "epizode_8_wait";
		break;
		
		case "patria_64":
			dialog.text = "Mükemmel. Mektubu al, şalopa hazır ve emrini bekliyor.";
			link.l1 = "Hiç vakit kaybetmeyelim, Şövalye!";
			link.l1.go = "patria_65";
		break;
		
		case "patria_65":
			DialogExit();
			AddQuestRecord("Patria", "38");
			pchar.questTemp.Patria = "epizode_8_continue";
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_3");
			Patria_SiegeCreateSquadron();
		break;
		
		case "patria_66":
			dialog.text = "Evet, evet, dostum, senin alçakgönüllülüğünü çok iyi biliyorum. Gerçek bir subaysın! Ve ödülünü de alacaksın, buna emin olabilirsin! Böyle zorlu bir savaştan sonra biraz dinlenmeye ihtiyacın olacağını tahmin ediyorum. Tam bir haftan var. Yedi gün sonra konuşmak için odama gel – şehir kahramanına layık bir ödül hazırlayacak.";
			link.l1 = "Evet, Mösyö. Gidebilir miyim?";
			link.l1.go = "patria_67";
		break;
		
		case "patria_67":
			dialog.text = "Git ve güzelce dinlen. Sonra ciddi meselelerle ilgilenmemiz gerekecek - gördüğün gibi, şu anda Hollandalılarla barış imkânsız. Şimdilik, albayla ben bazı önemli konuları konuşacağız.";
			link.l1 = "O zaman bir hafta sonra görüşürüz, Şövalye.";
			link.l1.go = "patria_68";
		break;
		
		case "patria_68":
			DialogExit();
			AddQuestRecord("Patria", "45");
			pchar.questTemp.Patria = "epizode_8_end";
			Patria_SiegeEnd();
			ChangeCharacterNationReputation(pchar, FRANCE, 20);
			ChangeCharacterComplexReputation(pchar, "nobility", 10); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 10);
		break;
		
		case "patria_69":
			pchar.quest.Patria_BastionTimeOver.over = "yes"; //снять таймер
			dialog.text = "We've had a discussion with Colonel Doily and he has agreed to help me. England will support us in the war against the Dutch. You and I must strike back and restore justice – the isle of Saint Martin must return to France. I assign this task to the best navy captain – you, Charles de Maure! The enemy has not yet recovered from their squadron's defeat; we will attack Philipsburg and take it.\nThe battle will not be easy. First, we must destroy the fort, then break through the garrison's defences... (whispering) You will also need to make a forced march through the jungle to the salt deposit I told you about, and kill the enemies encamped there...";
			link.l1 = "Görev oldukça zor, Şövalye...";
			link.l1.go = "patria_70";
		break;
		
		case "patria_70":
			dialog.text = "Seni çok iyi anlıyorum, dostum. Filon takviye edilecek. Basse-Terre ve Saint-Pierre valileri şimdiye kadar birer gemi hazırlamış olmalı—birer fırkateyn. Bu fırkateynleri komutanlığına almak için sadece Guadeloupe ve Martinique'e uğraman yeterli olacak. Tabii, eğer bu gemileri kendin istiyorsan—hangi gemileri seçeceğine karışmayacağım. Ayrıca amiral gemin için erzak ve teçhizat alman amacıyla sana 20.000 peso yardım veriyorum. Al, buyur...";
			link.l1 = "Pekâlâ, Mösyö.";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail")) link.l1.go = "patria_71";
			else link.l1.go = "patria_71_1";
		break;
		
		case "patria_71_1":
			dialog.text = "Ayrıca, her zamanki gibi, 'Eclatant' gemisi de sizin emrinizde. Onarıldı ve donatıldı, şu anda liman ağzında bekliyor. Kaptanla konuştuktan sonra istediğiniz an gemiyi alabilirsiniz.";
			link.l1 = "Mükemmel!";
			link.l1.go = "patria_71";
			pchar.questTemp.Patria.Ecliaton_Bastion = "true";
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_7";
			sld.DeckDialogNode = "ecliaton_cap_7";
		break;
		
		case "patria_71":
			AddMoneyToCharacter(pchar, 20000);
			dialog.text = "Zaman kaybedemeyiz, kaptan. Casuslarım, Hollandalıların Saint Martin için tehlikeyi anladıklarını ve savunmalarını güçlendirmeye niyetlendiklerini bildirdi. Ama hâlâ iki ayın var. Görevi zamanında bitirmelisin!";
			link.l1 = "Yapacağım... (fısıldayarak) Saint Martin'deki tuz yatağı nerede? Adanın hiçbir haritasında işaretli değil...";
			link.l1.go = "patria_72";
		break;
		
		case "patria_72":
			dialog.text = "(fısıldayarak) Şehre saldırdığında, Philipsburg'un genel valisi Mynheer Martin Thomas'ı sorgula, sana söyleyecektir. O Hollandalı tam bir korkaktır, sana karşı koymayacaktır, buna kefilim.";
			link.l1 = "Anladım. O halde izninizle ayrılabilir miyim?";
			link.l1.go = "patria_73";
		break;
		
		case "patria_73":
			dialog.text = "Bir dakika, Charles. Aziz Christopher'ı kurtardığın için ödülünü henüz almadın. Şehir halkı adına şu altın sandıklarını ve parayla ölçülemeyecek kadar derin minnettarlığımızı kabul et!";
			link.l1 = "Teşekkür ederim, Mösyö!";
			link.l1.go = "patria_74";
		break;
		
		case "patria_74":
			TakeNItems(pchar, "chest", 10);
			Log_Info("You've received 10 chests of doublons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Artık gidebilirsin. İyi şanslar, kaptan! Hepimiz zaferini bekliyoruz!";
			link.l1 = "Hoşça kal, Şövalye.";
			link.l1.go = "patria_75";
		break;
		
		case "patria_75":
			DialogExit();
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Bastion")) sTemp = "The warship 'Eclatant' will also be under my command.";
			AddQuestRecord("Patria", "48");
			AddQuestUserData("Patria", "sText", sTemp);
			pchar.questTemp.Patria = "epizode_9_continue";
			SetFunctionTimerCondition("Patria_BastionSturmTimeOver", 0, 0, 62, false);
			// вернуть Синт-Маартен в норму
			int n = FindIsland("SentMartin");
			Islands[n].reload.l1.radius = 600.0;
			LocatorReloadEnterDisable("Marigo_ExitTown", "reload3", false); // открыть городские ворота
			sld = CharacterFromID("Marigo Fort Commander");
			LAi_SetImmortal(sld, false);
			Character_SetAbordageEnable(sld, true);
			// атрибут квестовой высадки десанта
			pchar.TempPerks.QuestTroopers = true;
		break;
		
		case "patria_76":
			dialog.text = "Kim derdi ki, sadece bir yıl önce, senin amiral yardımcılığına terfi edeceğini, dostum? Bu haber Fransa'ya ulaştığında babanın ne kadar gururlanacağını ancak tahmin edebilirim!";
			link.l1 = "Babam buna çok sevinecek.";
			link.l1.go = "patria_77";
		break;
		
		case "patria_77":
			dialog.text = "Filo içindeki yerini hak ettin! Saint Martin tekrar Fransa'ya döndü, Stuyvesant ağır bir ders aldı. Bu büyük bir zaferdi! Ama duramayız, Hollandalılara bir an bile rahat vermemeliyiz. İhanetlerinin bedelini ödeyecekler! Albay Doily şu anda Port Royal'de, deniz filosunu hazırlıyor: Düşmanımızın belini Curacao'ya saldırarak kıracağız. Ama bu sonra olacak, şimdilik iki işi bir arada halletmemiz gerekiyor, Charles.\nŞirket bütün o muazzam servetini ticaretle kazanmadı. Hollandalıların bölgedeki ana gelir kaynağı, plantasyonlarındaki köle emeği. Haberin yoksa, Charles: Hollanda, en büyük köle sahibi ve köle ticareti yapan ülke. Batı Afrika'dan Curacao'ya düzenli olarak 'kara fildişi' taşıyan Doğu Hindistan gemileri geliyor. Ve ben de bu konuda bir şeyler biliyorum, ne yazık ki Stuyvesant'ın aleyhine.\nŞu anda iki Hollanda Doğu Hindistan gemisi, Gine'den Karayipler'e doğru yolda. Ambarları siyah esirlerle dolu. Yaklaşık on gün içinde, konvoy Trinidad adasının çevresinden Curacao'ya doğru geçecek. Görevin, konvoyu bulup bu iki Doğu Hindistan gemisini ve yüklerini ele geçirmek. Onları koruyan gemileri yok etmeli ve köleleri müttefikimiz Albay Doily'ye, Jamaika'ya götürmelisin. Bu çok önemli, Charles, böylece onun güvenini kazanacağız... Umarım anlıyorsun.\nSana dinlenmek için vakit bırakmadığım için üzgünüm, ama bu görev hem önemli hem de hassas, ve bunu yalnızca sana emanet edebilirim.";
			link.l1 = "Hizmet şeker değil, Şövalye. Bunu herkesten iyi bilirim. Gemimi hazırlayıp en kısa sürede yola çıkacağım.";
			link.l1.go = "patria_78";
		break;
		
		case "patria_78":
			dialog.text = "Sana iyi rüzgarlar ve güvenli bir yolculuk dilerim, amiral yardımcısı. Saint-Christopher'a döndüğünde, ortak dostumuz Monsieur Noel Forget, Philipsburg'daki denetlemesini tamamlamış olacak ve Hollandalılardan alınan ganimetlerin bir kısmının bizzat sana verilmesini sağlayacağım.";
			link.l1 = "Çok minnettar olurum, Şövalye. Gidebilir miyim?";
			link.l1.go = "patria_79";
		break;
		
		case "patria_79":
			dialog.text = "Git. Sana bol şanslar, dostum!";
			link.l1 = "...";
			link.l1.go = "patria_80";
		break;
		
		case "patria_80":
			DialogExit();
			Items[sti(pchar.EquipedPatentId)].TitulCur = 5; 
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
			pchar.questTemp.Patria = "epizode_10_start";
			AddQuestRecord("Patria", "52");
			Patria_SlaveShipsStart();
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			ChangeCharacterComplexReputation(pchar, "nobility", 10); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 10);
		break;
		
		case "patria_81":
			dialog.text = "Mükemmel! Sen 'imkansız' kelimesini bilmiyorsun, Charles. Eskiden kardeşinin Karayipler'deki en iyi deniz subayı olduğunu düşünürdüm, ama kaba bir karşılaştırma olacaksa, senden öğreneceği çok şey var. Sanırım Willemstad'a saldırıya katılmak için sevgili albayımıza kimin gideceğini zaten biliyorsun.";
			link.l1 = "Kesinlikle hayır, Mösyö! Bunu nasıl bilebilirim ki!";
			link.l1.go = "patria_82";
		break;
		
		case "patria_82":
			dialog.text = "Ah, o meşhur mizah anlayışın, sevgili dostum! Ha-ha! Tabii ki sen olacaksın, amiral yardımcısı. Herkesin en layığı sensin. Hazır mısın?";
			link.l1 = "Elbette, Şövalye. Sadece biraz onarıma ve ekipmana ihtiyacım var – sonra hazırım.";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail")) link.l1.go = "patria_83";
			else link.l1.go = "patria_83_1";
		break;
		
		case "patria_83_1":
			dialog.text = " 'Eclatant'ı komutanız altına almayı unutmayın. Gemi onarıldı ve donatıldı, sizi limanda bekliyor. Marki Hubert Dassier ise şimdiden sabırsızlanıyor ve sizinle bir sonraki savaşa çıkmak için can atıyor.";
			link.l1 = "Harika. Uzun menzilli kalverin topları olan güçlü bir gemi, kaleyi bombalamak için tam da ihtiyacım olan şey.";
			link.l1.go = "patria_83";
			pchar.questTemp.Patria.Ecliaton_Curacao = "true";
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_11";
			sld.DeckDialogNode = "ecliaton_cap_11";
		break;
		
		case "patria_83":
			dialog.text = "Bir dakika, Charles. Dostumuz Baron Forget, sana Saint Martin'den haberler getirdi.";
			link.l1 = "...";
			link.l1.go = "patria_84";
		break;
		
		case "patria_84":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_25";
			sld.greeting = "noel_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			ChangeCharacterComplexReputation(pchar, "nobility", 2); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "fame", 2);
		break;
		
		case "patria_85":
			dialog.text = "Paris'ten senin için haberlerim var. Kral, seni amiral yardımcılığına atayan kararı imzaladı. İlgili belgeleri alacaksın. O halde, seni tebrik ediyorum!";
			link.l1 = "Teşekkür ederim, Mösyö! Fransa'ya ve Kral'a hizmet etmekten mutluluk duyuyorum!";
			link.l1.go = "patria_coat";
		break;
		
		case "patria_coat":
			dialog.text = "Ve ben de, her zamanki gibi, bu sözleri sizden duymaktan büyük memnuniyet duyuyorum. Charles, belki benimle biraz şarap içmek istersin? Paris'ten özel olarak getirildi, bu kalitede bir şarabı buralarda kolay kolay bulamazsın!";
			link.l1 = "Teşekkür ederim, şövalye, ama sanırım bu kez pas geçeceğim. Birazdan gemiye dönmem gerekecek, Fransa'nın Viseamiralinin güvertede sarhoş halde durması pek uygun olmaz.";
			link.l1.go = "patria_coat_01";
			link.l2 = "Pekâlâ, neden olmasın? Her gün bizzat genel valinin kendisiyle bir içki içme fırsatı bulamıyorum!";
			link.l2.go = "patria_coat_02";
		break;
		
		case "patria_coat_01":
			dialog.text = "Pekâlâ, biraz dinlenebilirsin, hemen gemiye dönmene gerek yok. Ama bu senin seçimin ve buna saygı duyuyorum. O halde, doğrudan konuya geçelim.";
			link.l1 = "Dikkatle dinliyorum.";
			link.l1.go = "patria_coat_13";
		break;
		
		case "patria_coat_02":
			dialog.text = "Ve her genel vali, sadece en iyi deniz subayı değil, aynı zamanda dostu olan bir başamirale sahip olacak kadar şanslı değildir; onunla aynı masada oturup uzak bir memleketten getirilen şarabı paylaşmak herkese nasip olmaz!";
			link.l1 = "Fransa için!";
			link.l1.go = "patria_coat_03";
			link.l2 = "Sağlığınıza, şövalye!";
			link.l2.go = "patria_coat_04";
		break;
		
		case "patria_coat_03":
			dialog.text = "Ve kral için!";
			link.l1 = "...";
			link.l1.go = "patria_coat_05";
		break;
		
		case "patria_coat_04":
			dialog.text = "Ve seninkine de, Charles!";
			link.l1 = "...";
			link.l1.go = "patria_coat_05";
		break;
		
		case "patria_coat_05":
			LAi_Fade("", "");
			if(LAi_GetCharacterHP(pchar) == LAi_GetCharacterMaxHP(pchar))
			pchar.chr_ai.hp = stf(pchar.chr_ai.hp) - 1.0;
			GiveItem2Character(pchar, "potionwine");
			DoCharacterUsedItem(pchar, "potionwine");
			npchar.dialog.currentnode = "patria_coat_06";
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorSetHuberMode(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 1.2);
		break;
		
		case "patria_coat_06":
			dialog.text = "Hm, enfes bir şarap! Katılmıyor musun?";
			link.l1 = "Evet, haklıydın. Bana memleketim Gaskonya'da yaptıkları şarabı hatırlatıyor...";
			link.l1.go = "patria_coat_07";
		break;
		
		case "patria_coat_07":
			dialog.text = "Biraz yanıldın dostum - Bordeaux. Yine de eminim ki Gaskonya şarabı da en az onun kadar iyidir!";
			link.l1 = "Sanırım artık tadını unutmaya başlıyorum... Fransa'dan ayrılalı ne kadar oldu? Bir yıl mı? İki?";
			link.l1.go = "patria_coat_08";
		break;
		
		case "patria_coat_08":
			dialog.text = "Ah, Charles, sanki daha dün tanışmışız gibi... hem de pek hoş olmayan koşullarda. Bunu gündeme getirdiğim için kusura bakma, ama o zamanlar biri bana o hücrede karşımda duran adamın bir gün Fransız kolonilerinde sağ kolum olacağını söyleseydi, herhalde kahkahalarla gülerdim.";
			link.l1 = "Tanrı'nın yolları gizemlidir.";
			link.l1.go = "patria_coat_09";
		break;
		
		case "patria_coat_09":
			dialog.text = "Affedersiniz, az önce ne dediniz?";
			link.l1 = "Latince bu, şövalye. Tanrı'nın yolları gizemlidir. Hayatın ne getireceğini kimse bilemez.";
			link.l1.go = "patria_coat_10";
		break;
		
		case "patria_coat_10":
			dialog.text = "Seni her seferinde şaşırtmayı başarıyorsun, Charles. Şuna bak - Latince de konuşabildiğini bilmiyordum. Ama öte yandan, bir bakıma kaderimizi kendimiz şekillendiriyoruz, değil mi?";
			link.l1 = "Bence ikisi de doğru. Bizim için ne olacağını yalnızca Tanrı bilir. Ama O, azimlileri ödüllendirir.";
			link.l1.go = "patria_coat_11";
		break;
		
		case "patria_coat_11":
			dialog.text = "Kesinlikle katılıyorum. Mesela, sana deniz subayı yetkisini verdiğim ve o üniformayı teslim ettiğim günü hatırlıyorum. Ve şimdi, karşımda bir tümamiral duruyor, hem de öyle az buz değil!";
			link.l1 = "Zaman su gibi akıp geçiyor, şövalye.";
			link.l1.go = "patria_coat_12";
		break;
		
		case "patria_coat_12":
			dialog.text = "Indeed... And even on your uniform, I see the cuts left by sabers; some cuts have been stitched, and some are clearly fresh. This needs to be corrected.";
			link.l1 = "Aklınızda ne var, Genel Vali?";
			link.l1.go = "patria_coat_13";
		break;
		
		case "patria_coat_13":
			dialog.text = "Karayip takımadalarındaki Fransız filosunun yeni Başkan Amiral Yardımcısı olarak atanmanın yanı sıra, sana bir hediyem daha var.";
			link.l1 = "Beni utandırıyorsunuz, şövalye. Hangi hediye?";
			link.l1.go = "patria_coat_14";
		break;
		
		case "patria_coat_14":
			dialog.text = "Kişisel terzimle - Fransız kolonilerinin en iyisidir! - rütbene yakışır bir üniforma diktirmesi için anlaştım. Ödeme konusunda endişelenme, her şeyi ben hallettim.";
			link.l1 = "Gerçekten minnettarım! Terzini mutlaka ziyaret edeceğim. Onu nerede bulabilirim?";
			link.l1.go = "patria_coat_15";
		break;
		
		case "patria_coat_15":
			dialog.text = "Şu anda liman ofisinde olmalı - anakaradan yeni bir kurye gemisi geldi, yanında birkaç küçük paket getirmiş. Terzimiz burada bulması zor olan kumaşları hep sipariş eder.";
			link.l1 = "O halde liman ofisine gideceğim. Tekrar teşekkürler, monsieur!";
			link.l1.go = "patria_86";
		break;
		
		case "patria_86":
			dialog.text = "Ve şimdi, eminim ki iyi bir dinlenmeye ihtiyacın olacak. Sana bir ay veriyorum, bu zamanı akıllıca geçir. Ne iş, ne de endişe. Tüm işleri subaylarına bırak ve iyice dinlen. Konutumda odaları kullanabilirsin. Hizmetkarlar konaklamanı en rahat şekilde sağlayacaklar. Bir ay sonra tekrar görüşeceğiz – ve seninle konuşmam gereken hassas bir mesele olacak.";
			link.l1 = "Pekâlâ, Şövalye. Hoşça kal!";
			link.l1.go = "patria_87";
		break;
		
		case "patria_87":
			npchar.dialog.currentnode = "First time";
			LAi_Fade("","");
			LAi_SetHuberType(npchar);
			DialogExit();
			AddQuestRecord("Patria", "65"); // далее коллизия Пуанси-Инспектор-Шарль
			pchar.questTemp.Patria = "epizode_12_start";
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			SetFunctionLocationCondition("Patria_Tailor", "Charles_PortOffice", false)
			Patria_CondotierStart();
			ChangeCharacterComplexReputation(pchar, "nobility", 15); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 15);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
		break;
		
		case "patria_88":
			dialog.text = "Evet, Charles. Bunu kendi başıma halledebileceğimi sanmıştım ama... ne yazık ki yeteneklerinden bir kez daha faydalanmam gerekecek. Fakat önce sana bir şey vermeliyim: üç yüz bin peso ve beş sandık dublon. Bunlar, Stuyvesant'ın anlaşmamız gereği bana ödediği katkının büyük bir kısmı. Sanırım bunların hepsini hak ettin, çünkü işin çoğunu sen yaptın. Kabul et. Memnun musun, dostum?";
			link.l1 = "Para hiçbir zaman kimseye zarar vermez, Mösyö, bu dersi iyi öğrendim.";
			link.l1.go = "patria_89";
		break;
		
		case "patria_89":
			AddMoneyToCharacter(pchar, 300000); 
			TakeNItems(pchar, "chest", 5);
			dialog.text = "Ah, amiral yardımcısı, geçmişte olanlardan dolayı bana kırgın değilsinizdir umarım?.. Artık ulusunuzun bir kahramanısınız, biliyor muydunuz? Bu yeni konumda kendinizi nasıl hissediyorsunuz? Unutmayın: birçok değerli subay rütbelerde yıllarını harcadı, ama tecrübeli bir el olmadan... komutanlıkta kalıyorlar. Ama siz, dostum, imkansızı başarma konusunda eşsiz bir yeteneğe sahipsiniz! Ve yüksek mevkilerde bir dostunuz, aynı zamanda koruyucunuz var; bu yüzden gelecekte bir sorun yaşarsanız, size yardımcı olmak için orada olacağım.";
			link.l1 = "Bu güzel sözleriniz için teşekkür ederim, Ekselansları. Bu bölgede neredeyse her şeyi başardığımı hissediyorum. Elbette sizin yardımınızla. Artık kendi işlerimle huzur içinde ilgilenebilirim sanırım? Ailemi düşünmem gerek.";
			link.l1.go = "patria_90";
		break;
		
		case "patria_90":
			dialog.text = "Evlenmek mi istiyorsun, Charles? Ah-ha-ha! Paris'te güzel bir kadını göster - anında senin olur! Ama, ne yazık ki, bu biraz bekleyecek. Sana burada ihtiyacım var, dostum, en azından şimdilik.";
			link.l1 = "Görünüşe göre Fransa, Takımadalar'da her zamankinden daha güçlü. İngilizlerle ittifak, Şirketle ateşkes. Sorun çıkaracak... 'Levasseur'lar da kalmadı. Değil mi?";
			link.l1.go = "patria_91";
		break;
		
		case "patria_91":
			dialog.text = "Uluslar da tıpkı insanlar gibi, ne kadar çok şeye sahip olurlarsa olsunlar, hep daha fazlasını isterler... Ve gerçekten de yeni bir 'Levasseur'umuz var, Koramiral...";
			link.l1 = "Gerçekten mi? Kimmiş bu?";
			link.l1.go = "patria_92";
		break;
		
		case "patria_92":
			dialog.text = "Eski tanıdığımız Baron Noel Forget. Buraya neden geldiğini hatırlıyor musun?";
			link.l1 = "Hmm... Batı Hint Ticaret Şirketi'nden bahsettiniz. Paris, Hollandalılar gibi aynı örgütü kurmaya mı karar verdi?";
			link.l1.go = "patria_93";
		break;
		
		case "patria_93":
			dialog.text = "Kesinlikle. Tıpkı Hollanda Şirketi gibi. Ama sıfırdan bir şirket kurmak çok zor. Bak, Stuyvesant'ın farklı kıtalarla ticaret konusunda yıllarca deneyimi, gelişmiş bir ajan ağı ve güçlü bir ticaret filosu vardı. Fransa'nın böyle bir şeyi yok ve bilmeyebilirsin Charles, Kral şu anda ciddi bir para sıkıntısı çekiyor. Ticaretin buraya kaydırılmasıyla metropolün mali durumunu düzeltmeyi umuyorlar, ama karşılaşacağımız zorlukları anlamıyorlar.\nHem İngilizlerle hem de Hollandalılarla rekabet, İspanyolların toprak hırsları, eşi benzeri görülmemiş bir şekilde gelişen korsanlık... Her ticaret gemisinin yanında bir donanma gemisi olması şart, yoksa varacağı yere asla ulaşamayabilir. Ve bizde ne Hollanda Doğu Hindistan Şirketi gibi güçlü bir filo var, ne de İspanyolların büyük kalyonları.";
			link.l1 = "Ama bütün bunları barona anlattınız mı? Korsanlar hakkında da?";
			link.l1.go = "patria_94";
		break;
		
		case "patria_94":
			dialog.text = "Elbette yaptım. Ve Levasseur'u ortadan kaldırma görevinizden sonra Tortuga'dan korsanların sürgün edilmesiyle ilgili olarak da... Korsanlar bunu unutmadı ve bunu bize her zaman karşı kullanacaklar. Endişelerimi doğrulayan çeşitli insanlarla toplantılar düzenledim, ama ne yazık ki baron üzerinde hiçbir etkisi olmadı. Bakanlar tarafından buraya gönderildi ve onlara borçlu... Durum böyle işte.";
			link.l1 = "Hıh...";
			link.l1.go = "patria_95";
		break;
		
		case "patria_95":
			dialog.text = "Ve Archipelago'da Paris'ten doğrudan yönetilen bir ticaret şirketine ihtiyacımız olmadığını da saklamayalım... sen ve ben, amiral yardımcısı... burada böyle bir şeye gerek yok.";
			link.l1 = "Anladım.";
			link.l1.go = "patria_96";
		break;
		
		case "patria_96":
			dialog.text = "Görüyorsun ya dostum, sana karşı son derece dürüstüm... O yüzden bütün kalbimle Monsieur Forget'in bu ticaret şirketini kurmaktan vazgeçeceğini ummuştum, ama... öyle olmadı. Baron üzerinde tüm nüfuzumu harcadım ve şimdi oyuna senin girmen gerekiyor.";
			link.l1 = "Hmm... Levasseur'da olduğu gibi mi?";
			link.l1.go = "patria_97";
		break;
		
		case "patria_97":
			dialog.text = "Aman Tanrım, hayır, beni kim sanıyorsun Charles?! Baron etkili bir isim, Maliye Bakanı'nın dostu! Üstelik onu ortadan kaldırmak hiçbir işe yaramaz: Paris'ten hemen yeni bir siyasetçi gönderirler. Asıl yapmamız gereken, böyle bir şirket kurma fikrini kökünden yok etmek, anlıyor musun Charles? Böylece baron Fransa'ya döner ve bunun mali açıdan riskli, mantıksız olduğunu rapor eder...";
			link.l1 = "Bir fikriniz var mı, Mösyö?";
			link.l1.go = "patria_98";
		break;
		
		case "patria_98":
			dialog.text = "Ne yazık ki hayır, Charles. Her şeyi denedim. Onu gemi ve para yokluğuyla, Hollandalılarla, korsanlarla korkuttum... Hiçbir etkisi olmadı.";
			link.l1 = "Görünüşe bakılırsa, yalnızca sözlerle yetinemeyiz. Hm... Korsanlar, öyle mi?";
			link.l1.go = "patria_99";
		break;
		
		case "patria_99":
			dialog.text = "Bir fikrin olduğunu görüyorum, dostum? Hiç şüphem yoktu. Zekân gerçekten parlak. Şu baronu ikna et, ben de babanın evini Louvre’a yakışır hazinelerle dolduracak kadar para kazanmasını sağlayacağım. Sana söz veriyorum, Charles.";
			link.l1 = "Pekâlâ, Şövalye. Görev açık.";
			link.l1.go = "patria_100";
		break;
		
		case "patria_100":
			dialog.text = "Yemin ederim Charles, eğer başarırsan asla pişman olmayacaksın. Bundan emin olabilirsin. Sana hiç ihanet ettim mi, dostum?";
			link.l1 = "Kesinlikle hayır, Mösyö. Baronu nerede bulabilirim?";
			link.l1.go = "patria_101";
		break;
		
		case "patria_101":
			dialog.text = "Şu anda Port-au-Prince'de. Hispaniola'nın uçsuz bucaksız tarlalarını ve vadilerini çok güzel bulduğunu söyledi...";
			link.l1 = "Harika. Şimdi, müsaadenizle ayrılıyorum.";
			link.l1.go = "patria_102";
		break;
		
		case "patria_102":
			DialogExit();
			AddQuestRecord("Patria", "67");
			pchar.questTemp.Patria = "epizode_12_pirates";
			Patria_CondotierSail();
		break;
		
		case "patria_103":
			dialog.text = "Tam olarak öyle. Baron bana her şeyi anlattı. Bunca yaşadıklarından sonra... Yine de, olayları kimsenin yapamayacağı kadar açık anlatabiliyorsun, amiral yardımcısı! Bunu senden öğrenmeliyim!";
			link.l1 = "Sizden çok şey öğrendim, Şövalye.";
			link.l1.go = "patria_104";
		break;
		
		case "patria_104":
			dialog.text = "Arkadaşım, sana borçlandım. Emin ol, sevgili babanın hayatı boyunca ihtiyaç duyacağı her şey ona sağlanacak, aile yuvanız ise eyaletin en güzel evi olacak... ve Fransa'nın da en iyilerinden biri. Ayrıca sana 100.000 peso ödeyeceğim - umarım bu, korsanlara olan borcunu kapatmaya yeter...";
			link.l1 = "Bunu duymak ne güzel, Mösyö!";
			link.l1.go = "patria_105add";
		break;
		
		case "patria_105add":
			AddMoneyToCharacter(pchar, 100000); 
			dialog.text = "Sana özel bir hediye de hazırladım. Bu eşyanın değerini ve sadık hizmetlerin için duyduğum içten minnettarlığı takdir edeceğinden eminim! O halde, Amiral Yardımcısı Charles de Maure, sana Malta Şövalyeleri’ne ait şahsi tören kılıcımı takdim ediyorum! Bu değerli silahın üniformana mükemmel uyacağını düşünüyorum! Eğer Paris’e dönmeye karar verirsen, Baron Noel Forget seni Kral’a takdim etmeye söz verdi — ona tam teçhizatlı olarak gitmelisin: üniformanı giyip bu muhteşem kılıcı taşıyarak! Fransız donanmasında seni çok daha parlak kariyer fırsatları bekliyor!";
			link.l1 = "Bu kılıcın güzelliği eşsiz! Teşekkür ederim, Mösyö, gerçekten bu onuru hak etmiyorum...";
			link.l1.go = "patria_105";
		break;
		
		case "patria_105":
			ref itm = ItemsFromID("blade_36");
			itm.picIndex = 16;
			itm.picTexture = "ITEMS_17";
			itm.price = 10000;
			itm.Weight = 3.0;
			itm.lenght = 1.05;
			itm.curve = 1.0;
			itm.Balance = 1.9;
			GiveItem2Character(pchar, "blade_36");
			Log_Info("You've received the Maltese Sword");
			PlaySound("interface\important_item.wav");
			dialog.text = "Kesinlikle öyle! Ve burada bulunduğun sürece, seni büyük değişiklikler bekliyor. Hem de iyi değişiklikler. Amiral Yardımcısı Charles de Maure, seni Saint Martin Valisi olarak atıyorum!";
			link.l1 = "Hah! Doğru mu duydum seni?";
			link.l1.go = "patria_106";
		break;
		
		case "patria_106":
			ChangeCharacterComplexReputation(pchar, "nobility", 12); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 12);
			ChangeCharacterComplexReputation(pchar, "fame", 12);
			dialog.text = "Evet, dostum. Artık Saint Martin'in valisisin, ki orayı büyük bir özveriyle korudun.";
			link.l1 = "Şövalye, bu onuru kabul etmeme izin verin. Sadece bu yoksul adaya bağlı kalmak istemiyorum! Bir de şu iç meseleler... Benim kaderim bu değil!";
			link.l1.go = "patria_107";
		break;
		
		case "patria_107":
			dialog.text = "Reddini kabul etmiyorum. Dostum, korkma: hayatın eskisi gibi devam edecek. Sıkıcı işlerle mevcut vekil vali ilgilenecek. Sen fiilen vali olacaksın. Charles, neden özellikle SENİN Saint Martin'in başına atandığını anlamıyor musun? Şimdi tam zamanı, kimse soru sormayacak. Orada valilikte KENDİ adamlarımdan birine ihtiyacım var, ne demek istediğimi anlıyor musun?";
			link.l1 = "Tuz madeni mi?";
			link.l1.go = "patria_108";
		break;
		
		case "patria_108":
			dialog.text = "Elbette! Ve ikinci güzel haber: bundan böyle, her ayın 15'inde madenden ve Doily'nin ticaretinden payına düşen kazancı alacaksın. Pasif gelirinin aylık 100.000 peso olacağını bilmelisin.";
			link.l1 = "Hah! Bunu duymak güzel! Teşekkür ederim, Şövalye. Peki, orada oturup kalmak zorunda olmayacaksam, valiliği kabul ediyorum. Peki ya Fransa'ya yelken açmaya karar verirsem?";
			link.l1.go = "patria_109";
		break;
		
		case "patria_109":
			dialog.text = "Ne zaman karar verirsen — gidersin, ve ben de, çok hayal kırıklığına uğrasam da, yerine birini bulurum. Ama hepsi bu kadar değil. Burada babandan bir mektup var. Bir bak.";
			link.l1 = "Babamdan mı? Çok sevindim!.. Pekâlâ, Mösyö, anlaştık. Artık gidebilir miyim? Mektubu okumak istiyorum... Bana yeni bir görev yok, değil mi?";
			link.l1.go = "patria_110";
		break;
		
		case "patria_110":
			dialog.text = "Şimdi değil, Valim, ama bir iş bulursam sizi nasıl bulacağımı biliyorum. İyi şanslar, Charles!";
			link.l1 = "Ve size de, Şövalye!";
			if (pchar.questTemp.Patria == "epizode_12_baronwin") link.l1.go = "patria_119";
			else link.l1.go = "patria_111";
		break;
		
		case "patria_111":
			DialogExit();
			AddQuestRecord("Patria", "77");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			pchar.questTemp.Patria.Governor = "true"; // Шарль губернатор
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			sld = CharacterFromID(pchar.questTemp.Patria.SpanishID);
			SetCharacterRemovable(sld, true);
		break;
		
		case "patria_112":
			dialog.text = "Lanet olsun, ne felaket! Şimdi başımızda daha fazla sorun var. Bunun sorumlusu sen misin, Charles? Doğruyu söyle. Bu bir kaza mıydı?";
			link.l1 = "Bir şeyler ters gitti...";
			link.l1.go = "patria_113";
		break;
		
		case "patria_x112":
			dialog.text = "Lanet olsun, ne felaket! Şimdi başımıza daha çok iş çıktı. Baron ölmek için gerçekten berbat bir yer seçmiş! Emin misin, onun bu dünyadan ayrılmasına yardım etmedin?";
			link.l1 = "Ne diyorsunuz, Şövalye?! Tabii ki hayır!";
			link.l1.go = "patria_x113";
		break;
		
		case "patria_y112":
			dialog.text = "Lanet olsun, ne felaket! Şimdi başımızda daha fazla dert var. Emin misin, onun bu dünyadan ayrılmasına sen yardım etmedin?";
			link.l1 = "Ne diyorsunuz, Şövalye?! Tabii ki hayır!";
			link.l1.go = "patria_y113";
		break;
		
		case "patria_x113":
			dialog.text = "Pekala. O halde, dostum, belki de her şey mahvolmuş değil. Ateş ateştir, öyle değil mi? Ve bakanlıktan yeni bir müfettiş gelene kadar, buradaki karmaşayı toparlayıp misafirlerimizi silahlı bir şekilde bekleyeceğiz... Şimdi ise, Charles, tüm bağlantılarımızı kapatmamız gerekiyor. Nedenini anladığını umuyorum?";
			link.l1 = "Elbette.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_y113":
			dialog.text = "Pekala. O halde, dostum, belki de her şey mahvolmuş değil. Karayipler'de çatışmalar beklenir, değil mi? Bakanlıktan yeni bir müfettiş gelene kadar burada işleri toparlayıp misafirlerimizi silahlı bir şekilde karşılayacağız... Ve şimdi, Charles, tüm bağlantılarımızı kapatmamız gerekiyor. Nedenini anladığını umuyorum?";
			link.l1 = "Elbette.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_113":
			dialog.text = "Pekala. O halde, dostum, belki de her şey mahvolmuş değil. Korsanlar korsandır, öyle değil mi? Bakanlıktan yeni bir müfettiş gelene kadar burada ortalığı toparlayıp misafirlerimizi silahlarımızla hazır şekilde bekleyeceğiz... Ve şimdi, Charles, tüm bağlantılarımızı kapatmamız gerekiyor. Nedenini anladığını umuyorum?";
			link.l1 = "Elbette.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_114":
			dialog.text = "Her halükarda, dostum, elinden gelen her şeyi yaptın. Bu da hiç yoktan iyidir. Kaderin bizi bir araya getirmesine sevindim. Mevkiini koruyabilirsin, ve eminim Fransa'da seni parlak bir kariyer bekliyor. Ayrıca, bence artık Paris'e dönmenin vakti geldi. Al, babandan bir mektup. Bunu al.";
			link.l1 = "Babam mı? Bu harika bir haber!.. Peki, Mösyö, anladım. Hiçbir temas yok, tam gizlilik, ve mümkün olan en kısa sürede Paris'e gitmeliyim. Şimdi gidebilir miyim? Mektubu okumak istiyorum...";
			link.l1.go = "patria_115";
		break;
		
		case "patria_115":
			dialog.text = "Git, Charles. Bol şans!";
			link.l1 = "Ve size de, Şövalye!";
			link.l1.go = "patria_116";
		break;
		
		case "patria_116":
			DialogExit();
			AddQuestRecord("Patria", "78");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			sld = CharacterFromID(pchar.questTemp.Patria.SpanishID);
			SetCharacterRemovable(sld, true);
		break;
		
		case "patria_117":
			dialog.text = "Kesinlikle. Hiç kimsenin yapamayacağı kadar açık anlatıyorsunuz, amiral yardımcısı! Bunu sizden öğrenmeliyim!!";
			link.l1 = "Sizden çok şey öğrendim, Şövalye.";
			link.l1.go = "patria_118";
		break;
		
		case "patria_118":
			dialog.text = "Dostum, sana borçlandım. Emin ol, sevgili babanın hayatı boyunca ihtiyaç duyacağı her şey sağlanacak, aile eviniz ise eyaletin en güzel evi olacak... ve Fransa'nın en iyilerinden biri olacak. Ayrıca sana 100.000 peso ödeyeceğim - umarım bu, yol masraflarını karşılar ve hak ettiğin bir dinlenmenin tadını çıkarmana olanak tanır.";
			link.l1 = "Bunu duymak harika, Mösyö!";
			link.l1.go = "patria_105add";
		break;
		
		case "patria_119":
			DialogExit();
			AddQuestRecord("Patria", "87");
			pchar.questTemp.Patria = "europe";
			pchar.questTemp.Patria.Governor = "true"; // Шарль губернатор
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			SetFunctionTimerCondition("Patria_EuropeTime", 0, 0, 175+rand(10), false); // таймер
		break;
		
		case "patria_prison":
			dialog.text = "Bunu nasıl yapabildin, Charles! Bunu bana nasıl yapabildin?!";
			link.l1 = "Hımm...";
			link.l1.go = "patria_prison_1";
		break;
		
		case "patria_prison_1":
			dialog.text = "Biliyorum, sendin! Bunu sen yaptın! İnkar etme! Senin yardımın olmasaydı, Baron Forget asla maden müdüründen raporları, ne madenin yerini, ne de Peter Stuyvesant'ın belgelerini alabilirdi. Orada adın geçmiyordu ama söyleyeyim, eminim: sendin. Neden, Charles?.. Sadece cevap ver... Neden? Michel mi? Bir milyon peso mu? Levasseur mu? Yoksa Genel Vali makamı mı?";
			// belamour legendary edition -->
			link.l1 = "İlk karşılaşmamızı hatırlıyor musunuz, Şövalye? Beni nasıl hizaya getirdiğinizi? Benden nasıl bir milyon peso kopardığınızı? Sadece bir gün yer değiştirebilsek diye dilemiştim. Size söyleyecek başka bir sözüm yok.";
			link.l1.go = "patria_prison_2";
			link.l2 = "Levasseur için. Bir milyonluk borcu, bunu hâlâ anlayabiliyorum. Çalıştım, öldürdüm, kazandım, soydum ama sana verdiğim tüm zararı fazlasıyla ödedim. Yine de bu sana yetmedi. Sen, Şövalye, kişisel gücünü daha da artırmak için beni Taç'a karşı intihar görevine gönderdin! İhanetinin bir karşılığı olmalıydı. Ve cevabını aldın!";
			link.l2.go = "patria_prison_2";
			link.l3 = " Hırs, Şövalye. Bu tuhaf yeni dünyada, ulaşabileceğim hemen hemen her şeye zaten ulaşmıştım. Genel vali makamı bana layık bir hedef gibi görünüyordu. Sizden çok şey öğrendim. Hoşça kalın!";
			link.l3.go = "patria_prison_2";
			link.l4 = "Açıkçası, ben de tam olarak bilmiyorum. Belki de baronun ülkemize olan sadık hizmetinden etkilenmişimdir? Her neyse, artık bu meseleyi benim için düşünmek için bolca vaktin olacak. Hoşça kal!";
			link.l4.go = "patria_prison_2";
			// <-- legendary edition
		break;
		
		case "patria_prison_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;//закрыть переход
			LAi_SetActorType(npchar);
			SetFunctionTimerCondition("Patria_EuropePuancieClear", 0, 0, 5, false); // таймер
			pchar.quest.Patria_Europe_final.win_condition.l1 = "location";
			pchar.quest.Patria_Europe_final.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Europe_final.function = "Patria_EuropeFinal";
		break;
		
		case "patria_patentfail":
			DialogExit();
			pchar.questTemp.Patria = "fail";
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			// убрать Эклятон, если есть
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton"))
			{
				sld = characterFromId("Ecliaton_Cap");
				RemoveCharacterCompanion(pchar, sld);
				sld.lifeday = 0;
				DeleteAttribute(pchar, "questTemp.Patria.Ecliaton");
			}
		break;
		
		// Rebbebion, квест "Путеводная звезда"
		case "PZ_1":
			SetTimerCondition("PZ_NormanBackToStreets", 0, 0, 1, false);	//Вовзращаем Акулу или Тиракса в Шарптаун
			// ставим сразу прерывание, чтобы потом по тысячу раз не копировать
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				if (CheckAttribute(pchar, "questTemp.PZ.LongwayMayfang") || CheckAttribute(pchar, "questTemp.PZ.LongwayTorero") || CheckAttribute(pchar, "questTemp.PZ.LongwayElCasador"))
				{
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition.l1 = "location";
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition.l1.location = "Charles_town";
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition = "PZ_AfterPoincyLongwayDialog";
				}
			}
			
			if (!CheckAttribute(pchar, "questTemp.PZ_ChangShinMertva")) 
			{
				dialog.text = "Seni görmek güzel, Charles. Yaptıklarını duydum. Harika bir iş çıkarmışsın!";
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "Hepsi bu değil, Ekselansları.";
					link.l1.go = "PZ_2";
				}
				else
				{
					link.l1 = "Şimdi kardeşimin serbest bırakılması için sizden yazılı bir emir alabilir miyim?";
					link.l1.go = "serve";
				}
			}
			else 
			{
				dialog.text = "Greetings, Charles. Come in; I've already been informed.";
				link.l1 = "Bilgilendirildim mi? Bir yanlışlık olmalı, Ekselansları. Görevinizi başarıyla tamamladığımı bildirmeye geldim, fakat görüyorum ki keyfiniz pek yerinde değil.";
				link.l1.go = "PZ_PoincyAngry1";
			}
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube");
		break;
					
		case "PZ_2":
			dialog.text = "Öyle mi? Ne demek istiyorsunuz, Kaptan?";
			link.l1 = "Levasseur'u sağ olarak yakaladım ve size getirdim. İşimiz biter bitmez, onu huzurunuza çıkarmalarını emredeceğim.";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "Böyle bir şeyin mümkün olabileceğini hiç düşünmemiştim! Gerçekten harika bir iş çıkardın, Charles! Meşhur kardeşin bile bundan iyisini yapamazdı sanırım. Baban seninle gurur duyardı, dostum.";
			link.l1 = "Güzel sözleriniz için teşekkür ederim, Mösyö Philippe.";
			link.l1.go = "exit";
			npchar.greeting = "";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie");
		break;
		
		case "PZ_5":
			dialog.text = "Çok iyi, Charles. Senden memnunum.";
			link.l1 = "Kardeşimin şimdi serbest bırakılması için sizden yazılı bir emir alabilir miyim?";
			link.l1.go = "serve";
			LAi_SetHuberType(npchar);
		break;
		
		case "PZ_PoincyAngry1":
			dialog.text = "Belki de senin kardeşin olmadığını düşünmeliydim—ne bir asker, ne bir gizli ajan, ne de hassas işlerde tecrübeli birisin. Tortuga sokaklarında askerlerle açıkça çatışmamalıydın. Sorgulamalar olacak, bana da soracaklar. Hem de ciddi kişiler tarafından, anlıyorsun.";
			link.l1 = "Affedersiniz, Şövalye. Biliyorsunuz ki, Levasseur savaşmadan geri çekilmezdi.";
			link.l1.go = "PZ_PoincyAngry2";
		break;
		
		case "PZ_PoincyAngry2":
			dialog.text = "Doğru, ama... boşver. İlk operasyon için fena değil. Kraliyet Denetçisi'ne ve korumasına resmi bir denetim sırasında saldırdığını rapor edeceğim.";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
			{
				link.l1 = "Majesteleri, isterseniz Levasseur'u size getirebilirim. Adamlarımla birlikte, onun adamları sokakta bizi yakalamaya çalıştıktan sonra, onu tenha bir yerde yakalama şansını bulduk.";
				link.l1.go = "PZ_PoincyAngry3";
			}
			else
			{
				link.l1 = "Kardeşimin şimdi serbest bırakılması için sizden yazılı bir emir alabilir miyim?";
				link.l1.go = "serve";
			}
		break;
				
		case "PZ_PoincyAngry3":
			dialog.text = "Ne dedin Charles? Bir daha söyler misin.";
			link.l1 = "François Levasseur şu anda ambarımda, size teslim edilmeye hazır, Mösyö Philippe.";
			link.l1.go = "PZ_PoincyAngry4";
		break;
		
		case "PZ_PoincyAngry4":
			dialog.text = "Daha önce söylediklerimi unut. Kesinlikle fazla tepki verdim. Harika bir iş çıkardın. Eminim, senin o meşhur kardeşin bile bunu başaramazdı.";
			link.l1 = "Teşekkür ederim, Şövalye.";
			link.l1.go = "PZ_PoincyAngry5";
		break;
		
		case "PZ_PoincyAngry5":
			dialog.text = "Büyük bir potansiyelin var, dostum. Keşke yeteneklerini ülkemizin iyiliği için daha sık kullanabilsen. Ama lütfen, bundan sonra biraz daha... dikkatli olmaya çalış. Bizim işimiz genellikle hassas bir yaklaşım gerektirir. Ah evet, bir de bir şey daha.";
			link.l1 = "Evet, Ekselansları?";
			link.l1.go = "exit";
			npchar.greeting = "";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
