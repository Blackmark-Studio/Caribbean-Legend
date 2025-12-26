// boal 08/04/04 общий диалог торговцев
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06

void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	

	string iDay, iMonth, sTemp, sMoney, attrL;
	
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;
	
	int iMoney, iQuantityGoods, iTradeGoods, iTmp;
	
	bool  ok;

	int iTest, cn, i;
	iTest = FindColony(NPChar.City); // город магазина
	ref rColony, chref;
	
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}

	if(!CheckAttribute(npchar, "quest.trade_date"))
	{
		npchar.quest.trade_date = "";
	}
    
	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Store\" + NPChar.City + "_Store.c";
	if(LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	
	// вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	
	string attrLoc   = Dialog.CurrentNode;
	
	if(HasSubStr(attrLoc, "TransferGoodsTo_"))
	{
		NPChar.CharToTransferGoodsID = FindStringAfterChar(attrLoc, "_");
		Dialog.CurrentNode = "TransferGoods_Start";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Kasabada alarm verildi ve herkes seni arıyor. Senin yerinde olsam orada kalmazdım.","Şehirdeki tüm muhafızlar seni arıyor. Ben aptal değilim ve seninle konuşmayacağım!","Koş, "+GetSexPhrase("dostum","lass")+", askerler seni delik deşik etmeden önce..."),LinkRandPhrase("Ne istiyorsunuz, "+GetSexPhrase("serseri","serseri")+"?! Şehir muhafızları zaten senin kokunu aldı, fazla uzağa gidemezsin, "+GetSexPhrase("pislik korsan","katil pisliği")+"!","Pis katil, hemen evimden defol! Muhafızlar!","Senden korkmuyorum, "+GetSexPhrase("creep","pislik")+"! Yakında kalemizde asılacaksın, fazla uzağa gidemezsin..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, bir alarm benim için asla sorun değildir...","Beni asla yakalayamazlar."),RandPhraseSimple("Kapa çeneni, "+GetWorkTypeOfMan(npchar,"")+", yoksa o pis dilini koparırım!!","Heh, "+GetWorkTypeOfMan(npchar,"")+", ve oradaki herkes korsanları yakalamak için burada! Sana şunu söyleyeyim dostum: sessizce oturursan ölmezsin..."));
				link.l1.go = "fight";
				break;
			}
			if (sti(pchar.GenQuest.Piratekill) > 20 && sti(npchar.nation) == PIRATE)
			{
				dialog.text = RandPhraseSimple("Hey, alçak! Ne sanıyorsun, istediğini alabileceğini mi? Tabii ki hayır! Arkadaşlar! Silah başına! Bu manyağı indirin!","Bir şey istiyorsan al, seni kaba herif! Şimdi göstereceğim sana gününü! Beyler, silahlarınızı alın! Dikkat!");
				link.l1 = RandPhraseSimple("Ha? Ne?","Ee, neden bunu yapıyorsunuz?");
				link.l1.go = "fight";
				bDisableFastReload = true;//закрыть переход
				pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
				pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
				pchar.quest.pirate_in_town.function = "TownPirate_battle";
				break;
			}
			//--> Jason Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				//Jason --> мини-квест Дефицитный товар
				if (CheckAttribute(pchar, "questTemp.Wine.Trader") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "Sizden bir parti Avrupa şarabı satın almak istiyorum – elli ya da altmış şişe. Stoklarınızda yeterince olduğunu söylediler."; 
					link.l13.go = "Wine_Trader";
				}
				if (CheckAttribute(pchar, "questTemp.Wine.Repeat2") && NPChar.location == pchar.questTemp.Wine.City + "_store" && CheckCharacterItem(pchar, "letter_1") && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "Tekrar merhaba. Lütfen bu mektuba bir göz atın – belki bana şarap satma konusundaki kararınızı yeniden gözden geçirirsiniz?"; 
					link.l13.go = "Wine_Repeat2";
				}
				if (CheckAttribute(pchar, "questTemp.Wine.wait") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "Yine ben geldim. Yarım kalan şarap anlaşmamıza devam edebilir miyiz? Yeterince para toplamayı başardım."; 
					link.l13.go = "Wine_Price";
				}
				// <-- мини-квест Дефицитный товар
				dialog.text = "Bir şey almak ister miydiniz, monsieur?";
				Link.l1 = "Elbette yaptım - dükkanlar başka ne işe yarar ki? Mallarını göster bana.";
				Link.l1.go = "trade_1";
				Link.l2 = "Belirli bir iş için geldim...";
				Link.l2.go = "quests";
				Link.l3 = "Üzgünüm, ama gitmem gerekiyor.";
				Link.l3.go = "exit";
				// туториал Мартиника
				if(NPChar.City == "FortFrance")
				{
					if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
					{
						Link.l2 = "Dinleyin, efendim, iş arıyorum. Tam zamanlı bir pozisyon ya da yük taşımak değil, daha çok ara sıra işler yapmak gibi. Yardıma ihtiyacınız var mı acaba?";
						Link.l2.go = "Sharlie_storehelper";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
					{
						Link.l2 = "İşinizi hallettim. Gralam Lavoie'yi buldum.";
						Link.l2.go = "Sharlie_storehelper_2";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
					{
						Link.l2 = "Yeni yardımcınızla tanışın, monsieur.";
						Link.l2.go = "Sharlie_storehelper_11";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
					{
						Link.l2 = "Yine ben geldim, monsieur. Ödülümü almaya geldim.";
						Link.l2.go = "Sharlie_storehelper_13";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
					{
						link.l4 = "Şu küpelere bir bakın, monsieur. Onları ormanda öldürülen bir haydutun üstünde buldum. Bunlar kesinlikle usta bir kuyumcunun işi ve eminim ki buralı değil. Bu küpeler hakkında söyleyebileceğiniz bir şey var mı?";
						link.l4.go = "Sharlie_junglejew";
					}
				}
				break;
			}			
			//<-- Бремя гасконца
			
			// Warship, 29.05.11. Дело чести - трусливый фехтовальщик.
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk"))
			{
				dialog.text = "Kaptan, beni kurtardığınız için teşekkür ederim.";
				Link.l1 = "Rica ederim.";
				Link.l1.go = "exit";
				DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk");
				break;
			}
			// Карибские нравы
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "Ne oldu, kaptan? Bir şey mi kaybettiniz? Neden dükkânımda böyle koşturuyorsunuz?";
				Link.l1 = "Şuna bak sen – gerçekten de yaptım! O lanet Gerard LeCroix nerede? Florian Shoke'un bana verdiği tüm görevleri yerine getirdim ve, köpekbalığı beni yutsun, bunu yapmak için canım çıktı! Şimdi ise ödülümü almaya geldiğimde, meğerse bu kuş uçup gitmiş!";
				Link.l1.go = "trial";
				// belamour legendary edition -->
				Link.l2 = "Sana nasıl söyleyebilirim... Kayboldu. Müvekkilimi gördün mü? Adı Gerard LeCroix.";
				Link.l2.go = "trialA";
				//<-- legendary edition
				DelLandQuestMark(npchar);
				break;
			}
			// belamour legendary edition Бесчестный конкурент -->
			if(!CheckAttribute(pchar, "questTemp.Shadowtrader") && sti(npchar.nation) != PIRATE && npchar.location == "baster_store")
			{
				dialog.text = "Kaptan, sizden bir ricam olacak. Bana yardım eder misiniz?";
				link.l1 = "Size nasıl yardımcı olabilirim?"; 
				link.l1.go = "Shadowtrader_begin";
				break;
			}
			// <-- legendary edition			
            dialog.Text = GetNatPhrase(npchar,LinkRandPhrase("Sizi tanıdığıma memnun oldum, efendim! Bu topraklarda yeni misiniz?","Hoş geldiniz, kaptan! Mağazam emrinizde, efendim.","Efendim, lütfen buyurun! Size bu takımadalarda bulabileceğiniz en kaliteli malları sunmaktan mutluluk duyarım."),LinkRandPhrase("Oh, monsieur kaptan! Tüm Fransız kolonilerindeki en iyi mallar - tam burada, tam şimdi ve sadece sizin için!","Ne hoş bir karşılaşma, monsieur! En kaliteli Fransız mallarını sunan en iyi dükkân - hizmetinizde!","Daha önce tanışmış mıydık, monsieur kaptan? Bilirsiniz, dükkânım anavatanın en iyi mağazaları kadar kalitelidir!"),LinkRandPhrase("Oh! Señor kaptan! Sizi mağazamda gördüğüme çok sevindim!","Böylesine parlak bir caballero'yu tüm İspanyol kolonilerinin en seçkin dükkânında ağırlamaktan mutluluk duyuyorum!","Ah, soylu hidalgo! Kader sizi mütevazı dükkanıma getirdi! Burada aradığınız her şeyi bulacaksınız!"),LinkRandPhrase("İyi günler, kaptan efendi. Burası sizin ilk ziyaretiniz mi?","Merhaba, efendim. Buraya ilk gelişiniz mi? Emin olun, Hollanda mallarımızın kalitesi sizi hoş bir şekilde şaşırtacak!","Lütfen buyurun, kaptan efendi! En kaliteli mallar, en uygun fiyatlarla - Hollanda ticaretinin yolu budur!"));
			Link.l1 = LinkRandPhrase("Ben de memnun oldum. Benim adım "+GetFullName(pchar)+" ve bu topraklarda yeniyim sayılırım. Hadi, bana takımadaların zenginliklerini göster!","Ben de tanıştığımıza memnun oldum. Ben "+GetFullName(pchar)+"  ' gemisinin kaptanı."+pchar.ship.name+"'. Peki, bugün hangi fırsatlar var?",""+GetFullName(pchar)+",   ' gemisinin kaptanı "+pchar.ship.name+", tanıştığımıza memnun oldum. Peki, bana ne sunabilirsiniz?");
			link.l1.go = "node_1";
			
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_store")
			{
				dialog.text = "Kaptan Helen! Her zaman bir zevk.";
				link.l1 = "Ben de size minnettarım, teşekkür ederim.";
				link.l1.go = "Helen_node_1";
			}
			NextDiag.TempNode = "Second time";
		break;

		case "second time":
			if (LAi_group_GetPlayerAlarm() > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Kasabada alarm verildi ve herkes seni arıyor. Senin yerinde olsam orada kalmazdım.","Şehirdeki tüm muhafızlar seni arıyor. Ben aptal değilim ve seninle konuşmayacağım!","Koş, "+GetSexPhrase("dostum","lass")+", askerler seni delik deşik etmeden önce..."),LinkRandPhrase("Ne istiyorsun, "+GetSexPhrase("alçak","serseri")+"?! Şehir muhafızları zaten kokunu aldı, fazla uzağa gidemezsin, "+GetSexPhrase("pislik korsan","katil pislik")+"!","Pis katil, derhal evimden çık! Muhafızlar!","Senden korkmuyorum, "+GetSexPhrase("sürüngen","pislik")+"! Yakında kalemizde asılacaksın, fazla uzağa gidemezsin..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, bir alarm benim için asla sorun değildir...","Beni asla yakalayamayacaklar."),RandPhraseSimple("Çeneni kapa, "+GetWorkTypeOfMan(npchar,"")+", yoksa o pis dilini kökünden koparırım!","Heh, "+GetWorkTypeOfMan(npchar,"")+", ve oradaki herkes - korsanları yakalamak için burada! Sana şunu söyleyeyim dostum: sessizce oturursan ölmezsin..."));
				link.l1.go = "fight";
				break;
			}
            
			//--> Jason, Сомнительное предложение
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Trader.busy"))
			{
				dialog.text = "Lütfen, affedin beni, ama şu anda sizinle ilgilenecek vaktim yok.";
				link.l1 = "Evet, tabii. O zaman başka bir zaman uğrarım.";
				link.l1.go = "exit";
				break;
			}
			//<-- Сомнительное предложение
            
			// Warship, 29.05.11. Дело чести - трусливый фехтовальщик.
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk"))
			{
				dialog.text = "Kaptan, beni kurtardığınız için teşekkür ederim.";
				Link.l1 = "Ah, rica ederim.";
				Link.l1.go = "exit";
				DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk");
				break;
			}
			// Карибские нравы
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "Ne oldu, kaptan? Bir şey mi kaybettiniz? Neden dükkânımda böyle dolaşıyorsunuz?";
				Link.l1 = "Şuna bak sen – gerçekten de yaptım! Nerede o lanet olası Gerard LeCroix? Florian Shoke’un bana verdiği tüm görevleri yerine getirdim, ve köpekbalığı beni yutacaksa yutsun, bunu yapmak için canımı dişime taktım! Şimdi ise, ödülümü almaya geldiğimde, meğerse bu kuş çoktan uçup gitmiş!";
				Link.l1.go = "trial";
				// belamour legendary edition -->
				Link.l2 = "Sana nasıl söyleyebilirim... Kayboldu. Müşterimi gördün mü? Adı Gerard LeCroix.";
				Link.l2.go = "trialA";
				//<-- legendary edition
				DelLandQuestMark(npchar);
				break;
			}
 			// belamour legendary edition Бесчестный конкурент -->
			if(!CheckAttribute(pchar, "questTemp.Shadowtrader") && sti(npchar.nation) != PIRATE && npchar.location == "baster_store")
			{
				dialog.text = "Kaptan, sizden bir ricam olacak. Bana yardım eder misiniz?";
				link.l1 = "Size nasıl yardımcı olabilirim?"; 
				link.l1.go = "Shadowtrader_begin";
				break;
			}
			// <-- legendary edition           
			dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Bakın kim gelmiş! Derler ya, paranın kokusu olmaz, o yüzden buyurun kaptan, ticaretimizi yapalım...","Seni gördüğüme sevindiğimi söyleyemem, "+GetFullName(pchar)+"... Ama yine de seninle ticaret yapabilirim.","He-he... Pekâlâ, sizi evime davet etmem, kaptan - ama dükkânım hâlâ hizmetinizde."),LinkRandPhrase("Ah, bak kim gelmiş! Bu   "+GetFullName(pchar)+"! Alışveriş mi yapmak istiyorsun, yoksa bir şeyleri bedavaya mı alacaksın? Şaka yapıyorum tabii...","Seni burada gördüğüme sevindiğimi söyleyemem, "+GetAddress_Form(NPChar)+". Ama harcayacak paran varsa - buyur, buyur içeri...","Ticaret yapmak ister misiniz, kaptan "+GetFullName(pchar)+"? Eğer öyleyse, lütfen biraz acele eder misiniz? Diğer müşteriler sizden uzak duruyor, bu da işime zarar veriyor,"),LinkRandPhrase("Ticaret yapmak ister misiniz, efendim? Bir saniye, parayı sayayım – bilirsiniz, buralarda tekin olmayan tipler dolaşıyor... Tabii, sizi kastetmiyorum kaptan!","Seni açık denizde görseydim, "+GetAddress_Form(NPChar)+", muhtemelen daha fazla yelken sipariş ederdim... Ama burada, dükkanımda, sana bir ticaret teklif edebilirim.","Kaptan, baştan söyleyeyim: Kumaş kanla lekelenmişse ve kahve barut kokuyorsa, almam. Onun dışında, bakın ve seçiminizi yapın.")),LinkRandPhrase(LinkRandPhrase("Ve seni tekrar gördüğüme sevindim, "+GetAddress_Form(NPChar)+"   Almak ya da satmak – size her zaman yardımcı olmaktan memnuniyet duyarım. ","Sana yalvarıyorum, "+GetAddress_Form(NPChar)+", buyurun! En sevdiğim müşterimi burada görmek her zaman beni mutlu eder. Bu sefer neyle geldiniz - almak mı, satmak mı?","Ah, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Sizi tekrar gördüğüme çok sevindim! Bu sefer ne olacak - alış mı, satış mı?"),LinkRandPhrase("Ürünlerimizi beğendiniz mi, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"? Her zaman hizmetinizdeyim - göz atın ve seçiminizi yapın.","Merhaba, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+". Sizi tekrar görmek ne güzel! Ürünlerimize göz atmak ister misiniz?","Sizi görmek ne güzel, kaptan! Kaliteli ürünlerimizi takdir edeceğinizi biliyordum. Yeni gelenlere göz atmak ister misiniz?"),LinkRandPhrase("Ah, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Lütfen buyurun! Tüm mallar sizin için hazır - üstelik bu vesileyle büyük indirimlerimiz var!","Kaptan "+GetFullName(pchar)+", yine ziyaretinizle beni mutlu ettiniz! Lütfen, istediğinizi seçin, ne arzu ediyorsanız!","Bu kez ne arzu edersiniz, kaptan? Hâlâ beni bulmayı hatırlamanıza sevindim. İhtiyacınız olabilecek her türlü malımız var – hem de en iyi kalitede!")));
			Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("Beni böyle mi karşılıyorsun, dostum? Bunu denizde karşılaşırsak hatırlayacağım... Titreme, sadece şaka yapıyordum. Hadi, neler sattığını göster bakalım.","Pekâlâ, dostum. Mallarına ihtiyacım olabilir, ama diline değil. Susabilecek misin, yoksa yardım mı istersin? Kapa çeneni ve mallarını göster."),RandPhraseSimple("Sadede gelelim, tüccar. Seninle ahlak meselelerini tartışacak vaktim yok, o yüzden gel düzgün insanlar gibi ticaretimizi yapalım.","Sakin ol biraz. Şaka yapmak güzel, ama unutma ki sinirlenebilirim... O yüzden beni daha fazla kızdırma ve mallarını göster.")),RandPhraseSimple(RandPhraseSimple("Sizi ziyaret etmek her zaman keyifli. Dikkatimi çekebilecek ne var elinizde?","Seni görmek her zaman güzel, dostum. Peki, aylardır karaya ayak basmamış deniz gezginleri için ne var ne yok?"),RandPhraseSimple("Ve yine, ben buradayım "+XI_ConvertString("Colony"+npchar.City+"Acc")+"! Unutmadığıma sevindim. Ama depolarında benim için bir şey kaldı mı? Yoksa her şey çoktan halledildi mi?","Nasıl gelmezsin? Her zaman bundan fazlasını yaparsın, beni daha çok memnun edersin. Peki, orada neyin var?")));
			link.l1.go = "node_1";
			NextDiag.TempNode = "Second time";
		break;

		case "node_1":
			dialog.text = NPCStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase(RandPhraseSimple("Herkes güverteye! ","Denetim yapın! ")+LinkRandPhrase("Bir     "+GetSexPhrase("beyefendi","beyefendi, ah, affedersiniz - bir hanımefendi")+" şansına ihtiyacın olan her şey mağazamda, he-he?","Zavallı yaşlı bir dükkâncı için ne sürpriz ama! He-he!","Peki, hangi güzel rüzgar sizi dükkanıma getirdi?"),LinkRandPhrase("Limanları açın!","Kancaları yana!","Doğrudan ileriye yelken aç!")+RandPhraseSimple(" Burada bulacaksınız"," Dükkanımda var")+LinkRandPhrase(" adadaki en iyi fiyatlar burada."," mükemmel bir ürün yelpazesi."," en kaliteli mallar mevcut.")+RandPhraseSimple(" Hizmetinizdeyim "," Ne isterseniz")+", kaptan!"),pcharrepphrase(RandPhraseSimple("Herhangi bir mal var mı "+GetSexPhrase("beyler","beyefendiler ve hanımefendiler")+" talihin adamları! He-he! Güneşte kurutulmaya asılana kadar!","Liman’da asılı adamlar rüzgârda sallanıyor, zincirlerin şıngırtısı havada yankılanıyor. Ama paranın kokusu yok, öyle değil mi?"),"İster misiniz "+LinkRandPhrase("en iyi malları satın al "+NationNameGenitive(sti(NPChar.nation)),"yükünü al ya da sat","Karlı bir yükün var mı?")+RandPhraseSimple("? Hizmetinizdeyim!","? Dükkanım hizmetinizde!")+RandPhraseSimple("Seni gördüğüme sevindim"," Sen bilirsin")+", kaptan!")),NPCharRepPhrase(npchar,pcharrepphrase("Benim tavsiyem, Kaptan - saçma mermiden kısmayın. Bilirsiniz, ölüleri aramak çok daha kolaydır!","Senin bir   olduğunu hemen fark ettim "+GetSexPhrase("kurnaz dostum","kurnaz kız")+". "+RandPhraseSimple("Ama şimdi senin gerçekten bir      olduğunu görebiliyorum "+GetSexPhrase("hero","gözüpek")+".","Gençsin, ama "+RandPhraseSimple("aklını başında tutuyorsun.","sizi kandırmak hiç de kolay değil."))),pcharrepphrase("Ele geçirdiğiniz ganimetlerin tüm yükünü sizden almaya hazırım. Ödemeyi gümüşle mi yoksa altınla mı almak istersiniz? O mallar her zaman pahalıdır.","Ticari denizcilik kârlı bir iştir, kaptan "+GetFullName(pchar)+", değil mi?")),NPCharRepPhrase(npchar,RandPhraseSimple("Hepsini ana halatın sıkı bir döngüsüne sardık, yirmi kez halat doladık ve onları kaldırıp gözden kaybolana dek attık! ",RandPhraseSimple("Ölü bir adamın sandığında on beş adam!","İçki ve şeytan diğerlerinin işini bitirdi!")+" Yo ho ho ve bir şişe rom! ")+RandPhraseSimple("Ne var ne yok, kaptan?","Bir şey almak mı istiyorsunuz, kaptan?"),pcharrepphrase("Bakıyorum da pazarlıkta ustasınız, kaptan "+GetFullName(pchar)+" . Siz tekrar gelen bir müşteri olduğunuz için size çok iyi fiyatlar sunuyorum!","Pekâlâ, Kaptan "+GetFullName(pchar)+", size olan saygımdan dolayı, birazcık daha fazlasını sunabilirim! Ne istersiniz?")),NPCharRepPhrase(npchar,"Yemin ederim, seninle konuşmak beni hasta ediyor. "+LinkRandPhrase("Birkaç yer fıstığı al. Domuzlar o şeye bayılır. ","Burada birinin çizmelerini romla parlatmasını mı bekliyorsun? ",pcharrepphrase("Senin gibileri iyi bilirim. Romu kafaya dikip doğruca darağacına gidersiniz.","Annenin seni nasıl denizci olmaya izin verdiğini merak ediyorum! Denizci! Terzi olsan çok daha iyi olurmuşsun...")),pcharrepphrase(RandPhraseSimple("Öyle düşünmüştüm ki ","Ummuştum ki ")+RandPhraseSimple("adamızdan temelli ayrıldığını sanmıştım.","Seni bir daha asla göremeyeceğimi sanmıştım.")+RandPhraseSimple(" Ölüler boynunda birer değirmen taşı gibi asılı duruyor..."," Şu mercanların arasında çürümeye terk ettiğin denizci sayısı ne kadar?!"),"Kaptan "+GetFullName(pchar)+", ticarete olan tutkun tüm beklentilerimi aştı!"+RandPhraseSimple(" Yelken açmadan önce son alışverişlerinizi yapmak ister misiniz?","   Özel bir şey mi arıyorsunuz?"))),"cycle",10,npchar,Dialog.CurrentNode);
			// belamour legendary edition на пару с Акулой -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && npchar.location == "caracas_store")
			{
				if(pchar.questTemp.SharkGoldFleet == "start" || pchar.questTemp.SharkGoldFleet == "afterGvik")
				{
					dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Bakın, kim gelmiş! Derler ya, paranın kokusu olmaz, buyurun kaptan, ticaretimizi yapalım...","Seni gördüğüme sevindiğimi söyleyemem, "+GetFullName(pchar)+"... Ama yine de seninle ticaret yapabilirim.","He-he... Yani, kaptan, sizi evime davet etmem ama dükkânım hâlâ hizmetinizde."),LinkRandPhrase("Ah, bak kim gelmiş! Bu   "+GetFullName(pchar)+"! Alışveriş mi yapmak istiyorsunuz, yoksa bir şeyi bedavaya mı almak? Şaka yapıyorum tabii...","Seni burada gördüğüme pek sevindiğimi söyleyemem, "+GetAddress_Form(NPChar)+". Ama harcayacak paran varsa - buyur, buyur...","Ticaret yapmak ister misiniz, kaptan "+GetFullName(pchar)+"? Eğer öyleyse, lütfen biraz acele eder misiniz? Diğer müşteriler sizden uzak duruyor, bu da işlerime zarar veriyor,"),LinkRandPhrase("Alışveriş yapmak ister misiniz, efendim? Bir saniye, parayı sayayım – bilirsiniz, buralarda biraz tekin olmayan tipler dolaşıyor... Tabii ki sizi kastetmiyorum, kaptan!","Seni açık denizde görseydim, "+GetAddress_Form(NPChar)+", muhtemelen daha fazla yelken sipariş ederdim... Ama burada, dükkânımda, size bir ticaret teklif edebilirim.","Kaptan, baştan uyarayım: kumaş kanla lekelenmişse ve kahve barut kokuyorsa, almam. Onun dışında, buyur bak, seç beğen.")),LinkRandPhrase(LinkRandPhrase("Ve seni tekrar gördüğüme sevindim, "+GetAddress_Form(NPChar)+"Almak ya da satmak - size her zaman yardımcı olmaktan mutluluk duyarım.","Sana yalvarıyorum, "+GetAddress_Form(NPChar)+", buyurun! En sevdiğim müşterimi burada görmek her zaman beni mutlu eder. Bu sefer ne olacak – alıyor musunuz, satıyor musunuz?","Ah, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Sizi tekrar gördüğüme çok sevindim! Bu sefer ne olacak - alım mı satım mı?"),LinkRandPhrase("Ürünlerimizi beğendiniz mi, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"? Her zaman hizmetinizdeyim - göz atın ve seçiminizi yapın.","Merhaba, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+". Sizi tekrar görmek ne güzel! Ürünlerimize göz atmak ister misiniz?","Sizi görmek ne güzel, kaptan! Kaliteli ürünlerimizi beğeneceğinizi biliyordum. Yeniliklerimize göz atmak ister misiniz?"),LinkRandPhrase("Oh, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+" ! Lütfen, buyurun! Tüm mallar sizin için hazır - üstelik bu özel günde büyük indirimlerle!","Kaptan "+GetFullName(pchar)+", tekrar ziyaretinizle beni mutlu ettiniz! Lütfen, istediğinizi seçin, ne arzu ederseniz!","Bu sefer ne arzu edersiniz, kaptan? Hâlâ beni bulmayı unutmamanıza sevindim. İhtiyacınız olabilecek her türlü malımız var – hem de en kaliteli olanından!")));
					link.l14 = "Dinle, şimdi Porto Bello'ya gitmek üzereyim ve senden bir parti kahve ile kakao almak istiyorum. Diyelim, her birinden üç yüz birim."; 
					link.l14.go = "SharkGoldFleet";
				}
			}
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && npchar.location == "caracas_store" && pchar.questTemp.SharkGoldFleet == "buyincar")
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Bakın hele, kim gelmiş! Derler ya, paranın kokusu olmaz, o yüzden buyurun kaptan, alışverişimizi yapalım...","Seni gördüğüme sevindiğimi söyleyemem, "+GetFullName(pchar)+"... Ama yine de seninle ticaret yapabilirim.","He-he... Pekâlâ, kaptan, sizi evime davet etmem ama dükkânım hâlâ hizmetinizde."),LinkRandPhrase("Ah, bak kim gelmiş! Bu   "+GetFullName(pchar)+"! Ticaret mi yapmak istiyorsun yoksa bazı şeyleri bedavaya mı almak? Şaka yapıyorum tabii...","Seni burada gördüğüme sevindiğimi söyleyemem, "+GetAddress_Form(NPChar)+". Ama harcayacak paran varsa - buyur, buyur...","Ticaret yapmak ister misiniz, kaptan "+GetFullName(pchar)+"? Eğer öyleyse, lütfen biraz acele eder misiniz? Diğer müşteriler sizden uzak duruyor, bu da işime zarar veriyor,"),LinkRandPhrase("Ticaret yapmak ister misiniz, efendim? Bir dakika, kasayı sayayım – bilirsiniz, buralarda tekin olmayan tipler dolaşıyor... Tabii ki sizi kastetmiyorum, kaptan!","Seni açık denizde görseydim, "+GetAddress_Form(NPChar)+", muhtemelen daha fazla yelken sipariş ederdim... Ama burada, dükkânımda, sana bir ticaret teklif edebilirim.","Kaptan, baştan söyleyeyim: kumaş kan lekeli, kahve de barut kokuyorsa almam. Onun dışında, buyur bak ve seç beğendiğini.")),LinkRandPhrase(LinkRandPhrase("Ve seni tekrar gördüğüme sevindim, "+GetAddress_Form(NPChar)+" ! Alım ya da satım - size her zaman yardımcı olmaktan mutluluk duyarım.","Sana yalvarıyorum, "+GetAddress_Form(NPChar)+", buyurun! En sevdiğim müşterimi burada görmek her zaman beni mutlu eder. Bu sefer ne olacak - alım mı, satım mı?","Ah, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Sizi tekrar gördüğüme çok sevindim! Bu sefer ne olacak - alacak mısınız, satacak mısınız?"),LinkRandPhrase("Ürünlerimizi beğendiniz mi, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"? Her zaman hizmetinizdeyim - göz atın ve seçiminizi yapın.","Merhaba, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+". Sizi tekrar görmek güzel! Ürünlerimize göz atmak ister misiniz?","Sizi görmek güzel, kaptan! Kaliteli ürünlerimizi takdir edeceğinizi biliyordum. Yeni gelenlere göz atmak ister misiniz?"),LinkRandPhrase("Ah, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Lütfen, buyurun! Tüm mallar sizin için hazır - üstelik bu vesileyle büyük indirimlerle!","Kaptan "+GetFullName(pchar)+", yine ziyaretinle beni mutlu ettin! Lütfen, istediğini seç, ne istersen al!","Bu sefer ne arzu edersiniz, kaptan? Hâlâ beni bulmayı unutmamanıza sevindim. İhtiyacınız olabilecek her türlü malımız var – hem de en kaliteli olanlarından!")));
				link.l14 = "Kahve ve kakao için buradayım. "; 
				link.l14.go = "SharkGoldFleet_again";
			}
										
			// <-- на пару с Акулой
			link.l1 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Bana neler sattığını göster, eski korsan!","Sadece mallarınıza bir göz atmak istedim, iyi adamım."),pcharrepphrase("İdam sehpası üzerine yemin ederim, "+GetFullName(npchar)+", beni oyalamana izin vermeyeceğim! Hemen mallarını göster bana!","Şu mallarınıza bir bakalım, "+GetAddress_FormToNPC(NPChar)+".")),NPCharRepPhrase(npchar,pcharrepphrase("Orası kesin! Ölüler ısırmaz! Şimdi, ambarında ne var bakalım?","İşinize bakmanız en iyisi olur, iyi adamım. Bana ne tür mallar sunabilirsiniz?"),pcharrepphrase("Bir gün gelip sen benim ganimetim olacaksın, heh-heh. Şaka yapıyorum. Mallarını göster bakalım.","İşlerimizi konuşalım, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"")),NPCharRepPhrase(npchar,pcharrepphrase("Ne mi istiyorum? Bir şey satın almak istiyorum!","İçki seni mezara götürecek, "+GetFullName(npchar)+". Mallarınıza göz atmak istiyorum."),pcharrepphrase("İndirimlerini biliyorum! Üç pound fiyatına iki pound kakao! Şimdi mallarını göster bakalım.","Bu her zaman iyidir. O zaman pazarlık yapalım.")),"Ne sattığını göster. Lafı uzatmayalım. Acelem var.",npchar,Dialog.CurrentNode);
			link.l1.go = "market";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Ah, birini bıçaklamayı gerçekten isterdim. Neyse, hadi işe koyulalım.","Hadi diğer işlere geçelim, iyi adamım."),pcharrepphrase("Caramba! Ben burada başka bir iş için geldim!","Sizinle özel bir iş hakkında konuşmak istiyorum, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+".")),NPCharRepPhrase(npchar,pcharrepphrase("Seninle bir işim var, yaşlı korsan!","Hadi işe koyulalım, dostum!"),pcharrepphrase("Şeytana yemin ederim, beni kandıramazsın, alçak! Seninle başka bir hesabım var!","Kesinlikle katılıyorum, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+", sizinle başka konuları konuşmak istiyordum.")),NPCharRepPhrase(npchar,pcharrepphrase("Şimdiden hazır mısın? Seninle konuşacak işlerim var.","Ben buraya ticaret için gelmedim, iyi adamım. Başka işlerim var."),pcharrepphrase("Bu fiyatlarla yıldırım çarpsın seni! Seninle bir işim var.","İndirimler her zaman güzeldir, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+", ama sizinle başka bir işim var.")),NPCharRepPhrase(npchar,pcharrepphrase("Dilini tut, yaşlı ayyaş, seninle işim var","Sanırım romdan hastasın. Ben de senden pek hoşlanmıyorum açıkçası. Hadi işimize bakalım."),pcharrepphrase("Beni zaten kazıkladın, alçak! Seninle işim var.","İroniniz yersiz. Sizinle başka bir işim var.")),npchar,Dialog.CurrentNode);
			link.l2.go = "business";
			/*link.l3 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Önce iş, sonra eğlence. Sana bir şey sormak istiyorum.","Şu anda değil. Bilgiye ihtiyacım var."),pcharrepphrase("Fiyatlarını cehenneme yolla! Önce bana bilmem gereken her şeyi anlatacaksın.","Memnuniyetle. Size bir şey sormak istiyordum.")),NPCharRepPhrase(npchar,pcharrepphrase(" Tavsiyen için sağ ol, eski katil. Sana bir şey sormak istiyordum. ","Özel bir sorum vardı."),pcharrepphrase("Altın bekleyebilir. Sana bir şey sormak istiyordum.","Evet, katılıyorum. Sana bir şey sormak istiyordum.")),NPCharRepPhrase(npchar,pcharrepphrase("Sanırım ne soracağımı biliyorsun.","Umarım soruma cevap verirsiniz."),pcharrepphrase("Fiyat etiketlerinden başka bir şey aklına geliyor mu? Çünkü sana tam da bunu sormak üzereydim.","Bu beni ilgilendirmiyor. Bilgiye ihtiyacım var.")),NPCharRepPhrase(npchar,pcharrepphrase("Çok heyecanlanma, dostum! Sadece sana bir soru soracaktım.","Çok heyecanlanma, yoksa felç geçirirsin. Sadece bir soruya cevap ver, sonra gideceğim"),pcharrepphrase("Senden akıllıca bir şey söylemeni beklemiyorum, çünkü bir hamam böceği kadar beynin var. Ama elbette bir şeyler biliyor olmalısın.","Sizi fazla oyalamayacağım. Sadece bir sorum olacak.")),npchar,Dialog.CurrentNode);*/
			//link.l3 = "Başka bir işle meşgulüm.";
			//link.l3.go = "quests";
			// --> Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "Sana kasabanın fiyat listesini getirdim "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//<--генер почтового курьера 2 уровня	
						
			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.Trader") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "Sizden bir parti Avrupa şarabı almak istiyorum - elli ya da altmış şişe. Stoklarınızda yeterince olduğu söylendi bana.."; 
				link.l13.go = "Wine_Trader";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.Repeat2") && NPChar.location == pchar.questTemp.Wine.City + "_store" && CheckCharacterItem(pchar, "letter_1") && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "Tekrar merhaba. Lütfen, şu mektuba bir göz atın – belki bana şarap satma konusundaki fikrinizi tekrar gözden geçirirsiniz?"; 
				link.l13.go = "Wine_Repeat2";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.wait") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "Yine ben geldim. Yarım kalan şarap anlaşmamıza devam edebilir miyiz? Yeterince para buldum."; 
				link.l13.go = "Wine_Price";
			}
			// <-- мини-квест Дефицитный товар
			
			// туториал Мартиника
			if(CheckAttribute(pchar, "questTemp.Sharlie.Lock") && NPChar.City == "FortFrance")
			{
				if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
				{
					Link.l2 = "Dinleyin, efendim, iş arıyorum. Tam zamanlı bir pozisyon ya da ağır yük taşıma işi değil, daha çok ufak tefek işler, tabiri caizse ayak işleriyle ilgileniyorum. Yardıma ihtiyacınız var mı, acaba?";
					Link.l2.go = "Sharlie_storehelper";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
				{
					Link.l2 = "İşinizi hallettim. Gralam Lavoie'yi buldum.";
					Link.l2.go = "Sharlie_storehelper_2";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
				{
					Link.l2 = "Yeni yardımcınızla tanışın, monsieur.";
					Link.l2.go = "Sharlie_storehelper_11";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
				{
					Link.l2 = "Yine ben geldim, monsieur. Ödülümü almaya geldim.";
					Link.l2.go = "Sharlie_storehelper_13";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
				{
					link.l4 = "Şu küpelere bir bakın, monsieur. Onları ormanda öldürülen bir haydutun üzerinde buldum. Bunlar kesinlikle usta bir kuyumcunun işi, eminim ki buralı değil. Bu küpeler hakkında söyleyebileceğiniz bir şey var mı?";
					link.l4.go = "Sharlie_junglejew";
				}
			}
						
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "store_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l9 = "Merhaba, oğlunuzun davetiyle geldim."; 
					link.l9.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "store_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "Bu, kızınızla ilgili...";
						link.l9.go = "EncGirl_1";
					}
				}				
			}			
			link.l5 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Görüşürüz, yaşlı ayyaş.","Güzel bir gün geçir, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"."),pcharrepphrase("Caramba! Hiçbir yere gitme, birazdan döneceğim.","Burada olman güzeldi, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"! Hoşça kal!")),NPCharRepPhrase(npchar,pcharrepphrase("Demir alın!","Hoşça kal, iyi adamım."),pcharrepphrase("Hey! Orada ne saklıyorsun? Rom mu? Hayır mı? Peki, o zaman gidip boğazımı ıslatayım.","Üzgünüm, ama şehirde acil işlerim var.")),NPCharRepPhrase(npchar,pcharrepphrase("Heh! Pekala, görüşürüz!","Gitmem gerek. Hoşça kal, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!"),pcharrepphrase("Benimle tartışmayı aklından bile geçirme! Buna ayıracak vaktim yok!","Belki de gemimde neler olup bittiğine bakmalıyım. Hoşça kal, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),NPCharRepPhrase(npchar,pcharrepphrase("Ne var ne yok, ihtiyar dostum? Benim - "+GetFullName(pchar)+"! Kendine gel, sonra tekrar uğrarım.","Korkarım, sana bir daha gelme fırsatım olmadan ciğerin seni bitirecek."),pcharrepphrase("Guinealarını ve doblonlarını saymaya devam et, kurnaz tilki! Geri döneceğim.","Seni gördüğüme sevindim, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),npchar,Dialog.CurrentNode);
			link.l5.go = "exit";
		break;
		
		case "Helen_node_1":
			dialog.text = "Sana nasıl yardımcı olabilirim? Rainbow'u doldurmak, ganimet satmak ister misin? Şu an kârlı yükler ilgini çeker mi sanmam, ha-ha.";
			link.l1 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Bana neler sattığını göster, eski korsan!","Sadece mallarınıza bir göz atmak istedim, iyi adamım."),pcharrepphrase("İdam sehpası üzerine yemin ederim, "+GetFullName(npchar)+", beni başından savmana izin vermeyeceğim! Hemen mallarını göster bana!","Malınıza bir göz atalım, "+GetAddress_FormToNPC(NPChar)+".")),NPCharRepPhrase(npchar,pcharrepphrase("Orası kesin! Ölüler ısırmaz! Şimdi, ambarında ne var bakalım?","İşinize bakmanız en iyisi olur, iyi adamım. Bana ne tür mallar sunabilirsiniz?"),pcharrepphrase("Bir gün geldiğinde benim ganimetim olacaksın, heh-heh. Şaka yapıyorum. Mallarını göster bakalım.","İşlerimizi konuşalım, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"")),NPCharRepPhrase(npchar,pcharrepphrase("Ne mi istiyorum? Bir şey satın almak istiyorum!","İçki seni mezara götürecek, "+GetFullName(npchar)+". Mallarınıza bir göz atmak istiyorum."),pcharrepphrase("İndirimlerini biliyorum! Üç pound fiyatına iki pound kakao! Şimdi mallarını göster bakalım.","Bu her zaman iyidir. O zaman pazarlık edelim.")),"Ne sattığını göster. Lafı uzatmaya gerek yok. Acelem var.",npchar,Dialog.CurrentNode);
			link.l1.go = "market";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Ah, birini bıçaklamayı gerçekten isterdim. Peki, hadi işe koyulalım.","Şimdi asıl işimize dönelim, iyi adamım."),pcharrepphrase("Caramba! Ben burada başka bir iş için geldim!","Sizinle özel bir iş hakkında konuşmak istiyorum, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+".")),NPCharRepPhrase(npchar,pcharrepphrase("Seninle bir işim var, yaşlı korsan!","Hadi işe koyulalım, dostum!"),pcharrepphrase("Şeytana yemin ederim, beni kandıramazsın, alçak! Seninle başka bir hesabım var!","Kesinlikle katılıyorum, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+", sizinle başka konuları konuşmak istiyordum.")),NPCharRepPhrase(npchar,pcharrepphrase("Zaten hazır mısın? Seninle konuşacak işlerim var.","Buraya ticaret için gelmedim, iyi adamım. Başka işlerim var."),pcharrepphrase("Böyle fiyatlara yıldırım çarpsın seni! Seninle bir işim var.","İndirimler her zaman güzeldir, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+", ama sizinle başka bir işim var.")),NPCharRepPhrase(npchar,pcharrepphrase("Dilini tut, yaşlı ayyaş, seninle işim var","Sanırım romdan hastasın. Ben de senden pek hoşlanmıyorum açıkçası. Hadi işimize bakalım."),pcharrepphrase("Beni zaten dolandırdın, alçak! Seninle bir işim var.","İronin yersiz. Seninle başka bir işim var.")),npchar,Dialog.CurrentNode);
			link.l2.go = "business";
			link.l3 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Önce iş, sonra eğlence. Sana bir şey sormak istiyorum.","Şu anda değil. Bilgiye ihtiyacım var."),pcharrepphrase("Senin fiyatların batsın! Önce bana bilmem gereken her şeyi anlatacaksın.","Memnuniyetle. Size bir şey sormak istiyordum.")),NPCharRepPhrase(npchar,pcharrepphrase("Tavsiyen için sağ ol, eski katil. Sana bir şey sormak istiyordum.","Özel bir sorum vardı."),pcharrepphrase("Altın bekleyebilir. Sana bir şey sormak istedim.","Evet, katılıyorum. Sana bir şey sormak istiyordum.")),NPCharRepPhrase(npchar,pcharrepphrase("Bence ne soracağımı zaten biliyorsunuz.","Umarım soruma cevap verirsiniz."),pcharrepphrase("Fiyat etiketlerinden başka bir şey aklına geliyor mu? Çünkü sana tam da bunu sormak üzereydim.","Bu beni ilgilendirmiyor. Bilgiye ihtiyacım var.")),NPCharRepPhrase(npchar,pcharrepphrase("Çok heyecanlanma dostum! Sadece sana bir soru soracaktım.","Çok heyecanlanma, yoksa felç geçirirsin. Sadece bir soruma cevap ver, sonra gideceğim."),pcharrepphrase("Senden akıllıca bir şey söylemeni beklemiyorum, çünkü bir hamam böceği kadar zekân var. Ama eminim bir şeyler biliyorsundur.","Sizi fazla oyalamayacağım. Sadece bir sorum olacak.")),npchar,Dialog.CurrentNode);
			link.l3.go = "quests";
			link.l5 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Görüşürüz, yaşlı ayyaş.","Güzel bir gün geçir, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"."),pcharrepphrase("Caramba! Hiçbir yere gitme, yakında döneceğim.","Burada olman güzeldi, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"! Hoşça kal!")),NPCharRepPhrase(npchar,pcharrepphrase("Demir alın!","Hoşça kal, iyi adamım."),pcharrepphrase("Hey! Orada ne saklıyorsun? Rom mu? Hayır mı? Peki, ben de gidip boğazımı ıslatayım.","Üzgünüm, ama şehirde acil işlerim var.")),NPCharRepPhrase(npchar,pcharrepphrase("Heh! Pekala, görüşürüz!","Gitmem gerek. Hoşça kal, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!"),pcharrepphrase("Ve benimle tartışmayı aklından bile geçirme! Buna ayıracak vaktim yok!","Belki de gemimde neler olup bittiğine bakmalıyım. Hoşça kal, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),NPCharRepPhrase(npchar,pcharrepphrase("Ne haber, ihtiyar dostum? Benim - "+GetFullName(pchar)+"! Kendine gel, sonra tekrar uğrarım.","Korkarım, sana bir daha uğrama fırsatım olmadan ciğerin seni bitirecek."),pcharrepphrase("Guinealarını ve dublonlarını saymaya devam et, kurnaz tilki! Geri döneceğim.","Seni gördüğüme sevindim, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),npchar,Dialog.CurrentNode);
			link.l5.go = "exit";
		break;

		case "market":
//navy -->
			//занят ПГГ
			if (CheckFreeServiceForNPC(NPChar, "Store") != -1)	 // to_do имя сунуть
			{
				dialog.text = "Üzgünüm, ama şu anda çok meşgulüm. O kadar çok müşteri var ki! Yarın tekrar gel.";
				link.l1 = "Gerçekten mi? O zaman, sonra tekrar uğrarım.";
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = RandPhraseSimple("Yuvarlak gülle, yelken bezi, ilaç, kaliteli kereste ve başka mallarım var! Hangisiyle ilgileniyorsunuz?","Şeker ve baharat almak ister misiniz? Ya da belki rom ve barut?");
			link.l1 = pcharrepphrase(LinkRandPhrase("Ambarımda bir sürü ganimet var! Paranın kokusu olmaz, değil mi?","Ambarımdaki ganimeti boşaltıp, yerine senin altınlarını doldurmam lazım. Ha-ha!","Ah, sen anneni bile tam tartılmış bir kese dublon için satarsın, biliyorum! Ama benim sadece erzaklarımı yenilemem gerek."),LinkRandPhrase("Yükümü satmak ve erzaklarımı yenilemek istiyorum.","Satış için mal satın almak istiyorum.","Bana top güllelerini, bombaları ve buna benzer şeyleri göster."));
			link.l1.go = "trade_1";

			if(CheckFunctionalTreasurer() && CheckAttribute(PChar, "TransferGoods.Enable")) // Автозакупка товаров
			{
				link.l5 = "Katibim tüm gerekli alışverişleri yapacak...";
				link.l5.go = "TransferGoods";
			}
			
			link.l3 = pcharrepphrase(RandPhraseSimple("Alışveriş yapmadan gidiyorum. Görüşürüz!","Biraz içki içip ağzımı ıslatacağım. Sen orada kal!"),RandPhraseSimple("Hayır, şu anda ticaret için vaktim yok. Hoşça kal.","Üzgünüm, acil işlerim var. Hoşça kalın!"));
			link.l3.go = "exit";
		break;
		
		case "EncGirl_1":
			dialog.text = "Tamamen sizi dinliyorum.";
			link.l1 = "Kaçağını getirdim.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Ah, kaptan, çok teşekkür ederim! Nasıl, iyi mi? Yaralandı mı? Yaramaz kız, kaçalı bir gün oldu. Ona zarar verecek biri gibi mi görünüyorum? Ona bir koca buldum. Evlilik ayarladım. Zengin, genç bir nişanlı. Belki çok yakışıklı değil ama kimin umurunda görünüş? Hayır! Hep kendi bildiğini okur. Tıpkı annesi gibi, kahretsin!\nGerçi, annesi de zamanında umut vadeden bir aptalla kaçmasaydı, o doğmazdı... neyse... Gençlik işte, saf, düşüncesiz ve acımasız.";
			link.l1 = "Elbette, babası sensin ve karar vermek sana kalmış, ama ben düğün için acele etmezdim...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "Ne biliyorsun ki? Senin de çocuğun var mı? Yok mu? O zaman benimle konuş, bir gün olursa...\nEvet... Onu geri getiren kişiye ödül vadetmiştim. Al, işte ödülün.";
			link.l1 = "Teşekkürler. Ve ona göz kulak ol. İçimde bir his var, bununla yetinmeyecek gibi.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Demek sen   "+GetSexPhrase("getiren o kaptan","getiren o kız")+"   hovardalığa meyilli oğlum genç bir gelinle mi?";
				link.l1 = "Evet, kaçmalarına yardım ettim.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Ah, orada "+GetSexPhrase("o, bizim iyilikseverimiz","O, bizim hayırseverimiz")+"   Bir ödül bekliyorsun, öyle mi? ";
				link.l1 = "Pekâlâ, ödül istemem ama teşekkürünüz yeter.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Çocuğumu zor durumda bırakmadığınız ve onu hassas bir durumdan çıkarmak için yardım ettiğiniz için size çok minnettarım. Size teşekkür etmeme izin verin, lütfen bu mütevazı miktarı ve şahsen benden bir hediyeyi kabul edin.";
			link.l1 = "Teşekkür ederim. Bu genç çifte yardımcı olmak benim için bir zevkti.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Teşekkür mü? Ne teşekkürü?! O sersem yarım yıldır işsiz güçsüz dolaşıyor – bir de bak hele, aşk meşk işlerine vakit buluyor! Ben onun yaşındayken kendi işimi kurmuştum! Püh! Vali'nin evlenme çağına gelmiş bir kızı var – ama o ahmak, kimseleri olmayan bir kızı evime getirdi, üstüne üstlük bir de benden hayır duası istemeye cüret etti!";
			link.l1 = "Hmm... Görünen o ki, gerçek duygulara inanmıyorsun?";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "Ne hisleri? Hangi hislerden bahsediyorsun? Hisler... Senin yaşında biri nasıl bu kadar düşüncesiz olabilir?! Gençlerin heveslerine boyun eğip onları şımartmakla kalmayıp bir de aracılık ediyorsun! Sadece bir kızı evinden alıp götürmekle kalmadın, acemimin hayatını da mahvettin. Sana teşekkür falan yok. Elveda.";
			link.l1 = "Peki, sana da aynı şekilde...";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
		// Warship. Автозакупка товаров -->
		case "TransferGoods":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				dialog.text = LinkRandPhrase("...Zaten hallettim. Şimdi geriye sadece hangi gemiye yükleme yapacağımıza karar vermek kaldı.","Haznedarınız bunu zaten yaptı. Şimdi hangi geminin yükleneceğine karar verelim.","Evet, "+PChar.name+", biliyorum. Zaten bana uğradı. Şimdi, hangi gemiye yükleme yapacağız?");
					
				for(i=0; i<COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						if(!GetRemovable(chref)) continue;
						
						attrL = "l"+i;
						Link.(attrL)    = "It will be " + XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
						Link.(attrL).go = "TransferGoodsTo_" + chref.id;
					}
				}
				
				Link.l99 = "Fikrimi değiştirdim, başka bir şeye gerek yok.";
				Link.l99.go = "exit";
			}
			else // Корабля нету
			{
				dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("Benimle dalga mı geçiyorsun? Gemin nerede? İskelede göremiyorum!","Şeytana yemin ederim, beni kandıramazsın! Gemin iskelede değil!"),pcharrepphrase("Liman’da geminizi göremiyorum, Kaptan "+GetFullName(pchar)+". Umarım o 'Uçan Hollandalı' değildir?","Kaptan, yükü iskeleden yüklemek çok daha kolay. Ben de böyle yapmayı tercih ederim. Gemini çabucak getir ve geri dön."));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"Ne dert ama! Peki, kurnaz ihtiyar, yakında görüşürüz!","Seni kandırmak istemedim, "+GetFullName(npchar)+", adanın diğer tarafında bir gemi var."),pcharrepphrase("Hayır. Gemimin adı 'Kara İnci.' Neden yüzün bembeyaz oldu? Haha! Şaka yaptım sadece!"," Tavsiyeniz için teşekkürler, mutlaka dikkate alacağım. "));
				link.l1.go = "exit";
			}
			break;
			
		case "TransferGoods_2": // Тут уже не проверяем, есть корабль или нету (выбрали корабль, в который груз не помещается)
			dialog.text = LinkRandPhrase("Peki, kaptan, hangi gemiyi yükleyeceğiz?","O halde, hangi gemi yüklenecek?",PChar.name+", malları hangi geminin ambarına yüklemeliyiz?");
				
			for(i=0; i<COMPANION_MAX; i++)
			{
				cn = GetCompanionIndex(PChar, i);
				if(cn > 0)
				{
					chref = GetCharacter(cn);
					if(!GetRemovable(chref)) continue; // Если квестовый - пропускаем
					
					attrL = "l"+i;
					Link.(attrL)    = "It will be " + XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
					Link.(attrL).go = "TransferGoodsTo_" + chref.id;
				}
			}
			
			Link.l99 = "Fikrimi değiştirdim, hiçbir şeye ihtiyacım yok.";
			Link.l99.go = "exit";
			break;
			
		case "TransferGoods_Start":
			chref = CharacterFromID(NPChar.CharToTransferGoodsID);
			
			iQuantityGoods = TransferGoods_CalculateWeight(chref);
			
			if(GetCargoFreeSpace(chref) >= iQuantityGoods)
			{
				if(TransferGoods_StartTransfer(chref, NPChar.City) != 0)
				{
					dialog.text = LinkRandPhrase("Her şey hazır! Seçilen geminin yüklemesi başladı.","Pekala, seçilen gemiye malların yüklenmesine başlandı.","Kaptan, seçilen gemiye malların yüklenmesi başladı.");
					link.l1 = "Teşekkür ederim. Sizinle iş yapmak bir zevkti.";
					link.l1.go = "exit";
          SetPriceListByStoreMan(rColony); // mitrokosta обновляем список цен
					WaitDate("", 0, 0, 0, 1, 0); // Крутим время
				}
				else
				{
					dialog.text = LinkRandPhrase("Kaptan, veznedarınızın istediği tüm mallar, belirttiğiniz gemiye çoktan yüklendi!","Kaptan, tüm mallar zaten belirttiğiniz gemiye yüklendi!","Kaptan, o geminin bakıma ihtiyacı yok, çünkü tüm mallar zaten orada.");
					link.l1 = "Evet, tabii.";
					link.l1.go = "exit";
					link.l2 = "Demek ki başka bir gemi seçmem gerekecek, o zaman.";
					link.l2.go = "TransferGoods_2";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Korkarım, o tip bir gemi bu kadar yükü taşıyamaz.","Kaptan, geminiz o kadar yükü taşıyamaz!","Kaptan, geminizin ambarı bu kadar yükü alamaz!");
				link.l1 = "Evet, haklısınız. Başka bir gemi seçmem gerekecek.";
				link.l1.go = "TransferGoods_2";
				link.l2 = "Bir süredir düşünüyorum... Hiçbir şey almama gerek yok.";
				link.l2.go = "exit";
			}
			break;
		// <-- Автозакупка товаров

		case "trade_1":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
			    DialogExit();
			    Pchar.PriceList.StoreManIdx = rColony.index; // boal 27.02.05
			    LaunchStore(sti(rColony.StoreNum));
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar,pcharrepphrase("Benimle dalga mı geçiyorsun? Gemin nerede? İskelede göremiyorum!","Şeytana yemin ederim, beni kandıramazsın! Gemin iskelede değil!"),pcharrepphrase("Liman’da geminizi göremiyorum, Kaptan "+GetFullName(pchar)+". Umarım o 'Uçan Hollandalı' değildir?","Kaptan, yükü iskeleden almak çok daha kolay. Geminizi hemen getirin ve geri dönün."));
				link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"Ne dert ama! Peki, kurnaz ihtiyar, yakında görüşürüz!","Seni kandırmak istemedim, "+GetFullName(npchar)+", adanın diğer tarafında bir gemi var."),pcharrepphrase("Hayır. Gemimin adı 'Kara İnci.' Neden yüzün soldu? Haha! Şaka yapıyorum!"," Tavsiyeniz için teşekkürler, bundan faydalanacaklar. "));
			    link.l1.go = "exit";//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		break;

		case "storage_0":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 
			{
				dialog.text = "Kira konusunda, bana hâlâ borcun var "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
				{
					link.l1 = "Pekala, şimdi kiranın parasını ödeyeceğim.";
					link.l1.go = "storage_3";
				}
				else
				{
					link.l1 = "Daha sonra geri geleceğim.";
					link.l1.go = "exit";
				}
			}		
			else
			{
				dialog.text = "Gel.";
				link.l1 = "Teşekkürler.";
				link.l1.go = "storage_2";
			}
			link.l2 = "Hayır, fikrimi değiştirdim.";
			link.l2.go = "exit"; 						
		break;
		
		case "storage_01":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "Evet, limanda bir depom var - 50.000 kentner yük alabilir. "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+" ayda, mallarınızı güvende tutabilirim. "+"Bu, koruma, su baskınlarına karşı önlem alma ve farelerle ilgilenmeyi de kapsıyor. Ne dersiniz? Ayrıca... Bir aylık ücreti peşin almam gerekecek.";	
			link.l1 = "Takım elbisesi. Bakabilir miyim? Orada çok fare var mı?";
			link.l1.go = "storage_1";
			link.l2 = "Hayır, sadece soruyorum. Gerekirse kullanabilirim...";
			link.l2.go = "exit";
		break;
		
		case "storage_1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "Dediğim gibi, ödemeyi bir ay önceden isterim. Ve fare istemem!";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "Oldukça ticari birisiniz, doğrusu. Alın paranız - bu depoyu kiralıyorum.";
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = "Oldukça ticari birisiniz, doğrusu. Peki, parayla yakında döneceğim.";
				link.l1.go = "exit";
			}
		break;
		
		case "storage_11":
			AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForStorage)); 
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			NPChar.Storage.Activate = true;
			Achievment_Set("ach_67"); // ugeen 2016
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
				
		case "storage_2":			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
		
		case "storage_3":			
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;		

		case "storage_04":
			dialog.text = "Şimdiden mi gidiyorsunuz? Ne yazık - burası gerçekten harika şartlara sahip mükemmel bir yer. Emin olun, Karayipler'de böyle bir fırsatı başka yerde bulamazsınız.";
			link.l1 = "Dedim ki - affet. Yoksa havayı depolamanın parasını mı ödeyeyim diyorsun? Başka bir kiracı ara.";
			link.l1.go = "storage_4";
			link.l2 = "Karayipler'de hiçbir yerde yok diyorsun? Peki, o zaman bir süreliğine vazgeçiyorum.";
			link.l2.go = "exit";
		break;
		
		case "storage_4":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar,"Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 			
			{
				dialog.text = "Ve kiraya gelince, hâlâ bana borcun var "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))			
				{
					link.l1 = "Pekâlâ.";
					link.l1.go = "storage_5";
				}
			}
			else
			{
				dialog.text = "Eşyalarını topla, ben de depoyu kapatacağım.";
				link.l1 = "Pekâlâ.";
				link.l1.go = "storage_6";
			}
		break;
		
		case "storage_5":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.Storage.NoActivate = true;
			DeleteAttribute(NPChar,"Storage.Activate");
			DialogExit();
		break;
		
		case "storage_6":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			DeleteAttribute(NPChar,"Storage.Activate");
			NPChar.Storage.NoActivate = true;
			DialogExit();
		break;		

		case "business":
			iTest = 0;			
	
	
			//Jason --> генератор Сомнительное предложение
			/*if (hrand(3) == 1 && !CheckAttribute(pchar, "GenQuest.Contraoffer.Trader") && !CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes") && sti(npchar.nation) != PIRATE && 7-sti(RealShips[sti(pchar.ship.type)].Class) > 0) 
			{
				if (!CheckAttribute(npchar, "Contraoffer") || GetNpcQuestPastDayParam(npchar, "Contraoffer") >= 30) 
				{
					dialog.text = "Oh! Tam zamanında geldiniz, Kaptan. Sizden bir iyilik isteyecektim.";
					link.l1 = "Dinleyelim."; 
					link.l1.go = "Contraoffer";
					break;
				}
			}
		
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Trader") && NPChar.location == pchar.GenQuest.Contraoffer.Trader.City + "_store") 
			{
				dialog.text = "Sizi dinliyorum, kaptan.";
				link.l5 = "Siparişinizi getirdim."; 
				link.l5.go = "Contraoffer_check";
			}
			
			if (!CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves") && sti(npchar.quest.Contraoffer.chance) == 2 && GetNpcQuestPastDayParam(npchar, "Contraoffer") >= 30) //единичный вариант за всю игру, ака 'пасхалка'
			{
				dialog.text = "Oh! Tam zamanında geldiniz, Kaptan. Sizden özel bir ricam olacak.";
				link.l5 = "Dinleyelim."; 
				link.l5.go = "Contraoffer_slaves";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes") && NPChar.location == pchar.GenQuest.Contraoffer.Slaves.City + "_store") 
			{
				dialog.text = "Sizi dinliyorum, kaptan.";
				link.l5 = "Sana köleleri getirdim."; 
				link.l5.go = "Contraoffer_slaves_check";
			}*/
			// <-- генератор Сомнительное предложение
	
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_store" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Dinle, her türlü mal alıp satıyorsun... Dün ya da bugün - sana satmak isteyen biri oldu mu "+pchar.GenQuest.Device.Shipyarder.Type+"?";
				link.l16.go = "Device_Trader";
			}
			// <-- генератор Неудачливый вор
			
			//Jason --> генератор Место под солнцем
			// belamour legendary edition втречается чаще
			if (!CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && !CheckAttribute(npchar, "quest.Sunplace") && sti(npchar.nation) != PIRATE && sti(pchar.rank) < 20 && hrand(2) == 2 && !CheckAttribute(pchar, "questTemp.Shadowtrader_Block")) 
			{
				dialog.text = "Kaptan, sizden bir iyilik isteyeceğim ve kabul ederseniz sizi cömertçe ödüllendireceğim.";
				link.l1 = "İlginç. Peki, sorun ne?"; 
				link.l1.go = "Sunplace_begin";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "complete" && npchar.location == pchar.GenQuest.Sunplace.Trader.City + "_store") 
			{
				dialog.text = "Kaptan, sizi görmekten memnun oldum. İsteğimi yerine getirdiğinizi zaten biliyorum, "+pchar.GenQuest.Sunplace.Trader.Enemyname+".";
				link.l1 = "Heh! Orası kesin. "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType),"Name")))+" "+pchar.GenQuest.Sunplace.Trader.ShipName+" ve yük - "+GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods))+", artık rakibinize ait değil."; 
				link.l1.go = "Sunplace_complete";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "complete_murder" && npchar.location == pchar.GenQuest.Sunplace.Trader.City + "_store") 
			{
				dialog.text = "Efendim, Kaptan... Neden onu öldürdünüz? Ben sadece gemisini batırmanızı istemiştim! Kutsal Meryem, şimdi masum bir adamın kanı ellerimde...";
				link.l1 = "Heh! Sana ne oldu, "+npchar.name+"? Kimin umurunda – seni bir daha asla rahatsız etmeyecek, önemli olan da bu!"; 
				link.l1.go = "Sunplace_complete_murder";
				break;
			}
			// <-- генератор Место под солнцем
			
