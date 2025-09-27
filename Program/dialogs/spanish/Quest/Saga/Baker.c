// Раймонд Бейкер - палач Сент-Джонса и возможный офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_", 0) != -1)
	{
		i = findsubstr(sAttr, "_", 0);
		NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
		Dialog.CurrentNode = "SetGunBullets2";
	}

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "¿Quieres algo?";
		link.l1 = "No, es nada.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "baker":
		dialog.text = "¡Gracias, Capitán! No puedo ni imaginar qué habría hecho sin usted...";
		link.l1 = "Puedo imaginarlo. Habrías muerto de hambre o terminado en el estómago de un salvaje de Dominica. Pero tienes una oportunidad de pagarme.";
		link.l1.go = "baker_1";
		break;

	case "baker_1":
		dialog.text = "¿Cómo puedo ayudarle, Capitán?";
		link.l1 = "Quiero saber más sobre un hombre. Es nuestro amigo común, por así decirlo. En realidad, un amigo muy cercano tuyo. Me refiero al capitán Butcher. Sí, el que colgaste hace veinte años. ¡Señor, por qué estás tan pálido? ¿Quieres un sorbo de ron?";
		link.l1.go = "baker_2";
		break;

	case "baker_2":
		dialog.text = "¿Te   ha   enviado   él?";
		link.l1 = "¡Tonterías! ¿Cómo puedo ser 'enviado por él' si está muerto? Me interesan más las cosas que ha dejado que el propio Butcher. Cartas, documentos, cosas así. Quizás hayas encontrado algo en sus bolsillos... ¡Espera! No lo entiendo. ¿De verdad crees que Butcher está vivo? ¡Tú mismo lo ejecutaste!";
		link.l1.go = "baker_3";
		break;

	case "baker_3":
		dialog.text = "¡Maldición! No tienes ni idea. Eso significa que no has sido enviado por Butcher como pensé...";
		link.l1 = "Vaya, vaya. Esto se está poniendo más interesante. Parece que Henry tenía todas las razones para temer a Butcher y por eso murió de un ataque al corazón... ¿Butcher está vivo?";
		link.l1.go = "baker_4";
		break;

	case "baker_4":
		dialog.text = "Él es, Capitán... Y ellos me están buscando.";
		link.l1 = "Raymond, me dijeron que no eres un hombre estúpido. No trates de jugar conmigo. Estás a salvo de cualquier amenaza aquí. Dime todo lo que sabes y se me ocurrirá algo para ayudarte. Quizás compartamos enemigos comunes. Empecemos con Butcher.";
		link.l1.go = "baker_5";
		break;

	case "baker_5":
		dialog.text = "¡Está vivo, pero su nombre es diferente ahora! Sus hombres me hicieron una visita la noche de la ejecución. Jackman y otro hombre con un apodo extraño. Por lo que recuerdo, era el 'Ahogado'.";
		link.l1 = "Ahorcado. Henry el Ahorcado.";
		link.l1.go = "baker_6";
		break;

	case "baker_6":
		dialog.text = "¡Correcto! Me ofrecieron un trato simple: morir de la manera más dolorosa o salvar a su capitán. Así que tuve que fingir la ejecución con un equipo especial que había creado en mi tiempo libre. Verás, tal construcción de cinturones y abrazaderas puede distribuir el peso del cuerpo.\nTodo lo que tenía que hacer era conectarlo con un gancho secreto en el lazo. Sin embargo, el 'cadáver' tenía que desempeñar bien su papel. Debo decir que la actuación de Lawrence fue muy creíble, hizo todo bien, excepto que se negó a orinarse encima, debido a...";
		link.l1 = "¿Acabas de llamara Butcher 'Lawrence'?";
		link.l1.go = "baker_7";
		break;

	case "baker_7":
		dialog.text = "Ése es su verdadero nombre. Te dije que se llama Lawrence Beltrope. He estado inquieto desde que regresó al Caribe hace un año. Y cuando supe que algunas personas malas me están buscando...\nIncluso he escrito una confesión para las autoridades por si acaso. La llevo conmigo todo el tiempo porque tengo demasiado miedo de entregarla. Podrían pensar que fui un cómplice voluntario. Por favor, déjame quedarme con tu tripulación. Te juro, soy un excelente médico y puedo ayudarte mucho.";
		link.l1 = "Bien. ¿Y qué hay de los objetos personales de Butcher... eh, de Beltrope? ¿Está relacionado con Thomas Beltrope?";
		link.l1.go = "baker_8";
		break;

	case "baker_8":
		dialog.text = "Ni idea. No tengo nada especial de Beltrope en sí. Pero te daré todo lo que tengo, eres libre de hacer lo que quieras con ello. Todos los papeles relacionados con el tema están en mi bolsa. Guardé todo por si acaso y lo mantengo cerca de mí.\nAquí, echa un vistazo... esta es la leyenda del capitán Butcher, esta es mi confesión... Estas son cosas que pertenecieron a Joshua Leadbeater...";
		link.l1 = "¡Alto! ¿Leadbeater? ¿Quién es ese?";
		link.l1.go = "baker_9";
		break;

	case "baker_9":
		dialog.text = "¡Oh! Era un hombre muy especial. Fue él quien persiguióa Butcher él mismo. La gente lo recordaba como el 'hombre enmascarado'. Fue asesinado poco después de la ejecución de Butcher. ¡Alguien le cortó la garganta con un diente de tiburón! Un solo corte y estaba acabado. Cuando aún estaba vivo, debió haber sufrido mucho. \nSi hubieras visto su rostro bajo la máscara, ¡no era más que carne! Tenía esta página de diario en su bolsillo cuando murió. Debe haber sido de los escritos de Jessica Rose. ¡Historia escalofriante! Léelo, hará que las cosas sean mucho más comprensibles. \nY este es el diente en sí. ¿Puedes ver las letras? S.D.... Lo que sea que signifique. También hay algunas manchas de sangre.";
		link.l1 = "¡Basta! Necesito leer todo detenidamente y pensarlo. Y tú serás mi pasajero o médico del barco hasta que resuelva todo esto. Puedes respirar tranquilo, Raymond, estás seguro en mi barco.";
		link.l1.go = "baker_10";
		break;

	case "baker_10":
		DialogExit();
		sld = characterFromId("Baker_Cap");
		LAi_SetImmortal(sld, false);
		sld.lifeday = 0;
		// sld.ship.hp = 0;
		// sld.SinkTenPercent = true;
		bQuestDisableMapEnter = false;
		GiveItem2Character(pchar, "shark_teeth");
		GiveItem2Character(pchar, "letter_jess");
		GiveItem2Character(pchar, "letter_baker");					 // показания бейкера
		ChangeItemDescribe("letter_baker", "itmdescr_letter_baker"); // Addon-2016 Jason
		AddQuestRecordInfo("Legend_CapBucher", "1");
		AddQuestRecordInfo("Letter_jess", "1");
		AddQuestRecord("Shadows", "5");
		pchar.questTemp.Saga.Shadows = "islatesoro";
		// в офицеры
		npchar.quest.OfficerPrice = sti(pchar.rank) * 500;
		npchar.OfficerWantToGo.DontGo = true; // не пытаться уйти
		npchar.CompanionDisable = true;		  // нельзя в компаньоны
		npchar.loyality = MAX_LOYALITY;
		AddPassenger(pchar, npchar, false);
		SetCharacterRemovable(npchar, true);
		npchar.Payment = true;
		npchar.DontClearDead = true;
		NextDiag.CurrentNode = "Baker_officer";
		npchar.OfficerImmortal = true;
		npchar.Health.HP = 60.0;
		npchar.Health.maxHP = 60.0;
		SetCharacterPerk(npchar, "ShipEscape");
		LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
		AddCharacterExpToSkill(pchar, "Sailing", 50);
		AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

	//--> ----------------------------------- офицерский блок ------------------------------------------
	case "Baker_officer":
		dialog.text = "¿Sí, capitán?";
		Link.l1 = "¡Escucha mi orden!";
		Link.l1.go = "stay_follow";

		////////////////////////казначей///////////////////////////////////////////////////////////
		// boal отчёт о корабле
		if (CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
		{
			Link.l11 = "Raymond, dame un informe completo del barco.";
			Link.l11.go = "QMASTER_1";

			// Warship. Автозакупка товара
			Link.l12 = "Quiero que compres ciertos bienes cada vez que estemos atracados.";
			Link.l12.go = "QMASTER_2";
		}

		link.l2 = "No es nada. ¡Retírate!";
		link.l2.go = "exit";
		NextDiag.TempNode = "Baker_officer";
		break;

	/////////////////////////// ответы для казначея ///////////////////////////////////
	case "QMASTER_1":
		dialog.Text = "Vamos, Capitán, soy médico, no intendente. Aunque, en el pasado, solía trabajar en una capacidad diferente... no importa. Realmente no hago contabilidad, lo siento.";
		Link.l1 = "Está bien, que así sea. Eres mi médico, tal como acordamos después de que te uniste a mi tripulación.";
		Link.l1.go = "exit";
		break;

	case "QMASTER_2":
		dialog.text = "Capitán, para ser completamente honesto, nunca adquirí mucha experiencia con el comercio. Nunca regateé, nunca seguí etiquetas de precios. Además... Preferiría seguir quedándome en el barco, si no le importa. Algunos de esos mercaderes podrían reconocerme y antes de que te des cuenta los hombres enmascarados llegarían en breve.";
		link.l1 = "Entonces, seguirás viviendo con miedo a tu pasado... Bien, exhala, lo haré yo mismo.";
		Link.l1.go = "exit";
		break;

	case "stay_follow":
		dialog.Text = "¿Órdenes?";
		Link.l1 = "¡Quédate aquí!";
		Link.l1.go = "Boal_Stay";
		Link.l2 = "¡Sígueme y no te quedes atrás!";
		Link.l2.go = "Boal_Follow";
		sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
		if (sGun != "")
		{
			rItm = ItemsFromID(sGun);
			if (CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
			{
				Link.l3 = "Cambia el tipo de munición para tu arma de fuego.";
				Link.l3.go = "SetGunBullets";
			}
		}
		break;

	case "SetGunBullets":
		Dialog.Text = "Eligiendo el tipo de munición:";
		sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
		rItm = ItemsFromID(sGun);
		makearef(rType, rItm.type);
		for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
		{
			sAttr = GetAttributeName(GetAttributeN(rType, i));
			sBullet = rItm.type.(sAttr).bullet;
			rItem = ItemsFromID(sBullet);
			attrL = "l" + i;
			Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
			;
			Link.(attrL).go = "SetGunBullets1_" + i;
		}
		break;

	case "SetGunBullets2":
		i = sti(NPChar.SetGunBullets) + 1;
		sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
		rItm = ItemsFromID(sGun);
		sAttr = "t" + i;
		sBullet = rItm.type.(sAttr).bullet;
		LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
		LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
		NextDiag.CurrentNode = NextDiag.TempNode;
		rItem = ItemsFromID(sBullet);
		notification(GetFullName(NPChar) + " " + XI_ConvertString("AmmoSelectNotif") + GetConvertStr(rItem.name, "ItemsDescribe.txt") + "", "AmmoSelect");
		DeleteAttribute(NPChar, "SetGunBullets");
		DialogExit();
		break;

	case "Boal_Stay":
		Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
		AddDialogExitQuestFunction("LandEnc_OfficerStay");
		dialog.Text = "¡Hay un cambio de disposición!";
		Link.l1 = "Despedido.";
		Link.l1.go = "Exit";
		Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
		break;

	case "Boal_Follow":
		SetCharacterTask_FollowCharacter(Npchar, PChar);
		dialog.Text = "¡Hay un cambio de disposición!";
		Link.l1 = "Despachado.";
		Link.l1.go = "Exit";
		break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
