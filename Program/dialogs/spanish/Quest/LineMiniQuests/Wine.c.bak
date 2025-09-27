void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "Esto es un error. Informad a los desarrolladores.";
		link.l1 = "¡Claro!";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "Wine_fort":
		dialog.text = "¿Trajiste la botella?";
		if (CheckCharacterItem(pchar, "potionwine"))
		{
			link.l1 = "Sí, así lo hice. Pagué 700 pesos por ello, así que espero 1000 pesos de ti.";
			link.l1.go = "Wine_fort_1";
		}
		link.l2 = "No, estoy trabajando en ello.";
		link.l2.go = "exit";
		NextDiag.TempNode = "Wine_fort";
		break;

	case "Wine_fort_1":
		AddMoneyToCharacter(pchar, 1000);
		RemoveItems(PChar, "potionwine", 1);
		dialog.text = "¡Alabado sea Dios, me estaba secando de sed! ¡Muchas gracias, señor! Aquí tienes tus mil y yo me quedo con tu botella, ¡jajaja! Oye, ya que estamos haciendo unos buenos tratos aquí, tengo otra petición para ti\n ¿Podrías conseguir más vino para mí y mis amigos para nuestro... uso futuro? Acabamos de saquear a una banda de contrabandistas, así que tenemos monedas de sobra, jeje...";
		link.l1 = "Lo siento, compañero, no tengo tiempo para hacer otra carrera de licor para ti.";
		link.l1.go = "Wine_fort_exit";
		link.l2 = "El dinero siempre es bienvenido. ¿Cuántas botellas necesitas?";
		link.l2.go = "Wine_fort_2";
		break;

	case "Wine_fort_exit":
		DelLandQuestMark(npchar);
		WineTraderQMDel();
		dialog.text = "Como desees. ¡Gracias por tu ayuda de todos modos! ¡Salud y a tu buena salud!";
		link.l1 = "¡Sigue con el buen trabajo, soldado!";
		link.l1.go = "exit";
		sld = characterFromId(pchar.questTemp.Wine.id);
		sld.lifeday = 0;
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
		pchar.questTemp.Wine.fail = "true";
		CloseQuestHeader("Wine");
		break;

	case "Wine_fort_2":
		dialog.text = "A 1000 piezas de a ocho por botella, podemos permitirnos comprar sesenta botellas, pero no más. ¡Pero tampoco nos traigas menos de diez, eso solo nos dejará sedientos!";
		link.l1 = "Entendido, no más de 60 botellas y no menos de diez. Traeré tu vino.";
		link.l1.go = "Wine_fort_3";
		break;

	case "Wine_fort_3":
		dialog.text = "¡Benditos sean los pies que traen buenas nuevas de buen licor! Cuento contigo, capitán. ¡Ah, casi lo olvido! Necesitarás traer el licor aquí en menos de una semana, porque mi compañía marina será rotada a la flota en siete días y nos iremos por un par de meses una vez que partamos.";
		link.l1 = "Ya veo. Intentaré ser rápido.";
		link.l1.go = "exit";
		pchar.questTemp.Wine.bottles = "true";
		npchar.lifeday = 7;
		AddQuestRecord("Wine", "1");
		AddQuestUserData("Wine", "sCity", XI_ConvertString("Colony" + pchar.questTemp.Wine.City + "Gen"));
		AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.SName);
		SetFunctionTimerCondition("Soldier_wait", 0, 0, 7, false);
		NextDiag.TempNode = "Wine_fort_check";
		SetFunctionLocationCondition("WineTraderQM", pchar.questTemp.Wine.City + "_town", 0);
		break;

	case "Wine_fort_check":
		dialog.text = "Entonces, capitán, ¿ha traído el vino?";
		if (sti(pchar.items.potionwine) >= 10)
		{
			link.l1 = "Sí, lo he hecho.";
			link.l1.go = "Wine_take";
		}
		link.l2 = "No. Todavía estoy trabajando en ello.";
		link.l2.go = "exit";
		NextDiag.TempNode = "Wine_fort_check";
		break;

	case "Wine_take":
		pchar.questTemp.Wine.Qty = sti(pchar.items.potionwine);
		pchar.questTemp.Wine.Money = sti(pchar.questTemp.Wine.Qty) * 1000;
		if (sti(pchar.items.potionwine) > 60)
		{
			dialog.text = "¡Santo San Arnulf, ruega por nosotros! ¡Eso es mucho vino! ¡Excelente! Lamentablemente, como dije, solo podemos permitirnos sesenta botellas, desafortunadamente no tenemos suficiente dinero para comprar más. Toma tus pesos y cuidaré bien de estas sesenta botellas. Por favor, guarda el resto.";
			link.l1 = "Gracias. ¡Asegúrate de que tú y tus amigos soldados levanten una copa por mi salud!";
			link.l1.go = "Wine_take_1";
			pchar.questTemp.Wine.Money = 60000;
			RemoveItems(PChar, "potionwine", 60);
		}
		else
		{
			dialog.text = "Bienvenido de nuevo. Veamos... Has traído " + sti(pchar.questTemp.Wine.Qty) + " botellas. ¡Bien! Las tomaré. El pago es " + FindRussianMoneyString(sti(pchar.questTemp.Wine.Money)) ".";
			link.l1 = "Gracias. ¡Asegúrate de que tú y tus amigos soldados levanten un vaso a mi salud!";
			link.l1.go = "Wine_take_1";
			RemoveItems(PChar, "potionwine", sti(pchar.questTemp.Wine.Qty));
		}
		break;

	case "Wine_take_1":
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.Wine.Money));
		dialog.text = "Por supuesto que lo haremos, " + GetAddress_Form(NPChar) + "¡El tambor está sonando asamblea, tengo que irme ahora. ¡Adiós!";
		link.l1 = "¡Vientos favorables y mares tranquilos, camarada!";
		link.l1.go = "Wine_take_2";
		break;

	case "Wine_take_2":
		DelLandQuestMark(npchar);
		DialogExit();
		PlaySound("interface\important_item.wav");
		Log_Info("Entregaste el vino");
		pchar.quest.Soldier_wait.over = "yes"; // снять прерывание
		DeleteAttribute(pchar, "questTemp.Wine.City");
		sld = characterFromId(pchar.questTemp.Wine.id);
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
		sld.lifeday = 0;
		CloseQuestHeader("Wine");
		AddCharacterExpToSkill(pchar, "Commerce", 150);	 // торговля
		AddCharacterExpToSkill(pchar, "Leadership", 50); // авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 50);	 // везение
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
