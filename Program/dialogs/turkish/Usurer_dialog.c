// общий диалог ростовщиков
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, chr, sld;
	aref Link, NextDiag;
	string NPC_Area, sTemp, sTitle, sDepositType1, sDepositType2;
	int LoanSum, LoanInterest, LoanPeriod, LoanResult, iPastMonths, DepositSum, DepositInterest, DepositResult, iNum, iTemp, iTotalDublonQty;
	int iRes, iPer, iDep;
	float fPer;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string iDay, iMonth, s1;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	NPC_Area = Npchar.City;
	sDepositType1 = NPC_Area + "_Type1";
	sDepositType2 = NPC_Area + "_Type2";
 
	if(!CheckAttribute(npchar, "quest.item_date"))
	{
		npchar.quest.item_date = "";
	} 
 
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Usurer\" + NPChar.City + "_Usurer.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06

	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }
    if (!CheckAttribute(npchar, "quest.FindCitizenNoShip"))
    {
        npchar.quest.FindCitizenNoShip = 0;
    }

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
			if (LAi_group_GetPlayerAlarm() > 0)
			{
				//--> работорговец
				if(pchar.questTemp.Slavetrader == "After_enterSoldiers" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
				{
					dialog.text = " Bitti. Şimdi buradan defol, "+pchar.name+". Bütün bu karmaşayı ben temizleyeceğim.";
					link.l1 = "Pekala, yelken açıyorum!";
					link.l1.go = "exit";
					break;
				}
				//<-- работорговец
			
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Şehir alarma geçti ve her yerde seni arıyorlar! Ben olsam burada fazla kalmazdım.","Tüm muhafızlar seni arıyor. Aptal değilim, seninle konuşmayı göze alamam!","Kaç, "+GetSexPhrase("pal","kız")+", askerler seni delik deşik etmeden önce..."),LinkRandPhrase("Ne istiyorsun, aşağılık yaratık?! Şehir muhafızları durumundan haberdar ve kaçamayacaksın, "+GetSexPhrase("pis korsan","sen korsan fahişesi")+"!","Pis katil, buradan defol! Muhafızlar!","Senden korkmuyorum, alçak yaratık! Yakında kalemizde asılacaksın, kaçamayacaksın..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, bu benim için sorun değil...","Beni asla yakalayamazlar."),RandPhraseSimple("Çeneni kapa, "+GetWorkTypeOfMan(npchar,"")+", yoksa o lanet dilini koparırım!","Heh, "+GetWorkTypeOfMan(npchar,"")+" , sen de bir korsanı yakalamak mı istiyorsun? Dinle evlat, burada sessizce oturursan hayatta kalırsın..."));
				link.l1.go = "fight";
				break;
			}
		//Jason ---------------------------------------Бремя гасконца------------------------------------
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.location == "Fortfrance_bank")
			{
				dialog.text = "Bir şey mi istiyorsunuz, monsieur?";
				Link.l1 = "Bazı bilgilere ihtiyacım var... Sana bir şey sormak istiyorum.";
				Link.l1.go = "quests";
				Link.l2 = "Küçük bir borç almak ister misiniz?";
				Link.l2.go = "sharlie_credit";
				Link.l3 = "Hayır, fikrimi değiştirdim.";
				Link.l3.go = "exit";
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
				{
					link.l4 = "Şu küpelere bir bakın, monsieur. Onları ormandaki bir haydutun cebinde buldum. Bu kesinlikle usta bir kuyumcunun işi ve eminim ki bu vahşi topraklardan gelmiyor. Ne dersiniz?";
					link.l4.go = "Sharlie_junglejew";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskiper")
				{
					link.l1 = "Folke Deluc adında bir borçlunuz olduğunu biliyorum. Söyler misiniz, onun... gecikmesi ne kadar ciddi?";
					link.l1.go = "Sharlie";
				}	
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipermoney")
				{
					link.l1 = "Folke Deluc'un borcu hakkında buradayım.";
					link.l1.go = "Sharlie_repeat";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipercaptive")
				{
					link.l1 = "Görevinizi tamamladım, monsieur. İşte sizin... İspanyol dostunuz.";
					link.l1.go = "Sharlie_14";
				}
				break;
			}			
		//<-- Бремя гасконца
			
			//--> работорговец
			if (pchar.questTemp.Slavetrader == "canTakeQuest" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Nihayet, değerli bir kaptan mekanımı şereflendirdi. Sürekli, paralarını bana verip ben de onları toprağa eker gibi ekerek her ay faizlerini ödediğimi sanan aptallardan bıktım artık.\nHer kuruşlarını sayıyorlar, zavallı tefeci ise açlıktan ölmemek için türlü hilelere başvurmak zorunda kalıyor, bir yandan da onlara Noel’de kaz alacak parayı sağlıyor, bundan haberleri yok.";
				Link.l1 = "Müşterilerinizin, birikimlerini emanet ettikleri adamdan böyle sözler duymaktan memnun kalacaklarını sanmıyorum.";
				Link.l1.go = "GiveTaskSlave";
				npchar.quest.slave = "current";//чтобы камнем не долбил
				break;
			}	
			
			if (pchar.questTemp.Slavetrader == "TakeShoreCap_end" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "...";
				Link.l1 = "Dinle, yaşlı fare, şimdi her şeyi bana en iyi şekilde açıklaman gerekiyor! O geminin yükünde köle yoktu, sadece bir grup asker vardı! Onlarla başa çıkmak gerçekten zordu! Çok sinirliyim, o yüzden kendini iyi açıklasan iyi edersin!";
				Link.l1.go = "Slaveshore_5";
				break;
			}	
			if (pchar.questTemp.Slavetrader == "Win_HavanaFort" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Ah, sonunda geldiniz! Tüm takımada cesur saldırınızı konuşuyor. Sizi görmek güzel!";
				Link.l1 = "Böyle bir şöhrettense bilinmezliği tercih ederim... Bu çok tehlikeli.";
				Link.l1.go = "Win_Havana_Fort";
				break;
			}	
			if (pchar.questTemp.Slavetrader == "Havana_seekslaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Beş bin kölemi getirdin mi?";
				if (GetSquadronGoods(Pchar, GOOD_SLAVES) >= 5000)
				{
					Link.l1 = "Var. Yük ambarımda duruyorlar.";
					Link.l1.go = "Havana_Fort_yesA";
				}
				else
				{
					Link.l1 = "Hayır, bunun üzerinde hâlâ çalışıyorum.";
					Link.l1.go = "exit";
				}
				break;
			}	
			
			if (pchar.questTemp.Slavetrader == "End_quest_bad" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Hm... Hâlâ hayatta mısın? Garip. Ama uzun sürmeyecek. Askerler! Yardım edin! Burada bir haydut var!";
				link.l1 = "Ne alçak herif!";
				link.l1.go = "exit";
				LAi_group_Attack(NPChar, Pchar);
				break;
			}
			
			if(pchar.questTemp.Slavetrader == "wait_6" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_6") > 6 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "İyi günler. Benim adım "+GetFullName(npchar)+". Size nasıl yardımcı olabilirim?";
				link.l1 = "Ah! Burada ne yapıyorsunuz, efendim?";
				link.l1.go = "Usurer_Escape";
				break;
			}
			//<-- работорговец
			// ФМК-Гваделупа
			if(CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "killers" && npchar.location == "BasTer_bank")
			{
				dialog.Text = "...";
				link.l1 = "Hey orada, seni alçak. Parlak bir fikrin mi vardı? Kiralık adamlar tuttun beni öldürmek için? Beni susturmak mı istedin? Konuş, şimdi!";
				link.l1.go = "FMQG_x";
				break;
			}
			// Леди Бет -->
			if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_Bank" && !CheckAttribute(pchar, "questTemp.LadyBeth_Usurer")) // Блеквуд в городе
			{
				dialog.Text = "Oh, Kaptan! Lütfen, bugün size neler getirdiğime bir bakın. Blackwood'un adamlarından aldığım bazı eşyalar var. Yeni bir sefer için paraya ihtiyaçları var, bize ise... kâr, değil mi?";
				link.l1 = "Blackwood adamlarının bulduklarını sattıklarından haberdar mı?";
				link.l1.go = "LadyBeth_Usurer_1";
				break;
			}
			// Леди Бет <--
			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = LinkRandPhrase(LinkRandPhrase("İyi günler dilerim, "+GetAddress_Form(NPChar)+" . Size nasıl yardımcı olabilirim? Sizi tanıyor muyum?","Buyurun, kaptan. Benim adım "+GetFullName(npchar)+" ve ben buranın bankacısıyım.","Tanıştığımıza memnun oldum, "+GetAddress_Form(NPChar)+"! Ben yerel bir bankacıyım, eğer bir para sorununuz varsa, size yardımcı olabilirim."),LinkRandPhrase("Daha önce tanışmış mıydık, kaptan? Ben "+GetFullName(npchar)+", ve ben yerel bir bankacıyım.","Buyurun, Kaptan. Benim adım "+GetFullName(npchar)+" ve ben buranın yerel bankacısıyım.","Selamlar, "+GetAddress_Form(NPChar)+". Ben "+GetFullName(npchar)+",   yerel bankacı."),LinkRandPhrase("Tanıştığımıza memnun oldum, "+GetAddress_Form(NPChar)+", ben "+GetFullName(npchar)+" bu harika kasabada sadece mütevazı bir bankacıyım.","Karar sizin, kaptan! Benden borç almak mı istersiniz yoksa faizle para mı vermek istersiniz?","Sayın Kaptan! Mütevazı ofisimi ziyaret ettiğiniz için çok memnun oldum!"));
				link.l1 = RandPhraseSimple(LinkRandPhrase("Memnuniyetle! Şehirde dolaşıyordum ve sizi ziyaret etmeye karar verdim.","Memnuniyetle, ben "+GetFullName(pchar)+", tanıştığımıza memnun oldum.",""+GetFullName(pchar)+" ,   adındaki geminin kaptanı "+pchar.ship.name+" , tanıştığımıza memnun oldum. Burası bir banka, değil mi?"),RandPhraseSimple("Sizinle tanışmak güzel. Ben "+GetFullName(pchar)+".   Bir geminin kaptanı, adı  "+pchar.ship.name+". Sadece sizi tanımak istemiştim.","Aha, demek burada bir bankanız var, öyle mi? Tanıştığımıza memnun oldum, ben "+GetFullName(pchar)+", kendi gemimin kaptanıyım."));
				link.l1.go = "next";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_bank")
				{
					dialog.text = "Lady MacArthur, hoş geldiniz, lütfen buyurun.";
					link.l1 = "Sana da, "+npchar.lastname;
					link.l1.go = "Helen_next";
				}
			}
			else
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Sen misin! Ne istiyorsun, "+GetAddress_Form(NPChar)+"?","Ne getirdi sizi buraya, kaptan? Üzgünüm ama itibarınız sizi pek arzu edilen bir müşteri yapmıyor.","Aha, bir müşteri daha! İlk başta seni bir soyguncu sandım... ha-ha, şaka yapıyorum tabii."),LinkRandPhrase("Ah! Ne istiyorsunuz? Burası bir banka, meyhane değil.","İyi günler dilerim, kaptan. Size belirtmeliyim ki, müşterilerimi seçerken oldukça titizim.","Ne istiyorsunuz, "+GetFullName(pchar)+"? Ününüzün büyük bir kredi çekmenize yetmeyeceğini hatırlıyorsunuzdur umarım?"),LinkRandPhrase("Umarım para yatırmak istiyorsunuz, "+GetAddress_Form(NPChar)+"? Sizin için bir kredi sağlamak kolay olmayacak.","Kaptan "+GetFullName(pchar)+" Ne istiyorsunuz mütevazı bir bankacıdan? Üzgünüm, fakat size kredi ayarlayamam. Yalnızca ben size faizle borç verebilirim.","Buyurun, "+GetAddress_Form(NPChar)+"Üzgünüm, size en hoş karşılanan müşteri olmadığınızı bildirmek zorundayım, fakat genelde insanları hemen geri çevirmem.")),LinkRandPhrase(LinkRandPhrase("Merhaba, efendim "+GetFullName(pchar)+"! İş konularında size her zaman yardımcı olmaya hazırım.","Merhaba, efendim "+GetAddress_Form(NPChar)+". Her zaman kredi vermeye ya da herhangi bir yatırımı kabul etmeye hazırım.","Sayın "+GetFullName(pchar)+"! Sizi görmek ne güzel! Ne istemiştiniz?"),LinkRandPhrase("Kaptan "+GetFullName(pchar)+"! Her zaman hizmetinizdeyim. Kredi almak mı yoksa faizle para yatırmak mı istersiniz?","Size selamlar, kaptan! Burada her zaman hoş karşılanan bir müşterisiniz. Ticaretteki ününüz gerçekten etkileyici!","İyi günler, "+GetFullName(pchar)+". Sizi tekrar gördüğüme sevindim. Umarım karlı bir iş anlaşması için geldiniz?"),LinkRandPhrase("İyi günler kaptan! Ne arzu edersiniz? Borç almak mı yoksa yatırım yapmak mı istiyorsunuz?","Kaptan "+GetFullName(pchar)+"! Karlı şartlarla borç almak mı istiyorsunuz? Böyle saygın bir müşteriyi her zaman görmekten memnuniyet duyarım.","Sizi tekrar görmek ne güzel, kaptan! Size her zaman yardımcı olmaya hazırım; ister kredi çekmek, ister yatırım yapmak isteyin.")));
				link.l1 = pcharrepphrase(RandPhraseSimple(LinkRandPhrase("Şaka yapmıyorum, banker, burada işimi yürütmem gerekiyor.","Çok fazla konuşuyorsun dostum. Hadi doğrudan işe geçelim.","Paranın kokusu olmadığını duydunuz mu? O halde burnunuzu tıkayın ve işimize bakalım."),LinkRandPhrase("Ve müşterilerinizi böyle mi karşılıyorsunuz? Neyse ki bugün keyfim yerinde.","Ha! Beni gördüğüne sevinmedin mi, ha? Sana iyi bir izlenim bırakacak altın bir doblon değil miyim ben. Neyse, işimize bakalım, tefeci.","Eh, sana biraz saygı öğretmek isterdim ama buna vaktim yok. Bunun yerine paradan konuşalım.")),RandPhraseSimple(LinkRandPhrase("Eski dostumu görmek ne güzel!","Buraya gelmek her zaman bir zevk, dostum. Hadi doğrudan konuya girelim.","Ben de çok memnun oldum. Şimdi iş konuşalım, dostum."),LinkRandPhrase("Sizi görmek gerçekten güzel. Finansal denizlerde neler var, anlat bakalım?","Beni hâlâ hatırladığınıza sevindim. Acelem var, o yüzden hemen konuya girelim.","Merhaba, eski dostum! Seni tekrar görmek ne güzel!")));
				link.l1.go = "next";
			}
			break;
			
			case "next":
			dialog.text = NPCStringReactionRepeat("Size nasıl yardımcı olabilirim?","Bu sefer ne istiyorsunuz?","Hm... endişeleriniz neler?","Eh, "+GetAddress_Form(npchar)+", müşterilerin ne kadar sinir bozucu olabileceğini hayal bile edemezsin...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Hayır, teşekkürler, sadece dolaşıp konuşuyorum.","Yine ben. Sadece seninle konuşmak istedim.","Evet, yine ben. Ciddi bir şey yok, sadece seninle konuşmak istedim.","Evet, banker olmak bazen o kadar da kolay değil. Sadece konuşmak istedim...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = "Finansal meselelerimizi konuşmak istiyorum.";
			link.l2.go = "LoanUsurer";//(на кредитный генератор)
			link.l3 = "Mücevherler ve sıradışı putlar ya da değerli taşlar ilgimi çeker.";
			if (!isMultiObjectKnown("gold_dublon"))
			{
				link.l3.go = "items_0";
			}
			else
			{
				link.l3.go = "items_1";
			}	
			link.l4 = "Biraz bilgiye ihtiyacım var. Aslında, size bir şey sormak istiyorum.";
			link.l4.go = "quests";//(перессылка в файл города)
//Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "Sana iş evraklarını getirdim "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//квесты мэра, проникновение во враждебный город
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("Ben buraya bir adamın emriyle geldim. O bir vali "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+"   beni buraya gönderdi. Senden bir şey almam gerekiyor.");
				link.l7.go = "IntelligenceForAll";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "usurer_keeper")
			{
				link.l9 = "İyi günler, oğlunuz tarafından davet edildim."; 
				link.l9.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}	
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer"))
			{
				link.l10 = "Belgenin sahibinin kim olduğunu öğrenmek istiyorum.";
				link.l10.go = "ShipLetters_Usurer1";			
			}
			
			//--> семейная реликвия // лесник переписал с нпчара на чара 
			if (CheckAttribute(pchar, "GenQuest.Noblelombard") && npchar.city == pchar.GenQuest.Noblelombard.City && !CheckAttribute(pchar, "quest.noblelombard"))// вот тут 
			{
				link.l11 = "Müşterinizin borcu hakkında konuşmak istiyorum. Adı "+pchar.GenQuest.Noblelombard.Name+". Aile yadigarını rehin bıraktı. Burada onun adına konuşuyorum ve size iadesi hakkında konuşma hakkım var.";
				link.l11.go = "Noblelombard";			
			}
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Giveregard") && npchar.city == pchar.GenQuest.Noblelombard.City)
			{
				link.l11 = "Üç ay önce bir toplantı yapmıştık ve bir adamın yadigârı hakkında konuşmuştuk. Adı "+pchar.GenQuest.Noblelombard.Name+" . Hatırlıyor musun? Benim adıma bir mevduat hesabı açmak zorunda kaldı. Tutarı ise  "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Regard))+"...";
				link.l11.go = "Noblelombard_5";			
			}
			//<-- семейная реликвия
			
			//-->работорговец
			if (pchar.questTemp.Slavetrader == "Seek_slaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id) 
			{
				link.l8 = "Bu ... köle görevinizle ilgili.";
				link.l8.go = "Checkslaves";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "İyi günler, "+NPChar.name+", göreviniz hakkında konuşalım.";
				link.l8.go = "Takeslaves_4_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway_pinas" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "İyi günler, "+NPChar.name+", göreviniz hakkında konuşalım.";
				link.l8.go = "Pinas_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "died" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "İyi günler, "+NPChar.name+", göreviniz hakkında konuşalım.";
				link.l8.go = "Takeslaves_4_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait") > 20 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Anlaştığımız gibi geldim. Benim için bir işin var mı?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "waitship" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Söz verdiğim gibi geldim. Bir iş var mı?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_1" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_1") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "İyi günler, "+npchar.name+" . Nasılsınız? Benim için yeni bir görev var mı?";
				link.l8.go = "EscapeSlave";
				break;
			}
			if(pchar.questTemp.Slavetrader == "escapeslave_win" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Göreviniz tamamlandı. O kaçakları bulabildim. Ama o kadar da kolay olmadı.";
				link.l8.go = "Escape_slaves_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_2" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_2") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "İyi günler, "+npchar.name+". Yeni, kârlı bir görev için geldim.";
				link.l8.go = "Slaveshore";
				break;
			}			
			
			if(pchar.questTemp.Slavetrader == "goodbye" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Kötü haber,"+npchar.name+". Brigantinayı ele geçiremedim.";
				link.l8.go = "Brig_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goodbye_1" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bak,  "+npchar.name+". Brigantini kovaladım, ama hiçbir belge bulamadım. Orada olduklarına emin misiniz?";
				link.l8.go = "Letter_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "winbrig" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "İyi haber, "+npchar.name+". O brigantinoyu bulup evrakları geri almayı başardım. İşte burada.";
				link.l8.go = "Brig_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_3" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_3") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "İyi günler, "+npchar.name+" . Benim için yeni bir görev hazırladınız mı?";
				link.l8.go = "SlaveGalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wingalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", şu sözde 'galyonu' ele geçirmeyi başardım.";
				link.l8.go = "Wingalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostgalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", Çok üzgünüm, ama bu kalyona çıkamadım.";
				link.l8.go = "Lostgalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_4" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_4") > 4 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "İyi günler, "+npchar.name+". Paramı almaya geldim.";
				link.l8.go = "FindRat";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wincorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", göreviniz tamamlandı. O alçak Gontier öldü, mürettebatı da onunla birlikte.";
				link.l8.go = "Wincorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostcorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", Üzgünüm, fakat Francois Gontier'i yakalayamadım, onu Tortuga'ya kadar takip etmeme rağmen. Kendi korvetiyle benden kaçmayı başardı.";
				link.l8.go = "lostcorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_5" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_5") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "İyi günler,"+npchar.name+" .   Bana hazırladığınız bu yeni görevden bahseder misiniz?";
				link.l8.go = "Havana_fort";
				break;
			}
			//<--работорговец
			NextDiag.TempNode = "First time";
		break;
		
		case "Helen_next":
			dialog.text = NPCStringReactionRepeat("Paraya ihtiyacınız olduğunu ya da servetinizi artırmak istediğinizi söyleyemem. Sizi ofisime getiren sebep nedir?","Bu sefer ne istiyorsunuz?","Hm... endişeleriniz neler?","Eh, "+GetAddress_Form(npchar)+", müşterilerin ne kadar can sıkıcı olabileceğini hayal bile edemezsin...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Hayır, teşekkürler, sadece dolaşıp konuşuyorum.","Yine ben. Sadece seninle konuşmak istedim.","Evet, yine ben. Ciddi bir şey yok, sadece seninle konuşmak istedim.","Evet, banker olmak bazen o kadar da kolay değil. Sadece biraz konuşmak istedim...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = "Finansal meselelerimizi konuşmak istiyorum.";
			link.l2.go = "LoanUsurer";//(на кредитный генератор)
			link.l3 = "Mücevherler, sıradışı putlar ya da değerli taşlar ilgimi çeker.";
			if (!isMultiObjectKnown("gold_dublon"))
			{
				link.l3.go = "items_0";
			}
			else
			{
				link.l3.go = "items_1";
			}	
			link.l4 = "Biraz bilgiye ihtiyacım var. Aslında, size bir şey sormak istiyorum.";
			link.l4.go = "quests";//(перессылка в файл города)
//Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "Sana iş evraklarını getirdim "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//квесты мэра, проникновение во враждебный город
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("Ben buraya bir adamın emriyle geldim. O bir vali "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".",GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+"     beni buraya gönderdi. Senden bir şey almam gerekiyor.");
				link.l7.go = "IntelligenceForAll";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "usurer_keeper")
			{
				link.l9 = "İyi günler, oğlunuz tarafından davet edildim."; 
				link.l9.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}	
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer"))
			{
				link.l10 = "Belgenin sahibinin kim olduğunu öğrenmek isterim.";
				link.l10.go = "ShipLetters_Usurer1";			
			}
			
			//--> семейная реликвия // лесник переписал с нпчара на чара 
			if (CheckAttribute(pchar, "GenQuest.Noblelombard") && npchar.city == pchar.GenQuest.Noblelombard.City && !CheckAttribute(pchar, "quest.noblelombard"))// вот тут 
			{
				link.l11 = "Müşterinizin borcu hakkında konuşmak istiyorum. Adı "+pchar.GenQuest.Noblelombard.Name+". Aile yadigârını rehin bıraktı. Burada onun çıkarlarını temsil ediyorum ve size iadesini konuşma hakkım var.";
				link.l11.go = "Noblelombard";			
			}
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Giveregard") && npchar.city == pchar.GenQuest.Noblelombard.City)
			{
				link.l11 = "Üç ay önce bir toplantı yapmıştık ve bir adamın yadigârı hakkında konuşmuştuk. Adı "+pchar.GenQuest.Noblelombard.Name+". Hatırlıyor musun? Benim adıma bir mevduat hesabı açmak zorundaydı. Tutarı ise  "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Regard))+"...";
				link.l11.go = "Noblelombard_5";			
			}
			//<-- семейная реликвия
			
			//-->работорговец
			if (pchar.questTemp.Slavetrader == "Seek_slaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id) 
			{
				link.l8 = "Bu ... köle görevinizle ilgili.";
				link.l8.go = "Checkslaves";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "İyi günler, "+NPChar.name+", göreviniz hakkında konuşalım.";
				link.l8.go = "Takeslaves_4_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway_pinas" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "İyi günler, "+NPChar.name+", göreviniz hakkında konuşalım.";
				link.l8.go = "Pinas_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "died" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "İyi günler, "+NPChar.name+", göreviniz hakkında konuşalım.";
				link.l8.go = "Takeslaves_4_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait") > 20 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Söz verdiğimiz gibi geldim. Bana bir işin var mı?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "waitship" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Söz verdiğim gibi geldim. Bir iş var mı?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_1" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_1") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "İyi günler, "+npchar.name+" . Nasılsınız? Benim için yeni bir görev var mı?";
				link.l8.go = "EscapeSlave";
				break;
			}
			if(pchar.questTemp.Slavetrader == "escapeslave_win" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = " Görevin tamamlandı. O kaçakları bulabildim. Ama o kadar da kolay olmadı.";
				link.l8.go = "Escape_slaves_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_2" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_2") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "İyi günler, "+npchar.name+". Yeni kârlı bir görev için geldim.";
				link.l8.go = "Slaveshore";
				break;
			}			
			
			if(pchar.questTemp.Slavetrader == "goodbye" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Kötü haber,"+npchar.name+". Brigantinayı alamadım.";
				link.l8.go = "Brig_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goodbye_1" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Bak,  "+npchar.name+". Brigantini yakaladım, ama hiçbir belge bulamadım. Emin misiniz orada olduklarından?";
				link.l8.go = "Letter_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "winbrig" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "İyi haberler,"+npchar.name+". O brigantinoyu bulup belgeleri geri almayı başardım. İşte burada.";
				link.l8.go = "Brig_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_3" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_3") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "İyi günler, "+npchar.name+" . Benim için yeni bir görev hazırladınız mı?";
				link.l8.go = "SlaveGalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wingalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", o sözde 'galyonu' yakalamayı başardım.";
				link.l8.go = "Wingalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostgalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", Çok üzgünüm, ama bu kalyona çıkamadım.";
				link.l8.go = "Lostgalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_4" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_4") > 4 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "İyi günler, "+npchar.name+". Paramı almaya geldim.";
				link.l8.go = "FindRat";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wincorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", göreviniz tamamlandı. O alçak Gontier öldü, mürettebatı da öyle.";
				link.l8.go = "Wincorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostcorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = ""+npchar.name+", Üzgünüm, ama Francois Gontier'i yakalayamadım, onu Tortuga'ya kadar takip etmeme rağmen. Kendi korvetiyle elimden kaçmayı başardı.";
				link.l8.go = "lostcorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_5" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_5") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "İyi günler,"+npchar.name+" .   Bana benim için hazırladığınız bu yeni görevden bahsedin.";
				link.l8.go = "Havana_fort";
				break;
			}
			//<--работорговец
			NextDiag.TempNode = "First time";
		break;

		case "items_0":
			dialog.text = "Altın doblonlar ya da sandıklar satın almak ister misiniz? Bana güvenin, bu çok değerli bir yatırım.";
			link.l1 = "Evet, bu gerçekten çok ilginç.";
			link.l1.go = "items";
			AddQuestRecordInfo("Recipe", "Gold_dublon");
			SetAlchemyRecipeKnown("gold_dublon");
			SetAlchemyRecipeKnown("Chest");
			npchar.quest.meeting = "1"; 			
		break;
		
		case "items_1":
			dialog.text = "Peso mu yoksa dublon mu kullanmak istersiniz?";
			link.l1 = "Peso karşılığında.";
			link.l1.go = "items";
			link.l2 = "Dubloonlar için.";
			link.l2.go = "items_dub";
		break;
		
		case "items":
			if (npchar.quest.item_date != lastspeak_date)
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}
			if(CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu")) AddItems(npchar, "gold_dublon", 100);
			if(CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat")) AddItems(npchar, "gold_dublon", 100);
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "items_dub":
			if (npchar.quest.item_date != lastspeak_date)
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}
			if(CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu")) AddItems(npchar, "gold_dublon", 100);
			if(CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat")) AddItems(npchar, "gold_dublon", 100);
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 1);
		break;
		
		//<<<<----------генератор -"Shipping documents". ------		
		case "ShipLetters_Usurer1":
			pchar.questTemp.different.GiveShipLetters.speakUsurer = true;
			dialog.text = "Bu evrakları okumak çok vaktimi alacak ve vaktim gerçekten pahalıya mal olur.";
			link.l1 = "Belki, "+sti(pchar.questTemp.different.GiveShipLetters.price1)+" peso bu süre için size yeterli bir karşılık olur mu?";
			link.l1.go = "ShipLetters_Usurer2";
			link.l2 = "Dediğiniz gibi. Hoşça kalın!";
			link.l2.go = "exit";
		break;
		
		case "ShipLetters_Usurer2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.GiveShipLetters.price1));
			pchar.questTemp.different.GiveShipLetters.speakUsurer_1 = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Bir bakayım! Hayır, bu ismi daha önce hiç duymadım. Bunu liman başkanımıza göster.";
				link.l1 = "Üzgünüm, ama bir anlaşmamız vardı! Bana bu kaptan hakkında bilgi vereceğine söz vermiştin!";
				link.l1.go = "ShipLetters_Usurer2_1";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				s1 = "Well... I know the owner of this ship. He is not a very rich man, but he has some wealth.";
				dialog.text = s1+" Onun başarılı bir kaçakçı olduğunu söylüyorlar. Duymak istediğin bu muydu?";
				link.l1 = "Öyle görünüyor...";
				link.l1.go = "ShipLetters_Usurer2_2";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				s1 = "Well... I am not sure that I can congratulate you for your found.";
				dialog.text = s1+"Bu belgeler sömürge devriye gemimiz için imzalanmış, ve kaptanı sağlam prensipleriyle tanınır.";
				link.l1 = "Bir devriye mi? Komutanın emriyle mi?";
				link.l1.go = "ShipLetters_Usurer2_3";
			}
		break;
		
		case "ShipLetters_Usurer2_1":
			dialog.text = "Sana o evraklara bakacağıma ve başka bir şey yapmayacağıma söz verdim. Gidebilirsin.";
			link.l1 = "Teşekkürler... sanırım.";
			link.l1.go = "exit";
		break;
		
		case "ShipLetters_Usurer2_2":
			dialog.text = "Karar sizin. Komutanımız uzun zamandır bu kişiye karşı epey bir 'ilgi' gösteriyor. Şimdiden bir fikriniz var mı? Burada ise üzerinde hiçbir işaret olmayan konşimentolarımız var...";
			link.l1 = "Anladım. Teşekkür ederim!";
			link.l1.go = "exit";		
		break;
		
		case "ShipLetters_Usurer2_3":
			s1 = "Exactly. Our smugglers are bearing a grudge against this captain by the way.";
			dialog.text = s1+"Ve daha önce de belirttiğim gibi, senedin sahibi prensip sahibi bir adamdır ve yerel suçlardan pek hoşlanmaz.";
			link.l1 = "Anladım. Minnettarım!";
			link.l1.go = "exit";		
		break;

		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Ah, anladığım kadarıyla kayıp oğlumu ve genç gelinini getiren kaptan sizsiniz?";
				link.l1 = "Evet, onlara kaçmalarında yardım eden bendim.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Ah, işte buradasınız, iyilikseverim. Bir ödül bekliyorsunuz, öyle mi?";
				link.l1 = "Teşekkürünüz yeterli olurdu, en azından...";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Çocuğuma yardım edip onu o sıkıntılı durumda yalnız bırakmadığınız için gerçekten minnettarım. Lütfen, size elimden geldiğince teşekkür etmeme izin verin. Bu mütevazı miktarı ve küçük bir hediyemi kabul edin.";
			link.l1 = "Teşekkür ederim. Bu genç çifte yardım etmek benim için bir zevkti.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Teşekkür mü? Neyin teşekkürü? Bu ahmak yılın yarısını işsiz geçirdi, şimdi de hemen kendine bir kız bulmuş! Ben onun yaşındayken kendi işimi yürütüyordum. Evlenilecek bir valinin kızı var, ama o kalkıp bu kadını buraya getiriyor—Tanrım, bunu söylediğim için beni affet! Şimdi de benden hayır duası bekliyor!";
			link.l1 = "Duygulara inanmadığınızı mı düşünmeliyim?";
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
			dialog.text = "Duygular mı? Ne duygusu? Koskoca adamsın, bir de duygulardan mı bahsediyorsun? Gençlere yaranmak için kendini bu kadar küçültmene yazıklar olsun. Kızı ailesinden aldın, oğlumun hayatını mahvettin. Benden bir teşekkür bekleme. Elveda.";
			link.l1 = "Hoşça kal o zaman...";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("saw","saw"));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Кредитный генератор Loan
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "LoanUsurer":
			if (npchar.id == "Panama_Usurer")
			{
				if (sti(pchar.reputation.nobility) > 70 && ChangeCharacterNationReputation(pchar, SPAIN, 0) >= 80 && !CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
				{
					dialog.text = "Konuşalım. Dinliyorum.";
				}
				else
				{
					dialog.text = "Üzgünüm, size yardımcı olamam. "+GetAddress_Form(NPChar)+". Üzgünüm, ancak bankam İspanya'nın düşmanlarına hizmet vermiyor.";
					link.l1 = "Paranın milliyeti yoktur, señor banker.";
					if (CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
					{
						if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)) && makeint(Pchar.Quest.Deposits.(sDepositType1)) == true)
						{
							dialog.text = "Hı-hı, "+GetAddress_Form(NPChar)+". Size bildirmek zorundayım ki, mevduatınız artık geçerli değil.";
							Link.l1 = "Hangi gerekçeyle?!";
							Link.l1.go = "Panama_Deposit_SgorelVklad";
							DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
							break;						
						}
						else
						{
							link.l1.go = "Panama_Deposit_Cartahena";
							break;
						}
					}
					if (sti(pchar.reputation.nobility) < 71 || ChangeCharacterNationReputation(pchar, SPAIN, 0) < 80)
					{
						link.l1.go = "Panama_Deposit_NoReputation";
						break;
					}
				}
			}
			dialog.text = "Konuşalım. Dinliyorum.";
			//кредиты
            if(CheckAttribute(Pchar, "Quest.Loans." + (NPC_Area)) && makeint(Pchar.Quest.Loans.(NPC_Area)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makefloat(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);// boal 23.01.2004
				if(makeint(PChar.money) >= makeint(Pchar.Quest.Loans.(NPC_Area).Result))
				{
					Link.l5 = "Sana borçluyum "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result))+LinkRandPhrase(", paranızı geri ödemeye hazırım",". Borcumu ödemek istiyorum.",".  Sonunda, hesabı kapatma vakti geldi.");
					Link.l5.go = "loan_return";	
					sTemp = "credit";
				}					
			}
			else
			{
				Link.l6 = LinkRandPhrase("Birkaç altın ödünç almak istiyorum.","Gerçekten biraz peso bulmam lazım.","Küçük bir borç almak ister misiniz?");
				Link.l6.go = "loan";					
				if(makeint(Pchar.money) >= 100)
				{
					Link.l7 = LinkRandPhrase("Paramı faize yatırmak istiyorum.","Birkaç çuval gümüşümü burada saklamayı kabul eder misiniz?","Sana kötü günler için biraz gümüş bırakabilir miyim?"); // patch
					Link.l7.go = "deposit";				
				}			
				if(CheckUseDublons(NPChar))
				{
					Link.l8 = "Faiz için biraz doblon yatırmak istiyorum.";
					Link.l8.go = "deposit_dub";				
				}
			}
			
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)) && makeint(Pchar.Quest.Deposits.(sDepositType1)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(sDepositType1).StartYear),makeint(Pchar.Quest.Deposits.(sDepositType1).StartMonth),makeint(Pchar.Quest.Deposits.(sDepositType1).StartDay), makefloat(Pchar.Quest.Deposits.(sDepositType1).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+ ".Rem"))
				{
					Pchar.Quest.Deposits.(sDepositType1).Result = makeint(Pchar.Quest.Deposits.(sDepositType1).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)/100)*makefloat(Pchar.Quest.Deposits.(sDepositType1).Interest))*iPastMonths+sti(Pchar.Quest.Deposits.(sDepositType1).Rem);
				}
				else
				{
					Pchar.Quest.Deposits.(sDepositType1).Result = makeint(Pchar.Quest.Deposits.(sDepositType1).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)/100)*makefloat(Pchar.Quest.Deposits.(sDepositType1).Interest))*iPastMonths;
				}
				Link.l9 = LinkRandPhrase("Yatırımımı geri almak için buradayım, pesos olarak.","Bana borçlu olduğun gümüşü geri almanın zamanı geldi.","Yatırımımı faiziyle birlikte peso olarak geri istiyorum.");
				Link.l9.go = "Deposit_return";									
			}
			
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)) && makeint(Pchar.Quest.Deposits.(sDepositType2)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(sDepositType2).StartYear),makeint(Pchar.Quest.Deposits.(sDepositType2).StartMonth),makeint(Pchar.Quest.Deposits.(sDepositType2).StartDay), makefloat(Pchar.Quest.Deposits.(sDepositType2).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+ ".Rem"))
				{
					Pchar.Quest.Deposits.(sDepositType2).Result = makeint(Pchar.Quest.Deposits.(sDepositType2).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType2).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType2).Interest))*iPastMonths+sti(Pchar.Quest.Deposits.(sDepositType2).Rem);
				}
				else
				{
					Pchar.Quest.Deposits.(sDepositType2).Result = makeint(Pchar.Quest.Deposits.(sDepositType2).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType2).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType2).Interest))*iPastMonths;
				}
				Link.l10 = LinkRandPhrase("Yatırımımdaki doblonları geri almak istiyorum.","Bana borçlu olduğun altını geri alma zamanı geldi.","Yatırdığım doblonları, faiziyle birlikte geri istiyorum.");
				Link.l10.go = "Deposit_return_dub";									
			}
