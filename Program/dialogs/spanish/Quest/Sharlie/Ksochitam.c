// диалоги НПС по квесту Коварный остров Ксочитэм
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "¿Hay algo que quieras?";
		link.l1 = "No, nada.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	// капитан-нежить Санта-Квитерии
	case "SQC_skeletcap":
		PlaySound("Types\Spanish\skel-02.wav");
		dialog.text = "Tú... aún tendrás... que morir. Él vendrá... y te matará... como nos ha matado a todos nosotros... como ha matado a todos aquí...";
		link.l1 = "¿Qué? ¿Quién eres tú? ¿De quién estás hablando?";
		link.l1.go = "SQC_skeletcap_1";
		break;

	case "SQC_skeletcap_1":
		PlaySound("Types\Spanish\skel-02.wav");
		dialog.text = "Es enorme... es invulnerable... mata... te matará. Debo matarte... si te mato, no te convertirás en uno de nosotros... no entiendes... morirás por su espada... te convertirás en lo que somos... como todos en la Santa Quiteria...";
		link.l1 = "¡De ninguna manera!";
		link.l1.go = "SQC_skeletcap_2";
		break;

	case "SQC_skeletcap_2":
		DialogExit();
		LAi_SetWarriorType(npchar);
		LAi_SetImmortal(npchar, false);
		LAi_SetCurHPMax(npchar);
		LAi_GetCharacterMaxEnergy(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		for (i = 2; i <= 3; i++)
		{
			sld = characterFromId("SQI_skelet_" + i);
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
		PlaySound("Voice\Spanish\sharlie\Hranitel Maski Kukulkana.wav");
		dialog.text = "¡He estado esperando por ti, desde hace mucho tiempo!";
		link.l1 = "¡Erm!.. ¡Impresionante!... ¡Es todo un esqueleto!";
		link.l1.go = "guardmask_1";
		break;

	case "guardmask_1":
		dialog.text = "Lo veo... Lo siento... Me has traído... mi libertad...";
		link.l1 = "¿De qué estás hablando? ¡¿Qué eres tú?!";
		link.l1.go = "guardmask_2";
		break;

	case "guardmask_2":
		dialog.text = "Soy el Guardián de Ksocheatem, el custodio de la máscara de Kukulcán... ¡y tu eminente muerte!..";
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
		for (i = 1; i <= 4; i++)
		{
			CreateLocationParticles("fire_incas_Simple", "fire_incas", "fire_incas" + i, 1, 0, 0, "fortfire");
			CreateLocationParticles("fire_incas_Simple", "fire_incas", "fire_incas" + i, 2.5, 0, 0, "fortfire");
		}
		break;

	case "guardmask_4":
		PlaySound("Voice\Spanish\sharlie\Hranitel Maski Kukulkana.wav");
		dialog.text = "Detente...";
		link.l1 = "¿Y por qué debería hacer eso, eh? ¿Te falta el aliento, saco de huesos?";
		link.l1.go = "guardmask_5";
		break;

	case "guardmask_5":
		dialog.text = "No. Nunca podrás matarme, jamás. Ni siquiera con ese puñal mágico. Nuestro duelo puede durar un tiempo muy, muy largo hasta que te quedes completamente sin fuerzas y mueras.";
		link.l1 = "¿Es así? ¿Y por qué es que no puedes golpearme?";
		link.l1.go = "guardmask_6";
		break;

	case "guardmask_6":
		dialog.text = "Eres un valiente y fuerte guerrero y empuñas la Garra del Jefe. Estoy obligado a dejarte vivir, pues aquel o aquella que posea este puñal, que se atreva a enfrentarse a mí en batalla, recibe lo que ha venido a buscar.";
		link.l1 = "¿Quién eres tú? ¿Quién eres realmente, Guardián?";
		link.l1.go = "guardmask_7";
		break;

	case "guardmask_7":
		dialog.text = "Solían llamarme Alberto Casco. Fui soldado en el escuadrón de Alonso de Maldonado. Habíamos encontrado el antiguo Tayasal, pero nos atraparon y nos sacrificaron. Debido a mi altura y mi fuerza, el pagano Kanek me convirtió en el Guardián de Ksocheatem, el custodio de la máscara de Kukulkán. Todos los que alguna vez pisaron Ksocheatem fueron encontrados por mí y masacrados por mi mano y luego convertidos en no-muertos.\nLa daga Garra del Jefe fue utilizada para tallar un mapa de este lugar en mi carne. Vigilaré la seguridad de la máscara por siempre y no descansaré hasta tener la daga en mis manos.";
		link.l1 = "¿Necesitas la Garra del Jefe?";
		link.l1.go = "guardmask_8";
		break;

	case "guardmask_8":
		dialog.text = "Sí. Ya que necesitas la máscara. Dame la daga. Encontraré mi tan ansiada paz y tú recibirás la máscara. Te juro que podrás llevártela contigo y dejar Ksocheatem con vida.";
		link.l1 = "Acepto tu oferta, Guardián. He visto la máscara en ese pedestal detrás de la fuente bautismal. ¿Es esa?";
		link.l1.go = "guardmask_9";
		break;

	case "guardmask_9":
		dialog.text = "Así es. Este es el poderoso artefacto del mismo Kukulcán, la serpiente emplumada. Después de que terminemos esta conversación, puedes caminar hasta allí y tomarlo.";
		link.l1 = "Bueno, espero que cumplas tu palabra, Guardián...";
		link.l1.go = "guardmask_10";
		break;

	case "guardmask_10":
		dialog.text = "He jurado...";
		link.l1 = "Entonces toma la Garra del Jefe. Espero que traiga tranquilidad a tu alma.";
		link.l1.go = "guardmask_11";
		break;

	case "guardmask_11":
		RemoveItems(pchar, "knife_01", 1);
		PlaySound("interface\important_item.wav");
		Log_Info("¡Has entregado la Garra del Jefe!");
		RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
		dialog.text = "¡Oh, cuánto tiempo he esperado este momento! Ahora, por fin puedo irme... Pero como regalo de despedida, me gustaría transmitirte una partícula de mi poder. Este será el último presente que Alberto Casco dará jamás.";
		link.l1 = "...";
		link.l1.go = "guardmask_12";
		break;

	case "guardmask_12":
		DialogExit();
		LAi_SetActorType(pchar);
		DoQuestCheckDelay("Ksochitam_GuardMaskGift", 1.5);
		break;

	case "guardmask_13":
		dialog.text = "Ahora es hora de que me vaya. No te demores, sin su Guardián y la máscara de Kukulcán, la isla pronto desaparecerá para siempre.";
		link.l1 = "No hay nada que lamentar al respecto. Un agujero del infierno menos en el mundo... Pero espera, ¡Guardián! ¡Has estado en Tayasal! Por favor, dime qué es ese lugar.";
		link.l1.go = "guardmask_14";
		break;

	case "guardmask_14":
		dialog.text = "Es una antigua ciudad maya. Su apariencia se ha conservado desde cuando la gente aún residía allí. Majestuosos templos, altas pirámides... Ahora, la tribu Itza vive allí, afirmando ser los descendientes directos de los mayas. Intentan imitarlos en todos los aspectos, en religión, cultura y su forma de vida.";
		link.l1 = "¿Cómo puedo llegar allí?";
		link.l1.go = "guardmask_15";
		break;

	case "guardmask_15":
		dialog.text = "Nuestro comandante conocía el camino, Alonso de Maldonado. Solo lo seguimos a través de la jungla. Solo recuerdo que desembarcamos en la bahía de Mosquito, al norte del Cabo Perlas, y nos adentramos en la selva hacia el Oeste.";
		link.l1 = "¿Qué hay de notable en Tayasal?";
		link.l1.go = "guardmask_16";
		break;

	case "guardmask_16":
		dialog.text = "Todo es digno de mención allí. Absolutamente todo. Pero no nos interesaba nada más que los tesoros mayas. Y los encontramos. Y pagamos caro por ellos, especialmente yo. ¡Pero ahora, por fin soy libre!";
		link.l1 = "¿Qué necesito saber antes de dirigirme a Tayasal?";
		link.l1.go = "guardmask_17";
		break;

	case "guardmask_17":
		dialog.text = "El pueblo Itza posee gran fuerza e ingenio. Odian a los blancos sin importar su nacionalidad y destruirán a cualquier extranjero que invada su territorio. Los simples guerreros Itza no se involucrarán en ningún tipo de comunicación, pero Kanek o su hijo Urakan, si ven la máscara... podrían hacerlo. Si logras llegar a Tayasal con vida, lo verás por ti mismo. Pero, ¿serás capaz de salir de allí...?";
		link.l1 = "¿Ofrece Kanek a todos los blancos que llegan a Tayasal como sacrificio?";
		link.l1.go = "guardmask_18";
		break;

	case "guardmask_18":
		dialog.text = "Supongo que sí. Pero eso podría no incluir al hombre que lleva la máscara de Kukulcán.";
		link.l1 = "Está bien. Contaré con eso.";
		link.l1.go = "guardmask_19";
		break;

	case "guardmask_19":
		dialog.text = "Adiós, soldado. Espero que uses el poder de la máscara para el propósito correcto.";
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
