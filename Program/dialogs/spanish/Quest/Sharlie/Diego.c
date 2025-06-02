// Диего де Монтойя
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "¿Hay algo que desees?";
			link.l1 = "No, nada.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "patrol":
			dialog.text = TimeGreeting()+", "+GetFullName(npchar)+", Jefe de la patrulla de San José. Hemos recibido un mensaje sobre un comportamiento sospechoso en las afueras de esta ciudad. ¿Serías tan amable de explicarnos quién eres y qué estás haciendo?";
			link.l1 = "Capitán "+GetFullName(pchar)+", señor oficial. Estoy aquí bajo la autoridad e instrucciones directas del Inquisidor Padre Vincento. Aquí está un documento que confirma mi autorización.";
			link.l1.go = "patrol_1";
		break;
		
		case "patrol_1":
			dialog.text = "Está bien... Todo parece en orden. Está debidamente escrito con la firma del inquisidor. Mis disculpas por mis sospechas. ¿Qué haces en el faro?";
			link.l1 = "No estoy autorizado para responder a tales preguntas. Si está genuinamente interesado en el propósito de mi trabajo para el inquisidor, le recomendaría dirigirse directamente a él en Santiago, para obtener aclaraciones. Usted es un oficial, seguramente tiene conocimiento de secretos militares y de servicio. Lo único que puedo decirle es que estoy investigando las circunstancias de un naufragio de un barco español.";
			link.l1.go = "patrol_2";
		break;
		
		case "patrol_2":
			dialog.text = "Mis disculpas una vez más, monsieur. No me atreveré a retrasarlo más... ¡ah, un momento! ¿Acabo de ver la hoja de un acero frío, o fue solo mi imaginación? ¡Qué daga tan interesante tienes! ¿Puedes mostrármela?";
			link.l1 = "Asegúrate de no olvidar devolverla. Es muy importante para mí.";
			link.l1.go = "patrol_3";
		break;
		
		case "patrol_3":
			dialog.text = "¡Dios mío! ¡Conozco este puñal, lo vi en uno de los libros de la biblioteca! ¡Este es el puñal del propio Cortés! Está marcado justo aquí... Monsieur, por favor no se niegue. ¡Déjeme tener este puñal! Colecciono armas antiguas y personalizadas, y este es simplemente un objeto increíble. Le pagaré bien por él.";
			link.l1 = "Señor, este puñal no está en venta. Lo recibí como un regalo, y no tengo intención de venderlo a nadie. Devuélvamelo, por favor.";
			link.l1.go = "patrol_4";
		break;
		
		case "patrol_4":
			dialog.text = "¿Ni siquiera estarás contento con quinientos doblones de oro? Eso es un montón de dinero. ¡Podrías comprar un barco con eso!";
			link.l1 = "No. Ya tengo un barco y la daga es única en su tipo. No la venderé.";
			link.l1.go = "patrol_5";
		break;
		
		case "patrol_5":
			dialog.text = "Eh, qué lástima... Está bien, toma tu valioso tesoro. No me atreveré a molestarte más. ¡Buena suerte!";
			link.l1 = "Todo lo mejor para usted, oficial.";
			link.l1.go = "patrol_6";
		break;
		
		case "patrol_6":
			DialogExit();
			AddQuestRecord("Guardoftruth", "42");
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "GuardOT_ClearMayakPatrol", 12.0);
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("GOT_spamayaksold_"+i);
				sld.lifeday = 0;
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", 10.0);
			}
		break;
		
		case "shore":
			PlaySound("Voice\Spanish\Sharlie\Diego De Montoya.wav");
			dialog.text = "¡Basta! Quiero hablar con él...";
			link.l1 = "Entonces, veo al propio Diego de Montoya justo frente a mí... Pero disculpe, señor. Nos hemos visto antes, ¿verdad? Ah, sí, es cierto. Trinidad, en el faro. Pero estoy seguro de que allí se hacía llamar de otra manera...";
			link.l1.go = "shore_1";
		break;
		
		case "shore_1":
			dialog.text = "Su memoria le sirve bien, señor. Bueno, no eres el único capaz de encender intrigas y librar guerras entre bastidores. Estoy bien informado de su deseo inquebrantable de verme. Vaya, parece que su deseo se ha hecho realidad.";
			link.l1 = "Este no era exactamente el tipo de encuentro que esperaba, señor.";
			link.l1.go = "shore_2";
		break;
		
		case "shore_2":
			dialog.text = "Bueno, es lo que es. Pero te daré una oportunidad de salir de aquí con vida si me das tu daga.";
			link.l1 = "¿Tu pasión por coleccionar rarezas realmente te ha llevado tan lejos por las cañerías, caballero, que has tenido que preparar una trampa tan bien pensada para mí?  Oh, no lo creo. ¿El Guardián de la Verdad te mantiene trotando, o estoy muy equivocado?";
			link.l1.go = "shore_3";
		break;
		
		case "shore_3":
			dialog.text = "No tengo ni idea de lo que estás hablando. La daga debe regresar a donde pertenece, y eso es todo lo que necesitas saber. No quisiste entregarla por oro, así que ahora la entregarás por tu propia vida.";
			link.l1 = "¿De verdad piensas, que voy a creer en lo que acabas de decirme? Ya has decidido que no saldré de esta bahía, ¿verdad?";
			link.l1.go = "shore_4";
		break;
		
		case "shore_4":
			dialog.text = "¿Y qué si te doy mi palabra?";
			link.l1 = "¿La palabra de un 'comedor de ranas'? Hm...";
			link.l1.go = "shore_5";
		break;
		
		case "shore_5":
			dialog.text = "Monsieur, te doy una última oportunidad. O entregas la daga que me interesa, o saquearé tu cadáver en unos minutos. La resistencia es inútil, tenemos una ventaja abrumadora en número.";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.SanAntonio")) link.l1 = "Me has sorprendido, eso seguro. ¿De verdad crees que soy un imbécil tan cabezota que metería la cabeza en las fauces de un tiburón sin preocuparme de enganchar mi arpón? ¡Chicos, mátenlos!";
			else link.l1 = "¡El verdadero poder no está en los números, sino en la habilidad, señor!";
			link.l1.go = "shore_6";
		break;
		
		case "shore_6":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto5", "none", "", "", "", 10.0);
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.SanAntonio"))
			{
				PlaySound("interface\abordage_wining.wav");
				PlaySound("interface\abordage_wining.wav");
				for(i=1; i<=10; i++)
				{
					sld = characterFromId("GuardOT_Oursoldier_"+i);
					LAi_SetWarriorType(sld);
					ChangeCharacterAddressGroup(sld, "Shore15", "reload", "reload1_back");
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			sld = CharacterFromID("spa_baseprisoner");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			for(i=1; i<=13; i++)
			{
				sld = characterFromId("GOT_spashore_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_DiegoShoreGuardDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
