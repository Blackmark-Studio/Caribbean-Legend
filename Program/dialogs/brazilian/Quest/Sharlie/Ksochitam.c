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
			dialog.text = "Você quer alguma coisa?";
			link.l1 = "Não, nada.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// капитан-нежить Санта-Квитерии
		case "SQC_skeletcap":
			PlaySound("Types\skel.wav");
			dialog.text = "Você... ainda vai... ter... que morrer. Ele vai vir... e te matar... como matou todos nós... como matou todo mundo aqui...";
			link.l1 = "O quê? Quem é você? De quem você está falando?";
			link.l1.go = "SQC_skeletcap_1";
		break;
		
		case "SQC_skeletcap_1":
			PlaySound("Types\skel.wav");
			dialog.text = "Ele é enorme... ele é invulnerável... ele mata... ele vai te matar. Eu preciso te matar... se eu te matar, você não vai se tornar como a gente... você não entende... você vai morrer pela espada dele... vai virar o que nós somos... como todo mundo na Santa Quiteria...";
			link.l1 = "De jeito nenhum!";
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
			dialog.text = "Esperei tanto por você!..";
			link.l1 = "Erm!.. Espantoso!... Isso sim é um esqueleto!";
			link.l1.go = "guardmask_1";
		break;
		
		case "guardmask_1":
			dialog.text = "Eu vejo... Eu sinto... Você me trouxe... a minha liberdade...";
			link.l1 = "Do que você está falando? O que você é?!";
			link.l1.go = "guardmask_2";
		break;
		
		case "guardmask_2":
			dialog.text = "Eu sou o Guardião de Ksocheatem, o portador da máscara de Kukulcan... e a sua morte iminente!..";
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
			dialog.text = "Pare...";
			link.l1 = "E por que eu faria isso, hein? Tá cansado, saco de ossos?";
			link.l1.go = "guardmask_5";
		break;
		
		case "guardmask_5":
			dialog.text = "Não. Você nunca vai conseguir me matar. Nem mesmo com essa adaga mágica. Nosso duelo pode durar muito, muito tempo, até que você esteja completamente exausto e morra.";
			link.l1 = "É mesmo? E por que você não pode me atacar?";
			link.l1.go = "guardmask_6";
		break;
		
		case "guardmask_6":
			dialog.text = "Você é um guerreiro corajoso e forte, e empunha a Garra do Chefe. Sou obrigado a poupar sua vida, pois aquele que possui esta adaga, que ousa me enfrentar em combate, recebe aquilo que veio buscar.";
			link.l1 = "Quem é você? Quem é você de verdade, Guardião?";
			link.l1.go = "guardmask_7";
		break;
		
		case "guardmask_7":
			dialog.text = "Costumavam me chamar de Alberto Casco. Fui soldado no esquadrão de Alonso de Maldonado. Encontramos a antiga Tayasal, mas fomos capturados e sacrificados. Por causa da minha altura e força, o pagão Kanek me transformou no Guardião de Ksocheatem, o protetor da máscara de Kukulcan. Todos que pisaram em Ksocheatem foram encontrados por mim, mortos pelas minhas mãos e depois transformados em mortos-vivos.\nA adaga Garra do Chefe foi usada para entalhar um mapa deste lugar na minha carne. Vou vigiar a segurança da máscara para sempre, e não terei descanso até segurar a adaga em minhas mãos.";
			link.l1 = "Você precisa da Garra do Chefe?";
			link.l1.go = "guardmask_8";
		break;
		
		case "guardmask_8":
			dialog.text = "Sim. Já que você precisa da máscara, me dê a adaga. Assim, encontrarei a paz que tanto busquei e você receberá a máscara. Juro que poderá levá-la com você e sair de Ksocheatem com vida.";
			link.l1 = "Eu aceito sua oferta, Guardião. Vi a máscara naquele pedestal atrás da fonte do batistério. É essa mesmo?";
			link.l1.go = "guardmask_9";
		break;
		
		case "guardmask_9":
			dialog.text = "É isso mesmo. Este é o poderoso artefato do próprio Kukulcan, a serpente alada. Assim que terminarmos esta conversa, você pode ir até lá e pegá-lo.";
			link.l1 = "Bem, espero que cumpra sua palavra, Guardião...";
			link.l1.go = "guardmask_10";
		break;
		
		case "guardmask_10":
			dialog.text = "Eu jurei...";
			link.l1 = "Então leve a Garra do Chefe. Espero que ela traga tranquilidade para sua alma.";
			link.l1.go = "guardmask_11";
		break;
		
		case "guardmask_11":
			RemoveItems(pchar, "knife_01", 1);
			PlaySound("interface\important_item.wav");
			Log_Info("You've given the Chief's Claw");
			RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
			dialog.text = "Oh, por quanto tempo esperei por este momento! Agora finalmente posso partir... Mas, como presente de despedida, gostaria de lhe passar um fragmento do meu poder. Este será o último presente que Alberto Casco dará a alguém.";
			link.l1 = "...";
			link.l1.go = "guardmask_12";
		break;
		
		case "guardmask_12":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Ksochitam_GuardMaskGift", 1.5);
		break;
		
		case "guardmask_13":
			dialog.text = "Now it's time for me to leave. Don't waste any time; without its Guardian and the Kukulcan mask, the island will soon disappear forever.";
			link.l1 = "Não há nada do que se arrepender nisso. Um inferno a menos no mundo... Mas espere, Guardião! Você já esteve em Tayasal! Por favor, me conte como é aquele lugar.";
			link.l1.go = "guardmask_14";
		break;
		
		case "guardmask_14":
			dialog.text = "É uma antiga cidade maia. Sua aparência foi preservada desde a época em que ainda era habitada. Templos majestosos, pirâmides imponentes... Agora, lá vive a tribo Itza, que afirma ser descendente direta dos maias. Eles tentam imitá-los em tudo: na religião, na cultura e no modo de vida.";
			link.l1 = "Como eu chego lá?";
			link.l1.go = "guardmask_15";
		break;
		
		case "guardmask_15":
			dialog.text = "Nosso comandante sabia o caminho, Alonso de Maldonado. Só seguimos ele pela selva. Só me lembro que desembarcamos na Baía dos Mosquitos, ao norte do Cabo Perlas, e seguimos selva adentro para o oeste.";
			link.l1 = "O que há de interessante em Tayasal?";
			link.l1.go = "guardmask_16";
		break;
		
		case "guardmask_16":
			dialog.text = "Tudo lá chama atenção. Absolutamente tudo. Mas só nos interessavam os tesouros maias. E nós os encontramos. E pagamos caro por eles, especialmente eu. Mas agora, finalmente estou livre!";
			link.l1 = "O que devo saber antes de ir para Tayasal?";
			link.l1.go = "guardmask_17";
		break;
		
		case "guardmask_17":
			dialog.text = "O povo Itza é muito forte e astuto. Eles odeiam os brancos, não importa a nacionalidade, e destroem qualquer forasteiro que invada seu território. Os guerreiros comuns dos Itza não vão conversar de jeito nenhum, mas Kanek ou o filho dele, Urakan, se virem a máscara... talvez aceitem falar. Se você conseguir chegar vivo a Tayasal, vai ver com seus próprios olhos. Mas será que vai conseguir sair de lá...";
			link.l1 = "Kanek oferece todos os brancos que chegam a Tayasal como sacrifício?";
			link.l1.go = "guardmask_18";
		break;
		
		case "guardmask_18":
			dialog.text = "Eu acho que sim. Mas talvez isso não inclua o homem que usa a máscara de Kukulcán.";
			link.l1 = "Certo. Vou contar com isso.";
			link.l1.go = "guardmask_19";
		break;
		
		case "guardmask_19":
			dialog.text = "Até logo, soldado. Espero que você use o poder da máscara para o bem.";
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