//navy -->
			//занят ПГГ
			iTmp = CheckAvailableTaskForNPC(NPChar, PGG_TASK_WORKONSTORE);
			if (iTmp != -1)
			{
				dialog.text = "Bir işim vardı, ama "+GetFullName(&Characters[iTmp])+" bunu zaten benim için yapmayı üstlendi.";
				link.l1 = "Gerçekten mi? O halde, daha sonra tekrar uğrarım.";
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = NPCharRepPhrase(npchar,"Ne işi?! Her şeyi anlat bana!","Dinliyorum. Bahsettiğiniz anlaşma nedir?");
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
            if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
    			if (CheckQuestAttribute("generate_trade_quest_progress", "begin") || CheckQuestAttribute("generate_trade_quest_progress",  "failed"))
    			{
    				if (pchar.CargoQuest.TraderID == npchar.id )
    				{
    					link.l1 = RandPhraseSimple("Gemimin ambarında dükkanınıza getirdiğim bir parti mal var.","Gemilerim mağazanıza mal teslim etmek üzere kiralandı. Eşyalar şu anda indiriliyor.");
    					link.l1.go = "generate_quest_2";
    				}
    				else
    				{
                        if (!CheckQuestAttribute("generate_trade_quest_progress",  "failed") && pchar.CargoQuest.GiveTraderID == npchar.id && GetNationRelation2MainCharacter(sti(characters[GetCharacterIndex(pchar.CargoQuest.TraderID)].nation)) == RELATION_ENEMY)
                        {
                            link.l1 = "Ne yazık ki, taahhütlerimi yerine getiremeyeceğim. Siyasi durum, malları teslim etmeme izin vermiyor.";
            				link.l1.go = "generate_quest_cannot_done";
                        }
                        else
                        {
                            if (rand(1) == 1)
                            {
                                link.l1 = RandPhraseSimple("Yük taşımacılığı için gemimi kiralayabilirim.","Güzel bir gemim var ve istediğiniz her türlü yükü dilediğiniz yere teslim edebilirim.");
            				    link.l1.go = "generate_quest_not_closed";
        				    }
    				    }
    				}
    			}
    			else
    			{
    				link.l1 = "Bir gemi kiralamak ister misiniz, "+GetAddress_FormToNPC(NPChar)+"? Güvenilir bir gemim ve deneyimli bir mürettebatım var.";
    				link.l1.go = "generate_quest";
    			}
				link.l22 = "Başka bir işle meşgulüm.";
				link.l22.go = "quests";
    			// --> на кредитный генератор
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
    			{
	                link.l3 = pcharrepphrase(RandPhraseSimple("Ah, denizde gerçekten çok yoruldum... Şimdi, dostum, para benim için gerçekten büyük bir sorun.","Pekâlâ, kurnaz tilki, hadi mali işlerimizi konuşalım."),RandPhraseSimple("Sizinle mali konuları görüşmek istiyorum.","Mali konuları konuşalım, bunları ele almamız gerekiyor."));,
	
	                link.l3.go = "LoanForAll";
                }
				//квест мэра - на связь с нашим шпионом
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") 
				{
					link.l4 = RandPhraseSimple("Buraya bir adamın isteği üzerine geldim. Adı Vali "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" beni sana gönderdi. Bir şey almam gerekiyormuş...");
					link.l4.go = "IntelligenceForAll";
				}	
				
				//homo 25/06/06 слухи
                link.l6 = pcharrepphrase(RandPhraseSimple("Bana son dedikoduları anlatır mısın? Zaten bütün gün burada oyalanıyorsun.","Yaygara yapma, yaşlı sahtekâr - bana karada neler olup bittiğini anlat bakalım?"),RandPhraseSimple("Denizde bir ömür geçirmişim gibi hissediyorum. Sizin buralarda ne var ne yok?","Muhtemelen en son haberleri biliyorsunuzdur? Önemli neler oldu?"));,

    		    link.l6.go = "rumours_trader";

				// ugeen --> склад товаров для ГГ
				if(CheckAttribute(NPChar,"Storage") && Pchar.location.from_sea == "Pirates_town")
				{
					if(CheckAttribute(NPChar,"Storage.Activate"))
					{
						link.l7 = "Beni depoya götür. Ne durumda olduğunu görmek istiyorum.";
						link.l7.go = "storage_0";
						link.l8 = "Depoyu bırakmaya karar verdim. Şu anda ihtiyacım yok.";
						link.l8.go = "storage_04";
					}
					else
					{
						if(!CheckAttribute(NPChar,"Storage.NoActivate"))
						{
							link.l7 = "Affedersiniz, iyi adamım - acaba depo kiralıyor musunuz?";
							link.l7.go = "storage_01";
						}	
					}
				}				
				// <-- ugeen
				// Jason --> квест губера на поиск дезертира
				if(CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE)
				{
					link.l8 = "Bakın, yoldaşımı bulmaya çalışıyorum, "+pchar.GenQuest.FindFugitive.Name+" onun adı. Port Royal'da, meyhanedekiler bana onun sizin yerleşkenize doğru gittiğini söylediler. Onunla karşılaştınız mı, tesadüfen?";
					link.l8.go = "FindFugitiveSt";
				}
				//<-- поиск дезертира
				
				// <-- homo
				link.l99 = "Ama şimdi konuşacak zaman yok.";
    			link.l99.go = "no_quests";
			}
			else
			{
                link.l1 = NPCharRepPhrase(npchar,pcharrepphrase(""+RandSwear()+"Gemiyi adanın öbür tarafında bıraktım. Sonra geri döneceğim!","Affedersiniz, "+GetFullName(npchar)+", daha sonra geleceğim. Gemim henüz iskeleye yanaşmadı."),pcharrepphrase("Lanet olsun! Bu aptallar gemiyi yüklemeye hazırlamamışlar! Sonra geri geleceğim!","Affedersiniz, gemimi iskeleye yanaştırmak için emir vermem gerekiyor!"));
                link.l1.go = "exit";
				link.l22 = "Başka bir işle meşgulüm.";
				link.l22.go = "quests";
    			// --> на кредитный генератор
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
    			{
	                link.l3 = pcharrepphrase(RandPhraseSimple("Ah, denizde gerçekten çok yoruldum... Şimdi, dostum, para benim için gerçekten büyük bir sorun.","Pekâlâ, kurnaz tilki, hadi mali işlerimizi konuşalım."),RandPhraseSimple("Sizinle mali konuları konuşmak istiyorum.","Konuşmamız gereken mali meseleleri ele alalım."));,
	
	                link.l3.go = "LoanForAll";
                }
				//квест мэра - на связь с нашим шпионом
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") 
				{
					link.l7 = RandPhraseSimple("Buraya bir adamın isteği üzerine geldim. Adı Vali "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+" beni sana gönderdi. Bir şeyi teslim almam gerekiyormuş...");
					link.l7.go = "IntelligenceForAll";
				}
				// Jason --> квест губера на поиск дезертира
				if(CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE)
				{
					link.l8 = "Bakın, yol arkadaşımı bulmaya çalışıyorum, "+pchar.GenQuest.FindFugitive.Name+" onun adı. Port Royal'daki meyhanede bana onun sizin yerleşkenize doğru gittiğini söylediler. Onunla karşılaştınız mı, acaba?";
					link.l8.go = "FindFugitiveSt";
				}
				//<-- поиск дезертира
			}
		break;
		
		case "generate_quest":
			if (npchar.quest.trade_date != lastspeak_date || bBettaTestMode)
			{
				npchar.quest.trade_date = lastspeak_date;
				//проверка враждебности нам страны торговца
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "Hayır, hizmetine ihtiyacım yok! En azından, şu anda  ile düşman olduğun sürece."+NationNameAblative(sti(NPChar.nation))+".";
					link.l1 = "Öyleyse, hoşça kal.";
					link.l1.go = "exit";
				}
				else
				{
                    // проверка на проф пригодность -->
                    if (isBadReputation(pchar, 42))
                    {
                        dialog.text = RandSwear()+"Sen "+GetFullName(pchar)+", değil mi? Duyduğuma göre "+RandPhraseSimple("senin hakkında çok korkutucu şeyler","senin hakkında pek hoş olmayan şeyler")+", ve seninle uğraşmak istemiyorum.";
						link.l1 = RandPhraseSimple("Elbette - bir kere hata yaparsan, herkes seve seve üstüne tükürür.",RandSwear()+"Denizde yapılacak daha iyi şeyler var, "+GetFullName(npchar)+".");
						link.l1.go = "exit";
                        break;
                    }
                    // проверка на проф пригодность <--
                    int iTradeNation = GenerateNationTrade(sti(NPChar.nation));

					if (iTradeNation < 0)
					{
						dialog.text = NPCharRepPhrase(npchar,"Heh, "+GetAddress_Form(NPChar)+", bugün yük taşımacılığı için vaktim yok. Yarın tekrar gel.","Yarın tekrar gelin. Belki size avantajlı bir teklif sunarım.");
						link.l1 = "Pekala, yarın geri geleceğim.";
						link.l1.go = "exit";
					}
					else
					{
                        int storeMan = findStoreMan(NPChar, iTradeNation);
                        if (storeMan > 0)
                        {
                            //проверяем импорт/экспорт
							iTradeGoods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE)); //Jason
    						//проверяем свободное место (при этом должно вмещаться по меньшей мере 100 единиц выбранного груза
    						RecalculateSquadronCargoLoad(pchar); // fix неверное место
    						iQuantityGoods = GetSquadronFreeSpace(pchar, iTradeGoods);
							if (sti(Goods[iTradeGoods].Weight)/sti(Goods[iTradeGoods].Units)*sti(iQuantityGoods) > 1500) iQuantityGoods = makeint(1500/(sti(Goods[iTradeGoods].Weight)/sti(Goods[iTradeGoods].Units))); //Jason: больше 1500 массы не дадим - большие фрахты только через ПУ
    						if (iQuantityGoods < 100)// это в шт. товара
    						{
    							dialog.text = NPCharRepPhrase(npchar,"Senin zavallı eski teknen tüm partiyi taşıyamaz, bu yüzden bugün bir anlaşma yok.","Maalesef, kaptan "+GetFullName(pchar)+", teslimatım için daha büyük bir gemiye ihtiyacım olacak.");
    							link.l1 = NPCharRepPhrase(npchar,"Gemicim fena değil, ama dediğiniz doğru. Hoşça kalın.","Bakış açını anlıyorum, ticaret ticarettir. Hoşça kal.");
    							link.l1.go = "exit";
    						}
    						else
    						{
    							iQuantityGoods = iQuantityGoods - rand(makeint(iQuantityGoods/3)) - 10;
    							iMoney = makeint((iQuantityGoods * sti(Goods[iTradeGoods].Weight) / sti(Goods[iTradeGoods].Units)) * (4+rand(3) + GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE)) + 0.5);

    							pchar.CargoQuest.iTradeGoods = iTradeGoods;
    							pchar.CargoQuest.iQuantityGoods = iQuantityGoods;
    							pchar.CargoQuest.iMoney = iMoney;
    							pchar.CargoQuest.iTradeNation = iTradeNation;
    							pchar.CargoQuest.iDaysExpired = 25 + rand(5);
    							
    							pchar.CargoQuest.iTradeColony = Characters[storeMan].city;
    							pchar.CargoQuest.iTradeIsland = GetIslandByCityName(Characters[storeMan].city);
    							pchar.CargoQuest.TraderID     = Characters[storeMan].id;
    							pchar.CargoQuest.GiveTraderID = NPChar.id;
                                SaveCurrentQuestDateParam("CargoQuest");
    							string sNation = XI_ConvertString("Colony"+Characters[storeMan].city);
                                sTemp = "";
                                if (pchar.CargoQuest.iTradeIsland != Characters[storeMan].city)
								{
                                    sTemp = ", which is on " + XI_ConvertString(pchar.CargoQuest.iTradeIsland+"Voc");
                                }
                                dialog.text = "Ah! Tam da senden bir iyilik isteyecektim. Bak, bir yükü teslim etmem gerekiyor "+GetGoodsNameAlt(iTradeGoods)+" tutarında "+FindRussianQtyString(iQuantityGoods)+"  kasabasına "+sNation+sTemp+", ve ne kadar erken olursa o kadar iyi. Eğer bunu şu zamana kadar başarırsan "+FindRussianDaysString(makeint(pchar.CargoQuest.iDaysExpired))+", ardından varışta alacaksınız "+FindRussianMoneyString(iMoney)+" ödülünüz olarak. Ne dersiniz?";
    							link.l1 = "Bence katılıyorum.";
    							link.l1.go = "exit_trade";
    							link.l2 = "Bu muhtemelen bana göre değil.";
    							link.l2.go = "exit";
    						}
                        }
                        else
                        {
                            dialog.text = "Takımadadaki siyasi gerçekler ticaret yapmama izin vermiyor. "+XI_ConvertString(NationShortName(sti(NPChar.nation))+"hunter")+" herkese düşman ve dükkanda sadece beni bıraktı.";
    						link.l1 = "Ah! Üzgünüm. Bol şans.";
    						link.l1.go = "exit";
                        }
					}
				}
			}
			else
			{
				dialog.text = NPCharRepPhrase(npchar,"Defol, boş laf edecek vaktim yok!","Sana zaten verecek bir şeyim olmadığını söyledim.");
				link.l1 = NPCharRepPhrase(npchar,"Nezaketli olursan, sana biraz edep öğretirim!","Ah, özür dilerim!");
				link.l1.go = "exit";
			}
		break;

		case "exit_trade":
			AddDialogExitQuest("trade_quest_open");
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;

		case "generate_quest_2":
			if (pchar.quest.generate_trade_quest_progress == "failed")
			{
				dialog.text = RandSwear()+"Bu anlaşmayı biraz geç hatırladığını düşünmüyor musun? Malları tekrar sipariş etmek zorunda kaldım. Hoşça kal.";
				link.l1 = "Beni affedin, acelem vardı. Belki zararınızı karşılayabilirsem, itibarım geri kazanılır?";
				link.l1.go = "generate_quest_failed";
				link.l9 = "Her şey gönlünüzce olsun.";
				link.l9.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
			}
			else
			{
                iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
                iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
                
                dialog.text = "Gerçekten de! Bunu uzun zamandır bekliyordum. Bana bir yük teslim etmen gerekiyor: "+GetGoodsNameAlt(iTradeGoods)+" tutarında "+FindRussianQtyString(iQuantityGoods)+" ve bunun karşılığında al "+FindRussianMoneyString(sti(pchar.CargoQuest.iMoney))+".";
				link.l1 = "Kesinlikle.";
				link.l1.go = "generate_quest_ready";
			}
		break;
		
		case "generate_quest_ready":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            // блок кидалова нас на бабки -->
            if (rand(8) == 1 && sti(Goods[iTradeGoods].Cost) <= 44 && GetQuestPastDayParam("CargoQuest") > 5)
            {
                dialog.text = RandSwear()+"Sana karşı özür borçluyum, "+GetAddress_Form(NPChar)+".  Bakın, sorun şu ki ben "+RandPhraseSimple("utanç verici bir durumda kalırım ve sana ödeme yapamam"," o yükü başka bir satıcıdan daha iyi bir fiyata zaten aldım")+". Kiralama bedeli olarak, teslim ettiğiniz tüm yükü kendinize almanızı öneriyorum.";
				link.l1 = RandSwear()+RandPhraseSimple("Ve o lanet kargoyu her türlü tehlikeden korudum! Onun yüzünden iki yüz fare öldürdüm!","Beni köşeye sıkıştırdınız, bu yüzden kabul etmek zorundayım.");
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", 2);
				AddCharacterExpToSkill(pchar, "Sailing", 60);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCharacterExpToSkill(pchar, "COMMERCE", 15);

				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "4");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen")); // belamour gen
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
                break;
            }
            // блок кидалова нас на бабки <--
			if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
                iTmp = iQuantityGoods - GetSquadronGoods(pchar, iTradeGoods);
                dialog.text = "Bu hepsi değil! Anlaşmamıza göre, benim ihtiyacım olan "+FindRussianQtyString(iTmp)+" birim daha.";
				link.l9 = RandPhraseSimple("Evet, gerçekten öyle. O zaman eksikliği telafi etmem gerekecek. Sonra görüşürüz.",RandSwear()+"Bu lanet olası fareler yükü mahvetti. Eksikliği telafi edeceğim ve geri döneceğim.");
				link.l9.go = "exit";
                AddQuestRecord("DELIVERY_TRADE_QUEST", "8");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sHaveNotQty", iTmp);
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			}
			else
			{
                dialog.text = "Harika! İşte ödülünüz, kaptan "+GetFullName(pchar)+".";
				link.l1 = "Sizinle çalışmak bir zevkti.";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", 3);
				AddCharacterExpToSkill(pchar, "Sailing", 100);
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterExpToSkill(pchar, "COMMERCE", 100);

				AddMoneyToCharacter(pchar, makeint(pchar.CargoQuest.iMoney));
				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
				RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));
				
                OfficersReaction("good");
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "2");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
			}
		break;
		
		case "generate_quest_failed":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            iMoney =  3*makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
			dialog.text = "Pekala... Toplamı "+FindRussianMoneyString(iMoney)+" anlaşmamızın şartlarının ihlalinden kaynaklanan zararları karşılayacağım.";
			link.l1 = "Vay canına! Hayır, bu olmaz! Bir daha asla yük taşımayacağım! Denizde zaten bu saçmalıklardan fazlasıyla var!";
			link.l1.go = "exit";
            if (sti(pchar.Money) >= iMoney)
            {
    			link.l2 = "İşte istenen miktar";
    			link.l2.go = "generate_quest_failed_2";
			}
            else
            {
                AddQuestRecord("DELIVERY_TRADE_QUEST", "7");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
    		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            }
		break;
		
		case "generate_quest_failed_2":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            iMoney =  3*makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
			dialog.text = "Mükemmel. Artık meslektaşlarıma seninle hâlâ makul şartlarda iş yapılabileceğini söyleyebilirim.";
			link.l1 = "Teşekkür ederim! Sana bir daha asla hayal kırıklığı yaşatmayacağım.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			AddCharacterExpToSkill(pchar, "Sailing", -100);
			AddCharacterExpToSkill(pchar, "Leadership", -50);
			AddCharacterExpToSkill(pchar, "COMMERCE", -100);

			AddMoneyToCharacter(pchar, -iMoney);
			pchar.quest.generate_trade_quest_progress = "";
			pchar.quest.generate_trade_quest.over = "yes";

            AddQuestRecord("DELIVERY_TRADE_QUEST", "5");
            AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
            AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            CloseQuestHeader("DELIVERY_TRADE_QUEST");
		break;
		
		case "generate_quest_not_closed":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);

            dialog.text = "Hmm. Önceki sözleşmedeki yükümlülüklerini yerine getirmediğini duydum - şimdi ise bir yenisini mi istiyorsun? Teslim etmen gereken yük şuydu: "+GetGoodsNameSeaSection(&Goods[iTradeGoods])+" to "+XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony)+".";
			link.l1 = "Evet, kesinlikle! Haklısınız!";
			link.l1.go = "exit";
		break;
		
		case "generate_quest_cannot_done":
            dialog.text = RandSwear()+GetAddress_Form(NPChar)+", beni hayal kırıklığına uğratıyorsun!!! Belki bu sorunu çözmek için bir şeyler yapabilirsin?";
			link.l1 = "Pekala. Sevkiyatı teslim etmek için elimden geleni yapacağım.";
			link.l1.go = "exit";
			link.l2 = "Hayır, yapamam. Üzgünüm";
			link.l2.go = "generate_quest_cannot_done_2";
			
		break;
		
		case "generate_quest_cannot_done_2":
		    iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
				dialog.text = "Dur bir dakika! Geminde yeterli mal yok! Sahip olduğun şeyler yetmiyor "+FindRussianQtyString(iQuantityGoods - GetSquadronGoods(pchar,iTradeGoods))+" yük birimi.";
				link.l9 = RandPhraseSimple("Evet, gerçekten de. O zaman eksikliği telafi etmem gerekecek.",RandSwear()+"Fareler yükü mahvetmiş. Eksik miktarı satın alıp döneceğim.");
				link.l9.go = "exit";
			}
			else
			{
                dialog.text = "Anladım, anladım... Yükü geri alacağım.";
    			link.l1 = "Teşekkür ederim! Sana bir daha asla hayal kırıklığı yaşatmayacağım!";
    			link.l1.go = "exit";
    			ChangeCharacterComplexReputation(pchar,"nobility", -3);

				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
				RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "6");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodQty", FindRussianQtyString(sti(pchar.CargoQuest.iQuantityGoods)));
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
    		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen")); // belamour gen
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
            }
		break;
	