/*			
			
*/			
			//выход
			if (sTemp == "credit")
			{
				link.l11 = "Borcumu hatırlıyorum, ama henüz ödemeye hazır değilim...";
				link.l11.go = "Loan_Remind";
			}
			else
			{
				link.l11 = "Benim hatam, sizinle herhangi bir mali meselem yok. Hoşça kalın.";
				link.l11.go = "exit";
			}
		break;
		
		//============== кредиты ===============
		case "loan":
            if (sti(NPChar.nation) == PIRATE)
            {
                dialog.text = "Hayır, size yardımcı olamam. Bu sıkıntılı yerde yalnızca yatırımları kabul edebilirim. Gümüş peso ya da altın doblon yatırabilirsiniz.";				
                if(makeint(Pchar.money) >= 100)
				{
	                Link.l1 = "Peso yatırmak istiyorum, o yüzden miktarı konuşalım.";
	                Link.l1.go = "deposit";
				}				
				if(CheckUseDublons(NPChar))
				{
					Link.l2 = "Altın yatırmak istiyorum. Miktarı netleştirelim.";
					Link.l2.go = "deposit_dub";
				}
                Link.l3 = "İlgilenmiyorum.";
				link.l3.go = "exit";
                break;
            }
			// проверка на проф пригодность -->
            if (isBadReputation(pchar, 42))
            {
                dialog.text = RandSwear()+"Adınız "+GetFullName(pchar)+", değil mi? Sende var "+RandPhraseSimple("kötü bir şöhret ","kötü bir ün ")+" ve seninle iş yapmak istemiyorum.";
				link.l1 = RandPhraseSimple("Bir insan hata yapamaz mı?",RandSwear()+"Ne halin varsa gör!");
				link.l1.go = "exit";
                break;
            }
            // проверка на проф пригодность <--
			Dialog.snd = "voice\USDI\USDI016";
			dialog.text = "Ah, her zaman hoş geldiniz. Ne kadar bir miktara ihtiyacınız var?";
			Link.l1 = "Küçük bir tane.";
			Link.l1.go = "Small";
			Link.l2 = "Orta.";
			Link.l2.go = "Medium";
			Link.l3 = "Mümkün olduğunca büyük.";
			Link.l3.go = "Large";
		break;

		case "small":
			Pchar.Quest.Loans.(NPC_Area).Sum = 500*makeint(Pchar.rank)+125*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI017";
			dialog.text = "Mükemmel! Küçük meblağlarla uğraşmak her zaman çok daha kolaydır – iki taraf için de daha az risk demektir. Size şunu önerebilirim: "+FindRussianMoneyString(sti(Pchar.Quest.loans.(NPC_Area).sum))+"...";
			Link.l1 = "Anlaştık.   Peki ya sizin payınız?";
			Link.l1.go = "Interest";
			Link.l2 = "Bu bana uygun değil. Değiştirelim.";
			Link.l2.go = "Loan";
			Link.l3 = "Sanırım benim yüzümden borca girmemek daha iyi olur. Hoşça kal.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Medium":
			Pchar.Quest.Loans.(NPC_Area).Sum = 1500*makeint(Pchar.rank)+325*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI018";
			dialog.text = "Hiç sorun değil. Umarım "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum))+" sorunlarınızı çözmenize yardımcı olacak. Oldukça yüklü bir meblağ bu.";
			Link.l1 = "Anlaştık. Peki ya sizin payınız?";
			Link.l1.go = "Interest";
			Link.l2 = "Bu bana uygun olmaz. Değiştirelim.";
			Link.l2.go = "Loan";
			Link.l3 = "Borc işlerinden uzak durmam sanırım daha iyi olur. Hoşça kal.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Large":
			Pchar.Quest.Loans.(NPC_Area).Sum = 4000*makeint(Pchar.rank)+600*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI019";
			dialog.text = "Pekâlâ... bu biraz riskli. Tamam, sana bir kredi vermeye hazırım, miktarı ise "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum))+". Umarım beni anlarsınız, kaptan, bu gerçekten hatırı sayılır bir meblağ. Lütfen bunu ciddiye almanızı rica ediyorum.";
			Link.l1 = "Anlaştık. Peki, sizin payınız ne olacak?";
			Link.l1.go = "Interest";
			Link.l2 = "Bu bana uygun olmayacak. Hadi değiştirelim.";
			Link.l2.go = "Loan";
			Link.l3 = "Borc işlerinden uzak durmam sanırım daha iyi olur. Hoşça kal.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Interest":
			Pchar.Quest.Loans.(NPC_Area).Interest = 4.0 + (makeint((((6.0 - 4.0) * (GetSummonSkillFromName(pchar, "Commerce") + GetSummonSkillFromName(pchar, "Leadership")) / 200) ) / 0.5 + 0.5)) * 0.5;
			//Pchar.Quest.Loans.(NPC_Area).Interest = 16 - makeint(Pchar.skill.commerce);
			// Rebbebion, добавил фикс отображения знака процента
			Dialog.snd = "voice\USDI\USDI020";
			dialog.text = fts(stf(Pchar.Quest.Loans.(NPC_Area).Interest),1)+"Aylık %% . Sizin hakkınızdaki bilgilerime dayanarak daha iyi bir teklif sunamam."; 
			Link.l1 = "Bana uyar. Şimdi süreyi konuşalım.";
			Link.l1.go = "Period";
			Link.l3 = "Borc işlerinden uzak durmam sanırım daha iyi olur. Hoşça kalın.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Period":
			Pchar.Quest.Loans.(NPC_Area).Period = makeint(makeint(Pchar.reputation.nobility)/20) + 1;			
			Dialog.snd = "voice\USDI\USDI021";
			dialog.text = "Sizin hakkınızda bildiklerimi göz önünde bulundurarak, "+Pchar.name+",   bu borcun geri dönüşünü bekleyeceğim "+FindRussianMonthString(sti(Pchar.Quest.Loans.(NPC_Area).Period))+" . Bundan sonra gerekli önlemleri alacağım. Umarım bunu anlıyorsunuzdur."; 
			Link.l1 = "Şartlarınızı... ve paralarınızı memnuniyetle kabul ediyorum.";
			Link.l1.go = "LoanGranted";
			Link.l3 = "Affedersiniz, ama bu benim için uygun değil. Hoşça kalın.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "LoanGranted":
			Dialog.snd = "voice\USDI\USDI022";
			dialog.text = "Gerçekten memnun oldum. Ama sizi uyarmama izin verin. Bu işi uzun zamandır yapıyorum ve yatırımlarımı nasıl geri alacağımı iyi bilirim. O yüzden aklınızdan en ufak bir aptallık geçerse, bundan vazgeçmenizi tavsiye ederim\nAlınmayın, sadece bir uyarı.";
			Link.l1 = "Hm... Peki. Hoşça kal.";
			Link.l1.go = "LoanGranted_exit";
		break;

		case "Loan_Remind":
			Dialog.snd = "voice\USDI\USDI023";
			dialog.text = "Karar sizin, kaptan. Faizim artıyor ve sizin o kadar vaktiniz yok.";
			Link.l1 = "Endişelenme. Görüşürüz.";
			Link.l1.go = "exit";
		break;

		case "loan_return":
			addMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Loans.(NPC_Area).Result)));
			// boal 27.01.2004 -->
            if (npchar.quest.trade_date != lastspeak_date) // дыра с прокачкой была
            {
    			AddCharacterExpToSkill(Pchar, "Commerce", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 350);
    			AddCharacterExpToSkill(Pchar, "Leadership", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 700);
			}
			// boal 27.01.2004 <--
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area); // bug fix
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			Dialog.snd1 = "voice\USDI\USDI024";
			Dialog.snd2 = "voice\USDI\USDI025";
			Dialog.snd3 = "voice\USDI\USDI026";
			dialog.text = LinkRandPhrase("Harika! Paraya ihtiyacın olduğunda bana gel. Her zaman hizmetinde olacağım.","Teşekkür ederim. Borçlarını zamanında ödeyebilen biriyle iş yapmak her zaman bir zevk. Bazen aksilikler olur, bunu anlarım... ama sorunların çözüme kavuşmasını tercih ederim.","Ah, sana güvenmekle doğru yapmışım, "+GetAddress_Form(NPChar)+"! Umarım hizmetlerimden son kez yararlanmıyorsunuzdur. Artık dürüst bir insan olduğunuzu bildiğime göre, belki sizin için daha da iyi anlaşmalar yapabiliriz.");
			Link.l1 = LinkRandPhrase("Biraz borç para almak istiyorum.","Gerçekten biraz peso bulmam lazım.","Küçük bir borç almak ister misiniz?");
			Link.l1.go = "loan";			
			if(makeint(PChar.money) >= 100)
			{
				Link.l2 = LinkRandPhrase("Paramı yatırmak istiyorum.","Biraz korsan ganimeti saklayacak mısınız?","Yağmurlu bir gün için size biraz gümüş bırakabilir miyim?");
				Link.l2.go = "deposit";				
			}		
			if(CheckUseDublons(NPChar))	
			{
				Link.l3 = "Biraz dublonumu faizle yatırmak istiyorum";
				Link.l3.go = "deposit_dub";				
			}
			Link.l4 = "Elveda, "+NPchar.name+".";
			Link.l4.go = "ExitDelLoan1";
		break;

		case "deposit":
			dialog.text = LinkRandPhrase("Bilge birini görüyorum! Hangi meblağı yatırmak istersiniz?","Pekala. Bana güvenin, bu meblağ burada güvenle ve faiziyle birlikte sizi bekleyecek.","Bu hayatta gerçekten neyin önemli olduğunu bildiğinizi görüyorum. Ne kadar yatırım yapmak istersiniz?");
			link.l1.edit = 3;
			link.l1 = "";	
			Link.l1.go = "result";
		break;
		
		case "result":
			Pchar.QuestTemp.Deposits.(sDepositType1).Interest = GetDepositRate();
			Pchar.QuestTemp.Deposits.(sDepositType1).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = "Şaka yapıyorsun, öyle mi?";
				link.l1 = "Benim hatam.";
				link.l1.go = "exit";
				break;
			}
			if (iTemp > sti(pchar.money))
			{
				dialog.text = "Hm, maalesef o kadar paranız yok. Ciddileşelim...";
				link.l1 = "Pekâlâ.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Pekâlâ. Size sunabileceğim... diyelim ki..."+fts(stf(Pchar.QuestTemp.Deposits.(sDepositType1).Interest),1)+" %. Elbette, aylık olarak.";
			Link.l1 = "Benim için uygundur.";
			Link.l1.go = "Deposit_placed";
			Link.l2 = "Tutarı değiştirmem daha iyi olur.";
			Link.l2.go = "Deposit";
			Link.l3 = "Görünüşe bakılırsa bu kötü bir fikirdi... Elveda.";
			Link.l3.go = "Exit";
		break;

		case "Deposit_placed":
			Dialog.snd = "voice\USDI\USDI033";
			if ( !CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+".Result"))
			{
			    Pchar.Quest.Deposits.(sDepositType1).Result = 0;//fix
			}
			// boal limit
			if ( (sti(Pchar.Quest.Deposits.(sDepositType1).Result) + sti(Pchar.QuestTemp.Deposits.(sDepositType1).Sum)) > sti(NPChar.UsurerDeposit)*1000)
			{
			    dialog.text = "Affedersiniz kaptan, fakat bu miktar kolonimin bankası için fazla büyük. Size faiz ödemen mümkün olmayacak. Ayrıca güvenilir bir koruma da yok... Umarım beni anlarsınız. Her neyse, sizden kabul edebileceğim en yüksek miktar "+FindRussianMoneyString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*1000,MONEY_SIGN,MONEY_DELIVER))+".";
				Link.l1 = "Ne yazık ki, o zaman başka bir tefeci bulmam gerekecek.";
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = "Artık en şiddetli fırtına bile seni parasız bırakmaz, bundan emin olabilirsin.";
				Link.l1 = "Pekala. Görüşürüz.";
				Link.l1.go = "Deposit_Exit";
			}
		break;
		
		case "Deposit_return":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = "Vaat edilen faiz ve geçen süreyi göz önünde bulundurursak, size borcum "+FindRussianMoneyString(sti(Pchar.Quest.Deposits.(sDepositType1).Result))+"... Parayı almak istediğinizden emin misiniz?";
			Link.l1 = "Elbette. Verin bana.";			
			Link.l1.go = "Deposit_return_1";		
			Link.l2 = "Paramın bir kısmını almak istiyorum.";			
			Link.l2.go = "Deposit_return_part";
			Link.l3 = "Haklısınız. Bir süre sizde kalmasına izin vereceğim. İyi günler.";			
			Link.l3.go = "Exit";		
		break;		
		
		case "Deposit_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+ ".Rem"))
			{
				DeleteAttribute(Pchar,"Quest.Deposits." + (sDepositType1)+ ".Rem");
			}
			Pchar.Quest.Deposits.(sDepositType1).Interest = stf(Pchar.QuestTemp.Deposits.(sDepositType1).Interest);
			Pchar.Quest.Deposits.(sDepositType1).Sum      = sti(Pchar.QuestTemp.Deposits.(sDepositType1).Sum);
			Pchar.Quest.Deposits.(sDepositType1).city 	  = NPC_Area;	

			AddMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)));
			// общий долг
			Pchar.Quest.Deposits.(sDepositType1).Sum = sti(Pchar.Quest.Deposits.(sDepositType1).Result) + sti(Pchar.Quest.Deposits.(sDepositType1).Sum);
			Pchar.Quest.Deposits.(sDepositType1) = true;
			Pchar.Quest.Deposits.(sDepositType1).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType1).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType1).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType1).StartTime 	= getTime();
			DialogExit();
		break;
		
		//--> Jason забор денег по частям
		case "Deposit_return_part":
			dialog.text = "Ve ne kadar?";
			link.l1.edit = 4;
			link.l1 = "";	
			Link.l1.go = "result_part";
		break;

		case "result_part":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0)
			{
				dialog.text = "Bu gerçekten çok saçma bir şakaydı, efendim!";			
				link.l1 = "Lanet olsun! Çok üzgünüm... Hadi tutarı değiştirelim.";	
				Link.l1.go = "Deposit_return_part";
				break;
			}
			if (iTemp > sti(Pchar.Quest.Deposits.(sDepositType1).Result))
			{
				dialog.text = "Hesabınızda o kadar para yok.";			
				link.l1 = "Kahretsin! Benim hatam. Miktarı değiştirelim.";	
				Link.l1.go = "Deposit_return_part";
				break;
			}
			if (iTemp == sti(Pchar.Quest.Deposits.(sDepositType1).Result))
			{
				dialog.text = "Hepsi mi? Peki, nasıl isterseniz. İşte paranız.";			
				link.l1 = "Teşekkür ederim!";	
				Link.l1.go = "Deposit_return_all";
				break;
			}
			dialog.text = "Pekala. Al şunu. İşte paran.";			
			link.l1 = "Teşekkürler!";	
			Link.l1.go = "result_part_1";
		break;
		
		case "result_part_1":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			addMoneyToCharacter(Pchar, iTemp);
			iRes = sti(Pchar.Quest.Deposits.(sDepositType1).Result)-iTemp; //остаток на счете
			fPer = stf(Pchar.Quest.Deposits.(sDepositType1).Interest);
			iDep = sti(Pchar.Quest.Deposits.(sDepositType1).Sum); //стартовая сумма
			if (iRes <= sti(Pchar.Quest.Deposits.(sDepositType1).Sum)) // стало меньше начальной суммы
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
				Pchar.Quest.Deposits.(sDepositType1).Interest = fPer;
				Pchar.Quest.Deposits.(sDepositType1).Sum = iRes;
				Pchar.Quest.Deposits.(sDepositType1).Result = 0;
			}
			else // если остаток больше начальной суммы - проценты продолжаем считать с неё, а не с остатка, ибо нефиг, дельту приплюсуем к набежавшим процентам - банкир Jason :) 
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
				Pchar.Quest.Deposits.(sDepositType1).Interest = fPer;
				Pchar.Quest.Deposits.(sDepositType1).Sum = iDep;
				Pchar.Quest.Deposits.(sDepositType1).Rem = iRes-iDep;
			}
			Pchar.Quest.Deposits.(sDepositType1).city 	  	= NPC_Area;	
			Pchar.Quest.Deposits.(sDepositType1) 			= true;
			Pchar.Quest.Deposits.(sDepositType1).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType1).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType1).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType1).StartTime 	= getTime();
		break;
		
		case "Deposit_return_all":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			addMoneyToCharacter(Pchar, iTemp);
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
		break;
		//<-- забор денег по частям		
		
		case "Deposit_return_1":
			addMoneyToCharacter(Pchar, makeint(Pchar.Quest.Deposits.(sDepositType1).Result));
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Ah... Bunu kaybetmek çok zor. Bu paraya gerçekten alışmıştım. Yine de tekrar beklerim.";			
			Link.l1 = "Gerekirse yaparım. Hoşça kal.";			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
		break;
		
		//  ugeen -> вклады в дублонах	
		case "deposit_dub":
			dialog.text = LinkRandPhrase("Bilge birini görüyorum! Hangi meblağı yatırmak istersiniz?","Pekâlâ. Güvenin bana, bu miktar burada güvenle ve tüm faiziyle sizi bekliyor olacak.","Bu hayatta asıl önemli olanın ne olduğunu bildiğinizi görüyorum. Ne kadar yatırım yapmak istersiniz?");
			link.l1.edit = 3;
			link.l1 = "";	
			Link.l1.go = "result_dub";
		break;
		
		case "result_dub":		
			iTotalDublonQty = GetCharacterItem(pchar,"gold_dublon") + CheckItemMyCabin("gold_dublon");		
			Pchar.QuestTemp.Deposits.(sDepositType2).Interest = 1;
			Pchar.QuestTemp.Deposits.(sDepositType2).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = "Şaka mı yapıyorsun, ha?";
				link.l1 = "Hm, benim hatam...";
				link.l1.go = "exit";
				break;
			}						
			if (iTemp > iTotalDublonQty)
			{
				dialog.text = "Hm, maalesef o kadar paranız yok. Ciddileşelim...";
				link.l1 = "Hm... iyi.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Pekala. Sana sunabileceğim... diyelim ki..."+Pchar.QuestTemp.Deposits.(sDepositType2).Interest+" %. Elbette, aylık olarak.";
			Link.l1 = "Bana uyar.";
			Link.l1.go = "Deposit_placed_dub";
			Link.l2 = "Tutarı değiştirmem daha iyi olur.";
			Link.l2.go = "Deposit_dub";
			Link.l3 = "Sanırım altınımı saklamak daha iyi. Hoşça kal.";
			Link.l3.go = "Exit";
		break;
		
		case "Deposit_placed_dub":
			Dialog.snd = "voice\USDI\USDI033";
			if ( !CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+".Result"))
			{
			    Pchar.Quest.Deposits.(sDepositType2).Result = 0;//fix
			}
			// boal limit
			if ( (sti(Pchar.Quest.Deposits.(sDepositType2).Result) + sti(Pchar.QuestTemp.Deposits.(sDepositType2).Sum)) > sti(NPChar.UsurerDeposit)*10)
			{
			    dialog.text = "Affedersiniz kaptan, fakat bu miktar kolonimin bankası için fazla büyük. Size faiz ödemen mümkün olmayacak. Ayrıca güvenilir bir koruma eksikliği de var... Umarım beni anlarsınız. Her neyse, sizden kabul edebileceğim en yüksek miktar "+FindRussianDublonString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*10,MONEY_SIGN,MONEY_DELIVER))+".";
				Link.l1 = "Ne yazık ki, o zaman başka bir tefeci bulmam gerekecek.";
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = "Artık en şiddetli fırtına bile seni parasız bırakmaz, bundan emin olabilirsin.";
				Link.l1 = "Güzel. Hoşça kal.";
				Link.l1.go = "Deposit_Exit_dub";
			}
		break;
		
		case "Deposit_return_dub":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = "Vaat edilen faiz ve geçen süreyi göz önünde bulundurursak, size borcum "+FindRussianDublonString(sti(Pchar.Quest.Deposits.(sDepositType2).Result))+"... Parayı almak istediğinizden emin misiniz?";
			Link.l1 = "Elbette. Verin bana.";			
			Link.l1.go = "Deposit_return_dub_1";		
			Link.l2 = "Paramın bir kısmını almak istiyorum.";			
			Link.l2.go = "Deposit_return_dub_part";
			Link.l3 = "Haklısınız. Bir süre daha sizde kalmasına izin vereceğim. İyi günler.";			
			Link.l3.go = "Exit";		
		break;	

		case "Deposit_exit_dub":
			NextDiag.CurrentNode = NextDiag.TempNode;		
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+ ".Rem"))
			{
				DeleteAttribute(Pchar,"Quest.Deposits." + (sDepositType2)+ ".Rem");
			}	
			Pchar.Quest.Deposits.(sDepositType2).Interest = sti(Pchar.QuestTemp.Deposits.(sDepositType2).Interest);
			Pchar.Quest.Deposits.(sDepositType2).Sum      = sti(Pchar.QuestTemp.Deposits.(sDepositType2).Sum);
			Pchar.Quest.Deposits.(sDepositType2).city 	  = NPC_Area;	
			
			iTemp = GetCharacterItem(pchar,"gold_dublon");
			if(iTemp > sti(Pchar.Quest.Deposits.(sDepositType2).Sum))
			{
				TakeNItems(pchar,"gold_dublon", -sti(Pchar.Quest.Deposits.(sDepositType2).Sum));
			}
			else
			{
				TakeNItems(pchar,"gold_dublon", -iTemp));
				iTemp = sti(Pchar.Quest.Deposits.(sDepositType2).Sum) - iTemp;
				GetItemMyCabin("gold_dublon", iTemp);
			}
						
			// общий долг
			Pchar.Quest.Deposits.(sDepositType2).Sum = sti(Pchar.Quest.Deposits.(sDepositType2).Result) + sti(Pchar.Quest.Deposits.(sDepositType2).Sum);
			Pchar.Quest.Deposits.(sDepositType2) = true;
			Pchar.Quest.Deposits.(sDepositType2).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType2).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType2).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType2).StartTime 	= getTime();
			DialogExit();
		break;	
		
		//-->забор дублонов по частям
		case "Deposit_return_dub_part":
			dialog.text = "Ve ne kadar?";
			link.l1.edit = 4;
			link.l1 = "";	
			Link.l1.go = "result_dub_part";
		break;
		
		case "result_dub_part":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0)
			{
				dialog.text = "Böylesine saçma bir şaka, efendim!";			
				link.l1 = "Lanet olsun! Çok üzgünüm... Hadi miktarı değiştirelim...";	
				Link.l1.go = "Deposit_return_dub_part";
				break;
			}			
			if (iTemp > sti(Pchar.Quest.Deposits.(sDepositType2).Result))
			{
				dialog.text = "Hesabınızda o kadar altın yok, efendim.";			
				link.l1 = "Kahretsin! Benim hatam. Miktarı değiştirelim...";	
				Link.l1.go = "Deposit_return_dub_part";
				break;
			}			
			if (iTemp == sti(Pchar.Quest.Deposits.(sDepositType2).Result))
			{
				dialog.text = "Hepsi mi? Peki, nasıl isterseniz. İşte paranız.";			
				link.l1 = "Teşekkürler!";	
				Link.l1.go = "Deposit_return_dub_all";
				break;
			}
			dialog.text = "Pekâlâ. Al, işte paran.";			
			link.l1 = "Teşekkür ederim!";	
			Link.l1.go = "result_dub_part_1";
		break;
		
		case "result_dub_part_1":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			TakeNItems(pchar,"gold_dublon", iTemp);
			iRes = sti(Pchar.Quest.Deposits.(sDepositType2).Result)-iTemp; //остаток на счете
			iPer = sti(Pchar.Quest.Deposits.(sDepositType2).Interest);
			iDep = sti(Pchar.Quest.Deposits.(sDepositType2).Sum); //стартовая сумма
			if (iRes <= sti(Pchar.Quest.Deposits.(sDepositType2).Sum)) // стало меньше начальной суммы
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
				Pchar.Quest.Deposits.(sDepositType2).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType2).Sum = iRes;
				Pchar.Quest.Deposits.(sDepositType2).Result = 0;
			}
			else // если остаток больше начальной суммы - проценты продолжаем считать с неё, а не с остатка, ибо нефиг, дельту приплюсуем к набежавшим процентам - банкир Jason :) 
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
				Pchar.Quest.Deposits.(sDepositType2).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType2).Sum = iDep;
				Pchar.Quest.Deposits.(sDepositType2).Rem = iRes-iDep;
			}
			Pchar.Quest.Deposits.(sDepositType2).city 	  	= NPC_Area;	
			Pchar.Quest.Deposits.(sDepositType2) 			= true;
			Pchar.Quest.Deposits.(sDepositType2).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType2).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType2).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType2).StartTime 	= getTime();
		break;
		
		case "Deposit_return_dub_all":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			TakeNItems(pchar,"gold_dublon", iTemp);
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
		break;
		//<-- забор денег по частям		
		
		case "Deposit_return_dub_1":
			TakeNItems(pchar,"gold_dublon", sti(Pchar.Quest.Deposits.(sDepositType2).Result));
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Ah... Bunu kaybetmek gerçekten çok zor. Bu paraya alışmıştım. Yine de yine beklerim.";			
			Link.l1 = "Gerekirse yaparım. Hoşça kal.";			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
		break;
		//  ugeen <- вклады в дублонах	
		
		case "DeadMotherfucker":
			Dialog.TempNode = "DeadMotherFucker_1";
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Hâlâ hayatta mısın? Belki de paramı geri vermek istiyorsun? Kahrolası! O kadar çok para kaybettim ki, asla geri ödeyemezsin! Ve senin cansız bedenini görmeden huzur bulamayacağım!";
            Link.l1 = "Ben sadece işleri barışçıl bir şekilde çözmek istiyorum.";
			Link.l1.go = "LoanRestore_1";
			Link.l2 = LinkRandPhrase("Pekâlâ, o zaman görelim! Bil ki sen de ölümden güvende değilsin!","Bir tehdit mi?! O zaman bakalım ne yapacaksın...","Para hayatımızdaki en önemli şey değil. Bunun için fazla üzülme ve kimseyi öldürme. Hadi, seni meydan okumaya davet ediyorum.");
			Link.l2.go = "ExitDelLoan2";
		break;

		case "DeadMotherFucker_1":			
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Defol! Bir daha seni asla görmek istemiyorum.";			
			Link.l1 = "...";			
			Link.l1.go = "ExitDelLoan2";
            Dialog.TempNode = "DeadMotherFucker_1";
		break;
		// boal обратимость факапства -->
		case "LoanRestore_1":
            iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
			Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makefloat(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);
			dialog.text = "Gerçekten mi? Endişeleriniz neler?";
			Link.l1 = "Bugünlük, sana borçluyum "+FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result))+". Ve bu parayı size sunuyorum.";
			Link.l1.go = "DeadMotherFucker_1";
            if (sti(Pchar.Money) >= 2*sti(Pchar.Quest.Loans.(NPC_Area).Result))
            {
    			Link.l2 = "Sizinle iyi ilişkilerimizi yeniden kurmak için borcumu sunuyorum. Bu "+FindRussianMoneyString(2*sti(Pchar.Quest.Loans.(NPC_Area).Result))+".";
    			Link.l2.go = "LoanRestore_2";
			}
		break;
		
		case "LoanRestore_2":
			dialog.text = "İşte şimdi konuşuyoruz! Sonunda seninle iş yapabilirim.";
			Link.l1 = "Teşekkürler. Bir daha sizi hayal kırıklığına uğratmayacağım.";
			Link.l1.go = "ExitDelLoan2";
			NextDiag.TempNode = "First time";			
			addMoneyToCharacter(Pchar, -2*sti(Pchar.Quest.Loans.(NPC_Area).Result));
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area);
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			ChangeCharacterHunterScore(PChar, NationShortName(sti(NPChar.nation)) + "hunter", -30);
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
		break;

		case "ExitDelLoan1":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
		break;

		case "ExitDelLoan2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
			DeleteAttribute(Pchar, "quest.Deposits." + (NPC_Area));
		break;
		
        case "LoanGranted_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;

			AddMoneyToCharacter(Pchar, makeint(Pchar.Quest.Loans.(NPC_Area).Sum));
			Pchar.Quest.Loans.(NPC_Area) = true;
			Pchar.Quest.Loans.(NPC_Area).StartDay = getDataDay();
			Pchar.Quest.Loans.(NPC_Area).StartMonth = getDataMonth();
			Pchar.Quest.Loans.(NPC_Area).StartYear = getDataYear();
			Pchar.Quest.Loans.(NPC_Area).StartTime = getTime();

			sTemp = "Loans_" + NPC_Area;			
			SetTimerCondition(sTemp, 0, makeint(Pchar.Quest.Loans.(NPC_Area).Period), 0, false);
			pchar.quest.(sTemp).CityId = NPC_Area;
			pchar.quest.(sTemp).win_condition = "LoansForAll";
			
			DialogExit();
			npchar.quest.trade_date = lastspeak_date; // дыра с прокачкой была
		break;
        
		//работорговец
		int iSlaveMoney;
		int amount;
		case "GiveTaskSlave":
			pchar.questTemp.Slavetrader.iSlaveQuantity = 100;
			pchar.questTemp.Slavetrader.iSlaveMoney = sti(pchar.questTemp.Slavetrader.iSlaveQuantity) * 250;
			dialog.Text = "Ama hadi ama! Sen de ben de ciddi insanlarız, tek bir dublon için canını vermeye hazır olan şu aptallardan çok daha iyiyiz, ama o dublondan iki dublon çıkarmayı asla denemeyenlerden.\nCiddi bir iş teklif edebileceğim bir adam arıyorum. Cesur ve atak, dürüst ve dakik, ama... eh... ahlaki ikilemler konusunda fazla titiz olmayan biri. Umarım aradığım adam sensindir.";
			Link.l1 = "Bana ne tür bir 'anlaşma' sunacağınız bağlı olacak.";
			Link.l1.go = "GiveTaskSlave_1";
		break;
			
		case "GiveTaskSlave_1":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(npchar.city);
			dialog.Text = "Pekâlâ, o halde dinleyin. Kölelik şu sıralar Karayipler'deki en kârlı iş. Ben bir plantasyon sahibi değilim, ama güvenilir müşterilerim var\nYani, bana şu kadar köle lazım - "+pchar.questTemp.Slavetrader.iSlaveQuantity+" baş. Her biri için size 250 peso ödemeye hazırım. Bana güvenin, bu adil bir fiyat. Toplamda kazanacağınız miktar "+FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney))+".";
			Link.l1 = "Hayır, ben köle taciri değilim. Vicdanını görmezden gelmeyen başka bir yardımcı bul kendine.";
			Link.l1.go = "exit_slaves";
			Link.l2 = "Cazip bir teklif. Bunu yapmak isterim. Kölelere ne kadar çabuk ihtiyacınız var?";
			Link.l2.go = "GiveTaskSlave_2";
		break;
			
		case "exit_slaves":
			dialog.Text = "Eh, kimsenin altındaki altını almak için kılını kıpırdatmaya niyeti yok anlaşılan. Gerçekten hayal kırıklığına uğradım. Hoşça kal, ve sakın aramızdaki konuşmayı başkalarına anlatmaya kalkma. Kolum uzundur...";
			Link.l1 = "Uzanışın da, dilin kadar 'kirli'... Hoşça kal.";
			Link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
			DeleteAttribute(npchar, "quest.slave");
		break;
			
		case "GiveTaskSlave_2":
			dialog.Text = "Süreni sınırlamayacağım, ama görevi mümkün olduğunca çabuk tamamlamaya çalış. 'Kara fildişi'ne olan talep çok büyük. İşini iyi yaparsan, gelecekte de sana bu tür işler vereceğim.";
			Link.l1 = "Kulağa hoş geliyor. Pekâlâ, iyi haberleri bekle.";
			Link.l1.go = "exit";						
			pchar.questTemp.Slavetrader = "Seek_slaves"; // это ввод имени квеста и состояния квеста
			AddQuestRecord("Slavetrader", "1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("Slavetrader", "sQty", makeint(pchar.questTemp.Slavetrader.iSlaveQuantity));
			AddQuestUserData("Slavetrader", "sSum", makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			LAi_LocationDisableOfficersGen(&Locations[FindLocation(pchar.location)], true); // блокируем вход офицеров 2015
		break;
			
		case "Checkslaves":
			amount = GetSquadronGoods(Pchar, GOOD_SLAVES) - sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = "O 'siyah fildişi' sevkiyatını temin etmeyi başardınız mı?";
            if (amount < 0)
			{
				Link.l1 = "Henüz değil. Sadece anlaşmamızın hâlâ geçerli olup olmadığını kontrol ediyorum.";
            	Link.l1.go = "exit";
			}
			else
			{
				Link.l1 = "Var. Hepsi yükümde.";
            	Link.l1.go = "Takeslaves";
			}
		break;
		
		case "Takeslaves":
			amount = sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = "Harika. Adamlarım onları alacak... Gümrük ya da kalenin komutanı konusunda endişelenme. Burada büyük bir operasyon yürütüyorum, o yüzden sorun bekleme ve kimse seni kaçakçılıkla suçlamayacak.";
			Link.l1 = "Burada güçlü bir konum elde etmişsiniz... Peki ya benim ödemem ne olacak?";
            Link.l1.go = "Takeslaves_1";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, amount);
		break;
		
		case "Takeslaves_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.Text = "İşte burada. Boş konuşmam ben. Benimle kal kaptan, yakında o kadar çok altının olacak ki taşımak için bir kalyona ihtiyacın olacak!";
			Link.l1 = "Harika olurdu, ha-ha... Sırada ne var?";
            Link.l1.go = "Takeslaves_2";
		break;
		
		case "Takeslaves_2":
			dialog.Text = "Sıradaki? Üç hafta sonra tekrar gelin. Şu anda bir anlaşma üzerinde çalışıyorum, o zamana kadar hazır olur.";
			Link.l1 = "Pekâlâ, anlaştık. Hoşça kal.";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "2");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "wait";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait");//запомнить дату
		break;
		
		case "Takeslaves_3":
			if (4-sti(RealShips[sti(pchar.ship.type)].Class) < 0)//проверка класса корабля
			{
				dialog.Text = "Sana bir işim var, ama gemin çok zayıf. Görevi başaramamanı istemem, seni ölüme göndermek de niyetim değil. Hâlâ zamanın var, kendine daha büyük bir gemi bul, en azından bir barkantin, brigantin, brig veya flüt gibi. Zaman kaybetme!";
				Link.l1 = "Anladım, hallederim. Görüşürüz.";
            	Link.l1.go = "Takeslaves_3_smallship";
			}
			else
			{
				dialog.Text = "Nihayet! Sizi bekliyordum. Şimdi doğrudan konuya gelelim. Bildiğiniz gibi, her işte rakipler olur... ve benim de var. Bu açgözlü ve vicdansız herifler, her zaman bir müşterimi kapmak için can atıyorlar! Aslında, onlardan birini ortadan kaldırmak ve aynı zamanda iyi bir para kazanmak istiyorum.";
				Link.l1 = "Tamamen sizi dinliyorum.";
            	Link.l1.go = "Takeslaves_4";
			}
		break;
		
		case "Takeslaves_3_smallship":
			pchar.questTemp.Slavetrader = "waitship";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Takeslaves_4":
			Slavetrader_GetRandomShore();//выбор бухты
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Harika. Şimdi dinle. Bu serseri denen "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+", Afrika'dan köleler getirdi ve demir attı "+XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore+"Gen")+",   bir adada, adı da  "+XI_ConvertString(pchar.questTemp.Slavetrader.Island)+". Orada kaçakçıları bekliyor. Galyonunun adı '"+pchar.questTemp.Slavetrader.ShipName+" . Her ne pahasına olursa olsun, onların anlaşması bozulmalı!";
			link.l1 = "Ya köleler ne olacak? Onları batırmak büyük israf olurdu!";
			link.l1.go = "Takeslaves_5";
		break;
		
		case "Takeslaves_5":
			dialog.Text = "Neden böyle bir şey yapasınız ki? Buna hiç gerek yok. "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+" Kötü bir şöhreti var ve ortadan kaybolmasına kimse üzülmeyecek. Galyonuna çık, adamı öldür ve öldüğünden emin ol, yükü bana getir, ben de onu satarım. Kaynaklarıma göre, yaklaşık bin beş yüz köle var.";
			Link.l1 = "Vay canına. Bu gerçekten büyük bir rakam. Peki ya benim ödemem?";
            Link.l1.go = "Takeslaves_6";
			Link.l2 = "Hayır efendim, bu entrikalar bana göre değil. Neden kaçakçılarla olan ilişkilerimi bozayım ki?";
            Link.l2.go = "exit_slaves_1";
		break;
		
		case "exit_slaves_1":
			dialog.Text = "Pekâlâ... Görünen o ki, senin hakkında yanılmışım... Elveda, ve aramızdaki konuşmayı unut. Burada duyduklarını da kimseye anlatma. Bu kasaba bana ait. Ve eğer ' gemisine çıkmayı düşünüyorsan..."+pchar.questTemp.Slavetrader.ShipName+" kendin için... Seni darağacında görmekten emin olacağım. Bunu bir düşün.";
			Link.l1 = "Endişelenmeyin, sizi yetkililere şikayet etmeyeceğim ve geminize de ihtiyacım yok. Elveda.";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase(" agreed"," agreed"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";//конец квеста
		break;
		
		case "Takeslaves_6":
			dialog.Text = "Sana yükün yerini verdiğimi ve 'bir ganimet' aramak için denize açılmana gerek olmadığını düşünürsek, ödeme biraz daha düşük – kafa başı 200 peso. Yine de bu büyük bir meblağ – başarılı olursan ve gemiyi de alırsan toplam üç yüz bin peso.";
			Link.l1 = "Anlaştık. Ne kadar sürem var?";
            Link.l1.go = "Takeslaves_7";
			Link.l2 = "Ho-ho! Bunu sanki o köleler kendi istekleriyle gemime yüzüp, bir an önce yükümde yer almak istermiş gibi söylüyorsun! Adamlarımın böyle cüzi bir meblağ için hayatlarını riske atmasını gerçekten bekliyor musun? Ödülümü artır yoksa bu işten çekiliyorum.";
            Link.l2.go = "exit_slaves_1";
		break;
		
		case "Takeslaves_7":
			dialog.text = "İki haftan var. Sakın geç kalma, yoksa yükünü başkasına devreder ve her şey biter.";
			link.l1 = "O halde acele etmem gerekecek. İyi haberlerle döneceğim.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "3");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sShoreName", XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("Slavetrader", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetrader.Island) + "Voc")); // belamour gen
			pchar.quest.Slavetrader_ShipsAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_ShipsAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;
            pchar.quest.Slavetrader_ShipsAttack.function = "Slavetrader_CreateSlaveShips";//создание кораблей
			SetFunctionTimerCondition("Slavetrader_SlaveShipsOver", 0, 0, 15, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//это заглушка
		break;
		
		case "Takeslaves_4_lose":
			dialog.text = "Pekâlâ, "+GetFullName(pchar)+", peki ya görevimiz? Suratındaki o karamsar ifade görevi başaramadığını söylüyor.";
			link.l1 = "Lanet olsun, haklısın... Ben... şey, biliyorsun... geç kaldım. Görünüşe göre o zaten oradan ayrılmıştı, çünkü orada kimseyi bulamadım. Tüm yolu rüzgarla gitmek zorunda kaldım, kahretsin... ";
			link.l1.go = "Takeslaves_5_lose";
		break;
		
		case "Takeslaves_4_win":
			dialog.text = "Pekâlâ, "+GetFullName(pchar)+", bugün ne avladın? Bana söylediler ki "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+" balıkları besliyor! Ha-ha-ha!";
			link.l1 = "Evet, tam zamanında yetiştim! "+GetName(NAMETYPE_ORIG,pchar.questTemp.Slavetrader.UnknownPirateName,NAME_NOM)+" köleleri kaçakçı gemisine aktarıyordu. İkisine de çıkmak zorunda kaldım ve onları bizzat Davy Jones'un yanına gönderdim, artık daha az rakibin var.";
			link.l1.go = "Takeslaves_5_win";
		break;
		
		case "Takeslaves_5_lose":
			dialog.text = "Evet, sanırım senin hakkında yanılmışım. Geç mi kaldın? Yoksa dövüşmekten mi korktun? Her neyse. Artık hiçbir önemi yok. Kaybol. Seninle işim bitti. Burada gördüğün ya da duyduğun her şeyi unut.";
			link.l1 = "Öyleyse hoşça kal.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "5_5");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
		
		case "Takeslaves_5_win":
			pchar.questTemp.Slavetrader.Nation = npchar.nation;
			amount = 1600 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			if (amount < 0)
			{
				dialog.text = "Senin hakkında haklıymışım - "+GetSexPhrase(" sen alımlı bir serserisin"," sen vahşi bir genç kızsın")+"! Senin gibi adamlara ihtiyacım var. Görevini en mükemmel şekilde yerine getirdin – bin beş yüzden fazla köle getirdin! Ne yazık ki, sana sadece bin altı yüz köle için ödeme yapabilirim. Geri kalanı için yeterli param yok, onları kendin satmak zorunda kalacaksın. Ödülün 320.000 peso.";
				link.l1 = "Teşekkür ederim. Sizinle iş yapmak bir zevkti, "+npchar.name+"!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, 320000);
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, 1600);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", 1600);
				AddQuestUserData("Slavetrader", "sMoney", 320000);
				break;
			}
			if (amount >= 0 && amount < 200)
			{
				dialog.text = "Senin hakkında haklıymışım - "+GetSexPhrase(" sen tam bir çapkın serserisin"," sen cesur bir genç kızsın")+"! Senin gibi adamlara ihtiyacım var. Görevini en mükemmel şekilde yerine getirdin - bana getirdin "+sTemp+" köleler. Ödülünüz ise "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "Teşekkür ederim. Sizinle iş yapmak bir zevkti, "+npchar.name+"!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 200 && amount < 600)
			{
				dialog.text = "En azından en zor durumdan onurunla çıktın. Ödül beklediğimden az olsa da, yine de memnunum. Getirdin "+sTemp+" köleler. Ödülünüz ise "+FindRussianMoneyString(iSlaveMoney)+"";
				link.l1 = "Teşekkür ederim. Sizinle iş yapmak bir zevkti, "+npchar.name+"!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = "Anlıyorum... Bunu anlayabilirim, fakat çok daha fazlasını bekliyordum. Sadece getirdiğiniz şey bu mu? "+sTemp+" köleler. En azından rakiplerimi ortadan kaldırdın, bu da bir şeydir. Ödülün ise  "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "Teşekkür ederim. Anlayışınız için minnettarım. "+npchar.name+"!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 1100 && amount < 1600)
			{
				dialog.text = "Kulağa hoş geliyor, ama... hmm. Sanırım senin hakkında yanılmışım. Ne getirdin? "+sTemp+" köleler mi? Peki ya geri kalanı? Sakın bana onları batırdığını söyleme. Eminim onları kaçakçılara sattın, ya da daha da kötüsü – o alçak Lavoisier'ye. Defol git, artık seninle hiçbir işim olmak istemiyor!";
				link.l1 = "Dediğiniz gibi, hoşça kalın.";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "Kulağa hoş geliyor ama... kölelerimiz nerede? Yükümüz nerede? Sakın bana batırdığını söyleme. Kesin kaçakçılara ya da, daha kötüsü, o alçak Lavoisier'ye sattın. Defol git, seninle işim bitti.";
			link.l1 = "Dediğiniz gibi, hoşça kalın.";
			link.l1.go = "node_hanter_1";
		break;
		
		case "node_hanter_1":
			dialog.text = "Bu iş burada bitmedi. Kimse beni kandırmaya cesaret edemez! Ve senin bu girişiminin bedelini ödeyeceksin – başına dert açacağım. Şimdi defol buradan!";
			link.l1 = "Seninle ve köle ticaretinle cehenneme! Seni olduğun yerde biçmeliyim, ama ben senin asla olamayacağın kadar iyi bir adamım.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 30);
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Takeslaves_6_win":
			dialog.text = "Birlikte iyi çalışıyor gibiyiz, "+pchar.name+". Çok memnun oldum. Bir ay sonra tekrar gel, belki sana özel bir iş bulabilirim. Zaten aklımda birkaç fikir var.";
			link.l1 = "Elbette, bir ay sonra görüşürüz. Sizinle çalışmak oldukça kârlı.";
			link.l1.go = "Takeslaves_7_win";
		break;
			
		case "Takeslaves_7_win":
			dialog.text = "Sana bir servet kazandıracak... Son bir soru, "+pchar.name+", geminin kamarasında olağanüstü bir şey buldun mu?";
			link.l1 = "Pek bir şey yok aslında... Bir şeyi kaçırdım mı?";
			link.l1.go = "Nostatue";
			if (CheckCharacterItem(pchar, "talisman8"))
			{
				link.l2 = "Şu eski toka mı, bir 'akrep' muskası mı diyorsun?";
				link.l2.go = "Yestatue";
			}
		break;
			
		case "Nostatue":
			dialog.text = "Belki yaptınız, belki yapmadınız ... Artık önemi yok. Bir ay sonra görüşürüz. Hoşça kalın!";
			link.l1 = "Görüşürüz, "+npchar.name+".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Yestatue":
			dialog.text = "Kesinlikle! Bu bir Medici fibulası... onlardan hiç duydunuz mu? Demek ki gerçekten o alçağın kamarasındaymış... Bakabilir miyim?";
			link.l1 = "Tabii, al.";
			link.l1.go = "Yestatue_1";
			RemoveItems(PChar, "talisman8", 1);
		break;
			
		case "Yestatue_1":
			Log_Info("You gave a talisman");
			PlaySound("interface\important_item.wav");
			dialog.text = "Bak, bak... Gerçekten de öyle. Dinle, "+pchar.name+", bana satın. Yüz bin peso ödemeye hazırım.";
			link.l1 = "Yüz bin mi? Hm... Kabul ediyorum. Buyurun!";
			link.l1.go = "Buystatue";
			link.l2 = "Hayır, satmayacağım. Bu fibulanın gerçek değeri ne gümüşle ne de altınla ölçülebilir. Böyle şeylerin nasıl işlediğini bilirim.";
			link.l2.go = "Nobuystatue";
		break;
			
		case "Buystatue":
			dialog.text = "Mükemmel! Anlaştığımıza sevindim. Alın paranızı. Bir ay sonra sizi tekrar görmeyi dört gözle bekliyorum.";
			link.l1 = "Elveda, "+npchar.name+".";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 100000);
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Nobuystatue":
			dialog.text = "You see, I desperately need this fibula! I completely agree with you, it can't be valued in money; any foolish merchant wouldn't even pay you five thousand for it. But it seems you truly understand its worth, since you refuse to sell it for such a sum.\n May I offer you a trade, if you don't want money? I have something you might find interesting. Here, take a look. Remarkable light armour! See for yourself! I offer it to you in exchange for the fibula.\nIt is not unique, by the way. You sailors can always find more for yourselves, but I cannot. Do you agree now?";
			link.l1 = "Heh... Sanırım öyle. Zırhı ver ve şu fibulayı al.";
			link.l1.go = "Nobuystatue_yes";
			link.l2 = "Hayır, bu fibula benim için bu zırhtan çok daha değerli. Onu kendime saklayacağım.";
			link.l2.go = "Nobuystatue_no";
		break;
			
		case "Nobuystatue_yes":
			dialog.text = "Harika! Anlaştığımıza sevindim. Bu zırh artık senin. Al bunu. Bir ay sonra görüşürüz. Hoşça kal.";
			link.l1 = "Görüşürüz, "+npchar.name+".";
			link.l1.go = "exit";
			TakeNItems(pchar, "cirass7", 1);
			Log_Info("You have received a Brigandine");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Nobuystatue_no":
			dialog.text = "Ne yazık... Gerçekten kötü. Peki, al bakalım. Seni yargılamayacağım. Bir ay sonra görüşürüz. Hoşça kal.";
			link.l1 = "Elveda.";
			link.l1.go = "exit";
			TakeNItems(pchar, "talisman8", 1);
			Log_Info("You have received a talisman");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "EscapeSlave":
			dialog.text = "Tam zamanında geldiniz, "+pchar.name+". Sizin için bir görevim var, eğer başlamaya hazırsanız.";
			link.l1 = "Elbette, hazırım.";
			link.l1.go = "EscapeSlave_1";
		break;
			
		case "EscapeSlave_1":
			dialog.text = "Mükemmel! Şimdi, doğrudan konuya gelelim. Son haberleri duydunuz mu?";
			link.l1 = "Hm, ne demek istiyorsunuz? Her gün birçok haber geliyor.";
			link.l1.go = "EscapeSlave_2";
		break;
			
		case "EscapeSlave_2":
			dialog.text = "Bu tamamen işimizle ilgili. Yeni Dünya'nın tarihinde eşi benzeri görülmemiş bir köle kaçışı yaşandı! Binlerce insan kaçmayı başardı ve bu arada Hollanda'nın birkaç karakolunu yakıp yıktılar.";
			link.l1 = "İlginç. Devam edin.";
			link.l1.go = "EscapeSlave_3";
		break;
			
		case "EscapeSlave_3":
			dialog.text = "Ama sadece kaçmakla kalmadılar, bir şekilde adadan ayrılmayı da başardılar! Hiçbir iz bırakmamışlar. Mathias Beck öfkeden deliye dönmüş durumda. Ama mesele bu değil... Asıl mesele şu ki, sizden Curacao'ya gitmenizi, orada ne olduğunu öğrenmenizi, kaçakların izini bulup onları yakalamanızı istiyorum\nVe tabii ki, onları Hollanda adaletinin ellerinden kurtarmanızı; çünkü onlara hiç acımazlardı. Kişi başı 300 peso ödeyeceğim – iyi köle olduklarını duydum.";
			link.l1 = "Anladım. Curaçao'ya gidiyorum. Beni iyi haberlerle bekle.";
			link.l1.go = "EscapeSlave_yes";
			link.l2 = "Biliyor musun, bu görevi kabul etmeyeceğim. İnsanların özgürlüğünü ellerinden alamam. Onlar bunu kazanmak için hayatlarını riske attılar. Özgürlüklerini hak ettiler.";
			link.l2.go = "EscapeSlave_no";
		break;
			
		case "EscapeSlave_no":
			dialog.text = "Ne yazık... Bunu senden beklemezdim... hem de en uygunsuz zamanda. Sanırım ortaklığımızın sona erdiği artık sana da açık. Elveda.";
			link.l1 = "İyi günler.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "EscapeSlave_yes":
			Slavetrader_GetEscapeShore();
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(HOLLAND);
			pchar.questTemp.Slavetrader = "EscapeSlave_Villemstad";
			AddQuestRecord("Slavetrader", "22_1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			DialogExit();
		break;
			
		case "Escape_slaves_win":
			int iSlaveMoneyH;
			string sNum;
			amount = 1100 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*300;
			sNum = GetSquadronGoods(Pchar, GOOD_SLAVES) - 1100;
			iSlaveMoneyH = makeint(sNum)*100;
			if (amount < 0)
			{
				dialog.text = "Ha! Zorlu görevinin üstesinden gelmekle kalmamışsın, üstelik istediğimden de fazla köle getirmişsin - "+sTemp+" köleler. Ama "+sNum+" köleler Curacao'dan kaçmadı. Her biri için sana 100 peso ödeyeceğim. Sanırım bu senin için uygundur. Ödülün 330.000 peso ve "+FindRussianMoneyString(iSlaveMoneyH)+" fazlası için, ha-ha.";
				link.l1 = "Ha! Sizi kandırmak mümkün değil, kesinlikle. Kabul ediyorum, ne derseniz o olsun. "+npchar.name+"!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, 330000);
				AddMoneyToCharacter(pchar, makeint(iSlaveMoneyH));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_5");
				AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoneyH));
				break;
			}
			if (amount < 101 && amount >= 0)
			{
				dialog.text = "O zorlu görevi en mükemmel şekilde tamamladınız ve bana getirdiniz "+sTemp+" köleler. Ödülünüz ise "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "Teşekkür ederim. Sizinle iş yapmak bir zevkti, "+npchar.name+"!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 100 && amount < 600)
			{
				dialog.text = "Bu zorlu görevi başardınız. Ödül beklediğim kadar büyük değil, ama yine de memnunum. Yani onu buraya getirdiniz "+sTemp+" köleler. Ödülünüz ise "+FindRussianMoneyString(iSlaveMoney)+".";
				link.l1 = "Teşekkürler. Sizinle iş yapmak bir zevkti, "+npchar.name+"!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = "Onları buldunuz mu? Hm... bana ne getirdiniz?"+sTemp+" Köleler mi? Geri kalan yük nerede? Sakın bana batırdığını söylemeye kalkma. Kesin kaçakçılara sattın, ya da daha kötüsü - Isla-Tesoro'dan o alçak Lavoisier'ye verdin. Defol buradan, artık seninle çalışmak istemiyorum.";
				link.l1 = "Hoşça kal.";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "Buldun mu? Peki ya köleler? Yükümüz nerede? Sakın bana batırdığını söylemeye kalkma. Kesin kaçakçılara sattın ya da daha kötüsü, Isla-Tesoro'dan o alçak Lavoisier'ye verdin. Defol buradan, artık seninle çalışmak istemiyorum.";
			link.l1 = "Elveda.";
			link.l1.go = "node_hanter_1";
		break;
		
		case "Escape_slaves_win_1":
			dialog.text = "Sana gerçekten minnettarım, "+pchar.name+". Gerçekten. Bir ay sonra tekrar gelin, ikimiz için de kârlı yeni bir iş hazırlayacağım.";
			link.l1 = "Ben de ortaklığımızdan memnunum, "+npchar.name+". Bir ay sonra görüşürüz.";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_2");
			pchar.questTemp.Slavetrader = "wait_2";
		break;
			
		case "Slaveshore":
			dialog.text = "Tam zamanında geldiniz, "+pchar.name+". Cesur ve gözü pek bir denizci arıyorum, ha-ha. Benim işimi üstlenmeye hazır mısın?";
			link.l1 = "Tamamen sizi dinliyorum.";
			link.l1.go = "Slaveshore_1";
		break;
			
		case "Slaveshore_1":
			pchar.questTemp.Slavetrader.Island = Islands[GetCharacterCurrentIsland(pchar)].id;
			pchar.questTemp.Slavetrader.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.Slavetrader.Island);
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = "Bu sefer oldukça basit. Bugün bir pinas "+pchar.questTemp.Slavetrader.ShipName+"'   bayrağı   altında "+NationNameGenitive(sti(npchar.nation))+"  demir attı  "+XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore+"Gen")+" koyunda. Yerel kaçakçıların yardımıyla büyük bir 'abanoz' yüküyle doldurulmuştu. Tam iki bin kafa, azı değil\nMürettebatta asker yok, kaptan da bir tüccar. Yani hiçbir tehdit yok. Gemiyi ele geçir ve yükü bana getir. Her kafa için her zamanki gibi 200 peso.";
			link.l1 = "Hm... Bu, önceki işten farklı. Kendi ulusunun gemisine saldırmamı öneriyorsun!";
			link.l1.go = "Slaveshore_2";
		break;
			
		case "Slaveshore_2":
			dialog.text = "Anlamıyorum, "+pchar.name+"Gemi bayrağının önemi var mı? Gerçekten umurunuzda mı bu?";
			link.l1 = "Öyle mi? Hayır, umurumda bile değil, altının milliyeti olmaz. Sadece biraz beklenmedikti...";
			link.l1.go = "Slaveshore_3_yes";
			link.l2 = "Umurumda. Sahip olmak istemiyorum "+NationNameAblative(sti(npchar.nation))+" düşmanlarım arasında.";
			link.l2.go = "Slaveshore_3_no";
		break;
			
		case "Slaveshore_3_no":
			dialog.text = "Ciddi misiniz? Şaka yapıyor olmalısınız, bu devirde kimseye güvenilmez... O halde, defolun. Ve burada gördüğünüz ya da duyduğunuz her şeyi unutun!";
			link.l1 = "Görüşürüz,"+npchar.name+".";
			link.l1.go = "node_hanter_1";
		break;
			
		case "Slaveshore_3_yes":
			dialog.text = "Neden şaşırdınız? Sikkelerin milliyeti umurumda değil diye mi? Emin olun, gerçekten de umurumda değil. Açıkçası, bir bankacı için vatanseverlik iyi bir şey değildir, tabii bir gün iflas etmek istemiyorsa\nAma felsefeyi bir kenara bırakalım. Sadede gelelim - gemi burada gece yarısına kadar kalacak, yani fazla vaktiniz yok. Devam etmeye hazır mısınız?";
			link.l1 = "Evet, "+npchar.name+", yoldayım.";
			link.l1.go = "Slaveshore_4";
		break;
			
		case "Slaveshore_4":
			dialog.text = "Harika. Görevimizde başarılı olacağınızdan hiç şüphem yok. Bol şans."+pchar.name+".";
			link.l1 = "Teşekkür ederim! Hoşça kalın.";
			link.l1.go = "exit";
            AddQuestRecord("Slavetrader", "10");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShip", pchar.questTemp.Slavetrader.ShipName);
			pchar.quest.Slavetrader_ShoreAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_ShoreAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;//отправляем в локацию
            pchar.quest.Slavetrader_ShoreAttack.function = "Slavetrader_CreateShoreShips";//создание кораблей
			SetFunctionTimerCondition("Slavetrader_ShoreShipsOver", 0, 0, 1, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//заглушка
		break;
			
		case "Pinas_lose":
		dialog.text = "Pekâlâ, "+GetFullName(pchar)+", peki ya göreviniz? Kederli yüzünüzden başarısız olduğunuzu anlıyorum.";
			link.l1 = "Kesinlikle haklısın... Ben... Yani... Çok geç kaldım. Meyhanedeydim, denize açıldığımda ortalıkta kimse yoktu.";
			link.l1.go = "Takeslaves_5_lose";
		break;
			
		case "Slaveshore_5":
			dialog.text = ""+pchar.name+", lütfen sakin olun. Benim suçum değil! Kahretsin, raporu çok geç aldım... İhanet vardı! Güvendiğim adamlardan biri beni sattı!";
			link.l1 = "Pekâlâ, doğruyu söylediğini görüyorum. Şanslısın ki, pinasın kaptanı bana 'işimizin' ortaya çıktığını söyledi. Eğer o geveze olmasaydı, seni çoktan öldürmüştüm. Ama sen, şu lanet para torbası, bunca zamandır bana durmadan bu kasabanın sahibi olduğunu söylüyordun!";
			link.l1.go = "Slaveshore_6";
		break;
			
		case "Slaveshore_6":
			dialog.text = "Pusu yerel yetkililer tarafından düzenlenmemiş, yoksa haberim olurdu... "+pchar.name+", this is not the right time for quarrels. Both of us are in danger; one of my former contractors has set us up\nI managed to find out that all the gathered evidence—a package of papers—is being transported to our governor-general. If he gets them, we are finished! You, by the way, will suffer the most.";
			link.l1 = "Şimdi o alçak kaptanın ne demek istediğini anladım!";
			link.l1.go = "Slaveshore_7";
		break;
			
		case "Slaveshore_7": //выбор острова, куда бригантина пойдёт
			switch (sti(NPChar.nation))
            {
                case HOLLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Curacao";
                break;
                case FRANCE :
					pchar.questTemp.Slavetraderbrig.Island = "Nevis";
                break;
                case SPAIN :
					pchar.questTemp.Slavetraderbrig.Island = "Cuba2";  
                break;
                case ENGLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Jamaica";     
                break;
			}
			pchar.questTemp.Slavetraderbrig.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));//имя бригантины
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = "Dikkatlice dinle. Hâlâ bir şansımız var. Paket, ' adlı brigantinle gönderildi."+pchar.questTemp.Slavetraderbrig.ShipName+". Bundan başka hiçbir şeyden emin değilim. Belgeler vali-generale konutunda teslim ediliyor "+XI_ConvertString(pchar.questTemp.Slavetraderbrig.Island)+". Onu yakalayıp, gemiye çıkmalı ve o suçlayıcı kanıtı bulmalısınız.";
			link.l1 = "Burada fazla seçeneğim yok. Benim için, kendin için dua et ve um ki bunu yakalayabileyim. Döndüğümde bütün bunları tekrar konuşacağız. Bunu öylece bırakacağımı sanma.";
			link.l1.go = "Slaveshore_8";
			AddQuestRecord("Slavetrader", "14");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetraderbrig.ShipName);
			AddQuestUserData("Slavetrader", "sIsland", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetraderbrig.Island)));
			pchar.quest.Slavetrader_BrigAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_BrigAttack.win_condition.l1.location = pchar.questTemp.Slavetraderbrig.Island;//отправляем в локацию
            pchar.quest.Slavetrader_BrigAttack.function = "Slavetrader_CreateBrig";//создание бригантины
			SetFunctionTimerCondition("Slavetrader_BrigOver", 0, 0, 15, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//это нода ожидания, пустая
		break;
		
		case "Slaveshore_8":
			dialog.text = "Bu paketi almak senin en önemli önceliğin! Onu bana teslim etmeden kendimi güvende hissetmeyeceğim... Kahretsin..."+pchar.name+", burada bir sorunla karşı karşıyayız gibi görünüyor...";
			link.l1 = "Ne var?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_enterSoldiers");
			break;
			
		case "Brig_lose":
			dialog.text = "Lanet olsun... Sana güveniyordum. "+pchar.name+". Peki öyle. Ama bundan sonra artık iş yapmayacağız. Soruşturmacıyı rüşvetle kandıramazsam kaçmak zorunda kalacağım. Sana da burada kalmanı tavsiye etmem – askerler her an gelebilir. Elveda.";
			link.l1 = "Elveda, "+npchar.name+".";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Letter_lose":
			dialog.text = "Onlardaydılar. Eh, artık birlikte iş yapamayız, güvenli değil. Elveda.";
			link.l1 = "Elveda, "+npchar.name+".";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Brig_win":
			dialog.text = "Mükemmel! Senden hiç şüphem yoktu, "+pchar.name+". Lütfen o evrakları verin, çok gerginim.";
			link.l1 = "Al onları.";
			link.l1.go = "Brig_win_1";
		break;
			
		case "Brig_win_1":
			RemoveItems(PChar, "letter_1", 1);
			dialog.text = "Güzel... Şimdi güvendeyim. Genel vali hiçbir şey öğrenmeyecek ve yerel yetkililerle ilgili tüm sorunları çoktan hallettim, ama sana söyleyeyim, bu bana pahalıya patladı.";
			link.l1 = "Kulağa hoş geliyor, ama düşüncesizce yaptıkların yüzünden çektiğim sıkıntılar için bana bir karşılık vermen gerekmiyor mu sence?";
			link.l1.go = "Brig_win_2";
		break;
			
		case "Brig_win_2":
			dialog.text = "Elbette, "+pchar.name+". Dahası, size çok şey borçluyum. Ve işlerimizi sürdürmeyi gerçekten umuyorum. Ancak beni anlamanızı rica ediyorum – bir servet harcadım – valiyle komutanın sadakati hiç de ucuz değil. Üstelik bankamda bütün devriyenin öldürülmesiyle de uğraşmak zorunda kaldım...";
			link.l1 = "Yani masraflarımı karşılamayacak mısınız?!";
			link.l1.go = "Brig_win_3";
		break;
			
		case "Brig_win_3":
			dialog.text = "Bukadar sert olma, "+pchar.name+"Şu anda gerçekten maddi sıkıntıdayım, bu yüzden sana farklı bir ödeme şekli teklif ediyorum.";
			link.l1 = "Sizi dinliyorum o halde.";
			link.l1.go = "Brig_win_4";
		break;
			
		case "Brig_win_4":
			dialog.text = "My companion and I were caught in a storm near the southern shores of the Main a year ago. Our ships were thrown onto the rocks of the Boca de la Serpienta coast; although they soon sank, we managed to drag our cargo ashore. Chests filled with precious stones and jewellery. The bay seemed quite cosy, so we hid the treasures without any trouble\nBut we were attacked by the Indians the next morning as soon as the storm had ended. That's how most of the survivors died, including my companion. A few sailors and I managed to escape on a longboat\nWe reached Cumana safely, yet I didn't dare return for the treasures. I am sure the local savages are still guarding their shore, along with my chests. But you can deal with that band of redskins\nThe jewellery you'll find there is more than enough to cover all your expenses, including an expedition to the southern Main.";
			link.l1 = "Hm... peki. O zaman Cumana'ya gidiyorum";
			link.l1.go = "Brig_win_5";
		break;
			
		case "Brig_win_5":
			dialog.text = "Emin olabilirsiniz, "+pchar.name+", söylediklerimin hepsi doğru. Bir ay içinde seni tekrar görmeyi bekliyorum. Zaten aklımda başka bir anlaşma var ve zor durumdaki işime nasıl yardımcı olabileceğimi düşünüyorum. Hoşça kal.";
			link.l1 = "Görüşürüz, "+npchar.name+".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_3");
			pchar.questTemp.Slavetrader = "wait_3";
			Pchar.quest.Slavetrader_Bonanza.win_condition.l1 = "location";
            Pchar.quest.Slavetrader_Bonanza.win_condition.l1.location = "Shore18";
            Pchar.quest.Slavetrader_Bonanza.function = "Slavetrader_Bonanza";
		break;
			
		case "SlaveGalleon":
			dialog.text = "Ve işte buradasınız, "+pchar.name+". Güzel, her zamanki gibi tam zamanında geldiniz. Bir sonraki görevinizi vermeden önce Karayipler'deki köle pazarı hakkında size biraz daha bilgi vermek isterim. 'Repartimiento' kelimesinin ne anlama geldiğini biliyor musunuz?";
			link.l1 = "Hm, hayır, "+npchar.name+", Hayır, bilmiyorum. Ama sanırım birinden bir şeyi almakla ilgili. Doğru mu?";
			link.l1.go = "SlaveGalleon_1";
		break;
			
		case "SlaveGalleon_end":
			dialog.text = "Beni şaşırttınız. Benden ne bekliyordunuz? Gidin!";
			link.l1 = "Yasa dışı bir iş vicdanıma fazla gelir. Özellikle de köle ticareti.";
			link.l1.go = "node_hanter_1";
		break;
			
		case "SlaveGalleon_1":
			dialog.text = "Neredeyse başardınız,"+pchar.name+"   Birinin özgürlüğünü elinden almak. Repartimiento, yerli halkı köleleştirmenin kurnazca ve yasal bir yolu. Tabiri caizse. İspanyol yetkililer bunu ana karadaki yerlilere karşı kullanıyor. Daha fazlasını öğrenmek ister misiniz?";
			link.l1 = "Neden olmasın?";
			link.l1.go = "SlaveGalleon_2";
		break;
			
		case "SlaveGalleon_2":
			dialog.text = "İspanyol tacının temsilcileri, Kızılderili yerleşimlerini ziyaret ediyor. Sinsi aldatmacalar ve açık tehditler kullanarak, Kızılderililere çürük et, eski tıraş bıçakları gibi her türlü ıvır zıvırı fahiş fiyatlara satmaya zorluyorlar. Üstelik veresiye.\nBir süre sonra, diyelim ki bir yıl, temsilciler geri dönüp ödeme talep ediyor. Kızılderililer ödeyemezse — ki genellikle böyle oluyor — İspanyollar onların çalışabilecek erkeklerinden bazılarını, sözde bir süreliğine ve 'onlara toprak işlemeyi öğretmek için' alıp götürüyor.\nAnlayacağın, onlar asla köylerine geri dönmüyor. İşte bizim saf Kızılderililerimiz bu şekilde şeker plantasyonlarında ve maun fabrikalarında çalışmaya mahkûm oluyor.";
			link.l1 = "Lanet olsun... gerçekten mi... Peki, bu konuda yerliler ne yapıyor? İspanyollar onları köleleştirince karşı mı çıkıyorlar? Yoksa olan biteni hiç mi anlamıyorlar?";
			link.l1.go = "SlaveGalleon_3";
		break;
			
		case "SlaveGalleon_3":
			dialog.text = "Sanırım her zaman neyin geleceğini seziyorlar, ama sadece birkaçı açıkça karşı çıkmaya cesaret edebiliyor, özellikle de İspanyollar reislerin parmak izinin olduğu bir belge sunduklarında. Tabii, bu tür taktikler genellikle Arawaklar veya Miskitolar gibi barışçıl kabilelere karşı kullanılır. Böyle bir numara savaşçı Itza veya Akawoylar üzerinde işe yaramaz\nNeyse, şimdi görevinizden bahsedelim.";
			link.l1 = "Şimdiden bolca para kokusu alıyorum! Dinliyorum, "+npchar.name+".";
			link.l1.go = "SlaveGalleon_4";
		break;
			
		case "SlaveGalleon_4":
			Slavetrader_GetHispanShore();
			sTemp = pchar.questTemp.SlavetraderAreal.add; 
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			dialog.text = "Yakında, Caracas'tan ağır bir kalyon yola çıkacak. Adı "+pchar.questTemp.Slavetrader.ShipName+". It contains a huge number of slaves - about 3,000 men - Indians from the Orinoco, captured according to the repartimientos policy. The galleon is sailing to Santiago; the sugar plantations of Cuba need many workers. You must capture the galleon with her cargo. I would take at least two ships with me if I were you; they say the galleon is the finest of its kind. Pay rates remain the same - 200 pesos per head. ";
			link.l1 = "Heh! Kulağa hoş geliyor. Kabul ediyorum.";
			link.l1.go = "SlaveGalleon_5";
			link.l2 = "Biliyorsun, o repartimiento işini hiç sevmiyorum. Fazla acımasızca. Bunu yapmayacağım.";
			link.l2.go = "SlaveGalleon_end";
		break;
			
		case "SlaveGalleon_5":
			sTemp = pchar.questTemp.SlavetraderAreal.add; 
			dialog.text = "O zaman sana bol şans diliyorum. Bil ki bu geminin kaptanı çok yetenekli ve tecrübeli bir savaş denizcisidir. Mücadele kolay olmayacak, kendini hazırla. Zaman kaybetme, ona ulaşman on beş ya da yirmi gün sürecek "+sTemp+" Santiago. Kaçırmamaya çalış, gerçi bu kalyonu gözden kaçırmak gerçekten zor\nEvet! Az kalsın unutuyordum! Gemide bolca Hintli süs eşyası var, yerliler borçlarını sık sık kült eşyaları ve el işleriyle öderler. Bulduğun özel bir şeyi bana getir, getirdiğin her değerli eşya için sana iyi bir ödeme yaparım.";
			link.l1 = "Anladım.";
			link.l1.go = "exit";
			SlavetraderGalleonInWorld();
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Slavetrader_SlaveGalleonOver", 0, 0, 20, false);
			pchar.questTemp.Slavetrader = "wait1";
			AddQuestRecord("Slavetrader", "18");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sAreal", sTemp);
		break;
			
		case "Lostgalleon":
			dialog.text = "Pekâlâ, "+pchar.name+", bu benim son umudumdu... Bu yüzden bu işi sana teklif ettim. Bunu senden başka kimse başaramazdı... ve şimdi görüyorum ki sen de yapamıyorsun. O halde veda edelim. Son başarısızlıktan ve çıkan tüm dedikodulardan sonra, bütün müşterilerimi kaybettim. Neredeyse iflas ettim, belki de bu şehirden ayrılmam gerekecek. Seni suçlamıyorum - bu iş gerçekten zordu. Eh... Elveda,"+pchar.name+".";
			link.l1 = "Çok üzgünüm, "+npchar.name+", bu gerçekten fazla oldu. Gerçekten üzgünüm. Belki de her şey yoluna girer. Hoşça kal.";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Wingalleon":
			pchar.questTemp.Slavetrader.Nation = npchar.nation;
			amount = 3000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			if(amount < 1) 
			{
				dialog.text = "Of, şimdi kendimi daha iyi hissediyorum... Sana güvenmekle doğru yapmışım... Bu alaycılık da nereden çıktı? Ne oldu?";
				link.l1 = "Sayın efendim, bu bir kalyon değildi... ya da çok büyük bir kalyon değildi... Kahretsin! Bu bir Hat Gemisiymiş! Hem de bana hiç haber vermediniz! Ama yine de gemiye çıkmayı başardım. Benim elimde "+sTemp+" köleler ve onları size devretmeye hazırım. Anlaşmamıza göre, bana borçlusunuz - "+FindRussianMoneyString(iSlaveMoney)+". Yanlış bilgilendirmeniz için bir miktar tazminat almak harika olurdu.";
				link.l1.go = "Wingalleon_1";
			}
			else
			{
			dialog.text = "Galyonu buldun mu? Köleler ne oldu? Orada en az üç bin köle olmalıydı! Kahretsin, herkes hain ve alçak çıktı! Senden beklemezdim... sen benim son umudumdun\nPekala... Yemin ederim, elimde kalan son parayı seni yok etmek, seni öldürmek için harcayacağım! Tüm filomla "+NationNameGenitive(sti(npchar.nation))+" seni avlayacağım! Defol buradan!";
				link.l1 = "Pekâlâ...";
				link.l1.go = "Wingalleon_goaway";
			}
		break;
			
		case "Wingalleon_goaway":
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
			DialogExit();
		break;
			
		case "Wingalleon_1":
			dialog.text = "Yok artık! Yemin ederim, hiçbir fikrim yoktu. Ağır bir kalyonun yola çıkması gerekiyordu, lanet olası bir savaş gemisinin değil! Görünen o ki, son anda planlarını değiştirmişler... Ama yine de başardın!\nParan ve masraflarının karşılanması konusunda tamamen haklısın, ama mesele şu ki, şu anda böyle bir meblağa sahip değilim. Son zamanlardaki sıkıntılarımı biliyorsun... Ama lütfen kızma, "+pchar.name+"Tanrı aşkına. Sen bana yükü ver, ben de onu satarım, müşterim zaten bekliyor\nBeş gün içinde tüm parayı toplayacağım, böylece hak ettiğini alacaksın. Bana güvenebilirsin. Al, şu anda yanımda olan tüm nakiti sana veriyorum.";
			link.l1 = "Hm... Parayı şimdi alacağımı sanmıştım. Ne zorluklarla karşılaştığımı bir bilsen! Neyse... Sana anlayış göstereceğim. Ama unutma, beni kandırmaya kalkarsan, seni Avrupa'da bile bulurum!";
			link.l1.go = "Wingalleon_yes";
			link.l2 = "Biliyor musunuz, "+npchar.name+", defol git! Bu bir anlaşma değildi. Ne tür bir kavgayla uğraştığımı hayal bile edemezsin. Tüm köleleri kendime alacağım ve onları senin aracılığın olmadan satacağım.";
			link.l2.go = "Wingalleon_no";
		break;
			
		case "Wingalleon_no":
			dialog.text = "Demek sonunda konuşmaya başladınız! Görünüşe bakılırsa hazırlıksız "+npchar.name+"   benim için sadece sağılacak bir inektin, en ufak bir gecikmede bana ihanet edip kendi başına harekete geçiyorsun. Sana işi verenin ve ganimet hakkında bilgi verenin ben olduğumu unutmuş gibisin\nPekâlâ... Yemin ederim, elimde kalan son parayı bile seni yok etmek, seni öldürmek için harcayacağım! Tüm filo "+NationNameGenitive(sti(npchar.nation))+" Seni avlayacağım! Gözümün önünden kaybol!";
			link.l1 = "Beni boş bir para sandığıyla korkutmaya kalkma. Tüm filolarını batırır, onları yengeçlere yem ederim.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Wingalleon_yes":
			dialog.text = "Anlayışınız için teşekkür ederim, "+pchar.name+". Her şeyin yolunda gideceğine söz veriyorum, tehdit etmene gerek yok\nBunu avans olarak al. On beş sandık. Beşi manevi zararların tazmini için. Kalanı almak için beş gün sonra yanıma gel.\nGemide bulduğun Hint eşyalarını da getirmeyi unutma... tabii bulduysan. Zaten onlar için sana ödeyecek bir şeyim yok.";
			link.l1 = "Beş gün içinde,"+npchar.name+"Beş gün içinde...";
			link.l1.go = "Wingalleon_yes_1";
		break;
			
		case "Wingalleon_yes_1":
			TakeNItems(pchar, "chest", 15);
			Log_Info("You've received credit chests");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_4");
			pchar.questTemp.Slavetrader = "wait_4";
			AddQuestRecord("Slavetrader", "20");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			pchar.questTemp.Slavetrader.iSlaveMoney = makeint(sTemp)*200-120000;
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
			DialogExit();
		break;
	
		case "FindRat":
			dialog.text = "Söz verdiğim gibi, "+pchar.name+", ödemeye hazırım. Köleler satıldı, müşteri memnun, biz de öyle. Avansı düştükten sonra ödülünüz"+FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney))+". Lütfen, paranızı alın.";
			link.l1 = "Harika, "+npchar.name+". Sözünde duran bir adamla iş yapmak güzel...";
			link.l1.go = "FindRat_1";
		break;
			
		case "FindRat_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.text = "Her zaman sözüme güvenebilirsiniz, "+pchar.name+" . Sana asla güvenini sarsacak bir sebep vermedim. Ortaklar birbirine dürüst olmalı, işin özü budur\nŞimdi Hint eserlerinden konuşalım. Ne getirdiysen göster, benim gibi bir koleksiyoncuyu bekletme.";
			link.l1 = "Hm... Bir bakın.";
			link.l1.go = "FindRat_2";
		break;
			
		case "FindRat_2":
			if (CheckCharacterItem(pchar, "talisman16"))
			{
				dialog.text = "Evet! Mükemmel! Altın bir ritüel bıçağı! Çok nadir bir eşya. Koleksiyonumda hep böyle bir şey olsun istemişimdir. Sana bunun için 30.000 teklif ediyorum, ya da karşılığında bir 'Ehecatl' muskası verebilirim. Zaten elimde iki tane var.";
				link.l1 = "Parayı alırdım.";
				link.l1.go = "BG_money";
				link.l2 = "'Ehecatl' muskası karşılığında alırım.";
				link.l2.go = "BG_change";
				link.l3 = "Bu bıçağı yanımda tutmam daha iyi olur.";
				link.l3.go = "BG_no";
			}
			else
			{
				dialog.text = "Bakalım... Maalesef, benim için ilginç bir şeyin yok.";
				link.l1 = "Ne derseniz deyin.";
				link.l1.go = "BG_PF";
			}
		break;
			
		case "BG_money":
			dialog.text = "Harika. Al şu 30.000'i ve bu Hint bıçağı artık benim.";
			link.l1 = "Güzel. Ve ilgilendiğiniz tek şey bu mu...";
			link.l1.go = "BG_PF";
			AddMoneyToCharacter(pchar, 30000);
			Log_Info("You've given a golden knife");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "talisman16", 1);
		break;
			
		case "BG_change":
			dialog.text = "Harika! İşte muskanız, ve bu Hint bıçağı artık benim.";
			link.l1 = "Güzel. Ve ilgilendiğiniz tek şey bu mu...";
			link.l1.go = "BG_PF";
			Log_Info("You've given a golden knife");
			Log_Info("You've received an amulet of 'Ehecatl'");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "talisman16", 1);
			TakeNItems(pchar, "obereg_9", 1);
		break;
			
		case "BG_no":
			dialog.text = "Her neyse. Ama yine de, bu gerçekten çok yazık...";
			link.l1 = "Güzel. Ve ilgilendiğiniz tek şey bu mu...";
			link.l1.go = "BG_PF";
		break;
			
		case "BG_PF":
			dialog.text = "Bekleyin! Bir kez daha bakmama izin verin...";
			link.l1 = "Elbette. Gel bak, istediğini seç.";
			link.l1.go = "PF_check";
		break;
			
		case "PF_check":
			if (CheckCharacterItem(pchar, "mineral31"))
			{
				dialog.text = "Bu! Ve başta fark etmemiştim bile. Şu bakır halkalı kemiğe ilgim var. Ne kadar ilginç bir şey, size söylüyorum... Size 20.000 peso ödeyebilirim ya da karşılığında bir 'Cimaruta' muskası verebilirim.";
				link.l1 = "Parayı alırım.";
				link.l1.go = "PF_money";
				link.l2 = "'Cimaruta' muskası karşılığında alırım.";
				link.l2.go = "PF_change";
				link.l3 = "Bu eseri yanımda tutardım.";
			link.l3.go = "PF_no";
			}
			else
			{
				dialog.text = "Hayır... burada ilgimi çeken başka hiçbir şey yok.";
				link.l1 = "Ne halin varsa gör!";
				link.l1.go = "FindRat_3";
			}
		break;
			
		case "PF_money":
			dialog.text = "Mükemmel! İşte 20.000 peso ve bu kemik artık benim.";
			link.l1 = "Güzel. Anlaşmamızdan memnunum.";
			link.l1.go = "FindRat_3";
			AddMoneyToCharacter(pchar, 20000);
			Log_Info("You've given a magic bone");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "mineral31", 1);
		break;
			
		case "PF_change":
			dialog.text = "Harika! İşte muskanız, bu kemik de artık benim.";
			link.l1 = "Güzel. Anlaşmamızdan memnunum.";
			link.l1.go = "FindRat_3";
			Log_Info("You've given a magic bone");
			Log_Info("I've received an amulet of 'Cimaruta'");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "mineral31", 1);
			TakeNItems(pchar, "amulet_11", 1);
		break;
			
		case "PF_no":
			dialog.text = "Her neyse. Ama yine de çok yazık...";
			link.l1 = "O kemiğe kendim için ihtiyacım var, çok üzgünüm.";
			link.l1.go = "FindRat_3";
		break;
			
		case "FindRat_3":
			dialog.text = "Şey... kadırgaya—ah, pardon, Savaş Gemisine—binerek beni kurtardınız. Ortaklığımızı gerçekten takdir ediyorum, "+pchar.name+". Sen benim en iyi ajanımsın.";
			link.l1 = "İltifatınız için teşekkür ederim. Başarılarımı biraz fazla abartıyorsunuz...";
			link.l1.go = "FindRat_4";
		break;
			
		case "FindRat_4":
			dialog.text = "Tamamen ciddiyim. Olağanüstü yetenekleriniz ve size duyduğum güven nedeniyle sizden bir görev daha üstlenmenizi isteyeceğim.";
			link.l1 = "Heh! Şaşırtıcı! Dinliyorum. Kölelerle dolu diğer kalyon nerede?";
			link.l1.go = "FindRat_5";
		break;
			
		case "FindRat_5":
			dialog.text = "Bu sefer mesele kölelerle ilgili değil. Şaşırdınız mı? Görev için size iyi bir ödeme yapacağım... Hem de çok iyi.";
			link.l1 = "Doğrudan konuya gir.";
			link.l1.go = "FindRat_6";
		break;
			
		case "FindRat_6":
			dialog.text = "Bu iş, senin de dahil olduğun son olaylarla bağlantılı... Bildiğin gibi, ben biraz yasa dışı bir işle uğraşıyorum - köle ticaretiyle. Ayrıca, senin gibi korsanlara her türlü görev için iş veriyorum\nAdamlarımdan biri kısa süre önce, nedeni bilinmeyen bir şekilde bana ihanet etti. Delil toplayıp yetkililere rapor verdi. Sonuçlarını bizzat gözlerinle görme şansın oldu. Asker dolu bir gemi buraya geldi... gerisini biliyorsun\nDurumu düzeltmek için epey uğraştım. Muhtemelen anlıyorsundur, bu ihaneti karşılıksız bırakamam. Ayrıca, o sıçan hâlâ hayattayken huzur içinde yaşayıp çalışamam. Ödül avcıları gönderdim, ama henüz bir sonuç yok\nBu meseleyle bizzat ilgilenmeni istiyorum. Üstelik, onun yaptıkları seni de etkiledi.";
			link.l1 = "Hm... o alçak doğrudan seren direğine asılmalı! Bana ondan daha fazla bahset, tabii işin karşılığında alacağım ücreti de anlat.";
			link.l1.go = "FindRat_7";
		break;
			
		case "FindRat_7":
			dialog.text = "Bu konuda endişelenmeyin. Onu ortadan kaldırmanız için size cömertçe ödeme yapacağım, üstelik sadece paradan bahsetmiyorum. Koleksiyonumun en değerli parçalarını da esirgemeyeceğim. Şimdi adamdan bahsedelim. Adı Francois Gontier\nAv peşinde olduğumu biliyor, bu yüzden izini kaybettirmek için fırkateynini sattı. Meslektaşlarım onu Panama'da gördüklerini söylediler. Bence aramaya oradan başlamalısınız.";
			link.l1 = "Pekala, o zaman ben gidiyorum.";
			link.l1.go = "FindRat_8";
		break;
			
		case "FindRat_8":
			dialog.text = "O zaman sana bol şans dilerim. Şunu bil ki bu Gontier çok deneyimli bir denizci ve yanında gözü kara haydutlardan oluşan bir tayfası var. Kaybedecek hiçbir şeyi yok, bu yüzden son derece umutsuzca savaşacak.";
			link.l1 = "Böyle insanlardan korkmam, ama söylediklerini dikkate alacağım. Hoşça kal, ve emin ol, onu cehennemde bile bulacağım.";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			AddQuestRecord("Slavetrader", "21");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "FindRatPanama";
		break;
			
		case "Wincorvette":
			dialog.text = "Harika! Artık raporlarını denizanasına yazabilir. Kimse bana karşı çıkmaya cesaret edemez. Size minnettarım, "+pchar.name+", siz vazgeçilmez bir insansınız.";
			link.l1 = "Teşekkür ederim, "+npchar.name+", eylemlerimi bu kadar olumlu değerlendirdiğiniz için teşekkür ederim. Peki ya ödemem?";
			link.l1.go = "Wincorvette_1";
		break;
			
		case "Wincorvette_1":
			dialog.text = "Elbette. Böyle zorlu bir iş için adil bir ücret öderim. Öncelikle, size bu mükemmel dürbünü sunuyorum.";
			link.l1 = "Böylesi bir hediye, ne büyük sürpriz!";
			link.l1.go = "Wincorvette_2";
		break;
			
		case "Wincorvette_2":
			dialog.text = "Ayrıca, işinize karşılık olarak 100.000 peso ve kendi masraflarınız için de 50.000 peso ödemeniz var.";
			link.l1 = "Teşekkürler, "+npchar.name+". Tekrar ediyorum, sizinle iş yapmak gerçekten bir zevk.";
			link.l1.go = "Wincorvette_3";
			Log_Info("You've received an excellent spyglass");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "spyglass4", 1);
		break;
			
		case "Wincorvette_3":
			dialog.text = "Her zamanki gibi, bir ay sonra seni bekliyor olacağım. Bu sefer işimiz gerçekten büyük, iyi donanımlı bir filoya ihtiyacın olacak. Lütfen bunu anla ve kendini iyi hazırla. Planım işe yararsa, zengin olacağız.";
			link.l1 = "Güzel,"+npchar.name+". Hazır olduğumda geri geleceğim.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 150000);
			AddQuestRecord("Slavetrader", "21_13");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;
			
		case "Lostcorvette":
			dialog.text = "Yazık, ne ayıp... Neyse, üzülme, o alçağın kandırdığı ilk adam sen değilsin. Bir gün onu yakalayacağım zaten\nGelelim sana, bir ay sonra yanıma uğra. Bu iş büyük olacak, o yüzden iyi donanımlı ve silahlı bir filo topla. Lütfen, bunu ciddiye al ve elinden gelenin en iyisini yaparak hazırlan. Eğer planım işe yararsa, zengin olacağız.";
			link.l1 = "Güzel, "+npchar.name+". Hazır olduğumda geri geleceğim.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_14");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;
		
		case "Havana_fort":
			dialog.text = "Tam zamanında geldiniz, "+pchar.name+"! Az daha endişelenmeye başlayacaktım, seni bulması için birini gönderecektim\nHadi başlayalım! Görevin şimdi gerçekten büyük ve riskli, ama ödül buna değer. İş bittiğinde bir milyondan fazla peso alacaksın.";
			link.l1 = "Şimdi konuşuyoruz! Dinliyorum, "+npchar.name+".";
			link.l1.go = "Havana_fort_1";
		break;
		
		case "Havana_fort_1":
			dialog.text = "Köleleştirilen yerliler, Ana Kara'nın dört bir yanından küçük gruplar halinde Havana'ya getiriliyordu, ayrıca Afrika'dan da birkaç kalyon gelip boşaltıldı. Şimdiye dek, Havana kalesinin yüksek duvarlarının ardında neredeyse beş bin köle var.";
			link.l1 = "Bu anlaşmanın Havana'ya saldırmakla ilgili olduğuna dair bir his var içimde.";
			link.l1.go = "Havana_fort_2";
		break;
		
		case "Havana_fort_2":
			dialog.text = "Doğru hissediyorsun, "+pchar.name+". Tam olarak senden yapmanı istediğim şey bu. Sadece senden. Diğer ajanlarımın bunu başarabileceğinden şüpheliyim\nSanırım kabul ediyorsun, değil mi?";
			link.l1 = "Açıkçası, "+npchar.name+", şu an biraz şaşkınım. Operasyonunuzun bu kadar... büyük çaplı olduğunu hiç bilmiyordum. Elbette, varım. "+RandSwear()+"";
			link.l1.go = "Havana_fort_3";
			link.l2 = "Biliyor musun, "+npchar.name+", bu iş artık fazla ileri gidiyor. Sürprizlerinden bıktım. Bir dahaki sefere, açgözlülüğün yüzünden İspanya'ya savaş ilan etmek zorunda kalacağım ve onlarla tek başıma savaşacağım. O kölelere gerçekten ihtiyacın varsa, Havana'yı kendi başına ele geçir.";
			link.l2.go = "Havana_fort_not";
		break;
		
		case "Havana_fort_not":
			dialog.text = "Senden bunu beklemezdim... Kahretsin, şimdi müşterime ne diyeceğim? Peki. Karar senin ve ben de yeni bir ortak bulmalıyım. Hoşça kal, "+pchar.name+". Ve gelecekte de hizmetlerinizi kullanmayacağım. Unutmayın, yedi nesil boyunca soyunuzu zengin edebilecek bir anlaşmayı elinizden kaçırdınız.";
			link.l1 = "Dünyadaki tüm parayı alamazsınız, gözünüzden fazlasını istediniz. Elveda, "+npchar.name+".";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
		
		case "Havana_fort_3":
			dialog.text = "Anlaşacağınızı biliyordum. Şimdi, ayrıntıları dinleyin. Havana kalesi her zaman zorlu bir hedefti, fakat şimdi daha da zor.\nCuba kıyılarını iki hat gemisi koruyor ve kaleye saldırmadan önce önce onlarla başa çıkmalısınız...";
			link.l1 = "Anladım. Hat Gemileriyle ilk kez savaşmayacağım, ha-ha. Ne kadar vaktim var?";
			link.l1.go = "Havana_fort_4";
		break;
		
		case "Havana_fort_4":
			dialog.text = "Çok değil. En fazla üç hafta, sonra köleler Küba’daki İspanyol karakollarına gönderilecek. Acele etmelisiniz. ";
			link.l1 = "O halde zaman kaybetmeyelim. Hemen yola çıkıyorum!";
			link.l1.go = "Havana_fort_5";
		break;
		
		case "Havana_fort_5":
			dialog.text = "Bir dakika!"+pchar.name+", seninle aramızda bugüne kadar hiçbir yanlış anlaşılma ya da anlaşmazlık yaşanmadı. Yine de burada neler olup bittiğini bilmeni isterim. Sana güveniyorum, müşteri de bana güveniyor\nBu operasyona çok emek ve para yatırdık. Her bir köle, tüm beş bin kişi, bana teslim edilmeli\nAksi takdirde sana karşı çok ciddi önlemler almak zorunda kalacağız. Alınma, bu sadece bir uyarı. ";
			link.l1 = "Endişelenme, "+npchar.name+", İşin ne olduğunu anlıyorum, bu yüzden teslim ettiğimde bana ödeme yapmayı da unutma. Hoşça kal.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "24");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.quest.Slavetrader_HavanaAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_HavanaAttack.win_condition.l1.location = "Cuba2";//отправляем в локацию
            pchar.quest.Slavetrader_HavanaAttack.function = "Slavetrader_CreateLineShips";//создание линейных кораблей
			SetFunctionTimerCondition("Slavetrader_HavanaOver", 0, 0, 20, false);	//таймер
			characters[GetCharacterIndex("Havana_Mayor")].dialog.captureNode = "Slavetrader_HavanaAttack"; //капитулянтская нода мэра
			pchar.questTemp.Slavetrader = "wait1";
		break;
		
		case "Win_Havana_Fort":
			pchar.quest.Slavetrader_FiveTSlavesOver.over = "yes";
			amount = 5000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			if (amount < 1)
			{
				dialog.text = "Peki... Zaferinizin ödülü ne olacak?";
				link.l1 = "Sahip oldum "+sTemp+" köleler.";
				link.l1.go = "Havana_Fort_yes";
				break;
			}
			if (amount < 4500 && amount >= 1)
			{
				dialog.text = "Pekâlâ, pekâlâ. Ne dediğimi unuttun mu? Bana en az beş bin köle getirecektin, ama sen getirdiğin sayı sadece "+sTemp+". Neden böyle?";
				link.l1 = "Hmm... Bazıları Havana'dan yolculuğu sağ salim atlatamadı... yiyecek ve ilaçlarımız tükeniyordu.";
				link.l1.go = "Havana_Fort_no";
				break;
			}
			dialog.text = "Pekâlâ, pekâlâ... Beni kandırmaya mı çalışıyorsun? Sana ne dediğimi unuttun mu? Kölelerim nerede, sana soruyorum! Nerede onlar?!";
			link.l1 = "Hm... Şey, bakın...";
			link.l1.go = "Havana_Fort_no";
		break;
		
		case "Havana_Fort_no":
			dialog.text = "Pekâlâ. Açıklamalarına ihtiyacım yok. Bir anlaşmamız vardı ve sana en az beş bin köle toplaman için bir hafta veriyorum. Aksi takdirde başın çok derde girer.";
			link.l1 = "Pekala, pekala, sakin ol, onları senin için getireceğim.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "29");
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Slavetrader_HavanaSeekOver", 0, 0, 14, false);
			} 
			else SetFunctionTimerCondition("Slavetrader_HavanaSeekOver", 0, 0, 7, false);
			pchar.questTemp.Slavetrader = "Havana_seekslaves";
		break;
		
		case "Havana_Fort_yes":
			dialog.text = "Harika! Görevimi her zamanki gibi başarıyla tamamladınız. Sizden çok memnunum.";
			link.l1 = "Ben de öyleyim... Ama yükün parasını alınca daha da memnun olacağım.";
			link.l1.go = "Havana_Fort_yes_1";
		break;
		
		case "Havana_Fort_yesA":
		dialog.text = "Bundan dolayı çok memnunum. Geç kaldınız, fakat görevimi son derece mükemmel bir şekilde yerine getirdiniz.";
			link.l1 = "Ve şimdi yükün karşılığında ödeme almak istiyorum.";
			link.l1.go = "Havana_Fort_yes_1";
			pchar.quest.Slavetrader_HavanaSeekOver.over = "yes";
		break;
		
		case "Havana_Fort_yes_1":
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			dialog.text = "Tabii. Köleleri müşterime satacağım, o ödeyecek ve sen de paranı alacaksın. Tıpkı geçen seferki gibi. Bakalım, buraya getirdiğin "+sTemp+" köleler. Toplam tutar "+FindRussianMoneyString(iSlaveMoney)+" . Ödemeyi almak için bir hafta sonra buraya gel.";
			link.l1 = "Pekala, "+npchar.name+", anlaştık. Bir hafta sonra burada olacağım. Ama çok dikkatli ol...";
			link.l1.go = "Havana_Fort_yes_2";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
		break;
		
		case "Havana_Fort_yes_2":
			dialog.text = ""+pchar.name+", lütfen yapma. Biz ortağız ve aramızda hileye ya da güvensizliğe yer yok. Sana bolca para sözü verdim ve aldın da. İlginç görevler vaat ettim, onları da yaşadın. Masraflarını her zaman karşıladım, işlerim en kötü durumdayken bile. Hiç sözümden döndüm mü?";
			link.l1 = "Hmm... Hayır... Sadece paramı almak istiyorum, hepsi bu.";
			link.l1.go = "Havana_Fort_yes_3";
		break;
		
		case "Havana_Fort_yes_3":
			dialog.text = "Bak şimdi..."+pchar.name+", sen benim en iyi müşterimsin ve gelecekte de seninle iş yapmayı dört gözle bekliyorum. ";
			link.l1 = "Pekala, "+npchar.name+". Ama beni de anlamalısınız - bir milyon peso çok büyük bir meblağ.";
			link.l1.go = "Havana_Fort_yes_4";
		break;
		
		case "Havana_Fort_yes_4":
			dialog.text = "Sizi çok iyi anlıyorum, fakat önce köleleri satmam gerekiyor, ancak o zaman parayı alacağım.";
			link.l1 = "Pekâlâ. Sanırım birbirimizi anladık.";
			link.l1.go = "Havana_Fort_yes_5";
		break;
		
		case "Havana_Fort_yes_5":
			dialog.text = "Harika. Bir hafta sonra görüşürüz. Şimdi hazırlanmam ve müşterimle ticaret yapmak için yola çıkmam gerek.";
			link.l1 = "O halde sizi rahatsız etmeyeyim. Bir hafta sonra görüşürüz, "+npchar.name+".";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.Name = npchar.name;
			AddQuestRecord("Slavetrader", "32");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_6");
			SetFunctionTimerCondition("Slavetrader_UsurerEscape", 0, 0, 8, false);
			pchar.questTemp.Slavetrader = "wait_6";
			pchar.questTemp.Slavetrader.Cityname = npchar.city +"_town";
			LocatorReloadEnterDisable(npchar.city +"_town", "reload8_back", true);//чтобы не ходил неделю сюда вообще
		break;

		case "Usurer_Escape":
			dialog.text = "Burada ne mi yapıyorum? Şey... bu banka artık benim. İki gün önce satın aldım. Sen benim ilk müşterimsin ve sana çok cazip kredi koşulları sunabilirim...";
			link.l1 = "Krediler umurumda değil! Nerede "+pchar.questTemp.Slavetrader.Name+"?";
			link.l1.go = "Usurer_Escape_1";
		break;

		case "Usurer_Escape_1":
			dialog.text = "Sakin olun, lütfen! O çoktan kaçtı.";
			link.l1 = "Nasıl?";
			link.l1.go = "Usurer_Escape_2";
		break;
		
		case "Usurer_Escape_2":
			dialog.text = "Bilmiyor musunuz? Bir hafta önce ortadan kayboldu. Meğerse tüm müşterilerinin yatırımlarını alıp gitmiş. Söylenenlere göre vali bile zarar görmüş. Bu ev geride kaldı ve ben de onu koloniden satın aldım.";
			link.l1 = "Kayboldu mu? Nasıl?";
			link.l1.go = "Usurer_Escape_3";
		break;
		
		case "Usurer_Escape_3":
			dialog.text = "Onun kolonimizden kaçtığını duydum... Sanırım sana da borcu var. Hem de çok mu?";
			link.l1 = "Bir milyondan fazla! Ama bu sıçanı yine de yakalayacağım! Nereye gitti? Gemisinin adı ne?";
			link.l1.go = "Usurer_Escape_4";
		break;
		
		case "Usurer_Escape_4":
			dialog.text = "Nobody knows. Seriously. He just disappeared. The ship named 'Mauritius' or 'Maurdius' sailed away that day; perhaps he used it to escape.";
			link.l1 = "Kahretsin! O herife güvenmiştim! Daha ilk günden hain gibi kokuyordu! Ama biz gerçekten ortaktık diye kendimi kandırdım! Bir gün ona pişmanlığını yaşatacağım... Peki,"+npchar.name+", Davranışım için özür dilerim... Eğer iyi bir insansanız, ileride sizinle iş yapacağım, bundan emin olun, ama şimdilik hoşça kalın.";
			link.l1.go = "Usurer_Escape_5";
		break;
		
		case "Usurer_Escape_5":
			string sColony;
			sColony = npchar.city;
			SetNull2Deposit(sColony);
			dialog.text = " Sorun değil. Anlıyorum. Eğer paraya ihtiyacınız olursa ya da yatırım yapmak isterseniz, her zaman hizmetinizdeyim. ";
			link.l1 = "Teşekkürler. Ama paramı kendime saklasam daha iyi olur. Görüşürüz.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "33");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "wait1";
			pchar.questTemp.SanBoxTarget.Slavetrader = true;
			ChangeCharacterComplexReputation(pchar, "fame", 25);
			LAi_LocationDisableOfficersGen(&Locations[FindLocation(pchar.location)], false); // разблокируем вход офицеров 2015
		break;
	//<--работорговец	

	//--> семейная реликвия
		case "Noblelombard":
			dialog.text = "Gerçekten mi? Görünen o ki, kendisi benimle konuşmak istemiyor.... Peki, o zaman bu meseleyi seninle konuşalım. "+pchar.GenQuest.Noblelombard.Name+"Bana borcu var "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Summ))+": "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Money))+" ve ayrıca faizim - "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Percent))+" üç ay boyunca. Eğer yarına kadar parayı görmezsem, onun yadigârını satarım, ona ne kadar değer verdiği umurumda olmaz. İş iştir.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Summ))
			{
				link.l1 = "Harika! O halde, tüm faiziyle birlikte borcun tamamını derhal ödeyeceğim - "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Summ))+". Emanetini kendisi alacak. İşte paranız.";
				link.l1.go = "Noblelombard_1";
			}
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Percent)*2)
			{
				link.l2 = "Müvekkilim parayı üç ay içinde ödeyecek. Anlaşalım, geçen üç ayın faizini ve önümüzdeki üç ayın faizini ödeyeyim."+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Percent)*2)+".   Borcun kendisi ise daha sonra size ödenecek.";
				link.l2.go = "Noblelombard_2";
			}
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Percent))
			{
				link.l3 = "Müvekkilim üç ay içinde parayı bulacak. Son üç ayın faizini size şimdi ödeyeyim, siz de müvekkilim parayı tamamlayana kadar bekleyin, ne dersiniz?";
				link.l3.go = "Noblelombard_3";
			}
			link.l4 = "Bu nadirlik servet değerinde! Görünen o ki, müşterim bunun bedelini kendisi ödemek zorunda kalacak.";
			link.l4.go = "Noblelombard_4";
			pchar.quest.noblelombard = "true";//лесник с нпчара на пчара
		break;
		
		case "Noblelombard_1":
			dialog.text = "Mükemmel! Her şey yolunda gitti, paramı aldım ve "+pchar.GenQuest.Noblelombard.Name+"   emanetini geri alacak.";
			link.l1 = "Sizinle iş yapmak bir zevkti, "+npchar.name+"! Şimdilik hoşça kalın.";
			link.l1.go = "exit";
			pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Summ)*2;
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Summ));
			pchar.GenQuest.Noblelombard = "full";
			AddCharacterExpToSkill(pchar, "Leadership", 150);
	
		break;
		
		case "Noblelombard_2":
			if(sti(pchar.GenQuest.Noblelombard.Chance) < 7)
			{
				dialog.text = "Hm... Pekala. Bu bana uyar. Ama eğer "+pchar.GenQuest.Noblelombard.Name+" üç ay içinde parayı bulamazsa, bir daha süre vermem. Bunu ona mutlaka bildir.";
				link.l1 = "Elbette! Anlaştığımıza memnun oldum. Şimdi hoşça kalın.";
				link.l1.go = "exit";
				pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Percent)*4;
				AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Percent)*2);
				pchar.GenQuest.Noblelombard = "maxpercent";
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				AddCharacterExpToSkill(pchar, "Fortune", 70);
			
			}
			else
			{
				dialog.text = "Hayır. Bu işe yaramaz. Gün batımından önce tüm meblağı istiyorum. 'Müşterin'in bunu bildiğinden emin ol. Sana başka söyleyecek bir şeyim yok.";
				link.l1 = "Hm... peki. Uzlaşmak istememeniz üzücü.";
				link.l1.go = "Noblelombard_4";
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			
			}
		break;
		
		case "Noblelombard_3":
			if(sti(pchar.GenQuest.Noblelombard.Chance) < 3)
			{
				dialog.text = "Hm... Peki. Sadece müşterinize olan saygımdan kabul ediyorum. Ama eğer "+pchar.GenQuest.Noblelombard.Name+" üç ay içinde parayı bulamazsa, bir daha süre vermem. Bunu bildiğinden emin ol.";
				link.l1 = "Elbette! Anlaştığımıza memnun oldum. Şimdi hoşça kalın.";
				link.l1.go = "exit";
				pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Percent)*2;
				AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Percent));
				pchar.GenQuest.Noblelombard = "minpercent";
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				AddCharacterExpToSkill(pchar, "Fortune", 150);
			}
			else
			{
				dialog.text = "Hayır. Bu işe yaramaz. Gün batımından önce tüm tutarı istiyorum. 'Müşterinizin' bunu bildiğinden emin olun. Size söyleyecek başka bir şeyim yok.";
				link.l1 = "Hm... peki. Uzlaşmak istememeniz ne yazık.";
				link.l1.go = "Noblelombard_4";
				AddCharacterExpToSkill(pchar, "Fortune", 60);
	
			}
		break;
		
		case "Noblelombard_4":
			DialogExit();
			pchar.GenQuest.Noblelombard = "fail";
		break;
		
		case "Noblelombard_5":
			if(sti(pchar.GenQuest.Noblelombard.Chance) == 9)
			{
				dialog.text = "Yok artık! "+pchar.GenQuest.Noblelombard.Name+" adınıza bir mevduat hesabı açmamış. Hatta bizim kolonide bile değil - Avrupa'ya yelken açmış. Size söyleyeyim, böyle sahtekâr bir adamı daha önce hiç görmedim. Beni de kandırmaya çalıştı ama başaramadı - benim de birkaç numaram vardır...";
				link.l1 = "Alçak! Bana söz vermişti....";
				link.l1.go = "Noblelombard_6";
			}
			else
			{	// Addon-2016 Jason уменьшаем раздачу дублонов
				dialog.text = "Doğru. "+pchar.GenQuest.Noblelombard.Name+" adınıza bir mevduat yatırdı. Lütfen, buyurun alın...";
				link.l1 = "Harika! Hoşça kal, "+npchar.name+".";
				link.l1.go = "Noblelombard_9";
			}
		break;
		
		case "Noblelombard_6":
			dialog.text = "Böyle insanlar için böyle bir şey yok "+pchar.GenQuest.Noblelombard.Name+" çünkü ne onurları ne de vicdanları var. Sanırım sizi de kandırdı?";
			link.l1 = "Sanırım öyle. Her neyse, "+npchar.name+", ben de burada uzun süre kalmayacağım ve Avrupa küçük... Belki bir gün karşılaşırız. Elveda!";
			link.l1.go = "Noblelombard_7";
		break;
		
		case "Noblelombard_7":
			DialogExit();
			AddDialogExitQuestFunction("Noblelombard_Usurer_bad");
		break;
		
		case "Noblelombard_9":
			DialogExit();
			AddDialogExitQuestFunction("Noblelombard_Usurer_good");
		break;
