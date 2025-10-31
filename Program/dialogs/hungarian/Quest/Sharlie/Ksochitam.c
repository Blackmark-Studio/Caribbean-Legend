// диалоги НПС по квесту Коварный остров Ксочитэм
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Van valami, amit szeretnél?";
			link.l1 = "Nem, semmit.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// капитан-нежить Санта-Квитерии
		case "SQC_skeletcap":
			PlaySound("Types\skel.wav");
			dialog.text = "Neked... még mindig.... kell... meghalnod. El fog jönni... és megöl téged... ahogy mindannyiunkat megölt... ahogy mindenkit megölt itt...";
			link.l1 = "Micsoda? Ki vagy te? Kirôl beszélsz?";
			link.l1.go = "SQC_skeletcap_1";
		break;
		
		case "SQC_skeletcap_1":
			PlaySound("Types\skel.wav");
			dialog.text = "Hatalmas... sebezhetetlen... gyilkol... meg fog ölni téged. Meg kell öljelek... ha megöllek, nem leszel olyan, mint mi... nem érted... a kardja által fogsz meghalni... olyanná válsz, mint mi... mint mindenki a Santa Quiteria-n...";
			link.l1 = "Nem lehet!";
			link.l1.go = "SQC_skeletcap_2";
		break;
		
		case "SQC_skeletcap_2":
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for(i=2; i<=3; i++)
			{
				sld = characterFromId("SQI_skelet_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Ksochitam_SQCskeletcapdie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// Страж маски Кукулькана
		case "guardmask":
			PlaySound("Voice\English\sharlie\Hranitel Maski Kukulkana.wav");
			dialog.text = "Olyan régóta vártam rád!...";
			link.l1 = "Erm!... Lenyûgözô!... Ez aztán a csontváz!";
			link.l1.go = "guardmask_1";
		break;
		
		case "guardmask_1":
			dialog.text = "Látom... Érzem... Elhoztad nekem... a szabadságomat...";
			link.l1 = "Mirôl beszélsz? Mirôl beszélsz?!";
			link.l1.go = "guardmask_2";
		break;
		
		case "guardmask_2":
			dialog.text = "Én vagyok Ksocheatem ôrzôje, Kukulcan maszkjának ôrzôje... és a közelgô halálod!...";
			link.l1 = "...";
			link.l1.go = "guardmask_3";
		break;
		
		case "guardmask_3":
			PlaySound("Ambient\Teno_inside\big_ring.wav");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "KSOCHITAM_MONSTERS");
			LAi_group_FightGroups("KSOCHITAM_MONSTERS", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			DoQuestFunctionDelay("Terrapin_SetMusic", 1.2);
			n = Findlocation("Shore_mask");
			locations[n].type = "seashore";
			pchar.questTemp.Ksochitam.GuardMaskFight = "true";
			for (i=1; i<=4; i++)
			{
				CreateLocationParticles("fire_incas_Simple", "fire_incas", "fire_incas"+i, 1, 0, 0, "fortfire");
				CreateLocationParticles("fire_incas_Simple", "fire_incas", "fire_incas"+i, 2.5, 0, 0, "fortfire");
			}
		break;
		
		case "guardmask_4":
			PlaySound("Voice\English\sharlie\Hranitel Maski Kukulkana.wav");
			dialog.text = "Állj...";
			link.l1 = "És miért tennék ilyet, mi? Kifogytál a levegôbôl, csontzsák?";
			link.l1.go = "guardmask_5";
		break;
		
		case "guardmask_5":
			dialog.text = "Nem. Nem fogsz tudni megölni, soha. Még azzal a mágikus tôrrel sem. A párbajunk hosszú-hosszú ideig tarthat, amíg teljesen elfogy az erôd és meghalsz.";
			link.l1 = "Valóban? És miért nem tudsz megütni?";
			link.l1.go = "guardmask_6";
		break;
		
		case "guardmask_6":
			dialog.text = "Te egy bátor, erôs harcos vagy, és a Fônök Karma van a kezedben. Kötelességem életben hagyni téged, mert aki birtokolja ezt a tôrt, aki szembe mer szállni velem a csatában, az megkapja, amiért jött.";
			link.l1 = "Ki vagy te? Ki vagy te valójában, Ôrzô?";
			link.l1.go = "guardmask_7";
		break;
		
		case "guardmask_7":
			dialog.text = "Alberto Cascónak hívtak. Alonso de Maldonado csapatának katonája voltam. Megtaláltuk az ôsi Tayasalt, de elfogtak és feláldoztak minket. Magasságom és erôm miatt a pogány Kanek Ksocheatem ôrzôjévé, Kukulcan maszkjának ôrzôjévé tett. Mindenkit, aki valaha Ksocheatemben állt, én találtam meg, és a kezem által lemészároltam, majd élôhalottá változtattam.\nA Fônök karma tôrével a húsomba vésték ennek a helynek a térképét. Örökké vigyázni fogok a maszk biztonságára, és nyughatatlan leszek, amíg a kezemben nem tartom a tôrt.";
			link.l1 = "Szükséged van a Fônök karma tôrre?";
			link.l1.go = "guardmask_8";
		break;
		
		case "guardmask_8":
			dialog.text = "Igen. Mivel szükséged van a maszkra. Add ide a tôrt. Megtalálom a régóta várt békémet, te pedig megkapod a maszkot. Esküszöm neked, hogy magaddal viheted, és élve hagyhatod el Ksocheatemet.";
			link.l1 = "Elfogadom az ajánlatodat, Ôrzô. Láttam a maszkot azon a talapzaton a keresztelôkút mögött. Ez az?";
			link.l1.go = "guardmask_9";
		break;
		
		case "guardmask_9":
			dialog.text = "Igen, az. Ez maga Kukulcan, a repülô kígyó hatalmas ereklyéje. Miután befejeztük ezt a beszélgetést, odasétálhatsz és elveheted.";
			link.l1 = "Nos, remélem, megtartod a szavad, Ôrzô...";
			link.l1.go = "guardmask_10";
		break;
		
		case "guardmask_10":
			dialog.text = "Megesküdtem...";
			link.l1 = "Akkor vedd el a Fônök karmait. Remélem, nyugalmat hoz majd a lelkedre.";
			link.l1.go = "guardmask_11";
		break;
		
		case "guardmask_11":
			RemoveItems(pchar, "knife_01", 1);
			PlaySound("interface\important_item.wav");
			Log_Info("Átadtad a fônök karmait.");
			RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
			dialog.text = "Ó, milyen régóta vártam ezt a pillanatot! Most végre elmehetek... De búcsúajándékként szeretném átadni neked erôm egy részecskéjét. Ez lesz az utolsó ajándék, amit Alberto Casco valaha is ad.";
			link.l1 = "...";
			link.l1.go = "guardmask_12";
		break;
		
		case "guardmask_12":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Ksochitam_GuardMaskGift", 1.5);
		break;
		
		case "guardmask_13":
			dialog.text = "Itt az ideje, hogy elmenjek. Ne húzzátok az idôt, az Ôrzôje és a Kukulcan maszk nélkül a sziget hamarosan örökre eltûnik.";
			link.l1 = "Nincs mit sajnálni. Egy pokollal kevesebb a világon... De várj, Ôrzô! Te már jártál Tayasalban! Kérlek, mondd el, mi az a hely.";
			link.l1.go = "guardmask_14";
		break;
		
		case "guardmask_14":
			dialog.text = "Ez egy régi maja város. A külsejét megôrizték abból az idôbôl, amikor az emberek még ott laktak. Fenséges templomok, magas piramisok... Most az Itza törzs él ott, azt állítva, hogy ôk a maják közvetlen leszármazottai. Mindenben próbálják utánozni ôket, a vallásban, a kultúrában és az életmódjukban.";
			link.l1 = "Hogyan juthatok el oda?";
			link.l1.go = "guardmask_15";
		break;
		
		case "guardmask_15":
			dialog.text = "A parancsnokunk, Alonso de Maldonado ismerte az utat. Mi csak követtük ôt a dzsungelen keresztül. Csak arra emlékszem, hogy a Mosquito öbölnél szálltunk partra, a Perlas-foktól északra, és nyugat felé mélyen a selva belsejébe vonultunk.";
			link.l1 = "Mi említésre méltó Tayasalban?";
			link.l1.go = "guardmask_16";
		break;
		
		case "guardmask_16":
			dialog.text = "Ott minden figyelemre méltó. Abszolút minden. De minket semmi más nem érdekelt, csak a maja kincsek. És meg is találtuk ôket. És drágán fizettünk értük, különösen én. De most végre szabad vagyok!";
			link.l1 = "Mit kell tudnom, mielôtt Tayasalba indulok?";
			link.l1.go = "guardmask_17";
		break;
		
		case "guardmask_17":
			dialog.text = "Az itzai emberek nagy erôvel és szellemességgel rendelkeznek. Gyûlölik a fehér embereket, nemzetiségre való tekintet nélkül, és minden kívülállót elpusztítanak, aki a területükre hatol. Az egyszerû itza harcosok nem bocsátkoznak semmiféle kommunikációba, de Kanek vagy a fia, Urakan, ha meglátják a maszkot... talán igen. Ha sikerül élve eljutnod Tayasalba, akkor meglátod a saját szemeddel. De vajon képes leszel-e elhagyni...";
			link.l1 = "Kanek feláldozza az összes fehér embert, aki Tayasalba jön?";
			link.l1.go = "guardmask_18";
		break;
		
		case "guardmask_18":
			dialog.text = "Azt hiszem, igen. De ez nem biztos, hogy a Kukulcan maszkot viselô férfira vonatkozik.";
			link.l1 = "Rendben, akkor... Erre számítok.";
			link.l1.go = "guardmask_19";
		break;
		
		case "guardmask_19":
			dialog.text = "Viszlát, katona. Remélem, hogy a maszk erejét a megfelelô célra fogja használni.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("Ksochitam_GuardMaskGoAway");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