//Jason --> мини-квест Дефицитный товар
		case "Wine_Trader":
			dialog.text = "Neden bahsediyorsunuz? Belli ki yanlış bilgilendirilmişsiniz – ben asla bu kadar büyük miktarda Avrupa şarabı satmadım. Bir iki şişe olur, fazlası değil. Ama yerel şarap başka mesele – ondan bolca var, ve şişeyle değil, damacana ile satılır!";
			link.l1 = "Kahretsin! Ama bana söylenmişti...";
			link.l1.go = "Wine_Trader_1";
		break;
		
		case "Wine_Trader_1":
			dialog.text = "Ne söylendiğini bilmiyorum, ama tekrar ediyorum: elimde Avrupa şarabı yok. Bu konuda söyleyeceklerim bu kadar.";
			link.l1 = "Pekala... O zaman gidip halledeceğim, tamam mı!";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "5");
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.Name);
			DeleteAttribute(pchar, "questTemp.Wine.Trader");
			pchar.questTemp.Wine.Repeat1 = "true";
		break;
		
		case "Wine_Repeat2":
			RemoveItems(PChar, "letter_1", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Bu başka bir mesele. Burası her çeşit insanın gelip gereksiz sorular sorduğu bir yer. Şimdi, pazarlık yapacak mıyız?";
			link.l1 = "Tabii!";
			link.l1.go = "Wine_Price";
			pchar.questTemp.Wine.wait = "true";
			DeleteAttribute(pchar, "questTemp.Wine.Repeat2");
			SetFunctionTimerCondition("Wine_wait", 0, 0, 7, false);
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId(pchar.questTemp.Wine.ItemTraderID), "questmarkmain");
		break;
		
		case "Wine_Price":
			dialog.text = "Kaç şişe istiyorsunuz? Bir şişenin fiyatı 500 peso, en az sipariş ise 20 şişe.";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "Wine_Qty";
			link.l2 = "Şu anda yeterli param yok. Daha sonra geri geleceğim.";
			link.l2.go = "Wine_Qty_exit";
		break;
		
		case "Wine_Qty":
			int iQty = sti(dialogEditStrings[4]);
			pchar.questTemp.Wine.Qty = sti(iQty);
			if (iQty < 20)
			{
				dialog.text = "Ben seyyar satıcı değilim, kaptan. Bildiğim kadarıyla, daha büyük bir parti konuşuyordunuz?";
				link.l1 = "Üzgünüm... O zaman miktarı tekrar gözden geçirelim.";
				link.l1.go = "Wine_Price";
				break;
			}
			if (iQty > 70)
			{
				dialog.text = "Maalesef, o kadarım yok.";
				link.l1 = "Yazık... O zaman, miktarı tekrar gözden geçirelim.";
				link.l1.go = "Wine_Price";
				break;
			}
			pchar.questTemp.Wine.Summ = sti(iQty)*500;
			dialog.text = ""+sti(iQty)+" Şişeler mi? Peki. Bunun sana maliyeti şu olacak "+FindRussianMoneyString(sti(pchar.questTemp.Wine.Summ))".";
			if (makeint(Pchar.money) >= sti(pchar.questTemp.Wine.Summ))
			{
				link.l1 = "Buyurun.";
				link.l1.go = "Wine_Qty_1";
			}
			link.l2 = "Şu anda yeterli param yok. Daha sonra geri geleceğim.";
			link.l2.go = "Wine_Qty_exit";
		break;
		
		case "Wine_Qty_exit":
			dialog.text = "Tamam, ama çok oyalanmamaya çalış. Bu mallar burada oldukça rağbet görüyor.";
			link.l1 = "Yakında döneceğim!";
			link.l1.go = "exit";
		break;
		
		case "Wine_Qty_1":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Wine.Summ));
			dialog.text = "Bakalım... Her şey yolunda görünüyor. Satın aldıklarınızı teslim alabilirsiniz.";
			link.l1 = "Teşekkürler! Bol şanslar!";
			link.l1.go = "Wine_Qty_2";
		break;
		
		case "Wine_Qty_2":
			pchar.quest.Wine_wait.over = "yes";//снять прерывание
			DeleteAttribute(pchar, "questTemp.Wine.wait");
			TakeNItems(pchar, "potionwine", sti(pchar.questTemp.Wine.Qty));
			PlaySound("interface\important_item.wav");
			Log_Info ("You have received wine");
			AddQuestRecord("Wine", "8");
			DelLandQuestMark(npchar);
			DialogExit();
		break;
		// <-- мини-квест Дефицитный товар
		
