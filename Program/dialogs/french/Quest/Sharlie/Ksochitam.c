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
			dialog.text = "Y a-t-il quelque chose que tu désires ?";
			link.l1 = "Non, rien.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// капитан-нежить Санта-Квитерии
		case "SQC_skeletcap":
			PlaySound("Types\skel.wav");
			dialog.text = "Tu... devras encore... mourir. Il viendra... et te tuera... comme il nous a tous tués... comme il a tué tout le monde ici...";
			link.l1 = "Quoi ? Qui êtes-vous ? De qui parlez-vous ?";
			link.l1.go = "SQC_skeletcap_1";
		break;
		
		case "SQC_skeletcap_1":
			PlaySound("Types\skel.wav");
			dialog.text = "Il est immense... il est invulnérable... il tue... il va te tuer. Je dois te tuer... si je te tue, tu ne deviendras pas comme nous... tu ne comprends pas... tu mourras par son épée... tu te transformeras en ce que nous sommes... comme tout le monde sur la Santa Quiteria...";
			link.l1 = "Pas question !";
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
			dialog.text = "Je t'ai attendu si longtemps !..";
			link.l1 = "Erm!.. Époustouflant!... C'est un sacré squelette !";
			link.l1.go = "guardmask_1";
		break;
		
		case "guardmask_1":
			dialog.text = "Je le vois... Je le ressens... Tu m'as apporté... ma liberté...";
			link.l1 = "De quoi parles-tu ? Qu'es-tu ? ";
			link.l1.go = "guardmask_2";
		break;
		
		case "guardmask_2":
			dialog.text = "Je suis le Gardien de Ksocheatem, le gardien du masque de Kukulcan... et ta mort imminente!..";
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
			dialog.text = "Arrête...";
			link.l1 = "Et pourquoi devrais-je faire ça, hein? T'es à bout de souffle, sac d'os?";
			link.l1.go = "guardmask_5";
		break;
		
		case "guardmask_5":
			dialog.text = "Non. Tu ne pourras jamais me tuer. Pas même avec ce poignard magique. Notre duel peut durer très, très longtemps jusqu'à ce que tu sois complètement épuisé et que tu meures.";
			link.l1 = "Vraiment ? Et pourquoi ne peux-tu pas m'attaquer ?";
			link.l1.go = "guardmask_6";
		break;
		
		case "guardmask_6":
			dialog.text = "Tu es un guerrier courageux et fort, et tu brandis la Griffe du Chef. Je suis obligé de te laisser vivre, car celui ou celle qui possède ce poignard, qui ose se dresser contre moi au combat, reçoit ce pour quoi il est venu.";
			link.l1 = "Qui es-tu ? Qui es-tu vraiment, Gardien ?";
			link.l1.go = "guardmask_7";
		break;
		
		case "guardmask_7":
			dialog.text = "Ils m'appelaient autrefois Alberto Casco. J'étais soldat dans l'escouade d'Alonso de Maldonado. Nous avions trouvé l'ancien Tayasal, mais ils nous ont attrapés et sacrifiés. En raison de ma taille et de ma force, le païen Kanek m'a transformé en Gardien de Ksocheatem, le gardien du masque de Kukulcan. Tous ceux qui ont jamais mis le pied sur Ksocheatem ont été découverts par moi et massacrés de ma main, puis transformés en morts-vivants.\nLe poignard Griffe du Chef a été utilisé pour graver une carte de cet endroit sur ma chair. Je veillerai à la sécurité du masque pour toujours et je serai sans repos, jusqu'à ce que je tienne le poignard dans mes mains.";
			link.l1 = "As-tu besoin de la Griffe du Chef?";
			link.l1.go = "guardmask_8";
		break;
		
		case "guardmask_8":
			dialog.text = "Oui. Puisque tu as besoin du masque. Donne-moi la dague. Je trouverai enfin la paix tant attendue et tu recevras le masque. Je te jure que tu pourras l'emporter avec toi et quitter Ksocheatem vivant.";
			link.l1 = "J'accepte votre offre, Gardien. J'ai vu le masque sur ce piédestal derrière la fontaine du baptistère. Est-ce bien cela ?";
			link.l1.go = "guardmask_9";
		break;
		
		case "guardmask_9":
			dialog.text = "C'est ça. C'est l'artefact puissant de Kukulcan lui-même, le serpent volant. Après que nous ayons terminé cette conversation, tu pourras y aller et le prendre.";
			link.l1 = "Eh bien, j'espère que tu tiendras parole, Gardien...";
			link.l1.go = "guardmask_10";
		break;
		
		case "guardmask_10":
			dialog.text = "J'ai juré...";
			link.l1 = "Alors prends la Griffe du Chef. J'espère qu'elle apportera la tranquillité à ton âme.";
			link.l1.go = "guardmask_11";
		break;
		
		case "guardmask_11":
			RemoveItems(pchar, "knife_01", 1);
			PlaySound("interface\important_item.wav");
			Log_Info("You've given the Chief's Claw");
			RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
			dialog.text = "Oh, combien j'ai attendu ce moment ! Maintenant je peux enfin partir... Mais comme cadeau d'adieu, j'aimerais vous transmettre une parcelle de mon pouvoir. Ce sera le dernier présent qu'Alberto Casco offrira jamais.";
			link.l1 = "...";
			link.l1.go = "guardmask_12";
		break;
		
		case "guardmask_12":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Ksochitam_GuardMaskGift", 1.5);
		break;
		
		case "guardmask_13":
			dialog.text = "Il est temps pour moi de partir. Ne traîne pas, sans son Gardien et le masque de Kukulcan, l'île disparaîtra bientôt à jamais.";
			link.l1 = "Il n'y a rien à regretter à ce sujet. Un enfer de moins dans le monde... Mais attendez, Gardien ! Vous avez été à Tayasal ! S'il vous plaît, dites-moi ce qu'est cet endroit.";
			link.l1.go = "guardmask_14";
		break;
		
		case "guardmask_14":
			dialog.text = "C'est une vieille cité maya. Son apparence a été conservée depuis l'époque où des gens y résidaient encore. Des temples majestueux, de hautes pyramides... Maintenant, la tribu Itza y vit, prétendant être les descendants directs des Mayas. Ils essaient de les imiter de toutes les manières, en religion, culture et mode de vie.";
			link.l1 = "Comment puis-je y arriver ?";
			link.l1.go = "guardmask_15";
		break;
		
		case "guardmask_15":
			dialog.text = "Notre commandant connaissait le chemin, Alonso de Maldonado. Nous l'avons simplement suivi à travers la jungle. Je me souviens seulement que nous avons débarqué à la baie des Moustiques, au nord du cap Perlas, et que nous avons avancé profondément dans la selva à l'ouest.";
			link.l1 = "Qu'y a-t-il de remarquable à Tayasal ?";
			link.l1.go = "guardmask_16";
		break;
		
		case "guardmask_16":
			dialog.text = "Tout est digne d'intérêt là-bas. Absolument tout. Mais nous n'étions intéressés que par les trésors mayas. Et nous les avons trouvés. Et nous les avons payés chèrement, surtout moi. Mais maintenant, je suis enfin libre !";
			link.l1 = "Que dois-je savoir avant de me rendre à Tayasal ?";
			link.l1.go = "guardmask_17";
		break;
		
		case "guardmask_17":
			dialog.text = "Les Itza possèdent une grande force et une vive intelligence. Ils détestent les blancs, peu importe leur nationalité, et détruiront tout étranger envahissant leur territoire. Les simples guerriers Itza n'engageront aucune communication, mais Kanek ou son fils Urakan, s'ils voient le masque... peut-être qu'ils le feront. Si tu parviens à atteindre Tayasal vivant, tu verras par toi-même. Mais seras-tu capable d'en repartir...";
			link.l1 = "Kanek offre-t-il en sacrifice tous les Blancs venant à Tayasal?";
			link.l1.go = "guardmask_18";
		break;
		
		case "guardmask_18":
			dialog.text = "Je le supposerais. Mais cela pourrait ne pas inclure l'homme qui porte le masque de Kukulcan.";
			link.l1 = "D'accord. Je compterai là-dessus.";
			link.l1.go = "guardmask_19";
		break;
		
		case "guardmask_19":
			dialog.text = "Adieu, soldat. J'espère que tu utiliseras le pouvoir du masque à bon escient.";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuest("Ksochitam_GuardMaskGoAway");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
