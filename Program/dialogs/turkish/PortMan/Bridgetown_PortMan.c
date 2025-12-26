// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
    switch (Dialog.CurrentNode)
	{
		case "quests":
			//регата
			if (CheckAttribute(pchar, "questTemp.Regata.Go") && !CheckAttribute(npchar, "quest.regatatalk"))
			{
				dialog.text = "Ne istiyorsun? Ah, regatta katılımcısısın! Doğru mu?";
				link.l1 = "Aynen öyle, efendim. Kurallara göre burada kaydolmam gerekiyor.";
				link.l1.go = "Regata_check";
				break;
			}
			//регата
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne tür sorular?","Ne istiyorsun, "+GetAddress_Form(NPChar)+"?"),"Bana zaten bir soru sormaya çalıştın "+GetAddress_Form(NPChar)+"...","Bugün bu soruyu üçüncü kez gündeme getiriyorsunuz...","Bak, eğer liman işleriyle ilgili bana söyleyecek bir şeyin yoksa, sorularınla beni meşgul etme.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim.","Konuşacak bir şeyim yok."),"Boş ver.","Gerçekten de, bu artık üçüncü sefer...","Üzgünüm, ama şimdilik liman işleriyle ilgilenmiyorum.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Blueweld'e biraz paprika satmaya gidiyorum. Söylesene, bayım, Blueweld'e giden bir yolcunuz var mı? Ya da en azından Port Royal'e. Bir yolcudan para almak harika olurdu, tayfanın maaşını ödemeye yardımcı olur. Zaten maaşlarını en aza indirdim ama şu tembel herifler hâlâ para istiyor...";
                link.l1.go = "PortofficeDone";
            }
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "barbados")
			{
				link.l1 = "Philipsburg'da Gaius Marchais komutasında 'Admirable' adında bir kalyon yüklenmişti. Buraya bir miktar paprika getirmesi gerekiyordu. Bu kaptanı bulmama yardım edebilir misiniz?";
                link.l1.go = "guardoftruth";
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && !CheckAttribute(npchar, "quest.garpiya"))
			{
				if (CheckAttribute(npchar, "questTemp.caleuche"))
				{
					link.l1 = "Garip bir isme sahip bir xebec hakkında sormak istiyordum.";
					link.l1.go = "caleuche_2";
				}
				else
				{
					link.l1 = "Bir Kaptan Jack... ya da Jackson'a ait bir xebecin sık sık limanınızı ziyaret ettiğini duydum. Onu nerede bulabileceğimi söyleyebilir misiniz?";
					link.l1.go = "caleuche";
				}
			}
		break;

		//Голландский гамбит
		case "PortofficeDone":
			dialog.text = "Maalesef, Blueweld ya da Port-Royal için yolcumuz yok. Yarın ya da öbür gün tekrar gelin.";
			link.l1 = "Ne yazık. O halde hoşça kal.";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-9");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
				DelMapQuestMarkCity("Bridgetown");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;

		//регата
		case "Regata_check":
		iTest = FindColony(npchar.city); 
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			bool bRegLugger = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
			pchar.quest.Regata_PU.over = "yes"; // mitrokosta снимаем прерывание
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || !CheckAttribute(pchar, "questTemp.Regata.Sentjons") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
				dialog.text = "Hm... Regata kurallarını çiğnediniz ve sizi diskalifiye etmek zorundayım. Üzgünüm. Bir sonraki sefere katılamayacaksınız. Port Royal'a zaten bir rapor hazırladım.";
				link.l1 = "Eh... ne yazık! Ama burada yapabileceğim bir şey yok, çok dikkatliydin. Hoşça kal!";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Regata");
				AddQuestRecord("Regata", "45");
				CloseQuestHeader("Regata");
			}
			else
			{
				pchar.questTemp.Regata.FourthTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());//истратил ГГ в часах на 1+2+3+4 переход
				dialog.text = "Kaptan, şehrin kuşatma altında olduğunu fark etmiş olabilirsiniz. İspanyolların her an saldırmasını bekliyoruz ve kuvvetlerimizi seferber ediyoruz. Ama regatta hâlâ devam ediyor\nHaydi kaydolalım, kaptan "+GetFullName(pchar)+", gemi - "+pchar.Ship.Name+"... Regatta süresinin saat cinsinden ifadesi "+sti(pchar.questTemp.Regata.FourthTransitionTime)+". Tamam, sonucun kaydedildi, yoluna devam edebilirsin.";
				link.l1 = "Rütbemi söyle.";
				link.l1.go = "Regata_info";
			}
		}
		else
		{
			dialog.text = "Buradasınız ama geminizi göremiyorum. Nerede?";
			link.l1 = "Üzgünüm efendim. Gemimi hemen limana çekeceğim.";
			link.l1.go = "exit";
		}
		break;
		
		case "Regata_info":
			int n=1;
			string sTemp, sName, sShip;
			for (int i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				if (pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FourthTransitionTime))
				{
					n++;
					sName = pchar.questTemp.Regata.AdversaryName.(sTemp);//имя ближайшего противника
					sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp);//его корабль
				}
			}
			if (n==1)
			{
			dialog.text = "Ah, evet... Üzgünüm, bunun için fazla meşguldüm. İlk sizsiniz.";
			link.l1 = "Anladım. Bilgi verdiğiniz için teşekkürler.";
			link.l1.go = "exit";
			AddQuestRecord("Regata", "22");
			}
			else
			{
				if (n==6)
				{
				dialog.text = "Ah, evet... Üzgünüm, bunun için çok meşgulüm. Sen sonuncusun.";
				link.l1 = "Anladım. Bilgi verdiğiniz için teşekkürler.";
				link.l1.go = "exit";
				AddQuestRecord("Regata", "27");
				}
				else
				{
					if (n==2)
					{
						dialog.text = "Ah, evet... Üzgünüm, bunun için fazla meşgulüm. Sen ikincisin. Senden önce sadece bir kaptan var. Onun adı "+sName+" gemide "+sShip+".";
						link.l1 = "Anladım. Bilgilendirmeniz için teşekkürler.";
						link.l1.go = "exit";
						AddQuestRecord("Regata", "23");
					}
					else
					{
						dialog.text = "Ah, evet... Üzgünüm, bunun için çok meşgulüm. Rütbeniz "+n+" . En yakın rakibiniz "+sName+" gemide "+sShip+".";
						link.l1 = "Anladım. Bilgi verdiğiniz için teşekkürler.";
						link.l1.go = "exit";
						if (n==3) AddQuestRecord("Regata", "24");
						if (n==4) AddQuestRecord("Regata", "25");
						if (n==5) AddQuestRecord("Regata", "26");
					}
				}
			}
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 30);//защита
			AddCharacterExpToSkill(pchar, "Repair", 30);//починка
			AddCharacterExpToSkill(pchar, "Fortune", 30);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 30);//скрытность
			npchar.quest.regatatalk = "true";
			pchar.questTemp.Regata.Bridgetown = "true";//отметка Бриджтауна
			pchar.quest.Regata_Check1.win_condition.l1 = "location";
			pchar.quest.Regata_Check1.win_condition.l1.location = "Curacao";
			pchar.quest.Regata_Check1.function = "RegataCheck";//проверка 1
			pchar.quest.Regata_Check2.win_condition.l1 = "location";
			pchar.quest.Regata_Check2.win_condition.l1.location = "Caracas";
			pchar.quest.Regata_Check2.function = "RegataCheck";//проверка 2
			pchar.quest.Regata_Check3.win_condition.l1 = "location";
			pchar.quest.Regata_Check3.win_condition.l1.location = "PortoBello";
			pchar.quest.Regata_Check3.function = "RegataCheck";//проверка 3
			pchar.quest.Regata_Check.win_condition.l1 = "location";
			pchar.quest.Regata_Check.win_condition.l1.location = "Jamaica";
			pchar.quest.Regata_Check.function = "RegataCheck";//проверка 4
			pchar.questTemp.Regata.AttackIsland = "Curacao";
			pchar.questTemp.Regata.AttackNation = HOLLAND;
			pchar.quest.Regata_Attack.win_condition.l1 = "location";
			pchar.quest.Regata_Attack.win_condition.l1.location = "Curacao";
			pchar.quest.Regata_Attack.function = "RegataAttack_Brigantine";
			pchar.quest.Regata_Attack1.win_condition.l1 = "location";
			pchar.quest.Regata_Attack1.win_condition.l1.location = "Curacao";
			pchar.quest.Regata_Attack1.function = "RegataAttack_Corvette";//третья засада
			pchar.quest.Regata_Hunter.win_condition.l1 = "location";
			pchar.quest.Regata_Hunter.win_condition.l1.location = "Barbados";
			pchar.quest.Regata_Hunter.function = "RegataAttack_Hunter";//ДУ у Барбадоса
			pchar.quest.Regata_Finish.win_condition.l1 = "location";
			pchar.quest.Regata_Finish.win_condition.l1.location = "Jamaica";
			pchar.quest.Regata_Finish.function = "RegataFinishSea";
			pchar.quest.Regata_Finish1.win_condition.l1 = "location";
			pchar.quest.Regata_Finish1.win_condition.l1.location = "Portroyal_town";
			pchar.quest.Regata_Finish1.function = "RegataFinishTown";//финиш регаты
			//ситуации
			pchar.quest.Regata_Siege.win_condition.l1 = "location";
			pchar.quest.Regata_Siege.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.Regata_Siege.function = "RegataSiegeOfficer";//на квест по вывозу жителей
		break;
		//регата
		
		// Страж Истины
		case "guardoftruth":
			dialog.text = "Evet, bu kalyon buradaydı, mallarından arındırıldı ve ardından limanımızdan ayrıldı. Gideceği yer hakkında bilgi... hm... yok, hiçbir şey yok. Üzgünüm ama yapabileceğim bir şey yok.";
			link.l1 = "Anladım. Ne yazık... Aramaya devam edeceğim.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			DialogExit();
			AddQuestRecord("Guardoftruth", "13");
			pchar.questTemp.Guardoftruth = "barbados1";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Efendim, geminin tam adını bilmem gerekiyor. Limanımızdan pek çok Jack ve Jackson geçiyor. Peki, geminin adı nedir?";
			link.l1 = "";
			Link.l1.edit = 2;
			link.l1.go = "caleuche_name";
			link.l2 = "Sorun şu ki, onun eski teknesinin adını bilmiyorum. Garip, bir kuş kadınıymış, doğmuş...";
			link.l2.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Beyefendi, hikayelerinizi ve bilmecelerinizi meyhanede anlatın, burası saygın bir kurum. Ya o xebec'in adını söyleyin ya da işimden alıkoymayın beni.";
			link.l1 = "Pekala, öğrenmeye çalışacağım.";
			link.l1.go = "exit";
			npchar.questTemp.caleuche = "true";
		break;
		
		case "caleuche_2":
			dialog.text = "Peki? Geminin adını biliyor musun? Dinliyorum.";
			link.l1 = "";
			Link.l1.edit = 2;
			link.l1.go = "caleuche_name";
		break;
		
		case "caleuche_name":
			if (GetStrSmallRegister(dialogEditStrings[2]) == "harpy")
			{
				dialog.text = "'Harpy'? Tabii ki o xebec'i biliyorum. Kaptanı Reginald Jackson. Ama Bridgetown'da çok uzun zamandır değil. Duyduğuma göre artık Hollanda Batı Hindistan Şirketi için çalışıyor. Yani onu Willemstad'da aramalısınız.";
				link.l1 = "Çok teşekkür ederim! Bana gerçekten çok yardımcı oldunuz.";
				link.l1.go = "caleuche_3";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "Üzgünüm, ama bu bana hiçbir şey hatırlatmıyor. Kaptanınızın gerçekten burada, Bridgetown'da olduğundan emin misiniz?";
				link.l1 = "Eminim. Peki, belki bir şeyler bulurum ...";
				link.l1.go = "exit";
			}
		break;
		
		case "caleuche_3":
			DialogExit();
			AddQuestRecord("Caleuche", "18");
			pchar.questTemp.Caleuche.Garpiya = "gwik"; 
			npchar.quest.garpiya = "true";
			AddLandQuestMarkToPhantom("GVIK", "HWIC_headclerk");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
