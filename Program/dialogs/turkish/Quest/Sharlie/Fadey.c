int iFadeyPseudoGlobal;

// Фадей Московит
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;
	string sTemp;
    bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//--> LoyaltyPack
			if (GetDLCenabled(DLC_APPID_1))
			{
				if (CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.Fadey", "ready"))
				{
					link.l32 = "Fadey, Alonso adında bir adamı tanıyor musun?";
					link.l32.go = "LoyaltyPack_Fadey_1";
				}
				if (CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.Fadey", "money") && PCharDublonsTotal() >= 1000)
				{
					link.l32 = "Fadey, aynalı göğüs zırhını satın almaya hazırım.";
					link.l32.go = "LoyaltyPack_Fadey_1000";
				}
			}
			//<-- LoyaltyPack
			if (CheckAttribute(pchar, "questTemp.Sharlie"))
			{
				if (pchar.questTemp.Sharlie == "fadey")
				{
					dialog.text = "Size nasıl yardımcı olabilirim, Mösyö? Tanımadığım insanlarla konuşmam. Eğer sadece sohbet etmek ya da 1640 yılında Maracaibo'ya İspanyol Gümüş Treni'nin hangi ayda geldiğini sormak için uğradıysanız, sizi hayal kırıklığına uğratacağım. Boş laflara vaktimi harcamam.";
					link.l1 = "İyi günler, Mösyö Fadey. Benimle henüz tanışmamış olabilirsiniz, ama kardeşimi tanıyorsunuz. Kendimi tanıtmama izin verin - Charles de Maure, Michel de Monper’in kardeşi.";
					link.l1.go = "Sharlie";
					break;
				}
				if (pchar.questTemp.Sharlie == "takeknife" && !CheckAttribute(pchar, "questTemp.Persian"))
				{
					dialog.text = "Aha, yine sen, Charles! Nasılsın? Bu sefer ne var?";
					link.l1 = "Soyulduğunu söylemiştin... Suçluları bulabildin mi?";
					link.l1.go = "Sharlie_8";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "fadey")
				{
					dialog.text = "Yani Charles, o vahşiyle konuşmaya gittin mi?";
					link.l1 = "Ben de... Bu yüzden tekrar sana geldim.";
					link.l1.go = "Tichingitu";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "dublon")
				{
					dialog.text = "Ah, yine sen geldin, sevgili dostum! Ee, Hintli için fidye altınlarını getirdin mi?";
					if (CheckAttribute(npchar, "questTemp.Sharlie.Tichingitu_Skidka"))
					{
						if (PCharDublonsTotal() >= 35) // belamour legendary edition
						{
							link.l1 = "Evet. İşte senin 35 doblonun.";
							link.l1.go = "Tichingitu_7";
						}
						else
						{
							link.l1 = "Hayır, henüz yeterince toplamadım.";
							link.l1.go = "exit";
						}
					}
					else
					{
						if (PCharDublonsTotal() >= 40) // belamour legendary edition
						{
							link.l1 = "Evet. İşte 40 dublonun.";
							link.l1.go = "Tichingitu_7";
						}
						else
						{
							link.l1 = "Hayır, henüz yeterince toplamadım.";
							link.l1.go = "exit";
						}
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "begin")
				{
					dialog.text = "Ha, demek bizzat Monsieur de Maure gelmiş! Dedim ya, içeri gel, öyle ayakta durma! Seni benim evime getiren nedir?";
					link.l1 = TimeGreeting()+", Fadey, ağabeyim bana sana gelmemi söyledi. Bana iş bulmamda yardımcı olacağını söyledi.";
					link.l1.go = "trial";
					// опоздал
					if (CheckAttribute(pchar, "questTemp.Trial.late")) {
						link.l1.go = "trial_late";
					}
					break;
				}
				if (pchar.questTemp.Sharlie == "trial" && !CheckAttribute(npchar, "quest.vodka"))
				{
					dialog.text = "Ha, demek sensin! Seni buraya ne getirdi, Monsieur de Maure?";
					link.l1 = TimeGreeting()+", Fadey. Ağabeyim bu konuda seninle konuşmamam gerektiğinde ısrar etti, ama kendimi tutamadım... ";
					link.l1.go = "vodka";
					break;
				}
				// belamour legendary edition пиратская линейка -->
				if(CheckAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves") && pchar.questTemp.Mtraxx.GiveMeSlaves == "Baster")
				{
					dialog.text = "Ah, eski dostum! Gir içeri, gir, "+pchar.name+"! Nasılsın?";
					link.l1 = TimeGreeting()+" , Fadey. Seni görmek güzel. Aslında, konuşmamız gereken önemli bir işim var. Kara altın.";
					link.l1.go = "Slaves";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves") && pchar.questTemp.Mtraxx.GiveMeSlaves == "FindGold")
				{
					dialog.text = "Ah, yine sen geldin, sevgili dostum! Ganimeti buldun mu? Yeterince dublon bulabildin mi?";
					if(PCharDublonsTotal() >= 150)
					{
						link.l1 = "Evet, Mösyö Fadey! Altınınız burada.";
						link.l1.go = "Slaves_2";
					}
					else
					{
						link.l1 = "Hayır, sadece uğruyorum. Hâlâ doğru miktarı arıyorum.";
						link.l1.go = "exit";
					}
					
					link.l2 = "Fadey, az önce aklıma bir fikir geldi. Artık kölelere ihtiyacım yok. Beni mazur gör, sonra görüşürüz!";
					link.l2.go = "Slaves_3";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Baster")
				{
					dialog.text = "Ah, eski dostum! Gel, gel, "+pchar.name+"! Nasılsın?";
					if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves"))
					{
						if(pchar.questTemp.Mtraxx.GiveMeSlaves == "Deal" || pchar.questTemp.Mtraxx.GiveMeSlaves == "WithoutSlaves")
						{
							link.l1 = TimeGreeting()+", yine yardımına ihtiyacım var.";
						}
					}
					else
					{
						link.l1 = TimeGreeting()+", Fadey. Seni görmek güzel. Seninle konuşacak bir işim var.";
					}
					link.l1.go = "pistols";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "FindMoney")
				{
					dialog.text = "Ah, yine sen misin, sevgili dostum! Ee, parayı bulabildin mi?";
					if(PCharDublonsTotal() >= 75)
					{
						link.l1 = "Teslim ettim, Mösyö Fadey! İşte 75 dublonunuz.";
						link.l1.go = "pistols_4D";
					}
					if(sti(Pchar.money) >= 40000)
					{
						link.l2 = "Ben getirdim, Mösyö Fadey! İşte sizin 40.000 peso.";
						link.l2.go = "pistols_4P";
					}
					if(PCharDublonsTotal() < 75 || sti(Pchar.money) < 40000) 
					{
						link.l3 = "Hayır, sadece uğruyorum. Hâlâ uygun miktarı arıyorum.";
						link.l3.go = "exit";
					}
					link.l4 = "Affedersin Fadey, ama bunu karşılayacak durumda değilim. Kendi başıma halletmeye çalışacağım. Görüşürüz!";
					link.l4.go = "pistols_x";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Today")
				{
					dialog.text = "Gel, gel, "+pchar.name+"! Gözlerinde başarılarımı duymak istediğini görebiliyorum.";
					link.l1 = "Aynen öyle, Fadey. İstediğim şeyi getirdiğine güveniyorum.";
					link.l1.go = "pistols_5";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "FindMoney")
				{
					dialog.text = "Ah, yine sen geldin, sevgili dostum! Ee, parayı bulabildin mi?";
					if(PCharDublonsTotal() >= 75)
					{
						link.l1 = "Al yetmiş beş dublon. Bu sandığı gemime taşımaları için tayfalara söyleyeceğim. Ah Fadey, sensiz ne yapardım ben?! Bana ne kadar çok yardım ettiğini tahmin bile edemezsin!";
						link.l1.go = "pistols_5D";
					}
					if(sti(Pchar.money) >= 40000)
					{
						link.l2 = "Al kırk bin peso. Tayfalara bu sandığı gemime taşımalarını söyleyeceğim. Ah, sensiz ne yapardım, Fadey?! Bana ne kadar yardımcı olduğunu tahmin bile edemezsin!";
						link.l2.go = "pistols_5P";
					}
					if(PCharDublonsTotal() < 75 || sti(Pchar.money) < 40000) // возможность найти без отказа
					{
						link.l3 = "Hayır, sadece uğruyorum. Hâlâ yeterince toplamaya çalışıyorum.";
						link.l3.go = "exit";
					}
					link.l4 = "Excuse me, Fadey, I'm completely broke. Keep the deposit; I hope it will be enough to cover your expenses for this deal, and I'll try to manage on my own. See you!";
					link.l4.go = "pistols_x";
					break;
				}
				// <-- legendary edition
				//--> Дикая Роза
				if (CheckAttribute(pchar, "questTemp.WildRose_Etap5_Fadey"))
				{
					dialog.text = "Ah, işte buradasınız, iyi adam! Geminizin limanımıza demir attığını öğrenince, belki beni ziyaret edersiniz diye ummuştum.";
					link.l1 = "Merhaba, "+npchar.name+".  Seni uzun bir hikayeyle sıkmayacağım. Ben ve yol arkadaşım Mary, yirmi yıl önce hiçbir iz bırakmadan ortadan kaybolan babasını arıyoruz...";
					link.l1.go = "WildRose_Fadey_4";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.WildRose_Etap5_Fadey_2")) 
				{
					link.l31 = "Mary'nin babasına gelince...";
					link.l31.go = "WildRose_Fadey_return";
				}
				if (CheckAttribute(pchar, "questTemp.WildRose_Etap5_Fadey_3"))
				{
					dialog.text = "Bak hele, kim gelmiş, "+pchar.name+"!";
					link.l1 = "Adeta parlıyorsun, "+npchar.name+"   Ee, anlat bakalım—bir şey öğrenebildin mi?";
					link.l1.go = "WildRose_Fadey_16";
					break;
				}
				//<-- Дикая Роза
				if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && pchar.questTemp.Guardoftruth.Baster_church == "seek")
				{
					dialog.text = "Ah, İşaretli Olan—yani "+pchar.name+" ! Hadi, bana neyin var söyle bakalım!";
					link.l1 = TimeGreeting()+", Fadey. Seni görmek güzel. Seninle iş hakkında konuşmaya geldim.";
					link.l1.go = "guardoftruth";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && pchar.questTemp.Guardoftruth.Baster_church == "find" && !CheckAttribute(npchar, "quest.utensil"))
				{
					dialog.text = TimeGreeting()+", "+pchar.name+". Ruhumla hesaplaştığım o konuşmanın sonucunu papazdan öğrenmek için sabırsızlandığına eminim.";
					link.l1 = "Elbette öyleyim! Nasıl geçti?";
					link.l1.go = "guardoftruth_9";
					break;
				}
				if (CheckAttribute(npchar, "quest.utensil") && PCharDublonsTotal() >= 250)
				{
					dialog.text = "Ah, affedersiniz, ceplerinizdeki şıngırtıdan öyle dikkatim dağıldı ki!";
					link.l1 = "Ne açgözlülük bu, Fadey! Al altınını.";
					link.l1.go = "guardoftruth_11";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "guadeloupe")
				{
					dialog.text = "Aha, eski dostum! Gel, gel, "+pchar.name+"! Ee, yeni bir şeyin var mı?";
					link.l1 = "Merhaba, Fadey. Yine desteğini istemeye geldim.";
					link.l1.go = "guardoftruth_14";
					break;
				}
				dialog.text = "Ne oldun, heykel misin? Söyleyecek bir şeyin varsa, dökül. Yoksa, yoluna devam et. "+pchar.name+"!";
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "start" && CheckNCountPersian() > 0)
				{// персидские клинки
					link.l2 = "Bir bak, Fadey. Sanırım bu bir Fars şemşiri, muhtemelen koleksiyonundan çalınanlardan biri?";
					link.l2.go = "persian";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "one" && CheckNCountPersian() > 0)
				{
					link.l2 = "Sana iyi bir haberim var. Burada senin için bir Fars şemşiri daha var.";
					link.l2.go = "persian_6";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "two" && CheckNCountPersian() > 0)
				{
					link.l2 = "Üçüncü bir Fars şemşirim var. İstediğin gibi, mümkün olan en kısa sürede geri getirdim.";
					link.l2.go = "persian_9";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "cirass")
				{
					link.l2 = "Hani şu konuştuğumuz hafif zırh için geldim.";
					link.l2.go = "persian_13";
				}
				if(CheckAttribute(npchar, "quest.ropes") && GetDataDay() == 20) // торговля канатами
				{
					link.l3 = "Fadey, meşhur halatlarından biraz almak istiyorum.";
					link.l3.go = "ropes";
				}
				link.l1 = "Fadey, yardımına ihtiyacım var.";
				link.l1.go = "help";
 				link.l9 = "Hayır, şu anda hiçbir şey yok.";
				link.l9.go = "exit";
			}
			else
			{
				dialog.text = "Size nasıl yardımcı olabilirim, Mösyö? Tanımadığım insanlarla konuşmam.";
				link.l1 = "Ah, sadece burada kimin yaşadığını görmek için uğradım.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Sharlie":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("baster_town", "reload", "houseSp1");
			dialog.text = "Ah, demek sen iyi kalpli Michel'in küçük kardeşisin! Bu her şeyi değiştirir! Buyur, buyur Monsieur, otur lütfen. Toplantımızı kutlamak için bir kadeh votka içer misin? Hâlâ birkaç şişem kaldı, iyi bir dostun kardeşiyle paylaşmak büyük zevk olurdu, da!";
			link.l1 = "Beni affedin, Mösyö Fadey, ama bu gece içki içmek bana göre değil. Doğrudan işe geçmeyi tercih ederim.";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "Ne diyorsunuz! Bu yerel rom, Rus votkasının yanında su gibi kalır! Neler kaçırdığınızı bilmiyorsunuz, yalan söylüyorsam deniz beni alsın! Peki, işimize dönelim o zaman. Sizi dinliyorum Charles.";
			link.l1 = "Monsieur, size söyleyeceklerim pek hoşunuza gitmeyecek, ama ne yazık ki görevim gereği anlatmak zorundayım! Michel bana, kendisine kumarda hatırı sayılır bir borcunuz olduğunu söyledi. Ayrıca, parayı bana teslim etmenizi istedi, çünkü kardeşim... şu anda şahsen gelip sizi göremeyecek durumda.";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "Ah, genç adam! Elbette, her şeyi hatırlıyorum ve kardeşinize borçlu olduğumu kabul ediyorum. Kumar borcu kutsaldır, bu sorumluluğu yerine getirmek bizi ölümcül anarşiden ve tehlikeli haydutlardan koruyan tek şeydir! Ama size yalvarıyorum, lütfen halimi anlayın! Yakın zamanda başıma tatsız bir olay geldi - beni en yüzsüz şekilde soydular!\nLanet olası hırsızlar ellerine ne geçtiyse, yıllarca çalışarak kazandığım her şeyi, paramı ve paha biçilmez koleksiyonumu aldılar! Şu anda borcumu ödeyemem, maalesef\nAma, Mösyö de Maure, yükümlülüklerimden vazgeçmem! Sadece sizden biraz anlayış bekliyorum. Şu anda elimde hiç para olmadığı için size bu harika, nadir hançeri sunuyorum. Bir bakın!\nBu, çalınan koleksiyonumun gururu, gerçek bir çelik şaheseri. Üstelik, Hintli şamanlar tarafından büyülenmiş ve gizli güçlü yeteneklere sahip! Yerliler ona Şefin Pençesi derdi\nNormalde asla vermeye razı olmazdım, çünkü hançer için borcumdan çok daha fazla para ödedim. Ama şartları ve ağabeyinizle olan ilişkimi düşünerek, size vermeye hazırım. Alın, bu gerçekten iyi bir anlaşma!";
			link.l1 = "Paradan bıçağı bin kere tercih ederim...";
			link.l1.go = "Sharlie_3";
		break;
		
		case "Sharlie_3":
			dialog.text = "Ama param yok ve elimde bu nadir, büyülü eser var! Söylesene, drug moy, başka bir durumda sana birkaç değersiz gümüş para yerine bu muazzam sihirli hançeri teklif edeceğimi gerçekten düşünüyor musun? Peso her yerde bulunur, sokakta bile rastlayabilirsin! Kabul etmelisin, biraz köşeye sıkıştım. Bu eşsiz ustalık eseriyle vedalaşma düşüncesi bile yüreğimi sızlatıyor, ama kumar borcu namus borcudur; bu yüzden, bana çok kıymetli olmasına rağmen, onu sadece sana vermeye razıyım, çünkü sen gerçek bir onur adamı ve gerçek bir dostsun.";
			link.l1 = "Pekala, madem paran olmadığını söylüyorsun, o zaman şu sihirli hançerini alacağım. Umarım iyi bir fiyata satabilirim...";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			dialog.text = "'Sat onu' mu!? Defol buradan, stal- yani Charles! Hayır, kulaklarıma inanamıyorum! En değerli hazinemi veriyorum, ki Avrupa'da bundan en az on kat fazlasını alabilirdim, sen ise burada utanmadan bunu bozdurup gideceğini mi söylüyorsun!? Bak, bu hançer, delikanlı, bir adamın hayatını kurtardı! Bak anlatayım sana-";
			link.l1 = "Ve bahsettiğin bu gizli güç nedir?";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			dialog.text = "Oh, ho ho! Şimdi Charles, ben iyi bir Hristiyanım biliyorsun, öyle bir Kızılderili şamanı değilim. Bu bıçağın tüm gizli özelliklerini bilmem mümkün değil. Ama varlar, hem de nasıl! Bu hançeri eline al, içindeki gücü kendin hissedeceksin! Al, al! Ne dersin! Bir şey hissediyor musun?";
			link.l1 = "Hm... Hiçbir şey hissetmiyorum. Yine de elimde rahatça duruyor.";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			dialog.text = "Ah ha! İşte bu! Ama bu onun en önemsiz özelliği. Bu hançeri savaşta kullanırsan, eminim gücünü çok farklı şekillerde gösterecektir! Peki, alıyor musun?";
			link.l1 = "Pekâlâ, başka seçeneğim var mı? Alıyorum, madem paran yok...";
			link.l1.go = "Sharlie_7";
		break;
		
		case "Sharlie_7":
			GiveItem2Character(pchar, "knife_01");
			PlaySound("interface\important_item.wav");
			//Log_Info("You've received the Chief's Claw'");
			sld = ItemsFromID("knife_01");
			sld.Weight = 1.5;
			sld.price = 0;
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddMapQuestMarkCity("FortFrance", false);
			dialog.text = "Teşekkür ederim, Charles. Buna pişman olmayacaksın, emin ol! Al bakalım. Michel’e de selamımı ilet lütfen! Ona fırsat bulunca uğramasını söyle.";
			link.l1 = "Ah, ona söylerim...";
			link.l1.go = "exit";
			link.l2 = "Soyulduğunu söylemiştin... Suçluları bulabildin mi?";
			link.l2.go = "Sharlie_8";
			pchar.questTemp.Sharlie = "takeknife";
			AddQuestRecord("Sharlie", "18-1");
			sld = characterFromId("Mishelle");	
			sld.greeting = "mishelle_2";
			
			// Sinistra - Старт квеста "Деньги на деревьях"
			PChar.quest.MOT_BarbieSpawn.win_condition.l1 = "location";
			PChar.quest.MOT_BarbieSpawn.win_condition.l1.location = "BasTer_town";
			PChar.quest.MOT_BarbieSpawn.win_condition = "MOT_BarbieSpawn";
			//убрать запрет боёвок на Мартинике
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_town")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_townhall")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_prison")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_fort")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_ammo")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("LeFransua_town")], false);
			LocatorReloadEnterDisable("FortFrance_townhall", "reload2", false);
			LocatorReloadEnterDisable("FortFrance_townhall", "reload3", false);
			sld = &Locations[FindLocation("FortFrance_prison")];
			sld.locators_radius.item.detector1 = 0.5;
		break;
		
		case "Sharlie_8":
			dialog.text = "The problem is, I haven't. Those ruffians cleared out the whole house, ran off with all the silver, gold, my savings from years of back-breaking labour. Now, that usually doesn't bother me; after all, a real gentleman, even if he loses everything he owns, must show no emotion! Money must be so far beneath a gentleman that it is hardly worth troubling about. But the worst part is, they swooped up my magnificent collection of Persian shamshirs! There isn't a collection like it in all of the New or Old World combined. Truly remarkable Persian cavalry swords...";
			link.l1 = "Fars kılıçları mı dediniz? Kulağa oldukça ilginç geliyor. Demek koleksiyoncusunuz, öyle mi?";
			link.l1.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			dialog.text = "Şey, nadir şeyleri toplamayı severim... Bak Charles, belki bu konuda bana yardımcı olabilirsin...";
			link.l1 = "Yardım mı? Ama nasıl? Hırsızları yakalamamı mı istiyorsunuz?";
			link.l1.go = "Sharlie_10";
		break;
		
		case "Sharlie_10":
			dialog.text = "Hayır. Hırsızlarla özellikle ilgilenmiyorum. Fars süvari kılıçlarımı geri almak istiyorum. Eğer bulursanız, karşılığını fazlasıyla vereceğim, söz veriyorum.";
			link.l1 = "Hm. Ama onları nerede arayacağım ki? Karayipler'de mi? Yoksa tüm dünyada mı?";
			link.l1.go = "Sharlie_11";
		break;
		
		case "Sharlie_11":
			dialog.text = "Well, perhaps you'll catch sight of them on the islands at some street merchants; those scoundrels can't even comprehend the value of those cavalry swords, and they'll surely sell them for scraps. So if you see the Persian swords anywhere, bring them to me. Will you be able to recognise them?";
			link.l1 = "Bence öyle yapacağım. Tamam, gözümü dört açarım, tarifine uyan alışılmadık bir kılıç görürsem mutlaka sana getiririm.";
			link.l1.go = "Sharlie_12";
			link.l2 = "Biliyor musun, silahlar konusunda uzman sayılmam. Korkarım sana yardımcı olamayacağım. Bu yüzden sana boşuna umut vermem dürüst olmaz.";
			link.l2.go = "Sharlie_13";
		break;
		
		case "Sharlie_12":
			dialog.text = "Harika! Umarım şansın yaver gider ve o eserleri bulursun, ben de karşılığını fazlasıyla veririm. İyi avlar, avcı— pardon, kaptan! Evet Charles, düşünebiliyor musun, yakın zamanda yine soygun girişimi yaşadım!\nBir hırsız birkaç gün önce evime girmeye çalıştı\nBu bana fazla geldi! Ama bu sefer elimden kaçamadı, yakaladım, iyi bir patakladım ve şehirdeki hapishanede nöbetçilere teslim ettim. Umarım yakında onu asarlar!";
			link.l1 = "Sence o, şemşirlerini çalan hırsızlardan biri mi?";
			link.l1.go = "Sharlie_14";
			pchar.questTemp.Persian = "start";
			// --> скимитар 021012
			pchar.questTemp.Persian.skimitar = "true";
			pchar.quest.Persian.win_condition.l1 = "item";
			pchar.quest.Persian.win_condition.l1.item = "blade_23";
			pchar.quest.Persian.function = "Persian_FindSkimitar";
		break;
		
		case "Sharlie_13":
			dialog.text = "Yazık, ama boşuna hayal kurmanın anlamı yok. Evet Charles, düşünebiliyor musun, daha geçenlerde yine bir soygun girişimi yaşadım!\nBir hırsız birkaç gün önce evime girmeye kalktı\nBu bana fazlasıyla ağır geldi! Ama benden kaçamadı: Onu yakaladım, güzelce dövdüm ve yerel hapishaneye gönderdim. Başkasının acısı üzerinden mutlu olunmaz. Umarım yakında onu asarlar!";
			link.l1 = "Sence o, şemşirlerini çalan hırsızlardan biri mi?";
			link.l1.go = "Sharlie_14";
			pchar.questTemp.Persian = "end";
		break;
		
		case "Sharlie_14":
			dialog.text = "Hayır, sanmıyorum. Paranın peşindeydi. Onu odamda, sandıklarımı karıştırırken yakaladım\nİspanyol Sahili'nin derin ormanlarından bir Kızılderili. Buradaki yerlilere hiç benzemiyor, tuhaf görünüyor. Savaş boyasıyla kaplanmış, rengârenk bir kostüm giymiş... İstersen zindana inip şu soytarıyı kendin görebilirsin, hâlâ yaşıyorken.";
			link.l1 = "Hm... Belki uğrar, onu görürüm.";
			link.l1.go = "Sharlie_15";
		break;
		
		case "Sharlie_15":
			dialog.text = "Devam et, ucube gösterisine bir göz at... Horosho, Charles, güzel bir sohbetti. Martinique'e dönüş yolunda iyi yolculuklar, poputniy veter!";
			link.l1 = "Her şey gönlünce olsun, Fadey.";
			link.l1.go = "exit";
			SetQuestHeader("Tichingitu");
			AddQuestRecord("Tichingitu", "1");
			pchar.questTemp.Sharlie.Tichingitu = "true";
			AddDialogExitQuestFunction("Tichingitu_SetTichingituJail");
			SetFunctionTimerCondition("Tichingitu_FreeTichingituOver", 0, 0, 10, false);
			pchar.questTemp.Sharlie = "takeknife";
		break;
		
		case "Tichingitu":
			DelLandQuestMark(npchar);
			dialog.text = "Ne kadar ilginç! Dinliyorum.";
			link.l1 = "Fadey, o Kızılderiliyle konuştum. Onu oradan çıkarmak için senden yardım istemeye geldim. Zavallı adam sadece bir lokma yemek istemiş...";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "Hahaha, ve sen o hikayeye inandın mı? Şimdiki gençler ne kadar saf...";
			link.l1 = "Fadey, senden daha genç olabilirim ama bana doğruyu mu söylüyorsun yoksa yalan mı söylüyorsun, bunu ayırt edebiliyorum. Ayrıca, böyle bir suç için asılmanın uygun bir ceza olduğunu gerçekten düşünüyor musun? Bana fazla gibi geliyor. Bizde olsa, en fazla birkaç kırbaç ya da tekrar eden biriysen damga basılırdı.";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			dialog.text = "Aşırı mı!? Evime zorla girdi! O vahşi asla buraya gelmemeliydi! Benim yerimde olsan ne yapardın? Eminim onun iç organlarını dışarı çıkarır, onu solucanlara yem ederdin, değil mi?!";
			link.l1 = "Hayır, yapmazdım Fadey. Hâlâ çalınan şemşir koleksiyonuna kızgınsın. O olay olmasaydı, bu aptal Kızılderiliye güzel bir dayak atıp tekmeyi basmaya daha istekli olurdun, yanılıyor muyum?";
			link.l1.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			dialog.text = "Ahhhh, Charles... Sen de tıpkı kardeşin gibisin... Horosho. Bunu dürüst tüccarlar gibi halledeceğiz. Madem bu Hintliyi bu kadar istiyorsun, bana yaşattığı manevi sıkıntı ve verdiği maddi zararı telafi et, ben de komutana şikayetçi olmak istemediğimi söylerim. Ne dersin?";
			link.l1 = "Ne kadar?";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "Ha, Karayipler'in usullerini öğrenmeye başladın bile, Charles. Yüz elli altın doblon, bir kuruş eksik olmaz.";
			link.l1 = "Fadey, Tanrı merhamet etsin...";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			dialog.text = "Peki, peki, 40 altın dublon. Ama bu son fiyatım. Ve dublon, peso değil. Bizim tefeci mutlaka bulunduruyordur.";
			if(PCharDublonsTotal() >= 40) // belamour legendary edition
			{
				link.l1 = "İstediğin miktar şu anda bende var. Al, işte senin 40 dublonun.";
				link.l1.go = "Tichingitu_7";
			}
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l2 = "(Güvenilir) Fadey, dinle... Sinirini anlıyorum ama bu sıkıntı için sana gerçek parayla ödeme yapmaya razı olan tek kişi benim.";
				link.l2.go = "Tichingitu_7_TW";
			}
			else Notification_Perk(false, "Trustworthy");
			link.l3 = "Pekala, gidip ihtiyacın olanı getireceğim.";
			link.l3.go = "Tichingitu_6";
		break;
		
		case "Tichingitu_7_TW":
			dialog.text = "Ah, sen çok yol alırsın dostum. Beni ikna ettin! 35 altın — bir kuruş bile eksik olmaz!";
			link.l1 = "";
			link.l1.go = "Tichingitu_6";
			npchar.questTemp.Sharlie.Tichingitu_Skidka = true;
		break;
		
		case "Tichingitu_6":
			dialog.text = "Ve acele et, Charles! İdam edilmesine sadece on gün kaldı.";
			link.l1 = "Bunu aklımda tutacağım. Hoşça kal!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie.Tichingitu = "dublon";
		break;
		
		case "Tichingitu_7":
			if(CheckAttribute(npchar,"questTemp.Sharlie.Tichingitu_Skidka"))
			{
				RemoveDublonsFromPCharTotal(35);
				DeleteAttribute(npchar,"questTemp.Sharlie.Tichingitu_Skidka");
			}
			else RemoveDublonsFromPCharTotal(40); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Çok iyi. Hemen şimdi bir not yazıp mühürleyeceğim, bir saniye bekle... işte al. Bunu komutana ver, sonra Yerlini yanında götürebilirsin. Neden bu kadar çok önemsediğini tam anlamadım ama o senin meselen. Ne yapacaksın, onu maskeli baloda mı sergileyeceksin? Haha, ne fikir ama!";
			link.l1 = "Tanrı her şeyi görür, Fadey. Bir insanın hayatını kurtarmak asil bir iştir.";
			link.l1.go = "Tichingitu_8";
		break;
		
		case "Tichingitu_8":
			GiveItem2Character(pchar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_letter_1_Fadey");
			PlaySound("interface\important_item.wav");
			dialog.text = "İlk söylediğine katılıyorum, ama ikinci dediğin tartışılır, Charles. Ya bir katili ya da bir tecavüzcüyü ipte bekleyen adaletten kurtarırsan?  Bah, neyse, artık benim derdim değil. Tanrı yardımcın olsun. Komutana git, yoksa kızıl derili dostun boynuna ip dolanınca beti benzi atacak...";
			link.l1 = "Yoldayım. Sonra görüşürüz, Fadey.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie.Tichingitu = "pay";
			SetFunctionLocationCondition("Tichingitu_AddQuestMark", "baster_prison", false);
			QuestPointerToLoc("BasTer_town", "reload", "reload_jail");
			QuestPointerDelLoc("baster_town", "reload", "houseSp1");
		break;
		
		case "vodka":
			dialog.text = "Keyfin yok gibi, dostum! Sanırım bana kötü bir haber getireceksin?";
			link.l1 = "Durumun özü bu, evet. Sana açık konuşacağım, Fadey: Michel, şu 'Şefin pençesi' saçmalığıyla beni kandırdığını söyledi. Bunun bir eser olmadığını, herhangi bir sokak satıcısından birkaç yüz pesoya alabileceğimi söyledi. Metal eşya satan sokak satıcılarına sordum. Tam da o fiyatı verdiler bana.";
			link.l1.go = "vodka_1";
			npchar.quest.vodka = "true";
		break;
		
		case "vodka_1":
			dialog.text = "Ah, Monsieur de Maure... Çok kırıldım! Kardeşin beni şaşırttı. Sokaktaki şu yarım akıllı sahtekârlar ne derse desin, ama o! Söylesene Charles, biri sana Şarlman zamanından kalma eski bir şövalye kılıcı getirip satmak istese, ona ne verirdin?";
			link.l1 = "İki elli bir kılıç mı? Şaka mı yapıyorsun Fadey, ciddi misin? Ne işime yarar paslı bir cellat palası? Burası İsa Mesih’in on yedinci yüzyılı! Ona bir peso bile vermem!";
			link.l1.go = "vodka_2";
		break;
		
		case "vodka_2":
			dialog.text = "Ah, şimdi bak da gör, ne kadar dar görüşlüsün dostum! Bu tavırla hiçbir yere varamazsın. Ve eğer böyle bir eseri bana getirseydin, sana üç yüz doblon öderdim. Neden mi? Çünkü bu bir antika, tarihi bir hazine, bu devirde bulması çok zor! Anlamıyorsun ama yine de yargılıyorsun! Tanrı ve Kutsal Annesi şahit olsun, Şef'in Pençesi bir başyapıt hançer—kaynaklarım bana Cortés’in bizzat kendisine ait olduğunu söylüyor. O Hernán Cortés! Tenochtitlan’ı yağmalayan, Aztek imparatorunu ele geçiren efsanevi fatih! Ve sen küçümseyip bunun sıradan bir çöp olduğunu söylüyorsun! Ayrıca, sana zaten söyledim, bu herhangi bir hançer değil—büyülü bir hançer! Hâlâ o kadar toy musun ki Karayipler’in bütün harikalarını görmedin mi? Büyüler ve sihirler, ritüeller ve lanetler? Charles, burası Yeni Dünya, Maya ve Azteklerin anavatanı; onların bu şeytani sanatlar konusundaki bilgisi bizim Hristiyan aklımızın alamayacağı kadar yüksekti! Bu hançerin gizli güçleri var. Ne yazık ki, henüz kimse ne tür güçler olduğunu bilmiyor. Senin elinde, onun neler yapabileceğini kendi gözlerinle keşfetmek için eşsiz, inanılmaz bir fırsat var, ama hâlâ bunun bir 'bok parçası' olduğunu ve zavallı, yaşlı dostun Fadey’in seni kandırmaya çalıştığını iddia ediyorsun! Keşke kardeşine olan borcumu ödeyecek kadar param olsaydı, hemen senden o aşağılık parana karşılık geri alırdım... Bu çok değerli bir eşya ve değeri sadece parayla ölçülmez, da!";
			link.l1 = "Pekala, pekala, sakin ol Fadey. Sana inanıyorum. Argümanların oldukça ikna edici ve gösterdiğin ateşli tutku ya samimiyetinin bir kanıtı ya da eşsiz kurnazlığının.";
			link.l1.go = "vodka_3";
		break;
		
		case "vodka_3":
			dialog.text = "Teşekkürler! Charles, gücenmeden doğrudan açıklama istemeye geldiğin için iyi iş çıkardın. Şimdi meseleyi hallettik, değil mi?";
			link.l1 = "Evet, Mösyö Fadey. Tamamen. Şimdi, lütfen, müsaadenizle ayrılmak istiyorum...";
			link.l1.go = "vodka_4";
		break;
		
		case "vodka_4":
			PlaySound("Voice\English\sharlie\Fadey Moskovit-04.wav");
			dialog.text = "Dur, Charles! Açık konuşacağım, tarzını beğeniyorum. Belki bir gün seninle çok iyi dost olabiliriz. Neden o dostluğun ilk adımını şimdi atmayalım? Aşağıdaki kilerde, buz gibi kaynak suyunda iki şişe enfes Rus votkası soğutuyorum. Ne dersin, bir şişe açıp kardeşinin sağlığına içelim mi?";
			link.l1 = "Hm. Üzgünüm, Mösyö Fadey, ama artık yelken açma vaktim geldi. Biraz acelem var.";
			link.l1.go = "vodka_no";
			link.l2 = "Geçen sefer teklif ettin, ben reddettim... İki kez reddetmek ayıp olurdu. Peki, Fadey. Varım!";
			link.l2.go = "vodka_5";
		break;
		
		case "vodka_no":
			dialog.text = "Ne yazık. Votkayla karşılaştırınca rom su gibi, ucuz ve tatsız bir şey. Ama madem acelem var, seni daha fazla tutmayayım. İyi avlar, Charles!";
			link.l1 = "Sana da, Mösyö Fadey...";
			link.l1.go = "exit";
		break;
		
		case "vodka_5":
			dialog.text = "İşte duymak istediğim bu! Harika! Oturun, ayaklarınızı uzatın! Lütfen, Mösyö, ben votkayı getirirken kendinizi evinizde hissedin. Ah, dostlarla yapılan bu öğleden sonra buluşmalarını ne çok özlemişim! Bakın, votka buz gibi, kesinlikle beğeneceksiniz, nazdoroviya! Biraz turşu ve füme jambon da çıkarayım.";
			link.l1 = "...";
			link.l1.go = "vodka_6";
		break;
		
		case "vodka_6":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "BasTer_houseSp1";
			sld.startLocator = "bottle";
			sld = ItemsFromID("lcheer");
			sld.shown = true;
			sld.startLocation = "BasTer_houseSp1";
			sld.startLocator = "sit2";
			DoQuestReloadToLocation("BasTer_houseSp1", "sit", "sit2", "Sharlie_DrinkWithFadey");
			NextDiag.CurrentNode = "vodka_7";
		break;
		
		case "vodka_7":
			dialog.text = "";
			link.l1 = "Vay canına... Söylesene bana, Fadey, b-bu nasıl oluyor? Hık! Biz... i-ki şişe votka içtik... bu arada! - sen s-apsarıksın, bense... leş gibi sarhoşum. Nasıl oluyor bu, ha?";
			link.l1.go = "vodka_8";
		break;
		
		case "vodka_8":
			dialog.text = "Charles, dostum, rahatla. Tüm bunlarla kokarcanın ne ilgisi var? Az önce harika bir votka içtik. Biraz uyu, uyanınca kendini zinde ve dinç hissedeceksin. Başın bile ağrımayacak, hiçbir mahmurluk kalmayacak. Göreceksin.";
			link.l1 = "E-evet, votka... bu... bu votka gerçekten harika. Daha önce böyle bir şey içmemiştim.";
			link.l1.go = "vodka_9";
		break;
		
		case "vodka_9":
			dialog.text = "Ha! Doğru söyledin! O votka gizli tariflerle hazırlanır ve anavatanım Rusya'dan getirilir, orada bile herkes doğru düzgün yapamaz. Ben sadece en iyisini alırım! Şu anda seninle tattığımız gibi.";
			link.l1 = "A-ama söyle bana, Fadey: n-nasıl bu kadar çok içip de s-arhoş olmuyorsun? N-nasıl yapıyorsun bunu, ha? Ş-şu sırrını benimle paylaş. B-belki ileride işime yarar... Hık!";
			link.l1.go = "vodka_10";
		break;
		
		case "vodka_10":
			dialog.text = "Ha! Sen kendini benimle kıyaslayamazsın, genç Charles! Şuna bak, kamçı gibi zayıfsın. Üstelik ciddi içkiye de alışık değilsin, değil mi! Ama biz gerçek dostuz, bu yüzden sana içmenin ve altına kaçırmadan ayakta kalmanın birkaç sırrını paylaşacağım.";
			link.l1 = "L-lütfen y-yap... hık!";
			link.l1.go = "vodka_11";
		break;
		
		case "vodka_11":
			dialog.text = "Well, if you want to drink and not get instantly blasted, you must follow a few key rules. Most importantly, never drink on an empty stomach. Eat something hearty before the drinking session starts\nSecond, don't forget to eat something after every glass. Meat or fish is best, something nice and salty. Third, don't rinse your mouth with the vodka, swallow it at once\nAlso, having a small - no more than half a pint - shot before the main course will prepare your body for receiving serious doses of alcohol. Don't overdo this appetizer, otherwise the effect will be quite the opposite and you'll wreck yourself before setting sail\nFinally, disciplined training is key; drinking moderate amounts of rum or other types of alcohol on a regular basis will make you more resistant to them.";
			link.l1 = "Hm-mm... D-demek böyle yapılıyor! Kesinlikle... hık!.. bütün talimatlarını a-aklımda tutacağım, Fadey. T-teşekkür ederim. Ve ş-şimdi sanırım biraz uyusam iyi olacak, çünkü şu an pek iyi hissetmiyorum.";
			link.l1.go = "vodka_12";
		break;
		
		case "vodka_12":
			dialog.text = "Biraz dinlen, Charles. Güzel bir akşam geçirdik, seninle ben! Sana iyi avlar dilerim!";
			link.l1 = "D-d-do svidaniya, Fadey! Ben gidiyorum - hık! - Dilek Veren'e!";
			link.l1.go = "vodka_13";
		break;
		
		case "vodka_13":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = false;
			sld = ItemsFromID("lcheer");
			sld.shown = false;
			pchar.questTemp.CanDrink = true; // Шарль теперь знает секреты выпивки, это ему потом пригодится
			LAi_SetSitType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
			pchar.quest.Sharlie_TrialOver.over = "yes"; //снять таймер
			dialog.text = "Ne, gerçekten sana yardım edeceğimi mi söyledi?";
			link.l1 = "Pek sayılır. Eski dostunun kardeşine yardım eder misin? Dilenci gibi sadaka istemiyorum sonuçta. Bana para kazanabileceğim bir fırsat vermeni istiyorum.";
			link.l1.go = "trial_1";
		break;
		
		case "trial_late":
			dialog.text = "Ah Charles! Geç kaldın. Daha önce gelseydin, sana uygun bir iş bulabilirdim, ama şimdi - affet beni. Merak etme, şehirlerde dolaş, insanlarla sohbet et. Karayipler'de yapılacak çok iş var";
			link.l1 = "Anladım, bu üzücü. Hoşça kal!";
			link.l1.go = "trial_late_1";
		break;
		
		case "trial_late_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Trial");
		break;

		case "trial_1":
			dialog.text = "Hm. Hayır, seni geri çevirmem tabii ki. Birine balık vermek yerine, ona olta vermeli, öyle değil mi, Monsieur de Maure? Yani bir işe ihtiyacın var... Kolay iş. Tanıdığım biriyle konuşurum, seni ona tavsiye ederim. Gerisi ise işi ne kadar iyi yaptığına bağlı.";
			link.l1 = "Harika. Kiminle konuşmam gerekiyor?";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "Yarın dükkâna uğra. Gerard LeCroix adında bir adam orada seni bekliyor olacak. Sana bir iş verecek. Bu kolonide sadece yarın akşama kadar kalacak. Onunla bir an önce görüş ve işi düzgünce hallet. Beni zor durumda bırakma.";
			link.l1 = "Anlaştık. Teşekkür ederim, Fadey!";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			DialogExit();
			SetFunctionTimerCondition("Trial_StartLine", 0, 0, 1, false); // таймер
			pchar.questTemp.Trial = "start";
			AddQuestRecord("Trial", "1");
		break;
		// belamour legendary edition пиратская линейка -->
		case "Slaves":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "Ah, sana nasıl yardımcı olabilirim, dostum?";
			link.l1 = "Fadey, dinle, gerçekten kaçakçılardan elli köle almam gerekiyor. Sorun şu ki, onlar beni tanımıyor ve senin beni onlara tanıştırmanı istiyorum. Sensiz beni dinlemezler bile, üstelik bu çok önemli birinin hayat memat meselesi.";
			link.l1.go = "Slaves_1";
		break;
		
		case "Slaves_1":
			dialog.text = "Oh ho! İşini büyütüyorsun bakıyorum! Ne kârlı! Sana yardım edeceğim, sevgili dostum. Ama bildiğin gibi, bedavaya çalışmam. Satıcıyı iyi niyetine ikna edip zencileri satın alması için 150 altın dublon gerekecek ve elbette, benim titiz çabalarım için de ufak bir ek ödeme...";
			if(PCharDublonsTotal() >= 150)
			{
				link.l1 = "Başka türlüsünü beklemezdim, Mösyö Fadey! Altınınız burada.";
				link.l1.go = "Slaves_2";
			}
			else
			{
				link.l1 = "Hemen tefeciye gidiyorum! Bekleyin, Mösyö Fadey, hemen döneceğim!";
				link.l1.go = "exit";
				pchar.questTemp.Mtraxx.GiveMeSlaves = "FindGold"; 
			}
			
			link.l2 = "Fadey, galiba bir çözüm buldum ve artık zencilere ihtiyacım yok. Üzgünüm. Görüşürüz!";
			link.l2.go = "Slaves_3";
		break;
		
		case "Slaves_2":
			RemoveDublonsFromPCharTotal(150);
			pchar.questTemp.Mtraxx.GiveMeSlaves = "kapster";
			locations[FindLocation("Shore29")].DisableEncounters = true; //энкаутеры закрыть
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1 = "Hour";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1.start.hour = 22.00;
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1.finish.hour = 23.00;
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2 = "Timer";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l3 = "location";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l3.location = "Shore29";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.function = "MtraxxGiveMeSlavesKapsterInShore"; // прибыли
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1 = "Timer";
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.hour  = 23.0; // не пришли, значит гудбай
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.function = "MtraxxGiveMeSlavesKapsterInShoreLate"; // опоздание
			AddQuestRecord("Roger_3", "23");
			dialog.text = "Harika, dostum. Ama bu alışverişe gerçekten ihtiyacın olmadığı halde beni kandırmaya çalışıyorsan ve niyetlerin önemsizse, beni çok kızdırırsın. Bunu istemezsin. Yarın saat onda, gün batımında, Capster Plajı'nda senin için bir buluşma ayarlayacağım. Beni hayal kırıklığına uğratma.";
			link.l1 = "Endişelenecek bir şey yok, mallar için geri döneceğim.";
			link.l1.go = "exit";
		break;
		
		case "Slaves_3":
			DialogExit();
			AddQuestRecord("Roger_3", "22");
			pchar.questTemp.Mtraxx.GiveMeSlaves = "WithoutSlaves";
		break;
		
		case "pistols":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "Merhaba, merhaba! Söyle bakalım, iyi adam, seni bu mütevazı evime ne getirdi?";
			link.l1 = "Silahlara ihtiyacım var. Buradaki tüccarlar istediğim miktarı bulamıyorlar, ama sanırım sen bana yardımcı olabilirsin.";
			link.l1.go = "pistols_1";
		break;
		
		case "pistols_1":
			dialog.text = "Öncelikle, sevgili dostum, tam olarak neye ihtiyacın olduğunu söyle bana. Sonra sana yardımcı olup olamayacağımı söylerim.";
			link.l1 = "30 askerin tabancası, iki fitilli tüfek, onlar için 70 fişek ve 90 iyileştirici iksir istiyorum.";
			link.l1.go = "pistols_2";
		break;
		
		case "pistols_2":
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves"))
			{
				if(pchar.questTemp.Mtraxx.GiveMeSlaves == "Deal" || pchar.questTemp.Mtraxx.GiveMeSlaves == "WithoutSlaves")
				{
					dialog.text = pchar.name+", beni korkutuyorsun. Önce elli zenci, şimdi de silahlar. Bir köle isyanı mı başlatmaya çalışıyorsun, dostum?";
					link.l1 = "Çok dikkatlisiniz, Fadey. Daha önce de söylediğim gibi, tüm bunlar önemli bir kişiyi kurtarmak için gerekli. Merak etmeyin, onu İspanyolların elinden alacaklar, bu yüzden burada itibarınız zarar görmeyecek.";
					link.l1.go = "pistols_3";
					break;
				}
			}
			dialog.text = "Bunu duymak güzel. Yardımcı olabilirim.";
			link.l1 = "Bunu duyduğuma sevindim. Ne kadar?";
			link.l1.go = "pistols_4";
		break;
		
		case "pistols_3":
			dialog.text = "Açıklama yaptığın için memnunum. Ve eğer bu gerçekten İspanyollarla ilgiliyse, sana yardım edeceğim. Ama beni kandırdığın ortaya çıkarsa, çok kızarım.";
			link.l1 = "Bana biraz güven, Fadey. Ne kadar?";
			link.l1.go = "pistols_4";
		break;
		
		case "pistols_4":
			dialog.text = "Pekala, yani ... tabancalar ve birkaç tüfek, her biri için barut ve kurşun ... Bu yüzden ... İstediğiniz her şeyi tam olarak temin edeceğime söz veremem ama elimden gelen her şeyi yapacağım. Bu arada, 40.000 peso ya da isterseniz 75 dublon kapora almam gerekiyor.";
			if(PCharDublonsTotal() >= 75)
			{
				link.l1 = "Al paraları al, Fadey. Şu anda yanımda birkaç tane var.";
				link.l1.go = "pistols_4D";
			}
			if(sti(Pchar.money) >= 40000)
			{
				link.l2 = "Tüm doblonlarım bitti, peso al Fadey.";
				link.l2.go = "pistols_4P";
			}
			if(PCharDublonsTotal() < 75 || sti(Pchar.money) < 40000) // возможность найти без отказа
			{
				link.l3 = "Bankacıma konuşmam lazım. Hemen döneceğim!";
				link.l3.go = "exit";
				pchar.questTemp.Mtraxx.MagicBox = "FindMoney";
			}
			link.l4 = "Affedersin Fadey, ama bunu karşılayamam. Kendi başıma idare etmeye çalışacağım. Görüşürüz!";
			link.l4.go = "pistols_x";
		break;
		
		case "pistols_4D":
			SetFunctionTimerCondition("Mtraxx_MagicBoxready", 0, 0, 1, false);
			RemoveDublonsFromPCharTotal(75);
			pchar.questTemp.Mtraxx.MagicBox = "Tomorow";
            dialog.text = "Yarın gel, "+pchar.name+", ve ihtiyacın olan malzemeleri getireceğim.";
			link.l1 = "O halde yoluna çıkmayayım. Yarın görüşürüz!";
			link.l1.go = "exit";
		break;
		
		case "pistols_4P":
			AddMoneyToCharacter(pchar, -40000);
			SetFunctionTimerCondition("Mtraxx_MagicBoxready", 0, 0, 1, false);
            pchar.questTemp.Mtraxx.MagicBox = "Tomorow";
            dialog.text = "Yarın gel, "+pchar.name+", ve ihtiyacın olan malzemeleri getireceğim.";
			link.l1 = "O zaman yoluna çıkmayayım. Yarın görüşürüz!";
			link.l1.go = "exit";
		break;
		
		case "pistols_X":
			DialogExit();
			DeleteAttribute(pchar,"questTemp.Mtraxx.MagicBox");
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
		break;
		
		case "pistols_5":
			dialog.text = "Bak evlat, bu kadar kısa sürede istediğin her şeyi bulduğum için kendini şanslı saymalısın. Minnettar olmalısın! Şimdi, son ödeme. Bana kapora olarak verdiğin kadarını daha ver, silahlarını al.";
			if(PCharDublonsTotal() >= 75)
			{
				link.l1 = "Al yetmiş beş doblon. Adamlarım silahları gemime getirecek. Sensiz ne yapardım, Fadey? Bana ne kadar çok yardım ettiğinin farkında bile değilsin!";
				link.l1.go = "pistols_5D";
			}
			if(sti(Pchar.money) >= 40000)
			{
				link.l2 = "Al kırk bin peso. Adamlarım silahları gemime getirecek. Sensiz ne yapardım, Fadey? Bana ne kadar çok yardım ettiğinin farkında bile değilsin!";
				link.l2.go = "pistols_5P";
			}
			if(PCharDublonsTotal() < 75 || sti(Pchar.money) < 40000) // возможность найти без отказа
			{
				link.l3 = "Vay canına, parayı nasıl unuttum ben? Hemen dönerim.";
				link.l3.go = "exit";
				pchar.questTemp.Mtraxx.MagicBox = "FindMoney";
			}
			link.l4 = "Excuse me, Fadey, I'm broke. Keep the deposit; I hope it will be enough to cover your expenses for this deal, and I'll try to manage on my own. See you!";
			link.l4.go = "pistols_x";
		break;
		
		case "pistols_5D":
			Log_Info("Fadey's weapons are loaded on the ship");
			RemoveDublonsFromPCharTotal(75);
			pchar.questTemp.Mtraxx.MagicBox = "Full";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
            dialog.text = "Muhtaç olanlara yardım etmek bir onurdur. Para ödeyenlere yardım etmek ise bir zevktir. Bir dahaki sefere Basse-Terre’de olursan, mutlaka uğrayıp selam ver.";
			link.l1 = "Bu saçmalık – Basse-Terre'de olup da dostum Fadey'i görmemek! Bir dahaki sefere!";
			link.l1.go = "exit";
		break;
		
		case "pistols_5P":
			Log_Info("Fadey's weapons are loaded on the ship");
			AddMoneyToCharacter(pchar, -40000);
			pchar.questTemp.Mtraxx.MagicBox = "Full";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
            dialog.text = "İhtiyacı olana yardım etmek bir onurdur. Parasını verene yardım etmek ise bir zevk. Bir dahaki sefere Basse-Terre’de olursan, mutlaka uğra ve selam ver.";
			link.l1 = "Bu saçmalık – Basse-Terre'deyim ve dostum Fadey'i görmeden gidiyorum! Bir dahaki sefere!";
			link.l1.go = "exit";
		break;
		// <-- legendary edition
		
		//--> Дикая Роза
		case "WildRose_Fadey_4":
			dialog.text = "Ne oyunlar başlattın, "+pchar.name+"! Niyetin soylu olduğuna şüphe yok, fakat bu mümkün mü? Yirmi yıl bir insana her şeyi yapabilir...";
			link.l1 = "Haklısın, Fadey. Ama çok zaman ve emek harcadık, uzun bir yol geldik — ve neredeyse amacımıza ulaştık. Onun hakkında neredeyse her şeyi öğrendik: adını, Majestelerinin Kraliyet Donanması'ndaki hizmetini, görev yaptığı geminin adını... ve biyografisine dair bazı diğer ayrıntıları. İz, Haziran 1638'de Cape Catoche açıklarında meydana gelen bir gemi enkazında sona eriyor.";
			link.l1.go = "WildRose_Fadey_5";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap5_Fadey");
		break;

		case "WildRose_Fadey_5":
			dialog.text = "Catoche mi? Ah, iyi adamım, beni oraya sopayla bile sürükleyemezsin — o taraflarda lanetli vahşiler sürüler halinde dolaşır. Eğer oraya düştüyse ve denizde boğulmadıysa, Allah'ın günü gibi açık ki, o lanet yerliler onu afiyetle mideye indirmiştir...";
			link.l1 = "Bu adamın kazadan sağ çıktığına ve sonrasında Küba'ya ulaşmayı başardığına dair elimizde kanıt var. Belki orada hayatını kaybetmiştir, ama duyduğumuza göre engizitörlerin elinden kurtulacak kadar kurnazmış. Küba'da kalmış olması pek olası değil — büyük ihtimalle Takımadalar'daki yerleşimlerden birine yerleşti...";
			link.l1.go = "WildRose_Fadey_6";
		break;

		case "WildRose_Fadey_6":
			dialog.text = "Bu dünyada pek çok mucize olur, dostum, her şey mümkün. Ama yine de bana bunların hepsini neden anlattığını hâlâ anlamıyorum.";
			link.l1 = ""+npchar.name+", bazı valilerden daha çok bağlantınız var. Eminim elinizin altında basit işleri halledebilecek yetenekli adamlarınız vardır...";
			link.l1.go = "WildRose_Fadey_7_1";
			link.l2 = ""+npchar.name+", saygın ve etkili bir adamsınız. Yüksek çevrelerde dolaşıyor, önemli bağlantılarınız var. Eminim ticari çıkarlarınız Guadeloupe'un çok ötesine uzanıyor. Bütün bunları tek başınıza yapamayacağınıza göre, elbette güvenilir adamlarınız ve çok karmaşık olmayan işleri halledebilecek akıllı yardımcılarınız vardır...";
			link.l2.go = "WildRose_Fadey_7_2";
		break;

		case "WildRose_Fadey_7_1":
			dialog.text = "Sen zeki ve sezgili bir adamsın, "+pchar.name+". Gerçekten de, bunu daha önce de duydunuz. Evet, yetenekli ve işinin ehli adamlarım var, doğru söylüyorsunuz. Ama bana açıkça söyleyin — onlardan ne yapmalarını istiyorsunuz.";
			link.l1 = "Senden onları Takımadaların birkaç kolonisine göndermeni isteyeceğim, aradığımız adam hakkında bir şeyler öğrenmeye çalışsınlar. Belki birileri ondan haberdardır, hatta şahsen tanıyan bile çıkabilir. Masrafları elbette tamamen ben karşılayacağım. "+npchar.name+", bu Mary için gerçekten çok önemli, ve başka başvuracak kimsemiz yok.";
			link.l1.go = "WildRose_Fadey_8";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Fadey_7_2":
			dialog.text = "Sen zeki ve sezgili bir adamsın, "+pchar.name+" . Evet, bunu daha önce de duydun. Gerçekten de yetenekli ve işinin ehli adamlarım var, doğru söylüyorsun. Ama bana açıkça söyle — onlardan ne yapmalarını istiyorsun.";
			link.l1 = "Senden onları Takımadalar'daki birkaç kolonilere göndermeni isteyeceğim, aradığımız adam hakkında bir şeyler öğrenmeye çalışsınlar. Belki birileri ondan haberdardır, hatta şahsen tanıyan bile çıkabilir. Masrafları tamamen ben karşılayacağım, elbette. "+npchar.name+", bu Mary için gerçekten çok önemli, ve başka başvuracak kimsemiz yok.";
			link.l1.go = "WildRose_Fadey_8";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Fadey_8":
			dialog.text = "Böyle iyi bir dostu geri çevirebilir miyim, "+pchar.name+"? Özellikle de bu kutsal meseleye para harcamaya hazır olduğuna göre. O halde, bulmak istediğin adamın adını söyle bana.";
			link.l1 = "İsmi konusunda emin değilim, ama sanırım adı Rupert Casper ya da Joshua Northwood olabilir.";
			link.l1.go = "WildRose_Fadey_9";
		break;

		case "WildRose_Fadey_9":
			dialog.text = "Pekâlâ, dediğiniz isimlerle geçtiyse o adamı bulacağız...";
			link.l1 = "Mükemmel, "+npchar.name+". Hizmetlerinizin karşılığında ödemeyi konuşalım mı?";
			link.l1.go = "WildRose_Fadey_10";
		break;

		case "WildRose_Fadey_10":
			dialog.text = "Hoş olmayan bir iş, ama maalesef gerekli.";
			link.l1 = "O halde başlayalım. İspanyolların ya da Hollandalıların arasına karışmaya cesaret edeceğini sanmam. Antigua'da başını belaya sokmuş, orada aramanın anlamı yok, muhtemelen Barbados'ta da yok. Batı Anakarası'na, İspanyollar kovulduktan sonra Jamaika'ya, Fransız kolonilerine ya da belki de korsan yerleşimlerine yerleşmiş olabilir.";
			link.l1.go = "WildRose_Fadey_11";
		break;
		
				case "WildRose_Fadey_11":
			dialog.text = "Açıkça söyleyeyim, sevgili dostum: Basse-Terre'de yaşadığım bunca zaman boyunca, bu isimlerden hiçbiriyle anılan bir centilmen duymadım. Yani burada aramanıza gerek yok. Martinique ve Saint Christopher'da tanıdığım İngiliz beyefendiler var, ama o da onların arasında değil.";
			link.l1 = "O zaman arama alanı oldukça daralıyor.";
			link.l1.go = "WildRose_Fadey_12";
		break;

		case "WildRose_Fadey_12":
			dialog.text = "Elbette Tortuga'yı kontrol etmeliyiz — aynı adamı La Vega, Puerto Principe ve Port-au-Prince'e de göndereceğim. Yetenekli adamlarımı Belize ve Blueveld'e, ayrıca Jamaika ve Isla Tesoro'ya da yollayacağım.";
			link.l1 = "Bütün bunların bana maliyeti ne olacak?";
			link.l1.go = "WildRose_Fadey_13";
		break;

		case "WildRose_Fadey_13":
			dialog.text = "Bunlar bilgili ve çalışkan adamlardır, bu yüzden her biri için yüz elli dublon ödeyeceksiniz. Tortuga ve Hispaniola'ya, ayrıca Küba'ya göndereceğim elçiye ise fazladan ödül verilmeli — elli altın sikke daha. Sonuçta, dört yerleşim birini sayılmaz.";
			link.l1 = "Yani bu 800 doblon ediyor... Hesapları kapatmaya geçelim mi?";
			link.l1.go = "WildRose_Fadey_14";
		break;

		case "WildRose_Fadey_14":
			dialog.text = "Pekâlâ, neden vakit kaybedelim? Gerekli meblağ yanında mı, iyi adam?";
			if (PCharDublonsTotal() >= 800)
			{
				link.l1 = "Elbette. Al, buyur.";
				link.l1.go = "WildRose_Fadey_14_pay";
			}
			else
			{
				link.l1 = "Hmm... Tüm parayı yanımda bulundurmuyorum.";
				link.l1.go = "WildRose_Fadey_14_nopay";
			}
		break;

		case "WildRose_Fadey_14_pay":
			RemoveDublonsFromPCharTotal(800);
			dialog.text = "Harika, sevgili dostum! Hemen ajanlarıma yazılı emirler göndereceğim ve işe koyulacaklar. O tarafa giden gemiler bulmaları gerekecek, bu da biraz zaman alacak. Yolculuğun kendisi ise rüzgarın gücüne bağlı, o da Rabbimizin elinde. Ama anladığım kadarıyla adamlarım bir ay içinde dönmüş olmalı.";
			link.l1 = "Yani bir ay sonra buluşacağız, "+npchar.name+". Tekrar teşekkür ederim. Bana çok yardımcı oldun. O zamana kadar!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_1");
			DeleteAttribute(pchar, "questTemp.WildRose_Etap5_Fadey_2");
		break;

		case "WildRose_Fadey_14_nopay":
			dialog.text = "Anlıyorum, "+pchar.name+", miktar oldukça yüksek. Parayı bulduğunda seni evimde bekliyor olacağım.";
			link.l1 = "Yakında döneceğim.";
			link.l1.go = "exit";
			pchar.questTemp.WildRose_Etap5_Fadey_2 = true;
		break;

		case "WildRose_Fadey_return":
			dialog.text = "Senin meseleni hatırlıyorum, sevgili dostum. Sanırım sekiz yüz doblonu topladın?";
			if (PCharDublonsTotal() >= 800)
			{
				link.l21 = "Buyurun, Mösyö Fadey! Altınınız burada. Her şey anlaştığımız gibi.";
				link.l21.go = "WildRose_Fadey_14_pay";
			}
			link.l31 = "Gerekli miktarı toplamaya devam ediyorum, ama merak etme — fazla gecikmeyeceğim.";
			link.l31.go = "exit";
		break;

		case "WildRose_Fadey_16":
			dialog.text = "Başardık, dostum — hem de nasıl başardık! Adamlarımın hepsi ellerinde tek bir şeyle döndü. Belize’ye gönderdiğim Jerome Sauvernier ise dönmedi — ama haber yolladı. Üstelik senin için iyi haberlerle.";
			link.l1 = "Sana bir mektup mu gönderdi? Okuyabilir miyiz?";
			link.l1.go = "WildRose_Fadey_17";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.WildRose_Etap5_Fadey_3");
		break;

		case "WildRose_Fadey_17":
			dialog.text = "Elbette, "+pchar.name+". Bunu özellikle senin için sakladım, okumak isteyeceğini biliyordum. Lütfen, dostum.";
			link.l1 = "Teşekkürler, şimdi okuyacağız.";
			link.l1.go = "WildRose_Fadey_18";
			AddQuestRecordInfo("WildRose_Records_6", "1");
		break;

		case "WildRose_Fadey_18":
			dialog.text = "Uzun zamandır yüzünde böyle bir gülümseme görmemiştim, iyi adam!";
			link.l1 = "Şaşılacak bir şey yok, "+npchar.name+"! Çok bekledik! Ama biliyor musun, başaracağımıza inandık! Bunun bu kadar önemli bir parçası olduğun için sana nasıl teşekkür edeceğimi bilmiyorum.";
			link.l1.go = "WildRose_Fadey_19";
		break;

		case "WildRose_Fadey_19":
			dialog.text = "Ah, bırak artık, cesur dostum! Sen benim arkadaşımsın, arkadaşlar birbirine yardım etmeli. Yakında bana dön — eminim Mösyö Jerome hızla iyileşip ilk gemiye binecek...";
			link.l1 = "Bence işleri hızlandıracağız. Belize'ye kendimiz gidip ajanınızla konuşacağız. Tekrar teşekkürler, "+npchar.name+". Bizim için neler yaptığını hayal bile edemezsin! Tekrar görüşene dek!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_5");
		break;
		//<-- Дикая Роза
		
		//--> LoyaltyPack
		case "LoyaltyPack_Fadey_1":
			dialog.text = "Senin geminde görev yapan sevgili dostum Alonso Pimentel mi? Ha! Elbette. Gemin her limana yanaştığında, o iyi adam mutlaka bir içki için uğrar. Bana çok az dost kaldı, "+pchar.name+". Her birini ayrı ayrı değerli buluyorum.";
			link.l1 = "Alonso bana senin savaş maceralarınla ilgili inanılmaz hikayeler anlattı. Hatta bana senin fişekliğini bile verdi.";
			link.l1.go = "LoyaltyPack_Fadey_2";
			DelLandQuestMark(npchar);
		break;

		case "LoyaltyPack_Fadey_2":
			dialog.text = "Umarım ve inanırım ki en dikkat çekici olanları kendine saklamıştır. Ama Alonso dostluğumuzu seninle paylaştığına göre, ben de sana karşı bir merak duymaktayım. Bak şimdi!";
			link.l1 = "Bu... zırh mı?";
			link.l1.go = "LoyaltyPack_Fadey_3";
		break;

		case "LoyaltyPack_Fadey_3":
			dialog.text = "Ah, dostum. O lanetli savaşta giydiğim ayna zırhımdan geriye kalan tek şey bu. Sonra, Smolensk yakınlarında, bir keresinde\n"+" Her ne olursa olsun, bu halde bile muhteşem görünüyor ve koruması da harika. Ama artık bana hiç uymuyor!";
			link.l1 = "Egzotik görünüyor... buralar için bile. Muhteşem bir hediye, Fadey. Teşekkür ederim.";
			link.l1.go = "LoyaltyPack_Fadey_4";
		break;
		
		case "LoyaltyPack_Fadey_4":
			dialog.text = "Senin için, dostum, sadece bin doblon.";
			if (PCharDublonsTotal() >= 600)
			{
				if (GetSummonSkillFromName(pchar, SKILL_Commerce) >= 60)
				{
					link.l1 = "İzin ver de seni düzelteyim, sevgili Fadey. Bin doblon tam bir zırh takımı için olurdu. Ama sadece göğüslük için mi?";
					link.l1.go = "LoyaltyPack_Fadey_5";
					Notification_Skill(true, 60, SKILL_COMMERCE);
				}
				else if (PCharDublonsTotal() >= 1000)
				{
					link.l1 = "Seninle Alonso'nun iyi anlaşmasına şaşmamalı. Al altınını.";
					link.l1.go = "LoyaltyPack_Fadey_1000";
					Notification_Skill(false, 60, SKILL_COMMERCE);
				}
			}
			link.l2 = "Ha! Az kalsın kandırıyordun beni, Fadey! Belki başka bir zaman.";
			link.l2.go = "LoyaltyPack_Fadey_MoneyLater";
		break;
		
		case "LoyaltyPack_Fadey_MoneyLater":
			dialog.text = "Elbette, aceleye gerek yok. Aynalı zırhım seni her zaman bekliyor olacak.";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.LoyaltyPack.Fadey = "money";
		break;
		
		case "LoyaltyPack_Fadey_5":
			dialog.text = "Oh, sen akıllı birisin! Peki öyleyse, altı yüz altın karşılığında ondan vazgeçerim.";
			link.l1 = "Seninle Alonso'nun iyi anlaşmasına şaşmamalı. Al altınlarını.";
			link.l1.go = "LoyaltyPack_Fadey_600";
		break;
		
		case "LoyaltyPack_Fadey_1000":
			dialog.text = "Güzel bir anlaşma. Size teşekkür ederim ve aynalı zırhımı güvenilir ellere emanet ediyorum. Ve Alonso'ya da dikkat edin, kaptan.";
			link.l1 = "Burada kime kim bakıyor, belli değil...";
			link.l1.go = "LoyaltyPack_Fadey_end";
			RemoveDublonsFromPCharTotal(1000);
			GiveItem2Character(PChar, "cirass11");
		break;
		
		case "LoyaltyPack_Fadey_600":
			dialog.text = "Güzel bir anlaşma. Size teşekkür ederim ve aynalı zırhımı layık ellere emanet ediyorum. Alonso'ya da göz kulak olun, kaptan.";
			link.l1 = "Burada kime kim bakıyor acaba...";
			link.l1.go = "LoyaltyPack_Fadey_end";
			RemoveDublonsFromPCharTotal(600);
			GiveItem2Character(PChar, "cirass11");
		break;
		
		case "LoyaltyPack_Fadey_end":
			DialogExit();
			AddDialogExitQuestFunction("LoyaltyPack_Fadey_DlgExit");
		break;
		//<-- LoyaltyPack

		case "guardoftruth":
			dialog.text = "Eh, kim inanır ki senin iş için geldiğine, dostum! Ne yazık ki şu an sana ikram edecek votkam kalmadı, hepsini ben içtim. Söyle bakalım, bu sefer başın ne belada.";
			link.l1 = "Bir korsan, günahlarının affı için yerel bir kiliseye lazurit taşlı altın bir göğüs haçı sunmuş. Eşsiz ve değerli bir parça. Sorun şu ki, bu haç başka bir kiliseden çalınmış. Üstelik soygun sırasında bir rahip de öldürülmüş.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Ey lekesiz Tanrıdoğuran! Yok artık!";
			link.l1 = "Evet. Soyulan cemaatin temsilcisiyim ve haçı asıl sahiplerine geri vermeye çalışıyorum.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Asil bir davranış, hem de çok dindarca. Yüce Tanrı'nın gözüne girmeye mi çalışıyorsun?";
			link.l1 = "Ama buradaki rahip, ona ne anlattıysam da haçı bana geri vermeyi reddediyor. Anlamıyorum. Bir insan nasıl olur da, masum bir adamın kanıyla lekelenmiş çalıntı bir haçı, Tanrı'nın evine sakince koyabilir? Bu düpedüz küfür!";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Şimdi, teknik olarak kutsanmış her kadehte Masum İsa'nın kanı vardır... ama konuyu dağıtmayayım. Sanırım bana yardım etmemi istiyorsun?";
			link.l1 = "Evet, öylesiniz! Basse-Terre'de oldukça etkilisiniz. Size büyük saygı duyuluyor, belki de rahip uyarılarınızı dikkate alır.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = ""+pchar.name+", bu çalınan haçın hikayesini papazımıza tam olarak anlattın mı?";
			link.l1 = "Elbette! Dini duygularına, Hristiyan dayanışmasına, Tanrı aşkına o lanet vicdanına bile seslendim, ama kulaklarını tıkadı.";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Hm... Onu ikna etmek için başka yollar denedin mi?";
			link.l1 = "Rüşvet mi vermemi istiyorsun? Bir rahibe rüşvet vermem. Eğer bir bankacı, bir tüccar ya da hatta bir vali olsaydı, meseleyi öyle çözmeyi denerdim, ama bir rahibe asla!";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "My dear naive friend, if the priest's ears truly are closed to proclamations of conscience, then surely his hands will be open to gold... Or perhaps the other way around. I'll help you; I think that keeping such a tainted treasure here is bound to cause greater trouble down the road. However, it will require certain expenses."link.l1 = "Neden şaşırmadım ki? Bu sefer ne kadar?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Yarın uğra, "+pchar.name+", henüz fiyatı söyleyemem. Ama o çalınan haçı alacağına emin olabilirsin.";
			link.l1 = "Pekâlâ Fadey, o zaman seni daha fazla rahatsız etmeyeceğim. Yarın görüşürüz!";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			DialogExit();
			pchar.questTemp.Guardoftruth.Baster_church = "wait";
			SetFunctionTimerCondition("GuardOT_FadeyTimer", 0, 0, 1, false);
			AddQuestRecord("Guardoftruth", "29");
		break;
		
		case "guardoftruth_9":
			dialog.text = "Söz verdiğim gibi, haçı getirdim. Ayrıntılara gelince... boşver onları... tüm saçmalıklar Kıymetli Kurtarıcımızın dökülen kanıyla affedildi";
			link.l1 = "Sana ne kadar borcum var?";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "İki yüz elli doblon. Masraflarım için, tabii ki, haklı yardımıma küçük bir ek ödeme de memnuniyetle karşılanır...";
			if(PCharDublonsTotal() >= 250) // belamour legendary edition
			{
				link.l1 = "Buyurun, Monsieur Fadey. Altınınız burada.";
				link.l1.go = "guardoftruth_11";
			}
			else
			{
				link.l1 = "Kaptan kamarama gidip altınları almalıyım. Hemen dönerim.";
				link.l1.go = "exit";
				npchar.quest.utensil = "true";
			}
		break;
		
		case "guardoftruth_11":
			DeleteAttribute(npchar, "quest.utensil");
			dialog.text = "Pekala. İşte çalınan haç.";
			link.l1 = "Teşekkür ederim, Fadey. Benim için ne kadar çok şey yaptığını hayal bile edemezsin!";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			RemoveDublonsFromPCharTotal(250); // belamour legendary edition
			GiveItem2Character(pchar, "jewelry34");
			//Log_Info("You've received a golden cross with lazurite");
			PlaySound("interface\important_item.wav");
			dialog.text = "Yardımsever – ve daha da önemlisi – cömert bir dosta her zaman yardım etmekten mutluluk duyarım. Daha sık uğra. Belki anavatandan votka gelince beraber içeriz.";
			link.l1 = "Memnuniyetle!";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Guardoftruth.Baster_church");
			AddQuestRecord("Guardoftruth", "30");
		break;
		
		case "guardoftruth_14":
			dialog.text = "Vay canına, deniz seni henüz yutmadı demek! Anlat bakalım. Bu sefer hangi talihsizlikler seni kapıma getirdi?";
			link.l1 = "Başlarına talihsizlik mi demeli, bilmiyorum ama işte buradayım. Fadey, tanıştığımız ilk gün bana nadir bir hançer verdin, Şefin Pençesi. Şimdi biliyorum ki o hançer daha önce Archibald Calhoun adında bir adama aitti. Lütfen, bu adam hakkında bildiklerini anlat.";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "Senden hiçbir şey gizlenemez, "+pchar.name+". Her şeyi tıpkı kardeşin gibi hemen anlıyorsun. Evet, bu hançeri Calhoun'dan zar oyununda kazandım. Kim mi o? Ben de bilmiyorum. Tesadüfen meyhanede karşılaştık, sohbet ettik, birkaç kadeh içtik, sonra da geçmişinden gelen bazı günahların onu nasıl ezdiğini anlatmaya başladı...";
			link.l1 = "Sen onun günah çıkartıcısı mısın? Hangi günahlar?";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			dialog.text = "Archibald, Engizisyon yüzünden işkenceyle öldürülen bir adamın ve onun yüzünden ölen diğer masumların anısıyla lanetlenmiş gibiydi. Sürekli kendine Yahuda diyordu, Tanrı'nın onu günahları için cezalandırdığını ve Engizisyon'un peşine düştüğünü söylüyordu. Hatta İspanyol engizitörü Vincento'nun bizzat onu öldürmek istediğini ve Karayipler boyunca peşine paralı askerler gönderdiğini anlattı. Sonra alkol galip geldi ve bu eski hançer için kumar oynadık.";
			link.l1 = "Hepsi bu mu? Onu bir daha hiç görmedin mi?";
			link.l1.go = "guardoftruth_17";
		break;
		
		case "guardoftruth_17":
			dialog.text = "Tabii ki hayır, artık öldü. Bir grup sefil korsan onun fluytunu Davy Jones'un Sandığı'na, tüm mürettebatı ise Mictlantecuhtli'ye gönderdi. Doğrusunu söylemek gerekirse, söylentilere göre onlara korsan kılığında profesyoneller saldırmış... Engizisyon ajanları. Derler ki, Peder Vincento her zaman adamını bulur.";
			link.l1 = "Archibald Calhoun hayatta. Onu kısa bir süre önce, William Paterson adında biriyle birlikte gördüm. Ona birinci zabit olarak hizmet ediyor.";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "Oh ho, ne sürpriz ama! Archibald en azından Kaptan Paterson'ın kanatları altında biraz nefes alabilir. Yanında iyi insanlar var. İspanyollar Paterson'dan veba gibi korkar. Paterson'ın korumasındayken Archibald'a karşı bir şey planlamaya cesaret edemezler.";
			link.l1 = "Paterson'ı tanıyor musun?";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "William Paterson'ı kim bilmez ki!? O da senin gibi Karayiplere yeni gelmiş biri. Ve senin gibi, şimdiden kendine büyük bir ün kazandırdı. Bay Paterson, Albay Fox'un en yakın dostudur ve bizzat Lord Windsor'la, yani Karayiplerdeki tüm İngiliz kolonilerinin Genel Valisiyle arası çok iyidir. Sık sık Jamaika'daki Port Royal'de valinin sarayına uğrar.";
			link.l1 = "Anladım. Bilgi için teşekkürler, Fadey!";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "Ah, lafı bile olmaz dostum. Bir ara uğra bana! İyi avlar!";
			link.l1 = "Kesinlikle!";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			DialogExit();
			pchar.questTemp.Guardoftruth.Archy = "portroyal";
			AddQuestRecord("Guardoftruth", "62");
			// эскадру Патерсона - в Порт-Рояль
			Group_SetAddress("Willy_group", "Jamaica", "quest_ships", "quest_ship_1");
			pchar.quest.GuardOT_jamaica.win_condition.l1 = "location";
			pchar.quest.GuardOT_jamaica.win_condition.l1.location = "Jamaica";
			pchar.quest.GuardOT_jamaica.function = "GuardOT_PortRoyalArrive";
		break;
		
		// персидские клинки
		case "persian":
			dialog.text = "Hadi bakalım, "+pchar.name+"... Evet! İşte onlardan biri! Aferin sana, günümü güzelleştirdin! Nerede buldun bunu?";
			link.l1 = "Önemli olan bu değil. Asıl önemli olan, onun tekrar sana geri dönmüş olması.";
			link.l1.go = "persian_1";
		break;
		
		case "persian_1":
			dialog.text = "Sana kapsamlı araştırman için iyi bir ödeme yapacağım. Üç yüz altın doblon, zahmetine yeterli bir ödül olmalı...";
			link.l1 = "Beni daha önce benden kopardığın doblonlarla mı ödüyorsun? Gerçi, elbette, onları geri çevirecek değilim. İşte senin şemşirin.";
			link.l1.go = "persian_2";
		break;
		
		case "persian_2":
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Persian = "one";
			dialog.text = "Teşekkürler dostum! Hem kılıç hem de alaycı sözlerin için sağ ol. Yaşından daha bilgesin, "+pchar.name+", ama dostluğun insani bağı altının değerinden üstündür. Altın demişken, - sana borcumu tamamen ödeyeceğim. Al, işte doblonların.";
			link.l1 = "Teşekkürler.";
			link.l1.go = "persian_3";
		break;
		
		case "persian_3":
			TakeNItems(pchar, "gold_dublon", 300);
			//Log_Info("You've received 300 doubloons");
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
			dialog.text = "Ve dostluk bağlarından söz etmişken, özellikle seninkiyle benimki arasındaki, "+pchar.name+". Sizin çok ilginizi çekecek bir şeyim var.";
			link.l1 = "Dur tahmin edeyim, yine votka mı?";
			link.l1.go = "persian_4";
		break;
		
		case "persian_4":
			dialog.text = "Ha! Votka iyidir, ama ülkem sadece bununla ünlü değil. Sadece Rusya'nın ürettiği özel bir malzeme var. Bu malzemeyi memleketteki bağlantılarımdan buraya getirtiyorum, ticaret için. Her kaptan bunu ister, çünkü her gemiyi iyileştirir. Kenevir halatlardan bahsediyorum\nHem neme hem deniz tuzuna dayanıklı halatlar. Derler ki, donanım için en iyi malzeme budur\nHer ay, Reval'den bana belli bir miktar gönderilir. Genelde, her ayın ortasında depomda birkaç yüz top olur. Yani, "+pchar.name+", I am offering to sell you a batch of fifty coils. Ten doubloons a coil\nI have only two terms: first, I will keep your ropes until the 20th of every month; second, you can buy only the whole batch. Fifty coils for five hundred doubloons. Confidentially speaking, "+pchar.name+", they say that there are certain places where you can resell those ropes for a much greater price, but what do I know!\I am completely satisfied with the current state of my operation and don't need to find resellers myself. If you find a good merchant, you can turn a fine profit.";
			link.l1 = "Anladım. Harika bir teklif bu, Fadey! Sanırım sunduğun bu fırsatı değerlendireceğim. Yani, her ayın yirminci günü, elli parça için beş yüz dublon mu?";
			link.l1.go = "persian_5";
		break;
		
		case "persian_5":
			AddQuestRecordInfo("Unique_Goods", "2");
			dialog.text = "Evet. Git ve satın aldığını al. Ama bekle, bekle, sevgili dostum! Bana gerçek bir iyilikle geri verdiğin bu şemşir dışında, iki tane daha vardı. Ne olur, lütfen, eğer onları bulursan bana geri getir, karşılığında sana fazlasıyla adil bir ücret ödeyeceğim.";
			link.l1 = "Elbette, Fadey. Eğer onları bulursam, geri getireceğim.";
			link.l1.go = "exit";
			if (CheckNCountPersian() > 0)
			{
				link.l2 = "Sana iyi bir haberim var. Bir tane daha Fars şemşiri buldum.";
				link.l2.go = "persian_6";
			}
			npchar.quest.ropes = "true";
		break;
		
		case "persian_6":
			dialog.text = "Ah, canım dostum! Gözyaşlarımı sildin resmen! Bir bakayım... Ah! İşte bu, kıymetli şemşirim! Al, söz verdiğim gibi, işte sana bunun için üç yüz dublon ödül.";
			link.l1 = "Spasibo!";
			link.l1.go = "persian_7";
		break;
		
		case "persian_7":
			TakeNItems(pchar, "gold_dublon", 300);
			//Log_Info("You've received 300 doubloons");
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Persian = "two";
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
			dialog.text = "Lütfen minnettarlığımı ve mütevazı ama çok faydalı bir hediyemi kabul et. Benim ihtiyacım yok, ama sen ya da geminin marangozu için oldukça işe yarayacaktır\nBak, şu güzel yüzüğe bak! Artık senin. Ama bu sıradan bir yüzük değil, büyülü bir yüzük. Marangozlukta ve gemi tamirinde yardımcı olur. Pek çok usta böyle bir şey isterdi ama ben onu özel bir gün için saklamıştım. Al dostum, umarım yükünü hafifletir!";
			link.l1 = "Gerçekten ilginç eşyalar taşıyorsun. Teşekkürler, Fadey!";
			link.l1.go = "persian_8";
		break;
		
		case "persian_8":
			GiveItem2Character(pchar, "talisman7");
			//Log_Info("You've received the Scarab amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Kayıp koleksiyonumdan geriye sadece bir şemşir kaldı. Onu bulmanı sana emanet ediyorum, "+pchar.name+", ve şansına bağlı. Eğer bulursan, hiç vakit kaybetmeden bana geri dön.";
			link.l1 = "Kesinlikle! Yakında görüşürüz...";
			link.l1.go = "exit";
			if (CheckNCountPersian() > 0)
			{
				link.l2 = "Neden acele edeyim? Kılıç benimle.";
				link.l2.go = "persian_9";
			}
		break;
		
		case "persian_9":
			dialog.text = "İyi ki senden yardım istemişim, "+pchar.name+". Sen tam bir mucizesin, dostum! Göster bana... Ohooo! Bu, bu o! Sevgilim! Güzellik! Bin teşekkür, iyi adam, sana minnettarım! Al, işte paran. Dört yüz dublon, bir kuruş eksik değil! Cimrilik etmeyeceğim.";
			link.l1 = "Teşekkür ederim, Fadey. Yardım etmek benim için bir zevk.";
			link.l1.go = "persian_10";
		break;
		
		case "persian_10":
			TakeNItems(pchar, "gold_dublon", 400);
			//Log_Info("You've received 400 doubloons");
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 250);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 3);
			Achievment_Set("ach_65");
			dialog.text = "Kılıç koleksiyonum yeniden tamamen bir arada! Artık kimse onu benden çalmaya cesaret edemez, buna emin olacağım! Senin için çok özel bir ödülüm var, iyi adam. İki hafta içinde bir tüccar bana Avrupa'dan mükemmel bir eskrim zırhı getirecek. Bir soylu tarafından sipariş edilmiş, oldukça eşsiz bir zırh parçası\nEğer istersen, yalnızca yedi yüz altın doblona satın alabilirsin. Soyluya, zırhın yolda kaybolduğunu söyleyeceğim.";
			link.l1 = "Bu zırhın nesi bu kadar iyi?";
			link.l1.go = "persian_11";
		break;
		
		case "persian_11":
			dialog.text = "Çok rahat ve dayanıklı, üstelik demir zırh kadar iyi koruyor. Üstelik, harika görünüyor! Birkaç hafta sonra tekrar gel, bir bak istersen. Ama bir aydan fazla gecikirsen, onu asıl sahibine satarım.";
			link.l1 = "Anlaştık. İki hafta sonra evine uğrarım.";
			link.l1.go = "persian_12";
		break;
		
		case "persian_12":
			DialogExit();
			pchar.questTemp.Persian = "time";
			SetFunctionTimerCondition("Persian_CirassLamport", 0, 0, 14, false); // таймер
		break;
		
		case "persian_13":
			dialog.text = "Evet, çoktan teslim edildi ve seni bekliyor. Parayı getirdin mi?";
			if(PCharDublonsTotal() >= 700) // belamour legendary edition
			{
				link.l1 = "Evet. İşte yedi yüz dublon.";
				link.l1.go = "persian_14";
			}
			else
			{
				link.l1 = "Lanet olsun. Parayı gemide unuttum. Hemen getiririm!";
				link.l1.go = "exit";
			}
		break;
		
		case "persian_14":
			RemoveDublonsFromPCharTotal(700); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "cirass8"); 
			//Log_Info("You've received wicker armour");
			AddCharacterExpToSkill(pchar, "Sneak", 300);
			dialog.text = "Evet, iyi adamım! Al bakalım. Bu hasır zırh sana çok iyi hizmet edecek, emin olabilirsin. Tüm Karayipler'de bunun gibisi yok!";
			link.l1 = "Evet, görüyorum. Teşekkürler! Üzerimde denemek için sabırsızlanıyorum...";
			link.l1.go = "persian_15";
		break;
		
		case "persian_15":
			dialog.text = "Neden bekliyorsun? Devam et. Bakalım nasıl olacak.";
			link.l1 = "Yaparım. Sonra görüşürüz, Mösyö Fadey!";
			link.l1.go = "persian_16";
		break;
		
		case "persian_16":
			DialogExit();
			pchar.questTemp.Persian = "end";
			pchar.quest.Persian_CirassLamportOver.over = "yes"; //снять прерывание
		break;
		
		// торговля канатами
		case "ropes":
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes"))
			{
				dialog.text = "Buyurun, sevgili dostum. Mallarınız hazır, satın alabilirsiniz. İki yüz elli parça için iki bin yüz yirmi beş doblon.";
				if (PCharDublonsTotal() >= 2125)
				{
					link.l1 = "Her şey anlaştığımız gibi. Parayı al.";
					link.l1.go = "ropes_1";
				}
				else
				{
					link.l1 = "Sadece kamarama gidip paraları alayım.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Buyurun, sevgili dostum. Mallarınız hazır, dilediğiniz gibi alabilirsiniz. Elli parça için beş yüz doblon.";
				if (PCharDublonsTotal() >= 500)
				{
					link.l1 = "Her şey anlaştığımız gibi. Parayı al.";
					link.l1.go = "ropes_1";
				}
				else
				{
					link.l1 = "Bırak da paraları kamaradan alayım.";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.FadeyRopes) >= 1 && !CheckAttribute(pchar, "questTemp.FadeyRopesBlock")) // увеличить объём поставок канатами
			{
				link.l4 = "Fadey, anlaşmalarımızın hacmini artırabilir miyiz? Senden beş kat daha fazla mal almaya hazırım! Bunun ikimize de faydası olacağını düşünüyorum. Ne dersin?";
				link.l4.go = "UpgradeRopes";
			}
			if(sti(pchar.questTemp.FadeyRopes) >= 1 && CheckAttribute(pchar, "questTemp.FadeyRopesPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок канатами, если в первый раз не принесли
			{
				link.l4 = "Fadey, parayı getirdim! Anlaştığımız gibi, üç bin altın doblon.";
				link.l4.go = "UpgradeRopes_Agreed";
			}
		break;
		
		case "ropes_1":
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes")) RemoveDublonsFromPCharTotal(2125);
			else RemoveDublonsFromPCharTotal(500); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Sizinle iş yapmak bir zevkti, "+pchar.name+". Adamlarıma halatları geminize getirmelerini emredeceğim.";
			link.l1 = "Teşekkür ederim!";
			link.l1.go = "ropes_2";
		break;
		
		case "ropes_2":
			dialog.text = "Eğer hâlâ daha fazla halata ihtiyacın olursa, bir ay sonra tekrar gel.";
			link.l1 = "Pekâlâ, Fadey. Sonra görüşürüz!";
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes")) AddCharacterGoods(pchar, GOOD_ROPES, 250);
			else AddCharacterGoods(pchar, GOOD_ROPES, 50);
			DeleteAttribute(npchar, "quest.ropes");
			SetFunctionTimerCondition("Ropes_FadeyAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 200);
			pchar.questTemp.FadeyRopes = sti(pchar.questTemp.FadeyRopes) + 1; // счётчик покупок
		break;
		
		// уменьшение НЗГ
		case "help":
			if (!CheckAttribute(npchar, "quest.relation_info"))
			{
				dialog.text = "Size nasıl yardımcı olabilirim, sevgili dostum?";
				link.l1 = "Sen etkili bir adamsın, Fadey. Valinin dostusun ve söylentilere göre sarayda da bağlantıların var. Eğer başım yasalarla derde girerse, yetkililere ricada bulunabilir misin?";
				link.l1.go = "relation_info";
				break;
			}
			dialog.text = "Sana nasıl yardımcı olabilirim, dostum?";
			if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l1 = "İngiliz yetkilileriyle bir sorunum var.";
				link.l1.go = "relation";
				pchar.GenQuest.FadeyNation = ENGLAND;
			}
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l2 = "Fransız yetkilileriyle başım belaya girdi.";
				link.l2.go = "relation";
				pchar.GenQuest.FadeyNation = FRANCE;
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "Kaçakçılarla ilgili ciddi bir sorunum var.";
				Link.l5.go = "contraband";
            }
			link.l9 = "Üzgünüm, sanırım bunu kendim halledebilirim.";
			link.l9.go = "exit";
		break;
		
		case "relation_info":
			dialog.text = "Oh ho ho, iyi adamım, bunu sana kim söyledi? Herkes yalan söyler. Ama sen Michel'in kardeşi ve benim de iyi bir dostum olduğun için, senin için işleri yoluna koymaya çalışabilirim. Yalnızca İngiliz ve Fransız makamlarına başvurabilirim, bağlantılarımın da bir sınırı var. İspanyollarla ya da Hollandalılarla iş yapmam\nAyrıca seni uyarayım, nüfuzum sadece küçük kabahatlerden seni kurtarmaya yeter. Onların sana karşı tutumunu hafif bir yanlışta ya da küçük bir öfkeyi yatıştırmak için değiştirmelerini sağlayabilirim. Ama kalkıp savaş çıkarırsan ve kestanelerini ateşten çıkarmamı beklersen, işte orada dur!\nÜstelik, aynı anda sadece bir ulusu yatıştırabilirim: Fransa ya da İngiltere. Kendimi ikiye bölemem, iki işi birden yapamam. Elbette, rüşvet için de biraz para gerekecek. Şartlarımı kabul ediyorsan, yardım istemekten çekinme.";
			link.l1 = "Teşekkürler, Fadey. Bunu aklımda tutacağım.";
			link.l1.go = "exit";
			npchar.quest.relation_info = "true";
		break;
		
		case "relation":
			rate = wdmGetNationThreat(sti(pchar.GenQuest.FadeyNation));
			iFadeyPseudoGlobal = DiplomatDublonPayment(rate, "Fadey", false);
			sTemp = FindRussianDublonString(iFadeyPseudoGlobal);
			if (rate < 2)
			{
				dialog.text = "Of course. I have certainly heard of your adventures - or misadventures. I can take care of your little problem; nothing that the right amount of gold greasing the right palms can't fix. " + sTemp + " and I'll pull you out of the cookpot.";
				if (PCharDublonsTotal() >= iFadeyPseudoGlobal) // belamour legendary edition
				{
					link.l1 = "Harika! İşte altın.";
					link.l1.go = "agree";
				}
				link.l2 = "O halde gidip paraları almak için tam zamanı.";
				link.l2.go = "exit";
			}
			else
			{
				if (rate < 4)
				{
					dialog.text = "Of course. I have certainly heard of your adventures - or misadventures. I can take care of your little problem; there's nothing that the right amount of gold greasing the right palms can't fix. " + sTemp + " and I'll pull you out of the cookpot.";
					if (PCharDublonsTotal() >= iFadeyPseudoGlobal) // belamour legendary edition
					{
						link.l1 = "Harika!   Altın burada.";
						link.l1.go = "agree";
					}
					link.l2 = "O halde, paraları almaya gitmem için tam zamanı.";
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = "Evet, gerçekten zor bir durumdasın! Bu işi tamamen çözemem. Ama, başına inecek yıldırımın etkisini biraz hafifletebilirim. Sonrasında ise, paran ve isteğin olursa, istediğin zaman tekrar rüşvet teklif edebiliriz. "+sTemp+" ve sıkıntılarını hafifletmeye başlayabilirim.";
					if (PCharDublonsTotal() >= iFadeyPseudoGlobal) // belamour legendary edition
					{
						link.l1 = "Haydut avcılarının peşimde olmasından bıktım. Al altını.";
						link.l1.go = "agree";
					}
					link.l2 = "O halde tam zamanı, gidip paraları alayım.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveDublonsFromPCharTotal(iFadeyPseudoGlobal); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Peki, bana on beş güne kadar bir süre ver. Bu arada, gereken ayarlamaları yapar, şunu bunu hallederim. Her şey yaklaşık iki haftaya biter. ";
			link.l1 = "Teşekkür ederim, Fadey! Bekliyor olacağım...";
			link.l1.go = "agree_1";
		break;
		
		case "agree_1":
			DialogExit();
            bOk = HasShipTrait(pchar, "trait23");
            rate = 10 + hrand(5);
            rate = GetIntByCondition(bOk, rate, rate / 2);
			SetFunctionTimerCondition("ChangeNationRelationFromFadeyComplete", 0, 0, rate, false);
			pchar.GenQuest.FadeyNation.Rate = GetDiplomatRate(bOk, sti(pchar.GenQuest.FadeyNation));
			npchar.quest.relation = "true";
		break;
		
		case "contraband":
			iFadeyPseudoGlobal = DiplomatDublonPayment(rate, "Fadey", true);
			sTemp = FindRussianDublonString(iFadeyPseudoGlobal);
			dialog.Text = "Neden gidip onları kızdırdın, dostum? Kaçakçılar bu diyarlardaki en kötü insanlar değiller, üstelik iyi para da kazandırabilirler. Peki, sana yardım edeceğim, onları nasıl yumuşatacağımı biliyorum... O zaman şöyle yapalım "+sTemp+", pazarlık yok.";
			if (PCharDublonsTotal() >= iFadeyPseudoGlobal) // belamour legendary edition
			{
				Link.l1 = "Pekâlâ, Fadey, kabul ediyorum. Al altınını.";
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "Şu anda yanımda o kadar altın yok. Sonra tekrar geleceğim!";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "Pekâlâ, aralarını düzelteceğim, merak etme. Seninle yine iş yapacaklar, eskisi gibi.";
			Link.l1 = "Teşekkür ederim!";
			Link.l1.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			RemoveDublonsFromPCharTotal(iFadeyPseudoGlobal); // belamour legendary edition
			PlaySound("interface\important_item.wav");
		break;
		
		case "UpgradeRopes":
			dialog.text = "Ho-ho, işlerin yolunda gidiyor ve iştahlar kabarıyor anlaşılan! Haklısın, mallarımız kaliteli ve fiyatlarımız da makul. Yalnız unutma, yatırım şart! Böyle bir işte her şeyin kusursuz olması için ciddi bir yaklaşım gerekir.";
			link.l1 = "Böyle bir teklifle sana gelir miydim, yedekte birkaç yüz dublonum olmasa?";
			link.l1.go = "UpgradeRopes_1";
		break;
		
		case "UpgradeRopes_1":
			dialog.text = "Sandığında altınların olduğunu biliyorum, hem de bir iki tane değil, eminim elli tane bile sığar! Ama bizim işimiz sıradan değil – mesele sadece mal taşımak değil, bir yol bulmak... diyelim ki, gizlice. Bu kadar büyük bir iş için sadece ödeme yapmak yetmez, ciddi bir yatırım yapmalısın ki kârın olsun! Hem de paran havaya uçup gitmesin diye. Eğer üç bin altın dublonla vedalaşmaya hazırsan, söz veriyorum, her şey senin için, iyi bir dost olarak, en doğru şekilde yapılacak ve fiyat konusunda da seni mağdur etmeyeceğiz.";
			if (PCharDublonsTotal() >= 3000)
			{
				Link.l1 = "Üç bin doblon! Doğrusu, böylesine cömert bir teklif, en zengin tüccarların bile, en hayali hikâyelerde dahi nadiren duyduğu bir şey! Böyle bir işe bu kadar büyük bir yatırım yapmaya pek azı cesaret eder. Ama neyse ki, ben o azınlık arasındayım. İşte paranız, Mösyö Fadey.";
				Link.l1.go = "UpgradeRopes_Agreed";
			}
			Link.l2 = "Üç bin altın doblon! Böyle bir meblağa hazır değilim, Fadey. Ne yazık ki. Sonra tekrar uğrarım.";
			Link.l2.go = "UpgradeRopes_Potom";
			link.l3 = "Üç bin mi diyorsun? Hm... Doğrusu, böyle bir meblağ senin hırsına saygı duymamı sağlıyor. Ama itiraf etmeliyim ki - bu bana göre değil.";
			link.l3.go = "UpgradeRopes_2";
		break;
		
		case "UpgradeRopes_2":
			dialog.text = "Ne değişiklik ama! Bir teklifle geldin, sonra hemen geri adım attın! Doğrusu, hayal kırıklığına uğradım, ama dostluğumuzu bunun bozmasına izin vermem. Her şey eskisi gibi kalsın: Önceki anlaşmamız geçerli - her ayın 20'sinde, elli rulo, tanesi on dublondan.";
			link.l1 = "Beni anladığın iyi oldu, Fadey. Fikrimi değiştirmek isterdim ama böyle harcamalar bana göre değil. Ne yazık ki, bu konuda imkanlarım sınırlı.";
			link.l1.go = "UpgradeRopes_3";
		break;
		
		case "UpgradeRopes_3":
			dialog.text = "Pekala, madem kararın bu, konuşacak başka bir şey yok. Bu dostluğumuzu etkilemez. Yine de uğra, "+GetSexPhrase("iyi beyefendi","güzel hanımefendi")+".";
			link.l1 = "Elveda.";
			link.l1.go = "exit";
			pchar.questTemp.FadeyRopesBlock = true;
		break;
		
		case "UpgradeRopes_Potom":
			DialogExit();
			pchar.questTemp.FadeyRopesBlock = true;
			pchar.questTemp.FadeyRopesPotom = true;
		break;
		
		case "UpgradeRopes_Agreed":
			dialog.text = "İşte bu akıllıca! Boş laf sevmiyorsun, ama harekete geçmeyi biliyorsun. Senin gibi işten anlayanlara her zaman bir indirim bulunur! Tüm gelecek sevkiyatlarda yüzde on beş indirim! Anlaşmamız şöyle: Her ay senin için hazır tutacağım 250 top kenevir halatı. Önceden olduğu gibi, her ayın 20’sinde gelip alabilirsin, hepsi için 2125 dublon ödeyeceksin, üstü başı yok.";
			link.l1 = "Mükemmel, Fadey! Seninle iş yapmak gerçekten çok kolay. Eminim başarı bizi bekliyor. Bir dahaki sefere kadar!";
			link.l1.go = "exit";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "2_1");
			pchar.questTemp.UpgradeRopes = true;
			pchar.questTemp.FadeyRopesBlock = true;
			DeleteAttribute(pchar, "questTemp.FadeyRopesPotom");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}