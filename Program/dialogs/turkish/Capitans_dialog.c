// разговор с капитаном на палубе  Boal
//homo 25/06/06
#include "DIALOGS\%language%\Rumours\Common_rumours.c"

int iEncPow = -1;
int iCapBattleDifficulty = -1; // Действует, пока не выгружен этот диалог

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	//belamour рыбацкое судно
	int i, iTemp, iQty;
	string sTemp;
    //homo Осады
    aref aData;
    makearef(aData, NullCharacter.Siege);
    string sCap, sGroup;
    string fort;
	bool bOk, bOk1, bOk2;

    if (CheckAttribute(aData, "nation"))
    {
	    sCap = NationShortName(sti(aData.nation))+"SiegeCap_";
	    sGroup = "Sea_"+sCap+"1";
	    
	   // string myships  = GetCompanionQuantity(PChar);
       // string escships = Group_GetCharactersNum(sGroup);
        
        switch(sti(aData.conation))
        {
            case 0:  fort = "English fort"; break;
            case 1:  fort = "French fort"; break;
            case 2:  fort = "Spanish fort"; break;
            case 3:  fort = "Dutch fort"; break;
            case 4:  fort = "Pirate fort"; break;
        }
        int ifortPower = sti(colonies[FindColony(aData.colony)].FortValue);
        int fortDamage = CheckFortInjuri();
        int SquadronDamage = CheckSquadronInjuri();
        
    }

    int iMoney;
	ref sld;
    
    if (CheckNPCQuestDate(npchar, "Card_date"))
	{
		SetNPCQuestDate(npchar, "Card_date");
		npchar.money = 3000 + rand(10) * makeint(100 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
	}
	else
	{
		if(sti(npchar.money) > CAP_MAX_MONEY || sti(npchar.money) < CAP_MIN_MONEY) 	
		{
			npchar.money = CAP_MIN_MONEY + rand(CAP_NORM);
		}
	}
    //homo 26/06/06
	ProcessCommonDialogRumors(NPChar, Link, Diag);
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			DialogExit();
			Diag.CurrentNode = Diag.TempNode;
		break;
		
		case "First time":
			if (!bDisableMapEnter)
			{
				//--> Jason эскорт 2 уровень
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "begin" && NPChar.id == "WMCaptain")
				{
					dialog.text = "Merhaba, kaptan. Allah kahretsin, sizi gördüğüme ne kadar sevindiğimi bilemezsiniz!";
					link.l1 = "Merhaba. Kendimi tanıtmama izin verin - "+GetFullName(PChar)+" . Seni sağ salim görmek beni de mutlu etti, buraya özellikle seni ve gemini bulmak için geldim.";
					link.l1.go = "WM_Captain";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "wait" && NPChar.id == "WMCaptain")
				{
					dialog.text = "İstediğim malzemeleri getirdin mi?";
					if (sti(pchar.questTemp.WPU.Escort.Planks) - GetSquadronGoods(pchar, GOOD_PLANKS) <= 0 && sti(pchar.questTemp.WPU.Escort.Sailcloth) - GetSquadronGoods(pchar, GOOD_SAILCLOTH) <= 0 && sti(pchar.questTemp.WPU.Escort.Linen) - GetSquadronGoods(pchar, GOOD_COTTON) <= 0)
					{
						link.l1 = "Evet. Geminizi tamir etmek için ihtiyacınız olan her şey ambarımda.";
						link.l1.go = "WM_Captain_5";
					}
					else
					{
						link.l1 = "Hayır, hâlâ üzerinde çalışıyorum.";
						link.l1.go = "exit";
					}
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "toCap" && NPChar.id == "WMCaptain")
				{
					dialog.text = "Selam, "+GetAddress_Form(NPChar)+" . Benim adım "+GetFullName(NPChar)+", Ben bu geminin kaptanıyım. O lanet olası korsan pislikleriyle savaşta bize yardım ettiğiniz için en içten teşekkürlerimi sunmak isterim - siz müdahale etmeseydiniz, işler bizim için oldukça kötüye gidebilirdi. Bizi gerçekten kurtardınız, kahretsin!";
					link.l1 = "Önemli değildi,  "+GetAddress_FormToNPC(NPChar)+" . Kendimi tanıtmama izin verin - "+GetFullName(PChar)+", liman müdürünün isteği üzerine sana geldim "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+". Bana kervanınızın başına gelen talihsizlikleri anlattı ve geminizi bulmam için beni gönderdi.";
					link.l1.go = "VSP_Captain";
					break;
				}
				//<-- эскорт 2 уровень
				
				if(CheckAttribute(NPChar, "surrendered"))
				{
                    CalcBattleDifficulty();
                    if(iEncPow == -1) iEncPow = 0;
					Pchar.GenQuest.MoneyForCaptureShip = (70 + hrand(60, "&CapSur"+NPChar.id)) * iEncPow;
					if(HasShipTrait(pchar, "trait14")) Pchar.GenQuest.MoneyForCaptureShip = makeint(sti(Pchar.GenQuest.MoneyForCaptureShip) * 1.35);
					dialog.text = "Dur biraz, bu şekilde beni öldürebilirsin. Benden ne istiyorsun?";
					//выкуп
					link.l1 = "Bu meseleyi barışçıl bir şekilde çözelim. Sanırım fidye en iyi karar olacak. Bir miktar "+Pchar.GenQuest.MoneyForCaptureShip+" pesos bana gayet iyi uyar, "+GetAddress_FormToNPC(NPChar)+". Ve ondan sonra, kaybolabilirsin!";
					link.l1.go = "surrender1";
					// обираем до нитки
					link.l2 = "Ambarında neler olduğunu görmek istiyorum. Ondan sonra, sen ve tayfan istediğiniz yere gidebilirsiniz.";
					link.l2.go = "surrender2";
					break;
				}
				
				//Голландский Гамбит, против всех
				if (CheckAttribute(PChar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MeetingStivesant" && NPChar.id == "Stivesant")
				{
					dialog.text = "Merhaba, efendim. Sizi görmek güzel. Kaptan Longway muhtemelen daha sonra gemiye gelir, değil mi?";
					link.l1 = "İyi günler, Bay Stuyvesant. Kendimi tanıtmama izin verin - "+GetFullName(pchar)+". Longway gelmeyecek, 'Meifeng'de değil.";
					link.l1.go = "Stivesant_1";
					pchar.quest.QuestShipsTerms_Over.over = "yes"; //снять таймер
					break;
				}
				if (CheckAttribute(PChar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "FleutOnTrinidad" && NPChar.id == "Keller")
				{
					DelLandQuestMark(npchar);
					dialog.text = "Selam, kaptan. Neden flütümün yanına geldin?";
					link.l1 = "İyi günler, Bay Keller. Kendimi tanıtmama izin verin - "+GetFullName(pchar)+". Senden alışılmadık bir konuda yardım istemeye geldim.";
					link.l1.go = "Keller_1";
					break;
					//Голландский гамбит
				}
				// belamour рыбацкое судно -->
				if(npchar.id == "FishingBoatCap")
				{
					if(!CheckAttribute(pchar, "GenQuest.FishingBoatSecondTime"))
					{
						Dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Ben   kaptanıyım "+GetFullName(NPChar)+" . Gemime ne vesileyle geldiniz?";
						link.l1 = "Size de iyi günler. Bu koya ne getirdi sizi?";
						link.l1.go = "FishingBoat";
						break;
					}
					else
					{
						Diag.CurrentNode = "first time";
						dialog.text = "Başka bir şey konuşmak ister misiniz?";
						link.l1 = "İstedim"+GetSexPhrase("","")+" takımadadan en son haberleri öğrenmek için. ";
						link.l1.go = "rumours_capitan";
						if(CheckAttribute(pchar,"GenQuest.FishingBoatDialogEnb"))
						{
							link.l2 = "Tekrar gösterir misin lütfen, ne tür ıvır zıvırların var satılık. ";
							link.l2.go = "Торговля";
							if(pchar.GenQuest.FishingBoatDialogEnb != "no special goods")
							{
								link.l3 = "Hmm, ambarı biraz daha kurcala – belki satacak bir şeyler bulursun?";
								link.l3.go = "Особые товары";
							}
						}
						link.l4 = "Özel bir şey yok, sadece seni selamlamaya geldim!";
						link.l4.go = "exit";	
						break;
					}
				}
				// <-- рыбацкое судно
				
				//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
				// генерал губернатор
				if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
				{
					Dialog.text = "Genel Vali, Ekselansları, selamlar! Size nasıl yardımcı olabilirim?";
					link.l1 = "Sana bir işim var!";
					link.l1.go = "quests";
					link.l2 = "Özel bir şey yok, sadece selam vermeye geldim!";
					link.l2.go = "exit";
					break;
				}
				// вице адмирал
				if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
				{
					Dialog.text = "Gemime hoş geldiniz, Amiral Yardımcısı! Size nasıl yardımcı olabilirim?";
					link.l1 = "Sana bir işim var!";
					link.l1.go = "quests";
					link.l2 = "Özel bir şey yok, sadece seni selamlamaya geldim!";
					link.l2.go = "exit";
					break;
				}
				// Офицер с патентом
				if(IsOfficerFullEquip() && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
				{
					Dialog.text = "Sizi burada görmek güzel, Kaptan! Size nasıl yardımcı olabilirim?";
					link.l1 = "Sana bir işim var!";
					link.l1.go = "quests";
					link.l2 = "Özel bir şey yok, sadece selam vermeye geldim!";
					link.l2.go = "exit";
					break;
				}			
				// <-- legendary edition
                if (CheckAttribute(NPChar, "EncType")  && NPChar.EncType == "war")
                {
    			    Dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Ben "+GetFullName(NPChar)+" -   bir geminin kaptanı "+NationKingsName(NPChar)+". filo. Seni gemime ne getirdi?";
    			}
    			else
                {
    			    Dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Ben kaptanım "+GetFullName(NPChar)+". Seni gemime ne getirdi?";
    			}
    			link.l1 = "Benim adım "+GetFullName(Pchar)+". Sizinle bir işim var!";
    			link.l1.go = "quests";
                link.l2 = "Ah, hiçbir şey, sadece "+GetSexPhrase("geldi","geldi")+" seni selamlamak için!";
    			link.l2.go = "exit";
            }
            else
            {
                Dialog.text = "Fark etmedin mi, , "+GetAddress_Form(NPChar)+", şu anda bir savaşın içindeyiz? Konuşmanın sırası mı şimdi!";
    			link.l1 = "Kesinlikle katılıyorum! Gemime döneceğim.";
    			link.l1.go = "exit";
            }
			Diag.TempNode = "first time";
 		break;

        case "quests":
			// belamour рыбацкое судно -->
			if(npchar.id == "FishingBoatCap")
			{
				if(!CheckAttribute(pchar, "GenQuest.FishingBoatSecondTime"))
				{
					Dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Ben   kaptanıyım "+GetFullName(NPChar)+". Gemime ne vesileyle geldiniz?";
					link.l1 = "Ve sana da iyi günler. Bu körfezde ne yapıyorsun?";
					link.l1.go = "FishingBoat";
					break;
				}
				else
				{
					dialog.text = "Başka konuşmak istediğiniz bir şey var mı?";
					link.l1 = "İstedim"+GetSexPhrase("","")+" takımadadan en son haberleri öğrenmek için. ";
					link.l1.go = "rumours_capitan";
					if(CheckAttribute(pchar,"GenQuest.FishingBoatDialogEnb"))
					{
						link.l2 = "Lütfen tekrar gösterir misin, ne tür ıvır zıvırların var satılık. ";
						link.l2.go = "Торговля";
						if(pchar.GenQuest.FishingBoatDialogEnb != "no special goods")
						{
							link.l3 = "Hmm, ambarı biraz daha kurcala – belki satacak bir şeyler bulursun?";
							link.l3.go = "Особые товары";
						}
					}
					link.l4 = "Özel bir şey yok, sadece merhaba demeye geldim!";
					link.l4.go = "exit";	
					break;
				}
			}
			// <-- рыбацкое судно
            if (!CheckAttribute(NPChar, "MainCaptanId")  || NPChar.MainCaptanId == pchar.GenQuest.CaptainId)
            {
                Dialog.text = "Seni büyük bir dikkatle dinliyorum,  "+GetAddress_Form(NPChar)+".";
                link.l1 = "Takımadadan en son haberleri duymak istiyorum.";
                //homo 25/06/06
                link.l1.go = "rumours_capitan";
                //belamour legendary edition 
				bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
				bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
				bOk = bOk1 || bOk2;
                if (CheckAttribute(NPChar, "EncGroupName") && !bOk) // только для фантомов грабеж
                {
                    iCapBattleDifficulty = CalcBattleDifficulty();
                    link.l2 = "(Gözdağı verme şansı: "+iCapBattleDifficulty+"%%) "+RandPhraseSimple("Benim kim olduğumu biliyor musun? Toplarım senin tekneni delik deşik edebilir, bu açık. Gel, işi tatlıya bağlayalım. Bir fidye bana gayet yeter.","Gördün mü? Tam burada, açık denizde... Ne dersin, adamlarımın keyfi yerinde kalsın diye küçük bir bağışta bulunsan? Sadece senin adamlarının güvenliği için.");
                    link.l2.go = "Talk_board";
                }
                if (CheckAttribute(NPChar, "Ship.Mode") && NPChar.Ship.Mode == "Trade")
                {
	           		link.l3 = "Nereden geliyorsun?";
	    			link.l3.go = "price_1";
	    			link.l4 = "Ticaret yapmak ister misin?";
	    			link.l4.go = "Trade_1";
    			}
				//--> квест мэра, поиски пирата
				if (CheckAttribute(pchar, "GenQuest.DestroyPirate"))
				{
	    			link.l6 = "Bu sularda dolaşan bir korsan gemisi arıyorum. Şüpheli bir şey gördünüz mü?";
	    			link.l6.go = "MQ_step_1";
				}
				//<-- квест мэра, поиски пирата
    			link.l5 = "Biraz rahatlamak ister misin?";
			    link.l5.go = "Play_Game";
                link.l9 = "Sanırım gitmeliyim.";
    			link.l9.go = "exit";
			}
			else
			{
                Dialog.text = "Sizinle ilgilenmeye yetkim yok. Filomuzun komutanıyla konuşun. Adı  "+GetFullName(characterFromID(NPChar.MainCaptanId))+", onu   şurada bulabilirsin "+XI_ConvertString(RealShips[sti(characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Type)].BaseName)+" '"+characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Name+"'.";
                link.l1 = "Teşekkür ederim. Dediğiniz gibi yapacağım.";
                link.l1.go = "exit";
                Diag.TempNode = "Go_away_Good";
			}
        break;
        case "Trade_1":
			dialog.text = "Neden olmasın?";
			link.l1 = "Hadi gidip mallara bir bakalım.";
			link.l1.go = "Trade_2";
			link.l2 = "Fikrimi değiştirdim.";
			link.l2.go = "exit";
		break;
		
		case "Trade_2":
            Partition_GetCargoCostCoeff("after");
			FillShipStore(NPChar);
	    	pchar.shiptrade.character = NPChar.id;
   			Diag.CurrentNode = Diag.TempNode;
		    DialogExit();
		    DeleteAttribute(pchar, "PriceList.StoreManIdx"); // не вести лог по кораблям
		    LaunchStore(SHIP_STORE);
		break;
		
        case "Play_Game":
			dialog.text = "Ne öneriyorsun?";
			link.l1 = "Gerçek parayla kart oynamak ister misin?";
			link.l1.go = "Card_Game";
   			link.l2 = "Poker joker'da biraz zar atmaya ne dersin?";
			link.l2.go = "Dice_Game";
			link.l10 = "Üzgünüm, ama ilgilenmem gereken bazı işlerim var.";
			link.l10.go = "exit";
		break;
        // карты -->
        case "Card_Game":
            if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
            {
                SetNPCQuestDate(npchar, "Card_date_Yet");
                dialog.text = "Üçkağıtçılarla kumar oynamam!";
    			link.l1 = "Nasıl istersen.";
    			link.l1.go = "exit";
			}
			else
			{
                dialog.text = "Neden olmasın? Açıkçası, biraz ara vermek hiç fena olmazdı...";
    			link.l1 = "Mükemmel.";
    			link.l1.go = "Cards_begin";
    			link.l2 = "Kurallar neler?";
    			link.l2.go = "Cards_Rule";
			}
		break;

		case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "Pekala, o zaman başlayalım!";
			link.l1.go = "Cards_begin";
			link.l3 = "Hayır, bu bana göre değil...";
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			Dialog.text = "Önce bahiste anlaşalım.";
			link.l1 = "100 peso için oynayalım.";
			link.l1.go = "Cards_Node_100";
			link.l2 = "500 peso için oynayalım.";
			link.l2.go = "Cards_Node_500";
			link.l3 = "Sanırım gitmeliyim.";
			link.l3.go = "exit";
		break;

		case "Cards_Node_100":
		    if (sti(pchar.Money) < 300)
		    {
                dialog.text = "Şaka mı yapıyorsun, ne? Hiç paran yok!";
                link.l1 = "Olur böyle şeyler.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = "Pekala, bu kadar yeter, yoksa gemiyi idare etmeye yetecek param kalmayacak...";
                link.l1 = "Yazık.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Pekala, 100 altına oynayalım.";
			link.l1 = "Hadi başlayalım!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 100;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_Node_500":
		    if (sti(pchar.Money) < 1500)
		    {
                dialog.text = "Şaka mı yapıyorsun? 1.500 peso paran yok ki!";
                link.l1 = "Onları bulacağım!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = "Hayır, bu bahisler kesinlikle sonum olacak.";
                link.l1 = "Dediğiniz gibi.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Pekâlâ, 500 altına oynayalım.";
			link.l1 = "Hadi başlayalım!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 500;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_begin_go":
            Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // карты <--
	    //  Dice -->
        case "Dice_Game":
            if (!CheckNPCQuestDate(npchar, "Dice_date_Yet") || isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
            {
                SetNPCQuestDate(npchar, "Dice_date_Yet");
                dialog.text = "Üçkağıtçılarla kumar oynamam!";
    			link.l1 = "Nasıl istersen.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
				{
					dialog.text = "Neden olmasın! Rahatlamak her zaman sağlığın için iyidir... ama cüzdanın için her zaman öyle değil...";
	    			link.l1 = "Mükemmel.";
	    			link.l1.go = "Dice_begin";
	    			link.l2 = "Oyunumuzun kuralları neler?";
	    			link.l2.go = "Dice_Rule";
    			}
    			else
    			{
					dialog.text = "Hayır, bugünlük bu kadar. Yapacak işlerim var.";
	    			link.l1 = "Nasıl istersen.";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Dice_Rule":
   			dialog.text = DICE_RULE;
			link.l1 = "Pekala, o zaman başlayalım!";
			link.l1.go = "Dice_begin";
			link.l3 = "Hayır, bu bana göre değil...";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			Dialog.text = "Önce bahiste anlaşalım.";
			link.l1 = "50 peso için oynayalım.";
			link.l1.go = "Dice_Node_100";
			link.l2 = "200 peso için oynayalım.";
			link.l2.go = "Dice_Node_500";
			link.l3 = "Sanırım gitmeliyim.";
			link.l3.go = "exit";
		break;

		case "Dice_Node_100":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckDiceGameSmallRate() && !bOk)
		    {
                dialog.text = "Sen bir    olarak iyi tanınıyorsun"+GetSexPhrase("hileci","hileci")+".. Seninle asla zar atmam.";
                link.l1 = "Hepsi yalan! Peki, öyle olsun.";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 300)
		    {
                dialog.text = "Şaka mı yapıyorsun, ne? Paran yok ki!";
                link.l1 = "Olur böyle şeyler.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = "Yeter artık! Kumar oynamayı bırakıyorum - yoksa beni dolandırıcı diye damgalayıp gemiden atacaklar.";
                link.l1 = "Yazık.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Pekala, 50 altına oynayalım.";
			link.l1 = "Hadi başlayalım!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 50;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_Node_500":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckDiceGameSmallRate() && !bOk)
		    {
                dialog.text = "Sen   herkesçe   bir   olarak   biliniyorsun"+GetSexPhrase("hileci","hileci")+". Seninle asla zar atmam.";
                link.l1 = "Hepsi yalan! Peki, öyle olsun.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckDiceGameBigRate())
		    {
                dialog.text = "Senin iyi bir oyuncu olduğunu duydum. Seninle yüksek bahis oynamam.";
                link.l1 = "Bahsi biraz düşürelim mi, ne dersin?";
			    link.l1.go = "Dice_Node_100";
				link.l2 = "Üzgünüm, ama gitmem gerekiyor.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 1500)
		    {
                dialog.text = "Şaka mı yapıyorsun? 1.500 peso yok ki sende!";
                link.l1 = "Onları bulacağım!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = "Hayır, bu bahisler kesinlikle sonumu getirecek.";
                link.l1 = "Nasıl istersen.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Pekâlâ, 200 altına oynayalım.";
			link.l1 = "Hadi başlayalım!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 200;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_begin_go":
            SetNPCQuestDate(npchar, "Dice_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // Dice <--
        case "price_1":
			if (CheckNPCQuestDate(npchar, "trade_date"))
			{
                SetNPCQuestDate(npchar, "trade_date");
				iMoney = findPriceStoreMan(NPChar);
	            if (iMoney == -1)
	            {
	                Dialog.Text = "Neden bilmek istiyorsun? Bu benim özel meselem.";
					Link.l1 = "Dediğiniz gibi.";
					Link.l1.go = "exit";
	            }
	            else
	            {
                    sld = &Characters[iMoney];
                    pchar.PriceList.ShipStoreIdx = iMoney;
                    
					Dialog.Text = "Ben   şehirden   geliyorum"+GetCityName(sld.City)+".";
					Link.l1 = "Yerel dükkanda malların fiyatları nedir?";
					Link.l1.go = "price_2";
					Link.l9 = "Gitmeliyim.";
					Link.l9.go = "exit";
				}
			}
			else
			{
                Dialog.Text = "Sana zaten her şeyi anlattım. Boş yere beni rahatsız etme.";
				Link.l1 = "Evet, haklısın. Hoşça kal.";
				Link.l1.go = "exit";
            }
		break;
		
		case "price_2":
            sld = &Characters[sti(pchar.PriceList.ShipStoreIdx)];
			SetPriceListByStoreMan(&Colonies[FindColony(sld.City)]);
			Dialog.Text = "Buyurun... (fiyat listesini aldınız)..";
			Link.l1 = "Çok teşekkür ederim!";
			Link.l1.go = "exit";
			PlaySound("interface\important_item.wav");
		break;
		
        case "Talk_board":
            bOk = iCapBattleDifficulty > hrand(98);
            //if ((Group_GetCharactersNum(NPChar.EncGroupName) - Group_GetDeadCharactersNum(NPChar.EncGroupName)) > GetCompanionQuantity(PChar) && rand(11) > GetCharacterSkillToOld(PChar, SKILL_FORTUNE))
            if(!bOk && iCapBattleDifficulty <= 33)
            {
                Dialog.text = "Ha-ha! Güzel şaka. Özellikle de üstünlüğün bende olduğu bu durumda. Gemiye dön ve onunla birlikte bat.";
                link.l1 = "...";
                link.l1.go = "Boarding";
            }
            else
            {
                if(!bOk)
                {
                    Dialog.text = "Kaptan, pis işlerini gemimde yapmamalıydın. Ama sana merhamet göstereceğim ve gemine dönüp onunla birlikte boğulmana izin vereceğim.";
                    link.l1 = "Bugün kimin köpekbalıklarına yem olacağını göreceğiz!";
                    link.l1.go = "Boarding";
                }
                else
                {
                    if(iEncPow == -1) iEncPow = 0;
                    Pchar.GenQuest.MoneyForCaptureShip = (70 + hrand(60, "&CapSur"+NPChar.id)) * iEncPow;
					if(HasShipTrait(pchar, "trait14")) Pchar.GenQuest.MoneyForCaptureShip = makeint(sti(Pchar.GenQuest.MoneyForCaptureShip) * 1.35);
                    Dialog.text = RandSwear()+"Evet, senin rezilliklerini çok duydum. Öyle olsun, ama unutma "+XI_ConvertString(NationShortName(sti(NPChar.nation))+"hunter")+"Bunu cezasız bırakmam!";
                    link.l1 = "Mükemmel. Toplamda "+Pchar.GenQuest.MoneyForCaptureShip+" pesos bana yeter, "+GetAddress_FormToNPC(NPChar)+".";
                    link.l1.go = "Capture";
                    link.l2 = "Boşver, sadece şaka yapıyordum"+GetSexPhrase("","")+"!";
                    link.l2.go = "exit";
                }
            }
            // тут нужен учёт запрета повторного наезда
            Diag.TempNode = "Go_away";
			sld = characterFromId(pchar.GenQuest.CaptainId);
            sld.talk_date_Go_away =  lastspeakdate(); // boal злопамятность :)
        break;
		
		case "surrender1" :
			Diag.TempNode = "surrender_goaway";
            Dialog.Text = "Al bakalım - ve şimdi defol git!";
			Link.l1 = "Güzel! Sen de sağlıklı kal, dostum!";
			Link.l1.go = "exit";
			sld = characterFromId(pchar.GenQuest.CaptainId);
            sld.talk_date_Go_away = lastspeakdate();
			AddMoneyToCharacter(pchar, sti(Pchar.GenQuest.MoneyForCaptureShip));
			ChangeCharacterComplexReputation(pchar,"nobility", -2); 		
			ChangeCharacterComplexReputation(pchar,"authority", 1.0); 							
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			ChangeCharacterHunterScore(pchar, NationShortName(sti(NPChar.nation)) + "hunter", GetIntByCondition(HasShipTrait(pchar, "trait23"), 7 + rand(10), 3 + rand(5)));
		break;
		
		case "surrender_goaway":
			Dialog.Text = "Benden daha ne istiyorsun?";
			Link.l1 = "Hiçbir şey.";
			Link.l1.go = "exit";
			Diag.TempNode = "surrender_goaway";
		break;
		
		case "surrender2":			
			dialog.text = "Görünüşe göre sana boyun eğmekten başka çarem yok.";
			link.l1 = "Yoluna devam et, hadi!";
			link.l1.go = "surrender3";				
		break;
						
		case "surrender3":
			Diag.TempNode = "surrender_goaway";
			sld = characterFromId(pchar.GenQuest.CaptainId);
            sld.talk_date_Go_away = lastspeakdate();
			DialogExit(); 
			LaunchTransferMain(pchar, sld, "Transfer");
		break;
				
        case "rumours":
			Dialog.Text = SelectRumour(); // to_do
			Link.l1 = RandPhraseSimple(RandSwear()+"Bu çok ilginç. Başka bir sorunuz var mı?","Sadece başka bir mesele.");
			Link.l1.go = "quests";
			Link.l2 = RandPhraseSimple("Teşekkür ederim, artık gitmeliyim.","Her şey gönlünce olsun.");
			Link.l2.go = "exit";
			Diag.TempNode = "quests";
		break;
		
		case "Go_away":
			Dialog.Text = "Gemimden defol!";
			Link.l1 = "Zaten gidiyorum.";
			Link.l1.go = "exit";
			Diag.TempNode = "Go_away";
		break;
		
		case "Go_away_Good":
			Dialog.Text = "Konuşmamız bitti. Sana yeni bir şey söylemeyeceğim "+GetAddress_Form(NPChar)+".";
			Link.l1 = "Pekala. Denizde görüşürüz!";
			Link.l1.go = "exit";
			Diag.TempNode = "Go_away_Good";
		break;

        case "Capture":
            Diag.TempNode = "Go_away";
            Dialog.Text = "Al bakalım - ve şimdi defol!";
			Link.l1 = "Güzel!";
			Link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(Pchar.GenQuest.MoneyForCaptureShip));
			ChangeCharacterComplexReputation(pchar,"nobility", -5);			
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			ChangeCharacterHunterScore(pchar, NationShortName(sti(NPChar.nation)) + "hunter", GetIntByCondition(HasShipTrait(pchar, "trait23"), 7 + rand(10), 3 + rand(5)));
        break;

        case "Boarding":
            if (CheckAttribute(NPChar, "MainCaptanId"))
            {
                PChar.StartBattleAfterDeck = true;
                PChar.StartBattleMainCaptanId = NPChar.MainCaptanId;
                PChar.StartBattleEncGroupName = NPChar.EncGroupName;
            }
            DialogExit();
            Diag.CurrentNode = Diag.TempNode;
        break;
        
        case "QuestAboardCabinDialog":  // тестовый диалог, в игре не работает, для метода SetQuestAboardCabinDialog
			Diag.TempNode = "QuestAboardCabinDialog";
            Dialog.Text = "Dur biraz, bu şekilde beni öldürebilirsin. Benden ne istiyorsun?";
			Link.l1 = "Seni öldürmek için!";
			Link.l1.go = "QuestAboardCabinDialog_1";
			Link.l2 = "Teslim ol!";
			Link.l2.go = "QuestAboardCabinDialog_2";
			Link.l3 = "Haritayı ver bize, Billy (c)";  // предмет, далее не ясно или  QuestAboardCabinDialog_1 или QuestAboardCabinDialog_2
			Link.l3.go = "QuestAboardCabinDialog_3";  // можно закодить покидание корабля, но экипаж уже вырезан и тп...
        break;
        
        case "QuestAboardCabinDialog_1":
			Dialog.Text = "Pekâlâ, göreceğiz, alçak herif!";
			Link.l1 = "Ve ben ne görmem gerekiyor?";
			Link.l1.go = "exit";
			// тут можно восстановить НР противника (NPChar) или добавить парочку гардов против ГГ
			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattle"); // тут ругань обратно
		break;
		
		case "QuestAboardCabinDialog_2":
			Dialog.Text = "Pekala, kazandın!";
			Link.l1 = "Akıllıca bir karar!";
			Link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestAboardCabinDialogSurrender");
		break;
		
		case "QuestAboardCabinDialog_3":
			Dialog.Text = "Umarım boğazında kalır!";
			Link.l1 = "Çok iyi, zincirlerini tak ve çeneni kapa, mahkum.";
			if (rand(1) == 1)  // пример!!!
			{
				Link.l1.go = "QuestAboardCabinDialog_2";
			}
			else
			{
			    Link.l1.go = "QuestAboardCabinDialog_3_1";
			}
			TakeNItems(NPChar, "Chest", -1);
			TakeNItems(pchar, "Chest", 1);
		break;
		
		case "QuestAboardCabinDialog_3_1":
			Dialog.Text = ""+GetSexPhrase("Geldim","Geldim")+", ortalığı dağıttı"+GetSexPhrase("","")+", ve her şeyi aldı"+GetSexPhrase("","")+", şimdi de beni köle mi yapmak istiyorsun? Asla!";
			Link.l1 = "O halde ölmeye hazırlan.";
			Link.l1.go = "QuestAboardCabinDialog_1";
		break;
		//eddy. квест мэра, поиски пирата
		case "MQ_step_1":
			Dialog.Text = "Hayır, korsanlara benzeyen şüpheli bir gemi görmedim.";
			Link.l1 = "Anladım.";
			Link.l1.go = "exit";
		break;
		
		//homo Наводка на купца
		case "MerchantTrap_Abordage":

			Dialog.Text = "Adına "+NationKingsName(NPChar)+" teslim ol, "+GetSexPhrase("pislik korsan","pislik kadın!")+"! O zaman hayatın adil bir mahkemeye kadar bağışlanacak, orada her şey için yargılanacaksın "+NationNameSK(sti(NPChar.nation))+"yağmaladığın gemiler"+GetSexPhrase("","")+".";
			Link.l1 = "Siktir git! Teslim olmalısın!";
			Link.l1.go = "exit";
			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattleNoParam"); // тут ругань обратно
		break;
		
		case "Siegehelp":		
            ref rchar = Group_GetGroupCommander(sGroup);
            if (NPChar.id == rchar.id)
            {
    			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
				{
					dialog.text = "Sayın Valim, Genel Vali! Sizi dikkatle dinliyorum, fakat lütfen kısa tutun: şu anda savaş halindeyiz "+fort+", ve savaşın gidişatını yönlendirmem gerekiyor.";
				}
				else
				{
					if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
					{
						dialog.text = "Amiral Yardımcısı! Sizi dikkatle dinliyorum, fakat vaktim az: şu anda savaş halindeyiz "+fort+", ve savaşın gidişatını yönlendirmem gerekiyor.";
					}
					else
					{
						dialog.text = "Seni dinliyorum, ama ziyaretinin amacına hızlıca gelelim, çünkü şu anda savaş halindeyiz "+fort+", ve savaşın komutasını devralmam gerekiyor.";
					}
				}
                link.l1 = "İşte bu yüzden buradayım,  "+GetAddress_FormToNPC(NPChar)+".";
                link.l1.go = "attack_fort";

                link.l2 = "Öyleyse daha fazla vaktinizi almayayım. Hoşça kalın, "+GetAddress_FormToNPC(NPChar)+".";
                link.l2.go = "exit";
    			
            }
            else
            {
                Dialog.text = "Sizinle ilgilenmeye yetkim yok. Filomuzun komutanıyla konuşun. Adı  "+GetFullName(rchar)+", onu şurada bulabilirsin: "+XI_ConvertString(RealShips[sti(rchar.Ship.Type)].BaseName)+" ''"+rchar.Ship.Name+"''.";
                link.l1 = "Teşekkür ederim. Dediğiniz gibi yapacağım.";
                link.l1.go = "exit";
            
            }
            Diag.TempNode = "Siegehelp";
            
		break;
		
		case "attack_fort":
                dialog.text = "Ne demek istiyorsun?";
                link.l1 = "Sömürge kalesini yerle bir etmenize yardımcı olabilirim "+GetCityName(aData.Colony)+" ve şehri ele geçirip ganimetleri alacağız, eğer başarılı olursak, aramızda paylaşacağız.";
                link.l1.go = "Siegehelp_1";
                link.l2 = "Aslında, işim sizin zamanınıza değmez. Hoşça kalın, "+GetAddress_FormToNPC(NPChar)+".";
                link.l2.go = "exit";
                Diag.TempNode = "Siegehelp_0";
		break;
		
		case "Siegehelp_0":
            Dialog.text = "Yine sen mi? Her şeyi zaten konuştuğumuzu sanıyordum.";
            link.l1 = "Haklısın. Sanırım unuttum"+GetSexPhrase("","")+".";
			link.l1.go = "exit";
			NPChar.DeckDialogNode = "Siegehelp_0";
            Diag.TempNode = "Siegehelp_0";

		break;
		
		case "Siegehelp_1":
            SiegeResult("");
			// belamour legendary edition
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE;
			bOk = bOk1 || bOk2;
            if (sti(aData.win)==0 || bOk)
            {
                dialog.text = "Ve ganimetten ne kadar pay almayı bekliyorsun?";
                link.l1 = "Yarısı.";
                link.l1.go = "Big_part";
                link.l2 = "Üçte bir.";
                link.l2.go = "Middle_part";
                link.l3 = "Bir çeyrek.";
                link.l3.go = "Small_part";
            }
            else
            {
                dialog.text = "Senin hizmetlerine ihtiyacım yok, kaptan! Bu koloniyi kendim ele geçireceğim ve bunun için yardıma ihtiyacım yok.";
                link.l1 = "Neden bu kadar eminsin, "+GetAddress_FormToNPC(NPChar)+", herkesin başına talihsizlik gelebilir.";
                link.l1.go = "attack_fort_03";
                link.l2 = "Bu durumda, daha fazla vaktinizi almayayım, "+GetAddress_FormToNPC(NPChar)+". Elveda!";
                link.l2.go = "exit";
            }
			Diag.TempNode = "Siegehelp_0";

		break;
		
		case "attack_fort_03":
            if((sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) < 4000)
            {
                dialog.text = "Öte yandan, gemilerim bu savaşta epey hasar aldı ve takviye kuvvetler kesinlikle iyi olurdu. Eğer kabul ederseniz "+GetPart(4)+" , o zaman sanırım bir anlaşmaya varabiliriz.";
                link.l1 = "Bu bana uyar, "+GetAddress_FormToNPC(NPChar)+". Kaleye saldırmaya çalışacağım, siz de geminizin toplarıyla bize destek olacaksınız.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 4;
                link.l2 = "O kadar ucuz değilim, "+GetAddress_FormToNPC(NPChar)+". Rahatsızlık verdiğim için üzgünüm"+GetSexPhrase("","")+" seni meşgul eden işlerinden alıkoymayayım. Hoşça kal!";
                link.l2.go = "exit";
            }else{
                dialog.text = "Filo­mda bu kaleyi toza çevirecek kadar gemi var – bu sadece zaman meselesi. Ve şimdi, lütfen gemimden iner misiniz? Zafer beni bekliyor!";
                link.l1 = "Peki, o zaman, "+GetAddress_FormToNPC(NPChar)+", müsaadenizle ayrılıyorum. Hoşça kalın!";
                link.l1.go = "exit";
            }
		    Diag.TempNode = "Siegehelp_0";
		break;
		case "Big_part":
            if( (sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) <= -1500)
            {
                dialog.text = "Kaledeki toplar gemilerime ağır hasar verdi, ve yaklaşan savaşta kaybeden taraf olabiliriz. Yardımını kabul ediyorum ve şartlarını onaylıyorum.";
                link.l1 = "Harika, "+GetAddress_FormToNPC(NPChar)+" , o halde kaleye saldırmaya çalışacağız ve siz de geminizin toplarıyla bize destek olacaksınız.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 2;
            }
            else
            {
				// belamour legendary edition
				bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);
				bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE;
				bOk = bOk1 || bOk2;
				if(bOk)
				{
					dialog.text = "Ekselansları, operasyonun ilerleyişi hakkında hâlâ rapor vermem gerekiyor... En azından izin verin "+GetPart(4)+".";
				}
				else
				{
                dialog.text = "Fazla değil mi, kaptan? Sizde zaten "+GetNumShips(GetCompanionQuantity(PChar))+", ve filomun "+GetNumShips(Group_GetCharactersNum(sGroup))+". Sana sunabileceğim "+GetPart(4)+". Ve bunu adil say.";
				}
                aData.PartAttaksFort = 4;
                link.l1 = "Kabul ediyorum"+GetSexPhrase("","")+", "+GetAddress_FormToNPC(NPChar)+" , o halde kaleye saldıracağım ve siz de geminizin toplarıyla bize destek olacaksınız.";
                link.l1.go = "attack_fort_04";
                link.l2 = "Maalesef, sanmıyorum, "+GetAddress_FormToNPC(NPChar)+". Konuşacak başka bir şey yok. Hoşça kal.";
                link.l2.go = "exit";
            }
            Diag.TempNode = "Siegehelp_0";
        break;
        
        case "attack_fort_04":
            dialog.text = "Kale ele geçirilir geçirilmez, sahile çıkarma birlikleri göndermeye başlayacağız, ardından da kasabanın içinde savaşmaya devam edeceğiz. Orada sizinle buluşmayı umuyorum.";
            link.l1 = "O halde. Yakında görüşürüz, "+GetAddress_FormToNPC(NPChar)+"!";
            link.l1.go = "exit";
            Diag.TempNode = "Siegehelp_0";
            PChar.quest.Union_with_Escadra = "Yes";
        break;

        case "Middle_part":
            if((sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) <= -600)
            {
                dialog.text = "Sanırım şartlarını kabul edeceğim. Ortak bir operasyon bu savaşı kazanmamı kolaylaştırır. Her şey planlandığı gibi giderse, ganimetten payını alacaksın.";
                link.l1 = "Anlaşmaya vardığımıza sevindim, "+GetAddress_FormToNPC(NPChar)+". Adamlarıma kaleye hemen saldırmalarını emredeceğim.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 3;
            }else{
				// belamour legendary edition
				bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);
				bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE;
				bOk = bOk1 || bOk2;
				if(bOk)
				{
					dialog.text = "Ekselansları, operasyonun ilerleyişi hakkında hâlâ rapor vermem gerekiyor... En azından izin verin "+GetPart(4)+".";
				}
				else
				{
                dialog.text = "Fazla değil mi, kaptan? Sizde "+GetNumShips(GetCompanionQuantity(PChar))+", ve filomun "+GetNumShips(Group_GetCharactersNum(sGroup))+". Sana sunabileceğim şey şu "+GetPart(4)+". Ve bunu adil say.";
				}
                link.l1 = "Ben "+GetSexPhrase("kabul et","kabul et")+", "+GetAddress_FormToNPC(NPChar)+" , o halde ben kaleye saldıracağım, siz de geminizin toplarıyla bize destek olacaksınız.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 4;
                link.l2 = "Maalesef, sanmıyorum. "+GetAddress_FormToNPC(NPChar)+". Konuşacak başka bir şey yok. Hoşça kal.";
                link.l2.go = "exit";
            }
            Diag.TempNode = "Siegehelp_0";
        break;

        case "Small_part":
            dialog.text = "Gemilerim yorgun, ve böyle bir durumda her takviye kuvvet memnuniyetle karşılanır. Yardımını kabul ediyorum ve şartlarını kabul ediyorum.";
            link.l1 = "Memnun oldum"+GetSexPhrase("","")+", "+GetAddress_FormToNPC(NPChar)+".. Adamlarıma hemen kaleye saldırmaları için emir vereceğim.";
            link.l1.go = "attack_fort_04";
            aData.PartAttaksFort = 4;
            Diag.TempNode = "Siegehelp_0";
        break;
		
		case "Talk_Capture_City":
            AfterTownBattle();  // все, все свободны
            LAi_LoginInCaptureTown(NPChar, false);
            aData.win = 1;
            EndOfTheSiege("End");
            NPChar.location = "";
            int ilt = makeint(sti(aData.loot)/sti(aData.PartAttaksFort));
            dialog.text = "Merhaba, kaptan! Gerçekten de zorlu bir savaştı ama kasabanın savunucularının şiddetli direnişini kırmayı başardık. Yağmaladık "+sti(aData.loot)+" peso. Anlaşmamıza göre, senin payın "+ilt+". Please accept this money; you certainly deserve every last coin of it. And now please excuse me, but I must return to my business.";
            link.l1 = "O halde seni burada bırakıyorum, "+GetAddress_FormToNPC(NPChar)+". Elveda!";
            link.l1.go = "exit";
            //AddDialogExitQuest("End_Siege_and_Attaks_City");

            Diag.TempNode = "no_return_02";
            AddMoneyToCharacter(PChar, ilt);
            ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
            ChangeCharacterComplexReputation(PChar,"nobility", 10);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 80);
            AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Defence", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Fortune", 80);
            aData.loot = sti(aData.loot) - ilt;
            if (CheckAttribute(PChar, "quest.LeaveTown")) Pchar.quest.LeaveTown.over = "yes";
            //--> слухи
            SiegeRumour("I've been told that you had helped our squadron in the assault of the "+NationNameSK(sti(aData.conation))+" colony - "+GetCityName(aData.Colony)+"! We're so thankfull to you, "+ GetAddress_Form(NPChar)+".", "", sti(aData.nation), -1, 30, 3);
            //<-- слухи
		break;

        case "no_return_02":
            dialog.text = "Kaptan, benimle bir işiniz mi var?";
            link.l1 = "Hayır, "+GetAddress_FormToNPC(NPChar)+". Hoşça kal!";
            link.l1.go = "exit";
            Diag.TempNode = "no_return_02";
		break;
		
		case "GoldSquadron":
            ref rch = Group_GetGroupCommander("Sea_Head_of_Gold_Squadron");
            if (NPChar.id == rch.id)
            {
    			dialog.text = "Sizi dinliyorum, ama lütfen ziyaretinizin amacını çabucak söyleyin, fazla vaktim yok. Önemli ve gizli bir görevdeyim, ve konvoyumuz için tehdit oluşturabilecek şüpheli gemileri açık denizde batırmam için emir aldım.";                          
                link.l1 = "Öyleyse daha fazla vaktinizi almayayım. İyi şanslar, "+GetAddress_FormToNPC(NPChar)+".";
                link.l1.go = "exit";

            }
            else
            {
                Dialog.text = "Sizinle konuşmaya yetkim yok. Filomuzun komutanıyla konuşun. Adı "+GetFullName(rch)+", onu şurada bulabilirsin: "+XI_ConvertString(RealShips[sti(rch.Ship.Type)].BaseName)+" ''"+rch.Ship.Name+"''.";
                link.l1 = "Teşekkürler. Dediğin gibi yapacağım.";
                link.l1.go = "exit";

            }
            Diag.TempNode = "GoldSquadron";
		break;
		
		case "WM_Captain":
			dialog.text = "Tanıştığımıza memnun oldum, benim adım "+GetFullName(npchar)+"Yani bize yardım etmeye geldiniz? O halde özellikle memnun oldum, çünkü şu anki durumumuz gerçekten kritik - ıssız bir adanın kıyısında yapayalnızız, gemimiz zar zor yüzüyor ve mürettebatımız ağır kayıplar verdi...";
			link.l1 = "Duyduğuma göre korsanlarla savaşmışsın, sonra da o fırtına çıkmış...";
			link.l1.go = "WM_Captain_1";
			pchar.quest.DesIsland_Over.over = "yes";//снять прерывание
		break;
		
		case "WM_Captain_1":
			dialog.text = "Doğru. Gemim savaşta ağır hasar aldı – o korsan alçakların başlattığı bir bordalama saldırısına bile karşı koymak zorunda kaldık. Sonra bir fırtınaya yakalandık... ah, bunu hatırlamak bile istemiyorum. Bizi bu ıssız kıyıya sürükledi. Bütün gün Fıtrî Meryem Ana'ya dua ettik, fırtınadan kurtulalım, demir zincirlerimiz kopmasın diye\nVe işte buradayız. Bir haftadır gemimizi onarıyoruz, ama kendin gör: sadece elli adam kaldı ve tahtamız da yok – peki, onları nereden bulacağız? Ormandan mı? Elbette. Her gün var gücümüzle çalışıyoruz ama gereken malzemenin ancak beşte birini toplayabildik\nBöyle bir hasarla denize açılmak intihardan farksız. Şimdi burada halimizi görüyorsun kaptan...";
			link.l1 = "Evet... Durumun hiç de imrenilecek gibi değil. Ne yapabileceğimizi ve sana nasıl yardımcı olabileceğimi düşünelim.";
			link.l1.go = "WM_Captain_2";
		break;
		
		case "WM_Captain_2":
			dialog.text = "Ah, keşke yeterince tahta ve yelken bezi olsaydı - o zaman gemimizi bir haftada onarabilirdik\nKaptan, madem buraya özellikle geldiniz, belki en yakın limana gidip ihtiyacımız olan malzemeleri satın alabilirsiniz? O zaman sorunumuz çözülür. Parayı dert etmeyin, tüm masraflarınızı karşılayacağım.";
			link.l1 = "Elbette. Tam olarak ne teslim etmem gerekiyor ve ne kadar?";
			link.l1.go = "WM_Captain_3";
		break;
		
		case "WM_Captain_3":
			pchar.questTemp.WPU.Escort.Planks = 300 + hrand(5)*10;
			pchar.questTemp.WPU.Escort.Sailcloth = 150 + hrand(10)*10;
			pchar.questTemp.WPU.Escort.Linen = 70 + hrand(7)*10;
			dialog.text = "Ben zaten bunların hepsini çözdüm. Elimizdekileri göz önünde bulundurursak, ihtiyacım olan şey "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Planks))+" kalaslar, "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Sailcloth))+" yelken bezi ve "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Linen))+" pamuk. Bu malzemelerle gemiyi bir haftada onarıp tekrar denize açılabiliriz.";
			link.l1 = "Pekala. İhtiyacın olan tüm malzemeleri sana getireceğim. Beni bekle - en fazla on gün içinde döneceğim.";
			link.l1.go = "WM_Captain_4";
		break;
		
		case "WM_Captain_4":
			dialog.text = "Çok teşekkür ederim, kaptan! Bu içimi rahatlattı. Dönüşünüzü bekleyip sağ salim gelmeniz için dua edeceğiz!";
			link.l1 = "Merak etme. Yakında tamirat için ihtiyacın olan her şeye sahip olacaksın.";
			link.l1.go = "exit";
			AddQuestRecord("Escort", "27");
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			AddQuestUserData("Escort", "sIsland", XI_ConvertString("Colony"+pchar.questTemp.WPU.Current.TargetIslandID));
			AddQuestUserData("Escort", "sQty1", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Planks)));
			AddQuestUserData("Escort", "sQty2", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Sailcloth)));
			AddQuestUserData("Escort", "sQty3", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Linen)));
			Diag.TempNode = "WM_Captain_again";
			SetFunctionTimerCondition("WM_Captain_Over", 0, 0, 11, false);
			pchar.questTemp.WPU.Escort = "wait";
		break;
		
		case "WM_Captain_again":
			dialog.text = "Dönüşünüzü sabırsızlıkla bekleyeceğiz, kaptan!";
			link.l1 = "Demir alın!";
			link.l1.go = "exit";
			Diag.TempNode = "WM_Captain_again";
		break;
		
		case "WM_Captain_5":
			dialog.text = "Harika! Şimdi gemiyi onarmaya başlayabiliriz!";
			link.l1 = "Adamlarım sana yardım edecek - böylece daha hızlı olur. Ayrıca, seni koloniye kadar ben de götürmeliyim "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity)+", bu yüzden onarımları ne kadar çabuk bitirirsek, benim için o kadar iyi olur.";
			link.l1.go = "WM_Captain_6";
		break;
		
		case "WM_Captain_6":
			pchar.questTemp.WPU.Current.TargetIslandID.Shore = SelectQuestShoreLocationFromSea(pchar.questTemp.WPU.Current.TargetIslandID);
			dialog.text = "Gerçekten, size nasıl teşekkür edeceğimi bilemiyorum kaptan... Lütfen malzemelerin şu koyda boşaltılmasını emredin: "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore)+" - tamirler için her şeyimiz hazır.";
			link.l1 = "Pekâlâ. Kıyıda buluşacağız.";
			link.l1.go = "exit";
			AddQuestRecord("Escort", "29");
			AddQuestUserData("Escort", "sShore", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore+"Gen"));
			pchar.quest.DisasterShip_WMC.win_condition.l1 = "location";
			pchar.quest.DisasterShip_WMC.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID.Shore;
			pchar.quest.DisasterShip_WMC.function = "RepairShip_Prepare";
			Diag.TempNode = "WM_Captain_repeat";
		break;
		
		case "WM_Captain_repeat":
			dialog.text = "Onarımlara ne zaman başlayacağız, kaptan? Sizi kıyıda bekliyor olacağım.";
			link.l1 = "Evet, tabii ki. Şimdi gidiyorum.";
			link.l1.go = "exit";
			Diag.TempNode = "WM_Captain_repeat";
		break;
		
		case "Repair_start":
			dialog.text = "Pekâlâ, onarımlar için her şey hazır görünüyor. Sanırım yaklaşık beş güne kadar işimiz biter.";
			link.l1 = "Çok iyi! Zaten bu adayı keşfetmeyi düşünüyordum, böylece zamanı iyi değerlendireceğim.";
			link.l1.go = "Repair_start_1";
		break;
		
		case "Repair_start_1":
			DialogExit();
			pchar.quest.WM_Captain_Over.over = "yes";//снять прерывание
			sld = characterFromId("WMCaptain");
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			RemoveCharacterGoods(pchar, GOOD_PLANKS, sti(pchar.questTemp.WPU.Escort.Planks));
			RemoveCharacterGoods(pchar, GOOD_SAILCLOTH, sti(pchar.questTemp.WPU.Escort.Sailcloth));
			RemoveCharacterGoods(pchar, GOOD_COTTON, sti(pchar.questTemp.WPU.Escort.Linen));
			DoQuestFunctionDelay("RepairShip_WithoutMasts", 5.0);
		break;
		
		case "Repair_end":
			dialog.text = "Pekala, işte bu kadar. Tamiratı bitirdik ve gemi sefere hazır. Ne zaman yola çıkıyoruz, kaptan?";
			link.l1 = "Hazırsan, burada oyalanmanın anlamı yok. Demir alın!";
			link.l1.go = "Repair_end_1";
		break;
		
		case "Repair_end_1":
			DialogExit();
			sld = characterFromId("WMCaptain");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("Escort", "30");
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity));
			SetFunctionTimerCondition("DisasterShipWM_Over", 0, 0, 25, false);
			log_info("You have 25 days to escort "+pchar.questTemp.WPU.Escort.ShipBaseName+" '"+pchar.questTemp.WPU.Escort.ShipName+"' to the port of "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+"");
			pchar.quest.DisasterShip_final.win_condition.l1 = "location";
			pchar.quest.DisasterShip_final.win_condition.l1.location = pchar.questTemp.WPU.Escort.StartCity +"_town";
			pchar.quest.DisasterShip_final.function = "WMShip_final";
		break;
		
		case "WMShip_final":
			pchar.quest.Escort_fail.over = "yes";
			pchar.quest.DisasterShipWM_Over.over = "yes";//снимаем оба прерывания
			RemoveCharacterCompanion(Pchar, characterFromID("WMCaptain"));//удаляем компаньона
			pchar.questTemp.WPU.Escort.LevelUp_1Money = sti(pchar.questTemp.WPU.Escort.Planks)*15+sti(pchar.questTemp.WPU.Escort.Sailcloth)*9+sti(pchar.questTemp.WPU.Escort.Linen)*45;//деньги за материалы
			dialog.text = "Sana bir kez daha teşekkür etmek istiyorum kaptan - beni ve mürettebatımı o beladan kurtarmakta büyük yardımın dokundu. Söz verdiğim gibi, gemimi onarmak için gereken malzemelerin karşılığını ödeyeceğim. İşte "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+", lütfen, onları alın. Ve bu da size benim kişisel hediyem.";
			link.l1 = "Sana yardımcı olmaktan mutluluk duydum.";
			link.l1.go = "WMShip_final_1";
		break;
		
		case "WMShip_final_1":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.LevelUp_1Money));
			TakeNItems(pchar, "obereg_"+(hrand(10)+1), 1);
			dialog.text = "Ve şimdi, veda etme vakti kaptan. Liman idaresine uğramayı unutma - seni orada bekliyorlar. Görüşmek üzere!";
			link.l1 = "Güzel bir gün geçir, "+npchar.name+"!";
			link.l1.go = "WMShip_final_2";
		break;
		
		case "WMShip_final_2":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			DialogExit();
			sld = characterFromId("WMCaptain");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM")) AddQuestRecord("Escort", "31");
			if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1VSP")) AddQuestRecord("Escort", "37");
			if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1S")) AddQuestRecord("Escort", "40");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money)));
			AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		break;
		
		case "VSP_Captain":
			dialog.text = "Öyle mi? Ben de artık bizi unuttular sanıyordum. Evet, gemim en kötüsünü yaşadı. Fırtına korsanları kervanımıza saldırmaktan vazgeçmeye zorlayınca, biz de doğanın insafına kaldık. Bu elverişsiz kıyıya sürüklendik\nBirkaç gün boyunca tamirat yaptık ve dinlendik. Tam yelken açacakken, bu putperestler tekrar saldırdı\nVe sonra fırtına bir kez daha patladı—Rab sonunda işimizi bitirmeye karar verdi sandık, ama sonra sen geldin. Kutsal Meryem'e şükürler olsun! Sana da tekrar teşekkür ederim, kaptan!";
			link.l1 = "Her şey bitti, "+GetAddress_FormToNPC(NPChar)+". Şimdi sizi   götürmem gerekiyor "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+", onu daha fazla beladan korumak için. Artık gitmeye hazır mısın? Fırtına şimdiden dinmeye başladı.";
			link.l1.go = "VSP_Captain_1";
		break;
		
		case "VSP_Captain_1":
			dialog.text = "Elbette! Buradan ne kadar çabuk ayrılırsak, adamlarım o kadar rahatlayacak – zaten fazlasıyla acı çektiler. Hadi yelken açalım!";
			link.l1 = "Gemimi takip et - ve mürettebatını sakinleştir, artık korkacak bir şey yok.";
			link.l1.go = "VSP_Captain_2";
		break;
		
		case "VSP_Captain_2":
			pchar.quest.DisasterShip_GetOut.over = "yes";
			DialogExit();
			Group_DelCharacter("WMShip", "WMCaptain");//иначе будет клон
			sld = characterFromId("WMCaptain");
			LAi_SetImmortal(sld, false);
			SetCharacterRemovable(sld, false);
			sld.CompanionEnemyEnable = false; //всегда друзья
			SetCompanionIndex(pchar, -1, sti(sld.index));
			sld.loyality = MAX_LOYALITY;
			AddQuestRecord("Escort", "36");
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			SetFunctionTimerCondition("DisasterShipWM_Over", 0, 0, 25, false);
			log_info("You have 25 days to escort "+pchar.questTemp.WPU.Escort.ShipBaseName+" '"+pchar.questTemp.WPU.Escort.ShipName+"' to the port of"+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+"");
			pchar.questTemp.WPU.Escort = "win";
			pchar.quest.Escort_fail.win_condition.l1 = "NPC_Death";//прерывание на потопление сопровождаемого
			pchar.quest.Escort_fail.win_condition.l1.character = "WMCaptain";
			pchar.quest.Escort_fail.function = "DisasterShipWM_failed";
			pchar.quest.DisasterShip_final.win_condition.l1 = "location";
			pchar.quest.DisasterShip_final.win_condition.l1.location = pchar.questTemp.WPU.Escort.StartCity +"_town";
			pchar.quest.DisasterShip_final.function = "WMShip_final";
			Diag.currentnode = "VSP_Captain_again";
			Delete_EscortStorm();//уберем шторм
		break;
		
		case "VSP_Captain_again":
			dialog.text = "Yelken açalım mı, kaptan?";
			link.l1 = "Tabii. Şimdi gemime döneceğim.";
			link.l1.go = "exit";
			Diag.TempNode = "VSP_Captain_again";
		break;
		
		case "VSPShip_final":
			pchar.quest.Escort_fail.over = "yes";
			pchar.quest.DisasterShipWM_Over.over = "yes";//снимаем оба прерывания
			RemoveCharacterCompanion(Pchar, characterFromID("WMCaptain"));//удаляем компаньона
			pchar.questTemp.WPU.Escort.LevelUp_1Money = 10000+sti(pchar.rank)*200;
			dialog.text = "Sana bir kez daha teşekkür etmek istiyorum kaptan – bana ve mürettebatıma bu beladan kurtulmamızda büyük yardımın dokundu. İşte"+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+". Tüm mürettebat katkıda bulundu, bu yüzden sakın reddetmeyi düşünme. Ve bu da benim sana kişisel hediyem.";
			link.l1 = "Sana yardım etmekten mutluluk duydum!";
			link.l1.go = "WMShip_final_1";
		break;
		
		case "SShip_final":
			pchar.questTemp.WPU.Escort.LevelUp_1Money = 5000+sti(pchar.rank)*100;
			RemovePassenger(Pchar, npchar);//удаляем пассажира
			dialog.text = "Bir kez daha teşekkür etmek istiyorum, kaptan, bizi bu beladan kurtardığınız için. Buyurun, şu paraları kabul edin - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+"  ve işte, bu hediyeyi al. Çok büyük bir şey değil, ama yaptıkların için sana ancak bu kadar teşekkür edebilirim. Lütfen, bu teklifi geri çevirme\nEski tayfam sana ve Kızılderililerle, korsanlarla yaptığın savaşlara hayran kaldı. Hepsi sana katılmak istiyor. Gemilerini yeni kaybetmiş sadık denizcilerin hizmet teklifini geri çevirmeyeceğini umuyorum?";
			link.l1 = "Tabii ki hayır. Onu memnuniyetle saklarım. Sana yardım etmekten mutluluk duydum!";
			link.l1.go = "WMShip_final_1";
		break;
		
		//Голландский Гамбит
		case "Stivesant_1":
			DelLandQuestMark(npchar);
			dialog.text = "Pekâlâ. Ama, efendim, burada neler olduğunu açıklar mısınız? 'Meifeng'in komutasında nasıl siz varsınız! Longway'e bir şey mi oldu?";
			link.l1 = "İhtiyacın olan tüm açıklamalar bende var - ayrıca başka önemli bilgilerim de var.";
			link.l1.go = "Stivesant_2";			
		break;
		
		case "Stivesant_2":
			dialog.text = "O halde seni dinliyorum.";
			link.l1 = "Willemstad'da bir darbe oldu. Lucas Rodenburg, valinin yerine geçti ve Matthias Beck'i, İngiliz istihbaratıyla bağlantısı olduğuna dair saçma bir şüpheyle hapse attı.";
			link.l1.go = "Stivesant_3";			
		break;
		
		case "Stivesant_3":
			dialog.text = "Hmm... Beyim, bana anlattıklarınız gerçekten şaşırtıcı. Willemstad'dan çok da uzun olmayan bir süre önce haber aldım, ama içinde böyle bir şey yoktu.";
			link.l1 = "Lütfen beni dinleyin, mynheer Stuyvesant. Haberleri Rodenburg aracılığıyla almış olmalısınız ve o, Curaçao'ya ulaşamayacağınızdan emin olmalı.";
			link.l1.go = "Stivesant_4";			
		break;
		
		case "Stivesant_4":
			dialog.text = "Beyefendi, söyledikleriniz gittikçe daha az hoşuma gidiyor. Siz kimsiniz?";
			link.l1 = "Ben sadece bir kaptanım ve Hollandalı kolonistlerin kaderine kayıtsız kalamayan bir adamım. Lucas Rodenburg, Longway'e geminizi yok etmesini ve sizi de öldürmesini emretti. Ve 'Meifeng' size şüpheli gelmeyeceği için, bunu hiç zorlanmadan gerçekleştirecekti.";
			link.l1.go = "Stivesant_5";			
		break;
		
		case "Stivesant_5":
			dialog.text = "Yani, demek istiyorsun ki Lucas...";
			link.l1 = "Seni iktidardan en kolay yoldan uzaklaştırmaya karar verdiler - seni ortadan kaldırarak. Senin dışında, bölgede Rodenburg'un Takımadalar üzerindeki etkisine ciddi bir şekilde karşı koyabilecek başka kimse yok.";
			link.l1.go = "Stivesant_6";			
		break;
		
		case "Stivesant_6":
			dialog.text = "İnanamıyorum!";
			link.l1 = "Beck’in İngiliz istihbaratıyla bağlantısı olduğuna dair saçmalıklara inanmadım ve kendi araştırmamı yaptım. Seçme katillerle dolu ‘Meifeng’in Philipsburg’a gittiğini öğrendim. Peşlerine düştüm ve onlarla çatıştım. Longway’i yakaladım, bana tüm bu bilgileri ve senin nerede olduğunu söyledi.";
			link.l1.go = "Stivesant_7";			
		break;
		
		case "Stivesant_7":
			dialog.text = "Hm... Bu oldukça olası görünüyor. Rodenburg dışında kimse programımı ve rotamı bilmiyordu ya da bilemezdi! Kahretsin! Bu ihanet! Longway nerede?!";
			link.l1 = "Onu, gönüllü itirafı karşılığında serbest bıraktım. Doğrusunu söylemek gerekirse, Rodenburg'un emrini yerine getirmeye pek hevesli değildi, ama görmezden de gelemedi. Ayrıca, Rodenburg'un hizmetine bir daha dönmeyeceğini söyledi - bu son kirli iş bardağı taşıran damla olmuş.";
			link.l1.go = "Stivesant_8";			
		break;
		
		case "Stivesant_8":
			dialog.text = "Pekala... Kaptan "+GetFullName(pchar)+", benimle birlikte Willemstad'a geleceksin. 'Meifeng' gemisiyle benim gemimin önünde yelken açacaksın. Eğer söylediklerin doğruysa, Lucas tutuklanmalı ve sen de buna yardımcı olacaksın. Ama bana yalan söylediysen... Suçu yalnızca kendinde arayacaksın.";
			link.l1 = "Benim için sana yalan söylemenin bir anlamı yok, mynheer. Hadi acele edelim!";
			link.l1.go = "Stivesant_9";			
		break;
		
		case "Stivesant_9":
			DialogExit();
			Diag.CurrentNode = "Stivesant_10";
			AddQuestRecord("Holl_Gambit", "3-52");
			pchar.questTemp.HWIC.Self = "WayWithStivesant";
			Group_DelCharacter("Stivesant_Halleon", "Stivesant");
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //всегда друзья
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = 40;
			DeleteAttribute(npchar, "LifeDay");
			pchar.quest.Seek_Piter.win_condition.l1 = "location";
			pchar.quest.Seek_Piter.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Seek_Piter.win_condition.l2 = "Day";
			pchar.quest.Seek_Piter.function = "StivesantOnStreet";
			pchar.quest.Terms_Over.win_condition.l1 = "Timer";
			pchar.quest.Terms_Over.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Terms_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 15);
			pchar.quest.Terms_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 15);
			pchar.quest.Terms_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 15);
			pchar.quest.Terms_Over.function = "QuestShipsTerms_Over";
			AddMapQuestMarkCity("Villemstad", false);
		break;
		
		case "Stivesant_10":
			dialog.text = "Kaptan, 'Meifeng'e git. Yelken açma vakti geldi.";
			link.l1 = "Evet, efendim, elbette.";
			link.l1.go = "exit";
			Diag.TempNode = "Stivesant_10";
		break;
		
		case "Keller_1":
			dialog.text = "Çok ilginç! Lütfen, bana hikayeni anlat. Sana yardımcı olmak için elimden geleni yapacağım.";
			link.l1 = "Mynheer Keller, birkaç ay önce Willemstad'a giderken bir flütle karşılaştığınızı hatırlıyor musunuz? O gemide Yahudi mültecilerden oluşan bir aile vardı. O gemide yemek yediniz ve sonra yolculuğunuza devam ettiniz.";
			link.l1.go = "Keller_2";
		break;
		
		case "Keller_2":
			dialog.text = "Evet, sanırım öyle... Evet, şimdi oldukça net hatırlıyorum. Peki, mesele ne?";
			link.l1 = "O gün flüt korsanlar tarafından batırıldı. Sadece iki mülteci kurtulmayı başardı - Solomon ve kızı Abigail. Saldırının gerçekleştiği yerden sadece birkaç mil uzakta bir adada sığınak buldular. O adayı bulmam gerekiyor. O flütü nerede gördüğünü hatırlayabilir misin? Bu çok önemli.";
			link.l1.go = "Keller_3";
		break;
		
		case "Keller_3":
			dialog.text = "Ve ihtiyacın olan her şey bu mu? Bu adayı biliyorum. Çok yakın, Trinidad ile Curaçao arasında. Küçük, ıssız, kimsenin yaşamadığı bir ada. Orada Kızılderililer bile yok.";
			link.l1 = "Ve yaklaşık koordinatlarını biliyor musun?";
			link.l1.go = "Keller_4";
		break;
		
		case "Keller_4":
			dialog.text = "Sana tam koordinatları söyleyebilirim. 12  48'  Kuzey ve 64  41'  Batı'da. Orada ara. Ada oldukça küçük, ama kolayca bulabilirsin.";
			link.l1 = "Teşekkür ederim, Bay Keller! Bana çok yardımcı oldunuz. Hoşça kalın.";
			link.l1.go = "Keller_5";
		break;
		
		case "Keller_5":
			DialogExit();
			Diag.CurrentNode = "Keller_6";
			pchar.quest.Keller_fail.over = "yes";
			pchar.questTemp.HWIC_Coordinates = "true"; //атрибут координат на поиск острова через каюту
			DeleteAttribute(pchar, "questTemp.HWICMC");
			AddQuestRecord("Holl_Gambit", "3-66");
		break;
		
		case "Keller_6":
			dialog.text = "Başka bir isteğiniz var mı, kaptan?";
			link.l1 = "Hayır, teşekkür ederim. Sadece gemime geri dönüyordum.";
			link.l1.go = "exit";
			Diag.TempNode = "Keller_6";
		break;
		
		// belamour рыбацкое судно -->
		case "FishingBoat":
			pchar.GenQuest.FishingBoatSecondTime = true;
			dialog.text = "Özel bir şey yok, bu bir balıkçı teknesi, burada balık tutuyoruz. Sonuçta bir şekilde geçinmek lazım.";
			link.l1 = "Evet, katılıyorum, zamanlar böyle...";
			link.l1.go = "FishingBoat_1";			
		break;
		
		case "FishingBoat_1":
			Diag.TempNode = "FishingBoat_1";
			dialog.text = "Ne istiyorsun?";
			link.l1 = "İstedim"+GetSexPhrase("","")+" takımadadan en son haberleri öğrenmek için. ";
            link.l1.go = "rumours_capitan";
			link.l2 = "Bugün avın nasıl? Satış yapabiliyor musun? Biraz erzak fena olmazdı...";
			link.l2.go = "FishingBoat_2";
			link.l3 = "Özel bir şey yok, sadece merhaba demeye geldim!";
    		link.l3.go = "exit";	
	
		break;
		
		case "FishingBoat_2":
			if(GetDataDay() < 11) 
			{
				if(sti(RealShips[sti(npchar.ship.type)].basetype) == SHIP_TARTANE) iTemp = 100 + hrand(100);
				else iTemp = 200 + hrand(100);
				iMoney = sti(GetCurrentIslandGoodsPrice(GOOD_FOOD)*0.66);
				pchar.GenQuest.FishingBoatITemp = iTemp;
				pchar.GenQuest.FishingBoatIMoney = iMoney;
				
				dialog.text = "Bugün avımız iyi, sadece ağları çekmek için zamana ihtiyacımız var. İsterseniz size satabiliriz, dükkandakinden de ucuza – sonuçta balığı zaten yerel bir tüccara satıyoruz. Bunu erzağa çevirirsek... Şu anda elimizde "+iTemp+" bununla, onu iyi bir fiyata satabiliriz "+iMoney+" tanesi için peso. Kaç tanesini alırsın?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта";
				link.l2 = "Biliyor musun, erzaklarını almaktan vazgeçtim.";	
				link.l2.go = "exit";
				
			}
			if(GetDataDay() > 10 && GetDataDay() < 21) 
			{
				Diag.TempNode = "FishingBoat_1";
				dialog.text = "Evet, bir şeyler var ama dürüst olmak gerekirse, hiç balık yok ... Bugün neredeyse hiç tutamadık. Ama zıpkınlar elimizde kaldı - belki şansımız yaver gider de büyük bir balık ya da bir balina yakalarız diye düşünmüştük ... Belki zıpkına ihtiyacınız vardır?";
				link.l1 = "Hayır, zıpkınlarla ilgilenmiyorum.";
				link.l1.go = "exit";
				link.l2 = "Hmm, bir zıpkın da doğru ellerde işe yarar bir şeydir. Muhtemelen alacağım.";
				link.l2.go = "Гарпуны";
			}
			if(GetDataDay() > 20)
			{
				dialog.text = "Evet, bir şeyler var ama dürüst olmak gerekirse, hiç balık yok... Bugün neredeyse hiçbir şey yakalanmadı. Yani satacak pek bir şeyim yok. Yalnızca... Birkaç ufak tefek eşya var, belki ilginizi çeker. Göz atmak ister misiniz?";
				link.l1 = "Hayır, ıvır zıvırla ilgilenmiyorum.";
				link.l1.go = "exit";
				link.l2 = "Ne yazık ki bir av yok. Neyse, en azından şu ıvır zıvırlarına bir bakalım – belki gözüme bir şey çarpar ...";
				link.l2.go = "Торговля";
			}	
		break;
		
		case "Количество вбитого провианта":
			Diag.TempNode = "FishingBoat_1";
			iQty = sti(dialogEditStrings[3]);
			iTemp = makeint(pchar.GenQuest.FishingBoatITemp);
			pchar.GenQuest.FishingBoatIQty = iQty;
			iMoney = makeint(pchar.GenQuest.FishingBoatIMoney);
			if(iQty > iTemp)
			{
				dialog.text = "Bu çok fazla... O kadar param yok! Daha az alabilir misin?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта повтор";	
				link.l2 = "Biliyor musun, erzaklarını almaktan vazgeçtim.";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "Benimle dalga mı geçiyorsun? Erzağa ihtiyacın var mı yok mu? Varsa, ne kadar?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта повтор";	
				link.l2 = "Biliyor musun, erzaklarını almaktan vazgeçtim.";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "Anlaştık! "+sti(iQty*iMoney)+" pesos.";
				if(sti(pchar.money) < iQty*iMoney)
				{
					link.l1 = "Hmm, o kadar param yok. Belki başka zaman.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Anlaştık! Malları gemime getir.";
					link.l1.go = "Удачная покупка";
					link.l2 = "Biliyor musun, erzaklarını almaktan vazgeçtim.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "Количество вбитого провианта повтор":
			Diag.TempNode = "FishingBoat_1";
			iQty = sti(dialogEditStrings[3]);
			iTemp = makeint(pchar.GenQuest.FishingBoatITemp);
			pchar.GenQuest.FishingBoatIQty = iQty;
			iMoney = makeint(pchar.GenQuest.FishingBoatIMoney);
			if(iQty > iTemp)
			{
				dialog.text = "Bu çok fazla... O kadar param yok! Daha az alabilir misin?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта";	
				link.l2 = "Biliyor musun, erzaklarını almaktan vazgeçtim.";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "Benimle dalga mı geçiyorsun? Erzağa ihtiyacın var mı, yok mu? Varsa, ne kadar?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта";	
				link.l2 = "Biliyor musun, erzaklarını almaktan vazgeçtim.";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "Anlaştık! "+sti(iQty*iMoney)+" pesos.";
				if(sti(pchar.money) < iQty*iMoney)
				{
					link.l1 = "Hmm, o kadar param yok. Belki başka bir zaman.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Anlaştık! Malları gemime yükleyin.";
					link.l1.go = "Удачная покупка";
					link.l2 = "Biliyor musun, erzaklarını almaktan vazgeçtim.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "Удачная покупка":
			Diag.TempNode = "First time";
			Diag.CurrentNode = "First time";
			iQty = makeint(pchar.GenQuest.FishingBoatIQty);
			iMoney = makeint(pchar.GenQuest.FishingBoatIMoney);
			iTemp = iQty*iMoney;
			DialogExit();
			SetCharacterGoods(pchar, GOOD_FOOD, GetCargoGoods(pchar, GOOD_FOOD)+iQty);
			AddMoneyToCharacter(pchar, -iTemp);
		break;
		
		case "Гарпуны":
				Diag.TempNode = "FishingBoat_1";
				iTemp = 5+hrand(5);
				pchar.GenQuest.FishingBoatITemp = iTemp;
				dialog.text = "Bizde var "+iTemp+" parça. Her bir zıpkını yüz peso'ya satabiliriz. Kaç tane istersiniz?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов";
				link.l2 = "Biliyor musun, fikrimi değiştirdim, zıpkınlara ihtiyacım yok.";	
				link.l2.go = "exit";
		break;
		
		case "Количество вбитых гарпунов":
   
			iQty = sti(dialogEditStrings[3]);
			iTemp = makeint(pchar.GenQuest.FishingBoatITemp);
			pchar.GenQuest.FishingBoatIQty = iQty;
			Diag.TempNode = "FishingBoat_1";
			if(iQty > iTemp)
			{
				dialog.text = "Bu çok fazla... O kadar param yok! Daha az alabilir misin?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов заново";	
				link.l2 = "Biliyor musun, fikrimi değiştirdim, zıpkınlara ihtiyacım yok.";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "Benimle dalga mı geçiyorsun? Zıpkına ihtiyacın var mı yok mu? Varsa, kaç tane lazım?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов заново";	
				link.l2 = "Biliyor musun, fikrimi değiştirdim, zıpkınlara ihtiyacım yok.";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "Anlaştık! "+sti(iQty*100)+" pesos.";
				if(sti(pchar.money) < iQty*100)
				{
					link.l1 = "Hmm, o kadar param yok. Belki başka bir zaman.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Anlaştık! Onları bir şekilde değerlendireceğim.";
					link.l1.go = "Удачная покупка гарпунов";
					link.l2 = "Biliyor musun, fikrimi değiştirdim, zıpkınlara ihtiyacım yok.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "Количество вбитых гарпунов заново":
			iQty = sti(dialogEditStrings[3]);
			iTemp = makeint(pchar.GenQuest.FishingBoatITemp);
			pchar.GenQuest.FishingBoatIQty = iQty;
			Diag.TempNode = "FishingBoat_1";
			if(iQty > iTemp)
			{
				dialog.text = "Bu çok fazla... O kadar param yok! Daha az alabilir misin?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов";	
				link.l2 = "Biliyor musun, fikrimi değiştirdim, zıpkınlara ihtiyacım yok.";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "Benimle dalga mı geçiyorsun? Zıpkına ihtiyacın var mı yok mu? Varsa, kaç tane?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов";	
				link.l2 = "Biliyor musun, fikrimi değiştirdim, zıpkınlara ihtiyacım yok.";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "Anlaştık! "+sti(iQty*100)+" peso.";
				if(sti(pchar.money) < iQty*100)
				{
					link.l1 = "Hmm, o kadar param yok. Belki başka zaman.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Anlaştık! Onları bir şekilde değerlendireceğim.";
					link.l1.go = "Удачная покупка гарпунов";
					link.l2 = "Biliyor musun, fikrimi değiştirdim, zıpkınlara ihtiyacım yok.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "Удачная покупка гарпунов":
			DialogExit();
			Diag.TempNode = "First time";
			Diag.CurrentNode = "First time";
			iQty = makeint(pchar.GenQuest.FishingBoatIQty);
			TakeNItems(pchar, "slave_01", iQty);
			AddMoneyToCharacter(pchar, -iQty*100);
			
		break;
		
		case "Торговля":
			DialogExit();
			Diag.TempNode = "First time";
			Diag.CurrentNode = "First time";
			if(!CheckAttribute(pchar,"GenQuest.FishingBoatDialogEnb")) pchar.GenQuest.FishingBoatDialogEnb = true;
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "Особые товары":
			if(hrand(2, "&SpeGoo") == 0)
			{
				Diag.TempNode = "First time";
				Diag.CurrentNode = "First time";
				pchar.GenQuest.FishingBoatDialogEnb = "no special goods";
				dialog.text = "Hayır, başka bir şey yok. Bu bir balıkçı teknesi! Burada başka ne olabilir ki?";
				link.l1 = "Pekala, anladım.";
				link.l1.go = "exit";
			}
			else if(hrand(2, "&SpeGoo") == 1)
			{
				if(ChangeContrabandRelation(pchar, 0) > 5)
				{
					
					dialog.text = "Pekala ... Burada küçük bir şeyim var ... Sakladım, belki birine satarım diye düşündüm. Ama bunun için iyi bir para isterim! Ve ikinci kez teklif etmeyeceğim. İzleyecek misin?";
					link.l1 = "Bana göster, bakalım neymiş o küçük şey.";
					link.l1.go = "Особые товары предметы";
				}
				else
				{
					Diag.TempNode = "First time";
					Diag.CurrentNode = "First time";
					pchar.GenQuest.FishingBoatDialogEnb = "no special goods";
					dialog.text = "Hayır, başka bir şey yok. Bu bir balıkçı teknesi! Burada başka ne olabilir ki?";
					link.l1 = "Pekâlâ, anladım. ";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.GenQuest.FishingBoatDialogEnb = "no special goods";
				Diag.TempNode = "First time";
				Diag.CurrentNode = "First time";
				if(ChangeContrabandRelation(pchar, 0) > 5)
				{
					if(GetDataDay() < 8)
					{	
						iMoney = GetStoreGoodsPrice(&Stores[SantaCatalina_STORE], GOOD_SANDAL, PRICE_TYPE_BUY, pchar, 1);
						iTemp = GOOD_SANDAL;
						sTemp = "units of backout";
					}
					if(GetDataDay() > 7 && GetDataDay() < 15)
					{
						iMoney = GetStoreGoodsPrice(&Stores[PortSpein_STORE], GOOD_OIL, PRICE_TYPE_BUY, pchar, 1);
						iTemp = GOOD_OIL;
						sTemp = "barrels of ship tar"; 
					}
					if(GetDataDay() > 14 && GetDataDay() < 22) 
					{
						iMoney = GetStoreGoodsPrice(&Stores[BasTer_STORE], GOOD_ROPES, PRICE_TYPE_BUY, pchar, 1);
						iTemp = GOOD_ROPES;
						sTemp = "bays of ship ropes"; 
					}
					if(GetDataDay() > 21) 
					{
						iMoney = GetStoreGoodsPrice(&Stores[Villemstad_STORE], GOOD_SHIPSILK, PRICE_TYPE_BUY, pchar, 1);
						iTemp = GOOD_SHIPSILK;
						sTemp = "rolls of ship silk";
					}
					iQty = 20 + sti(rand(6)*5);
					pchar.GenQuest.FishingBoatITemp = iTemp;
					pchar.GenQuest.FishingBoatIMoney = iMoney;
					pchar.GenQuest.FishingBoatIQty = iQty;
					
					dialog.text = "Şey ... Burada iyi bir şeyim var ... Tamamen tesadüfen, körfezin kıyısında buldum. Bu "+iQty+" "+sTemp+". Parça başına fiyatı "+iMoney+". Ama her şeyi sadece bir seferde satarım ve ikinci bir teklifim olmaz. Ayrıca, bu işten kimsenin haberi olmayacak ... anladın mı?";
					link.l1 = "Hayır, şüpheli malları istemiyorum, teşekkürler. Merak etme, kimseye söylemeyeceğim.";
					link.l1.go = "exit";
					if(sti(pchar.money) >= iMoney*iQty)
					{
						link.l2 = "Seni anlıyorum. Ama mallar buna değer. Alıyorum. Onu gemime getirin.";
						link.l2.go = "Купили стратегический товар";
					}
				}
			}
		break;
		
		case "Особые товары предметы":
			pchar.GenQuest.FishingBoatDialogEnb = "no special goods";
			Diag.TempNode = "First time";
			Diag.CurrentNode = "First time";
			if(ChangeContrabandRelation(pchar, 0) > 5)
			{
				switch(GetDataDay())
				{
					case 21: sTemp = "mushket1";  break;
					case 22: sTemp = "cirass5";   break;
					case 23: sTemp = "blade_16";  break;
					case 24: sTemp = "blade_04";  break;
					case 25: sTemp = "blade_06";  break;
					case 26: sTemp = "compass1";  break;
					case 27: sTemp = "clock2";    break;
					case 28: sTemp = "pistol4";   break;
					case 29: sTemp = "pistol2";   break;
					case 30: sTemp = "obereg_9";  break;
					case 31: sTemp = "obereg_10"; break;	
				}
				pchar.GenQuest.FishingBoatSTemp = sTemp;
				dialog.text = "Bu "+GetItemName(sTemp)+". Bunu ele geçirdim... nereden olduğunu boşver. Bir bilene satmayı düşünüyordum. Sana sadece 10.000 peso'ya bırakırım! Alır mısın?";
				if(sti(pchar.money) > 9999)
				{
					link.l1 = "Tabii ki alırım! Sonuçta ayakta duruyor. ";
					link.l1.go = "Купили особый товар";
				}
				link.l2 = "Hayır, ihtiyacım yok. Almayacağım. ";
				link.l2.go = "exit";
			}
		
		break;
		
		case "Купили особый товар":
			Diag.TempNode = "First time";
			Diag.CurrentNode = "First time";
			DialogExit();
			sTemp = pchar.GenQuest.FishingBoatSTemp;
			if(GetDataDay() != 23 || GetDataDay() != 24 || GetDataDay() != 25) 
			{
				TakeNItems(pchar, sTemp, 1);
			}
			else
			{
				sTemp = GetGeneratedItem(sTemp);
				GiveItem2Character(pchar, sTemp);
			}
			AddMoneyToCharacter(pchar, -10000);
		break;
		
		case "Купили стратегический товар":
			Diag.TempNode = "First time";
			Diag.CurrentNode = "First time";
			iQty = makeint(pchar.GenQuest.FishingBoatIQty);
			iMoney = makeint(pchar.GenQuest.FishingBoatIMoney);
			iTemp = makeint(pchar.GenQuest.FishingBoatITemp);
			DialogExit();
			SetCharacterGoods(pchar, iTemp, GetCargoGoods(pchar,iTemp)+iQty);
			AddMoneyToCharacter(pchar, -iMoney*iQty);
		break;
		// <-- рыбацкое судно
	}
}

string GetNumShips(int ship)
{
    string numships;
    switch(ship)
    {
       case 0: numships = "no ships"; break;
       case 1: numships = "one ship";      break;
       case 2: numships = "two ships";       break;
       case 3: numships = "three ships";       break;
       case 4: numships = "four ships";    break;
       case 5: numships = "five ships";     break;
       case 6: numships = "six ships";    break;
    }
    return numships;
}

string GetPart(int part)
{
    string numpart;
    switch(part)
    {
       case 0: numpart = ""; break;
       case 1: numpart = "all loot"; break;
       case 2: numpart = "half of the loot"; break;
       case 3: numpart = "third of the loot"; break;
       case 4: numpart = "quarter of the loot";      break;
    }
    return numpart;
}

int findPriceStoreMan(ref NPChar)
{
    ref ch;
	int n;
    int storeArray[40];
    int howStore = 0;

	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
		if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_Store.c") // магазин
		{
            //if (sti(ch.nation) !=  sti(NPChar.nation)) continue;
            if (ch.location == "none") continue; // фикс для новых, невидимых до поры островов
            storeArray[howStore] = n;
            howStore++;
            
            // homo 05/09/06
            if ( CheckAttribute(NPChar, "FromColony") && NPChar.FromColony == ch.City ) return n;
            //
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

int CalcBattleDifficulty()
{
    UpdatePlayerSquadronPower();

    float encPow = 0.0;
    float pchPow = stf(PChar.Squadron.RawPower);

    string sTemp;
    if(CheckAttribute(CharacterRef, "SeaAI.Group.Name"))
        sTemp = CharacterRef.SeaAI.Group.Name;
    else return 0;

    int	iGroupIndex = Group_FindGroup(sTemp);
    if (iGroupIndex < 0)
    {
        Log_TestInfo("НЕТ ГРУППЫ В CalcBattleDifficulty");
        trace("НЕТ ГРУППЫ В CalcBattleDifficulty");
        return 0;
    }

    ref rGroup = Group_GetGroupByIndex(iGroupIndex);
    if (!CheckAttribute(rGroup, "Quest")) return 0;

    aref aCompanions, aCharInfo;
    makearef(aCompanions, rGroup.Quest);
    int qty = GetAttributesNum(aCompanions);

    ref rChar, rShip;
    int iShipType, idx;
    for(int i = 0; i < qty; i++)
    {
        aCharInfo = GetAttributeN(aCompanions, i);
        idx = sti(aCharInfo.index);
        if(idx == -1) continue;
        rChar = GetCharacter(idx);
        if(!CheckAttribute(rChar, "index") || rChar.index == "none" || LAi_IsDead(rChar)) continue;
        iShipType = sti(rChar.Ship.Type);
        if(iShipType == SHIP_NOTUSED) continue;
        rShip = GetRealShip(iShipType);
        encPow += GetRealShipPower(rChar);
    }

    iEncPow = encPow;

    if(pchPow == 0.0)
    {
        if(encPow == 0.0) return 50;
        return 0;
    }

    float fRatio = (encPow * 0.9) / pchPow;

    if(fRatio >= 1.7) return 0; // Кирдык
    // От 50 шанс быстро падает к 0
    if(fRatio >= 1.0)
    {
        return MakeInt(100 * 0.5 * pow((1.7 - fRatio) / 0.7, 2.5));
    }
    // От 50 шанс медленно растёт к 100
    return MakeInt(100 * (0.5 + 0.5 * pow((1 - fRatio), 0.5)));
}
