void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iGun, iMush, qty;
	string sGroup, sLink, sText;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Carib" + locations[FindLocation(npchar.location)].index + "_";

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		
		case "First time":
			dialog.text = "Gratulálok! Ez egy bogár. Vedd fel a kapcsolatot Jasonnel, és mondd el neki, hogyan és honnan szerezted ezt. Béke!";
			link.l1 = "Azonnal megteszem!";
			link.l1.go = "exit";
			Diag.TempNode = "First time";
		break;

		case "exit_fight":
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_CaribAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_peace":
			DialogExit();
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_SetImmortal(sld, false);
				LAi_CharacterDisableDialog(sld);
			}	
			ChangeIndianRelation(1.00);
		break;
		
		// военные индеи - карибы
		case "war_indian":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			if (sti(pchar.questTemp.Indian.relation) > 79)
			{
				dialog.text = LinkRandPhrase("Üdvözlégy, tenger fia! Hallottam rólad. Könnyedén léphetsz a mi földünkre.",""+npchar.name+" üdvözöl téged, sápadtarcú testvér. Örülünk, hogy vendégünk vagy.","üdvözöllek, bátor sápadtarcú harcos! "+npchar.name+" örül, hogy találkozhat egy indián barátjával. Menjetek békében!");
				link.l1 = RandPhraseSimple("És üdv neked, vörösbôrû testvér! Jó vadászatot neked!","Üdvözlet, bátor harcos! Az istenek áldjanak meg téged és családodat!");
				link.l1.go = "exit_peace";
				if (CheckCaribGuns())
				{
					npchar.quest.count = 0;
					link.l2 = RandPhraseSimple("Van valami, ami érdekes lehet számodra, vörösbôrû testvér. Akarsz cserélni?","Tudok ajánlani neked valami érdekeset, bátor harcos. Akarsz cserélni?");
					link.l2.go = "war_indian_trade";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Állj, sápadtarcú! Milyen jogon jársz a földemen?","Állj, fehér ember! Az ôseim földjén és az én földemen jársz!","Állj, sápadtarcú! Nem tartozol a földemhez!");
				link.l1 = RandPhraseSimple("A te földed? Tûnj el, te vörös képû söpredék!","Nézzétek - egy beszélô majom! Tûnjetek el, most!");
				link.l1.go = "war_indian_1";
				link.l2 = RandPhraseSimple("Békével jöttem, vörös bôrû harcos. Nem kellene a semmiért harcolnunk.","Én nem vagyok ellensége neked és a földednek, harcos. Békével jöttem.");
				if (sti(pchar.questTemp.Indian.relation)+(makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/3)) > hrand(80)) link.l2.go = "war_indian_2_1";
				else link.l2.go = "war_indian_2_2";
				link.l3 = RandPhraseSimple("Azért jöttem, hogy kereskedjek veled, nem azért, hogy harcoljak.","Nem harcolok indiánokkal. Én kereskedem velük.");
				if (sti(pchar.questTemp.Indian.relation)+(makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/6)+makeint(GetSummonSkillFromName(pchar, SKILL_FORTUNE)/6)) > hrand(90)) link.l3.go = "war_indian_3_1";
				else link.l3.go = "war_indian_3_2";
			}
		break;
		
		case "war_indian_1":
			dialog.text = RandPhraseSimple("Sajnálod, hogy megszülettél, sápadtarcú kutya... Kivágom a szívedet és tûzön sütöm!","Köveket etetek veled, sápadtarcú kutya! Röhögünk, hogy térden állva könyörögsz a halálért, fehér kankalin!");
			link.l1 = RandPhraseSimple("Még mindig nem tudod befogni a büdös szádat, festett madárijesztô? Visszaviszlek a dzsungelbe, ahonnan jöttél!","Mersz fenyegetni engem, te szemétláda?! Hát most visszamászol a fára, ahonnan az elôbb jöttél le!");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_2_1":
			dialog.text = RandPhraseSimple("Hallom, hogy a hangod igazat beszél. Ma nem fogunk baltát emelni ellened. Menj békében, sápadtarcú.","A sápadtarcú ritkán hoz békét, de látom a szemedben, hogy igazat beszélsz. Most menjetek.");
			link.l1 = RandPhraseSimple("Bölcs döntés, harcos. Sok szerencsét neked.","Örülök, hogy megegyeztünk, harcos.");
			link.l1.go = "exit_peace";
		break;
		
		case "war_indian_2_2":
			dialog.text = RandPhraseSimple("Hazudsz, sápadtarcú kripli! Idejöttél, hogy indiánokat ölj! Készen állsz a csatára, sápadtarcú?!","Indiánokat ölsz. A fehér nyelv hazug nyelv. Levágom és tûzön sütöm!");
			link.l1 = RandPhraseSimple("Akkor ne engem hibáztass, haver. Isten tudja, próbáltam elkerülni...","Nos, te akartad, harcos.");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_3_1":
			if (CheckCaribGuns())
			{
				npchar.quest.count = 0;
				dialog.text = "Cserélni? Szükségünk van a fehér emberek fegyverére. Félkezû tüzes fegyvert a sápadtarcúaknak! Ezért cseréljük el a portékáinkat! Van tüzes fegyvered, amivel kereskedhetsz?";
				link.l1 = "Hmm. Igen, hallom. És mit adsz nekem cserébe?";
				link.l1.go = "war_indian_trade";
				link.l2 = "Te gazember! És aztán a pisztolyaimmal lövöldözni fogsz a telepesekre? Nem, az nem fog megtörténni! Ami titeket, sakálok, most mindannyiótokat leváglak...";
				link.l2.go = "exit_fight";
			}
			else
			{
				dialog.text = "Nem kapjátok meg, amit mi akarunk, sápadtarcú... Te leszel a mi háborús trófeánk!";
				link.l1 = "Próbáld meg, ha mered, madárijesztô...";
				link.l1.go = "exit_fight";
			}
		break;
		
		case "war_indian_3_2":
			dialog.text = RandPhraseSimple("Nem kereskedünk sápadtarcú kutyákkal. Mi ölünk és viszünk!","Mi nem vagyunk mocskos miskito vagy arawak, mi nem kereskedünk sápadtarcúakkal! Megöljük ôket, és háborús trófeát szerzünk!");
			link.l1 = RandPhraseSimple("Hát akkor próbálj meg kirabolni, gazember!","Elôször is el kell venned tôlem a szablyámat, te mocsok!");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_trade":
			iGun = 1;
			dialog.text = "Mutasd meg, mid van, és mi megmondjuk, mit adunk érte.";
			for (i=6; i>=1; i--)
			{
				if (GetCharacterFreeItem(pchar, "pistol"+i) > 0)
				{
					sLink = "l"+iGun;
					link.(sLink) = "Ajánlat "+XI_ConvertString("pisztoly"+i)+".";
					link.(sLink).go = "gun_"+i;
					iGun++;				
				}
			}
		break;
		
		case "gun_1":
			npchar.quest.gun = "pistol1";
			if (hrand(1) == 0)
			{
				npchar.quest.item = "potion"+(rand(2)+2);
				iTotalTemp = hrand(1)+1;
				sText = ""+FindRussianQtyString(iTotalTemp)+"  vial of good curative potion";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(9)+14);
				iTotalTemp = hrand(2)+1;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful stone";
			}
			dialog.text = "Hé-hó! Adunk érte "+sText+".";
			link.l1 = "Áll az alku!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Nem. Szó sem lehet róla.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_2":
			npchar.quest.gun = "pistol2";
			if (hrand(3) < 2)
			{
				npchar.quest.item = "potion"+(rand(2)+2);
				iTotalTemp = hrand(2)+2;
				sText = ""+FindRussianQtyString(iTotalTemp)+" vial of good curative potion";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(3)+1);
				iTotalTemp = hrand(2)+2;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful stone";
			}
			dialog.text = "Hé-hó! Ravasz fegyver... Adunk érte "+sText+".";
			link.l1 = "Áll az alku!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Nem. Szó sem lehet róla.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_3":
			npchar.quest.gun = "pistol3";
			if (hrand(5) < 3)
			{
				qty = rand(1)+2;
				npchar.quest.item = "jewelry5"+qty;
				iTotalTemp = hrand(6)+qty*15;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful pearl";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(2)+2);
				iTotalTemp = hrand(2)+5;
				sText = ""+FindRussianQtyString(iTotalTemp)+"  this beautiful stone";
			}
			dialog.text = "Hé-hó! Hatalmas fegyver! Sok-sok ellenséget megölni! Adunk érte "+sText+".";
			link.l1 = "Áll az alku!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Nem. Szó sem lehet róla.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_4":
			npchar.quest.gun = "pistol4";
			if (hrand(9) < 8)
			{
				qty = rand(1)+1;
				npchar.quest.item = "jewelry"+(qty+4);
				iTotalTemp = hrand(10)+qty*30;
				sText = ""+FindRussianQtyString(iTotalTemp)+" piece of metal which paleface loves more than life";
			}
			else
			{
				npchar.quest.item = "obereg_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "Hé-hó! Félelmetes fegyver... Adunk érte "+sText+".";
			link.l1 = "Áll az alku!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Nem. Szó sem lehet róla.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_5":
			npchar.quest.gun = "pistol5";
			if (hrand(7) < 7)
			{
				if (hrand(10) < 8)
				{
					npchar.quest.item = "jewelry7";
					iTotalTemp = 2+hrand(1);
				}
				else
				{
					npchar.quest.item = "jewelry8";
					iTotalTemp = hrand(4)+10;
				}
				qty = hrand(1)+1;
				npchar.quest.item = "jewelry"+(qty+6);
				if (qty == 1) iTotalTemp = 2;
				else iTotalTemp = hrand(5)+qty*15;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful and precious petrified tar";
			}
			else
			{
				npchar.quest.item = "indian_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "Hé-hó! Gyönyörû és hatalmas fegyver! Sok-sok ellenséget megölni! Adunk érte "+sText+".";
			link.l1 = "Áll az alku!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Nem. Szó sem lehet róla.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_6":
			npchar.quest.gun = "pistol6";
			if (hrand(9) < 8)
			{
				qty = rand(1)+1;
				npchar.quest.item = "jewelry"+(qty+4);
				iTotalTemp = hrand(8)+qty*20;
				sText = ""+FindRussianQtyString(iTotalTemp)+" piece of metal which paleface loves more than life";
			}
			else
			{
				npchar.quest.item = "amulet_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "Hé-hó! Praktikus fegyver... Adunk érte "+sText+".";
			link.l1 = "Áll az alku!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Nem. Szó sem lehet róla.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "war_indian_trade_agree":
			ChangeIndianRelation(1.00);
			npchar.quest.count = sti(npchar.quest.count)+1;
			TakeNItems(pchar, npchar.quest.item, iTotalTemp);
			RemoveItems(pchar, npchar.quest.gun, 1);
			Log_Info("Megkaptad "+XI_ConvertString(npchar.quest.gun)+"");
			Log_Info("Ön a "+XI_ConvertString(npchar.quest.item)+" összeget kapta. "+FindRussianQtyString(iTotalTemp)+"");
			PlaySound("interface\important_item.wav");
			if (sti(npchar.quest.count) > 3+hrand(2));
			{
				dialog.text = "Jól van. Itt van az árud. Nem kereskedünk többé. Gyertek késôbb. Jobb tüzes fegyvert adunk érte. Most menjetek!";
				link.l1 = "Ég veled, vörös bôrû harcos.";
				link.l1.go = "exit_peace";
			}
			else
			{
				dialog.text = "Rendben. Itt van az áru. Van még tüzes fegyvered cserére?";
				if (CheckCaribGuns())
				{
					link.l1 = "Van. Megveszed?";
					link.l1.go = "war_indian_trade";
				}
				link.l2 = "Nem. Legközelebb többet hozok.";
				link.l2.go = "war_indian_trade_exit";
			}
		break;
		
		case "war_indian_trade_exit":
			dialog.text = "Hozd. Jobb tüzes fegyvert adunk érte. Most menjetek!";
			link.l1 = "Viszlát, harcos...";
			link.l1.go = "exit_peace";
		break;
		
		case "war_indian_trade_bad":
			if (sti(pchar.questTemp.Indian.relation) > 79)
			{
				DialogExit();
				sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
				for(i = 0; i < iTemp; i++)
				{
					sld = CharacterFromID(sTemp + i);
					LAi_SetWarriorTypeNoGroup(sld);
					LAi_group_MoveCharacter(sld, sGroup);
					LAi_SetImmortal(sld, false);
					LAi_CharacterDisableDialog(sld);
				}	
			}
			else
			{
				dialog.text = "Akkor mindent elviszünk ingyen, sápadtarcú!";
				link.l1 = "Megpróbálhatod...";
				link.l1.go = "exit_fight";
			}
		break;
		
		// мирные индеи - мискито
		case "peace_indian":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			dialog.text = LinkRandPhrase("Üdvözlégy, fehér ember. Mire van szükséged a mi dzsungelünkben?","A mi dzsungelünk nagyon veszélyes. Mit csinálsz itt?","Mi szél hozott ide, bátor sápadtarcú?");
			link.l1 = RandPhraseSimple("Csak erre jártam, vörösbôrû barátom. Azt hiszem, mindkettônknek van elég hely ezen az úton?","Üdvözletem, a dzsungel fia! Üzleti ügyben vagyok itt, és nem harcolok indiánok ellen.");
			link.l1.go = "peace_indian_1";
			link.l2 = RandPhraseSimple("És miért kell ezt tudnod? Menj a saját utadon, és maradj távol a bajtól!","Menj a saját utadon, vörösbôrû. Nincs idôm veled beszélgetni.");
			link.l2.go = "peace_indian_2";
		break;
		
		case "peace_indian_1":
			dialog.text = RandPhraseSimple("Mi békés emberek. Nem vagyunk a fehér ember ellenségei. Menjetek, de óvatosan a mi földünkön!","Örömmel találkozom az indiánok sápadt arcú barátjával. Menj békében, tenger fia!");
			link.l1 = RandPhraseSimple("Sok szerencsét neked is, a szelva fia...","Isten veled, vörösbôrû barátom.");
			link.l1.go = "exit_peace";
		break;
		
		case "peace_indian_2":
			dialog.text = RandPhraseSimple("Mi békés vadászok. De nem tûrjük, hogy sápadtarcúak így beszéljenek a földünkön!","Mi nem harcolunk a fehérekkel, de ha a fehérek megbántanak minket, úgy válaszolunk, ahogy ôseink tanították!");
			link.l1 = RandPhraseSimple("Még mindig nem tudod befogni a büdös szádat, festett madárijesztô? Visszaviszlek a dzsungelbe, ahonnan jöttél!","Mersz fenyegetni engem, te szemétláda?! Most pedig visszamászol arra a fára, ahonnan az elôbb jöttél le!");
			link.l1.go = "exit_fight";
		break;
	}
}
