// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Mit akarsz?", "Mit szeretnél tudni?"), "Mire van szüksége, " + GetAddress_Form(NPChar) + "?", "Már harmadszor próbálod megkérdezni...", "Elegem van belôled, tûnj el!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Sajnálom, meggondoltam magam.", "Semmiség, elnézést."), "Elfelejtettem, elnézést kérek...",
                      "Harmadszorra sikerül, mi? Elnézést...", "Bocsánat, bocsánat! Akkor majd én kikísérem magam...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "mayak")
			{
				link.l1 = "Üdvözletem. A santiagói inkvizítor, Dadre Vincento, megemlített téged a levelében. Azt mondta, talán segíthetnél nekem.";
                link.l1.go = "guardoftruth";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "mayak_next")
			{
				link.l1 = "Van valami hír Vincento atyáról, "+npchar.name+"?";
                link.l1.go = "guardoftruth_5";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && CheckCharacterItem(pchar, "jewelry33") && CheckCharacterItem(pchar, "jewelry34") && CheckCharacterItem(pchar, "jewelry35"))
			{
				link.l1 = "Látnom kell Vincento atyát. Megtaláltam a tárgyakat, amik érdeklik.";
                link.l1.go = "guardoftruth_7";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "inquisition")
			{
				link.l1 = "Szóval, "+npchar.name+", mit mondott neked Padre Vincento?";
                link.l1.go = "guardoftruth_11";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Persze, Senor. Ön biztosan nagy hírû ember, ha maga Vincento atya üzletel önnel.";
			link.l1 = "Pompás. Akkor maga a mi futónk. Figyelj, ez az ember nagyon érdekli Vincento atyát. Mostantól a maga felelôssége alatt áll, át kell vinnie Santiagóba, vagy találnia kell valakit, aki megteszi.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "...";
			link.l1 = "Ön felelôs a fogolyért az inkvizítor nevében. Nem tanácsolnám, hogy vegye le a bilincseit, Gaius Marchais erôs ember. Add át ezt a levelet Vincento páternek, és mondd meg neki, hogy két napon belül választ várok tôle. Remélem, ez elég lesz.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			Log_Info("Elválsz a levéltôl");
			PlaySound("interface\important_item.wav");
			dialog.text = "Értettem, Senor. Megteszek minden tôlem telhetôt. Nem ez az elsô alkalom, hogy segítek a szentatyának.";
			link.l1 = "Ez még nem minden. A carraca kapitánya, San Gregorio, Carlos Guevarra biztosan itt volt. Vaníliát hozott nekem. Átadta a levelemet?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Igen, a rakománya rendben van és várja önt, Senor.";
			link.l1 = "Jó, akkor majd a hajómon elszállíttatom. Két napig itt leszek, és várom Padre Vincento válaszát. Ez nem búcsú egyelôre, "+npchar.name+"!";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			LocatorReloadEnterDisable("mayak9", "boat", false);
			ref sld = characterFromId("GOT_Marshe");
			LAi_SetStayType(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			pchar.questTemp.Guardoftruth = "mayak_wait";
			SetFunctionTimerCondition("GuardOT_MayakNextStage", 0, 0, 2, false);
			SetCharacterGoods(pchar, GOOD_CINNAMON, GetCargoGoods(pchar, GOOD_CINNAMON) + sti(pchar.questTemp.Guardoftruth.VanilleQty));
			AddQuestRecord("Guardoftruth", "21");
		break;
		
		case "guardoftruth_5":
			dialog.text = "Igen, Senor. Itt van egy levél Vincento atyától. Nagyon örül önnek, a többit majd megtudja a levélbôl.";
			link.l1 = "Pompás. Addig is, "+npchar.name+". És most - viszlát.";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			DialogExit();
			pchar.questTemp.Guardoftruth = "mayak_exit";
			GiveItem2Character(pchar, "specialletter");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento_next";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Viszlát. Adja át nekem, és én elviszem a szentatyának.";
			link.l1 = "Nem lehet, fiam! Nem volt könnyû megszerezni azokat, és nem fogom így átadni. Csak személyesen adom át ôket Vincento atyának.";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "De senor! Honnan tudhatnám, hogy nem akar átverni?";
			link.l1 = "Nézze meg: a kengyeltartó, a kehely és a lazurit kereszt... "+npchar.name+", mit gondolsz, ki vagyok én? Tényleg azt hiszed, hogy elég hülye vagyok ahhoz, hogy ezek nélkül menjek az inkvizícióhoz?";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Bocsásson meg, senor... Jöjjön el holnap, és elmondom Vincento atyának, hogy megérkezett.";
			link.l1 = "Jól van. Holnap találkozunk.";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			DialogExit();
			pchar.questTemp.Guardoftruth = "mayak_wait";
			SetFunctionTimerCondition("GuardOT_MayakLastStage", 0, 0, 1, false);
		break;
		
		case "guardoftruth_11":
			dialog.text = "Ôkegyelme fogadni fogja, senor. Ne késleltesse a látogatását. Itt van a dokumentum, mutassa meg az ôröknek és beengedik. De elôbb húzzon fel egy spanyol zászlót, különben a katonák valószínûleg letartóztatják.";
			link.l1 = "Megvan. Akkor spanyolul. Kösz, haver! Máris indulok!";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			DialogExit();
			GiveItem2Character(pchar, "VerifyPaper");
			ChangeItemDescribe("VerifyPaper", "itmdescr_VincentoPaper");
			pchar.questTemp.Guardoftruth = "santiago";
			AddQuestRecord("Guardoftruth", "34");
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 400);//скрытность
			GuardOT_SetPadreVincento();
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
