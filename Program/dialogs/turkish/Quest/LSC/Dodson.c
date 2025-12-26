// Акула: Стивен Додсон
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
			// Jason НСО
			if(CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, ne oluyor lan?";
				link.l1 = "Steven, bir sorun çıktı. Ne gelebilirdim ne de yokluğumdan seni haberdar edebildim...";
				link.l1.go = "patria_33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Seni görmek güzel, dostum! Sana nasıl yardımcı olabilirim? ";
				link.l1 = "Seni görmek de güzel, Steve. O mükemmel şekilde düzenlenmiş gösteri için sana teşekkür etmek istiyorum!";
				link.l1.go = "patria_29";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Shark") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Seni görmek güzel, dostum! Sana nasıl yardımcı olabilirim?";
				link.l1 = "Sana bir teklifim var, Steven. Korsanlara yaraşır bir teklif.";
				link.l1.go = "patria";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Shark") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "There's our man! The job is done; your baron is sitting in a well-guarded dungeon. Perhaps you'd like to take a look? He-he!";
				link.l1 = "Ha, onun için sonra bolca vaktimiz olacak. Ona iyi davranıyorlar mı?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = "Seni görmek güzel, dostum! Sana nasıl yardımcı olabilirim?";
				link.l1 = "Bir şeye ihtiyacım var, Steven...";
				link.l1.go = "tieyasal";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "islatesoro")
			{
				dialog.text = "Seni görmek güzel, dostum! Sana nasıl yardımcı olabilirim?";
				link.l1 = "Steven, senin için bir şeyim var.";
				link.l1.go = "guardoftruth";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "islatesoro")
			{
				dialog.text = "Seni görmek güzel, dostum! Sana nasıl yardımcı olabilirim?";
				link.l1 = "Steven, sana bir şey sormam lazım. Hoşuna gitmeyebilir... ama yardımına ihtiyacım var.";
				link.l1.go = "shadows";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "islatesoro")
			{
				dialog.text = "Ha, işte buradasın, "+pchar.name+". I was expecting you; Forest Devil told me about your trouble with Tortuga...";
				link.l1 = "Bana ayrıca zaten bir çözüm bulduğunu da söyledi. Doğru mu?";
				link.l1.go = "terrapin";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin.Catherina") && pchar.questTemp.Terrapin == "tortuga")
			{
				dialog.text = "Nasıl gidiyor, "+pchar.name+"?";
				link.l1 = "Her yerde sırlar var... Tavsiyene ihtiyacım var, Steven.";
				link.l1.go = "terrapin_8";
				break;
			}
			// belamour legendary edition хвастовство "Фортуной"
			if(CheckShipTypeInSquadron(SHIP_FRIGATE_L) > 0 && !CheckAttribute(pchar,"questTemp.SharkFrigate"))
			{
				link.l2 = "Sana bir şey göstermek istiyorum... Benimle iskeleye yürür müsün?";
				link.l2.go = "check_out_my_frigate";
			}
			
			// belamour legendary edition на пару с Акулой
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "toDodson")
			{
				dialog.text = "Ah, dostum "+GetFullName(pchar)+" ! Gir içeri, gir, seni görmek güzel!";
				link.l1 = "Merhaba, Steven! Söz verdiğim gibi geldim. Gemin hazır mı?";
				link.l1.go = "SharkGoldFleet";
				break;
			}
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "RUinDeal")
			{
				link.l2 = "Peki, işler nasıl gidiyor? Hâlâ 'Altın Filo'nun peşinde misin?";
				link.l2.go = "SharkGoldFleet_10";
			}
			dialog.text = "Ah, dostum "+GetFullName(pchar)+" ! Gir içeri, gir, seni görmek güzel!";
			link.l1 = "Merhaba, Steven. İş için Sharptown'dayım ve bir dakikalığına uğramak istedim.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// --------------------------------------вариант R-----------------------------------------------
		case "Chad_die":
			dialog.text = "Ha! Demek gece misafirimiz sensin? Bu olaydan az önce haberdar edildim. Eşyalarını kontrol ettim ve Orman Şeytanı'ndan gelen mektubu buldum. Lanet olsun, neredeyse Yeni İspanya'nın ormanları gibi kokuyordu!\nAdın "+GetFullName(pchar)+"? I'm Steven Dodson, better known to some as Shark. Svenson must've told you about me. Around Justice Island, however, I'm known as the Admiral.\nI apologize for the actions of my men last night. They were acting on orders from me to capture anyone who snuck into the hold; the Narwhals and Rivados routinely send thieves to steal provisions from us.\nChad let you go, I assume? Odd... I was just about to order him to release you.\nWhere's your ship? Is she intact?";
			link.l1 = "Chad mi? Bildiğim kadarıyla, senin lostromusun beni o hapishaneden sağ çıkarmazdı. Kendi başıma kurtuldum, hem de o... o Rivados'lardan biriyle birlikte.";
			link.l1.go = "Chad_die_1";
		break;
		
		case "Chad_die_1":
			dialog.text = "Bu gerçekten ilginç. Peki, Tartarus'tan nasıl kurtuldun? Görünen o ki Chad ve adamlarıyla bir konuşma yapmam gerekecek...";
			link.l1 = "Tek taraflı bir konuşma olacak, korkarım. Hepsi öldü. Chad beni sonsuza kadar kafeste bırakmakla tehdit etti. Bana Rivados dedi, ona aksini kanıtlamamın tek yolunun siyah büyücü Chimiset'i öldürmek olduğunu söyledi.";
			link.l1.go = "Chad_die_2";
		break;
		
		case "Chad_die_2":
			dialog.text = "Ne?! Ah, Kapper, seni aptal herif...\nChimiset'in hayatta kalması gerekiyordu, Chad bunu biliyordu! Ve neden senin Rivados olduğunu düşünsün ki, hepsi zenci değil mi?!";
			link.l1 = "Chimiset ölmedi, Steven. O yaşlı büyücü beni ikna etti; onu öldürsem bile, Chad beni Tartarus'tan sağ çıkartmazdı...";
			link.l1.go = "Chad_die_3";
		break;
		
		case "Chad_die_3":
			dialog.text = "";
			link.l1 = "Chimiset'i öldürmek yerine, bir sandık silah ve cephaneyi açıp Chad ve adamlarını yere serdim.";
			link.l1.go = "Chad_die_4";
		break;
		
		case "Chad_die_4":
			dialog.text = "Harika! Gerçekten harika! Ama hâlâ aklım almıyor... Chad neden bütün bunları yapsın ki?";
			link.l1 = "Oraya yaklaşıyorum! Chimiset bana Chad'in Narwhals'la - başka bir klanmış, anladığım kadarıyla - senin ölmen ve korsanların başına geçmek için anlaşma yaptığını söyledi. Narwhals seni öldürmek istiyor, çünkü liderleri Alan'ı öldürdüğünden eminler... Alan Milton? Miller?";
			link.l1.go = "Chad_die_5";
		break;
		
		case "Chad_die_5":
			dialog.text = "Saçmalık! Alan Milrow'u ben öldürmedim! Onu başkası öldürdü - belki de Narwhal'lardan biri! Hatta şimdiki liderleri Donald Greenspan bile olabilir diye düşündüm.";
			link.l1 = "Hayır. Chad onu öldürdü. Chimiset suçu gördü - bu yüzden Chad onu da öldürmek istedi. Bunu kendi başına yapmak istemedi çünkü Chimiset'in ona musallat olmasından korkuyordu, ya da... ya da başka bir şeyden, bilmiyorum. Her neyse, işte bu yüzden işi bana yaptırmak istedi.";
			link.l1.go = "Chad_die_6";
		break;
		
		case "Chad_die_6":
			dialog.text = "Ve... Chad neden Alan'ı öldürsün ki?";
			link.l1 = "Sana tuzak kurup Narwhal'ların düşmanı yapmaktı. Suçu üstüne yıkacak dedikoduları yaydı, böylece ortalıkta görünmen tehlikeli hale geldi. Sen öldüğünde ise, cinayetini Rivado'ların üstüne atacak ve korsanların onlara saldıracaktı.";
			link.l1.go = "Chad_die_7";
		break;
		
		case "Chad_die_7":
			dialog.text = "";
			link.l1 = "Bu mektubu Chad'in sandığında buldum. Oku. Dolaylı da olsa sağlam bir kanıta benziyor.";
			link.l1.go = "Chad_die_8";
		break;
		
		case "Chad_die_8":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "...(reading)... heh! In hindsight I'm not surprised at Chad's betrayal. The whoreson always wanted more power.\nBut the Narwhals! To seriously think I killed Alan! This will cost them double their current price on provisions!\nAs for Chimiset... I was planning to release him anyway; it's high time we made peace with the Rivados. You have shocked me, mate, truly...";
			link.l1 = "Anlıyorum, Steven. Ben de hoşlanmıyorum bundan. Buraya bu siyasi entrikalara karışmak için gelmedim, seni ve Nathaniel Hawk'ı bulmak için geldim--";
			link.l1.go = "Chad_die_9";
		break;
		
		// ноды пересечения
		case "Chad_die_9":
			dialog.text = "Hawk mı? O Jamaika'da değil mi?";
			link.l1 = "Hayır. Artık Maroon Kasabası'nı Jackman yönetiyor. Hawk'ın da buraya benim gibi geldiğini öğrendim: Kukulcan'ın putu sayesinde.";
			link.l1.go = "Chad_die_10";
		break;
		
		case "Chad_die_10":
			dialog.text = "... Ne saçmalıyorsun sen?";
			link.l1 = "Buraya gemiyle gelmedim, Steven. Biliyorum, inanması zor, ama İspanyol Ana'da bir Hint putu var, bir çeşit kapı gibi çalışıyor – bana öyle bakma, deli ya da sarhoş değilim! Bunun nasıl mümkün olduğunu ben de anlamıyorum, ama gerçekten öyle!";
			link.l1.go = "Chad_die_11";
		break;
		
		case "Chad_die_11":
			dialog.text = "...";
			link.l1 = "Amatique Koyu'nun güneyindeki Miskito köyünde Yılan Göz adında bir şaman, Hawk'u onu öldürmeye çalışan adamlardan kurtulmasına yardım etmiş. Hawk'a Kızılderili putunu - Kukulcan'ın bir simgesini - göstermiş ve bu put onu bu adaya getirmiş. Yılan Göz, bir zamanlar kendisinin de tam olarak aynı şekilde bu adaya geldiğini ve benim de bunu nasıl yapabileceğimi anlattı.";
			link.l1.go = "Chad_die_12";
		break;
		
		case "Chad_die_12":
			dialog.text = "...";
			link.l1 = "Gece yarısı, tam dediği gibi, putun yanına geldim. Ve bu put, bütün gün sıradan bir taştan ibaretken, birdenbire saf altına dönüşmüştü! Üzerinden tuhaf bir ışık yayılıyordu.";
			link.l1.go = "Chad_die_13";
		break;
		
		case "Chad_die_13":
			dialog.text = "...";
			link.l1 = "Putperest heykele dokunduğumda, etrafında bir ışık halkası oluştu, her yerde alevler yükseldi, sonra birdenbire heykelin içine çekildim. Sonra kendimi burada, senin geminin ambarında, baş tarafa yakın, alt katta, o yarığın orada buldum...";
			link.l1.go = "Chad_die_14";
		break;
		
		case "Chad_die_14":
			dialog.text = "...";
			link.l1 = "Berbattı ama — yolculuktan sonra midem bulandı, bitkin düştüm. Yılan Göz bana o etkiyi gidermek için özel bir iksir verdi gerçi. Üstüne üstlük, devasa bir lanet yengeç bana saldırdı! (derin nefes) ";
			link.l1.go = "Chad_die_15";
		break;
		
		case "Chad_die_15":
			dialog.text = "... All right, I believe you.\nThat is, I believe the part about the crab. There are lot of those monsters around the island. We bait them with dead fish, so they hang around the submerged breaches in the hull.\nWonderful guards - scare thieves shitless. But all this about the idol...\nI won't reject that part of your story out of hand; I've heard about the strange rituals the Rivados used to conduct aboard their ships... There was talk of human sacrifices to a... to an Indian idol...";
			link.l1 = "Yemin ederim, hepsi doğru.";
			link.l1.go = "Chad_die_16";
		break;
		
		case "Chad_die_16":
			dialog.text = "Sana inandığına inanıyorum. Ama şimdilik sihirli putları bir kenara bırakalım.\nJan'ın mektubuna göre, Sahil Kardeşliği'nin başı olmamı istiyormuşsun?";
			link.l1 = "Aynen öyle. Sen ve Hawk ortadan kaybolduktan sonra pek çok şey değişti. Jackman Korsanlar Birliği'nin lideri olmak istiyor, ve Jan'la ben onu durdurmazsak olacak da.";
			link.l1.go = "Chad_die_17";
		break;
		
		case "Chad_die_17":
			dialog.text = "";
			link.l1 = "Jackman ciddi ve kanlı bir oyunun peşinde. Hawk'a kurulan pusuyu onun düzenlediğine eminim. Blaze Sharp'ı da öldürdüğünü düşünüyorum. Onu durdurmanın tek yolu, Kardeşliğin lideri olmanı sağlamak.";
			link.l1.go = "Chad_die_18";
		break;
		
		case "Chad_die_18":
			dialog.text = "Tahtı devralmaktan memnuniyet duyarım, ama önce bu adadan ayrılmamız gerek.\nBuradan bıktım artık. Planımız, burada üsse Dexter'ın bakmasını sağlamaktı - zaten uzun süre kalmaya hiç niyetim yoktu - ama gemim klanlarla bir çatışmada yakıldı.\nVe sakın bana adadan kurtulmak için mistik Hint saçmalıklarını önermeye kalkma. Ya gemiyle giderim ya da hiç gitmem.";
			link.l1 = "Steven... (ah) O putu hâlâ bulmam gerek! Snake Eye burada olacağına yemin etmişti. Şimdi, Rivados'un bir put kullanarak ayinler yaptığına dair bir şeyler bildiğini söyledin. Bana başka ne anlatabilirsin?";
			link.l1.go = "Chad_die_19";
		break;
		
		case "Chad_die_19":
			dialog.text = "Hiçbir şey. Bunların hepsi ben buraya gelmeden önceydi - hem de çok önce.";
			link.l1 = "Artık bu... bu Kukulcan'ın geçitlerinden geçmek beni korkutmuyor - ve bu, adadan çıkıp bir gemi bulmam ve seni eve götürmem için en hızlı yol olacak. Başka hiçbir şeye inanmasan da, sana yardım etmek istediğime inan.";
			if (pchar.questTemp.LSC == "entrance" || pchar.questTemp.LSC == "mary") link.l1.go = "entrance_4";
			else link.l1.go = "Chad_die_20";
		break;
		// ноды пересечения
		
		case "Chad_die_20":
			dialog.text = "I understand... but I. Can't. Help. You. Aside from the rumours, I know sweet fuck-all about this idol.\nAnd you know, call me selfish, but I'm a little more preoccupied with this assassination business; Chad is dead, but I doubt the Narwhals will give up on trying to kill me.\nSince you need me alive and you're already involved in this mess, I want you to investigate this conspiracy.\nAs a newcomer, you can go places and talk to people that my lads could never reach. Find Chad's partners and bring them to me - or kill them, I don't care.\nTalk to Chimiset; the old black knows more than he lets on. And he may know more about your idol...\nBe careful with the Narwhals, and don't cross their borders unless you have the current password - they change it every week.\nOnce this whole thing's put to bed, I'll give you my rutters. They contain sailing directions and information you'll need to sail to and from Justice Island.\nGo. Find the conspirators. Restore order. Keep me alive.\nNow... Dexter needs to clean the bodies out of the gaol... Tartarus needs a new gaoler... and I need some rum. Fuck me, what a day.";
			link.l1 = "...";
			link.l1.go = "Chad_die_21";
		break;
		
		case "Chad_die_21":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			pchar.questTemp.LSC.rvd_friend = "true"; //флаг на проход по кораблям ривадос
			// // ривадосы не будут останавливать где просят пароль
			sld = characterFromId("Chimiset");
			sld.dialog.currentnode = "Friend"; //ноду Чимисету
			pchar.quest.LSC_Eddy.win_condition.l1 = "location";
			pchar.quest.LSC_Eddy.win_condition.l1.location = "ProtectorFisher";
			pchar.quest.LSC_Eddy.function = "LSC_EddyTalk"; //на разговор с Эдди
			AddQuestRecord("SharkHunt", "10");
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			for (i=7; i<=12; i++)
			{
				sld = CharacterFromID("RivadosSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=4; i<=8; i++)
			{
				sld = CharacterFromID("RivadosProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			AddSimpleRumourCityTip("Would you believe it? Someone has killed the Admiral's gaoler, Chad Kapper! No doubt the work of that Rivados wizard he locked up, Chimiset...", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("I heard that Chad Kapper is dead, but there's been no official statement and his body hasn't turned up. Perhaps, the Admiral simply gave him a secret mission...?", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("I haven't seen our gaoler, Chad Kapper, lately. Some say he was killed, some say he's still alive. The only thing people agree on is that no one has seen him...", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that the Admiral doubled provision prices for the Narwhals! That pirate is truly reckless!", "LostShipsCity", 7, 3, "LSC", "");
		break;
		
			case "Mary_Die":
			dialog.text = "Peki, neyin var, "+pchar.name+"? Narwhals hakkında bir haber var mı?";
			link.l1 = "Evet. Bilmeni isterim Steven, komplo ortaya çıktı ve komplocular öldü. Artık her şeyi biliyorum.";
			link.l1.go = "Mary_Die_1";
		break;
		
		case "Mary_Die_1":
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack")) dialog.text = "Çatışma seslerini duyunca ben de öyle düşündüm... Konuş benimle.";
			else dialog.text = "Öyle mi? Eh, bu iyi haber! Anlat bakalım.";
			link.l1 = "Her şey başçavuşun Chad Kapper tarafından planlandı. Tartarus'un hücrelerinde Alan Milrow'u öldürdü ve suçu senin üstüne attı. Narwhal tayfası öfkelendi — özellikle Alan'ın sevgilisi Kızıl Mary...";
			link.l1.go = "Mary_Die_2";
		break;
		
		case "Mary_Die_2":
			dialog.text = "";
			link.l1 = "Mary intikam için yanıp tutuşuyordu ve Chad Kapper onun öfkesini kullandı. Seni öldürmek için bir plan yaptılar. San Augustine'in kıç galerisinde her akşam dolaşma alışkanlığın olduğunu biliyorum...";
			link.l1.go = "Mary_Die_3";
		break;
		
		case "Mary_Die_3":
			dialog.text = "Heh! Bu alışkanlığımdan vazgeçmem gerekecek... Devam et.";
			link.l1 = "Planlarını gerçekleştirmek için uzun menzilli ve isabetli bir tüfeğe ihtiyaçları vardı, bu yüzden Adolf Barbier onlara temin etti. Fakat onun stutzen'i Giuseppe Fazio'ya rehin verilmişti, bu yüzden Mary ve Chad onu geri almak zorunda kaldı - Adolf stutzen'i kurtardı...";
			link.l1.go = "Mary_Die_4";
		break;
		
		case "Mary_Die_4":
			dialog.text = "";
			link.l1 = "They hired Marcello Cyclops, a former royal hunter, to take the shot. After that, Mary would kill him and use his corpse and rifle as proof the Rivados were responsible for the attack; Cyclops was a mulatto.";
			link.l1.go = "Mary_Die_5";
		break;
		
		case "Mary_Die_5":
			dialog.text = "Hepsi de Chad'in şeytani zekasından... akıllı herifin teki!";
			link.l1 = "Ve sonunda, Narwhal'lar ve korsanlar Rivados klanına saldırıp onları yok ederdi. Chad amiral olurdu ve Mary de onun sevgilisi. Gerçi... birkaç gece geçirdikten sonra, muhtemelen onu boğazlayıverirdi, çünkü Mary fazlasıyla sır biliyordu.";
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack")) link.l1.go = "Mary_Die_6a";
			else link.l1.go = "Mary_Die_6";
		break;
		
		case "Mary_Die_6":
			dialog.text = "";
			link.l1 = "Her neyse, artık bitti. Adolf pek konuşkan değildi, bu yüzden onu kamarasında öldürmek zorunda kaldım. Mary ve Cyclops'la da ilgilendim, Adolf'dan stutzen'i almaya geldiklerinde.";
			link.l1.go = "Mary_Die_7";
		break;
		
		case "Mary_Die_7":
			dialog.text = "Yani, hepsi Santa Florentina'nın içinde ölü olarak yatıyor, öyle mi? Ve kimsenin bundan haberi yok?";
			link.l1 = "Evet. Üçü de - ve bunu bizden başka kimse bilmiyor.";
			link.l1.go = "Mary_Die_8";
		break;
		
		case "Mary_Die_8":
			dialog.text = "Güzel. Tanıklar işleri zorlaştırırdı. Cesetlerle ben ilgilenirim. İyi iş çıkardın, "+pchar.name+"! Mürettebatımda olsaydın, seni birinci subay yapardım.";
			link.l1 = "Büyük iltifat, Köpekbalığı. Sağ ol. Şuna da bir bak, bu mektupları Kiklop ve Mary'nin cesetlerinden aldım...";
			link.l1.go = "Mary_Die_9";
			AddSimpleRumourCityTip("Have you heard that? Our scrappy madcap Red Mary has disappeared. I wouldn't be surprised if she's dead...", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that Red Mary has disappeared. You heard about that?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("Mary Casper has vanished. Some people say that she's still inside her cabin, but I don't believe it; it's been a long time since I saw a light in her window.", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that Red Mary was murdered. Poor girl! Yes, she was a tough sort, but everybody loved her. Who could have done such a thing?", "LostShipsCity", 10, 1, "LSC", "");
		break;
		
		case "Mary_Die_6a":
			dialog.text = "";
			link.l1 = "Her neyse, artık bitti. Adolf pek konuşkan değildi, bu yüzden onu kamarasında öldürmek zorunda kaldım. Mary ve Cyclops'la da ilgilendim, onlar Adolf'tan stutzen almaya geldiklerinde.";
			link.l1.go = "Mary_Die_7a";
		break;
		
		case "Mary_Die_7a":
			dialog.text = "Eva'da kavga çıkarman kötü oldu. Narwhal'larla başın belada, adamlarını öldürdün. Barışana kadar onlardan uzak dur.\nGenel olarak, fena iş çıkarmadın, "+pchar.name+"! Mürettebatımda olsaydın, seni birinci subayım yapardım.";
			link.l1 = "Büyük iltifat, Köpekbalığı. Sağ ol. Şuna da bir bak, bu mektupları Cyclops ve Mary'nin cesetlerinden aldım...";
			link.l1.go = "Mary_Die_9";
			AddSimpleRumourCityTip("Such a massacre you've committed! The Narwhals won't forget it!", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("I understand killing Cyclops and two Narwhal bandits, but... the girl. Why did you have to kill poor Mary?", "LostShipsCity", 7, 5, "LSC", "");
		break;
		
		case "Mary_Die_9":
			RemoveItems(pchar, "letter_chad", 1);
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "Zavallı Mary mi? O fahişe için üzülüyorsun demek, ha.";
			link.l1 = "Evet, biliyorum. Chad onu kandırdı, duygularıyla ve doğal öfkesini kullanarak onu manipüle etti... Onun hırsları uğruna ölmemeliydi.";
			link.l1.go = "Mary_Die_10";
		break;
		
		case "Mary_Die_10":
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You have received 500 doubloons");
			PlaySound("interface\important_item.wav");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			dialog.text = "Pekâlâ, eğer bu kadar kötü hissediyorsan, Git Kardeş Julian'ı gör ve bir mum yak. Açıkçası, o kaltak öldüğü için çok memnunum.\nTamam, konuyu kapatalım. Yardımın için minnettarım, "+pchar.name+" . Artık desteğime güvenebilirsin. Mükemmel işin için sana ödeme yapmak istiyorum. Al, beş yüz dublon.";
			link.l1 = "Teşekkürler, Steven...";
			link.l1.go = "LSC_navy";
			AddSimpleRumourCityTip("They say the Admiral respects you, mister...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you're the Admiral's loyal friend. Is that true?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		// ----------------------------------------вариант N---------------------------------------------------
		case "entrance":
			dialog.text = "Seni tanımıyorum. Ne istiyorsun?";
			link.l1 = "Tabii ki, tanımıyorsun. Hiç karşılaşmadık, ben de daha yeni geldim. Merhaba, Steven. Seni arıyordum.";
			link.l1.go = "entrance_1";
		break;
		
		case "entrance_1":
			dialog.text = "Birçok kişi beni bulmaya geldi. Çoğu şimdi mezarlıkta yatıyor. Onlara katılmak istemiyorsan, belki de neden beni aradığını anlatmayı dene.";
			link.l1 = "Ortak bir dostumuz var. Al, bu mektubu sana vereyim. Jan Svenson yazdı bunu. Eski Orman Şeytanı her şeyi benden çok daha iyi açıklar.";
			link.l1.go = "entrance_2";
		break;
		
		case "entrance_2":
			RemoveItems(pchar, "letter_svenson", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "(okuyorum)... Hm. Bu bazı şeyleri açıklıyor. Ben de seni Blaze'i öldürdüğüm için bana kara işaret vermeye geldin sanmıştım - son zamanlarda bunu yapmak isteyen pek çok korsan çıktı.\nGemini dış halkada mı bıraktın? Ve burada olduğumu nasıl öğrendin?";
			link.l1 = "Ben yapmadım. Tamamen tesadüftü. Ve Blaze konusunda... Jan'la ben onun ölümünden seni sorumlu tutmuyoruz.";
			link.l1.go = "entrance_3";
		break;
		
		case "entrance_3":
			dialog.text = "Haklısın, değilim. Ama birileri Kardeşliğin bunu yaptığımı sanmasını istiyor.";
			link.l1 = "İlginç... Biliyor musun, buraya Nathaniel Hawk'ı bulmaya gelmiştim ama onun yerine seni buldum, heh!";
			link.l1.go = "Chad_die_9";
		break;
		
		case "entrance_4":
			dialog.text = "Bu konuda adanın eskileriyle konuşman gerekecek. Rivados büyücüsü Chimiset'i dene. O yaşlı zenci, göründüğünden çok daha fazlasını biliyor.";
			link.l1 = "Bu büyücüyü nerede bulabilirim?";
			if (pchar.questTemp.LSC == "mary") link.l1.go = "mary";
			else link.l1.go = "entrance_5";
		break;
		
		case "entrance_5":
			dialog.text = "In my prison, aboard the Tartarus. I was planning to release him soon; it's time to improve our relations with the Rivados.\nYou can deliver the order yourself! Go to the Tartarus, tell Chad Kapper, the gaoler, that I want Chimiset freed.\nBetter yet, ask to see Chimiset first. Tell him I sent you, that I'll release him if he's talkative enough. I'm sure he'll tell you what you want to know.";
			link.l1 = "Hmm... Tartarus nerede?";
			link.l1.go = "entrance_6";
		break;
		
		case "entrance_6":
			dialog.text = "Evimden çık, köprüyü geç, sola dön, Caroline firkateyninden geçerek Gloria kalyonuna git ve Esmeralda'ya var. 'Dükkan' yazan tabelayı bul ve altındaki kapılardan içeri gir. Geminin baş tarafındaki kapıdan geçersen Tartarus'a ulaşırsın.\nEsmeralda'da dikkatli ol, orası Narwhal bölgesi, başkaları da girebilir ama. Muhafızlarını kızdırma, sorun çıkarma.";
			link.l1 = "Bunlar kim, Rivados ve Narwhals mı?";
			link.l1.go = "entrance_7";
		break;
		
		case "entrance_7":
			dialog.text = "Adalet Adası'nın ilk yerleşimcilerinden türeyen klanlar bunlar. Narwhal'lar çoğunlukla İngiliz, Hollandalı ve Fransız kökenli. Rivados'ların hepsi Zenci.\nHer klanın bir lideri var ve her biri, yabancılara kapalı olan birkaç gemiden oluşan bir bölgeyi kontrol ediyor.\nNarwhal ya da Rivados bölgesine girmek için doğru parolaları bilmelisin, üstelik parolaları her hafta değiştiriyorlar.";
			link.l1 = "Bunu bilmek güzel, ama beni hapishaneye alacaklar mı?";
			link.l1.go = "entrance_8";
		break;
		
		case "entrance_8":
			dialog.text = "Olacaklar. İşte anahtar, böylece Chad seni benim gönderdiğimi anlar. Sakın kaybetme.";
			link.l1 = "Sağ ol. O... Chimiset denenle konuşup sonuçlarla döneceğim.";
			link.l1.go = "entrance_9";
		break;
		
		case "entrance_9":
			DialogExit();
			GiveItem2Character(pchar, "key_capper");
			NextDiag.CurrentNode = "Total_wait";
			sld = characterFromId("Chimiset");
			sld.dialog.currentnode = "prisoner"; //даем ноду Чимисету
			sld.quest.chimiset_die = "true";
			ChangeCharacterAddressGroup(sld, "Tartarusprison", "quest", "prison2"); // в закрытую клетку
			LAi_SetGroundSitTypeNoGroup(sld);
			sld = characterFromId("Capper");
			sld.dialog.currentnode = "prisoner"; //даем ноду Капперу
			LAi_LocationFightDisable(&Locations[FindLocation("Tartarusprison")], true);//запретить драться
			// прерывания на локаторы тартаруса
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1 = "locator";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.locator = "reload51";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l2 = "item";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l2.item = "key_capper";
			pchar.quest.LSC_TartarusEntrance1.function = "LSC_TartarusEntrance1_Open";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1 = "locator";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.locator = "reload52";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l2 = "item";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l2.item = "key_capper";
			pchar.quest.LSC_TartarusEntrance2.function = "LSC_TartarusEntrance2_Open";
			AddQuestRecord("SharkHunt", "19");
		break;
		
		case "entrance_10":
			dialog.text = "Tartarus'a mı gittin?";
			link.l1 = "Evet. Emirlerini Chad'e verdim ve Chimiset ile konuştum.";
			link.l1.go = "entrance_11";
		break;
		
		case "entrance_11":
			dialog.text = "Büyücü sana bir şey söyledi mi?";
			link.l1 = "Ah, evet. Aradığım putun nerede olduğunu bana söyledi. San Geronimo'daymış, Narwhal bölgesinin yakınlarında, birkaç yıl önce batmış.";
			link.l1.go = "entrance_12";
		break;
		
		case "entrance_12":
			dialog.text = "Ha-ha-ha! Demek sihirli putun şimdi denizin dibinde, ha? Eh dostum, artık bizimlesin gibi görünüyor.";
			link.l1 = " Bir yolunu bulup idole ulaşacağım. Şimdi, Chimiset Kapper'a güvenmemeni söyledi, çünkü Chad'in Alan Milrow adında birini öldürdüğünü görmüş--";
			link.l1.go = "entrance_13";
		break;
		
		case "entrance_13":
			dialog.text = "Ne?! Chad Alan'ı mı öldürdü? Chimiset yalan söylüyor, bu olamaz!";
			link.l1 = "Steve, Chimiset korkudan tir tir titriyordu. Eğer yalan söylüyorsa, bunu gerçekten ustaca yaptı...";
			link.l1.go = "entrance_14";
		break;
		
		case "entrance_14":
			dialog.text = "Lanet olsun, bu da harika şimdi!\nAlan'ın öldürülmesi Narwhal'larla aramı bozdu - bazıları suçu benim üstüme atıyor - ve şimdi bir de kendi subaylarımdan biri mi işlemiş cinayeti?!";
			link.l1 = "Yapmadığın şeyler için üstüne çok fazla suç atılıyor gibi görünüyor.";
			link.l1.go = "entrance_15";
		break;
		
		case "entrance_15":
			dialog.text = "Fark ettim.";
			link.l1 = "Maalesef işler daha da ilginçleşiyor: Chimiset, adamlarından bazılarının seni öldürmeyi planladığını duymuş. Sana daha fazlasını ancak onu serbest bıraktıktan sonra ve yalnızken anlatacak.";
			link.l1.go = "entrance_16";
		break;
		
		case "entrance_16":
			dialog.text = "Harika. Bugünün fazla sorunsuz geçtiğini biliyordum.\nChimiset sana ayrıntı verdi mi?";
			link.l1 = "Hayır. Chad'den fazlasıyla korkuyor. Önce kendi güvenliğinin garanti altına alınmasını istiyor.";
			link.l1.go = "entrance_17";
		break;
		
		case "entrance_17":
			dialog.text = "Pekala. Rivados'a Chimiset'le görüşmek istediğimi söyleyelim. Bakalım ne diyecek. Bana yapılan suikast girişimine gelince... yapacak bir şey yok, sadece dikkatli olacağım.\nPeki, şimdi ne yapacaksın, "+pchar.name+"?";
			link.l1 = "Henüz özel bir şey yok. Adada dolaşıp yerlilerle tanışacağım – belki buradan nasıl çıkabileceğime dair bir fikir bulurum. Bir de Nathaniel Hawk'ı bulmam lazım, buraya gelme sebebim o.";
			link.l1.go = "entrance_18";
		break;
		
		case "entrance_18":
			dialog.text = "Tamam. Bu adadan kurtulmanın bir yolunu bulduğunda mutlaka yanıma uğra, sana rotalarımı ve seyir talimatlarımı vereceğim, böylece bir gemiyle buraya geri dönebilirsin. Ayrıca ihtiyacın olacak başka bilgiler de vereceğim.";
			link.l1 = "Pekala. Kesinlikle seni ziyarete geleceğim, Steve!";
			link.l1.go = "entrance_19";
		break;
		
		case "entrance_19":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			// прерывание на вызов к Акуле
			pchar.quest.LSC_GotoShark.win_condition.l1 = "Timer";
			pchar.quest.LSC_GotoShark.win_condition.l1.date.hour  = 9.00;
			pchar.quest.LSC_GotoShark.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l2 = "location";
			pchar.quest.LSC_GotoShark.win_condition.l2.location = "LostShipsCity_town";
			pchar.quest.LSC_GotoShark.function = "LSC_GotoShark";
			AddQuestRecord("SharkHunt", "21");
		break;
		
		case "entrance_20":
			dialog.text = ""+pchar.name+", kötü haber: Chimiset öldü ve Chad Kapper ortadan kayboldu.";
			link.l1 = "Lanet olsun! Demek Chad sonunda yaşlı büyücüyü öldürdü...";
			link.l1.go = "entrance_21";
		break;
		
		case "entrance_21":
			dialog.text = "Öyle görünüyor. Durum saat geçtikçe daha da kötüleşiyor. Black Eddie ile bir ateşkes ayarlamıştım, ama şimdi...\nArtık Rivados'la barış hayal oldu. Bu arada, Chimiset ölmeden önce onunla konuştuğunu öğrendiler ve seni de adamlarımdan biri sayıyorlar, bu yüzden onlardan uzak dur.";
			link.l1 = "Harika.";
			link.l1.go = "entrance_22";
		break;
		
		case "entrance_22":
			dialog.text = "Daha bitmedi. Adanın arabulucusu ve diplomatı Giuseppe Fazio’dan bir mektup aldım. Gece yarısı Caroline gemisindeki kamarasında beni bekleyeceğini yazmış.\nAyrıca, yalnız gelmem gerektiğini, hayatımın tehlikede olduğunu ve adamlarıma güvenemeyeceğimi söyledi.\nBu mantıklı aslında - Chimiset ekibimizde bir hain olduğu konusunda bizi uyarmıştı - ama yine de bu işte bir bit yeniği var. Gece yarısı, tek başıma...\nNormalde o şişko adam bana gelir. Senden yardım isteyeceğim, "+pchar.name+"Jan seni becerikli, cesur bir adam ve mükemmel bir dövüşçü olarak tanıttı. Gece yarısı yapılacak toplantıya beni senin götürmeni istiyorum.";
			link.l1 = "No need to ask, Steven; I'm in. I don't like this invitation either - it's almost certainly a trap.";
			link.l1.go = "entrance_23";
		break;
		
		case "entrance_23":
			dialog.text = "Belki. Umarım yanılıyorumdur ama hazırlıklı olmayı tercih ederim. Yanımda olmandan memnunum\nGece yarısı San Augustine'in ana güvertesine gel, Fazio'yu görmeye gideceğiz. Caroline'e yürümek kısa sürecek.";
			link.l1 = "Gece yarısı, öyleyse. Ve ben silahımı kuşanmış olacağım.";
			link.l1.go = "entrance_24";
		break;
		
		case "entrance_24":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			pchar.quest.LSC_GotoShark.win_condition.l1 = "Timer";
			SetFunctionTimerCondition("LSC_MeetingSharkAugustine", 0, 0, 1, false); // таймер
			AddQuestRecord("SharkHunt", "22");
		break;
		
		case "caroline":
			dialog.text = "Pekâlâ, "+pchar.name+", hadi vakit kaybetmeyelim. Şu şişko Fazio ne diyecek bakalım. Yanımdan ayrılma.";
			link.l1 = "Seninleyim, Steve. Silahını hazır tut...";
			link.l1.go = "caroline_1";
		break;
		
		case "caroline_1":
			DialogExit();
			sld = characterFromId("Dodson");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload25", "CarolineBank", "barmen", "bar2", "LSC_CarolineOpen", -1);
		break;
		
		case "caroline_2":
			dialog.text = "Şu şişman adam nerede? Nereye gitti? Misafirine böyle mi davranılır! Görüyor musun onu, "+pchar.name+"? Bilmiyorum.\nBelki de sandıklarını kontrol etmeliyiz, içinde olabilir... başka bir şey olmasa da, en azından uğraşımızın karşılığını alırız, ha-ha!";
			link.l1 = "Heh, dünyada kendini sığdırabileceği bir sandık olduğunu sanmam - sus! Steven! Bir şey duydum...";
			link.l1.go = "caroline_3";
		break;
		
		case "caroline_3":
			dialog.text = "... hazırlan, "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LSC_Caroline_DlgExit_3");
		break;
		
		case "caroline_5":
			dialog.text = "Vay canına! Başardık... Lanet olsun, yakaladılar sandım.";
			link.l1 = "Bu işten daha beter belalara da bulaştım, ama kabul etmeliyim, bu sefer tehlike gerçekten burnumuzun dibindeydi. Chimiset haklıymış: Chad bir hainmiş. Onlara komuta eden o kız da kimdi?";
			link.l1.go = "caroline_6";
		break;
		
		case "caroline_6":
			dialog.text = "Mary Casper, nam-ı diğer Kızıl Mary. Merhum Alan Milrow'un sevgilisi.\nChad'in neden burada olduğunu anlıyorum - benim yerime geçmek istiyordu - ama Mary burada ne arıyordu?";
			link.l1 = "Eğer Alan'ın sevgilisiyse, o zaman her şey açık: Onun ölümünün intikamını almak istemiş. Zavallı kız, Alan'ı öldüren adamla yan yana savaştığını fark etmemiş...";
			link.l1.go = "caroline_7";
		break;
		
		case "caroline_7":
			dialog.text = "Anlaşılan bu. Ah, Narwhal'lara bunun hesabını ödeteceğim! Onlara erzak satmayı keseceğim, açlıktan gebersinler!\nVe onlar ne yapabilir ki? Bize saldırırlarsa, San Augustine her kuşatmaya dayanır! Bunu çok pişman olacaklar. Fazio'nun o şişko kıçını da sandalyemin arkasındaki duvara çivileyeceğim!";
			link.l1 = "Steve, Steve, bekle! Ya... ya Narwhal'ların bununla hiçbir ilgisi yoksa? Chad senin korsanlarından biriydi, Narwhal'lardan değil. Alan'ı öldüren Chad'di, Chimiset'i öldüren de Chad'di, hakkındaki söylentileri yayan da oydu. Ya bütün bunların başlangıcı ve sonu Chad'se?";
			link.l1.go = "caroline_8";
		break;
		
		case "caroline_8":
			dialog.text = "... Kahrolasıca, "+pchar.name+", ama... belki de haklısın.\nPeki, sana borçlandım, bu yüzden bu işi araştırman için sana bir şans vereceğim. Eğer Narwhal'ların bu işte parmağı olmadığını kanıtlarsan, savaşı bitiririm.\nGüvenimi kazandın, artık ne yaparsan yap desteğim arkanda. Hâlâ bir gemim olsaydı, seni başçavuşum yapardım.";
			link.l1 = "Buradan çıktığımızda Kıyı Kardeşliği'nin liderliğini üstlenerek bana borcunu ödeyebilirsin. Git biraz dinlen, ben de bu kamarada başka ipucu var mı diye bakacağım – ve ben yokken sakın ölmeye kalkışma!";
			link.l1.go = "caroline_9";
		break;
		
		case "caroline_9":
			dialog.text = "Heh, aklımın ucundan bile geçmezdi. Birini gönderip şu cesetleri temizleteceğim. Yengeçler bu gece bayram edecek! (tükürür) Hoşça kal, dostum.";
			link.l1 = "İyi geceler.";
			link.l1.go = "caroline_10";
		break;
		
		case "caroline_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SanAugustineResidence", "sit", "sit1", "LSC_SharkReturnSit", 10.0);
			AddQuestRecord("SharkHunt", "24");
		break;
		
		case "narval":
			dialog.text = "Pekâlâ, "+pchar.name+" , yeni bir şey öğrendin mi?";
			link.l1 = "İntikamını bırakabilirsin, Steven. Narwhal tayfası sana karşı kurulan tuzağa karışmadı, Mary ve Caroline'da savaştığımız adamlar hariç - sanırım onları bize saldırmaya o ikna etti. Fazio ise sana davetiyeyi göndermeye mecbur bırakılmış. Kamrasında bulduğum bir mektup birçok şeyi açıklıyor. Oku bunu.";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "(okuyorum)... Hmm... tam da Fazio'nun yapacağı şey: kendi derisini kurtarmak. Demek ki başından sonuna kadar her şey Chad'in işiymiş...";
			link.l1 = "Hepsi de amiral olmak istediği için. Donald Greenspan'ı ziyaret ettim. Ne kendisinin ne de adamlarının sana karşı bir şey planladığına yemin etti.";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			dialog.text = "Ona güveniyor musun?";
			link.l1 = "Evet, biliyorum. Donald, Alan'ın cinayetinden seni aklayacak. Seninle bizzat görüşmeye ve her şeyi konuşmaya hazır.";
			link.l1.go = "narval_3";
		break;
		
		case "narval_3":
			dialog.text = "Good. Much as I love a dustup, a war at this stage would be pointless. Too many have died already, and the ones who set all this in motion are crab food.\nYou say Donald is ready to apologize? Fine, let's salvage what relations we can with the Narwhals; I think the Rivados are lost to us because of Chimiset.";
			link.l1 = "Bu, huzur bulabileceğin tek fırsat olabilir.";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			dialog.text = "Beni zaten ikna ettin. Donald'a söyle, onu görmeye ve barışmaya hazırım.";
			link.l1 = "Yoldayım.";
			link.l1.go = "narval_5";
		break;
		
		case "narval_5":
			dialog.text = "Bekle, "+pchar.name+" . İyi iş çıkardın ve karşılığını da iyi almalısın. Al, beş yüz dublon.";
			link.l1 = "Teşekkür ederim!";
			link.l1.go = "LSC_navy";
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You have received 500 doubloons");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("SharkHunt", "27");
			pchar.questTemp.Saga.SharkHunt = "find"; //флаг - покушение предотвращено
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "shark_16"; // ноду Дональду Гринспи
			SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
			AddSimpleRumourCityTip("They say that the Admiral respects you, mister...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are the Admiral's loyal friend. Is that true?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		// ----------------------------------------вариант M----------------------------------------------------
		case "mary":
			dialog.text = "Benim zindanım Tartarus'ta. Oraya gidip onu görebilirsin. Sana anahtarı vereceğim. Gardiyanımız Chad Kapper'la konuş--";
			link.l1 = "Bekle, Steven. Kapper hakkında bilmen gereken bir şey var...";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			dialog.text = "... Dinliyorum ...";
			link.l1 = "Bunu başka nasıl söyleyeceğimi bilmiyorum ama... Kapper seni öldürmeyi planlıyor.";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "... Arkadaşlarımdan birini hainlikle suçlamak için lanet iyi bir sebebin olsa iyi edersin.";
			link.l1 = "Sana her şeyi en başından anlatayım--";
			link.l1.go = "mary_3";
		break;
		
		case "mary_3":
			dialog.text = "Çabuk konuş.";
			link.l1 = "Su basmış ambar bölümünde kendime geldiğimde, gövdedeki bir delikten çıktım ve enkazlar arasında yüzerek çıkacak bir yer aradım. Sonunda, baş kısmındaki bir kapıdan geçebileceğim bir batık buldum. Orada kırmızı ceketli bir kızla iki sert herif arasında bir kavga vardı--";
			if (pchar.questTemp.LSC.Mary == "alive") link.l1.go = "mary_4"; // Мэри жива
			else link.l1.go = "mary_15";
		break;
		
		case "mary_4":
			dialog.text = "Birisi Kızıl Mary'yi öldürmeye mi çalışıyordu?";
			link.l1 = "Görünüşe göre öyle. Ona o alçakları temizlemesinde yardım ettim ve sonrasında ilginç bir sohbetimiz oldu... Söylesene Steve, kim bu 'Narwhals' ve 'Rivados'? Onlardan birkaç kez bahsetti.";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "Adalet Adası'nın ilk yerleşimcilerinden türeyen klanlar bunlar. Narwhal'lar çoğunlukla İngiliz, Hollandalı ve Fransız kökenli. Rivados'ların hepsi zenci.\nHer klanın bir lideri var ve her biri, yabancılara kapalı olan birkaç gemiden oluşan bir bölgeyi elinde tutuyor.\nNarwhal ya da Rivados bölgesine girmek için doğru parolaları bilmelisin, üstelik bu parolaları her hafta değiştiriyorlar.";
			link.l1 = "A-ah, anladım... peki Mary bir Narwhal mı?";
			link.l1.go = "mary_6";
		break;
		
		case "mary_6":
			dialog.text = "Evet. Peki, sana ne söyledi?";
			link.l1 = "Chad Kapper, senin yakaladığın sevgilisi Alan Milrow'u öldürdü. Sonra da cinayeti senin işlediğine dair bir söylenti yaydı. Mary'nin intikam arzusunu kendi çıkarları için kullanmaya çalıştı.";
			link.l1.go = "mary_7";
		break;
		
		case "mary_7":
			dialog.text = "Chad, Alan'ı mı öldürdü?! Ama neden?";
			link.l1 = "Suçu senin üzerine yıkmak ve Narwhal'ları sana düşman etmek. Kapper'ın nihai amacı seni ortadan kaldırıp Amiral olarak senin yerini almak. Mary, onun planına katılmayı ve sevgilisi olmayı reddetti, bu yüzden adamlarına onu öldürmelerini emretti.";
			link.l1.go = "mary_8";
		break;
		
		case "mary_8":
			dialog.text = "Bunların hepsini sana o mu anlattı?";
			link.l1 = "Evet. Yalan söylediğini sanmıyorum. Ayrıca bana Chad Kapper'dan bir mektup verdi. Zaten okudum. Al.";
			link.l1.go = "mary_9";
		break;
		
		case "mary_9":
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = " (okuyarak) ... Evet, bu kesinlikle Chad'in el yazısı. Kahretsin! İnanılmaz! Alçak herif! Hain!\nOnu kendi bağırsaklarıyla asacağım! Layton! Beş adam al ve--\nBir dakika... vazgeçtim, Layton. Dağılın! Bunu akıllıca halledeceğiz.\nRivadoslarla aramızı düzeltmek için bir yol arıyordum, belki de bu fırsattır.\nOnların büyücüsü Chimiset, buradaki hapishane Tartarus'ta tutuluyor. Rivadosların adamlarını kurtarmasına izin vereceğiz ve bu sırada Chad'i bizim için öldürecekler.\nLayton! Tartarus'a git ve üst güvertedeki tüm nöbetçilerimizi çek!"+pchar.name+", senin için önemli bir işim var. Rivados'un lideri Kara Eddie'yi bul ve onunla anlaşmaya çalış--";
			link.l1 = "Ben mi? Ama burada kimseyi tanımıyorum!";
			link.l1.go = "mary_10";
		break;
		
		case "mary_10":
			dialog.text = "Başlamak üzeresin, ilk olarak Eddie ile: o, tüm Rivados klanının başı.\nBizim adımıza diplomasi yürütecek en iyi adamsın. Korsanlarımdan hiçbiri Eddie ile görüşemezdi... ve dürüst olmak gerekirse, hiçbirinin de iyi konuşma yeteneği yok.";
			link.l1 = "(iç çeker) Peki, gidip şu... Kara Eddie'ye bakacağım.";
			link.l1.go = "mary_11";
		break;
		
		case "mary_11":
			GiveItem2Character(pchar, "key_capper");
			Log_Info("You have received 50 doubloons");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "gold_dublon", 50);
			dialog.text = "Şu anahtarı al ve ona ver. Tartarus'taki her kapıyı açar – Zenciler Chimiset'i kurtaracaklarsa buna ihtiyaçları olacak.\nAyrıca, şu elli dublonu da al. Tanışacağın bir diğer yerli ise Caroline'da arabulucu ve diplomat olan Giuseppe Fazio. Dublonları al ve bu haftanın Rivados bölgesine giriş şifresini satın al – Fazio, şifreler seçildikçe onları edinmeyi kendine iş edinmiştir.\nSonra, Koruyucu'ya git. Orası Kara Eddie'nin ikametgahı. Ona Chad Kapper'ın Narwhals'a katıldığını, artık benim emirlerimi dinlemediğini ve bugün Chimiset'i öldürmeye gittiğini söyle.\nAnahtarı ona ver, güçlü bir kuvvet toplamasını ve Tartarus'a saldırmasını söyle.\nBir taşla iki kuş vuracağız: Rivados bizi müttefikleri olarak görecek ve Kapper Zencilerin elinde ölecek. Her şeyi anladın mı?";
			if (pchar.questTemp.LSC.Mary == "alive")// Мэри жива
			{
				link.l1 = "Bence de, ama Koruyucu'yu ve Caroline'i nerede bulacağım?";
				link.l1.go = "mary_12";
			}
			else
			{
				link.l1 = "Dinle Steve, şu Rivados ve Narwhal'lar kim, bana anlat. Hâlâ onlar hakkında hiçbir şey bilmiyorum.";
				link.l1.go = "mary_12_1";
			}
		break;
		
		case "mary_12_1":
			dialog.text = "Adalet Adası'nın ilk yerleşimcilerinden türeyen klanlar bunlar. Narwhal'lar çoğunlukla İngiliz, Hollandalı ve Fransız kökenli. Rivados'ların hepsi zenci.\nHer klanın bir lideri var ve her biri, yabancılara kapalı olan kendi gemilerinden oluşan bir bölgeye sahip.\nNarwhal ya da Rivados bölgesine girmek için doğru parolaları bilmen gerek, üstelik bu parolaları her hafta değiştiriyorlar.";
			link.l1 = "Şimdi anladım. Peki Koruyucu'yu ve Caroline'i nerede bulabilirim?";
			link.l1.go = "mary_12";
		break;
		
		case "mary_12":
			dialog.text = "Evimden çık, halat köprüsünü geç ve sola dön. Orası Caroline olacak.\Koruyucu'ya ulaşmak biraz daha zor: köprüyü geçtikten sonra sağa dön ve Santa Florentina'ya git - tahta köprünün diğer tarafına.\nRivados askerlerini bul - dediğim gibi, hepsi siyahi. Şifreyi soracaklar. Yüksek sesle ve net bir şekilde söyle. Sonra Fury'ye gir ve kıç tarafından Koruyucu'ya geç.";
			link.l1 = "Pekala... Sanırım çözdüm.";
			link.l1.go = "mary_13";
		break;
		
		case "mary_13":
			dialog.text = "Pekâlâ, o zaman işine bak, dostum!";
			link.l1 = "Yakında döneceğim.";
			link.l1.go = "mary_14";
		break;
		
		case "mary_14":
			DialogExit();
			NextDiag.CurrentNode = "dodson_warwait";
			AddQuestRecord("SharkHunt", "32");
			sld = characterFromId("Eddy");
			sld.dialog.currentnode = "capper"; // ноду Эдди
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			pchar.questTemp.LSC = "mary_go"; //меняем флаг
		break;
		
		case "dodson_warwait":
			dialog.text = "Hâlâ burada mısın? Hemen Kara Eddie'yi gör!";
			link.l1 = "Yoldayım.";
			link.l1.go = "exit";
			NextDiag.TempNode = "dodson_warwait";
		break;
		
		case "mary_15":
			dialog.text = "Birisi Kızıl Mary'i öldürmeye mi çalışıyordu?.";
			link.l1 = "Adı bu muydu? Onu kurtarmaya çalıştım, ama saldırganlarından biri kılıç darbesiyle onu yaraladı.";
			link.l1.go = "mary_16";
		break;
		
		case "mary_16":
			dialog.text = "Kıza üzüldüm ama şaşırmadım. Mary her zaman baş belasıydı.\nPeki ya Chad? O benim başçavuşum.";
			link.l1 = "Senin lostromusun mu? Aa... şey, bak, şu mektubu oku. Kızın cesedinde buldum. Kapper hayatına kastetmeyi planlıyor, Steven.";
			link.l1.go = "mary_9";
		break;
		
		// Каппер сбежал
		case "Chad_escape":
			dialog.text = "Neredeydin sen?! Rivados'un büyücüsünü serbest bıraktığını duydum ama saatlerdir seni gören olmamış!";
			link.l1 = "Üzgünüm, Steven. Siyahiler beni Protector'da rehin tuttular, eğer onlara ihanet edersen kendilerini güvenceye almak için. Chimiset'i serbest bıraktılar, evet, ama Chad kaçtı.";
			link.l1.go = "Chad_escape_1";
		break;
		
		case "Chad_escape_1":
			dialog.text = "Lanet olsun! Bir zencinin beyaz adamın işini yapacağına asla güvenme... En basit işi bile berbat ediyorlar... Kahrolası Rivadolar!";
			link.l1 = "Chad Narwhal'ların arasında saklanıyor...";
			link.l1.go = "Chad_escape_2";
		break;
		
		case "Chad_escape_2":
			dialog.text = "Tabii ki anladı! Aptal değil ya – Rivados'un Tartarus'a benim yardımım olmadan giremeyeceğini biliyor! Şimdi bir köşeye çekilip gizlice plan yapacak.\nLayton! Nöbetçileri iki katına çıkar! Gözünüzü dört açın! Chad Kapper'ı cehenneme gönderen adama servet var!!";
			link.l1 = "Steven, ben gidiyorum. Belki Chad'i bulabilirim. Bir haberim olursa geri dönerim.";
			link.l1.go = "Chad_escape_3";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Chad_escape_3":
			DialogExit();
			if (pchar.questTemp.LSC.Mary == "alive") 
			{
				pchar.questTemp.Saga.SharkHunt = "mary_whiskey"; // к Мэри
				AddQuestRecord("SharkHunt", "34");
			}
			else
			{ // не уберег Мэри - допетривай сам, куда идти
				pchar.questTemp.Saga.SharkHunt = "trader_whiskey"; // флаг на магазин - поиск виски
			}
			NextDiag.CurrentNode = "Total_wait";
			// добавим немного атмосферы - уберем Акселя до утра
			sld = characterFromId("Axel");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "EsmeraldaStoreBig", "goto", "goto5");
			sld = GetCharacter(NPC_GenerateCharacter("AxelHelper", "citiz_52", "man", "man", 35, PIRATE, 1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 100, 100, "blade_21", "pistol4", "bullet", 200);
			sld.dialog.Filename = "Quest\LSC\OtherNPC.c";
			sld.dialog.currentnode = "AxelHelper";
			LAi_SetOwnerType(sld);
			ChangeCharacterAddressGroup(sld, "EsmeraldaStoreBig", "barmen", "stay");
			LAi_group_MoveCharacter(sld, "LSC_NARVAL");
			SetFunctionTimerCondition("LSC_AxelReturnStore", 0, 0, 1, false); // таймер на возврат Акселя
		break;
		
		case "whiskey":
			dialog.text = "Ne oldu, "+pchar.name+"? Şeytanın ta kendisi peşindeymiş gibi görünüyorsun!";
			link.l1 = "Bir varil viski aldın mı?";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "Hangi viski--?";
			link.l1 = "Bir fıçı viski mi aldın?!";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Sessini alçalt, adamım! Viski yok bende! Ne oldu?";
			link.l1 = "Tanrıya şükür, tam zamanında geldim... Chad Kapper, Axel Yost'tan bir fıçı Bushmills satın almış--";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "Bushmills mı? O benim en sevdiğim içkidir! Yıllardır içmemiştim!";
			link.l1 = "Yes-yes, and Kapper knows that; he asked his pal, Marcello Cyclops, to buy some arsenic from Sancho Carpentero. You get it now?";
			link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			dialog.text = "Beni zehirleyecekti...?";
			link.l1 = "Evet! Bu yüzden bu kadar acele ettim. Kahretsin, kalbim... Dinle, eğer biri sana bir fıçı viski getirirse, sakın içme! Zehirli olacak.";
			link.l1.go = "whiskey_5";
		break;
		
		case "whiskey_5":
			dialog.text = ""+pchar.name+"Uyarın için sağ ol, dikkatli olacağım - dur, şimdi nereye gidiyorsun?";
			link.l1 = "Kapper ve Cyclops'u bulmam lazım. Nerede olduklarını sanırım biliyorum. Yakında seninle tekrar konuşacağım!";
			link.l1.go = "whiskey_6";
		break;
		
		case "whiskey_6":
			DialogExit();
			pchar.questTemp.LSC.Dodson_warning = "true"; // Акула предупрежден
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "45");
		break;
		
		case "whiskey_7":
			dialog.text = "Ha! Aradığım adam tam da sendin! Görünen o ki, sana hayatımı borçluyum.";
			link.l1 = "Vişki geldi mi?";
			link.l1.go = "whiskey_8";
		break;
		
		case "whiskey_8":
			dialog.text = "Oldu! Bushmills, aynen dediğin gibi. Sevgili Fazio’muz çok nazikti – bana hediye olarak verdi. Elbette, onu hemen tutukladım.";
			link.l1 = "İtiraf etti mi?";
			link.l1.go = "whiskey_9";
		break;
		
		case "whiskey_9":
			dialog.text = "Öyleymiş. Kapper onu buna zorlamış, bana viskinin Narwhal'lardan bir hediye olduğunu söylemesini istemiş..";
			link.l1 = "Kapper öldü. Narwhal dostları da öyle. Şimdi geriye tek bir alçak kaldı - Marcello Cyclops... Fazio'nun onun nerede olduğunu bildiğine eminim. Biraz sıkıştırayım şunu!";
			link.l1.go = "whiskey_10";
		break;
		
		case "whiskey_10":
			dialog.text = "Buyur, ama onu öldürmemeye dikkat et, sevgili Fazio’muzun sağlığı pek iyi değil.";
			link.l1 = " Nazik olacağım... çoğunlukla.";
			link.l1.go = "whiskey_11";
		break;
		
		case "whiskey_11":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			chrDisableReloadToLocation = true;//закрыть локацию
			sld = CharacterFromID("Facio");
			LAi_CharacterEnableDialog(sld);
		break;
		
		case "poison":
			pchar.questTemp.LSC.Dodson_poison = "true"; // разговор состоялся
			dialog.text = "Argh... "+pchar.name+", dostum, benimle ilgili bir şeyler çok ters gidiyor...";
			link.l1 = "Steven! Bu viskiyi sen mi içtin?!";
			link.l1.go = "poison_1";
		break;
		
		case "poison_1":
			dialog.text = "Evet... Bushmills... Giuseppe Fazio bugün getirdi bana, Narwhal liderinden bir hediye olduğunu söyledi... barışın bir işaretiymiş...\nAh, lanet olsun, ne acıyor!";
			link.l1 = "O viski arsenikle zehirlenmişti!! Chad ve Cyclops yaptı bunu!";
			link.l1.go = "poison_2";
		break;
		
		case "poison_2":
			dialog.text = "Ah... sonunda beni yakaladı o herif...";
			if (CheckCharacterItem(pchar, "ultimate_potion"))
			{
				link.l1 = "Ölmeyeceksin! Duydun mu beni? Ölmeyeceksin! Çabuk, şu matarayı al. Bu, dünyadaki en güçlü iyileştirici iksir, her şeyi iyileştirir. Hemen iç... şimdi!";
				link.l1.go = "poison_3";
			}
			else
			{
				link.l1 = "Steven...!";
				link.l1.go = "dodson_poison";
			}
		break;
		
		case "dodson_poison": // Акула умирает
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			SetFunctionTimerCondition("LSC_SetDexterAdmiral", 0, 0, 1, false); // через день Декстера в адмиралы
			if (CheckAttribute(pchar, "questTemp.LSC.CapperDie_Aeva"))
			{
				AddQuestRecord("SharkHunt", "41");
				sld = CharacterFromID("Facio");
				sld.dialog.currentnode = "whiskey";
				sld.greeting = "facio_2";
				sld.quest.poisonnode = 1;
			}
			else AddQuestRecord("SharkHunt", "42");
			pchar.questTemp.Saga.DodsonDie = "true"; // атрибут Саге что Акула погиб
		break;
		
		case "poison_3":
			RemoveItems(pchar, "ultimate_potion", 1);
			Log_Info("Comanche potion was used");
			Log_Info("Poison was cured!");
			PlaySound("interface\notebook.wav");
			dialog.text = "Oh... "+pchar.name+", bu şey inanılmaz. Hâlâ biraz midem bulanıyor, ama acı neredeyse geçti...";
			link.l1 = "Bir Hintli şaman verdi bana. Hepsini iç, çabuk! İşte böyle...";
			link.l1.go = "poison_4";
		break;
		
		case "poison_4":
			LAi_SetStayType(npchar);
			dialog.text = "Bir mucize... Kendimi gayet iyi hissediyorum! Teşekkürler dostum... Bunu unutmayacağım!";
			if (CheckAttribute(pchar, "questTemp.LSC.CapperDie_Aeva"))
			{
				link.l1 = "Şimdi biraz dinlensen iyi olur. Ölüm gibi görünüyorsun. O alçak Kapper artık sana tehdit olamayacak – onunla ve birkaç Narwhal dostuyla ilgilendim. Sadece Marcello Cyclops kaldı. Viskiyi sana Fazio'nun getirdiğini söylemiştin, değil mi?";
				link.l1.go = "poison_5";
			}
			else
			{
				link.l1 = "Şimdi biraz dinlensen iyi olur. Sanki ölü gibisin. Viskiyi sana Fazio'nun getirdiğini mi söyledin?";
				link.l1.go = "poison_7";
			}
		break;
		
		case "poison_5":
			dialog.text = "Evet. Neden gergin göründüğünü merak etmiştim... sadece benim ulu varlığımın karşısında durduğu için sandım, he-he...";
			link.l1 = "Kapper onu buna zorlamış olmalı. Tamam, şimdi gidip o şişko domuzdan biraz bilgi alacağım. Dinlen şimdi, Steven!";
			link.l1.go = "poison_6";
		break;
		
		case "poison_6":
			DialogExit();
			sld = CharacterFromID("Facio");
			sld.dialog.currentnode = "whiskey";
			sld.greeting = "facio_2";
			sld.quest.poisonnode = 1;
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "40");
		break;
		
		case "poison_7":
			dialog.text = "Evet. Neden gergin göründüğünü merak etmiştim... Sadece benim yüce varlığımın karşısında durduğu için sandım, he-he...";
			link.l1 = "Kapper onu buna zorlamış olmalı. O şişko domuzu eninde sonunda yakalayacağım, ama şu anda Kapper ve Cyclops'la ilgilenmem gerek. Nerede saklandıklarını biliyorum. Dinlen şimdi, Steven!";
			link.l1.go = "poison_8";
		break;
		
		case "poison_8":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "43");
		break;
		
		case "clear":
			dialog.text = "Selam, "+pchar.name+"! Eva'da Kapper'la yaşadığın kavgayı duydum, ha-ha! Şaşırdım doğrusu! Chad'i ve adamlarını tek başına öldürmüşsün... Jan dövüş yeteneğin konusunda haklıymış.";
			link.l1 = "Kapper'la sadece hesaplaşmadım, aynı zamanda hayatına yönelik bir suikastı da engelledim. Zehirlenecektin, Steven. Ama merak etme, hallettim.";
			link.l1.go = "clear_1";
		break;
		
		case "clear_1":
			dialog.text = "Beni zehirlemek mi? Nasıl?";
			link.l1 = "Chad, Axel'den bir varil İrlanda Bushmills viskisi aldı--";
			link.l1.go = "clear_2";
		break;
		
		case "clear_2":
			dialog.text = "Bushmills mı? Bu en sevdiğim! Yıllardır içmemiştim!";
			link.l1 = "Ve Kapper bunu biliyordu. Dostu Marcello Cyclops'tan, Sancho Carpentero'dan biraz arsenik almasını istedi. Sonra arkadaşlarıyla birlikte Fazio'yu yakalayıp Eva'nın ambarına indiler. Viskileri zehirleyip, Fazio'ya bunu sana 'Narwhal'lardan bir hediye' olarak getirtmeye kalkışacaktı.";
			link.l1.go = "clear_3";
		break;
		
		case "clear_3":
			dialog.text = "Damn... it would've worked, too; I'd have drink a pint of that whiskey in a heartbeat.";
			if (CheckCharacterItem(pchar, "cask_whisky"))
			{
				link.l1 = "Chad buna güveniyordu. Ama başaramadı - içine arsenik bile koymaya vakti olmadı. Yani... Fıçıyı yanıma aldım. Bozulmamış halde, alabilirsin.";
				link.l1.go = "clear_4";
			}
			else
			{
				link.l1 = "Chad buna güveniyordu. Ama başaramadı - arseniği içine koymaya bile vakti olmadı.";
				link.l1.go = "clear_7";
			}
		break;
	
		case "clear_4":
			RemoveItems(pchar, "cask_whisky", 1);
			PlaySound("interface\notebook.wav");
			dialog.text = "Bana göster... "+pchar.name+", bu gerçek Bushmills! En iyi İrlanda viskisi! Ah, yıllardır bunun hayalini kuruyordum!\nSen, dostum... Kahretsin, tam bir mucize yaratıcısısın! Chad'i ortadan kaldırıyorsun, hayatımı kurtarıyorsun, bir de üstüne en sevdiğim viskinin bir fıçısını getiriyorsun, sanki hiçbir şey değilmiş gibi!\nBu, hak ettiği bir ödülü gerektirir.\n (karıştırıyor) Lanet olsun, nereye koymuştum...? Ha! Al, bunu al. Buna Thor'un Çekici derler, hiç tükenmez. Artık toplarının yüzünde patlamasından korkmana gerek yok! Topçun buna bayılacak!";
			link.l1 = "Tanrım, Steven... teşekkür ederim! Eminim öyle olacaktır.";
			link.l1.go = "clear_5";
		break;
		
		case "clear_5":
			GiveItem2Character(pchar, "talisman3"); 
			PlaySound("interface\notebook.wav");
			Log_Info("You have received a 'Thor's hammer' amulet");
			dialog.text = "Şimdi, izninle, bu muhteşem viskiyle biraz yakınlaşma vakti... "+pchar.name+", yarın yanıma gel. Bu arada, biraz düşünmem gerekiyor...";
			link.l1 = "Pekala, Steven, seni viskinden alıkoymayacağım, ha-ha!";
			link.l1.go = "clear_6";
			AddQuestRecord("SharkHunt", "53");
		break;
		
		case "clear_6":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			DeleteAttribute(pchar, "questTemp.LSC.Whiskey_clear");
			if (CheckAttribute(pchar, "questTemp.LSC.CyclopDie"))
			{
				SetFunctionTimerCondition("LSC_WhiskeyStoryFinal_1", 0, 0, 1, false); // адмирал зовет
				DeleteAttribute(pchar, "questTemp.LSC.CyclopDie");
			}
		break;
		
		case "clear_7":
			dialog.text = "Bana bütün bunları anlatarak bana iyilik ettin. Sözlerini ve Chad'in yaptıklarını düşünmem gerek... sonra seni çağıracağım.";
			link.l1 = "Seni bekliyor olacağım!";
			link.l1.go = "clear_6";
			AddQuestRecord("SharkHunt", "54");
		break;
		
		case "whyskey_final":
			dialog.text = "Ha, işte buradasın, "+pchar.name+" . Herkes burada olduğuna göre başlayabiliriz. Seni ve Layton'ı buraya çağırdım, durumu konuşup Narwhal'larla ne yapacağımıza karar vermek için.";
			link.l1 = " 'Narwhallar hakkında ne yapmalı?' derken ne demek istiyorsun?";
			link.l1.go = "whyskey_final_1";
		break;
		
		case "whyskey_final_1":
			dialog.text = "Ne demek, 'ne demek?' Chad, Narwhal'ların yardımıyla hayatıma kast etti.\nBunu açık bir saldırı olarak görüyorum. Buna sessiz kalamayız. Rivados'larla aramız iyi olduğu için şöyle yapalım diyorum...\nNegroes'larla ittifakımızı resmileştirip adamlarımızı toplayalım ve Narwhal'ları kökünden temizleyelim.\nSen, "+pchar.name+", yine bizim elçimiz olacaksın. Black Eddie ve Chimiset ile konuş, onları dostluk teklifimi kabul etmeye ikna et. Savaş planlarımızı Dexter hazırlayacak, adayı herkesten iyi tanır. Layton?";
			link.l1 = "";
			link.l1.go = "whyskey_final_2";
		break;
		
		case "whyskey_final_2": // перекидываем ноду Декстеру
			DialogExit();
			sld = characterFromId("Dexter");
			sld.greeting = "";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "whyskey_final_3":
			dialog.text = "No need to exterminate the Narwhals at the first stroke; we control the island's food.\nForce them to retreat to the San Gabriel, and we can pen them up and starve them. What do you say, "+pchar.name+"?";
			link.l1 = "Ne diyeyim? ... Şunu diyeyim ki, Narwhal’ları rahat bırakmalısın, Steven.";
			link.l1.go = "whyskey_final_4";
		break;
		
		case "whyskey_final_4":
			dialog.text = "... buraya gelmeden önce kafana bir şey mi çarptı? Chad'le savaşan adamların Narwhal tayfası olduğunu unuttun mu?";
			link.l1 = "Hepsini kastetmiyorum. Marcello Cyclops değildi. Aslında, Rivados'a sadıktı - sonuçta melezdi. Bence Chad'e katılan Narwhal'lardan sadece parayla satın alabildikleri ya da Alan Milrow'u öldürdüğüne dair yalanla kandırabildikleri vardı.";
			link.l1.go = "whyskey_final_5";
		break;
		
		case "whyskey_final_5":
			dialog.text = "Peki ne yapmamı öneriyorsun, tüm bunları görmezden mi geleyim?";
			link.l1 = "Ben diplomat rolümü oynayayım diyorum... ama Narwhals'ın başı Donald Greenspan ile. Beni dinler misin, Steven?";
			link.l1.go = "whyskey_final_6";
		break;
		
		case "whyskey_final_6":
			dialog.text = "... Devam et...";
			link.l1 = "Buraya geldiğimden beri Terkedilmiş Gemiler Şehri hakkında çok şey öğrendim. Kasaba halkı, adada sadece iki klan varken savaşların hiç bitmediğini açıkça söyledi. Korsanlarınızın gelişi adaya üçüncü bir güç getirdi ve ilk kez dengeyle birlikte huzur sağlandı. Ama Narwhal’lar ve Rivado’lar hâlâ güçlü ve bir zafer çok pahalıya mal olacak.";
			link.l1.go = "whyskey_final_7";
		break;
		
		case "whyskey_final_7":
			dialog.text = "";
			link.l1 = "Narwhal'ların yok edilmesinin bedeli, birçok korsan ve Rivados'un hayatına mal olacak. Ayrıca, Layton San Gabriel kuşatmasının uzun süreceğini söyledi ve eğer Rivados bu seferde çok fazla kaybettiklerini hissederlerse, geri çekilirler... hatta belki de bize karşı dönebilirler.";
			link.l1.go = "whyskey_final_8";
		break;
		
		case "whyskey_final_8":
			dialog.text = "";
			link.l1 = "Her iki klanın da hâlâ adayı ele geçirmeye hevesli olduğunu unutma, üstelik daha kısa bir süre önce sana karşı birleşmişlerdi. Bu savaş düşündüğün kadar çabuk ya da tahmin edilebilir şekilde sona ermeyebilir. Ve tüm bu kargaşanın ortasında sıradan insanlar var. Gerçekten bir mezarlığın hükümdarı olmak mı istiyorsun?";
			link.l1.go = "whyskey_final_9";
		break;
		
		case "whyskey_final_9":
			dialog.text = "... Bazı iyi noktalar söyledin... ama henüz beni ikna edemedin.";
			link.l1 = "I also need to leave the island somehow; I have to reach the idol of Kukulcan on the seabed. The Rivados can't help me... but maybe the Narwhals can. I've heard they have some smart, talented men among them. They won't help me if they're at war with me.";
			link.l1.go = "whyskey_final_10";
		break;
		
		case "whyskey_final_10":
			if (pchar.questTemp.LSC.Mary != "die") sTemp = "A-ha! I knew you had selfish reasons for wanting peace! And I guess that one of them is that redhead on the Ceres, eh, my friend? Am I right? Don't worry about her, "+pchar.name+", we'll find a safe place for her before the fighting starts.\n";
			else sTemp = "";
			dialog.text = ""+sTemp+" Ama madem bu kadar kararlısın, peki. Git ve Donald'ı bul. Evi Esmeralda'nın arka tarafında. Şu alçağın ne diyeceğini dinle bakalım.\nEğer onun ve tayfasının Chad'in oyununda parmağı olmadığına ikna olursan... barışı düşünebilirim.";
			link.l1 = "Teşekkür ederim, Steven. Eminim bu doğru bir karar.";
			link.l1.go = "whyskey_final_11";
		break;
		
		case "whyskey_final_11":
			DialogExit();
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "negotiations"; // ноду Гринспи
			sld = characterFromId("Dexter");
			LAi_SetHuberType(sld);
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "negotiations_wait";
			pchar.questTemp.LSC.Donald_enter = "true";
			AddQuestRecord("SharkHunt", "55");
		break;
		
		case "negotiations_wait":
			dialog.text = "Ama onu öyle kolayca paçayı sıyırmasına izin verme, ha! Sonuçta o çocuklar Chad'le birlikte onun adamlarıydı – hâlâ Narwhal’dılar! Çizmelerini yalatsın, pişmanlığını iyice göstersin!";
			link.l1 = "Yapacağım, yapacağım.";
			link.l1.go = "exit";
			NextDiag.TempNode = "negotiations_wait";
		break;
		
		case "peace":
			dialog.text = "Peki, Donald ile konuştun mu?";
			link.l1 = "Ben de konuştum, şüphelerimi doğruladı. Ne o, ne de tüm klan Chad'in planıyla ilgiliymiş. O işe karışan tüm Narwhal'ları Kapper toplamış. Çok öfkeli ve bana, Alan Milrow'un öldürülmesinde ve sonrasında yaşananlarda seni suçsuz gördüğüne dair söz verdi.";
			link.l1.go = "peace_1";
		break;
		
		case "peace_1":
			dialog.text = "Bütün bunları yüzüme karşı söylemeye hazır mı bakalım?";
			link.l1 = "İncil üzerine yemin ettiğini söyledi.";
			link.l1.go = "peace_2";
		break;
		
		case "peace_2":
			dialog.text = "Heh, vay canına... Demek gerçekten de suçlanacak tek alçak, hain lostromommuş...";
			link.l1 = "Buna tamamen inanıyorum, Steven. Bu savaşa ihtiyacımız yok, kimsenin yok. İşlerimiz için de hiç iyi olmaz.";
			link.l1.go = "peace_3";
		break;
		
		case "peace_3":
			dialog.text = "(masaya vurur) Tamam, anlaştık! Eğer Greenspan gelip kıçımı öperse, her şey affedilir... ve barış sağlanır.";
			link.l1 = "Ona hemen söyleyeceğim. Steven... Bu savaşı önlediğimize sevindim.";
			link.l1.go = "peace_4";
		break;
		
		case "peace_4":
			if (pchar.questTemp.LSC.Mary == "alive") sTemp = "Feel free to bring your Mary over to the San Augustine, I can set aside some quarters for the two of you.";
			else sTemp = "";
			dialog.text = "Bekle... "+pchar.name+",   Burada, bu lanet olası Adalet Adası'nda ortaya çıkmana gerçekten çok sevindim.\nJan mektubunda senden övgüyle bahsetmişti... ama senden beklediğim her şey fazlasıyla aşıldı.\nEğer tayfamda olsaydın... aslında! Buradayken sana Kapper'ın yerini teklif ediyorum. Tartarus'taki garnizonuma sen komuta edeceksin. "+sTemp+".";
			if (pchar.questTemp.LSC.Mary == "alive") link.l1 = "Hayır Steven, teşekkür ederim ama burada fazla kalmayacağım. Bu işi daha layık, güvenilir bir delikanlıya ver. Ve Mary'ye gelince... Ceres'te gayet iyiyiz.";
			else link.l1 = "Hayır Steven, teşekkür ederim ama burada fazla kalmayacağım. Görevi daha layık, güvenilir bir delikanlıya ver.";
			link.l1.go = "peace_5";
		break;
		
		case "peace_5":
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You have received 500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Senden daha layık ya da güvenilir birini düşünmek zor, ve ne dersen de, bu adadan kurtulmanın umduğun kadar kolay olacağını sanmıyorum.\nAma olsun. Şimdi, buradan ödülsüz çıkmana izin veremem, o yüzden sus ve şu beş yüz dublonu al.";
			link.l1 = "Teşekkürler!";
			link.l1.go = "LSC_navy";
			AddQuestRecord("SharkHunt", "57");
			pchar.questTemp.Saga.SharkHunt = "find"; //флаг - покушение предотвращено
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "negotiations_17"; // ноду Дональду Гринспи
			AddSimpleRumourCityTip("They say that the Admiral respects you, mister...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are the Admiral's loyal friend. Is that true?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		case "LSC_navy":
			dialog.text = "Şimdi işimize bakalım... Al şu deniz defterlerimi. İçlerinde, seni adaya sağ salim götürecek rotalar var.\nSakın kaybetme! Onlar olmadan, gemin kayalıklara oturur ya da fırtınalarda paramparça olur. Ve unutma, adaya ancak nispeten küçük bir gemiyle yaklaşabilirsin! Sandal, tartan, lugger, şon, daha büyüğü olmaz.\nBeni almaya geri döndüğünde, ben de seninle ve Svenson'la bu oyuna katılırım.\nŞu batık Hint putunun sana yardım edeceğine hâlâ inanmıyorum ama... Yolun açık olsun, dostum.";
			link.l1 = "Tanrı'ya değil, Steven, Kukulcan'a güvenmemiz gerek. Yeniden görüşene dek.";
			link.l1.go = "LSC_navy_1";
		break;
		
		case "LSC_navy_1":
			GiveItem2Character(pchar, "LSC_navigation_map");
			dialog.text = ""+pchar.name+"... return as quickly as you can. My storehouses are running low; soon there will be no provision at all. You know what armed, hungry men are capable of?";
			link.l1 = "Bazı fikirlerim var. Hoşça kal.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dodson_wait";
			AddQuestRecord("LSC", "5");
			// убираем квестовые предметы
			sld = ItemsFromID("key_capper");
			sld.price = 10;
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
		break;
		
		case "Dodson_wait":
			dialog.text = "Adadan kurtulmanın bir yolunu buldun mu, "+pchar.name+"?";
			link.l1 = "Henüz değil, Steven, hâlâ bunun üzerinde çalışıyorum.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dodson_wait";
		break;
		
		// --> информационный блок
		case "Total_wait":
			dialog.text = "Peki, neyin var, "+pchar.name+"? İlginç bir haberin var mı?";
			
			if (!CheckAttribute(npchar, "quest.items") && CheckAttribute(npchar, "quest.takeitems"))
			{
				link.l1 = "Steven, eşyalarımı geri vermeni istiyorum. Onlara el koymuştun.";
				link.l1.go = "Items";
			}
			if (!CheckAttribute(npchar, "quest.story"))
			{
				link.l2 = "Steven, bu ada hakkında bana daha fazla anlat.";
				link.l2.go = "Story_island";
			}
			if (!CheckAttribute(npchar, "quest.natan"))
			{
				link.l3 = "Emin misin, Hawk adada değil mi? Putun içinden geçtiğine göre burada olmalı.";
				link.l3.go = "Natan";
			}
			if (!CheckAttribute(npchar, "quest.whiteboy"))
			{
				link.l4 = "Beyaz Oğlan adında bir adamı tanıyor musun?";
				link.l4.go = "Whiteboy";
			}
			if (!CheckAttribute(npchar, "quest.ships"))
			{
				link.l5 = "Narwhal'lara ve Rivado'lara hangi topraklar ait?";
				link.l5.go = "ships";
			}
			if (!CheckAttribute(npchar, "quest.parol"))
			{
				link.l6 = "Kabilelerin gemilerine binmek için şifreleri nasıl öğrenebilirim?";
				link.l6.go = "parol";
			}
			if (!CheckAttribute(npchar, "quest.map"))
			{
				link.l7 = "Dinle, adanın bir haritası var mı?";
				link.l7.go = "map";
			}
			if (!CheckAttribute(npchar, "quest.blade"))
			{
				link.l8 = "Böylesine güzel bir pala sende var. Daha önce hiç böyle bir şey görmemiştim...";
				link.l8.go = "blade";
			}
			link.l9 = "Henüz bir sorum yok. Belki yakında...";
			link.l9.go = "exit";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Items":
			dialog.text = "Ah, evet! Onları tamamen unutmuşum... Eşyaların yukarıda, bir sandığın içinde. Alabilirsin, Layton seni durdurmaz.";
			link.l1 = "Teşekkürler!";
			link.l1.go = "exit";
			npchar.quest.items = "true";
			NextDiag.TempNode = "Total_wait";
			ref location = &Locations[FindLocation(pchar.location)];
			DeleteAttribute(location, "private1.key");
			for (i=1; i<=10; i++) // можно лезть в сундук
			{
				sld = characterFromId("SharkSoldInside_"+i);
				DeleteAttribute(sld, "watchBoxes");
			}
		break;
		
		case "Story_island":
			dialog.text = "This island is over a hundred years old; I've seen caravels on the outer ring whose keels must've been laid in 1550 or earlier.\nThere's a shoal beneath our feet that buttresses the wrecks that founder here, keeps them above water. And even though many ships rot to dust each year, storms and a powerful sea current bring more.\nJustice Island shits, eats, and grows like a thing alive.\nThe first settlers arrived here on de Betancourt's expedition, of which the San Augustine and Tartarus were part. The Tartarus carried a lot of black slaves in her hold, one of whom was a man named Pedro Rivados. He led an uprising against his Spanish captors which failed, and he was sentenced to a slow death: tied to a mast and left to cook in the sun.\nBut his attempt at freedom weakened de Betancourt's crews such that a second uprising succeeded, and they formed the Rivados clan in his honour.\nFearing Rivados dominance of the island, with their savage African ways, the white Christian settlers miraculously managed to rise above their various nationalities and united to form the Narwhal clan.\nHeh, few things'll make white men set aside their differences faster than the threat of playing second fiddle to Negroes.\nThe Narwhals have a lot of mercenaries, soldiers, officers and adventurers in their ranks. Year on year they gather supplies and selectively recruit new men from the shipwrecks that arrive here. You can see the results today: they are a disciplined, professional army - and that's been enough to curb Rivados ambitions about ruling the island.";
			link.l1 = "Adanın Karayipler'in geri kalanıyla bir bağlantısı var mı?";
			link.l1.go = "Story_island_1";
		break;
		
		case "Story_island_1":
			dialog.text = "Son on yıldır kimse gelmedi. Buradakilerin anlattığına bakılırsa, adanın çevresindeki hava değişmiş: fırtınalar sıklaşmış, akıntı daha da güçlenmiş.\nSanki bir gün, ada Karayipler'in geri kalanından tamamen kopmuş gibi.\nEskiden adalılar Küba korsanlarıyla ticaret yapar, batık gemilerden çıkardıkları altın ve değerli eşyalarla yiyecek satın alırlardı, ama on yıldır Adalet Adası'na tek bir korsan uğramadı.\nYani, geri dönebilen olmadı en azından.";
			link.l1 = "Hm. Demek ki Orman Şeytanı da Kara Papaz da haklıymış... Peki, insanlar fırsatları varken neden adadan ayrılmadı?";
			link.l1.go = "Story_island_2";
		break;
		
		case "Story_island_2":
			dialog.text = "Bazıları gitti, ama çoğu kalmak istedi. Birçoğu burada kendine bir yuva kurdu, bazıları ise burada doğdu ve başka bir hayat bilmiyor.\nBazı insanlar gitmek istiyor ama eski, alelacele birleştirilmiş teknelerle fırtına bölgesine açılmaya cesaret edemiyorlar.\nRivado'lara gelince... şey, onlar zenci, ve bildiğim kadarıyla dışarısı beyaz adamın dünyası. Burada kalmak istemelerine şaşırabilir misin?";
			link.l1 = "Ve neden buraya geldin, Dodson? Bir fırkateynin vardı, saygın bir korsandın--";
			link.l1.go = "Story_island_3";
		break;
		
		case "Story_island_3":
			dialog.text = "(slams the table) I was being hunted!!\nI was blamed for the murder of Blaze Sharp! By whom, or for what reason, I've no idea.\nSomeone made me a pawn in their game and I was surrounded by enemies, abandoned by my friends, so I had to leave Isla Tesoro and lay low.\nI'd known of this island for a long time, but I couldn't reach it on my frigate; she was too big to bypass the reefs. So, I traded her for a brig.\nI was attacked by the Narwhals and Rivados as soon as I got here - guess the only people Negroes and white men hate more than each other are pirates, he-he. They rowed longboats to my ship at night and fired her.\nWe blasted their tubs to matchwood with our cannons, but the fire did its work - my poor brig was burnt to her frames.\nWe got mad as hell and struck back: we stormed the San Augustine and showed them how corsairs fight! They couldn't hold her and showed us their cowardly backs.\nWe captured San Augustine and discovered that the whole island used her as their storehouse! Overnight, we became the most important clan on the island.\nNow, every fucking Justice Islander has to buy back their own food at a price we name, ha-ha-ha!\nWe also captured two of the clan leaders: Alan Milrow of the Narwhals and a Rivados voodoo man name of Chimiset. My mate Layton spent the next few days scouting the island and then we attacked the Tartarus, the old slave ship.\nNow we hold two vessels and the clans have to deal with us... or starve. Nowadays, we have something like peace, here.\nAs for the citizens... we sell food to them proper cheap - they didn't take up arms against us. Anyway, they seem to like the fact that we balance out the other two clans, somewhat.";
			link.l1 = "İnanılmaz... bu gerçekten etkileyici bir hikaye!";
			link.l1.go = "exit";
			npchar.quest.story = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Natan":
			dialog.text = "Onu görmedim. Hawk'ın Maroon Kasabası dışında bir yerde olduğuna dair ilk kez senden duyuyorum.\nAdada ya da dış halkada bir yerde saklanıyor olabilir – gizlenmek için yeterince yer var – ama şimdiye kadar gelip beni bulurdu diye düşünürdüm...";
			link.l1 = "Anladım...";
			link.l1.go = "exit";
			npchar.quest.natan = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Whiteboy":
			dialog.text = "Beyaz oğlan mı? Hm... hayır, bu ismi duymadım. Ama burada olmadığı anlamına gelmez - buradaki bütün ayaktakımıyla ilgilenmek benim işim mi sanki?";
			link.l1 = "Hayır, hayır. Peki, başkasına sorarım.";
			link.l1.go = "exit";
			npchar.quest.whiteboy = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "ships":
			dialog.text = "The island is divided between the Narwhals, Rivados and my pirates, with a neutral area between us.\nI control the San Augustine and Tartarus.\nRivados hold Protector, which is their leader's residence, Fury, their barracks, and Velasco, their warehouse. Strangers are forbidden to pass, you must say a special password in order to get there.\nNarwhals hold a lot of ships: Esmeralda is a shop and the residence of their leader; the San Gabriel and Phoenix, run by some kind of scientist; and the Ceres, their smithy.\nEvery ship except the Esmeralda is a restricted area; you must say a password before they let you in. Same goes for the Rivados. And the passwords change every week.\nThe rest of the ships are considered neutral territory, and are where the citizens live.\nWho am I forgetting...? Oh, the Fleuron is a tavern run by a man named Sancho Carpentero, and the Gloria is the local church - Brother Julian is the pastor there.";
			link.l1 = "Hatırlanacak çok şey var... Sanırım şehri gezerek öğrenmem gerekecek.";
			link.l1.go = "exit";
			npchar.quest.ships = "true";
			NextDiag.TempNode = "Total_wait";
			AddQuestRecord("LSC", "2");
		break;
		
		case "parol":
			dialog.text = "Klanlarla işbirliği yaparak. Ama Narwhal'lar için yeterince sert, Rivados için de yeterince kara değilsin, o yüzden git, Caroline adında eski bir fırkateyne uğra ve Giuseppe Fazio adında şişman bir herifi bul. Burada bir çeşit diplomat gibi takılıyor.\nAdam adaya gelmeden önce ne haltlar karıştırdı bilmiyorum ama tam bir düzenbaz. Herkesle iş yapar. Klanlar onu arabulucu olarak kullanıyor, bu yüzden haftalık şifreleri hep ona verirler.\nFazio tamahkârın teki, bir altın için kendini bile yer. Rivados ya da Narwhal bölgesinin güncel şifresini ondan isteyebilirsin ama altın ödemeye hazır ol.";
			link.l1 = "Caroline... Fazio... tamam, sağ ol.";
			link.l1.go = "exit";
			npchar.quest.parol = "true";
			NextDiag.TempNode = "Total_wait";
			AddQuestRecord("LSC", "3");
		break;
		
		case "map":
			dialog.text = "Dexter'ın bir tane var. O benim başyardımcım. Buraya gelir gelmez ayrıntılı bir harita çizdi. Yukarı çıkıp onunla konuş, belki sana satar.";
			link.l1 = "Anladım. Teşekkürler!";
			link.l1.go = "exit";
			npchar.quest.map = "true";
			NextDiag.TempNode = "Total_wait";
			sld = characterFromId("Dexter");
			sld.quest.map = "true";
		break;
		
		case "blade":
			dialog.text = "Ha! Narwhal klanının başı Alan Milrow'dan bir ganimet.\nNarwhal'ın demircisi Jurgen, onu denizin dibinde buldukları nadir bir demirden yaptı. Paslanmaz, asla körelmez ve tek bir savuruşta iki bedeni ortadan ikiye bölebilir.\nBu kılıç, bu seferden çıkan birkaç iyi şeyden biri ve bu yüzden onu hiçbir fiyata bırakmam.";
			link.l1 = "Jurgen böyle bir pala daha yapabilir mi?";
			link.l1.go = "blade_1";
		break;
		
		case "blade_1":
			dialog.text = "Pfft! Not likely. Jurgen is a Narwhal; he's loyal to his clan and never makes weapons for outsiders.\n Besides, you'd need some of that special iron to make a second sword. That iron can only be found at the bottom of the sea, and unless you've got gills, how are you going to reach it? So, forget about it.";
			link.l1 = "Anladım... yazık...";
			link.l1.go = "exit";
			npchar.quest.blade = "true";
			NextDiag.TempNode = "Total_wait";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive")
			{
				sld = characterFromId("Schmidt");
				sld.quest.narval_blade = "begin"; // возможность сделать 'Нарвал' для Мэри
			}
		break;
		// <-- информационный блок
		
		case "return":
			chrDisableReloadToLocation = true;//закрыть локацию
			dialog.text = ""+pchar.name+"! Seni deli herif, ha-ha-ha, başardın!! Ufukta yelkenlerini gördüm! Nasılsın dostum? Yolculuk nasıldı?";
			link.l1 = "Heh, seni de görmek güzel Steven. Hayattayım.";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "Güzel! Tanrı aşkına, bu adadan kurtulup Orman Şeytanı'yla bir kadeh paylaşmaya hazırım.\nLayton Amiral olarak kalacak - zaten yerime oturdu bile, ha-ha! Sanırım burayı gerçekten sevdi.";
			link.l1 = "Bir keresinde buraya gelen birçok kişinin dışarıdaki hayata göre buradaki yaşamı tercih ettiğini söylemiştin. Dexter'ın da farklı olmamasına şaşırdın mı?";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "Eh, şaşırdım diyemem... Sadece onu kaybettiğim için üzgünüm. Daha iyi bir birinci zabit bulamazdın.\nPeki... demir almaya ne zaman niyetlisin?";
			link.l1 = "Yakında. Gemime bin, Steven. Buradaki işimi bitirir bitirmez yelken açacağız.";
			link.l1.go = "return_3";
		break;
		
		case "return_3":
			dialog.text = "Kaptan sensin! Ah, güvertede ayaklarımın altında o sallantıyı tekrar hissetmek güzel olacak!";
			link.l1 = "...";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LSC_SetDodsonPassenger", -1);
		break;
		
		case "return_5":
			dialog.text = "Blueweld... garip... bir yanım bir daha asla yeşil ağaçları ve tarlaları göremeyeceğimi düşünmüştü...\n...\n ... Öhöm, şey... Ben Svenson'a bakayım. Sen de onunla konuş, geleceği konuşun. Sıcak günler bekliyor bizi, ha?";
			link.l1 = "Şüphesiz, Steven. Rüzgarın hep arkanda olsun!";
			link.l1.go = "return_6";
		break;
		
		case "return_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseS1", "none", "", "", "OpenTheDoors", -1);
			sld = ItemsFromID("LSC_navigation_map");
			sld.price = 1000; // лоцию можно выкладывать 270912
			sld = ItemsFromID("keys_skel");
			sld.price = 3000; // отмычки можно выкладывать 270912 
			pchar.questTemp.LSC.Dios = "true"; // можно отдать лоцию Диосу
			CloseQuestHeader("LSC"); // 280313
		break;
		
		// Тени прошлого
		case "shadows":
			dialog.text = "Elbette, elimden geleni yaparım! Devam et.";
			link.l1 = "Steve, bir bak... Bir köpekbalığı dişi. Sakın bana bunun sana yabancı olduğunu söyleme!";
			link.l1.go = "shadows_1";
		break;
		
		case "shadows_1":
			RemoveItems(pchar, "shark_teeth", 1);
			dialog.text = "Ha! Doğru söyledin, bu diş bana ait – ya da daha doğrusu, bir kızı etkilemek için öldürdüğüm bir köpekbalığının dişi. Bu yüzden bana 'Köpekbalığı' Dodson derler.\nAz kişi basit bir pala ile suyun altında böyle bir şeyi başarabilir, ama ben genç ve deliydim, Beatrice Sharp ise Karayipler'in en güzel kızıydı...\nSen bunu nasıl aldın?";
			link.l1 = "A former executioner of St. John's gave it to me. A man was butchered with it; his name was Joshua Leadbeater.";
			link.l1.go = "shadows_2";
		break;
		
		case "shadows_2":
			dialog.text = "Mm-hmm, you've found your butcher; I cut his throat with this tooth.\nI was heartbroken by Beatrice's death, and I believed Leadbeater to be the only guilty man within my reach.\nI found some papers on him after he'd gurgled his last that clarified a few things. He had every right to crave revenge.\nBlaze's sister was just in the wrong place at the wrong time. Mask shouldn't have been blamed for her death - he was only interested in Butcher. Truthfully... I regret murdering him.\nThat bitch Jessica set the whole thing up.";
			link.l1 = "Hâlâ o belgeler sende mi?";
			link.l1.go = "shadows_3";
		break;
		
		case "shadows_3":
			dialog.text = "Elbette hayır. Onlara ihtiyacım yoktu. Ama istersen, Mask'ın neden Kasap'ın peşinde olduğunu anlatabilirim.";
			link.l1 = "Evet, fazlasıyla. Hadi, bana mürekkep ve bir tüy kalem ver de hepsini yazayım.";
			link.l1.go = "shadows_4";
		break;
		
		case "shadows_4":
			dialog.text = "Tabii. O zaman dinle. Joshua Leadbeater, İngiliz donanmasında Neptune adlı firkateynin kaptanıydı, ki o gemi sonradan efsaneye dönüştü...";
			link.l1 = "...";
			link.l1.go = "shadows_5";
		break;
		
		case "shadows_5":
			DialogExit();
			SetLaunchFrameFormParam("One hour later...", "Saga_FinalLedbitterStory", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shadows_6":
			AddQuestRecordInfo("Mask", "1");
			dialog.text = "... ancak Leadbeater hayatta kaldı ve yoldan geçen bir gemi tarafından kurtarıldı - fakat yaraları yüzünden tanınmaz hale gelmişti.\nO günden beri maske takıyordu ve başına gelen felaketlerin sorumlusunu bulup cezalandırmak hayatının amacı olmuştu.";
			link.l1 = "Anladım... peki, sanırım her kelimeyi not ettim. Sonra tekrar okuyacağım. Üzücü bir hikaye. Jessica'yı tanıyor muydun?";
			link.l1.go = "shadows_7";
		break;
		
		case "shadows_7":
			dialog.text = "Sure! She accompanied Butcher on all his voyages until he dumped her for Beatrice. Jess never forgave him.\nThey called her Butcher's talisman, because as long as she was with him, she brought him luck.\nAs soon as he left her on Barbados, his business went bad; the booty dried up and the Neptune became a frequent guest at the Isla Tesoror shipyard. Though that can be better explained by the fact that Butcher spent all his time in his cabin with Beatrice instead of on his quarterdeck.\nBeatrice wasn't like Jessica: she didn't crave adventure and battle- though Nicolas taught her fencing and seamanship. She was a romantic, wasn't hard enough to be a pirate.\nThis life wasn't for her, and in the end, it killed her.";
			link.l1 = " Peki ya Jessica? ";
			link.l1.go = "shadows_8";
		break;
		
		case "shadows_8":
			dialog.text = "Oh, she was something! Every sailor on the Neptune obeyed her orders without question, and not just because she was the captain's girl.\nJess was a master fencer and navigator - learned everything she knew from Butcher, and even exceeded him. She was tough and fearless, and blessed with looks that would make angels blush.\nA lot of men wanted her, but she only wanted Butcher. Chasing her was risky; she was likely to reward unwanted interest with a free fencing lesson, and for many, it was the last they ever received.\nJess owned a very special sword, the only one of it's kind in the Caribbean. I have no clue where she got it. The flame-bladed sword. The slightest touch of its blade leaves the most terrible wound.\nJess was an adventurer - not by birth, but by vocation. If you want to learn more about her, there's a friend of yours can tell you much more about her than.";
			link.l1 = "Gerçekten mi? Ve o adam kim?";
			link.l1.go = "shadows_9";
		break;
		
		case "shadows_9":
			dialog.text = "Jan Svenson.\nOld Forest Devil will never admit it, but he had plans for Jessica. This was just after he'd claimed the Spanish Main for himself and his fame was known throughout the Caribbean, so he figured the tigress was as good as his.\nAfter Butcher got rid of Jess, Jan started visiting Barbados on a regular basis. That set the Englanders' nerves on edge; as you know, Jessica was the daughter of a Bridgetown planter.\nWe all knew what he intended, and we knew it could end very badly, but we didn't say anything. Jan may sit on his arse in Blueweld these days, but speak the slightest ill of him back then and he'd turn up at your door with a poison blade and a band of hard buccaneers, he he...\nJan's plans came to naught: Jess couldn't live with the way Butcher treated her, so she took her revenge a year later with a help of Mask.\nIn the end, her vengeance destroyed her, along with Mask, Beatrice, and Butcher.";
			link.l1 = "Kasap hâlâ hayatta.";
			link.l1.go = "shadows_10";
		break;
		
		case "shadows_10":
			dialog.text = "... Saçmalık...";
			link.l1 = "Steven, Kaptan Butcher hâlâ hayatta. Jacob Jackman ve Cellat Henry celladı ziyaret etti. İdam sahteydi. Kanıtım var.";
			link.l1.go = "shadows_11";
		break;
		
		case "shadows_11":
			dialog.text = "Sahteymiş... Peki, Kasap şimdi nerede?!";
			link.l1 = "He calls himself Lawrence Beltrope now, and he lives in Port Royal. He's still dangerous though; Jackman, who caused so much trouble for the Brethren, was acting under Butcher's command.";
			link.l1.go = "shadows_12";
		break;
		
		case "shadows_12":
			dialog.text = "Lanet olsun! Sonunda çeyrekbaşı kaptanına kavuşmuş!\nBeltrope diyorsun... dur! Şimdi anladım neden Blaze'in evrakları arasında tuhaf bir sorgu kaydı vardı... Görünen o ki Blaze de Kasap-Beltrope'u bulmuş...";
			link.l1 = "Ne diyorsun?";
			link.l1.go = "shadows_13";
		break;
		
		case "shadows_13":
			dialog.text = "Bu eve yerleştikten sonra, Blaze’in eski evraklarını karıştırdım. Samuel Brooks adında birinin sorgusuna dair bir kayıt buldum.\nOrada ‘Thomas Beltrope’un maceraları’ndan bahsediliyordu ve onun bir korsan olduğu, ayrıca Nicolas Sharp’ın yakın dostu olarak bilindiği yazıyordu!\nGörünüşe göre Thomas, Butcher’ın babasıymış.";
			link.l1 = "İlginç... Görünüşe bakılırsa Sharp ve Beltrope'un çocukları, aile mesleğini sürdürmüş...";
			link.l1.go = "shadows_14";
		break;
		
		case "shadows_14":
			dialog.text = "Öyle görünüyor... Ama söyle bakalım dostum, ölülerin yaptıklarıyla neden bu kadar ilgileniyorsun?";
			link.l1 = "Bana belgeler lazım - Helen MacArthur'un Beatrice Sharp'ın kızı olduğunu ve onun mirası üzerindeki tüm haklara sahip olduğunu kanıtlayan belgeler. Helen'in aynı zamanda Beltrope'un kızı olması umurumda değil.";
			link.l1.go = "shadows_15";
		break;
		
		case "shadows_15":
			dialog.text = "Ne Leadbeater'ın evraklarında ne de Blaze'in arşivlerinde Helen MacArthur hakkında hiçbir şey yok.\nBeatrice'in, Blaze'e yeğeninin doğumunu söylememesi tuhaf, ona hiç benzemiyor...";
			link.l1 = "Dinle, belki Sharp'ın evraklarında başka bir şey vardır? Her ayrıntıya ihtiyacım var!";
			link.l1.go = "shadows_16";
		break;
		
		case "shadows_16":
			dialog.text = "Hm, I guess... According to Blaze's notes, he'd been trying to find the island where his sister died.\nThere're papers concerning Leadbeater's punitive expedition... Nothing interesting, except for latitude numbers.\nThis parallel crosses the northern Caribbean sea. But there's no longitude.\nObviously, Blaze's search failed; you can't imagine how many small islands there are along that latitude.";
			link.l1 = "Söyle bana sayıları.";
			link.l1.go = "shadows_17";
		break;
		
		case "shadows_17":
			dialog.text = "Bakalım... işte burada: enlem 21 derece 32 dakika Kuzey.\nAma boylamı olmadan ne işe yarar ki, anlamıyorum.";
			link.l1 = "Bunu bana bırak. Hikayeni paylaştığın için teşekkürler, Steven. Bir dahaki sefere kadar!";
			link.l1.go = "shadows_18";
		break;
		
		case "shadows_18":
			DialogExit();
			pchar.questTemp.Saga.Shadows = "jessika";
			AddQuestRecord("Shadows", "6");
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "First time";
			sld = characterFromId("Svenson");
			sld.quest.jessika = "true";
			// рифы доступны для посещения
			i = FindIsland("RockIsland");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			// для любителей самостоятельно добавлять локаторы
			LAi_LocationDisableOfficersGen("Shore67", true);//офицеров не пускать
			// и сразу прерывание
			pchar.quest.Saga_Jess_Island.win_condition.l1 = "location";
			pchar.quest.Saga_Jess_Island.win_condition.l1.location = "Shore67";
			pchar.quest.Saga_Jess_Island.function = "Saga_JessikaIsland"; 
			// активируем квест хронометра Алекса
			pchar.questTemp.AlexClock = "dodson"; // 280912
		break;
		
		// суп из черепахи
		case "terrapin":
			dialog.text = "You could say that. Now, about Tortuga.\nThe island was named such because it resembles a turtle. Well, Levasseur's been thickening turtle's shell for twelve years.\nHis crowning achievement is Fort La Roche. A frontal attack is suicidal; the fort's heavy cannons can smash even ships-of-the-line.\nMaking a soup out of this beauty won't be easy. The Spanish have been trying for a very long time and they've not yet succeeded.";
			link.l1 = "Svenson bana Levasseur'u alt etmemde yardım edeceğine söz verdi. Senin bir planın olacağını söyledi, peki nedir o?";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "I've had men walking the streets of Tortuga for the last few weeks and they've obtained a lot of interesting information. I have good news for you, pal: it seems you won't have to face the cannons of La Roche. We're not the only ones fed up with Levasseur; he has friends who want him dead.";
			link.l1 = "Devam et...";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "Levasseur'un genç kızlara düşkün olduğu herkesçe bilinir. Eğlencesini yaşadıktan sonra, o kızlar ortadan kaybolur.\nTortuga'daki köle ticaretinin başlıca tedarikçisi, Voltigeur adlı kalyonun sahibi Robert Marten'dir. Onun yardımcısı, Levasseur'un yeğeni Henri Thibaut, limandaki en güzel kızları patronu için seçer.\nKısa süre önce, Marten İngiliz bir brigden Molly Jones adında bir güzeli ele geçirdi. Onu gece vakti, Tortuga'daki gizli bir mağarada Levasseur'un yeğeni Thibaut'ya teslim etti.\nMürettebata, kızın kalp krizinden öldüğü ve cesedinin denize atıldığı söylendi; tabii o ceset muhtemelen, para verip sonra öldürdükleri zavallı bir liman fahişesine aitti.\nSonuç olarak, Marten ve Thibaut Molly'yi Levasseur'a vermek yerine kendilerine saklamaya karar vermiş gibi görünüyor. Levasseur bunu öğrenirse, ortalık fena karışacak.";
			link.l1 = "Are you sure we can exploit this? I'm sure Marten and Thibaut realize the risk they're running; they'll have taken precautions.";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			dialog.text = "Doğru. Ama her zincirin zayıf bir halkası vardır.\nÜç gün önce, Voltigeur'un eski tayfasından Fernand Lucas, Basse-Terre'deki meyhanede fazla içip ağzından ilginç laflar kaçırdı...\nMeğerse Molly Jones, ona St John's'taki kardeşinden yardım istemesini söylemiş. Ama Lucas ona hiç ulaşamamış.\nKaptanından kaçıp şimdi Guadeloupe'ta korkaklığını unutmak için içiyor.\nAntigua Fransız korsanları için güvenli bir yer değil - bunu aklında tut! Albay Fox, karısı bir Fransız korsanının elinde öldükten sonra adadaki her palmiye ağacına bir korsan asacağına yemin etti ve denizcileri de bu isteğini gerçekleştirmek için ellerinden geleni yapacaklar.";
			link.l1 = "Kendine gel, Steven... Marten ve Thibaut hakkında anlat bana. Neden böyle bir riske girdiler? Molly'nin cazibesi bu kadar mı güçlüydü, yoksa bu köle tacirleri bir kereliğine merhamet mi gösterdi?";
			link.l1.go = "terrapin_4";
		break;
		
		case "terrapin_4":
			dialog.text = "I know that scum Marten very well. If he's taking this risk, that means there's either gold or self-preservation involved.\nMaybe Marten thinks he can get a huge ransom for her - which is unlikely; the girl arrived on Tortuga in servant's garb.\nOr maybe... Ha! I wonder who Marten would be more afraid of than Levasseur...?";
			link.l1 = "Hmm... Thibaut hakkında biraz daha anlat.";
			link.l1.go = "terrapin_5";
		break;
		
		case "terrapin_5":
			dialog.text = "Adam hakkında fazla bir şey bilmiyorum, sadece Levasseur'un ona o kadar güvendiğini ve onu varisi yaptığını biliyorum.\nKızın nerede tutulduğu ve Thibaut'nun Marten'e neden bu kadar serbestlik tanıdığı belli değil, ama bu küçük bilmecenin cevabı, Tortuga'yı basmadan bu oyunu kazanmamıza yardımcı olabilir. Sen Fransızsın, bu yüzden böyle tercih edeceğini düşündüm.\nAma acele etmelisin, Lucas'ın sarhoş saçmalıkları ne zaman Tortuga'ya giden bir gemiye ulaşır, kimse bilemez; eğer Levasseur bundan biz harekete geçmeden önce haberdar olursa... yandık!";
			link.l1 = "Hemen ayrılıyorum.";
			link.l1.go = "terrapin_6";
		break;
		
		case "terrapin_6":
			dialog.text = "Here's what you do: visit Antigua first. Molly sent Lucas there to find her brother; maybe the brother has information that can help you.\nAfter that, get your arse to Guadaloupe. Find Lucas and learn everything you can about Marten, Thibaut, Voltigeur, and Molly.";
			link.l1 = "Teşekkürler, Steven. Önce Antigua, sonra Guadeloupe.";
			link.l1.go = "terrapin_7";
		break;
		
		case "terrapin_7":
			DialogExit();
			AddMapQuestMarkCity("SentJons", true);
			AddMapQuestMarkCity("BasTer", true);
			AddQuestRecord("Terrapin", "1");
			pchar.questTemp.Terrapin = "baster";
			pchar.questTemp.Terrapin.SJ_count = 0;
			// прячем Фокса
			sld = characterFromId("Fox");	
			ChangeCharacterAddressGroup(sld, "none", "", "");
			// садим в таверну Робера Мартэна
			float fMft = MOD_SKILL_ENEMY_RATE/10;
			sld = GetCharacter(NPC_GenerateCharacter("Rober", "Marten", "man", "man", 30, FRANCE, -1, true, "quest"));
			FantomMakeCoolSailor(sld, SHIP_GALEON_L, "Voltigeur", CANNON_TYPE_CANNON_LBS20, 90, 90, 90);
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_19", "pistol5", "bullet", 150);
			sld.name = "Rober";
			sld.lastname = "Marten";
			sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
			sld.dialog.currentnode = "Rober";
			sld.greeting = "pirat_common";
			TakeNItems(sld, "potion2", 1);
			TakeNItems(sld, "potion3", 2);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "BladeDancer");
		
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterPerk(sld, "LongRangeGrappling");
			SetCharacterPerk(sld, "GrapplingProfessional");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "CriticalShoot");
			SetCharacterPerk(sld, "LongRangeShoot");
			SetCharacterPerk(sld, "BasicBattleState");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "Doctor1");
			SetCharacterPerk(sld, "Doctor2");
			sld.MultiFighter = 1.0+fMft; // мультифайтер
			LAi_SetSitType(sld);
			UpgradeShipParameter(sld, "SpeedRate");//апгрейдить скорость
			UpgradeShipParameter(sld, "TurnRate");//манёвренность
			FreeSitLocator("Baster_tavern", "sit1");
			ChangeCharacterAddressGroup(sld, "Baster_tavern", "sit", "sit1");
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Terrapin_LateBaster", 0, 0, 20, false); // таймер
			}
			else SetFunctionTimerCondition("Terrapin_LateBaster", 0, 0, 10, false); // таймер
			
			// Квест "Погасшая Звезда" провалена, всё удаляем
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway"))
			{
				CloseQuestHeader("PZ");
				DeleteAttribute(pchar, "questTemp.PZ_Etap5_Start");
				DeleteAttribute(pchar, "questTemp.PZ_Etap4_Start");
				DeleteQuestCondition("PZ_Etap5_Start");
				DeleteQuestCondition("PZ_LongwayCapstervilleDialog");
				DeleteQuestCondition("PZ_OhotaNaZvezdu_Kapstervil");
				DeleteQuestCondition("PZ_OhotaNaZvezdu_Yamaika");
				DeleteQuestCondition("PZ_Beliz_PoterpKrushenie");
				pchar.questTemp.PZ_ProvalFinal = true;
			}
		break;
		
		case "terrapin_8":
			dialog.text = "Devam et!";
			link.l1 = "St. John's'ta Molly'nin kardeşini buldum. O, Albay Fox'un katibiymiş. Ama bir tuhaflık var... Kız kardeşi Molly'yi senin boylarında, ama senin kadar güzel olmayan, herkesin tanıdığı bir cadı olarak tarif etti. Molly, Fox'un kızı Catherine'in hizmetçisiymiş ve yakın zamana kadar onunla birlikte İngiltere'deymiş...";
			link.l1.go = "terrapin_9";
		break;
		
		case "terrapin_9":
			dialog.text = "";
			link.l1 = "Catherine ise, gerçekten güzelliğiyle tanınır ve babasını doğum gününde ziyaret etmeye gidiyordu, fakat onu taşıyan filo gecikti...";
			link.l1.go = "terrapin_10";
		break;
		
		case "terrapin_10":
			dialog.text = "";
			link.l1 = "Albay Fox, ona İngiltere'den bir refakat filosu olmadan ayrılmasını yasakladı, bu yüzden Molly Jones Thibaut'nun esiri olamaz. O halde o kim...?";
			link.l1.go = "terrapin_11";
		break;
		
		case "terrapin_11":
			dialog.text = "Hm... Kim bilir lanet olsun. Belki de başka bir Molly Jones'tur bu - senin sorduğun kişi değildir.\nAma... tesadüfler fazla. Bunun tamamen bir rastlantı olduğuna inanmıyorum!\nBiliyor musun... Bir şüphem var ama...";
			link.l1 = "Ne demek istiyorsun? Söylesene!";
			link.l1.go = "terrapin_12";
		break;
		
		case "terrapin_12":
			dialog.text = "... Ya Catherine babasının emirlerine karşı gelip korumasız denize açıldıysa? Geçen ay epey fırtınalıydı, Albatross hasar almış olabilir ve Marten için kolay av haline gelmiştir.\nSanırım Catherine gerçek adını Marten'den gizledi - nedenini anlayabilirsin - ve onun yerine Molly'nin adını verdi!";
			link.l1 = "Lanet olsun! Eğer durum buysa, her şey yerine oturuyor... ama bu gerçekten deli bir varsayım!";
			link.l1.go = "terrapin_13";
		break;
		
		case "terrapin_13":
			dialog.text = "Ben de tam bunu demek istiyorum, dostum. Yanılıyor olabilirim ama...";
			link.l1 = "... ama eğer doğruysa, her şey değişir! İngilizlerden destek isteyebiliriz, Deniz Tilkilerinin süngüleri bize yol açar!";
			link.l1.go = "terrapin_14";
		break;
		
		case "terrapin_14":
			dialog.text = "Sakin ol, "+pchar.name+"! We need proofs. As I said, I could be wrong, and Catherine could still be in London, waiting for an escort to set sail.\nThe English have problems of their own; they won't risk attacking La Roche. But if we're right, and Colonel Fox finds out what's happened to his daughter...\nHe'll set up a blockade around Tortuga and wait for reinforcements. Then he'll attack the city. Sea Foxes are fearsome in close-quarters, so there'll be lots of casualties - army and civilian.\n And in the end, I'm sure he'll raise the English flag above the ruins of Tortuga three days later. Do you really want that?";
			link.l1 = "Hayır... hayır, bilmiyorum. Şimdi Marten'ın bahsettiği fidyenin ne olduğunu anlıyorum.";
			link.l1.go = "terrapin_15";
		break;
		
		case "terrapin_15":
			dialog.text = "Dikkatli olmalıyız. Marten'in Catherine'in gerçek kimliğinden haberi olduğundan bile emin değiliz. Albay Fox'u şantajla tehdit etmek intihar olurdu, hele Cromwell'in filosu Karayipler'e geliyorken.\nEğer Catherine bizim yüzümüzden ölürse, başımız büyük belaya girer. Albay Fox, kızını öldürdüğümüze inanırsa Sahil Kardeşliği'ni yerle bir edebilir.\nAma sonunda Catherine'in ölmesi gerekirse, bunun bizim işimiz gibi görünmemesine ve onun da bize amaçlarımıza ulaşmada yardımcı olmasına dikkat etmeliyiz.\nEn iyi sonuç, kızı babasına teslim etmek olurdu. Onun kurtarıcısı iyi bir ödül alır, he-he...";
			link.l1 = "Steven, sen bir dahisin! Ben Tortuga'ya gidiyorum. Molly'nin Catherine Fox olup olmadığını doğrulayacağım.";
			link.l1.go = "terrapin_16";
		break;
		
		case "terrapin_16":
			dialog.text = "Zaman kaybetme, "+pchar.name+". Ve eğer haklı çıkarsam, o kızın hayatta kalmasını sağla.";
			link.l1 = "Elimden gelen her şeyi yapacağım.";
			link.l1.go = "terrapin_17";
		break;
		
		case "terrapin_17":
			DialogExit();
			AddQuestRecord("Terrapin", "7");
			pchar.questTemp.Terrapin = "tortuga1";
			pchar.questTemp.Terrapin.Room_close = "true": // не пускать в комнату таверны
		break;
		
		case "guardoftruth":
			dialog.text = "Ho-Ho! Söyle bakalım, dostum! Her türlü derdi çözeriz, merak etme!";
			link.l1 = "O zaman lafı dolandırmayacağım. Miguel Dichoso'yu tanıyor musun?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Onu tanırım. O İspanyol donu bana harika bir gemi sattı - bir fırkateyn. Eh, ne gemiydi ama, bir hayal etsene...";
			link.l1 = "Dur tahmin edeyim, özel bir gövde, azami on altı knot hız? 'Santa Quiteria' mı?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = " Gövdesi ve hızı konusunda haklısın, ama adı farklıydı - 'San Martin'. Ona yüklüce altın ödedim, sahip olduğum her şeyi verdim. Bütün birikimim o alçağın cebine gitti.";
			link.l1 = "Adının San Martin olduğundan emin misin, yoksa Santa Quiteria mıydı? Peki, onu ne zaman satın aldın? Ve neden ona serseri diyorsun?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Ne çok soru sordun! Hepsini sırayla cevaplayacağım: Eminim ki o gemi San Martin'di. Alexus’un işçilerine, kıçındaki o papaz ismini taşıyan tahtayı söktürmelerine bizzat yardım ettim. Ben ona 'Fortune' adını verdim – böyle bir prenses için çok daha uygun bir isimdi.\nOnu 1654 kışında Blaze Sharp öldürülmeden kısa süre önce satın aldım. Miguel’e neden öyle dedim? Çünkü o köpek, gemiyi Providence’daki İspanyol askeri üssünden çalmayı başarmıştı. Onlara tam San Juan kalesinin önünde güzel bir oyun hazırladık. Dövüş daha inandırıcı olsun diye iki can çekişen lugger’i feda ettim. Gemileri yaktık ve batırdık, fırkateynle savaşmışız gibi gösterdik. Ve karanlık çökünce San Martin’i Isla Tesoro’ya sürdük... Gemiyi ben aldım, Dichoso parayı aldı. Yüksek komutanına fırkateynin korsanlarla savaşta battığını söyledi, San Juan’ın komutanı da bunu doğruladı.";
			link.l1 = "Demek İspanyol soyluları ceplerini böyle dolduruyor! Ne alçak herif! Söylesene, bu gerçekten 1654 kışında mı oldu? Belki ilkbaharda mıydı? Fırkateyn fırtınalardan zarar gördü mü?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "Kışın... Lanet olsun, tam emin değilim - belki ilkbaharda da olabilir. Gerçekten hatırlamıyorum. Fırkateyn hasarsızdı, yepyeniydi. Daha yeni inşa edilmiş gibiydi. Onu düşündükçe, öfkeden ağlamak istiyorum...";
			link.l1 = "Neden? Evet, peki o güzel fırkateynin şimdi nerede?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Beni terk ettiği için değil. Bana tuzak kurdular, tılsımımı Blaze'in cesedine koyup katil olduğumu yaydılar. Sonra duydum ki Marcus Tyrex - bizim şifre bekçimiz - bana kara işaret verecekmiş. Ben de bir süreliğine o karmaşadan kaçmaya karar verdim, senin beni bulduğun Adalet Adası'na sığındım.\nOraya bir fırkateynle gidemedim, bu yüzden onu Black Pastor'a rehin verip karşılığında erzakla dolu bir brig aldım. O kurnaz Dichoso'yla yaptığım anlaşmadan sonra pek param kalmamıştı. Erzakı satıp bir iki aya Isla Tesoro'ya dönmeyi umuyordum... Gerisini zaten biliyorsun.";
			link.l1 = "Ve Kara Papaz seni beklemedi, bu yüzden onu sattı";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Kesinlikle. Kızı bir İngiliz, daha doğrusu bir İskoç, William Paterson satın aldı. Kızı geri almaya çalışabilirim tabii, ama bu dağlı ciddi bir adam, Kraliyet Donanması'nın kaptanı, Albay Fox'un yakın dostu. Ayrıca, Jackman'la iş yapıyordu, tıpkı senin Svenson'la yaptığın gibi\nİskoç'un bir filosu var... boşver, gemimi bir daha göremeyeceğim.";
			link.l1 = "Anladım. Peki, şimdi o Dichoso'nun nerede olduğunu bilmiyor musun?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Hiçbir fikrim yok. Fortune'umu aldıktan sonra onu bir daha hiç görmedim.";
			link.l1 = "Ve neden Miguel bunu başkasına satmayı teklif etmedi? Mesela Tyrex, Barbazon, Sharp? Ya da Paterson?";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Hiçbir fikrim yok. Paterson o zamanlar burada değildi, yanlış hatırlamıyorsam. Zachariah, Jacques ve Marcus asla kabul etmezdi ve ben... Ben o fırkateyni gerçekten çok seviyordum!";
			link.l1 = "Anlıyorum ki... Aslında hiçbir şey anlamıyorum. Her yerde bilmeceler...";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Yine geçmişi mi kurcalıyorsun? Bu sefer hangi adayı almak istiyorsun? Ha-ha-ha!";
			link.l1 = "Bir ada var... Ama henüz oraya nasıl gideceğimi bulamadım. Peki Steven, verdiğin bilgiler için sağ ol! Hoşça kal!";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "İyi şanslar, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			DialogExit();
			AddQuestRecord("Guardoftruth", "60");
			pchar.questTemp.Guardoftruth.Archy = "guadeloupe";
			// маленькая развлекуха
			pchar.quest.GuardOT_cabinattack.win_condition.l1 = "EnterToSea";
			pchar.quest.GuardOT_cabinattack.function = "GuardOT_PrepareCreateBandosInCabin";
		break;
		
		case "tieyasal":
			dialog.text = "Ve sana her zaman olduğu gibi yardımcı olmaktan memnuniyet duyarım. Bu sefer ne istiyorsun, "+pchar.name+"?";
			link.l1 = "Yine eski dostun Miguel Dichoso hakkında. Onun Isla Tesoro'da tekrar görüldüğünü duydum. Onu bulmamda bana yardım edemez misin?";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Hey dostum, aslında bunu bilmiyordum. Onu burada görmedim. 'Fortune'u ondan satın aldığımdan beri de görmedim. Peki, o İspanyol soylusunu neden arıyorsun?";
			link.l1 = "Ona ihtiyacım var. Miguel eski bir Kızılderili şehrine giden yolu biliyor. Oraya gitmek için gerçekten sabırsızlanıyorum.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Her zamanki gibi, dostum, yine kendini belaya bulaştıracaksın. Ne yazık ki sana yardım edemem. Sana tavsiyem, yerleşkede dolaşıp insanlara sor; belki birisi onu görmüştür. Burada ünlü biridir, biliyorsun.";
			link.l1 = "Hey, Steven, bana en azından nasıl göründüğünü söyleyebilir misin?";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "Yirmi beş - yirmi sekiz yaşlarında, senin kadar uzun boylu, koyu renk gözlü, peruğu yok. Sağ yanağında bir kılıç yarası var.";
			link.l1 = "Hm. Biliyor musun, bu tarife uyan pek çok insan var.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "Onun hakkında başka özel bir bilgi yok. Kendine güvenen, küstah ve son derece tehlikeli biri. Hakkında dedikodular dolaşıyordu...";
			link.l1 = "Anladım. Peki, onun hakkında etrafa soracağım. Bol şans, Steven!";
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			DialogExit();
			AddQuestRecord("Tieyasal", "2");
			npchar.quest.tieyasal = "true";
		break;
		
		// Jason НСО
		case "patria":
			dialog.text = "Ho-ho! Doğru yere geldin! Söyle bakalım!";
			link.l1 = "Korsanlardan hiç korkmayan bir adam var. Bizi ciddiye almıyor. Ona saygının ne demek olduğunu öğretmek gerek. Unutma, sakın öldürme.";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "Ha! Bu yaşlı Charles'dan başkası değil! Eminim yine bir belaya bulaştın! Hadi anlat bakalım, bu sefer hedef kim ve ona ne ders vereceğiz";
			link.l1 = "Avrupa'dan bir misafir, Fransız Maliye Bakanlığı'nın müfettişi - baron Noel Forget. Burada bir Fransız Ticaret Şirketi kurmak istiyor, ama ben ve yakın bir dostum buna karşı çıkıyoruz. Baronu ikna etmeye çalıştık; Levasseur yenildikten sonra buradaki ticaretin Hollandalılar, İngilizler ve özellikle de korsanlar yüzünden çok tehlikeli olacağını söyledik, ama dinlemedi. Ona korku salmamız, bunu kendi derisinde hissetmesini sağlamamız lazım.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			dialog.text = "Evet-evet... Gerçek bir baron!.. Gemisine saldıracak mıyız?";
			link.l1 = "Plan şöyle: Gemisi yakında Port-au-Prince'den Capsterville'e doğru yola çıkacak. Baronu ayrıldıktan sonra yakalayıp rehin almalısın. Gemiyi batırmasan ve mürettebatı öldürmekten kaçınsan iyi olur. Sonuçta Fransızlar bizim dostumuz. Bunun üstesinden gelebilecek misin?";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			dialog.text = "Pekala, hiçbir şeyin garantisini veremem. Ama deneyeceğim. Hangi gemi bu?";
			link.l1 = "'Favory' adında bir brig.";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "Bir brig benim fırkatin karşısında bir hiç. Onlarla kolayca başa çıkarız. Teslim olurlarsa, kimsenin kılına dokunmam.";
			link.l1 = "Mükemmel. Korku sal ve teslim olmalarını teklif et. Sonrasında Baronu fare kaynayan ambarın içine gönder. Bulabildiğin en pis yeri seç, ama onu orada bir günden fazla tutma, yoksa hastalanıp ölebilir. Sonra onu kamarada ağırlayın, Isla Tesoro'ya gidin ve onu tenha bir yere kilitleyin. Adamlarından birkaçını yakalanmış Fransız tüccarları gibi giydir ve öyle davranmalarını sağla. Üç gün boyunca, ona acımasız korsanların onları nasıl kovaladığını, soyduğunu, fidye istediğini, işkence ettiğini... gerekli tüm ayrıntılarıyla anlatsınlar.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "Ha-ha-ha! Bu, uzun zamandır üstlendiğim en komik iş olmalı! Pekâlâ, sana öyle oyuncular bulacağım ki, dostum. Hiç şüphen olmasın, onların hikâyelerinden sonra baronun altına edecek! Ona pala ve kızgın sürgü izlerini gösterecekler... ";
			link.l1 = "Harika. Sonra onu Poincy'ye fidye istemek için bir mektup yazmaya zorlayacaksın. Böyle bir adam için üç buçuk yüz bin o kadar da fazla değil.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			dialog.text = "Güzel. Peki şimdi ne yapacağız?";
			link.l1 = "Sonra Baronu Turks'e getireceksin. Orada fidyeyi alacaksın ve Baronu bana teslim edeceksin. Ayrıca şunu da belirtmelisin: Tüm Fransızlar Tortuga ve Levasseur'un hesabını verecek.";
			link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			dialog.text = "Ha-ha-ha! Bu gerçekten harika bir numara! Biz şahsen, yani, Levasseur'a ne yaptığımızı biliyorsun, şimdi de... ha-ha-ha!.. Tamam dostum. Halledeceğim! Gemi yakında gelecek diyorsun, öyle mi?";
			link.l1 = "Yakında. Gözümüz açık olmalı.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_8":
			dialog.text = "Canını sıkma , seni yüzüstü bırakmam. Bu işi bizzat halledeceğim. Bu baronun yakalandığına dair bir söylenti duyarsan, bana gel.";
			link.l1 = "İyi. Teşekkürler, Steven.";
			link.l1.go = "patria_9";
		break;
		
		case "patria_9":
			DialogExit();
			AddQuestRecord("Patria", "70");
			pchar.questTemp.Patria = "epizode_12_wait";
			pchar.questTemp.Patria.Condotier.Success = "true";
			LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
		break;
		
		case "patria_10":
			dialog.text = "Elbette, dostum. Anlaştığımız gibi. Kötü korsanlarla ilgili korkunç hikayeler, masum Fransız tüccarların katledilmesi, Kırbaç sesleri, inlemeler ve çığlıklar. Kömür dolu mangal ve yanık kelepçeler. Tam olması gerektiği gibi.";
			link.l1 = "Pekâlâ! Sakin ol biraz. Onu canlı istiyorum.";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "Merak etme, hayatta kalacak. O mektubu titrek bir elle yazmış. İşte burada.";
			link.l1 = "Orada ne yazıyor? Poincy'den onu buradan çıkarmasını mı diliyor?";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "Tam isabet, dostum! Yalvarıyor!";
			link.l1 = "Bu mektubu at, ya da daha iyisi - yak. Bir hafta sonra Turks'te buluşacağız. Fidye toplamak için zamana ihtiyacımız varmış gibi görünmeli.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			dialog.text = "Anladım. Bir hafta sonra, kuzey körfezinde. Parayı almayı unutma: işler düzgün görünmeli. Sonra bana gel, bunu hallederiz.";
			link.l1 = "Tabii ki, bunu deniz kestanesi bile anlardı. Sonra görüşürüz! ";
			link.l1.go = "patria_14";
		break;
		
		case "patria_14":
			DialogExit();
			AddQuestRecord("Patria", "73");
			pchar.questTemp.Patria = "epizode_12_terks";
			SetFunctionTimerCondition("Patria_CondotierTerks", 0, 0, 7, false);
			SetFunctionTimerCondition("Patria_CondotierTerksOver", 0, 0, 14, false);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		case "patria_15":
			pchar.quest.Patria_CondotierTerksOver.over = "yes"; //снять таймер
			dialog.text = "Hey, kurbağa yiyici! Dur!";
			link.l1 = "Kımıldamıyorum.";
			link.l1.go = "patria_16";
		break;
		
		case "patria_16":
			dialog.text = "Baronun burada. Biraz yıpranmış, ama tek parça halinde. Bu o mu?";
			link.l1 = "Evet.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "Mükemmel. Şimdi, parayı ver yoksa onun işi biter! Ve sakın bizi kandırmaya kalkma, seni gözümüzden kaçırmıyoruz!";
			if (sti(pchar.money) >= 350000)
			{
				link.l1 = "Al bakalım.";
				link.l1.go = "patria_18";
			}
			else
			{
				link.l1 = "Kahretsin! Onu gemide unuttum...";
				link.l1.go = "patria_22";
			}
		break;
		
		case "patria_18":
			AddMoneyToCharacter(pchar, -350000);
			dialog.text = "Ha-ha-ha! Akıllı bir çocuksun, Fransız. Al kutsalını. Ve Poincy'ye söyle, parayı hazırlasın: bütün Fransız piçleri, Levasseur ve Tortuga'ya yaptıklarınızın bedelini ödeyecek. Tüccarların ise mallarıyla ve gemileriyle bize ödeme yapacak. Ha-ha-ha! Takımadalara bize biraz daha baron getir, onlar bize iyi kazanç sağlıyor! Ha-ha-ha!";
			link.l1 = "Lütfen tekneme git, Baron.";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			sld = CharacterFromID("Noel");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			dialog.text = "Bizi takip etmeyi aklından bile geçirme, kaptan. Kim olduğumu biliyorsun. Daha elimde bir sürü Fransız esir var, eve zamanında dönmezsem adamlarım hepsini öldürür. Anladın mı?";
			link.l1 = "Zamanı gelince sizinle ilgileneceğiz, lanetli kafirler!";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "Ha-ha-ha-ha!";
			link.l1 = "...";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Patria", "74");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_baronalive";
			pchar.questTemp.Patria.DodsonAgain = "true";
			Island_SetReloadEnableGlobal("Bermudes", false); // закрыть остров до отвоза барона
			sld = CharacterFromID("Noel");
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Condotier_toPuancie.function = "Patria_CondotierEnCapstervil";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_22":
			dialog.text = "Benimle dalga mı geçiyorsun?";
			link.l1 = "Bir dakika, hemen getiriyorum...";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "Patria_CondotierBaronDie", 1.0);
		break;
		
		case "patria_24":
			dialog.text = "";
			link.l1 = "Ah, Steven, senin aptalın yine ne yaptı!";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25":
			dialog.text = "Charles, ne yapıyordun? Para nerede? Adamlarıma bunun gerçek olmadığını söylemedim... ve bu aptal da onları kandırmak istediğini sandı...";
			link.l1 = "Ne yazık! Baron öldü... Şimdi Poincy ne yapacak?";
			link.l1.go = "patria_26";
		break;
		
		case "patria_26":
			dialog.text = "Pekâlâ dostum, bunun senin suçun olduğunu umarım anlıyorsundur. Belki de senin için daha iyi olur.";
			link.l1 = "Ne aptalım ben! Her şeyi berbat ettim. Tamam, Poincy'ye gideceğim... Aptallığım için beni affet, Steven, görüşürüz.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "Dinlenmen lazım, eski formunda değilsin. Bir ara yanıma uğra, sana biraz rom ve güzel kadınlar ayarlarım.";
			link.l1 = "Teşekkür ederim, fırsat buldukça seni ziyaret edeceğim.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			DialogExit();
			AddQuestRecord("Patria", "75");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_barondie";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_29":
			dialog.text = "Rica ederim, dostum. Bu yıl en çok eğlendiğim an buydu! Ben ve adamlarım öyle çok güldük ki!.. Bunun için sana teşekkür etmek isterim. Al, paran burada.";
			link.l1 = "Kendine de bir pay ayırmalısın.";
			link.l1.go = "patria_30";
		break;
		
		case "patria_30":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "Boşver. Bunu dostluğumuz için yaptım. Kıyı Kardeşliği sana çok daha fazlasını borçlu, ama sen tek bir altın bile istemedin.";
			link.l1 = "Yine de, hizmetler ve tazminat için en az elli bin al. Teşekkür ederim, Steven! O kayıp gemilerden oluşan garip adada seninle tanıştığıma gerçekten memnunum.";
			link.l1.go = "patria_31";
		break;
		
		case "patria_31":
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "Ben de öyleyim. Charles, ne zaman vaktin olursa beni ziyaret et!";
			link.l1 = "Memnuniyetle!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Patria.DodsonAgain");
		break;
		
		case "patria_33":
			dialog.text = "Bir hafta geciktin! Adamlarıma bunun gerçek olmadığını söylemedim... ! Daha fazla beklemeyi reddettiler ve baronluğunu bitirmeye karar verdiler!";
			link.l1 = "Ne aptalım ben! Her şeyi berbat ettim! Poincy'ye ne diyeceğim şimdi?";
			link.l1.go = "patria_34";
		break;
		
		case "patria_34":
			dialog.text = "Pekâlâ dostum, bunun senin hatan olduğunu umarım anlıyorsundur. Belki de senin için böyle daha iyi olur.";
			link.l1 = "Pekala, Poincy'ye gideceğim... Aptallığım için beni affet, Steven, görüşürüz..";
			link.l1.go = "patria_35";
		break;
		
		case "patria_35":
			dialog.text = "Dinlenmen lazım, eski formunda değilsin. Bir ara yanıma gel, sana biraz rom ve güzel kadınlar ayarlarım";
			link.l1 = "Teşekkür ederim, fırsat buldukça sana uğrayacağım.";
			link.l1.go = "patria_36";
		break;
		
		case "patria_36":
			DialogExit();
			AddQuestRecord("Patria", "75");
			pchar.questTemp.Patria = "epizode_12_barondie";
			DeleteAttribute(pchar, "questTemp.Patria.DodsonFail");
		break;
		// belamour legendary edition хвастаемся Фортуной
		case "check_out_my_frigate":
			dialog.text = "İlginç, merak ettim. Hadi, biraz yürüyelim.";
			link.l1 = "...";
			link.l1.go = "check_out_my_frigate_01";
		break;
		
		case "check_out_my_frigate_01":
			DialogExit();
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			DoQuestReloadToLocation("pirates_town", "reload", "reload3_back", "SharkFrigateToTown");
			pchar.questTemp.SharkFrigate = true;
		break;
		
		case "check_out_my_frigate_02":
			dialog.text = "Vay canına! Gözlerime inanamıyorum! Bu gerçekten o mu? Söylesene, o mu? Bu 'Fortune' mü?!";
			link.l1 = "Evet dostum, gözlerin seni yanıltmıyor. O işte. Onu özledin mi?";
			link.l1.go = "check_out_my_frigate_03";
		break;
		
		case "check_out_my_frigate_03":
			dialog.text = "Ha ha ha, inanamıyorum! Bin şeytan aşkına! Ama bunu nereden buldun?";
			link.l1 = "William Paterson adında bir İskoç'tan. Evet, evet, Kara Papaz'dan satın alan o adamdan.";
			link.l1.go = "check_out_my_frigate_04";
		break;
		
		case "check_out_my_frigate_04":
			dialog.text = "Vay canına... Ne yani, sana 'Fortune'u sattı mı? Hem de böyle güzel bir gemiyi? Üstelik sen aldıktan sonra mı?";
			link.l1 = "Hehe, neredeyse öyle. Şöyle söyleyeyim: Hiç anlaşamadık ve aramızdaki sürtüşmeden doğan masraflarımın karşılığı olarak gemiyi aldım. Zaten onun gemiye ihtiyacı yok.";
			link.l1.go = "check_out_my_frigate_05";
		break;
		
		case "check_out_my_frigate_05":
			dialog.text = "Beni daha da şaşırtıyorsun ... O, İngiltere'nin hizmetindeki bir askeri kaptan. Kolonisinin filosu isterse yağma yapabilir. Ben bile onunla uğraşmaya cesaret edemedim. Peki sen nasıl başa çıktın? 'Fortune'u filodan koparmayı başardın mı?";
			link.l1 = "Hayır, filo battı. Aslında, bu kolay olmadı. Savaş ciddiydi, ama yerleşim yerlerinden uzakta gerçekleşti ve tanıklar arasında sadece benim denizcilerim ve subaylarım vardı. Genel olarak, İngiliz makamlarının peşime düşmesinden korkmuyorum. William Paterson ise sıradan bir macera sırasında ortadan kayboldu ...";
			link.l1.go = "check_out_my_frigate_06";
		break;
		
		case "check_out_my_frigate_06":
			dialog.text = "Vay canına... Kırlangıcımı bir daha göreceğimden umudumu çoktan kesmiştim. Neyse, umarım bu gemi sana sadakatle hizmet eder. Senin adına gerçekten çok sevindim, dostum!";
			link.l1 = "Ne? Ona ihtiyacın yok mu? Ben onu asıl sahibine geri vermek istemiştim...";
			link.l1.go = "check_out_my_frigate_07";
		break;
		
		case "check_out_my_frigate_07":
			if(CheckAttribute(pchar, "questTemp.SharkGoldFleet"))
			{
				dialog.text = "Ha-ha-ha, dostum, 'Fortune'u kendine sakla. Öncelikle, onun gerçek sahibi sensin. Onu savaşta hak ederek aldın. Bu durumda gemiyi terk etmek doğru olmaz. İkincisi ise, benim zaten yeni bir teknem var. Tabii, 'Fortune'u satın aldığımda onu bir gün başka bir şeyle değiştireceğim aklımın ucundan geçmezdi. Ama, onu bir daha göreceğimi beklemediğim için Alexus'a yeni bir fırkateyn sipariş ettim. Ve biliyor musun... Adam harika bir iş çıkarmış. Duyduğuma göre, bunda senin de parmağın varmış, ha ha!";
			}
			else
			{
				dialog.text = "Ha-ha-ha, dostum, 'Fortune'u kendine sakla. Öncelikle, onun gerçek sahibi sensin. Onu savaşta hak ederek aldın. Bundan sonra gemiyi terk etmek iyi olmaz. Ayrıca, benim için zaten yeni bir gemi inşa ediliyor. Tabii ki, 'Fortune'u satın aldığımda, bir gün onu başka bir şeyle değiştireceğim aklıma gelmezdi. Ama, onu bir daha göreceğimi beklemediğim için, Alexus'a yeni bir fırkateyn sipariş ettim. Ve onun güvertesine adım atacağım günü sabırsızlıkla bekliyorum.";
			}
			link.l1 = "O halde, bu güzel gemiyi kendime saklamaktan başka çarem yok, Steven!";
			link.l1.go = "check_out_my_frigate_08";
		break;
		
		case "check_out_my_frigate_08":
			dialog.text = "Aynen öyle. Senden tek istediğim, 'Fortune'a iyi bakman. İnan bana, böyle bir gemiyi başka yerde bulamazsın. O eşsizdir. Ve benim için bir hatıra. Bu geminin bir alçağın eline değil de dostumun eline geçtiğini bilmek beni mutlu eder.";
			link.l1 = "Pekala Steven. Söz veriyorum, 'Fortune'u koruyacağım.";
			link.l1.go = "check_out_my_frigate_09";
		break;
		
		case "check_out_my_frigate_09":
			dialog.text = "Evet, bir şey daha...";
			link.l1 = "Dinliyorum.";
			link.l1.go = "check_out_my_frigate_10";
		break;
		
		case "check_out_my_frigate_10":
			dialog.text = "Artık 'Fortune' sende olduğuna göre, sana bir iş teklif etmek istiyorum.";
			link.l1 = "Seni ÇOK dikkatli dinliyorum.";
			link.l1.go = "check_out_my_frigate_11";
		break;
		
		case "check_out_my_frigate_11":
			if(!CheckAttribute(pchar, "questTemp.SharkGoldFleet.KGBB"))
			{
				dialog.text = "Dediğim gibi, Alexus şu anda bana yeni bir fırkateyn inşa ediyor. Elbette, hız bakımından 'Fortune'u geçmesi pek mümkün değil, ama ondan da çok geri kalmayacak. Ve tam da bu yüzden bana birkaç güçlü ama hızlı gemi lazım. Belki tek başıma da halledebilirim, ama iki gemi çok daha iyi olur.";
				link.l1 = "Harika.   Peki, bu nasıl bir iş?";
				link.l1.go = "check_out_my_frigate_12";
			}
			else
			{
				dialog.text = "Dediğim gibi, Alexus yakın zamanda bana yeni bir fırkateyn yaptı. Elbette, hız konusunda 'Fortune'u geçmesi pek mümkün değil, ama çok da geri kalmayacak. Ve tam da bu iş için bana birkaç güçlü ama hızlı gemi lazım. Belki tek başıma da halledebilirim, ama iki gemi çok daha iyi olur.";
				link.l1 = "Harika.   Peki, bu ne tür bir iş?";
				link.l1.go = "check_out_my_frigate_13";
			}
		break;
		// Фрегат Акулы не построен
		case "check_out_my_frigate_12":
			dialog.text = "Bunun hakkında konuşmak için henüz erken, çünkü yeni gemimin ne zaman denize indirileceğini daha bilmiyorum. Alexus malzeme bulmakta biraz zorlanıyor gibi görünüyor. Bu arada, fırsatın olursa ona yardım edebilirsin. Eminim karşılığını iyi ödeyecektir: Ona oldukça yüklü bir avans verdim. Gerekli tüm malzemeleri bulduktan sonra, sanırım bir ay içinde gemim hazır olur. O zaman seni bekliyorum. Ama mutlaka 'Fortune' ile gel ve önceden donat, çünkü fazla zaman olmayacak! Bir de, İspanyolların kafanı gümüş tepside görmek isteyip istemediğinden emin ol. Tüm ayrıntıları sonra anlatırım.";
			link.l1 = "Pekala, gemi ustamıza ne yardıma ihtiyacı olduğunu soracağım. Sonra, Alexus'a yardım ettikten bir ay sonra, sen tekrar denize açılacağın zaman, sohbetimize döneriz.";
			link.l1.go = "check_out_my_frigate_14";
		break;
		
		// Фрегат Акулы построен
		case "check_out_my_frigate_13":
			dialog.text = "Bunun hakkında konuşmak için henüz erken, çünkü gemim daha tersaneden bile çıkmadı. Hâlâ donatmam gerekiyor. Yani seni bir aydan önce beklemiyorum. Ama mutlaka 'Fortune' ile gel ve önceden hazırla, yoksa zaman dar olur! Bir de, İspanyolların kafanı gümüş tepsiyle görmek istemediğinden emin ol. Tüm ayrıntıları sonra anlatırım.";
			link.l1 = "Pekâlâ, o zaman bu sohbetimize sen tekrar yelken açtığında döneriz.";
			link.l1.go = "check_out_my_frigate_14";
		break;
		
		case "check_out_my_frigate_14":
			dialog.text = "Pekâlâ, tamam. Şimdi izninle konağa gidiyorum. Malum, işler beklemez.";
			link.l1 = "Yakında görüşürüz, Köpekbalığı! Hoşça kal demiyorum.";
			link.l1.go = "check_out_my_frigate_15";
		break;
		
		case "check_out_my_frigate_15":
			DialogExit();
			sld = characterFromId("Dodson");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload3_back","SharkFrigateEnd", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		// belamour legendary edition на пару с Акулой
		case "SharkGoldFleet":
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = "Benimki hazır, ya seninki? Sana 'Fortune'a gelmeni söyledim. Onu nereye bıraktığını bilmiyorum ama başka bir gemide böyle bir riske girmek akıl kârı değil. O yüzden anlaştığımız gemide seni bekliyorum. Ve fazla sıkma kendini.";
				link.l1 = "Lanet olsun, tamamen unuttum, pislik! Bekle: doğru gemiye döneceğim.";
				link.l1.go = "exit";
				break;
			}
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Charles, sana filoyla gelmemeni söylemiştim. Seninle yapmak istediğim işte fazladan gemilere kesinlikle gerek yok. Filonu bir yere götür ve geri gel.";
				link.l1 = "Evet, tamamen unuttum. Bekle: Yakında bir filoyla dönmeyeceğim.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Ah, işte buradasın dostum! Sonunda! Neredeyse endişelenmeye başlamıştım. Gemim neredeyse hazır. Şimdi onu Tirax'a gönderdim: geçen ay ele geçirdiği ağır kalyondan aldığı otuz iki kalibrelik topları takacak. Onunla Türklere kadar gidip döndüm, şunu söylemeliyim ki Alexus harika bir iş çıkarmış. Bu arada, hâlâ ona uygun bir isim seçmedim, birkaç seçenek var gerçi. Bana seçimde yardımcı olur musun?";
			link.l1 = "Tabii ki yardım ederim! Bir gemiye ne isim verirsen, öyle yol alır, değil mi? Seçeneklerin neler?";
			link.l1.go = "SharkGoldFleet_01";
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "Şimdiye kadar üç seçenek belirledim.";
			link.l1 = "...";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "İlk seçenek 'Hayalet'. Fırkateyn hızlı ve güçlü, üstelik bu isimle Havana'dan Cumana'ya kadar bütün cimriler adını duyunca tir tir titreyecek!";
			link.l1 = "Evet, bir de sisin içinde görünüp kaybolman lazım ki denizciler kesinlikle haç çıkarmaya başlasınlar, ha ha! Güzel isim, hoşuma gitti.";
			link.l1.go = "SharkGoldFleet_03";
		break;
		
		case "SharkGoldFleet_03":
			dialog.text = "Ben de beğendim. İkinci seçenek 'Köpekbalığı'. Eee? Neden gemime de bir lakap koymayayım ki? Onunla adaş olalım, ha!";
			link.l1 = "'Köpekbalığı'nda bir köpekbalığı var... İronik. Ama herkes geminin kime ait olduğunu hemen anlayacak.";
			link.l1.go = "SharkGoldFleet_04";
		break;
		
		case "SharkGoldFleet_04":
			dialog.text = "Burada da aşağı yukarı aynıyım. Ve üçüncü seçenek 'Fırtına'. Herkes gemime yaklaşmaya bile korksun diye, ha ha ha!";
			link.l1 = "Yandan gelen bir kurşun yağmuruna tutulabilirsin diye mi? Eee, fena değilmiş.";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			dialog.text = "Aynen öyle! Ama şimdi bu üç isim arasında karar veremiyorum. Hadi ama, yardım et. Nasıl istersen.";
			link.l1 = "Bence adını 'Hayalet' koyalım. O zaman tüm tüccarlar seni ufukta görür görmez beyaz bayrağı çeker!";
			link.l1.go = "SharkGoldFleet_05f";
			link.l2 = "'Köpekbalığı' adını beğendim. Herkes bu geminin bir acemiye ait olmadığını, bizzat Kıyı Kardeşliği'nin başına ait olduğunu bilmeli!";
			link.l2.go = "SharkGoldFleet_05a";
			link.l3 = "Bence 'Flurry' iyi bir isim. Her savaşçı, korsan ya da tüccar, bu gemiyle dövüşmeye kalkarsa başına neler geleceğini bilir.";
			link.l3.go = "SharkGoldFleet_05s";
		break;
		
		case "SharkGoldFleet_05f":
			pchar.questTemp.SharkGoldFleet.KGBB = "Phantom";
			dialog.text = "Bak hele - askerler bile aynısını yapmaya başlayacak, ha! O halde karar verildi. Tut kupayı, dostum. Yeni gemime içelim. 'Phantom' için!";
			link.l1 = " Hayalet için! ";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_05a":
			pchar.questTemp.SharkGoldFleet.KGBB = "Shark";
			dialog.text = "Ve yoluma çıkmadan önce üç kez düşünsünler! Demek karar verildi. Bardağı tut, dostum. Yeni gemime içelim. 'Köpekbalığı' için!";
			link.l1 = "Köpekbalığı için!";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_05s":
			pchar.questTemp.SharkGoldFleet.KGBB = "Flurry";
			dialog.text = "Eğer hâlâ kararında ısrar ederse, öyle bir fırtına kopar ki tropik kasırgalar yanında esinti kalır! O zaman, karar verildi. Tut bakalım kupayı, dostum. Yeni gemime içiyoruz. 'Fırtına'ya!";
			link.l1 = " 'Fırtına!' için ";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			dialog.text = "Ve bu gemi sadakatle hizmet etsin, yenilginin acısını hiç tatmasın! Neyse, şimdi asıl meseleye gelelim.";
			link.l1 = "Seni dikkatle dinliyorum.";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "Söyle bana Charles, 'Altın Filo'nun ne olduğunu biliyor musun?";
			link.l1 = "Kha-kha! .. Neredeyse romdan boğuluyordum. Steven, bana söyleme, Karayipler'in en ağır silahlı konvoyunu soymak için iki fırkateynle geldin, değil mi?";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			dialog.text = "Hayır, tabii ki intihar etmek istemiyorum. Bütün konvoyu soymayacağız elbette. Ama buradan bir şeyler kapabiliriz.";
			link.l1 = "Steven, üzgünüm, elbette, ama buna hazır değilim. Evet, İspanyollar filolarına bulaşırsak bizi diri diri yakar! Bensiz devam et.";
			link.l1.go = "SharkGoldFleet_09";
			link.l2 = "Pekâlâ, kaybolmadığımız sürece ... Katılmaya hazırım!";
			link.l2.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_09":
			pchar.questTemp.SharkGoldFleet = "RUinDeal";
			dialog.text = "Ah! Yazık oldu. Sensiz bu iş fazla tehlikeli. Peki, şimdi ısrar etmeyeceğim, ama bir düşün olur mu? Eğer fikrini değiştirirsen, lütfen bana haber ver.";
			link.l1 = "Eğer yaparsam, tabii. Üzgünüm Steven.";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_10":
			dialog.text = "Böyle maceralar kolay kolay pes etmez! Peki ya sen? Belki fikrini değiştirdin mi?";
			link.l1 = "Hayır dostum, üzgünüm ama yine de kabul etmiyorum.";
			link.l1.go = "exit";
			link.l2 = "Pekâlâ, kaybolmadığımız sürece... Katılmaya hazırım!";
			link.l2.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_11":
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = "Hazır olabilirsin, ama gemin hazır değil. Sana 'Fortune' ile gelmeni söyledim. Onu nereye bıraktın bilmiyorum, ama başka bir gemiyle böyle bir riske girmek çok tehlikeli. Bu yüzden anlaştığımız gemide seni bekliyorum. Ve fazla kasma.";
				link.l1 = "Lanet olsun, tamamen unuttum, beceriksiz! Bekle: doğru gemiye döneceğim.";
				link.l1.go = "exit";
				break;
			}
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Hayır, Charles, henüz hazır değilsin. Sana filosuz gelmeni söylemiştim. Seninle yapmak istediğim işte fazladan gemilere kesinlikle gerek yok. Filonu bir yere götür ve sonra geri gel.";
				link.l1 = "Evet, tamamen unuttum. Bekle: Yakında bir filoyla değil, tek başıma döneceğim.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Bin şeytanın aklına, tam da duymak istediğim şey buydu! O halde, diyorum ki seninle birlikte konvoydan bir parça koparalım. Bolca ganimet...";
			link.l1 = "Çalmak mı diyorsun? Muhafız gemilerine yakalanmadan mı?";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			dialog.text = "Aynen öyle. Bak, muhtemelen biliyorsundur, 'Altın Filo' Porto Bello'da toplanır ve oradan Havana'ya gider. Havana'dan sonra onu yakalamak zaten imkânsız: Atlantik'i geçip İspanya'ya öyle bir korumayla gidiyor ki, ancak tam bir ahmak ona bulaşır. Porto Bello'dan Havana'ya geçişte de durum pek farklı değil. Tabii ki şansını deneyebilirsin, ama bunun için kaleleri ceviz gibi kırabilecek bir filo toplaman gerekir. Ama Porto Bello'da, Maine'in her yerinden gemiler buluşur ve orada artık pek korumasız kalırlar.";
			link.l1 = "Şimdi ise, bu tür gemilerin geçiş zamanı ve isimleri sıkı şekilde gizli tutuluyor. Porto Bello civarında aylarca oyalanıp limana giden tüm İspanyol gemilerini pusuya düşürecek halimiz yok.";
			link.l1.go = "SharkGoldFleet_13";
		break;
		
		case "SharkGoldFleet_13":
			dialog.text = "Elbette yapmayacağız. Mesela Cartagena'dan gemiler kendi başlarına gider, ve senin de doğru söylediğin gibi, ne tür gemiler olduklarını ve ne zaman gideceklerini yalnızca Tanrı bilir. Ama Caracas'tan, ki yanında bir İspanyol madeni var ve Porto Bello'dan epey uzakta, gemiler tamamen yalnız gitmez.";
			link.l1 = "Nasıl tamamen yalnız değil?";
			link.l1.go = "SharkGoldFleet_14";
		break;
		
		case "SharkGoldFleet_14":
			dialog.text = "Caracas'tan mallarla dolu bir geminin ya tek başına ya da küçük bir muhafızla ayrıldığını öğrendim, ama Maracaibo Körfezi boylarında bir yerde, İspanyol savaş gemileri ona katılıp güvenliğini sağlıyor. Sence orada kimi ve ne zaman karşılamaları gerektiğini nasıl biliyorlar?";
			link.l1 = "Onlara bir şey söylenmiş olmalı...";
			link.l1.go = "SharkGoldFleet_15";
		break;
		
		case "SharkGoldFleet_15":
			dialog.text = "Doğru. Ana gemi ayrılmadan önce, bir haberci gemi Karakas'tan Porto Bello'ya gider, buluşmanın yeri ve tarihiyle birlikte İspanyol gemisinin adını bildirir. Sonra geri döner ve geminin doğru zamanda ve doğru yerde karşılanacağına dair onayı getirir. Ancak bundan sonra, seninle birlikte hedefimiz Karakas'tan yola çıkar.";
			link.l1 = "Ama eğer ulak gemisini yakalarsak, Caracas'taki gemi onay alamayacak ve limandan ayrılmayacak. Bu konuda bir fikrin var mı? Ayrıca, ulak gemisini nasıl yakalayacağız? Ne zaman yola çıkacağını da bilmiyoruz.";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_16":
			dialog.text = "Ve burada küçük bir pürüz var. İspanyollar elbette bu işler için kurye luggerleri kullanıyorlar, ama bu oldukça riskli: ilk karşılarına çıkan korsan tarafından yakalanma ihtimali çok yüksek. Bu yüzden gemiyi göndermeden önce uzun süre bekleyebilirsin. Bu nedenle, fırsat bulurlarsa, talimatları güçlü ama hızlı gemilerle - mesela tüccarlarla ya da doğru rotadan giden özel korsanlarla - birlikte iletirler. \nTıpkı mühürlü bir posta gibi. Üstelik bu, ayrı bir kurye gemisi göndermekten, hatta bir luggerdan bile, çok daha ucuza gelir. Açgözlü İspanyol memurları da hem ceplerini doldurup hem de tasarruf etmeye bayılırlar, hehe.";
			link.l1 = "Bence anladım! Benim de böyle bir tüccar olmam mı gerekiyor?";
			link.l1.go = "SharkGoldFleet_17";
		break;
		
		case "SharkGoldFleet_17":
			dialog.text = "Kesinlikle! Ve şanslıydık: Güvenilir bir kaynaktan öğrendim ki, Caracas'ta şu anda böyle bir kurye arıyorlarmış, onu önümüzdeki üç hafta içinde bir mektupla göndermek için. Ve senin güçlü ve hızlı bir gemin var, hem de İspanyollar tarafından inşa edilmiş! Daha inandırıcı olmak için hemen altı aylık bir GVIK ruhsatı al, Caracas'ta Porto Bello'da kârlı bir şekilde satabileceğin kadar mal satın al, sonra da liman yetkilisinin yanına git ve yolda bir şey götürmen gerekip gerekmediğini sor. \nLiman yetkilisi sorarsa, kendini bir İspanyol olarak tanıt. Ve evet - sakın yanında bir filo sürüklemeyi aklından bile geçirme. Fazla dikkat çekmemize hiç gerek yok, yoksa tüm iş bozulabilir.";
			link.l1 = "Ve bana verecekleri belgelerden, gemiyle konvoyun buluşma tarihini ve yerini mi öğreneceğim?";
			link.l1.go = "SharkGoldFleet_18";
		break;
		
		case "SharkGoldFleet_18":
			dialog.text = "O kadar basit değil. Sana söylüyorum: belgeler mühürlü. Ve onları kendin açamazsın. Porto Bello liman idaresinde açacaklar, sonra bir cevap yazacaklar ve eğer Caracas'a geri döneceğini söylersen, senden onu oraya götürmeni isteyecekler. Tabii ki cevap da mühürlü olacak.";
			link.l1 = "Peki, o zaman toplantının yerini ve tarihini nasıl öğrenebilirim?";
			link.l1.go = "SharkGoldFleet_19";
		break;
		
		case "SharkGoldFleet_19":
			dialog.text = "Akıllı olmalı ve bir şekilde bunu gözetlemelisin ... Mesela Porto Bello’da belgeler açıldığında ve cevabı yazdıklarında. Ya da sana bir onay verdiklerinde, bunu çalıp Caracas’a götürebilirsin. Ama bu iyi bir seçenek değil: bundan sonra işler ters gidebilir.";
			link.l1 = "Elbette zor ... Ama sanırım bunun üstesinden gelebilirim.";
			link.l1.go = "SharkGoldFleet_20";
		break;
		
		case "SharkGoldFleet_20":
			dialog.text = "Ben de Marcus'tan gemimi alıp, Curacao'daki Santa Maria Burnu açıklarında demirlemiş halde seni bekleyeceğim. İşin bittiğinde, doğrudan bana gelirsin. Belirtilen koordinatlarda gemiyi yakalarız, sonra da hemen oradan defolup gideriz. Şimdi neden güçlü ama hızlı gemilere ihtiyaç olduğunu anladın mı? İspanyol askeri filosuyla hiç uğraşmak istemiyorum. Onlardan kaçmak zorunda kalacaksın.";
			link.l1 = "Anladım. O halde, ben çıkıyorum. Cape Santa Maria'da buluşalım!";
			link.l1.go = "SharkGoldFleet_21";
		break;
		
		case "SharkGoldFleet_21":
			dialog.text = "Aynen öyle, orada buluşacağız. Neyse, bol şans dostum! Umarım işimiz yolunda gider.";
			link.l1 = "Ben de öyle umuyorum. Neyse, ben gidiyorum.";
			link.l1.go = "SharkGoldFleet_22";
		break;
		
		case "SharkGoldFleet_22":
			DialogExit();
			AddQuestRecord("SharkGoldFleet", "1");
			pchar.questTemp.SharkGoldFleet = "start";
			SetFunctionExitFromLocationCondition("SharkGoldFleetStart", pchar.location, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleet21", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleet30", 0, 0, 30, false);
			else NewGameTip("Exploration mode: timer is disabled.");
		break;
		// провал
		case "SharkGoldFleet_23":
			dialog.text = "Lanet olsun Charles! Seni bir daha asla göremeyeceğimi sanmıştım! Neredeydin? Belirlenen yerde seni bekledim, ama hiç gelmedin. Senden de hiç haber çıkmadı.";
			link.l1 = "Üzgünüm Steven. Görevimi tamamlayamadım.";
			link.l1.go = "SharkGoldFleet_24";
		break;
		
		case "SharkGoldFleet_24":
			NextDiag.CurrentNode = "First time";
			dialog.text = "Eh, böyle bir balığı kaçırdılar ... Neyse, canını sıkma. Bir dahaki sefere şansın yaver gider.";
			link.l1 = "Umarım öyle.";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_25":
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = pchar.name+", ne oluyor? Sana filon olmadan gelmeni söyledim! Anla artık: bize fazlalık gerekmiyor, yoksa tüm operasyon suya düşer! Sana ne oldu bilmiyorum ama böyle olmaz. Karavanını hemen bir yere gönder ve tek bir gemiyle geri dön. Seni burada bekliyorum.";
				link.l1 = "Evet, sadece bunun daha olası olduğunu düşündüm ... Peki, seni anlıyorum. Burada bekle: hemen döneceğim!";
				link.l1.go = "exit";
				NextDiag.TempNode = "SharkGoldFleet_25";
				break;
			}
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = pchar.name+", ne oluyor? Sana 'Fortune'da olmanı söyledim! Anla artık: İki hızlı ve güçlü gemiye ihtiyacımız var, yoksa bütün iş berbat olabilir! Sana ne oldu bilmiyorum ama böyle olmaz. Hemen o külüstürü bırakıp 'Fortune'a geç ve geri dön. Burada seni bekliyorum.";
				link.l1 = "Evet, sadece bu geminin daha iyi olduğunu düşündüm ... Peki, seni anladım. Burada bekle: hemen döneceğim!";
				link.l1.go = "exit";
				NextDiag.TempNode = "SharkGoldFleet_25";
				break;
			} 
			dialog.text = "Ve işte buradasın, dostum! Peki, yakışıklımı nasıl buldun?";
			link.l1 = "Harika bir fırkateyn, Steven! Buna asla hayır demezdim...";
			link.l1.go = "SharkGoldFleet_26";
		break;
		
		case "SharkGoldFleet_26":
			dialog.text = "Hayır, artık 'Şans' sende, haha! Peki, anlat bakalım nasıl geçti.";
			if(pchar.questTemp.SharkGoldFleet == "LightVarToShark")
			{
				link.l1 = "Her şey kusursuz geçti: Dürüst ve güvenilir bir tüccar gibi davrandım. Belgeleri Porto Bello'ya götürdüm, orada liman yetkilisinin başını beş dakikalığına başka yöne çevirmeyi başardım ve gemilerin kargo ile askeri filoyla buluşma tarihini ve koordinatlarını kendi lehime yeniden yazdım.";
				link.l1.go = "SharkGoldFleet_27";
			}
			else
			{
				link.l1 = "Bazı ufak tefek aksilikler oldu. Mektup bir kurye ile Porto Bello'ya gönderilmişti. Onu ele geçirdim, alıcısına teslim ettim ve hatta bir cevap bile aldım, ama liman yetkilisinin başı belgeleri getirmesi gereken kişi olmadığımı anladı. Oradan dövüşerek çıkmak zorunda kaldım. Ama geminin yükle ve askeri filoyla buluşma tarihini ve koordinatlarını öğrendim, cevabı da Caracas'a ulaştırdım, yani üretim bizi bekliyor!";
				link.l1.go = "SharkGoldFleet_30";
			}
		break;
		
		case "SharkGoldFleet_27":
			dialog.text = "Bir saniye. 'Gemiler' mi dedin?";
			link.l1 = "Evet, Köpekbalığı! İkisi de orada olacak!";
			link.l1.go = "SharkGoldFleet_28";
		break;
		
		case "SharkGoldFleet_28":
			dialog.text = "Ha-ha-ha, evet, büyük vurgunu yapacağız! Benim canavarım da ateşle sınanmaya hazır. Ama henüz hiçbir savaşa katılmadı, o yüzden savaşı sen yönet. Şimdilik ben senin filona katılıyorum.";
			link.l1 = "Ben, Kıyı Kardeşliği'nin başı Steven Dodson'a mı komuta edeceğim? İşte buradayım!";
			link.l1.go = "SharkGoldFleet_29";
		break;
		
		case "SharkGoldFleet_29":
			NextDiag.TempNode = "SharkGoldFleet_33";
			pchar.questTemp.SharkGoldFleet.talk = true;
			AddQuestRecord("SharkGoldFleet", "22");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date);
			SGF_SharkCompanion();
			pchar.quest.SGF_SharkDelGroup1.win_condition.l1 = "ExitFromSea";
			pchar.quest.SGF_SharkDelGroup1.function = "SGF_SharkDelGroup";
			if(bImCasual)
			{
				pchar.GenQuest.SeaHunter2Pause = true;
				SeaHunter_Delete();
			}
			dialog.text = "Pek kibirli olma: sadece ilk kez kendi gemimde savaşacağım için böyle. Ve ödül gemileri için boş subayların hazır olduğundan emin ol. Çünkü onların ambarları dolup taşacak, ve benim tayfamdan hiçbiri o gemileri tek başına idare edemez ... Neyse, yeterince gevezelik ettik. Ganimet bizi bekliyor!";
			link.l1 = "Aynen öyle! Gemime gidiyorum.";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_30":
			dialog.text = "Evet, miras aldın ... O zaman filonun oraya anlaşılan tarihten önce varmasına hazırlıklı olmalıyız, ve herkesle aynı anda savaşmak zorunda kalacağız.";
			link.l1 = "Neden öyle diyorsun?";
			link.l1.go = "SharkGoldFleet_31";
		break;
		
		case "SharkGoldFleet_31":
			dialog.text = "Ve sen kafa yoruyorsun. Porto Bello'da, kargonun olduğu geminin kesinlikle Caracas'tan ayrılacağını biliyorlar, çünkü dönüş mektubunu oraya sen götürdün. Ama kendini ele verdiğin için, bu gemiyi ele geçirmemizi engellemek için ellerinden geleni yapacaklar. Bence filo oraya bizden önce varacak. Ben olsam öyle yapardım. O yüzden, sıkı bir dövüşe hazırlanalım. Geç kalırsak geri çekiliriz.";
			link.l1 = "Merak etme. Sen de ben de denizin kurduyuz, bunları yaşamadık mı sanki!";
			link.l1.go = "SharkGoldFleet_32";
		break;
		
		case "SharkGoldFleet_32":
			dialog.text = "Senin gerçeğin. Benim canavarım ateşle sınanmaya hazır. Ama henüz hiçbir savaşa katılmadı, o yüzden savaşı sen yönet. Bu arada, ben de senin filona katılayım.";
			link.l1 = "Ben, bizzat Kıyı Kardeşliği'nin başı Stephen Dodson'a mı komuta edeceğim? İşte bu!";
			link.l1.go = "SharkGoldFleet_29";
		break;
		
		case "SharkGoldFleet_33":
			NextDiag.TempNode = "SharkGoldFleet_33";
			dialog.text = "Konuşacak zaman yok, "+pchar.name+" ! Hadi ganimeti almaya gidelim!";
			link.l1 = "Ve şans bizimle olsun!";
			link.l1.go = "exit";
		break;
		// делим добычу на берегу
		case "SharkGoldFleet_34":
			if(makeint(pchar.questTemp.SharkGoldFleet) > 74)
			{
				dialog.text = "Bin şeytanın aklına! Harika iş çıkardın, Charles! Ganimet beklediğimden çok daha zengin çıktı! Bence bu yolculuk kesinlikle buna değdi.";
				link.l1 = "Kesinlikle sana katılıyorum Steven! Bugün kesinlikle bizim günümüz!";
				link.l1.go = "SharkGoldFleet_35";
			}
			else
			{
				if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
				{
					dialog.text = "İyi iş çıkardın, dostum. Yine de, kabul etmeliyiz ki çok fazla avı kaçırdık.";
					link.l1 = "Katılıyorum Steven, daha iyisini yapabilirdik. Ama olan da fena değil!";
					link.l1.go = "SharkGoldFleet_35";
				}
				else
				{
					dialog.text = "Lanet olsun! Ne harika bir fikirdi ... Ve sonuç olarak, bu seferden elde edilen masraflar kârdan fazla. Charles, aslında sana komutayı verdim, ama her şeyi kaybetmeyi başardın!";
					link.l1 = "Hiçbir şey söyleme... Ben de lanet olasıca sinirliyim. Ne kadar av elimizden kaçtı gitti!..";
					link.l1.go = "SharkGoldFleet_37";
				}
			}
		break;
		
		case "SharkGoldFleet_35":
			dialog.text = "Pekâlâ, ikimiz de iyi iş çıkardık. Ben bir plan yaptım ve ulak hakkındaki bilgileri topladım, sen de bu planı harika bir şekilde uyguladın. Avımız için de eşit şartlarda savaştık. Bu yüzden, Kıyı Kardeşliği yasalarına göre paylaşmayı öneriyorum: eşit olarak!";
			link.l1 = "Bunu yapacağız!";
			link.l1.go = "SharkGoldFleet_36";
		break;
		
		case "SharkGoldFleet_36":
			dialog.text = "Şimdi Isla Tesoro'ya gidiyorum. Gemiyi tamir etmem ve yeni gemimle yaptığım ilk başarılı seferi güzelce kutlamam lazım. İyi şanslar dostum! Her zaman konutumda seni görmekten mutluluk duyarım!";
			link.l1 = "İşimizin bu kadar kârlı olmasına sevindim. Kesinlikle bir ara seni ziyaret edeceğim. Bol şans!";
			link.l1.go = "SharkGoldFleet_39";
		break;
		
		case "SharkGoldFleet_37":
			dialog.text = "Pekâlâ, hepsini kendine sakla. Gerçi geriye bir şey kalmışsa tabii. Bu ufaklıklara aldırmıyorum. Sonuçta seni bu işe ben bulaştırdım.";
			link.l1 = "Evet, benim de hatam... Üzgünüm, Steven.";
			link.l1.go = "SharkGoldFleet_38";
		break;
		
		case "SharkGoldFleet_38":
			dialog.text = "Özür dileme, hâlâ sana hayatımı borçluyum ve bunu unutmayacağım. Şimdi Isla Tesoro'ya gidiyorum. Gemiyi tamir etmemiz ve temizlememiz lazım... Gerçi, neyi temizleyeceğiz ki... İyi şanslar dostum! Her zaman konutumda seni görmekten memnuniyet duyarım!";
			link.l1 = "Pekala, her şey olabilir, yenilgiler de olur. Önemli olan hayatta olmamız. Bir ara mutlaka seni ziyaret edeceğim, dostum! Bol şans!";
			link.l1.go = "SharkGoldFleet_39";
		break;
		
		case "SharkGoldFleet_39":
			if(makeint(pchar.questTemp.SharkGoldFleet) > 74)
			{
				AddQuestRecord("SharkGoldFleet", "34");	
				ChangeCharacterComplexReputation(pchar, "fame", 10);
				ChangeCharacterComplexReputation(pchar, "authority", 5);
				ChangeOfficersLoyality("good_all", 2);
				AddComplexSeaExpToScill(150, 150, 150, 150, 150, 150, 0);
				AddCharacterExpToSkill(pchar, "Leadership", 300);
				AddCharacterExpToSkill(PChar, "Fortune", 300);
				AddCharacterExpToSkill(PChar, "Sneak", 300);
			}
			else
			{
				if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
				{
					AddQuestRecord("SharkGoldFleet", "35");
					ChangeCharacterComplexReputation(pchar, "fame", 1);
					ChangeCharacterComplexReputation(pchar, "authority", 1);
					AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
					AddCharacterExpToSkill(pchar, "Leadership", 200);
					AddCharacterExpToSkill(PChar, "Fortune", 200);
					AddCharacterExpToSkill(PChar, "Sneak", 200);
				}
				else
				{
					AddQuestRecord("SharkGoldFleet", "36");
					AddCharacterExpToSkill(pchar, "Leadership", 100);
					AddCharacterExpToSkill(PChar, "Fortune", 100);
					AddCharacterExpToSkill(PChar, "Sneak", 100);
				}
			}
			if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
			{
				if(GetSquadronGoods(pchar, GOOD_GOLD)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_GOLD, sti(makeint(pchar.questTemp.SharkGoldFleet.Gold)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SILVER)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SILVER, sti(makeint(pchar.questTemp.SharkGoldFleet.Silver)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SANDAL)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SANDAL, sti(makeint(pchar.questTemp.SharkGoldFleet.Sandal)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SHIPSILK)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SHIPSILK, sti(makeint(pchar.questTemp.SharkGoldFleet.Silk)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_ROPES)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_ROPES, sti(makeint(pchar.questTemp.SharkGoldFleet.Ropes)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_OIL)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_OIL, sti(makeint(pchar.questTemp.SharkGoldFleet.Gold)/2));
				}
			}
			SGF_GoodSwimReturn();
			SGF_DelAllSubAttributes(); // убираем все лишнее, чтобы не болталось
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "SGF_SharkToIT", -1);
			CloseQuestHeader("SharkGoldFleet");
			DialogExit();
		break;
	}
}