// Jason --> -------------------------генератор Сомнительное предложение----------------------------------------
		int iCGood, amount;
		case "Contraoffer":
			pchar.GenQuest.Contraoffer.Trader.Goods = SelectContrabandGoods(pchar);
			while (sti(pchar.GenQuest.Contraoffer.Trader.Goods) == -1)
			{
				pchar.GenQuest.Contraoffer.Trader.Goods = SelectContrabandGoods(pchar);
			}
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			pchar.GenQuest.Contraoffer.Trader.Qty = makeint(15*(sti(pchar.rank)+30)/(sti(Goods[iCGood].Weight)/sti(Goods[iCGood].Units))*(8-sti(RealShips[sti(pchar.ship.type)].Class)));//количество
			pchar.GenQuest.Contraoffer.Trader.Price = sti(Goods[iCGood].Cost)/sti(Goods[iCGood].Units)*3;//цена единицы товара
			pchar.GenQuest.Contraoffer.Trader.Summ = sti(pchar.GenQuest.Contraoffer.Trader.Price)*sti(pchar.GenQuest.Contraoffer.Trader.Qty);//сумма
			pchar.GenQuest.Contraoffer.Trader.Days = 30+hrand(20);//срок
			pchar.GenQuest.Contraoffer.Trader.Chance = rand(5);//17% вероятности, что патруль накроет
			dialog.text = "İyi bir pazarlık yapmayı planlamıştım, ama bunun için hâlâ özel bir eşyaya ihtiyacım var - "+GetGoodsNameAlt(iCGood)+". Sorun şu ki, bu malzemeler kolonimizde kaçak sayılıyor, bu yüzden ticaret kaptanlarından satın alamam\nTek ihtiyacım olan "+FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Trader.Qty))+" adet bundan lazım. Belki bana getirebilir misiniz? Size iyi bir ödeme yaparım, "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Price))+" birim başına, bu da toplamda "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ))+". Ah, ve bunu en geç şu zamana kadar almam gerek "+FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Trader.Days))+". Peki, bana yardım edecek misin?";
			link.l1 = "Hmm... İlginç geliyor. Kabul ediyorum!";
			link.l1.go = "Contraoffer_1";
			link.l2 = "Kaçak mal mı getiriyorsunuz? Üzgünüm, ilgilenmiyorum.";
			link.l2.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
		break;
		
		case "Contraoffer_1":
			dialog.text = "Harika. Kabul ettiğine sevindim. O halde, mallarla geri dönmeni bekleyeceğim.";
			link.l1 = "Yakında döneceğim!";
			link.l1.go = "exit";
			rColony = GetColonyByIndex(FindColony(npchar.city));
			SetNull2StoreGood(rColony, sti(pchar.GenQuest.Contraoffer.Trader.Goods));//нулим товар
			pchar.GenQuest.Contraoffer = "begin";
			pchar.GenQuest.Contraoffer.Trader = "true";
			pchar.GenQuest.Contraoffer.Trader.City = npchar.city;
			pchar.GenQuest.Contraoffer.Trader.Nation = npchar.nation;
			iCGood = pchar.GenQuest.Contraoffer.Trader.Goods;
			ReOpenQuestHeader("Contraoffer");
			AddQuestRecord("Contraoffer", "1");
			AddQuestUserData("Contraoffer", "sGoods", GetGoodsNameAlt(iCGood));
			AddQuestUserData("Contraoffer", "sGoodQty", FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Trader.Qty)));
			AddQuestUserData("Contraoffer", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ)));
			AddQuestUserData("Contraoffer", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Contraoffer.Trader.City+"Gen"));
			AddQuestUserData("Contraoffer", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Trader.Days)));
			SetFunctionTimerCondition("Contraoffer_Over", 0, 0, sti(pchar.GenQuest.Contraoffer.Trader.Days), false);
		break;
		
		case "Contraoffer_check":
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			amount = sti(pchar.GenQuest.Contraoffer.Trader.Qty) - GetSquadronGoods(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Goods));
			if (amount > 0)
			{
				dialog.text = "Şaka mı yapıyorsunuz? İhtiyacım olan tüm mallar tam olarak sizde yok!";
				link.l1 = "Üzgünüm, benim hatam...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Bakalım, o zaman. Bir yük teslim etmen gerekiyordu "+GetGoodsNameAlt(iCGood)+" tutarında "+FindRussianQtyString(pchar.GenQuest.Contraoffer.Trader.Qty)+". Doğru mu?";
				link.l1 = "Aynen öyle, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "Contraoffer_pay";
			}
		break;
		
		case "Contraoffer_pay":
			dialog.text = "Yaptığınız iş için teşekkür ederim. Lütfen, ödemenizi alın - "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ))+".";
		link.l1 = "Teşekkürler! Sizinle iş yapmak bir zevkti.";
		link.l1.go = "Contraoffer_complete";
		break;
		
		case "Contraoffer_complete":
			pchar.quest.Contraoffer_Over.over = "yes";
			RemoveCharacterGoods(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Goods), sti(pchar.GenQuest.Contraoffer.Trader.Qty));
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Summ));
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
			npchar.quest.Contraoffer.chance = rand(2);//личный шанс торговца для 'пасхалки'
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			if (pchar.GenQuest.Contraoffer.Trader.Chance == 3)
			{
				dialog.text = "Ah... Kaptan, galiba burada bir sorunumuz var...";
				link.l1 = "Yine ne oldu?";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("Contraoffer_Patrol");
				pchar.GenQuest.Contraoffer.Trader.busy = "true";
				pchar.quest.Contraoffer_busy.win_condition.l1 = "ExitFromLocation";
				pchar.quest.Contraoffer_busy.win_condition.l1.location = pchar.location;
				pchar.quest.Contraoffer_busy.function = "Trader_free";
			}
			else
			{
				DialogExit();
				AddQuestRecord("Contraoffer", "3");
				CloseQuestHeader("Contraoffer");
				DeleteAttribute(pchar, "GenQuest.Contraoffer.Trader");
			}
		break;
		
		case "Contraoffer_slaves"://единичный вариант за всю игру, ака 'пасхалка'
			pchar.GenQuest.Contraoffer.Slaves.Name = GetFullName(npchar);
			pchar.GenQuest.Contraoffer.Slaves.Price = 300;//цена на рабов, пока фиксированная, можно подставить формулу
			pchar.GenQuest.Contraoffer.Slaves.Qty = 300+rand(50);//количество
			pchar.GenQuest.Contraoffer.Slaves.Days = 14+rand(6);//срок
			pchar.GenQuest.Contraoffer.Slaves.Money = sti(pchar.GenQuest.Contraoffer.Slaves.Qty)*sti(pchar.GenQuest.Contraoffer.Slaves.Price);
			dialog.text = "Acilen bir grup köleye ihtiyacım var - "+sti(pchar.GenQuest.Contraoffer.Slaves.Qty)+" başlar. Ödemeye hazırım "+sti(pchar.GenQuest.Contraoffer.Slaves.Price)+" ruh başına   sikke, toplamda  "+sti(pchar.GenQuest.Contraoffer.Slaves.Money)+" pesos in total; term - "+FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Slaves.Days))+".";
			link.l1 = "Bence kabul edeceğim. Zahmetli ama oldukça kârlı bir iş.";
			link.l1.go = "Contraoffer_slaves_1";
			link.l2 = "İlgilenmiyorum.";
			link.l2.go = "exit";
			pchar.GenQuest.Contraoffer.Slaves = "begin";
		break;
		
		case "Contraoffer_slaves_1":
			dialog.text = "Aynen öyle - gerçekten çok kârlı. O halde, kölelerimle birlikte dönüşünü bekliyor olacağım.";
			link.l1 = "Seni fazla bekletmeyeceğim. Görüşürüz!";
			link.l1.go = "exit";
			pchar.GenQuest.Contraoffer.Slaves.Yes = "begin";
			pchar.GenQuest.Contraoffer.Slaves.City = npchar.city;
			ReOpenQuestHeader("Contraoffer");
			AddQuestRecord("Contraoffer", "4");
			AddQuestUserData("Contraoffer", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Slaves.Days)));
			AddQuestUserData("Contraoffer", "sGoodQty", FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Slaves.Qty)));
			AddQuestUserData("Contraoffer", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Slaves.Money)));
			AddQuestUserData("Contraoffer", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Contraoffer.Slaves.City+"Gen"));
			SetFunctionTimerCondition("Contraoffer_Over", 0, 0, sti(pchar.GenQuest.Contraoffer.Slaves.Days), false);
		break;
		
		case "Contraoffer_slaves_check":
			amount = sti(pchar.GenQuest.Contraoffer.Slaves.Qty) - GetSquadronGoods(pchar, GOOD_SLAVES);
			if (amount > 0)
			{
				dialog.text = "Şaka mı yapıyorsun? İhtiyacım olan tüm köleler sende yok!";
				link.l1 = "Üzgünüm, benim hatam...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Bakalım, o zaman. Bana şu kadar köle teslim edecektiniz: "+FindRussianQtyString(pchar.GenQuest.Contraoffer.Slaves.Qty)+". Doğru mu?";
				link.l1 = "Aynen öyle, "+GetAddress_FormToNPC(NPChar)+".";
				link.l1.go = "Contraoffer_slaves_pay";
			}
		break;
		
		case "Contraoffer_slaves_pay":
			dialog.text = "Yaptığınız iş için teşekkür ederim. Lütfen ödemenizi alın - "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Slaves.Money))+". Ayrıca, lütfen bunu da kabul edin. Eminim işinize yarayacaktır.";
			link.l1 = "Teşekkürler! Sizinle iş yapmak bir zevkti.";
			link.l1.go = "Contraoffer_slaves_complete";
		break;
		
		case "Contraoffer_slaves_complete":
			DialogExit();
			pchar.quest.Contraoffer_Over.over = "yes";
			RemoveCharacterGoods(pchar, GOOD_SLAVES, sti(pchar.GenQuest.Contraoffer.Slaves.Qty));
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Contraoffer.Slaves.Money));
			AddQuestRecord("Contraoffer", "5");
			CloseQuestHeader("Contraoffer");
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
			AddCharacterExpToSkill(pchar, "Sailing", 150);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 200);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 150);//везение
			TakeNItems(pchar, "cirass3", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			DeleteAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes");
		break;
		// <-- генератор Сомнительное предложение
		
		//Jason --> генератор Неудачливый вор
		case "Device_Trader":
			dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Daha önce hiç duymadım... Aslında bu nedir? Bunca zaman böyle bir şey hiç duymadım.";
			link.l1 = "Eh, bu bir gemi yapımcısının aleti, "+pchar.GenQuest.Device.Shipyarder.Describe+". Sana böyle bir şey teklif eden oldu mu?";
			link.l1.go = "Device_Trader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Trader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) == 0)
			{
				dialog.text = "Hmm... Evet, tuhaf bir adam vardı. Ama bana o şeyin ne olduğunu söylemedi, sadece satmaya çalıştı. Ama ne işe yaradığını bilmeden ben ne yapayım ki onu? Nasıl tekrar satacağım? Bu yüzden reddettim.";
				link.l1 = "Nasıl biriydi ve nereye gitti? O alete gerçekten ihtiyacım var.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Hayır, öyle bir şey yok. Üzgünüm, sana yardımcı olamam. Etrafta sor.";
				link.l1 = "Anladım. O halde, biraz soruşturmanın zamanı geldi!";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор

		//Jason --> генератор Место под солнцем
		case "Sunplace_begin":
			dialog.text = "Rekabet... Onsuz ticaret olmaz. Sıcak işine sızmaya çalışan açgözlü herifler, müşterileri kendilerine çekmek için her türlü alçak yöntemi denerler.\nAma bunlar sadece lafta kalıyor. Aslında senden bir rakibimden kurtulmam için yardımını isteyeceğim. Hayır, öldürmene gerek yok. Sadece gemisini ve yükünü ele geçir ya da batır.";
			link.l1 = "Hmm... peki, eğer iyi ödeyecekseniz, bunu ayarlayabilirim.";
			link.l1.go = "Sunplace_1";
			link.l2 = "Hayır, ticari kavgalarınıza karışmıyorum. Rakibinizi benim yardımım olmadan batırın.";
			link.l2.go = "Sunplace_exit";
		break;
		
		case "Sunplace_exit"://если отказал - этот непись больше никогда не даст
			npchar.quest.Sunplace = "true";
			DialogExit();
		break;
		
		case "Sunplace_1":
			GetSunplaceShore();//бухта и остров
			pchar.GenQuest.Sunplace.Trader.Enemyname = GenerateRandomName_Generator(sti(npchar.nation), "man");//имя конкурента
			pchar.GenQuest.Sunplace.Trader.Nation = npchar.nation;//нация общая для торговца и конкурента
			pchar.GenQuest.Sunplace.Trader.City = npchar.City;//город квестодателя
			pchar.GenQuest.Sunplace.Trader.CityT = findSunplaceCity(NPChar);//город конкурента
			pchar.GenQuest.Sunplace.Trader.Shiptype = Sunplace_Shiptype();//тип корабля
			pchar.GenQuest.Sunplace.Trader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));//имя корабля
			pchar.GenQuest.Sunplace.Trader.DaysQty = 5 + hrand(5);//дни
			pchar.GenQuest.Sunplace.Trader.Money = sti(pchar.GenQuest.Sunplace.Trader.Shiptype)*3000;//оплата
			pchar.GenQuest.Sunplace.Trader.Goods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE));//товар
			dialog.text = "Pekala. Yani, adamınızın adı "+pchar.GenQuest.Sunplace.Trader.Enemyname+".   Son zamanlarda dışarıya göndermişti "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType),"Name")+"Acc"))+" '"+pchar.GenQuest.Sunplace.Trader.ShipName+"'  bir yükle birlikte "+GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods))+". Bu yük için oldukça iyi bir meblağ ödedi, bu yüzden onu kaybetmek cüzdanına epey bir darbe olacak.";
			link.l1 = "Ve bana o 'arkadaşını' tam olarak nerede aramam gerektiğini söyleyebilir misin?";
			link.l1.go = "Sunplace_2";
		break;
		
		case "Sunplace_2":
			dialog.text = " 'Arkadaşım' şu anda evinde "+XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Voc")+". Ona ihtiyacın yok - ihtiyacın olan onun gemisi, ki ben de yaklaşık olarak öğrendim ki "+FindRussianDaysString(sti(pchar.GenQuest.Sunplace.Trader.DaysQty))+" yakınından geçeceğim "+XI_ConvertString(pchar.GenQuest.Sunplace.Trader.Shore+"Gen")+". Batırabilirsin ya da gemiye çıkarak ele geçirebilirsin - fark etmez. En önemlisi, geminin ve yükün artık   mülkiyetinde olmamasını sağlamak."+pchar.GenQuest.Sunplace.Trader.Enemyname+". Ve kimin hak iddia ettiğini umursamıyorum - ister sen, ister deniz. Bu iş için sana ödeyeceğim "+FindRussianMoneyString(sti(pchar.GenQuest.Sunplace.Trader.Money))+".";
			link.l1 = "Anladım. O halde, yola koyulma vakti!";
			link.l1.go = "Sunplace_3";
		break;
		
		case "Sunplace_3":
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "true";
			if (sti(pchar.GenQuest.Sunplace.Chance) == 1 && sti(pchar.rank) > 9) pchar.GenQuest.Sunplace.Bonus = "true";
			ReOpenQuestHeader("Sunplace");
			AddQuestRecord("Sunplace", "1");
			AddQuestUserData("Sunplace", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods)));
			AddQuestUserData("Sunplace", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)));
			AddQuestUserData("Sunplace", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Sunplace.Trader.Money)));
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.City+"Gen"));
			AddQuestUserData("Sunplace", "sType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType), "Name") + "Acc")));
			AddQuestUserData("Sunplace", "sSName", pchar.GenQuest.Sunplace.Trader.ShipName);
			AddQuestUserData("Sunplace", "sName", GetFullName(npchar));
			AddQuestUserData("Sunplace", "sShore", XI_ConvertString(pchar.GenQuest.Sunplace.Trader.Shore+"Gen"));
			SetFunctionTimerCondition("Sunplace_Over", 0, 0, sti(pchar.GenQuest.Sunplace.Trader.DaysQty), false);
			pchar.quest.Sunplace_Trader.win_condition.l1 = "location";
			pchar.quest.Sunplace_Trader.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.Island;
			pchar.quest.Sunplace_Trader.win_condition.l2 = "Timer";
			pchar.quest.Sunplace_Trader.win_condition.l2.date.hour  = sti(GetTime());
			pchar.quest.Sunplace_Trader.win_condition.l2.date.day   = GetAddingDataDay(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.win_condition.l2.date.month = GetAddingDataMonth(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.win_condition.l2.date.year  = GetAddingDataYear(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.function = "Sunplace_CreateTraderShip";
		break;
		
		case "Sunplace_complete":
			dialog.text = "Harika! Sana güvenebileceğimi biliyordum. Sanırım o geminin ve yükünün nerede olduğuna dair soru sormayacağım. Sonuçta bu beni ilgilendirmez. Ayrıca arkadaşım böyle bir darbeden sonra kendine gelmek için epey zamana ihtiyaç duyacak, heh-heh. Al, lütfen paranı al – ve işi güzelce hallettiğin için teşekkür ederim.";
			link.l1 = "Rica ederim... Görüşürüz, "+npchar.name+"!";
			link.l1.go = "Sunplace_complete_1";
		break;
		
		case "Sunplace_complete_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Sunplace.Trader.Money));
			AddQuestRecord("Sunplace", "12");
			CloseQuestHeader("Sunplace");
			pchar.GenQuest.Sunplace.Chance = rand(2);
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 0, 0);
			AddComplexSelfExpToScill(20, 20, 20, 20);
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			DialogExit();
		break;
		
		case "Sunplace_complete_murder":
			dialog.text = "Zavallı "+pchar.GenQuest.Sunplace.Trader.Enemyname+", ne korkunç bir son! Ve doğrudan olmasa da, onun ölümüne ben sebep oldum! Anlamıyorsunuz, kaptan! Onu öldürmeni istedim mi? Planım, yük için harcanan parayı kaybettikten sonra onun tekrar... neyse... Sen...";
			link.l1 = "Hey, dinle - sızlanmayı bırak, tamam mı? Rakibini ortadan kaldırmamı istedin - ben de yaptım. Üstelik daha iyisini yaptım - sadece yükünü kaybetseydi, yine zengin olup işine zarar vermeye devam edebilirdi. Ama şimdi, ölü biri olarak elinden pek bir şey gelmez.";
			link.l1.go = "Sunplace_complete_murder_1";
		break;
		
		case "Sunplace_complete_murder_1":
			dialog.text = "Bu kadar! Yeter! Bu küfür dolu lafları artık duymak istemiyorum! Al şu lanet paranı ve hemen dükkanımdan çık!";
			link.l1 = "Selam, "+npchar.name+"Sakin ol biraz, olur mu? Yoksa seni ben sakinleştiririm – her zaman yanımda bir kılıcım var! Peki, korkma, sadece şaka yapıyordum. Bak, işlerin böyle gitmesine üzüldüm – ama en başta beni yanlış yönlendiren sendin. Hoşça kal.";
			link.l1.go = "Sunplace_complete_murder_2";
		break;
		
		case "Sunplace_complete_murder_2":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Sunplace.Trader.Money));
			AddQuestRecord("Sunplace", "13");
			AddQuestUserData("Sunplace", "sName", GetFullName(npchar));
			CloseQuestHeader("Sunplace");
			npchar.quest.Sunplace = "true";//этот непись повторно квест больше не даст
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 0, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			DialogExit();
		break;
		
		//Jason --> поиск дезертира
		case "FindFugitiveSt":
			if (NPChar.city == pchar.GenQuest.FindFugitive.City && sti(pchar.GenQuest.FindFugitive.Chance) == 1)
			{
				dialog.text = NPCStringReactionRepeat(""+pchar.GenQuest.FindFugitive.Name+"Evet, onu tanıyorum. Uzun sandalına erzak aldı benden. Gündüzleri genellikle tenha koylarda balık tutar, ama her akşam onu meyhanede bulabilirsin.","Bu adamı bana zaten sordunuz, ve bildiğim her şeyi anlattım!","Benimle dalga mı geçiyorsun, yoksa gerçekten aptal mısın?! Aynı soruları üçüncü kez soruyorsun zaten!","Şuna bak, böyle bir aptal nasıl kaptan olabilmiş...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Teşekkür ederim, bana çok büyük bir iyilik yaptınız!","Evet, evet, tamam.","Tamam, tamam, bu kadar heyecanlanma. Sadece unuttum.","Eh, gördüğün gibi yaptı...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("FindFugitiveSt_1", "exit", "", "", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("Port Royal'daki meyhanede ne konuşulduğunu bilmiyorum, ama o adamı dükkânımda hiç görmedim. Aslında, onu hiçbir yerde görmedim. Köyde birilerine sor, belki sana bir şey anlatırlar...","Bu adamı zaten bana sordunuz, ve size söyledim: Bilmiyorum!","Benimle dalga mı geçiyorsun yoksa gerçekten aptal mısın?! Aynı soruları üçüncü kez soruyorsun zaten!","Şuna bak, böyle bir aptal nasıl kaptan olmuş...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Anladım. Yine de teşekkür ederim.","Evet, evet, tamam.","Şimdi, şimdi, bu kadar heyecanlanma. Sadece unuttum.","Pekâlâ, gördüğün gibi yaptı...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
			}
		break;
		
		case "FindFugitiveSt_1":
			DialogExit();
			AddQuestRecord("MayorsQuestsList", "12-2");
			sld = characterFromId("Fugitive");
			LAi_SetSitType(sld);
			sld.dialog.currentnode = "Fugitive_tavern";
			LAi_SetLoginTime(sld, 20.0, 23.99);
			FreeSitLocator(pchar.GenQuest.FindFugitive.City + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.City+"_tavern", "sit", "sit_front1");
		break;
		//<-- поиск дезертира
		
		// --> Карибские нравы - временное завершение
		// belamour legendary edition -->
		case "trial":
			dialog.text = "Efendim, ne oluyor size, genç adam! Lütfen, daha ölçülü olun ve saygıdeğer insanlar hakkında konuşurken kelimelerinizi dikkatli seçin! Gerard LeCroix, Guadeloupe'dan ana karaya bir keşif gezisine çıktı, ama ödülünüzü burada sizin için bıraktı. Şimdi memnun musunuz?";
			link.l1 = "Hm... Lütfen beni mazur görün, monsieur. Biraz kendimi kaptırdım...";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "Çok iyi. Bay Lecroix ödülünüzü buradaki deniz feneri bekçisine bıraktı – onlar eski dostlar. Sadece gidip ödemenizi almanız yeterli. Bay Lecroix dürüst bir adamdır, bu yüzden ödülünüzden memnun kalacağınızı düşünüyorum.";
			link.l1 = "Anladım, teşekkürler! O zaman deniz feneri bekçisine gideceğim. Şimdi biraz dinleneyim.";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			//TakeNItems(pchar, "gold_dublon", 400);
			link.l1 = "...";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			DialogExit();
			AddQuestRecord("Trial", "22");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "FencingL", 20);
			AddCharacterExpToSkill(pchar, "FencingS", 20);
			AddCharacterExpToSkill(pchar, "FencingH", 20);
			AddCharacterExpToSkill(pchar, "Pistol", 20);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar, "questTemp.Trial");
			DeleteAttribute(npchar, "quest.trial_usurer");
			sld = characterFromId("BasTer_Lightman");
			sld.quest.trial_usurer = true;
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "trialA":
			dialog.text = "Evet, buradaydı, sizi bekliyordu. Ama belki de size verdiği görev beklediğinden daha zordu, bu yüzden beklemedi ve anakaraya bir sefere çıktı. Ödülünüzü ise güvendiği birine bıraktı.";
			link.l1 = "Evet, gerçekten beklenmedik durumlar yaşadım, ama görevi başarıyla tamamladım. Ödülümün beni beklediğini duymak güzel. Onu kimden teslim alacağım?";
			link.l1.go = "trialA_1";
		break;
		
		case "trialA_1":
			dialog.text = "Bay Lecroix ödülünüzü yerel deniz feneri bekçisine bıraktı – onlar eski dostlardır. Sadece gidip ödemenizi almanız yeterli. Monsieur Lecroix dürüst bir adamdır, bu yüzden ödülünüzden memnun kalacağınızı düşünüyorum.";
			link.l1 = "Anladım, teşekkürler! O zaman deniz feneri bekçisine gideceğim. Şimdi biraz dinleneyim.";
			link.l1.go = "trialA_2";
		break;
		
		case "trialA_2":
			dialog.text = "İyi şanslar, monsieur.";
			link.l1 = "...";
			link.l1.go = "trialA_3";
		break;
		
		case "trialA_3":
			DialogExit();
			AddQuestRecord("Trial", "22");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Commerce", 80);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar, "questTemp.Trial");
			DeleteAttribute(npchar, "quest.trial_usurer");
			sld = characterFromId("BasTer_Lightman");
			sld.quest.trial_usurer = true;
			AddLandQuestMark(sld, "questmarkmain");
		break;
		// <-- legendary edition
		/*case "trial":
			dialog.text = "Tanrım, neden bu kadar yüksek sesle konuşuyorsun, genç adam! Sakin ol ve saygıdeğer insanlardan bahsederken diline dikkat et! Gerard LeCroix, Guadeloupe'dan ana karaya bir keşif gezisiyle ayrıldı, ama sana bir mesaj bıraktı\nSakinleştin mi, efendim? Beni dinlemeye hazır mısın?";
			link.l1 = "Hm... Lütfen kusuruma bakmayın, monsieur. Biraz fazla heyecanlandım. Dinliyorum.";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "Çok iyi. Bir dahaki sefere önce sor, sonra bağır. Peki... Simon Maurois adında birini tanıyor musun?";
			link.l1 = "Ha! Simon Maurois'u duymayan kalmamıştır! Elbette onu tanıyorum.";
			link.l1.go = "trial_2";
			link.l2 = "Hiç duymadım. Kim o?";
			link.l2.go = "trial_3";
		break;
		
		case "trial_2":
			dialog.text = "Harika. O halde ona git. Monsieur Shoke'un seferini finanse eden oydu, ödülünü de ondan alabilirsin. Peki, gerçekten bu kadar sinirlenmek gerekli miydi?";
			link.l1 = "Bir kez daha affınızı rica ediyorum... Yardımınız için teşekkür ederim, efendim. Hemen monsieur Maurois'nin yanına gideceğim!";
			link.l1.go = "trial_exit";
		break;
		
		case "trial_3":
			dialog.text = "O, Maurois bankasının sahibi ve Capsterville şubesinin başıdır. Yani Saint-Christopher'a gidip Capsterville bankasını ziyaret etmeniz gerekecek. Monsieur Maurois, Monsieur Shoke'un seferini finanse eden kişiydi, bu yüzden ödülünüzü ondan alabilirsiniz. Peki, gerçekten bu kadar telaşlanmaya gerek var mıydı?";
			link.l1 = "Bir kez daha affınızı rica ediyorum... Yardımınız için teşekkür ederim, efendim. Hemen Bay Maurois'nin yanına gideceğim!";
			link.l1.go = "trial_exit";
		break;
		
		case "trial_exit":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(npchar, "quest.trial_usurer");
			pchar.questTemp.Trial = "usurer";
			AddQuestRecord("Trial", "22");
		break;*/
		
		// belamour legendary edition на пару с Акулой -->
		case "SharkGoldFleet":
			dialog.text = "Ah, girişimci tüccar! İş zekânı hemen fark ettim. Buna saygı duyarım. Tabii ki, ihtiyacın olan mallar bende var.";
			link.l1 = "Bundan kâr edebileceğimden eminim. Bildiğim kadarıyla Porto Bello'da bu mala iyi bir talep var. Bana kaça mal olacak?";
			link.l1.go = "SharkGoldFleet_01";
		break;
		
		case "SharkGoldFleet_01":
			pchar.questTemp.SharkGoldFleet = "buyincar";
			dialog.text = "Eh işte... Yani, üç yüz birim kahve... Ve aynı miktarda kakao... Bunun maliyeti..."+sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)],GOOD_COFFEE,PRICE_TYPE_BUY,pchar,300)+GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)],GOOD_CHOCOLATE,PRICE_TYPE_BUY,pchar,300))+" pesos!";
			if(pchar.money < sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)))
			{
				link.l1 = "Hmm... Affedersiniz, yeterli param yok gibi görünüyor. Lütfen bekleyin: Şimdi gemiye gidip biraz para alacağım - hemen döneceğim!";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "Buyurun.";
				link.l1.go = "SharkGoldFleet_02";
			}
		break;
		
		case "SharkGoldFleet_02":
			if(GetCargoFreeSpace(pchar) < 1200)
			{
				dialog.text = "Bir dakika, señor. Görünen o ki, geminizde böyle bir yük için yeterli yer yok. Ambarı boşaltıp tekrar gelin.";
				link.l1 = "Ah, boşaltmayı unuttum! Bir dakika bekleyin - hemen geliyorum!";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Harika! Malların geminize yüklenmesi için hemen talimat vereceğim. Sizinle iş yapmak gerçekten bir zevk!";
				link.l1 = "Karşılıklı, señor! Şimdi ise müsaadenizi isteyeyim: işler beklemez.";
				link.l1.go = "SharkGoldFleet_03";
			}
		break;
		
		case "SharkGoldFleet_03":
			DialogExit();
			AddMoneyToCharacter(pchar, -sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)))
			SetCharacterGoods(pchar, GOOD_COFFEE, GetCargoGoods(pchar, GOOD_COFFEE)+300);
			SetCharacterGoods(pchar, GOOD_CHOCOLATE, GetCargoGoods(pchar, GOOD_CHOCOLATE)+300);
			AddQuestRecord("SharkGoldFleet", "4");
			pchar.questTemp.SharkGoldFleet = "toCarPortOffice";
		break;
		
		case "SharkGoldFleet_again":
			dialog.text = " Mallar sizi bekliyor. Parayı getirdiniz mi? ";
			if(pchar.money < sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)))
			{
				link.l1 = "Henüz değil. Sadece teklifinizin hâlâ geçerli olduğundan emin olmak istedim. Para da yakında gelecek.";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "Buyurun.";
				link.l1.go = "SharkGoldFleet_02";
			}
		break;
		//<-- на пару с Акулой
		case "no_quests":
			dialog.text = "Şu anda hizmetlerinize ihtiyacım yok.";
			link.l1 = "Yazık. Konuyu değiştirelim.";
			link.l1.go = "node_1";
		break;
		
        case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Exit":			
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();			
		break;
	}
}

