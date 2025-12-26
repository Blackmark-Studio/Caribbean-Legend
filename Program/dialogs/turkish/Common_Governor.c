// boal 25/04/04 общий диалог Governor
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Governor\" + NationShortName(sti(NPChar.nation)) + "_Governor.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    
    ref offref, sld;
    int i, cn;
    int qty;
    int iSumm;
    string attrLoc;

    /// выкуп колонии
    ref CaptGovenor, FortColony;
    int f, colony_money;

    int k = 1000;
    if (CheckAttribute(Nations[sti(NPChar.nation)], "Fort"))
    {
        k = (300 - sti(Nations[sti(NPChar.nation)].Fort)*10);
    }
	bool ok;
	
	attrLoc = Dialog.CurrentNode;
	if (findsubstr(attrLoc, "CityGive_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.quest.CityIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "ColonyGive";
 	}
 	
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
            NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Vali genel müdürün ofisinde yüzünü göstermeye cüret ediyorsun ha?! Gerçekten delisin...","Bu tembeller nasıl oldu da bir düşmanın evime sızmasına izin verdi? Bunu aklım almıyor...","Elbette, bir serseri konutumda cirit atıyorsa muhafızlarımın bir kuruşluk değeri yok demektir..."),LinkRandPhrase("Ne istiyorsun, "+GetSexPhrase("serseri","pislik")+"?! Askerlerim zaten peşindeler, "+GetSexPhrase("pis korsan","pislik")+"!",""+GetSexPhrase("Pis","Pis")+" Katil, derhal evimden defol! Muhafızlar!","Senden korkmuyorum, "+GetSexPhrase("alçak","serseri")+"! Yakında kalemizde asılacaksın, fazla uzağa gidemezsin..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Askerler beş para etmez...","Beni asla yakalayamazsın."),RandPhraseSimple("Kapa çeneni, dostum, yoksa o pis dilini kökünden sökerim!","Sana söylüyorum dostum: Sessiz otur yoksa kafanı keserim ve o kapıdan köpeklerine fırlatırım..."));
				link.l1.go = "fight";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Senin bir görüşme talebinde çok ısrarcı olduğunu duydum. Benim adım "+GetFullName(npchar)+". Ben kolonilerin genel valisiyim "+NationNameGenitive(sti(NPChar.nation))+",   Kraliyet'in   vekili "+NationKingsName(npchar)+" bu sularda. Şimdi, lütfen bana söyler misiniz, ziyaretinizin amacı nedir, "+GetAddress_Form(NPChar)+".";
				link.l1 = "Benim adım "+GetFullName(pchar)+".";
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple("Ah, yine sen misin? Peki, genel valisinden ne istiyorsun "+NationNameGenitive(sti(NPChar.nation))+" bu sefer?","Ve yine, beni devletin önemli işlerinden alıkoyuyorsun? Ne istiyorsun, "+GetAddress_Form(NPChar)+"?");
				link.l1 = "Sana   Majestelerinin   adına   çalışmak   hakkında   konuşmak   istiyorum "+NationNameGenitive(sti(NPChar.nation));
				link.l1.go = "work";
				link.l2 = "Seninle önemli bir konu hakkında konuşmam gerek.";
				link.l2.go = "quests"; // файл нации
				//Jason --> Регата
				if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
				{
					link.l3 = "Davet üzerine regataya katılmak için geldim. İşte davetiyem.";
					link.l3.go = "Regata";
				}
				//<-- Регата
				link.l10 = "Üzgünüm, ama ilgilenmem gereken bazı işlerim var.";
				link.l10.go = "exit";
			}
		break;
		
		case "node_1":
			dialog.text = "Peki, seni buraya getiren ve devletin önemli işlerinden beni alıkoyan nedir?";
			link.l1 = "Sana   Majestelerinin   adına   çalışmak   hakkında   konuşmak   istiyordum "+NationNameGenitive(sti(NPChar.nation));
			link.l1.go = "work";
			link.l2 = "Sizinle önemli bir konu hakkında konuşacaktım.";
			link.l2.go = "quests";
			//Jason --> Регата
			if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
			{
				link.l3 = "Regataya katılmak için geldim. İşte davetiyem.";
				link.l3.go = "Regata";
			}
			//<-- Регата
			link.l10 = "Bu sadece bir nezaket ziyareti, başka bir şey değil. "+GetAddress_FormToNPC(NPChar);
			link.l10.go = "node_2";
		break;

		case "node_2":
			dialog.text = "Öyleyse, sizden ofisimi terk etmenizi ve işimden beni daha fazla alıkoymamanızı rica ediyorum.";
			link.l1 = "Evet, evet, tabii ki. Rahatsız ettiğim için kusura bakmayın.";
			link.l1.go = "exit";
		break;
		
		case "work":
            dialog.text = "Eğer iş arıyorsan, kolonilerin valileriyle konuş. Genellikle zeki ve cesur kaptanlara ihtiyaçları olur.";
			link.l1 = "Bunu aklımda tutacağım. Teşekkür ederim.";
			link.l1.go = "exit";
		break;
		
		//--> Jason регата
		case "Regata":
			dialog.text = "Oh, harika, seni görmek ne güzel kaptan! Tam zamanında geldin – regatta birkaç gün içinde başlayacak. Kuralları, sana ulaştırılmış olması gereken mektupta okudun mu?";
			link.l1 = "Evet, efendim, yaptım.";
			link.l1.go = "Regata_1";
			RemoveItems(PChar, "letter_open", 1);//уберем письмо
			TakeNationLicence(HOLLAND);//уберем лицензию
			DeleteAttribute(pchar, "questTemp.Regata.ToPortRoyal"); // patch-5
		break;
		
		case "Regata_1":
			dialog.text = "Ve giriş ücreti olarak ödeyeceğin 50.000 peso hazır mı? Bu para ödül havuzuna eklenecek.";
			if (makeint(Pchar.money) >= 50000)
			{
				link.l1 = "Evet, elbette. Lütfen ücretimi kabul edin.";
				link.l1.go = "Regata_2";
			}
			link.l2 = "Şu anda biraz nakit sıkıntım var. Ama en kısa zamanda kesinlikle getireceğim.";
			link.l2.go = "Regata_nomoney";
		break;
		
		case "Regata_2":
			dialog.text = "Very well. If you win, your money will be returned to you fivefold. Now, you should know how not to break the rules of the regatta.\nDiscuss the details with Henry Stevenson; he should be in the residence's room. Meet with him, he will explain everything.";
			link.l1 = "Pekala. Dediğin gibi yapacağım.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -50000);
			pchar.quest.Regata_Guber.win_condition.l1 = "location";
			pchar.quest.Regata_Guber.win_condition.l1.location = "Portroyal_Roomtownhall";
			pchar.quest.Regata_Guber.function = "PrepareToRegataInPortroyal";
			pchar.questTemp.Regata.Begin = "true";
			NextDiag.TempNode = "First time";
		break;
		
		case "Regata_nomoney":
			dialog.text = "Peki, ama lütfen fazla oyalanmayın kaptan. Regatta yakında başlayacak.";
			link.l1 = "Anladım. Regatta başlamadan önce sana parayı getirmeye çalışacağım.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_1";
			pchar.questTemp.Regata.nomoney = "true";
		break;
		
		//регата-финал
		case "Regata_Final":
			dialog.text = "Ve işte burada regatta'nın kazananı! Merhaba, Kaptan "+GetFullName(pchar)+"  Bu hak edilmiş başarınız için sizi tebrik etmeme izin verin! Regatta'nın kazananları her zaman İngiliz kolonilerinde popülerdir, hem de haklı olarak.";
			link.l1 = "Teşekkür ederim, efendim!";
			link.l1.go = "Regata_complete";
		break;
		
		case "Regata_complete":
			dialog.text = "Şimdi senin için en keyifli kısma geçelim - ödül töreni. Birincilik ödülü 250.000 peso. Buyur!";
			link.l1 = "Teşekkürler!";
			link.l1.go = "Regata_complete_1";
		break;
		
		case "Regata_complete_1":
			AddMoneyToCharacter(pchar, 250000);
			int iGift;
			string sItem1, sItem2, sItem3, sAdd;
			
			iGift = 3;
			switch (iGift)
			{
				case 0:
					sItem1 = "blade_10";//корд
					sItem2 = "cirass6";
					sItem3 = "bussol";
					sAdd = "cord, duelist's vest and boussole";
				break;
				
				case 1:
					sItem1 = "blade_15";//маринера
					sItem2 = "cirass2";//рейтарский панцирь
					sItem3 = "bussol";
					sAdd = "marinera, reiter's armour and boussole";
				break;
				
				case 2:
					sItem1 = "blade_17";//бретта
					sItem2 = "cirass7";//карацена
					sItem3 = "bussol";
					sAdd = "bretta, karacena and boussole";
				break;
				
				case 3://
					sItem1 = "blade_20";//мадонна
					sItem2 = "cirass2";//офицерская кираса
					sItem3 = "bussol";
					sAdd = "'Madonna', officer's cuirass and boussole";
				break;
			}
			GiveItem2Character(pchar, sItem1);
			GiveItem2Character(pchar, sItem2);
			GiveItem2Character(pchar, sItem3);
			dialog.text = "Ayrıca, değerli ödüllerden oluşan bir set kazanmaya hak kazandınız: "+sAdd+". Artık hepsi senin.";
			link.l1 = "Çok memnun oldum, efendim! Gerçekten, bunu hiç beklemiyordum.";
			link.l1.go = "Regata_complete_2";
		break;
		
		case "Regata_complete_2":
			dialog.text = "Tüm İngiliz kolonileri adına, regataya katıldığınız için size teşekkür ederim ve bir kez daha zaferinizi kutlarım! Eğer bir bahse girdiyseniz, şimdi Sir Henry Stevenson'a uğrayıp kazancınızı almak için tam zamanı, eğer henüz yapmadıysanız tabii. Size bol şanslar, kaptan!";
			link.l1 = "Nezaketiniz için teşekkür ederim efendim! Karşılığında, bana böyle büyük bir etkinliğe katılma fırsatı verdiğiniz için size teşekkür etmek isterim. Ve şimdi, izninizle size veda edip ayrılmak istiyorum.";
			link.l1.go = "Regata_complete_3";
		break;
		
		case "Regata_complete_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
		break;
		//<-- регата
	}
}
