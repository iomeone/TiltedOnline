#pragma once

struct UpdateEvent;
struct ConnectedEvent;
struct DisconnectedEvent;
struct ReferenceSpawnedEvent;
struct EquipmentChangeEvent;
struct FormIdComponent;
struct ActionEvent;
struct AssignCharacterResponse;
struct CharacterSpawnRequest;
struct ServerReferencesMoveRequest;
struct NotifyInventoryChanges;
struct NotifyFactionsChanges;
struct NotifyRemoveCharacter;

struct World;
struct TransportService;

struct CharacterService
{
    CharacterService(World& aWorld, entt::dispatcher& aDispatcher, TransportService& aTransport) noexcept;
    ~CharacterService() noexcept = default;

    TP_NOCOPYMOVE(CharacterService);

    void OnFormIdComponentAdded(entt::registry& aRegistry, entt::entity aEntity) const noexcept;
    void OnFormIdComponentRemoved(entt::registry& aRegistry, entt::entity aEntity) const noexcept;
    void OnUpdate(const UpdateEvent& acUpdateEvent) noexcept;
    void OnConnected(const ConnectedEvent& acConnectedEvent) const noexcept;
    void OnDisconnected(const DisconnectedEvent& acDisconnectedEvent) const noexcept;
    void OnAssignCharacter(const AssignCharacterResponse& acMessage) const noexcept;
    void OnCharacterSpawn(const CharacterSpawnRequest& acMessage) const noexcept;
    void OnReferencesMoveRequest(const ServerReferencesMoveRequest& acMessage) const noexcept;
    void OnActionEvent(const ActionEvent& acActionEvent) const noexcept;
    void OnEquipmentChangeEvent(const EquipmentChangeEvent& acEvent) noexcept;
    void OnInventoryChanges(const NotifyInventoryChanges& acEvent) const noexcept;
    void OnFactionsChanges(const NotifyFactionsChanges& acEvent) const noexcept;
    void OnRemoveCharacter(const NotifyRemoveCharacter& acEvent) const noexcept;

private:

    void RequestServerAssignment(entt::registry& aRegistry, entt::entity aEntity) const noexcept;
    void CancelServerAssignment(entt::registry& aRegistry, entt::entity aEntity) const noexcept;

    void RunLocalUpdates() const noexcept;
    void RunRemoteUpdates() const noexcept;
    void RunInventoryUpdates() noexcept;
    void RunFactionsUpdates() const noexcept;

    World& m_world;
    entt::dispatcher& m_dispatcher;
    TransportService& m_transport;

    Set<uint32_t> m_charactersWithInventoryChanges;

    entt::scoped_connection m_formIdAddedConnection;
    entt::scoped_connection m_formIdRemovedConnection;
    entt::scoped_connection m_updateConnection;
    entt::scoped_connection m_actionConnection;
    entt::scoped_connection m_equipmentConnection;
    entt::scoped_connection m_inventoryConnection;
    entt::scoped_connection m_factionsConnection;
    entt::scoped_connection m_removeCharacterConnection;
    entt::scoped_connection m_connectedConnection;
    entt::scoped_connection m_disconnectedConnection;
    entt::scoped_connection m_assignCharacterConnection;
    entt::scoped_connection m_characterSpawnConnection;
    entt::scoped_connection m_referenceMovementSnapshotConnection;
};