int findStoreMan(ref NPChar, int iTradeNation)
{
    ref ch;
	int n;
    int storeArray[30];
    int howStore = 0;

	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
        if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_Store.c") // магазин
		{
            if (sti(ch.nation) !=  iTradeNation) continue;
            if (NPChar.id == ch.id) continue;
            if (NPChar.id == "Panama_trader" || ch.id == "Panama_trader") continue; //нельзя доплыть
			if (NPChar.id == "SanAndres_trader" || ch.id == "SanAndres_trader") continue; // fix 2016-03-07
            if (ch.location == "none") continue; // фикс для новых, невидимых до поры островов
            if (GetIslandByCityName(ch.city) == GetIslandByCityName(NPChar.city)) continue; // хрен вам, а не читы!
            storeArray[howStore] = n;
            howStore++;
		}
    }
    if (howStore == 0)
    {
        return -1;
    }
    else
    {
        return storeArray[rand(howStore-1)];
    }
}

int Sunplace_Shiptype() // new
{
	int i;
	
	if (sti(pchar.rank) >= 1 && sti(pchar.rank) < 6) i = SHIP_SCHOONER;
	if (sti(pchar.rank) >= 6 && sti(pchar.rank) < 11) i = SHIP_FLEUT;
	if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 18) i = SHIP_PINNACE;
	if (sti(pchar.rank) >= 18) i = SHIP_GALEON_L;
	
	return i;
}

string findSunplaceCity(ref NPChar) // new
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != GetIslandByColony(&colonies[n])) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hrand(howStore-1)];
	return colonies[nation].id;
}