//<-- семейная реликвия

		// Бремя гасконца
		case "sharlie_credit":
			dialog.text = "Monsieur, sizi tanımıyorum. Ben yalnızca yerel vatandaşlara ya da kaptanlara borç veririm. Affedin beni...";
			link.l1 = "Anladım. Yine de bu üzücü.";
			link.l1.go = "exit";
		break;
		// Бремя гасконца
		
		// Addon-2016 Jason, французские миниквесты (ФМК)
		// ФМК-Гваделупа
		case "FMQG_x":
			DelLandQuestMark(npchar);
			dialog.text = "N-ne... Ne demek istiyorsunuz?";
			link.l1 = "Sen tam bir alçaksın! Şimdi beni çok dikkatli dinle: O kadar da aptal değilim. Pinette mektubun iki kopyasını yazdı. Birini sana verdim, diğeri ise güvendiğim adamımda. Bana bir şey olursa — adamım onu doğrudan valinin eline teslim edecek...";
			link.l1.go = "FMQG_x1";
		break;
		
		case "FMQG_x1":
			dialog.text = "";
			link.l1 = "Bu yüzden sana tavsiyem, her sabah ayininde kilisede sağlığım için dua etmen; hayatıma suikastçılar göndermek yerine. Son bir uyarı! Bana karşı bir hamle yaparsan, mahvolursun. Anladın mı? Güzel. Derin bir nefes al ve dublonlarını saymaya devam et.";
			link.l1.go = "FMQG_x2";
		break;
		
		case "FMQG_x2":
			DialogExit();
			pchar.questTemp.FMQG = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Guadeloupe", "27");
			CloseQuestHeader("FMQ_Guadeloupe");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Sneak", 400);
			AddCharacterExpToSkill(pchar, "Sailing", 200);
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		// Другое
		case "NeHochuRazgovarivat":
			dialog.text = "Seninle konuşmak istemiyorum.";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		// Леди Бет -->
		case "LadyBeth_Usurer_1":
			dialog.text = "Elbette! Birçoğu sadece parasını alıp gitmek istiyor. Özellikle son zamanlardaki söylentileri düşünürsek...";
			link.l1 = "Hangi dedikodular?";
			link.l1.go = "LadyBeth_Usurer_2";
		break;
		
		case "LadyBeth_Usurer_2":
			dialog.text = "Mürettebat arasında şartların kötüleştiğini söylüyorlar. Monsieur Blackwood artık düzenli kayıplara bile göz yummaya başlamış - bu daha önce hiç olmamıştı. Ama bu benim işim değil. Ben sadece mal satarım. Peki, neyle ilgileniyorsunuz?";
			link.l1 = "Hadi işe koyulalım.";
			link.l1.go = "next";
			npchar.quest.item_date = "LadyBeth";
			pchar.questTemp.LadyBeth_Usurer = true;
		break;
		// Леди Бет <--
	}	
}

