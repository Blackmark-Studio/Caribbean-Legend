// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	int i,n;
	string month;
	
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne tür sorular?","Ne istiyorsun, "+GetAddress_Form(NPChar)+"?"),"Bana zaten bir soru sormaya çalıştın "+GetAddress_Form(NPChar)+"...","Bugün bu soruyu üçüncü kez gündeme getiriyorsunuz...","Bak, eğer liman işleriyle ilgili bana söyleyecek bir şeyin yoksa, o zaman beni sorularınla meşgul etme.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim.","Konuşacak bir şeyim yok."),"Boş ver.","Gerçekten de, bu üçüncü sefer...","Üzgünüm, ama şimdilik limanın işleriyle ilgilenmiyorum.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPortobello_1")
            {
                link.l1 = "İyi günler. Kaptan Francois Gontier'in nerede olduğunu öğrenmek istiyorum. Önemli bir meselem var.";
                link.l1.go = "Portobello_ratP_1";
            }
			// belamour legengary edition на пару с Акулой -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet"))
			{
				if(pchar.questTemp.SharkGoldFleet == "toPBPortOffice" || pchar.questTemp.SharkGoldFleet == "KillCurier")
				{
					link.l1 = "Ben bir tüccarım, Caracas'tan geldim ve liman idaresinden bir meslektaşınız bana size bazı evrakları teslim etmemi rica etti ...";
					link.l1.go = "SharkGoldFleet";
				}
				if(pchar.questTemp.SharkGoldFleet == "MoneySpeak")
				{
					link.l1 = "Evet, ödemeyi almak için buradayım.";
					link.l1.go = "SharkGoldFleet_11";
				}
			}
			//<-- на пару с Акулой
		break;

		case "Portobello_ratP_1":
			dialog.text = "Önemli bir mesele diyorsun? Bakalım. Hmm...  Korvet 'Francois Gontier', "+pchar.questTemp.Slavetrader.ShipName+"... Notlarıma göre, Señor Gontier Jamaika'ya gidiyordu.";
			link.l1 = "Teşekkür ederim! Bana çok yardımcı oldunuz!";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatJamaica";
			AddQuestRecord("Slavetrader", "21_3");
			AddQuestUserData("Slavetrader", "sShip", pchar.questTemp.Slavetrader.ShipName);
		break;
		// на пару с Акулой -->
		case "SharkGoldFleet":
			if(!bImCasual) pchar.quest.SharkGoldFleetToPB10.over = "yes"; 
			RemoveItems(PChar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			dialog.text = "Ah, nihayet! Tüccar mısınız, öyle mi? Yine mi, yine kuryelerden tasarruf etmeye çalışıyorlar ve sevkiyatı son ana kadar erteliyorlar... Evet, tabii! Doğru. Peki ben bu kadar kısa sürede filoyu nasıl donatacağım, söyler misiniz?...";
			link.l1 = "Sorumsuzca geliyor...";
			link.l1.go = "SharkGoldFleet_01";
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "Böyle de denebilir! Neyse, yapacak bir şey yok. Zamanla görüşürüz... Kendi kendime konuşuyorum, aldırma. Dinle, belki geri dönüyor musun?";
			link.l1 = "Aslında, burada mal satacaktım, sonra da – evet, Caracas'a geri dönecektim ...";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "Harika! Şimdi onlara bir cevap yazacağım ve sana geri götürmeni isteyeceğim. Yani... lütfen bunu on gün içinde teslim et, yoksa hiçbir şey yapmaya vakitleri kalmaz... Ve adını belirt.";
			if(pchar.questTemp.SharkGoldFleet == "KillCurier")
			{
				link.l1 = "Benim adım "+GetFullName(pchar)+".";
				link.l1.go = "SharkGoldFleet_03";
			}
			else
			{
				link.l1 = "Benim adım Andreas Garcia.";
				link.l1.go = "SharkGoldFleet_09";
			}
		break;
		
		case "SharkGoldFleet_03":
			TakeNItems(pchar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_SharkGoldFleet_2");
			dialog.text = "Bir dakika... Kaydedildi. Al bakalım. Unutma: on gün! Bu arada, bana getirdiğin şeyleri daha ayrıntılı inceleyeceğim.";
			link.l1 = "Evet, hatırlıyorum. Hoşça kal!";
			link.l1.go = "SharkGoldFleet_04";
		break;

		case "SharkGoldFleet_04":
			dialog.text = "Bir dakika... Anlamadım... Bir daha söyler misiniz, adınız neydi?";
			link.l1 = "Ben mi?.. Şey... Neden bu kadar önemli?";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			n = GetAddingDataDay(0,0,21);
			if(n<21) i = GetAddingDataMonth(0,1,0);
			else i = GetDataMonth();
			month = XI_ConvertString("MonthGen_" + i);
			pchar.questTemp.SharkGoldFleet.Date = ""+n+" "+month+"";
			SetFunctionTimerCondition("SharkGoldFleet1269fail", 0, 0, 22, false);
			SetFunctionTimerCondition("SGF_FleetTime", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToCPO10", 0, 0, 10, false);
			else NewGameTip("Exploration mode: timer is disabled.");
			dialog.text = "Bu çok önemli! Diyor ki... Yani... "+n+" "+month+"... Hayır, bu değil... 12, 50, 69, 55... Ama nerede... Ah, işte burada! Mektup mutlaka Kaptan tarafından teslim edilmeli "+pchar.questTemp.SharkGoldFleet.CurierName+" "+pchar.questTemp.SharkGoldFleet.Curierlastname+". Ve adınızın... olduğunu söylediniz "+GetFullName(pchar)+"?";
			link.l1 = "Bir hata olmuş olmalı...";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			DeleteAttribute(pchar,"questTemp.SharkGoldFleet.CurierName");
			DeleteAttribute(pchar,"questTemp.SharkGoldFleet.Curierlastname");
			dialog.text = "Hayır, bunda bir hata olamaz. Sana verdiğim mektubu geri ver. Bunu çözmem lazım!";
			link.l1 = "Hadi... Teslim edeceğim, her şey yoluna girecek.";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "Hayır! Mektubu bana geri ver! Muhafızlar!!!";
			link.l1 = "Ha, işi zor yoldan yapmak istiyorsun demek, ha?";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			DialogExit();
			pchar.questTemp.SharkGoldFleet = "DifficultVar";
			LICENSE_AddViolation();
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Sold"+i, "sold_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", sti(pchar.rank), SPAIN, 0, true, "soldier"));
				SetFantomParamFromRank(sld, sti(pchar.rank), true);         
				ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto3");
				LAi_SetWarriorType(sld); 
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				LAi_group_Attack(sld, Pchar);
			}
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
			SetFunctionExitFromLocationCondition("SharkGoldFleetExitPO", pchar.location, false);
		break; 
		
		case "SharkGoldFleet_09":
			dialog.text = "Bir dakika... İşte oldu. İsmini cevap mektubuna yazacağım. Al bakalım. Unutma: On günün var! Bu arada, getirdiğin şeyi daha ayrıntılı okuyacağım.";
			link.l1 = "Evet, hatırlıyorum. Hoşça kal!";
			link.l1.go = "SharkGoldFleet_10";
		break;
		
		case "SharkGoldFleet_10":
			DialogExit();
			pchar.questTemp.SharkGoldFleet = "MoneySpeak";
			TakeNItems(pchar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_SharkGoldFleet_2");
			AddQuestRecord("SharkGoldFleet", "17");
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
		break;
		
		case "SharkGoldFleet_11":
			dialog.text = "Ödeme?..";
			link.l1 = "Karakas'ta, meslektaşınız mektubun teslimatı için ödeme yapacağınızı söyledi.";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			dialog.text = "Hayır, yani, orada tamamen delirmişler! Şimdi onların yerine ben ödemek zorundayım!";
			link.l1 = "...";
			link.l1.go = "SharkGoldFleet_13";
		break;
		
		case "SharkGoldFleet_13":
			dialog.text = "Sana ne kadar vaat ettiler?";
			link.l1 = "Beş bin peso.";
			link.l1.go = "SharkGoldFleet_14";
			link.l2 = "On bin peso.";
			link.l2.go = "SharkGoldFleet_15";
		break;
		
		case "SharkGoldFleet_14":
			pchar.questTemp.SharkGoldFleet = 5000;
			dialog.text = "Görünüşe bakılırsa, orada benim hesabıma yaşamaya karar vermişler... Sadece kuryelere para harcamayı reddetmekle kalmıyor, bu işleri geçen tüccar gemilerine bırakıyorlar, üstüne bir de masrafları bana yüklüyorlar! Onlar hakkında Havana'ya şikayet yazacağım!";
			link.l1 = "Öfkenizi anlıyorum, señor, ama ne yapmamı istersiniz?";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_15":
			pchar.questTemp.SharkGoldFleet = 10000;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeOfficersLoyality("bad", 1);
			dialog.text = "Görünüşe göre orada benim hesabıma yaşamaya karar vermişler... Sadece kuryelere para harcamayı reddetmekle kalmıyorlar, bu tür işleri geçen tüccar gemilerine bırakıyorlar, bir de masrafları bana yüklüyorlar! Onlar hakkında Havana'ya şikayet yazacağım!";
			link.l1 = "Öfkenizi anlıyorum, señor, ama ne yapmamı istersiniz?";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_16":
			dialog.text = "Ah, Karakas'taki Yeni İspanya yetkililerinin açgözlülüğü senin suçun değil. Ama şu anda yanımda o kadar para yok. Ve paranın ancak yarın gelmesi gerekiyor ... Lütfen burada bekle, şimdi tefeciye gidip hemen döneceğim.";
			link.l1 = "...";
			link.l1.go = "SharkGoldFleet_17";
		break;
		
		case "SharkGoldFleet_17":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload1");
			LAi_SetStayType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto2");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload1","SGF_toUsurer", -1);
		break;
		
		case "SharkGoldFleet_18":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.SharkGoldFleet));
			n = GetAddingDataDay(0,0,21);
			if(n<21) i = GetAddingDataMonth(0,1,0);
			else i = GetDataMonth();
			month = XI_ConvertString("MonthGen_" + i);
			pchar.questTemp.SharkGoldFleet.Date = ""+n+" "+month+"";
			SetFunctionTimerCondition("SharkGoldFleet1269fail", 0, 0, 22, false);
			SetFunctionTimerCondition("SGF_FleetTime", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToCPO10", 0, 0, 10, false);
			else NewGameTip("Exploration mode: timer is disabled.");
			AddQuestRecord("SharkGoldFleet", "18");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date);
			LAi_SetHuberType(npchar);
			Lai_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			dialog.text = "Beklettiğim için üzgünüm. İşte sizin "+makeint(pchar.questTemp.SharkGoldFleet)+" sekiz reales. Ve bu durumda, cevabın bedelini Caracas'ta kendileri ödeyecekler. Onlara bunu benim söylediğimi ilet.";
			link.l1 = "Peki, ileteceğim. Teşekkür ederim ve bol şans!";
			link.l1.go = "exit";
			pchar.questTemp.SharkGoldFleet = "LightVar";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