// ugeen проверка, можем ли мы использовать дублоны в качестве вклада
bool CheckUseDublons(ref NPChar)
{
	int iTest 	= FindColony(NPChar.City); // город банка
	if(iTest == -1) return false;
	
	ref rColony = GetColonyByIndex(iTest);
	 	 
	bool bOk1 = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea); 
	bool bOk2 = (GetCharacterItem(pchar,"gold_dublon") > 10) || (CheckItemMyCabin("gold_dublon") > 10);
	
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && bOk1 && bOk2) return true;

	return false;
}

void SlavetraderGalleonInWorld()
{
	//создаем галеон с рабами
	ref sld;
	string sName;
	sName = pchar.questTemp.Slavetrader.ShipName;
	sld = GetCharacter(NPC_GenerateCharacter("GaleonCap", "", "man", "man", 45, SPAIN, 20, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_LINESHIP, sName, CANNON_TYPE_CANNON_LBS42, 100, 100, 100);
	FantomMakeCoolFighter(sld, 45, 100, 100, "blade_21", "pistol5", "bullet", 100);
	sld.Ship.Mode = "war";	
	SetCaptanModelByEncType(sld, "war");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;
	sld.DontRansackCaptain = true;
	sld.WatchFort = true;
	sld.AlwaysEnemy = true;


	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterGoods(sld, GOOD_SLAVES, 3000 + rand(200));//положить в трюм рабов
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 100);
	//в морскую группу кэпа
	string sGroup = "SlaveGalleon";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1.group = "SlaveGalleon";
	pchar.quest.SlaveHalleon_AfterBattle.function = "Slavetrader_SlaveHalleon_AfterBattle";
	sld.city = pchar.questTemp.Slavetrader.Island; //определим колонию, из бухты которой выйдет
	sld.cityShore = pchar.questTemp.Slavetrader.Island.Shore;
	sld.quest.targetCity = "Santiago"; //определим колонию, в бухту которой он придёт
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	//Log_TestInfo("Captain of the galleon sailed away from " + sld.city + "and heading to " + sld.quest.targetShore);
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "Galleon '" + sName + " '";
	int daysQty = 20; //дней доехать даем с запасом
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);//вот он, сам запуск энкаунтера
}
